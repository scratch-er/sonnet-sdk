#ifndef __PERIPH_RETROSOC_GPIO_H
#define __PERIPH_RETROSOC_GPIO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    volatile uint32_t data __attribute__((__aligned__(4)));     /*<< Read or write GPIO level */
    volatile uint32_t mode __attribute__((__aligned__(4)));     /*<< Set pin direction, high for input, low for output */
    volatile uint32_t pullup __attribute__((__aligned__(4)));   /*<< Set pin pullup */
    volatile uint32_t pulldown __attribute__((__aligned__(4))); /*<< Set pin pulldown */
} __attribute__((__packed__)) retrosoc_gpio_map_t;

uint32_t retrosoc_gpio_read(retrosoc_gpio_map_t* gpio_bank);

void retrosoc_gpio_write(retrosoc_gpio_map_t *gpio_bank, uint32_t data);

void retrosoc_gpio_config_mode(retrosoc_gpio_map_t *gpio_bank, uint32_t pins, bool output);

void retrosoc_gpio_config_pullup(retrosoc_gpio_map_t *gpio_bank, uint32_t pins, bool enabled);

void retrosoc_gpio_config_pulldown(retrosoc_gpio_map_t *gpio_bank, uint32_t pins, bool enabled);

#ifdef __cplusplus
}
#endif

#endif // __PERIPH_RETROSOC_GPIO_H
