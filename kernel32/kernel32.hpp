#ifndef KERNEL32
#define KERNEL32
namespace KERNEL32{
        #define PROCESS_LIMIT 7
    #define STACK_FRAME_SIZE 256

    #include"./context/interrupts.hpp"
    #include"./context/init/init.hpp"
    #include"./process/process.hpp"
    #include"./scheduler/scheduler.hpp"
    #include"./syscalls/syscall.hpp"
    
}
#endif