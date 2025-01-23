#ifndef KERNEL32_PROCESS
#define KERNEL32_PROCESS
enum{STOPPED,SLEEP,READY,RUNNING,INTERRUPTED} typedef program_state;

typedef void (*func)(void);
class process{
    private:
     unsigned int* prepare_stack(func function);

    public:
    int PID;
    program_state status;
    unsigned int* stack;

    process create(func function);
    unsigned int start();
    unsigned int prepare_frame(unsigned int* stack, unsigned int PID);
};


#include"./process.cpp"

#endif