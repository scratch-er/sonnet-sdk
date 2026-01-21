APP_BUILD_DIR ?= build

CFLAGS += -isystem $(SONNET_SDK_PATH)/include -std=c23

APP_OBJS := $(patsubst %.c,$(APP_BUILD_DIR)/objs/%.o,$(APP_SRCS))
APP_OBJS := $(patsubst %.s,$(APP_BUILD_DIR)/objs/%.o,$(APP_OBJS))

BSP_BUILD_DIR := $(abspath $(APP_BUILD_DIR))/bsp

all: $(APP_BUILD_DIR)/application.elf $(APP_BUILD_DIR)/application.bin

clean:
	rm -rf $(APP_BUILD_DIR)

# Process module support
$(foreach module,$(MODULES),$(eval include $(module)/module.mk))
CFLAGS += $(foreach dir,$(MODULE_INCLUDE_DIRS),-isystem $(dir))

# Rule for C sources
$(APP_BUILD_DIR)/objs/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule for assembly sources
$(APP_BUILD_DIR)/objs/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule for startup code
$(APP_BUILD_DIR)/crt0.o: $(BSP_PATH)/crt0.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule for converting elf into bin
%.bin:%.elf
	$(OBJCOPY) -O binary --only-section .text $< $@

# Rule for building the application elf
$(APP_BUILD_DIR)/application.elf: $(APP_BUILD_DIR)/crt0.o $(APP_OBJS) $(MODULE_LIBS)
	$(MAKE) -C $(BSP_PATH) BSP_BUILD_DIR=$(BSP_BUILD_DIR) TOOLCHAIN_FILE=$(abspath $(TOOLCHAIN_FILE))
	$(LD) $(LDFLAGS) -T $(BSP_PATH)/linker.ld $(APP_BUILD_DIR)/crt0.o $(APP_OBJS) $(APP_BUILD_DIR)/bsp/libbsp.a $(MODULE_LIBS) -o $@

.PHONY: all clean clean_config clean_all example
