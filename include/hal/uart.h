#ifndef __HAL_UART_H
#define __HAL_UART_H

#include <stdint.h>

uint16_t uart_read(void *uart_periph);

void uart_write(void *uart_periph, uint16_t data);

void uart_config_baudrate(void *uart_periph, uint32_t baudrate, uint32_t periph_freq);

bool uart_check_rx(void *uart_periph);

bool uart_check_tx(void *uart_periph);

#endif // __HAL_UART_H
