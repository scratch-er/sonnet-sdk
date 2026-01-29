#include <hal/gpio.h>
#include <periph/retrosoc_gpio.h>
#include <stdint.h>

void gpio_config(void* gpio_bank, uint32_t gpio_pins, gpio_config_t* config) {
    retrosoc_gpio_config_mode((retrosoc_gpio_map_t*)gpio_bank, gpio_pins, config->output);
    retrosoc_gpio_config_pullup((retrosoc_gpio_map_t*)gpio_bank, gpio_pins, config->pullup);
    retrosoc_gpio_config_pulldown((retrosoc_gpio_map_t*)gpio_bank, gpio_pins, config->pulldown);
}

bool gpio_read(void* gpio_bank, uint8_t gpio_pin) {
    uint32_t state = retrosoc_gpio_read((retrosoc_gpio_map_t*)gpio_bank);
    return state&(1<<gpio_pin);
}

void gpio_write(void* gpio_bank, uint8_t gpio_pin, bool value) {
    uint32_t state = retrosoc_gpio_read((retrosoc_gpio_map_t*)gpio_bank);
    if (value) {
        state |= (1<<gpio_pin);
    } else {
        state &= ~(1<<gpio_pin);
    }
    retrosoc_gpio_write((retrosoc_gpio_map_t*)gpio_bank, state);
}
