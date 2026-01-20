#include <bsp/io.h>
#include <bsp/sys.h>
#include <bsp/time.h>
#include <hal/uart.h>
#include <soc/nemu.h>
#include <stdint.h>

extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _heap_start;

const area_t heap = {
    .start = &_heap_start,
    .end = (void*)(0x80000000+128*1024*1024)
};

void bsp_init (void) {
    return;
}

/* IO */

char getch(void) {
    return uart_read(UART);
}

void putch(char ch) {
    return uart_write(UART, ch);
}

/* System */

__attribute__((__noreturn__))
void halt(int code) {
    __asm__ volatile ("ebreak");
    while (true);
}

__attribute__((__noreturn__))
void reset(int code) {
    __asm__ volatile ("ebreak");
    while (true);
}

/* Time */

uint64_t uptime_us(void) {
    return MTIME->mtime;
}
