#include <hal/gpio.h>
#include <periph/simplesoc_gpio.h>
#include <stdint.h>

void gpio_config(void* gpio_bank, uint32_t gpio_pins, gpio_config_t* config) {
    config->pullup = false;
    config->pulldown = false;
}

bool gpio_read(void* gpio_bank, uint8_t gpio_pin) {
    uint32_t state = simplesoc_gpio_read((simplesoc_gpio_map_t*)gpio_bank);
    return state&(1<<gpio_pin);
}

void gpio_write(void* gpio_bank, uint8_t gpio_pin, bool value) {
    uint32_t state = ((simplesoc_gpio_map_t*)gpio_bank)->output;
    if (value) {
        state |= (1<<gpio_pin);
    } else {
        state &= ~(1<<gpio_pin);
    }
    simplesoc_gpio_write((simplesoc_gpio_map_t*)gpio_bank, state);
}
