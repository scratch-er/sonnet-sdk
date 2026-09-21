#ifndef __SOC_SIMPLESOC_H
#define __SOC_SIMPLESOC_H

#include <periph/simplesoc_uart.h>
#include <periph/simplesoc_gpio.h>
#include <periph/simplesoc_timer.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Core clock frequency in Hz. The SoC itself does not fix a frequency
 * (simulation harness / FPGA PLL decides), so override this from the
 * build flags to match the actual clock. Used for the UART divisor and
 * cycle-counter based timekeeping. */
#ifndef SIMPLESOC_CPU_FREQ_HZ
#define SIMPLESOC_CPU_FREQ_HZ 50000000UL
#endif

/* Console UART baudrate. */
#ifndef SIMPLESOC_UART_BAUD
#define SIMPLESOC_UART_BAUD 115200UL
#endif

#define UART0  ((simplesoc_uart_map_t*)  0x10000000)
#define UART1  ((simplesoc_uart_map_t*)  0x10001000)
#define GPIO0  ((simplesoc_gpio_map_t*)  0x10002000)
#define GPIO1  ((simplesoc_gpio_map_t*)  0x10003000)
#define TIMER0 ((simplesoc_timer_map_t*) 0x10004000)
#define TIMER1 ((simplesoc_timer_map_t*) 0x10005000)

#ifdef __cplusplus
}
#endif

#endif // __SOC_SIMPLESOC_H
