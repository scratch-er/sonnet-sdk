#ifndef __PERIPH_SIMPLESOC_UART_H
#define __PERIPH_SIMPLESOC_UART_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    volatile uint8_t data __attribute__((__aligned__(1)));
    volatile uint8_t status __attribute__((__aligned__(1)));
    volatile uint16_t divisor __attribute__((__aligned__(2)));
} __attribute__((__packed__)) simplesoc_uart_map_t;

uint8_t simplesoc_uart_read(simplesoc_uart_map_t *uart_periph);

void simplesoc_uart_write(simplesoc_uart_map_t *uart_periph, uint8_t data);

void simplesoc_uart_set_divisor(simplesoc_uart_map_t *uart_periph, uint16_t divisor);

#ifdef __cplusplus
}
#endif

#endif // __PERIPH_SIMPLESOC_UART_H
