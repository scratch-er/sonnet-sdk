#include <aal/context.h>
#include <aal/event.h>
#include <am.h>
#include <bsp/io.h>
#include <bsp/time.h>
#include <stddef.h>

/* IOE */

/* Peripherals are supposed to be initialized by `bsp_init()`
 * Doing nothing here.
 */
__attribute__((__weak__))
bool ioe_init(void) {
    return true;
}

__attribute__((__weak__))
void ioe_read(int reg, void *buf) {
    switch (reg) {
        case AM_UART_CONFIG: {
            AM_UART_CONFIG_T *dest = (AM_UART_CONFIG_T*) buf;
            dest->present = true;
            break;
        }
        case AM_UART_TX: {
            break;
        }
        case AM_UART_RX: {
            AM_UART_RX_T *dest = (AM_UART_RX_T*) buf;
            dest->data = getch();
            break;
        }
        case AM_TIMER_CONFIG: {
            AM_TIMER_CONFIG_T *dest = (AM_TIMER_CONFIG_T*) buf;
            dest->present = true;
            dest->has_rtc = false;
            break;
        }
        case AM_TIMER_RTC: {
            AM_TIMER_RTC_T *dest = (AM_TIMER_RTC_T*) buf;
            dest->year = 1900;
            dest->month = 1;
            dest->day = 1;
            dest->hour = 0;
            dest->minute = 0;
            dest->second = 0;
            break;
        }
        case AM_TIMER_UPTIME: {
            AM_TIMER_UPTIME_T *dest = (AM_TIMER_UPTIME_T*) buf;
            dest->us = uptime_us();
            break;
        }
    }
}

__attribute__((__weak__))
void ioe_write(int reg, void *buf) {
    switch (reg) {
        case AM_UART_CONFIG: {
            break;
        }
        case AM_UART_TX: {
            AM_UART_TX_T *src = (AM_UART_TX_T*) buf;
            putch(src->data);
            break;
        }
        case AM_UART_RX: {
            break;
        }
        case AM_TIMER_CONFIG: {
            break;
        }
        case AM_TIMER_RTC: {
            break;
        }
        case AM_TIMER_UPTIME: {
            break;
        }
    }
}

/* CTE */

bool cte_init(Context *(*handler)(Event, Context *)) {
    return set_event_handler(handler);
}

static void *cte_kcontext_entry(void *arg) {
    return arg;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
    return create_context(cte_kcontext_entry, entry, kstack.end, arg);
}

/* MPE */
__attribute__((__weak__))
bool mpe_init(void (*entry)()) {
    entry();
    return false;
}

__attribute__((__weak__))
int cpu_count(void) {
    return 1;
}

__attribute__((__weak__))
int cpu_current(void) {
    return 0;
}

__attribute__((__weak__))
int atomic_xchg(int *addr, int newval) {
    int ret = *addr;
    *addr = newval;
    return ret;
}
