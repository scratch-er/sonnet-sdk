#include <aal/context.h>
#include <stdint.h>

struct __attribute__((__packed__)) context_t {
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
};

context_t* create_context(void* (*entry)(void *), void (*exit)(void*), void* stack_pointer, void *arg) {
    // the ABI requires the stack frame to be 16-byte aligned
    uint32_t aligned_sp = (uint32_t)stack_pointer & (~0xf);
    // store the context on the stack
    context_t* new_context = (context_t*)(aligned_sp - sizeof(context_t));
    // when the context is switched to, it will be as if `entry` is called
    new_context->pc = (uint32_t)entry;
    // when `entry` returns, it will be as if `exit` is tall-called
    new_context->ra = (uint32_t)exit;
    // setup stack pointer
    new_context->sp = (uint32_t)aligned_sp;
    // pass the ner argument to `entry`
    new_context->a0 = (uint32_t)arg;
    return new_context;
}
