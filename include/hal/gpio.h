/**
 * @file gpio.h
 * @brief GPIO (General Purpose Input/Output) HAL interface
 */

#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H

#include <stdint.h>

typedef struct {
    bool output;    /**< Configure pin as output when true, input when false */
    bool pullup;    /**< Enable internal pull-up resistor */
    bool pulldown;  /**< Enable internal pull-down resistor */
} gpio_config_t;

/**
 * @brief Configure GPIO pin(s)
 *
 * Initialize and configure one or more GPIO pins. If the requested
 * configuration cannot be applied exactly, the `config` parameter
 * will be updated to reflect the actual configuration used.
 *
 * @param gpio_bank Pointer to the GPIO bank/peripheral instance
 * @param gpio_pins Bitmask of pins to configure
 * @param config Desired configuration
 */
void gpio_config(void* gpio_bank, uint32_t gpio_pins, gpio_config_t* config);

/**
 * @brief Read GPIO pin state
 *
 * Reads the GPIO level if the GPIO pin is set to input.
 * If the pin is set to output, the behavior is implement defined.
 *
 * @param gpio_bank Pointer to the GPIO bank/peripheral instance
 * @param gpio_pin Pin to read
 * @return true if high, false if low
 */
bool gpio_read(void* gpio_bank, uint8_t gpio_pin);

/**
 * @brief Write GPIO pin state
 *
 * Set the GPIO level if the pin is set to output.
 * If the pin is set to input, the behavior is undefined.
 *
 * @param gpio_bank Pointer to the GPIO bank/peripheral instance
 * @param gpio_pin Pin to write
 * @param value true to set the pin high, false to set the pin low
 */
void gpio_write(void* gpio_bank, uint8_t gpio_pin, bool value);

#endif // __HAL_GPIO_H
