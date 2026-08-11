APP_SRCS += src/bench.c
APP_SRCS += src/lzip/lzip.c
APP_SRCS += src/lzip/quicklz.c
APP_SRCS += src/qsort/qsort.c
APP_SRCS += src/md5/md5.c
APP_SRCS += src/fib/fib.c
APP_SRCS += src/bf/bf.c
APP_SRCS += src/sieve/sieve.c
APP_SRCS += src/queen/queen.c
APP_SRCS += src/15pz/15pz.cc
APP_SRCS += src/dinic/dinic.cc
APP_SRCS += src/ssort/ssort.cc

APP_INCLUDE_DIRS += include

SONNET_SDK_PATH ?= $(abspath ../..)
TOOLCHAIN_FILE ?= $(SONNET_SDK_PATH)/scripts/toolchains/rv32im-clang.mk
APP_BUILD_DIR ?= build

MODULES += $(SONNET_SDK_PATH)/modules/compiler-rt
MODULES += $(SONNET_SDK_PATH)/modules/sonnet-libc

include $(TOOLCHAIN_FILE)
include $(SONNET_SDK_PATH)/scripts/application.mk
