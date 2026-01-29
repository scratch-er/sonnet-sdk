#ifndef __SOC_RETROSOC_H
#define __SOC_RETROSOC_H

#include <periph/retrosoc_gpio.h>
#include <periph/retrosoc_sysuart.h>
// #include <periph/retrosoc_hpuart.h>

#define SYS_FREQ_MHZ 72
#define SYS_FREQ_KHZ (SYS_FREQ_MHZ*1000)
#define SYS_FREQ_HZ  (SYS_FREQ_KHZ*1000)

#define GPIO    ((retrosoc_gpio_map_t*)    0x03000000)
#define SYSUART ((retrosoc_sysuart_map_t*) 0x03000010)
// #define HPUART  ((retrosoc_hpuart_map_t* ) 0x03003000)

#endif // __SOC_RETROSOC_H
