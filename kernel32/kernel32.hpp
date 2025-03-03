#ifndef KERNEL32
#define KERNEL32

namespace KERNEL32{
    #define PROCESS_LIMIT 7
    #define STACK_FRAME_SIZE 256 // 1kb of stack memory
    #define MAX_QUEQUE 32
    #define TIME_SLICE 1000 //In microseconds

    enum{STOPPED,SLEEP,READY,RUNNING,INTERRUPTED} typedef program_state;
    enum{YIELD,WAIT,EXIT,SEND,RECV,GETPINFO} typedef syscall_type;

    #include"./loggin/logs.hpp"
    #include"./preemptive/systick.hpp"
    #include"./context/interrupts.hpp"  
    #include"./context/init/init.hpp"
    #include"./messages/messages.hpp"
    #include"./executables/executable.hpp"
    #include"./process/process.hpp"
    #include"./scheduler/scheduler.hpp"
    #include"./syscalls/syscall.hpp"
    #include"./preemptive/sdk_lock.h"
    
}
#endif