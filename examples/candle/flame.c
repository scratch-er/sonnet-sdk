#include "fixed_math.h"
#include "flame.h"

q32f16 brightness(state_t state, q32f16 x) {
    q32f16 offset = fixed_div(x-state.c, state.b);
    return fixed_div(state.a, fixed_mul(offset, offset) + fixed_int(1));
}

void apply_feedback(state_t k, state_t* state) {
    state->a -= fixed_mul(k.a, state->a - fixed_frac(1, 2));
    state->b -= fixed_mul(k.b, state->b - fixed_frac(1, 4));
    state->c -= fixed_mul(k.c, state->c);
}

void apply_disturbance(state_t k, state_t* state) {
    state->a = fixed_mul(state->a, fixed_int(1)+fixed_rand_norm());
    state->b = fixed_mul(state->b, fixed_int(1)+fixed_rand_norm());
    state->c = state->c + fixed_mul(k.c, fixed_rand_norm());
}

q32f16 force_add(q32f16 k, q32f16 delta_x) {
    return fixed_div(fixed_mul(-4*k, delta_x), 4*fixed_mul(delta_x, delta_x) + fixed_int(1));
}

q32f16 force_mul(q32f16 k, q32f16 delta_x) {
    q32f16 scaled = fixed_div(delta_x, k);
    q32f16 square = fixed_mul(scaled, scaled);
    return fixed_div(4*square, 4*square + fixed_int(1));
}

void apply_input(state_t k, state_t* state, q32f16 x) {
    q32f16 delta_x = x - state->c;
    state->a = fixed_mul(state->a, force_mul(k.a, delta_x));
    state->b = fixed_mul(state->b, force_mul(k.b, delta_x));
    state->c = state->c + force_add(k.c, delta_x);
}

char brightness_to_char(q32f16 brightness) {
    if (brightness < fixed_frac(1, 64)) {
        return ' ';
    } else if (brightness < fixed_frac(2, 64)) {
        return '.';
    } else if (brightness < fixed_frac(4, 64)) {
        return '-';
    } else if (brightness < fixed_frac(8, 64)) {
        return '~';
    } else if (brightness < fixed_frac(16, 64)) {
        return '+';
    } else if (brightness < fixed_frac(32, 64)) {
        return '=';
    } else if (brightness < fixed_frac(48, 64)) {
        return '*';
    } else {
        return '#';
    }
}
