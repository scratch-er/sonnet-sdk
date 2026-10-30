#ifndef __FIXED_MATH_H
#define __FIXED_MATH_H

#include <stdint.h>

typedef int32_t q32f16;

q32f16 fixed_int(int32_t n);

q32f16 fixed_frac(int32_t n, int32_t d);

q32f16 fixed_mul(q32f16 a, q32f16 b);

q32f16 fixed_div(q32f16 a, q32f16 b);

q32f16 fixed_rand_uniform(void);

q32f16 fixed_rand_norm(void);

q32f16 fixed_truncate(q32f16 ub, q32f16 lb, q32f16 x);

#endif
