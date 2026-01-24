#include <periph/simple_uart.h>

uint32_t simple_uart_read(simple_uart_map_t *uart_periph) {
    return (uint16_t) uart_periph->data;
}

void simple_uart_write(simple_uart_map_t *uart_periph, uint32_t data) {
    uart_periph->data = data;
}
