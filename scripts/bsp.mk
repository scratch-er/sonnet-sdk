SDK_SRCS += src/bsp/am.c
SDK_SRCS += src/bsp/io.c
SDK_SRCS += src/bsp/sys.c
SDK_SRCS += src/bsp/time.c

SONNET_SDK_PATH ?= $(abspath ../..)
BSP_BUILD_DIR ?= build

CFLAGS += --sysroot=$(SYSROOT) -isystem $(SYSROOT)/include -isystem $(SONNET_SDK_PATH)/include -std=c23

BSP_OBJS := $(patsubst %.c,$(BSP_BUILD_DIR)/bsp-objs/%.o,$(BSP_SRCS))
BSP_OBJS := $(patsubst %.s,$(BSP_BUILD_DIR)/bsp-objs/%.o,$(BSP_OBJS))
SDK_OBJS := $(patsubst %.c,$(BSP_BUILD_DIR)/sdk-objs/%.o,$(SDK_SRCS))
SDK_OBJS := $(patsubst %.s,$(BSP_BUILD_DIR)/sdk-objs/%.o,$(SDK_OBJS))

all: $(BSP_BUILD_DIR)/libbsp.a

clean:
	rm -rf $(BSP_BUILD_DIR)/libbsp.a $(BSP_BUILD_DIR)/bsp-objs $(BSP_BUILD_DIR)/sdk-objs

$(BSP_BUILD_DIR)/bsp-objs/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BSP_BUILD_DIR)/bsp-objs/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BSP_BUILD_DIR)/sdk-objs/%.o: $(SONNET_SDK_PATH)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BSP_BUILD_DIR)/sdk-objs/%.o: $(SONNET_SDK_PATH)/%.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BSP_BUILD_DIR)/libbsp.a: $(BSP_OBJS) $(SDK_OBJS)
	@rm -f $@
	$(AR) rcs $@ $(BSP_OBJS) $(SDK_OBJS)

.PHONY: all clean
