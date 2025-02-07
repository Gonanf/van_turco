#ifndef KERNEL32
#define KERNEL32

namespace KERNEL32{
        #define PROCESS_LIMIT 7
    #define STACK_FRAME_SIZE 256
    #define MAX_QUEQUE 32
    #define MAX_OUTPUT 1024 //Size in bytes
    #define MAX_INPUT 1024 //Size in bytes

    enum{STOPPED,SLEEP,READY,RUNNING,INTERRUPTED} typedef program_state;
    enum{WAIT,EXIT,SEND,RECV,GETPID,PRINTC,GETC} typedef syscall_type;

    #include"./loggin/logs.hpp"


    #include"./context/interrupts.hpp"
    #include"./context/init/init.hpp"
    #include"./messages/messages.hpp"
    #include "./executables/executable.hpp"
    #include"./process/process.hpp"
    #include"./scheduler/scheduler.hpp"
    
    #include"./syscalls/syscall.hpp"


    
}
#endif