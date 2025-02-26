#include "./syscall.hpp"
#include "../scheduler/scheduler.hpp"
#include "pico/stdlib.h"
unsigned int prueba[] = {10,10,10};

extern "C" unsigned int syscall(unsigned int *r0)
{
    if (global_scheduler == nullptr)
    {
        return 0;
    }
    switch (r0[9] /*9 is the index for the hardware saved r0, see svc.s*/)
    {
    case YIELD:
       {
        /*Set r1 into the wait time (We are going to use this later in the scheduler)*/
         /* r0[10] = to_ms_since_boot(get_absolute_time()) + r0[10];
        global_scheduler->programs[global_scheduler->current_program].status = program_state::SLEEP;*/
        return 1;
       }
        break;
    case WAIT:
       {
        /*Set r1 into the wait time (We are going to use this later in the scheduler)*/
        r0[10] = to_ms_since_boot(get_absolute_time()) + r0[10];
        global_scheduler->programs[global_scheduler->current_program].status = program_state::SLEEP;
        return 1;
       }
        break;
    case EXIT:
        /*
        Implement this as a message
        for (int i = 0; i < PROCESS_LIMIT;i++){
            if (global_scheduler->programs[i].status == program_state::SLEEP && global_scheduler->programs[i].stack[9] == WAIT_PID && global_scheduler->programs[i].stack[10] == global_scheduler->current_program){
                global_scheduler->programs[i].status = program_state::READY;
                global_scheduler->programs[i].stack[9] = 0;
            }
        }*/
        
        return global_scheduler->remove_process(global_scheduler->current_program);
        break;
    case SEND:
            /*R0 = 2 (Send message), R1 = {PID} (Destiny) R2 = {TYPE} R3 = {DATA}*/
            if (r0[10] < 0 || r0[10] >= PROCESS_LIMIT){
                r0[9] = -1;
                return 0;
            }
            if (global_scheduler->programs[r0[10]].status == program_state::STOPPED){
                r0[9] = -2;
                return 0;
            }
            global_scheduler->programs[r0[10]].queque.push(_queque_message{r0[11],r0[12],global_scheduler->current_program});
            KERNEL32::print("PID = %d\n",r0[10]);
            return 1;
        break;
    case RECV:
            {/*R0 = {TYPE}, R1 = {DATA}*/
            if (global_scheduler->programs[global_scheduler->current_program].queque.end <= 0){
                r0[9] = -1;
                return 0;
            }
            _queque_message msg = global_scheduler->programs[global_scheduler->current_program].queque.pop(); 
            global_scheduler->programs[global_scheduler->current_program].queque.current_message = msg;
            KERNEL32::print("TPY: %d DATA: %d FROM: %d\n",msg.type,msg.data,msg.from);
            r0[9] = (unsigned int)&global_scheduler->programs[global_scheduler->current_program].queque.current_message.type;
            return 1;
            }
        break;
    case GETPINFO:
        r0[9] = global_scheduler->current_program;
        return 0;
    break;
    default:
        break;
    }
    return 0;
}
