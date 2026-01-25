#include <periph/retrosoc_sysuart.h>

uint32_t retrosoc_sysuart_read(volatile retrosoc_sysuart_map_t *uart_periph) {
    return (uint16_t) uart_periph->data;
}

void retrosoc_sysuart_write(volatile retrosoc_sysuart_map_t *uart_periph, uint32_t data) {
    uart_periph->data = data;
}

void retrosoc_sysuart_config_baudrate(volatile retrosoc_sysuart_map_t *uart_periph, uint32_t baudrate_hz, uint32_t periph_freq) {
    uart_periph->clkdiv = periph_freq / baudrate_hz;
}
