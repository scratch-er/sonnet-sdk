#ifndef __AAL_CONTEXT_H
#define __AAL_CONTEXT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __riscv

#if __riscv_xlen == 32
#define word_t uint32_t
#define alignment __attribute__((__aligned__(4)))
#endif /* __riscv_xlen == 32 */

#if __riscv_xlen == 64
#define word_t uint64_t
#define alignment __attribute__((__aligned__(8)))
#endif /* __riscv_xlen == 64 */

typedef struct __attribute__((__packed__)) {
    word_t pc  alignment;
    word_t ra  alignment;
    word_t sp  alignment;
    word_t gp  alignment;
    word_t tp  alignment;
    word_t t0  alignment;
    word_t t1  alignment;
    word_t t2  alignment;
    word_t s0  alignment;
    word_t s1  alignment;
    word_t a0  alignment;
    word_t a1  alignment;
    word_t a2  alignment;
    word_t a3  alignment;
    word_t a4  alignment;
    word_t a5  alignment;
#ifndef __riscv_e
    word_t a6  alignment;
    word_t a7  alignment;
    word_t s2  alignment;
    word_t s3  alignment;
    word_t s4  alignment;
    word_t s5  alignment;
    word_t s6  alignment;
    word_t s7  alignment;
    word_t s8  alignment;
    word_t s9  alignment;
    word_t s10 alignment;
    word_t s11 alignment;
    word_t t3  alignment;
    word_t t4  alignment;
    word_t t5  alignment;
    word_t t6  alignment;
#endif /* __riscv_e */ 
} context_t;

#undef word_t
#undef alignment

#endif /* __riscv */

void* get_stack_pointer(void);

context_t* create_context(void* (*entry)(void*), void (*exit)(void*), void* stack_pointer, void* arg);

void switch_to_context(context_t* context, context_t** save);

#ifdef __cplusplus
}
#endif

#endif // __AAL_CONTEXT_H
