#ifndef KERNEL32_PROCESS
#define KERNEL32_PROCESS

typedef void (*func)(void);
class process{
    public:
    int PID;
    program_state status;
    unsigned int* stack;
    messages queque;
    

    process create(func function);
    unsigned int start();
    unsigned int prepare_frame(unsigned int* stack, unsigned int PID);
};


#include"./process.cpp"

#endif