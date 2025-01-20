#include"./process.hpp"
#include"../context/interrupts.hpp"
#include "pico/stdlib.h"

unsigned int* process::prepare_stack(func function){
    printf("Preparing stack...\n");

        this->stack += 256 - 17; /*because the stack grows downwards, we add the space minus the next 4*/
        this->stack[8] = 0xFFFFFFFD; /*This is the kernel saved LR, we are goint to return the end of the interrupt to restore the hardware saved registers*/
        this->stack[15] = (unsigned int)function; /*This is the PC register, we are going to point it to the start of the requested function*/
        this->stack[16] = 0x01000000; /*Tell the PSR to run in Thumb state by putting it in the default state*/
        this->stack = _save_kernel(this->stack); /*inmediately change into the task (To review once we have the priority check)*/
        /*Redifine the stack process pointer to the changes made*/
        printf("Stack prepared: %p\n",this->stack);
        return this->stack;
    }
 process process::create(func function, unsigned int* stack){
    printf("now in the create process function\n");

    process p;
    p.stack = stack;
    p.status = program_state::RUNNING;
    p.psp = p.prepare_stack(function);
    printf("Process stack prepared\n");

    return p;
}

unsigned int process::start(){
    printf("starting process...\n");

    this->psp = _save_kernel(this->psp);
    printf("Process started with psp: %p\n",this->stack);
    return 0;
}   

