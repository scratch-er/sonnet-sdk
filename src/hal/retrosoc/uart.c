#include <hal/uart.h>
#include <periph/retrosoc_sysuart.h>
#include <soc/retrosoc.h>
#include <stdint.h>

static uint16_t _uart_buff = (uint16_t)(-1);

uint16_t uart_read(void *uart_periph) {
    if (_uart_buff != (uint16_t)(-1)) {
        uint16_t data = _uart_buff;
        _uart_buff = (uint16_t)(-1);
        return data;
    } else {
        return retrosoc_sysuart_read((retrosoc_sysuart_map_t*)uart_periph);
    }
}

void uart_write(void *uart_periph, uint16_t data) {
    retrosoc_sysuart_write((volatile retrosoc_sysuart_map_t*)uart_periph, data);
}

void uart_config(void *uart_periph, uart_config_t *config) {
    retrosoc_sysuart_config_baudrate((volatile retrosoc_sysuart_map_t*)uart_periph, config->baudrate_hz, SYS_FREQ_HZ);
    config->word_length = 8;
    config->patity = false;
    config->stop_bits = 1;
    config->flow_control = false;
}

bool uart_check_rx(void *uart_periph) {
    if (_uart_buff == (uint16_t)(-1)) {
        _uart_buff = retrosoc_sysuart_read((retrosoc_sysuart_map_t*)uart_periph);
        return _uart_buff != (uint16_t)(-1);
    } else {
        return true;
    }
}

bool uart_check_tx(void *uart_periph) {
    return true;
}
