#include"../interrupts.hpp"
unsigned int init(){
    unsigned int init_stack[32];
    _switch_handler(init_stack + 32); /*Startup: Change to the handler mode (By causing an interrupt in a process stack)*/
    return 0;
}