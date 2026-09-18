#ifndef __PERIPH_SIMPLESOC_GPIO_H
#define __PERIPH_SIMPLESOC_GPIO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    volatile uint32_t output __attribute__((__aligned__(4)));    /*<< Write GPIO output level */
    volatile uint32_t input __attribute__((__aligned__(4)));     /*<< Read GPIO input level */
} __attribute__((__packed__)) simplesoc_gpio_map_t;

uint32_t simplesoc_gpio_read(simplesoc_gpio_map_t* gpio_bank);

void simplesoc_gpio_write(simplesoc_gpio_map_t *gpio_bank, uint32_t data);

#ifdef __cplusplus
}
#endif

#endif // __PERIPH_SIMPLESOC_GPIO_H
