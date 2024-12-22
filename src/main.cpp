#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "../modules/vga_test/vga.h"

#ifndef CYW43_WL_GPIO_LED_PIN
#define CYW43_WL_GPIO_LED_PIN 0
#endif

/**
 * @brief main execution point of the microkernel
 *
 * @return int
 */
int main() {
    stdio_init_all();
    cyw43_arch_init();
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);
    start_vga_test();
    return 0;
}
