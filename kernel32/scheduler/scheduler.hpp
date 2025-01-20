#ifndef KERNEL32_SCHEDULER
#define KERNEL32_SCHEDULER
#include"../process/process.hpp"
class scheduler{
    public:
    process programs[3];
    unsigned int stack_programs[3][256];
    unsigned int size_programs = 0;
    unsigned int current_program = 0;
    unsigned int create_process(func function);
    unsigned int start_scheduling();
};

#include"./scheduler.cpp"

#endif