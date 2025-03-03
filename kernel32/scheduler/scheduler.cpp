#include"./scheduler.hpp"
#include"pico/stdlib.h"
int scheduler::create_process(func function){
    KERNEL32::print("Creating process...\n");
    int return_value = -1;
    for (int i = 0; i < PROCESS_LIMIT; i++){
        if (this->programs[i].status == program_state::STOPPED){
            this->programs[i].create(function);
            return_value = i;
            KERNEL32::print("Proccess created\n");
            break;
        }
    }
    return return_value;
}

unsigned int scheduler::start_scheduling(){
        #ifdef KERNEL32_PREEMPTIVE
            _switch_handler();
        #endif
    while (true){
        #ifdef KERNEL32_PREEMPTIVE
            KERNEL32::reset_systick();
        #endif
        if (this->current_program > PROCESS_LIMIT){
            this->current_program = 0;
        }

        switch (this->programs[this->current_program].status)
        {
        case program_state::SLEEP:
            if (to_ms_since_boot(get_absolute_time()) > this->programs[this->current_program].stack[10]){
                this->programs[this->current_program].status = program_state::READY;
            }
        break;
        case program_state::STOPPED:
        break;

    /*Story: I used to put this following code in default but it ended up executing process that where not running or ready*/
        case program_state::RUNNING:
        case program_state::READY:
        
         this->programs[this->current_program].start();
            break;

        default:
        break;
        }

        this->current_program++;
    }
}

unsigned int scheduler::prepare_scheduler(){
    KERNEL32::print("Stack: %p --- %p (Difference = %p), Memory: %d words \n",this->stack_programs, this->stack_programs + (STACK_FRAME_SIZE * PROCESS_LIMIT),(this->stack_programs + (STACK_FRAME_SIZE * PROCESS_LIMIT)) -this->stack_programs,(STACK_FRAME_SIZE * PROCESS_LIMIT));
    for (int i = 0; i < PROCESS_LIMIT; i++){
        KERNEL32::print("Preparing frame for process %d, with stack %p\n",i,this->stack_programs[i]);
        this->programs[i].prepare_frame(this->stack_programs[i],i);
    }
    return 0;
}

unsigned int scheduler::remove_process(unsigned int PID){
    this->programs[PID].prepare_frame(this->stack_programs[PID],PID);
    return 0;
}
