#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "../modules/vga_test/vga.h"
#include "../modules/mod.cpp"
#include "libarbys/libarbys.hpp"

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
    while (true)
    {
            promise_L prom = read_into(buffer);
            if (prom.is_done)
            {
                process_command(buffer);
                printf("finished: %d\n",buffer.size);
                buffer.empty();
                printf("finished2: %d\n",buffer.size);
                buffer.print();
            }
    }

    return 0;
}
