#include "pico/stdlib.h"
#include"./sdk_lock.h"
#include "../scheduler/scheduler.hpp"
#include "libarbys/libarbys.hpp"

lock_owner_id_t get_task_id(void){
    return global_scheduler == nullptr ? 0 : global_scheduler->current_program;
}

void kernel_wait(void){
    if (global_scheduler != nullptr) LIB::yield();
    return;
}

bool kernel_wait_until(absolute_time_t until){
    if (global_scheduler != nullptr) LIB::yield();
    return time_reached(until);
}