.thumb
.syntax unified


/**
 * @brief This interrupt works with the SuperVisorCall (SVC), triggering an interrupt for the Interrupt Service Rutine (ISR) that saves the exeption frame into the process stack
 * 
 * https://s-o-c.org/cortex-m0-stack-frames-and-registers-during-hardfault/
 * 
 * 
 * xPSR [16]
 * PC
 * LR  (the original one, the one before the interrupt, we are not going to touch this)
 * R12
 * R3
 * R2
 * R1
 * R0
 * 
 * So all of these registers are free and already allocated into the process stack, whe have to allocate the following,
 * 
 * > Save from here
 * LR [8] (8 in the process stack, 9 in kernel stack)(We save twice because this one will hold the thread mode code to return to PSP and resume the remaining registers )
 * (PSR) -> Only for the kernel,
 * R11
 * R10
 * R9
 * R8
 * R7
 * R6
 * R5
 * R4 > Load from here
 */

/*This can be more efficient and fast by making 4 macros, load_kernel, save_kernel, load_process and save_process
being that the save and load kernel would use the push and pop in this order 

mov r0, r12
mov r1, lr
push {r0-r1}
mov r0, r4
mov r1, r5
mov r2, r6
mov r3, r7
mov r4, r8
mov r5, r9
mov r6, r10
mov r7, r11
push {r0-r7}

pop{r0-r7}
mov r11, r0
mov r10, r1
mov r9, r2
mov r8, r3
pop {r0, lr}
mov r12, r0


and this could be more efficient if i didn't care about order
 */

.macro push_r0 r
        mov r1, \r
        subs r0, #4
        str r1, [r0]
.endm


.macro pop_r0 r
        ldr r1, [r0]
        adds r0, #4
        mov \r, r1
.endm


.macro __save_context
        push_r0 r11
        push_r0 r10
        push_r0 r9
        push_r0 r8
        push_r0 r7
        push_r0 r6
        push_r0 r5
        push_r0 r4
.endm

.macro __load_context
        pop_r0 r4
        pop_r0 r5
        pop_r0 r6
        pop_r0 r7
        pop_r0 r8
        pop_r0 r9
        pop_r0 r10
        pop_r0 r11
.endm


.type isr_svcall, %function
.global isr_svcall
isr_svcall:
        /*Save process */
        mrs r0, psp /*r0 is now the process stack pointer (top of the process stack)*/
        push_r0 lr
        __save_context
        msr psp, r0

        /*Now the process is saved into the stack */
        /*Now we load the kernel from the Main Stack Pointer (Remembering we are in handler mode at this interrupt) */
        mov r0, sp
        __load_context
        pop_r0 r12
        msr psr_nzcvq, ip
        mov sp, r0
        mrs r0, psp /*return the process stack pointer to update the process class */
         pop {pc} /*Now it is getting LR (The address it should return) as the program counter (The address it is executing) */
        

.global _switch_context
_switch_context:
        /*now saving kernel */
        mrs ip, psr /*Save into r12 the process state register */
        mov r2, r0
        mrs r0, msp
        push_r0 lr
        push_r0 r12

        __save_context

        msr msp, r0

        /*load process */
        mov r0, r2
        /*R0 is a parameter from the interrupts.c that is a pointer to the PSP */
        __load_context
        pop_r0 lr

        msr psp, r0 /*adjust the process stack pointer into the adress withouth the saved registers */
        bx lr /*jump to resume process */

.global _switch_handler
_switch_handler:
        mrs ip, psr /*Save into r12 the process state register */
        mov r2, r0

        mrs r0, msp

        push_r0 lr
        push_r0 r12
        
        __save_context

        msr msp, r0


        msr psp, r2 /*R0 is a parameter */
        movs r0, #2 /*Privileged and in thread mode (Use the psp)*/
        msr control, r0
        isb /*clear the pipeline */
        svc #0 /*Switch again into the kernel but now in handler mode */

