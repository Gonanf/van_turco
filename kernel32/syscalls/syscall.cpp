#include "./syscall.hpp"
#include "../scheduler/scheduler.hpp"
#include "pico/stdlib.h"

extern "C" unsigned int syscall(unsigned int *r0)
{
    if (global_scheduler != nullptr)
    {
        printf("R0 = %d\n", r0[9]);
    }
    else
    {
        return 0;
    }
    switch (r0[9] /*9 is the index for the hardware saved r0, see svc.s*/)
    {
    case WAIT:
       {
        /*Set r0 into the wait time (We are going to use this later in the scheduler)*/
          r0[9] = to_ms_since_boot(get_absolute_time()) + r0[10];
        global_scheduler->programs[global_scheduler->current_program].status = program_state::SLEEP;
        
        return 1;
       }
        break;
    case EXIT:
        return global_scheduler->remove_process(global_scheduler->current_program);
        break;
    default:
        break;
    }
    return 0;
}
