#ifndef KERNEL32_PROCESS
#define KERNEL32_PROCESS
enum{SLEEP,READY,RUNNING,INTERRUPTED} typedef program_state;

typedef void (*func)(void);
class process{
    private:
     unsigned int* prepare_stack(func function);

    public:
    int PID;
    char *name;
    program_state status;
    unsigned int* stack;
    unsigned int* psp;

     static process create(func function, unsigned int* stack);
     unsigned int start();
};


#include"./process.cpp"

#endif