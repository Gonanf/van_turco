#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"


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
    for(;;){
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);
    sleep_ms(250);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);
    sleep_ms(250);
    }
    return 0;
}
