#ifndef __FLAME_H
#define __FLAME_H

#include "fixed_math.h"

typedef struct {
    q32f16 a;
    q32f16 b;
    q32f16 c;
} state_t;

q32f16 brightness(state_t state, q32f16 x);

void apply_feedback(state_t k, state_t* state);

void apply_disturbance(state_t k, state_t* state);

q32f16 force_add(q32f16 k, q32f16 delta_x);

q32f16 force_mul(q32f16 k, q32f16 delta_x);

void apply_input(state_t k, state_t* state, q32f16 x);

char brightness_to_char(q32f16 brightness);

#endif
