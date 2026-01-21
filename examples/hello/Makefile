APP_SRCS += hello.c

SONNET_SDK_PATH ?= $(abspath ../..)
TOOLCHAIN_FILE ?= $(SONNET_SDK_PATH)/scripts/toolchains/rv32im-clang.mk
APP_BUILD_DIR ?= build

MODULES += $(SONNET_SDK_PATH)/modules/compiler-rt

include $(TOOLCHAIN_FILE)
include $(SONNET_SDK_PATH)/scripts/application.mk