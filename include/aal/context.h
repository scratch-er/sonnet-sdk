#ifndef __AAL_CONTEXT_H
#define __AAL_CONTEXT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if __riscv_xlen == 32
typedef struct __attribute__((__packed__)) {
    uint32_t pc  __attribute__((__aligned__(4)));
    uint32_t ra  __attribute__((__aligned__(4)));
    uint32_t sp  __attribute__((__aligned__(4)));
    uint32_t gp  __attribute__((__aligned__(4)));
    uint32_t tp  __attribute__((__aligned__(4)));
    uint32_t t0  __attribute__((__aligned__(4)));
    uint32_t t1  __attribute__((__aligned__(4)));
    uint32_t t2  __attribute__((__aligned__(4)));
    uint32_t s0  __attribute__((__aligned__(4)));
    uint32_t s1  __attribute__((__aligned__(4)));
    uint32_t a0  __attribute__((__aligned__(4)));
    uint32_t a1  __attribute__((__aligned__(4)));
    uint32_t a2  __attribute__((__aligned__(4)));
    uint32_t a3  __attribute__((__aligned__(4)));
    uint32_t a4  __attribute__((__aligned__(4)));
    uint32_t a5  __attribute__((__aligned__(4)));
    uint32_t a6  __attribute__((__aligned__(4)));
    uint32_t a7  __attribute__((__aligned__(4)));
    uint32_t s2  __attribute__((__aligned__(4)));
    uint32_t s3  __attribute__((__aligned__(4)));
    uint32_t s4  __attribute__((__aligned__(4)));
    uint32_t s5  __attribute__((__aligned__(4)));
    uint32_t s6  __attribute__((__aligned__(4)));
    uint32_t s7  __attribute__((__aligned__(4)));
    uint32_t s8  __attribute__((__aligned__(4)));
    uint32_t s9  __attribute__((__aligned__(4)));
    uint32_t s10 __attribute__((__aligned__(4)));
    uint32_t s11 __attribute__((__aligned__(4)));
    uint32_t t3  __attribute__((__aligned__(4)));
    uint32_t t4  __attribute__((__aligned__(4)));
    uint32_t t5  __attribute__((__aligned__(4)));
    uint32_t t6  __attribute__((__aligned__(4)));
} context_t;
#endif

void* get_stack_pointer(void);

context_t* create_context(void* (*entry)(void*), void (*exit)(void*), void* stack_pointer, void* arg);

void switch_to_context(context_t* context, context_t** save);

#ifdef __cplusplus
}
#endif

#endif // __AAL_CONTEXT_H
