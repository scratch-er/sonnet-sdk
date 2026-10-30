APP_SRCS += main.c
APP_SRCS += flame.c
APP_SRCS += fixed_math.c

APP_BUILD_DIR ?= build
SONNET_SDK_PATH ?= $(abspath ../..)
BSP_PATH?=$(SONNET_SDK_PATH)/bsp/simplesoc-sram
TOOLCHAIN_FILE ?= $(SONNET_SDK_PATH)/scripts/toolchains/rv32e-clang.mk
export BSP_PATH
export TOOLCHAIN_FILE

MODULES += $(SONNET_SDK_PATH)/modules/compiler-rt
MODULES += $(SONNET_SDK_PATH)/modules/lightio

include $(TOOLCHAIN_FILE)
include $(SONNET_SDK_PATH)/scripts/application.mk
