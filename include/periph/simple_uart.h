#ifndef __PERIPH_SIMPLE_UART_H
#define __PERIPH_SIMPLE_UART_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    volatile uint8_t data;
    volatile uint8_t padding[3];
} __attribute__((__packed__)) simple_uart_map_t;

uint32_t simple_uart_read(simple_uart_map_t *uart_periph);

void simple_uart_write(simple_uart_map_t *uart_periph, uint32_t data);

#ifdef __cplusplus
}
#endif

#endif // __PERIPH_SIMPLE_UART_H
