#include <bsp/io.h>
#include <bsp/sys.h>
#include <bsp/time.h>
#include <hal/uart.h>
#include <soc/retrosoc.h>
#include <stdint.h>

extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _heap_start;

int main(void);

const area_t heap = {
    .start = &_heap_start,
    .end = (void*)0x04800000
};

void bsp_init (void) {
    uart_config_baudrate(SYSUART, 115200, SYS_FREQ_HZ);
}

void putch(char ch) {
    uart_write(SYSUART, ch);
}

uint64_t uptime_us(void) {
    static uint32_t higher = 0;
    static uint32_t lower_old = 0;
    uint32_t lower;
    __asm__ volatile ("rdcycle %0" : "=r"(lower));
    if (lower < lower_old) {
        higher += 1;
    }
    lower_old = lower;
    return (((uint64_t)(higher)<<32) | lower) / SYS_FREQ_MHZ;
}
