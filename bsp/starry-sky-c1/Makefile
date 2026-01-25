BSP_SRCS += bsp.c

SDK_SRCS += src/hal/retrosoc/uart.c
SDK_SRCS += src/periph/uart/retrosoc_sysuart.c

TOOLCHAIN_FILE ?= ../../scripts/toolchains/rv32im-clang.mk
BSP_BUILD_DIR ?= build
include $(TOOLCHAIN_FILE)
include ../../scripts/bsp.mk
