#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "vga_test/vga.h"
#include "libarbys/libarbys.hpp"
#include "../kernel32/kernel32.hpp"

#ifndef CYW43_WL_GPIO_LED_PIN
#define CYW43_WL_GPIO_LED_PIN 0
#endif

void sleep_example(void){
    for(int i = 0; i < 10; i++)
    {
        KERNEL32::print("Sleeping for 1 second\n");
        asm volatile("mov r0, #0");
        asm volatile("ldr r1, =1000");
        asm volatile("svc #0");
        KERNEL32::print("I am awake!\n");
    }
    asm volatile("mov r0, #1");
    asm volatile("svc #0");
}

void exit_example(void){
    while (true)
    {
        KERNEL32::print("Exiting\n");
        asm volatile("mov r0, #1");
        asm volatile("svc #0");
        KERNEL32::print("This should not be displayed");
    }
    
}

void send_example(void){
        KERNEL32::print("Sending message...\n");
        asm volatile("mov r0, #2");
        asm volatile("mov r1, #3");
        asm volatile("mov r2, #2");
        asm volatile("mov r3, #10");
        asm volatile("svc #0");
        KERNEL32::print("Message sended\n");
        asm volatile("mov r0, #1");
        asm volatile("svc #0");
    
}

void recv_example(void){
        asm volatile("mov r0, #4");
        asm volatile("svc #0");
        unsigned int PID;
        asm volatile("mov %0, r0" : "=r" (PID));
        unsigned int* msg_dir;
        KERNEL32::print("Getting message... PID: %d\n",PID);
        while(true){
            asm volatile("mov r0, #3");
        asm volatile("svc #0");

        asm volatile("mov %0, r0" : "=r" (msg_dir));

        if (*(msg_dir) != -1){
            break;
        }
        }
        
        KERNEL32::print("Message gotten: %d/%d from PID: %d\n",*(msg_dir),*(msg_dir + 1),*(msg_dir + 2));
        
        asm volatile("mov r0, #1");
        asm volatile("svc #0");
    
}

void shell_basic(void){
    string_L buffer;
    buffer.allocate(1024);
    while (true)
    {
            promise_L prom = buffer.read_character();
            if (prom.is_done)
            {
                buffer.split();
                KERNEL32::print("finished: %d\n",buffer.size);
                buffer.empty();
                KERNEL32::print("finished2: %d\n",buffer.size);
                buffer.print();
            }
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

    KERNEL32::print("Starting\n");

    KERNEL32::scheduler sch;
    KERNEL32::init_kernel();
    KERNEL32::print("Kernel started\n");
    global_scheduler = &sch;
    sch.prepare_scheduler();
    sch.create_process(sleep_example);
    sch.create_process(exit_example);
    sch.create_process(send_example);
    sch.create_process(recv_example);
    sch.start_scheduling();
    

    return 0;
}
