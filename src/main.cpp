#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "vga_test/vga.h"
#include "libarbys/libarbys.hpp"
#include "../kernel32/kernel32.hpp"

#ifndef CYW43_WL_GPIO_LED_PIN
#define CYW43_WL_GPIO_LED_PIN 0
#endif

void sleep_example(void){
    while (true)
    {
        printf("Sleeping for 1 second\n");
        asm volatile("mov r0, #0");
        asm volatile("ldr r1, =1000");
        asm volatile("svc #0");
        printf("I am awake!\n");

    }
}

void exit_example(void){
    while (true)
    {
        printf("Exiting\n");
        asm volatile("mov r0, #1");
        asm volatile("svc #0");
        printf("This should not be displayed");
    }
    
}

void test3(void){
    while (true)
    {
        printf("test3\n");
        asm volatile("svc #0");
    }
    
}

/**
 * @brief main execution point of the microkernel
 *
 * @return int
 */
int main()
{
    stdio_init_all();
    cyw43_arch_init();
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);
    // start_vga_test();
    string_L buffer;
    buffer.allocate(1024);
    printf("Starting\n");

    KERNEL32::scheduler sch;
    KERNEL32::init_kernel();
    printf("Kernel started\n");
    global_scheduler = &sch;
    sch.prepare_scheduler();
    sch.create_process(sleep_example);
    sch.create_process(exit_example);
    //sch.create_process(test3);
    sch.start_scheduling();
    while (true)
    {

            promise_L prom = buffer.read_character();
            if (prom.is_done)
            {
                buffer.split();
                printf("finished: %d\n",buffer.size);
                buffer.empty();
                printf("finished2: %d\n",buffer.size);
                buffer.print();
            }
           
    }

    return 0;
}
