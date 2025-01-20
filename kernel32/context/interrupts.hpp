#ifndef KERNEL32_INTERRUPTS
#define KERNEL32_INTERRUPTS
extern "C"{
    unsigned int* _save_kernel(unsigned int* psp);
    void _switch_handler(unsigned int* psp);
}
#endif