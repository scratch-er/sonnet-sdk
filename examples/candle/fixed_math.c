#include <stdint.h>
#include "fixed_math.h"

q32f16 fixed_int(int32_t n) {
    return n << 16;
}

q32f16 fixed_frac(int32_t n, int32_t d) {
    return ((int64_t)n << 16) / d;
}

q32f16 fixed_mul(q32f16 a, q32f16 b) {
    return ((int64_t)a * (int64_t)b) >> 16;
}

q32f16 fixed_div(q32f16 a, q32f16 b) {
    return ((int64_t)a << 16) / b;
}

q32f16 fixed_rand_uniform(void) {
    static uint32_t _random_seed = 0;
    if (_random_seed == 0) {
        _random_seed = 0x7a2d5eed;
    }
    unsigned int feedback = 0;
    feedback ^= (_random_seed>>31) | 1;
    feedback ^= (_random_seed>>21) | 1;
    feedback ^= (_random_seed>>1) | 1;
    feedback ^= (_random_seed>>0) | 1;
    _random_seed >>= 1;
    _random_seed |= feedback<<31;
    return (int32_t)((int16_t)(_random_seed&0xffff) >> 1);
}

q32f16 fixed_rand_norm(void) {
    q32f16 x = 0;
    for (int i=0; i<12; ++i) {
        x += fixed_rand_uniform();
    }
    return x;
}

q32f16 fixed_truncate(q32f16 ub, q32f16 lb, q32f16 x) {
    x = x >= ub ? ub-1 : x;
    x = x < lb ? lb : x;
    return x;
}
