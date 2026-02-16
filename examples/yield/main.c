#include <aal/context.h>
#include <aal/event.h>
#include <bsp/time.h>
#include <stddef.h>
#include <lightio.h>
#include <stddef.h>
#include <stdint.h>

#define STACK_SIZE 256
#define N_THREADS 8

typedef struct {
    uintptr_t stack[STACK_SIZE];
    context_t* context;
} thread_t;

thread_t threads[N_THREADS];

void* hello(void* arg) {
    uint32_t count = 0;
    while (true) {
        count += 1;
        output_str("Hello, world from thread ", 0);
        output_uint32_dec((uint32_t)arg, 0);
        output_str(", ", 0);
        output_uint32_dec(count, 0);
        output_str(" time(s).\r\n", 0);
        spin_delay(500000);
        yield();
    }
    return 0;
}

context_t *schedule(event_t event, context_t* context) {
    static size_t tid = SIZE_MAX;
    output_str("schedule: from tid ", 0);
    output_uint32_dec(tid, 0);
    if (tid < N_THREADS) {
        threads[tid].context = context;
        tid = (tid+1>=N_THREADS) ? 0 : tid+1;
    } else {
        tid = 0;
    }
    output_str(" to tid ", 0);
    output_uint32_dec(tid, 0);
    output_str(".\r\n", 0);
    context = threads[tid].context;
    return context;
}   

int main() {
    set_event_handler(schedule);
    for (size_t i=0; i<N_THREADS; ++i) {
        threads[i].context = create_context(hello, NULL, threads[i].stack+STACK_SIZE, (void*)i);
    }
    yield();
    return 0;
}
