.thumb
.syntax unified

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

.type isr_systick, %function
.global isr_systick
isr_systick:
/*Save process */
        mrs r0, psp /*r0 is now the process stack pointer (top of the process stack)*/
        push_r0 lr
        __save_context
        msr psp, r0 /*Now R0 is a parameter for the syscall, containing the process stack */

        /*Now the process is saved into the stack */
        /*Now we load the kernel from the Main Stack Pointer (Remembering we are in handler mode at this interrupt) */
        mov r0, sp
        __load_context
        pop_r0 r12
        msr psr_nzcvq, ip
        mov sp, r0
        mrs r0, psp /*return the process stack pointer to update the process class */
         pop {pc} /*Now it is getting LR (The address it should return) as the program counter (The address it is executing) */