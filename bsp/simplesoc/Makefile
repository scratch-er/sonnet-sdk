BSP_SRCS += bsp.c

SDK_SRCS += src/aal/riscv/context.c
SDK_SRCS += src/aal/riscv/context_asm.S
SDK_SRCS += src/aal/riscv/event.c
SDK_SRCS += src/aal/riscv/event_asm.S
SDK_SRCS += src/hal/simplesoc/gpio.c
SDK_SRCS += src/hal/simplesoc/uart.c
SDK_SRCS += src/periph/gpio/simplesoc_gpio.c
SDK_SRCS += src/periph/uart/simplesoc_uart.c

TOOLCHAIN_FILE ?= ../../scripts/toolchains/rv32e-clang.mk
BSP_BUILD_DIR ?= build
include $(TOOLCHAIN_FILE)
include ../../scripts/bsp.mk
