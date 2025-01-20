#include"./scheduler.hpp"
#include"pico/stdlib.h"
unsigned int scheduler::create_process(func function){
    printf("Creating process...\n");
    this->programs[this->size_programs] = process::create(function, this->stack_programs[this->size_programs]);
    this->size_programs++;
    printf("Proccess created\n");
    return 0;
}

unsigned int scheduler::start_scheduling(){
    printf("Scheduling...\n");

    while (true){
        if (this->current_program > 2){
            this->current_program = 0;
        }
        this->programs[this->current_program].start();
        this->current_program++;
    }
}
