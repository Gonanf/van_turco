#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "vga_test/vga.h"
#include "libarbys/libarbys.hpp"
#include "kernel32/scheduler/scheduler.hpp"
#include "kernel32/interrupts/interrupts.hpp"

#ifndef CYW43_WL_GPIO_LED_PIN
#define CYW43_WL_GPIO_LED_PIN 0
#endif

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
    scheduler_global.create();
    while (true)
    {
            promise_L prom = buffer.read_character();
            if (prom.is_done)
            {
                buffer.split();
                printf("finished: %d\n",buffer.size);
                scheduler_global.execute();
                buffer.empty();
                printf("finished2: %d\n",buffer.size);
                buffer.print();
            }
    }

    return 0;
}
