#include <bsp/io.h>
#include <bsp/sys.h>
#include <bsp/time.h>
#include <hal/uart.h>
#include <soc/simplesoc.h>
#include <stdint.h>

extern uint32_t _heap_start;
extern uint32_t _heap_end;

const area_t heap = {
    .start = &_heap_start,
    .end = &_heap_end
};

void bsp_init (void) {
    uart_config_t config = {
        .baudrate_hz = SIMPLESOC_UART_BAUD,
        .word_length = 8,
        .stop_bits = 1,
        .patity = false,
        .flow_control = false,
    };
    uart_config(UART0, &config);
}

/* IO */

char getch(void) {
    return uart_read(UART0);
}

void putch(char ch) {
    uart_write(UART0, ch);
}

/* System */

__attribute__((__noreturn__))
void halt(int code) {
    (void)code;
    __asm__ volatile ("ebreak");
    while (true);
}

__attribute__((__noreturn__))
void reset(int code) {
    (void)code;
    extern void _start(void);
    _start();
    while (true);
}

/* Time */

uint64_t cycle_count(void) {
    uint32_t hi, lo;
    do {
        __asm__ volatile ("csrr %0, mcycleh" : "=r"(hi));
        __asm__ volatile ("csrr %0, mcycle" : "=r"(lo));
    } while (hi != ({ uint32_t t; __asm__ volatile ("csrr %0, mcycleh" : "=r"(t)); t; }));
    return ((uint64_t)hi << 32) | lo;
}

uint64_t instr_count(void) {
    uint32_t hi, lo;
    do {
        __asm__ volatile ("csrr %0, minstreth" : "=r"(hi));
        __asm__ volatile ("csrr %0, minstret" : "=r"(lo));
    } while (hi != ({ uint32_t t; __asm__ volatile ("csrr %0, minstreth" : "=r"(t)); t; }));
    return ((uint64_t)hi << 32) | lo;
}

uint64_t uptime_us(void) {
    return cycle_count() / (SIMPLESOC_CPU_FREQ_HZ / 1000000UL);
}
