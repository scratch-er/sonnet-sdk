#include <periph/simplesoc_gpio.h>

uint32_t simplesoc_gpio_read(simplesoc_gpio_map_t* gpio_bank) {
    return gpio_bank->input;
}

void simplesoc_gpio_write(simplesoc_gpio_map_t *gpio_bank, uint32_t data) {
    gpio_bank->output = data;
}
