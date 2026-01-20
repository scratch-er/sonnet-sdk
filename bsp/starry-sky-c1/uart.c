#include <hal/uart.h>
#include <periph/retrosoc_sysuart.h>
#include <stdint.h>

uint16_t uart_read(void *uart_periph) {
    return retrosoc_sysuart_read((retrosoc_sysuart_map_t*)uart_periph);
}

void uart_write(void *uart_periph, uint16_t data) {
    retrosoc_sysuart_write((volatile retrosoc_sysuart_map_t*)uart_periph, data);
}

void uart_config_baudrate(void *uart_periph, uint32_t baudrate, uint32_t periph_freq) {
    retrosoc_sysuart_config_baudrate((volatile retrosoc_sysuart_map_t*)uart_periph, baudrate, periph_freq);
}

bool uart_check_rx(void *uart_periph) {
    return retrosoc_sysuart_read((retrosoc_sysuart_map_t*)uart_periph) != (uint32_t)(-1);
}

bool uart_check_tx(void *uart_periph) {
    return true;
}
