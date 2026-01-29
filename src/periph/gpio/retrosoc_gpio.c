#include <periph/retrosoc_gpio.h>
#include <stdint.h>

uint32_t retrosoc_gpio_read(retrosoc_gpio_map_t* gpio_bank) {
    return gpio_bank->data;
}

void retrosoc_gpio_write(retrosoc_gpio_map_t *gpio_bank, uint32_t data) {
    gpio_bank->data = data;
}

void retrosoc_gpio_config_mode(retrosoc_gpio_map_t *gpio_bank, uint32_t pins, bool output) {
    uint32_t mode = gpio_bank->mode;
    if (output) {
        mode &= ~pins;
    } else {
        mode |= pins;
    }
    gpio_bank->mode = mode;
}

void retrosoc_gpio_config_pullup(retrosoc_gpio_map_t *gpio_bank, uint32_t pins, bool enabled) {
    uint32_t config = gpio_bank->pullup;
    if (enabled) {
        config |= pins;
    } else {
        config &= ~pins;
    }
    gpio_bank->pullup = config;
}

void retrosoc_gpio_config_pulldown(retrosoc_gpio_map_t *gpio_bank, uint32_t pins, bool enabled) {
    uint32_t config = gpio_bank->pulldown;
    if (enabled) {
        config |= pins;
    } else {
        config &= ~pins;
    }
    gpio_bank->pulldown = config;
}
