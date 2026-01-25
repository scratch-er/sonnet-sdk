#include <hal/uart.h>
#include <periph/simple_uart.h>
#include <stdint.h>

uint16_t uart_read(void *uart_periph) {
    return simple_uart_read((simple_uart_map_t*)uart_periph);
}

void uart_write(void *uart_periph, uint16_t data) {
    simple_uart_write((simple_uart_map_t*)uart_periph, data);
}

void uart_config(void *uart_periph, uart_config_t *config) {
    config->baudrate_hz = 0;
    config->word_length = 8;
    config->patity = false;
    config->stop_bits = 0;
    config->flow_control = false;
}

bool uart_check_rx(void *uart_periph) {
    return true;
}

bool uart_check_tx(void *uart_periph) {
    return true;
}
