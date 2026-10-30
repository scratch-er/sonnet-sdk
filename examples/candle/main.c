#include <bsp/io.h>
#include <bsp/time.h>
#include <soc/simplesoc.h>
#include <hal/timer.h>
#include <hal/uart.h>
#include <hal/gpio.h>
#include <stdint.h>
#include "fixed_math.h"
#include "flame.h"
#include <lightio.h>

const char* msg = "Hello, SimpleSoc!\r\n";

#define N_SAMPLES 6

int main() {
    state_t state = {fixed_frac(1, 2), fixed_frac(1, 1), 0};
    state_t k_i = {fixed_frac(3, 4), fixed_frac(3, 4), fixed_frac(4, 16)};
    state_t k_d = {fixed_frac(1, 8), fixed_frac(1, 8), fixed_frac(1, 8)};
    state_t k_f = {fixed_frac(1, 8), fixed_frac(1, 8), fixed_frac(1, 4)};

    timer_config_t cfg;
    cfg.divisor = 0;
    cfg.wrap_reload = 65535;
    cfg.count_up = true;
    timer_config(TIMER0, &cfg);
    timer_config(TIMER1, &cfg);

    q32f16 samples[N_SAMPLES];
    uint32_t duties[N_SAMPLES];

    while (true) {
        for (int i=0; i<N_SAMPLES; ++i) {
            samples[i] = brightness(state, fixed_frac(i*2+1-N_SAMPLES, 2));
        }
        putch('[');
        for (int i=0; i<N_SAMPLES; ++i) {
            putch(brightness_to_char(samples[i]));
        }
        putch(']');
        putch(' ');
        for (int i=0; msg[i]; ++i) {
            putch(msg[i]);
        }
        for (int i=0; i<N_SAMPLES; ++i) {
            duties[i] = fixed_truncate(fixed_int(1), 0, fixed_int(1)-samples[i]);
        }
        timer_set_pwm_duty(TIMER1, 1, duties[0]);
        timer_set_pwm_duty(TIMER1, 0, duties[1]);
        timer_set_pwm_duty(TIMER0, 3, duties[2]);
        timer_set_pwm_duty(TIMER0, 2, duties[3]);
        timer_set_pwm_duty(TIMER0, 1, duties[4]);
        timer_set_pwm_duty(TIMER0, 0, duties[5]);
        if (!gpio_read(GPIO0, 0)) {
            apply_input(k_f, &state, fixed_frac(-3, 2));
        }
        if (!gpio_read(GPIO0, 1)) {
            apply_input(k_f, &state, fixed_frac(-1, 2));
        }
        if (!gpio_read(GPIO0, 2)) {
            apply_input(k_f, &state, fixed_frac(1, 2));
        }
        if (!gpio_read(GPIO0, 3)) {
            apply_input(k_f, &state, fixed_frac(3, 2));
        }
        apply_disturbance(k_d, &state);
        apply_feedback(k_f, &state);
        spin_delay(100*1000);
    }
}
