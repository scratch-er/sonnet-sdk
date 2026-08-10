/**
 * @file uart.h
 * @brief UART (Universal Asynchronous Receiver-Transmitter) HAL interface
 */

#ifndef __HAL_UART_H
#define __HAL_UART_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t baudrate_hz;  /**> Baudrate in Hz */
    uint8_t  word_length;  /**> Number of bis per frame */
    uint8_t  stop_bits;    /**> Number of stop bits */
    bool     patity;       /**> Enable parity bit */
    bool     flow_control; /**> Enable flow control */
} uart_config_t;

/**
 * @brief Read a single frame from the UART peripheral
 * @param uart_periph Pointer to the UART peripheral instance
 * @return Received data (not necessarily 8-bit)
 * @note This function should block until data is available
 */
uint16_t uart_read(void *uart_periph);

/**
 * @brief Write a single frame to the UART peripheral
 * @param uart_periph Pointer to the UART peripheral instance
 * @param data Data to transmit (not necessarily 8-bit)
 * @note This function should block until the frame can be transmitted
 */
void uart_write(void *uart_periph, uint16_t data);

/**
 * @brief Configure the UART peripheral
 *
 * Initialize and configure the UART hardware. If the requested
 * configuration cannot be applied exactly, the `config` parameter
 * will be updated to reflect the actual configuration used.
 *
 * @param uart_periph Pointer to the UART peripheral instance
 * @param config Desired configuration
 */
void uart_config(void *uart_periph, uart_config_t *config);

/**
 * @brief Check if receive data is available
 * @param uart_periph Pointer to the UART peripheral instance
 * @return true if data is available to be read, false otherwise
 */
bool uart_check_rx(void *uart_periph);

/**
 * @brief Check if transmitter is ready to accept new data
 * @param uart_periph Pointer to the UART peripheral instance
 * @return true if transmitter is ready, false otherwise
 */
bool uart_check_tx(void *uart_periph);

#ifdef __cplusplus
}
#endif

#endif // __HAL_UART_H
