#include "hardware/structs/systick.h"
#include "hardware/sync.h"

void set_hw_systick_priority(){
    hw_set_bits((io_rw_32 *)(PPB_BASE + M0PLUS_SHPR2_OFFSET), M0PLUS_SHPR2_BITS);
    hw_set_bits((io_rw_32 *)(PPB_BASE + M0PLUS_SHPR3_OFFSET), M0PLUS_SHPR3_BITS);
    return;
}

void reset_systick(){
    unsigned int slice = TIME_SLICE;
    systick_hw -> csr = 0; //Control Status Register, this code disables the timer
    __dsb();
    __isb();    
    hw_set_bits((io_rw_32 *)(PPB_BASE + M0PLUS_ICSR_OFFSET),M0PLUS_ICSR_PENDSTCLR_BITS);
    systick_hw -> rvr = (slice) - 1UL; //Reset Value Register, value to time on reset
    systick_hw -> cvr = 0; //Reset the Current Value Register

    uint32_t icsr = *(io_rw_32 *)(PPB_BASE + M0PLUS_ICSR_OFFSET);
    
    if (!(icsr & M0PLUS_ICSR_PENDSTCLR_BITS)) {
        KERNEL32::print("Cleared %d %d %d\n",systick_hw -> rvr,systick_hw -> cvr,systick_hw -> csr);
        systick_hw->csr = 0x03;  // Enable timer and interrupt
    }
        KERNEL32::print("Exiting");
}