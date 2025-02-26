#ifndef KERNEL32_PREEMPTIVE
#define KERNEL32_PREEMPTIVE
    void set_hw_systick_priority();
    void reset_systick();
    #include "./systick.cpp"

#endif