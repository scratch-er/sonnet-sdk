#ifndef __AAL_EVENT_H
#define __AAL_EVENT_H

#include <stdint.h>
#include <aal/context.h>

typedef struct {
    enum {
        EVENT_NULL = 0,
        EVENT_YIELD, EVENT_SYSCALL, EVENT_PAGEFAULT, EVENT_ERROR,
        EVENT_IRQ_TIMER, EVENT_IRQ_IODEV,
    } event;
    uintptr_t cause, ref;
    const char *msg;
} event_t;

bool ienabled(void);

void iset(bool enable);

bool set_event_handler(context_t *(*handler)(event_t ev, context_t *ctx));

void yield(void);

#ifdef __riscv
typedef enum : uintptr_t {
    INTERRUPT_S_SOFTWARE         = (1U << 31) | 1,
    INTERRUPT_M_SOFTWARE         = (1U << 31) | 3,
    INTERRUPT_S_TIMER            = (1U << 31) | 5,
    INTERRUPT_M_TIMER            = (1U << 31) | 7,
    INTERRUPT_S_EXTERNAL         = (1U << 31) | 9,
    INTERRUPT_M_EXTERNAL         = (1U << 31) | 11,
    INTERRUPT_M_COUNTER_OVERFLOW = (1U << 31) | 13,
    EXCEPTION_INSTRUCTION_ADDRESS_MISALIGNED  = 0,
    EXCEPTION_INSTRUCTION_ACCESS_FAULT        = 1,
    EXCEPTION_ILLEGAL_INSTRUCTION             = 2,
    EXCEPTION_BREAKPOINT                      = 3,
    EXCEPTION_LOAD_ADDRESS_MISALIGNED         = 4,
    EXCEPTION_LOAD_ACCESS_FAULT               = 5,
    EXCEPTION_STORE_AMO_ADDRESS_MISALIGNED    = 6,
    EXCEPTION_STORE_AMO_ACCESS_FAULT          = 7,
    EXCEPTION_U_ECALL                         = 8,
    EXCEPTION_S_ECALL                         = 9,
    EXCEPTION_M_ECALL                         = 11,
    EXCEPTION_INSTRUCTION_PAGE_FAULT          = 12,
    EXCEPTION_LOAD_PAGE_FAULT                 = 13,
    EXCEPTION_STORE_AMO_PAGE_FAULT            = 15,
    EXCEPTION_SOFTWARE_CHECK                  = 18,
    EXCEPTION_HARDWARE_ERROR                  = 19,
} mcause_t;
#endif

#endif // __AAL_EVENT_H
