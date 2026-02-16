BSP_SRCS += bsp.c

SDK_SRCS += src/aal/rv32i/context.c
SDK_SRCS += src/aal/rv32i/context_asm.s
SDK_SRCS += src/aal/rv32i/event.c
SDK_SRCS += src/aal/rv32i/event_asm.s
SDK_SRCS += src/hal/nemu/uart.c
SDK_SRCS += src/periph/uart/simple_uart.c

TOOLCHAIN_FILE ?= ../../scripts/toolchains/rv32im-clang.mk
BSP_BUILD_DIR ?= build
include $(TOOLCHAIN_FILE)
include ../../scripts/bsp.mk
