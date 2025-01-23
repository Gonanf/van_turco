#ifndef KERNEL32_INTERRUPTS
#define KERNEL32_INTERRUPTS
extern "C"{
    unsigned int* _switch_context(unsigned int* psp);
    void _switch_handler(unsigned int* psp);
}
#endif