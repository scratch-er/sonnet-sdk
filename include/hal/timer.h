/**
 * @file timer.h
 * @brief Timer HAL interface
 *
 * Generic hardware-independent interface for platform timers. A timer is an
 * opaque instance referenced by a pointer; the HAL makes no assumptions about
 * the underlying counter structure or register layout, which are defined by
 * the platform-specific peripheral driver.
 */

#ifndef __HAL_TIMER_H
#define __HAL_TIMER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Configuration for a timer instance.
 */
typedef struct {
    /** @brief Clock divisor; the counter advances at the input clock frequency divided by (divisor + 1). */
    uint32_t divisor;
    /** @brief Counter wrap/reload value.
     * The counter wraps to zero after reaching it if counting up.
     * The counter reloads to it when reaching zero if counting down.
     */
    uint32_t wrap_reload;
    /** @brief Count direction: true to count up, false to count down. */
    bool count_up;
} timer_config_t;

/**
 * @brief Apply a configuration to a timer.
 *
 * On return, @p config contains the actual configuration applied, which may
 * differ from the requested one if the implementation clamps or rounds
 * values.
 *
 * @param timer Pointer to the timer instance.
 * @param config Configuration to apply; updated in place with the actual
 *               configuration applied.
 */
void timer_config(void* timer, timer_config_t* config);

/**
 * @brief Read the current counter value of a timer.
 * @param timer Pointer to the timer instance.
 * @return Current counter value.
 */
uint32_t timer_get_counter(void* timer);

/**
 * @brief Set the wrap/reload value of a timer.
 * @param timer Pointer to the timer instance.
 * @param wrap_reload New wrap/reload value.
 * @return The actual value set; may differ from the requested value if the
 *         implementation clamps or rounds it.
 */
uint32_t timer_set_wrap_reload(void* timer, uint32_t wrap_reload);

/**
 * @brief Set the PWM duty cycle on a timer channel.
 * @param timer Pointer to the timer instance.
 * @param channel PWM channel number.
 * @param duty Duty cycle value.
 * @return The actual value set; may differ from the requested value if the
 *         implementation clamps or rounds it.
 */
uint32_t timer_set_pwm_duty(void* timer, uint8_t channel, uint32_t duty);

#ifdef __cplusplus
}
#endif

#endif // __HAL_TIMER_H
