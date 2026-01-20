#ifndef __SOC_NEMU_H
#define __SOC_NEMU_H

#include <periph/simple_uart.h>
#include <periph/riscv_mtime.h>

#define MTIME ((riscv_mtime_map_t*) 0xa0000048)
#define UART ((simple_uart_map_t*) 0xa00003f8)

#endif
