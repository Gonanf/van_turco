#ifndef KERNEL32_SYSCALL
#define KERNEL32_SYSCALL
    extern "C" unsigned int syscall(unsigned int* r0);
    #include "./syscall.cpp"
#endif