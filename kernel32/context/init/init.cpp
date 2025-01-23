#include"../interrupts.hpp"

unsigned int init_kernel(){
    unsigned int init_stack[17];
    _switch_handler(init_stack + 17); /*Startup: Change to the handler mode (By causing an interrupt in a process stack)*/
    return 0;
}


