#include "hardware/structs/systick.h"
#include "hardware/sync.h"

void set_hw_systick_priority(){
    hw_set_bits((io_rw_32 *)(PPB_BASE + M0PLUS_SHPR2_OFFSET), M0PLUS_SHPR2_BITS);
    hw_set_bits((io_rw_32 *)(PPB_BASE + M0PLUS_SHPR3_OFFSET), M0PLUS_SHPR3_BITS);
    return;
}

void reset_systick(){
    systick_hw -> csr = 0b00000000; //Control Status Register, this code disables the timer
    __dsb();
    hw_set_bits  ((io_rw_32 *)(PPB_BASE + M0PLUS_ICSR_OFFSET),M0PLUS_ICSR_PENDSTCLR_BITS);
    systick_hw -> rvr = TIME_SLICE - 1UL; //Reset Value Register, value to time on reset
    systick_hw -> cvr = 0; //Reset the Current Value Register
    systick_hw -> csr = 0b00000011; //Enable the timer and the interrupts
    return;
}