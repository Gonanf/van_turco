#include"./scheduler.hpp"
#include"pico/stdlib.h"
int scheduler::create_process(func function){
    printf("Creating process...\n");
    int return_value = -1;
    for (int i = 0; i < PROCESS_LIMIT; i++){
        if (this->programs[i].status == program_state::STOPPED){
            this->programs[i].create(function);
            return_value = i;
            printf("Proccess created\n");
            break;
        }
    }
    return return_value;
}

unsigned int scheduler::start_scheduling(){
int iter = 0;
    printf("%d\n",this->programs[0].stack - this->programs[1].stack);
     for (int i = 0; i < PROCESS_LIMIT; i++){
        printf("%d = %d\n",i,this->programs[i].status);
    }
    while (true){
        if (this->current_program > 2){
            this->current_program = 0;
        }

        switch (this->programs[this->current_program].status)
        {
        case program_state::SLEEP:
            if (to_ms_since_boot(get_absolute_time()) > this->programs[this->current_program].stack[9]){
                this->programs[this->current_program].status = program_state::READY;
            }
            break;
        case program_state::STOPPED:
        break;

        default:
         this->programs[this->current_program].start();
            break;
        }

        //printf("%d\n",iter++);
        this->current_program++;
    }
}

unsigned int scheduler::prepare_scheduler(){
    for (int i = 0; i < PROCESS_LIMIT; i++){
        printf("Preparing frame for process %d, with stack %p\n",i,this->stack_programs[i]);
        this->programs[i].prepare_frame(this->stack_programs[i],i);
    }
    return 0;
}

unsigned int scheduler::remove_process(unsigned int PID){
    this->programs[PID].prepare_frame(this->stack_programs[PID],PID);
    return 0;
}
