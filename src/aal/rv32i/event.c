#include <stddef.h>
#include <stdint.h>
#include <aal/event.h>
#include <aal/context.h>

__attribute__((__interrupt__)) void __irq_handler(void);

static context_t* (*user_handler)(event_t, context_t*) = NULL;

bool set_event_handler(context_t *(*handler)(event_t ev, context_t *ctx)) {
    // initialize exception entry
    __asm__ volatile("csrw mtvec, %0" : : "r"(__irq_handler));
    // register event handler
    user_handler = handler;
    return true;
}

context_t* __event_handler_wrapper(context_t* context, uintptr_t mcause, uintptr_t mtval) {
    if (user_handler) {
        event_t event;
        event.cause = mcause;
        event.ref = mtval;
        switch (mcause) {
            case EXCEPTION_M_ECALL:
            case EXCEPTION_S_ECALL:
            case EXCEPTION_U_ECALL:
                if (context->a7 == -1) {
                    event.event = EVENT_YIELD;
                } else {
                    event.event = EVENT_SYSCALL;
                }
                context->pc += 4;
                break;
            case INTERRUPT_M_TIMER:
            case INTERRUPT_S_TIMER:
                event.event = EVENT_IRQ_TIMER;
                // TODO: clear timer interrupt
                break;
            case INTERRUPT_M_EXTERNAL:
            case INTERRUPT_S_EXTERNAL:
                event.event = EVENT_IRQ_IODEV;
                // TODO: interact with PLIC
                break;
            default:
                event.event = EVENT_ERROR;
                break;
        }
        context = user_handler(event, context);
    }
    return context;
}