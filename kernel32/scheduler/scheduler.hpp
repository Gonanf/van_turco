#ifndef KERNEL32_SCHEDULER
#define KERNEL32_SCHEDULER
#include"../process/process.hpp"
/*264KB of RAM, 4kb of stack memory, in words that would be 1024 in a 32 bits system,we can only store 3 applications with 256 word*/
class scheduler{
    public:
    process programs[PROCESS_LIMIT];
    unsigned int stack_programs[PROCESS_LIMIT][STACK_FRAME_SIZE];
    unsigned int size_programs = 0;
    unsigned int current_program = 0;
    int create_process(func function); /*returns the index of the proccess, -1 if not able to create*/
    unsigned int start_scheduling();
    unsigned int remove_process(unsigned int PID);
    unsigned int prepare_scheduler();
};

extern scheduler* global_scheduler = nullptr;


#include"./scheduler.cpp"

#endif