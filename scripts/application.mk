APP_BUILD_DIR ?= build

CFLAGS += --sysroot=$(SYSROOT) -isystem $(SYSROOT)/include -isystem $(SONNET_SDK_PATH)/include -std=c23
# LDFLAGS += -L $(BSP_BUILD_DIR) -lbsp

APP_OBJS := $(patsubst %.c,$(APP_BUILD_DIR)/objs/%.o,$(APP_SRCS))
APP_OBJS := $(patsubst %.s,$(APP_BUILD_DIR)/objs/%.o,$(APP_OBJS))

COMPILER_RT_BUILD_DIR := $(abspath $(APP_BUILD_DIR))/compiler-rt
BSP_BUILD_DIR := $(abspath $(APP_BUILD_DIR))/bsp

all: $(APP_BUILD_DIR)/application.elf $(APP_BUILD_DIR)/application.bin

clean:
	$(MAKE) -C $(BSP_PATH) BSP_BUILD_DIR=$(BSP_BUILD_DIR) TOOLCHAIN_FILE=$(abspath $(TOOLCHAIN_FILE)) clean
	rm -f $(APP_OBJS)
	rm -f $(APP_BUILD_DIR)/crt0.o $(APP_BUILD_DIR)/application.elf $(APP_BUILD_DIR)/application.bin

$(APP_BUILD_DIR)/objs/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(APP_BUILD_DIR)/objs/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(APP_BUILD_DIR)/crt0.o: $(BSP_PATH)/crt0.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

%.bin:%.elf
	$(OBJCOPY) -O binary --only-section .text $< $@

$(APP_BUILD_DIR)/application.elf: $(APP_BUILD_DIR)/crt0.o $(APP_OBJS)
	$(MAKE) -C $(BSP_PATH) BSP_BUILD_DIR=$(BSP_BUILD_DIR) TOOLCHAIN_FILE=$(abspath $(TOOLCHAIN_FILE))
	$(LD) $(LDFLAGS) -T $(BSP_PATH)/linker.ld $(APP_BUILD_DIR)/crt0.o $(APP_OBJS) $(APP_BUILD_DIR)/bsp/libbsp.a -o $@

.PHONY: all clean clean_config clean_all example
