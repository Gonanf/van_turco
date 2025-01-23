#include"./process.hpp"
#include"../context/interrupts.hpp"
#include "pico/stdlib.h"

 process process::create(func function){
    this->status = program_state::READY;
    this->stack[15] = (unsigned int)function; /*This is the PC register, we are going to point it to the start of the requested function*/
    return *this;
}

unsigned int process::start(){
    this->status = program_state::RUNNING;
    this->stack = _switch_context(this->stack);
    return 0;
}   


unsigned int process::prepare_frame(unsigned int* stack, unsigned int PID){
    this->PID = PID;

    this->stack = stack;
    this->stack += STACK_FRAME_SIZE - 17; /*because the stack grows downwards, we add the space minus the next 4*/
    this->stack[8] = 0xFFFFFFFD; /*This is the kernel saved LR, we are goint to return the end of the interrupt to restore the hardware saved registers*/
    this->stack[16] = 0x01000000; /*Tell the PSR to run in Thumb state by putting it in the default state*/
    this->status = program_state::STOPPED;
    printf("STACK: %p\n",this->stack);
    return 0;
}

