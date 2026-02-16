#include <aal/context.h>
#include <stdint.h>

context_t* create_context(void* (*entry)(void *), void (*exit)(void*), void* stack_pointer, void *arg) {
    // the ABI requires the stack frame to be 16-byte aligned
    uintptr_t aligned_sp = (uintptr_t)stack_pointer & (~0xf);
    // store the context on the stack
    context_t* new_context = (context_t*)(aligned_sp - sizeof(context_t));
    // when the context is switched to, it will be as if `entry` is called
    new_context->pc = (uintptr_t)entry;
    // when `entry` returns, it will be as if `exit` is tall-called
    new_context->ra = (uintptr_t)exit;
    // setup stack pointer
    new_context->sp = (uintptr_t)aligned_sp;
    // pass the ner argument to `entry`
    new_context->a0 = (uintptr_t)arg;
    return new_context;
}
