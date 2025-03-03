#include"../interrupts.hpp"

    #ifndef KERNEL32_PREEMPTIVE
        #define init_kernel() _switch_handler()
        /*void init_kernel(){
            _switch_handler();
            return;
        }*/
    #else
        void init_kernel(){
            
            KERNEL32::set_hw_systick_priority();
        }
    #endif