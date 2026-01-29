#ifndef __PERIPH_RETROSOC_SYSUART_H
#define __PERIPH_RETROSOC_SYSUART_H

#include <stdint.h>

typedef struct {
    volatile uint32_t clkdiv __attribute__((__aligned__(4)));
    volatile uint32_t data __attribute__((__aligned__(4)));
} __attribute__((__packed__)) retrosoc_sysuart_map_t;

uint32_t retrosoc_sysuart_read(retrosoc_sysuart_map_t *uart_periph);

void retrosoc_sysuart_write(retrosoc_sysuart_map_t *uart_periph, uint32_t data);

void retrosoc_sysuart_config_baudrate(retrosoc_sysuart_map_t *uart_periph, uint32_t baudrate, uint32_t periph_freq_hz);

#endif // __PERIPH_RETROSOC_SYSUART_H
