#include <periph/simplesoc_uart.h>

uint8_t simplesoc_uart_read(simplesoc_uart_map_t *uart_periph) {
    while (!(uart_periph->status & 0x02)) {}
    return uart_periph->data;
}

void simplesoc_uart_write(simplesoc_uart_map_t *uart_periph, uint8_t data) {
    while (!(uart_periph->status & 0x01)) {}
    uart_periph->data = data;
}

void simplesoc_uart_set_divisor(simplesoc_uart_map_t *uart_periph, uint16_t divisor) {
    uart_periph->divisor = divisor;
}
