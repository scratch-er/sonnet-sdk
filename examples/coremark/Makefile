APP_SRCS += core_list_join.c
APP_SRCS += core_main.c
APP_SRCS += core_matrix.c
APP_SRCS += core_portme.c
APP_SRCS += core_state.c
APP_SRCS += core_util.c

SONNET_SDK_PATH ?= $(abspath ../..)
TOOLCHAIN_FILE ?= $(SONNET_SDK_PATH)/scripts/toolchains/rv32im-clang.mk
APP_BUILD_DIR ?= build

MODULES += $(SONNET_SDK_PATH)/modules/compiler-rt
MODULES += $(SONNET_SDK_PATH)/modules/sonnet-libc

include $(TOOLCHAIN_FILE)
include $(SONNET_SDK_PATH)/scripts/application.mk
