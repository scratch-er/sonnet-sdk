#ifndef __PERIPH_RISCV_MTIME_H
#define __PERIPH_RISCV_MTIME_H

#include <stdint.h>

typedef struct {
    volatile uint64_t mtime __attribute__((__aligned__(8)));
    volatile uint64_t mtimecmp __attribute__((__aligned__(8)));
} __attribute__((__packed__)) riscv64_mtime_map_t;

typedef struct {
    volatile uint32_t mtimel __attribute__((__aligned__(4)));
    volatile uint32_t mtimeh __attribute__((__aligned__(4)));
    volatile uint32_t mtimecmpl __attribute__((__aligned__(4)));
    volatile uint32_t mtimrcmph __attribute__((__aligned__(4)));
} __attribute__((__packed__)) riscv32_mtime_map_t;

typedef riscv64_mtime_map_t riscv_mtime_map_t;

#endif // __PERIPH_RISCV_MTIME_H
