#ifndef KERNEL32_SYSCALL
#define KERNEL32_SYSCALL
    extern "C" unsigned int syscall(unsigned int* r0);
    enum{WAIT,EXIT} typedef syscall_type;
    #include "./syscall.cpp"
#endif