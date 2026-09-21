/**
 * @file timer.c
 * @brief Timer HAL implementation for the SimpleSoC timer peripheral.
 *
 * The peripheral counts up only, so @ref timer_config_t.count_up is fixed at
 * true. cnt0 is the prescaler stage: it increments every clock cycle and
 * wraps at wrap0, so the counter advances at the input clock divided by
 * (wrap0 + 1). cnt1 is the counter: it increments on each prescaler wrap and
 * wraps at wrap1. The config divisor maps to wrap0 and the wrap/reload value
 * to wrap1 (both 16-bit, so wider values are truncated).
 */

#include <hal/timer.h>
#include <periph/simplesoc_timer.h>
#include <stdint.h>

void timer_config(void* timer, timer_config_t* config) {
    simplesoc_timer_map_t* map = (simplesoc_timer_map_t*)timer;
    map->wrap0 = (uint16_t)(config->divisor);
    map->wrap1 = (uint16_t)(config->wrap_reload);
    /* Report the actual configuration applied. */
    config->divisor = map->wrap0;
    config->wrap_reload = map->wrap1;
    config->count_up = true;
}

uint32_t timer_get_counter(void* timer) {
    simplesoc_timer_map_t* map = (simplesoc_timer_map_t*)timer;
    return map->cnt1;
}

uint32_t timer_set_wrap_reload(void* timer, uint32_t wrap_reload) {
    simplesoc_timer_map_t* map = (simplesoc_timer_map_t*)timer;
    map->wrap1 = (uint16_t)wrap_reload;
    return map->wrap1;
}

uint32_t timer_set_pwm_duty(void* timer, uint8_t channel, uint32_t duty) {
    simplesoc_timer_map_t* map = (simplesoc_timer_map_t*)timer;
    volatile uint16_t* cmp = &map->cmp0 + channel;
    *cmp = (uint16_t)duty;
    return *cmp;
}
