BSP_SRCS += uart.c
BSP_SRCS += bsp.c

SDK_SRCS += src/periph/simple_uart.c

TOOLCHAIN_FILE ?= ../../scripts/toolchains/rv32im-clang.mk
BSP_BUILD_DIR ?= build
include $(TOOLCHAIN_FILE)
include ../../scripts/bsp.mk
