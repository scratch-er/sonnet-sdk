#include <bsp/time.h>
#include <stdint.h>

__attribute__((__weak__))
uint64_t uptime_us(void) {
    return 0;
}

__attribute__((__weak__))
uint64_t cycle_count(void) {
    return 0;
}

__attribute__((__weak__))
uint64_t instr_count(void) {
    return 0;
}

__attribute__((__weak__))
void spin_delay(uint32_t us) {
    uint64_t time_begin = uptime_us();
    if (time_begin > 0) {
        // if `uptime_us` is supported, get time with it 
        while (uptime_us() < time_begin + us);
    } else {
        // if `uptime_us` is not supported, use a loop to approximate it.
        for (volatile uint32_t i=0; i<(us>>6); ++i);
    }
}
