#include <hal/uart.h>
#include <periph/simplesoc_uart.h>
#include <soc/simplesoc.h>
#include <stdint.h>

uint16_t uart_read(void *uart_periph) {
    return simplesoc_uart_read((simplesoc_uart_map_t*)uart_periph);
}

void uart_write(void *uart_periph, uint16_t data) {
    simplesoc_uart_write((simplesoc_uart_map_t*)uart_periph, (uint8_t)data);
}

void uart_config(void *uart_periph, uart_config_t *config) {
    /* bit time = divisor core clocks, so divisor = f_clk / baud - 1 */
    uint32_t divisor = SIMPLESOC_CPU_FREQ_HZ / config->baudrate_hz;
    if (divisor > 0) divisor -= 1;
    simplesoc_uart_set_divisor((simplesoc_uart_map_t*)uart_periph, (uint16_t)divisor);
    config->word_length = 8;
    config->patity = false;
    config->stop_bits = 1;
    config->flow_control = false;
}

bool uart_check_rx(void *uart_periph) {
    return ((simplesoc_uart_map_t*)uart_periph)->status & 0x02;
}

bool uart_check_tx(void *uart_periph) {
    return ((simplesoc_uart_map_t*)uart_periph)->status & 0x01;
}
