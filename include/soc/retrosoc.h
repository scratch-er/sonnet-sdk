#ifndef __SOC_RETROSOC_H
#define __SOC_RETROSOC_H

#include <periph/retrosoc_sysuart.h>

#define SYS_FREQ_MHZ 72
#define SYS_FREQ_KHZ (SYS_FREQ_MHZ*1000)
#define SYS_FREQ_HZ  (SYS_FREQ_KHZ*1000)

#define SYSUART ((retrosoc_sysuart_map_t*) 0x03000010)

#endif // __SOC_RETROSOC_H
