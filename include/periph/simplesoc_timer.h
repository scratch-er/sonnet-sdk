/**
 * @file simplesoc_timer.h
 * @brief Register map for the SimpleSoC timer peripheral.
 */

#ifndef __PERIPH_SIMPLESOC_TIMER_H
#define __PERIPH_SIMPLESOC_TIMER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief SimpleSoC timer register map.
 */
typedef struct {
    volatile uint16_t cnt0 __attribute__((__aligned__(2)));  /**< Low counter stage; wraps to 0 at wrap0. Bus word 0, low half. */
    volatile uint16_t cnt1 __attribute__((__aligned__(2)));  /**< High counter stage; increments on a cnt0 wrap and wraps at wrap1. Bus word 0, high half. */
    volatile uint16_t wrap0 __attribute__((__aligned__(2))); /**< Wrap value for cnt0. Bus word 1, low half. */
    volatile uint16_t wrap1 __attribute__((__aligned__(2))); /**< Wrap value for cnt1. Bus word 1, high half. */
    volatile uint16_t cmp0 __attribute__((__aligned__(2)));  /**< Compare value for PWM output 0 (pwm0 = cnt1 < cmp0). Bus word 2, low half. */
    volatile uint16_t cmp1 __attribute__((__aligned__(2)));  /**< Compare value for PWM output 1 (pwm1 = cnt1 < cmp1). Bus word 2, high half. */
    volatile uint16_t cmp2 __attribute__((__aligned__(2)));  /**< Compare value for PWM output 2 (pwm2 = cnt1 < cmp2). Bus word 3, low half. */
    volatile uint16_t cmp3 __attribute__((__aligned__(2)));  /**< Compare value for PWM output 3 (pwm3 = cnt1 < cmp3). Bus word 3, high half. */
} __attribute__((__packed__)) simplesoc_timer_map_t;

#ifdef __cplusplus
}
#endif

#endif // __PERIPH_SIMPLESOC_TIMER_H
