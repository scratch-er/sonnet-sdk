APP_BUILD_DIR ?= build

CFLAGS += -isystem $(SONNET_SDK_PATH)/include -std=c23
CXXFLAGS += -isystem $(SONNET_SDK_PATH)/include -std=c++23 -fno-rtti -fno-exceptions -nostdinc++
CFLAGS += $(foreach dir,$(APP_INCLUDE_DIRS),-I$(dir))
CXXFLAGS += $(foreach dir,$(APP_INCLUDE_DIRS),-I$(dir))

APP_OBJS := $(patsubst %.c,$(APP_BUILD_DIR)/objs/%.o,$(APP_SRCS))
APP_OBJS := $(patsubst %.cc,$(APP_BUILD_DIR)/objs/%.o,$(APP_OBJS))
APP_OBJS := $(patsubst %.cpp,$(APP_BUILD_DIR)/objs/%.o,$(APP_OBJS))
APP_OBJS := $(patsubst %.s,$(APP_BUILD_DIR)/objs/%.o,$(APP_OBJS))
APP_OBJS := $(patsubst %.S,$(APP_BUILD_DIR)/objs/%.o,$(APP_OBJS))

BSP_BUILD_DIR := $(abspath $(APP_BUILD_DIR))/bsp

all: $(APP_BUILD_DIR)/application.elf $(APP_BUILD_DIR)/application.bin

clean:
	rm -rf $(APP_BUILD_DIR)

# Process module support
$(foreach module,$(MODULES),$(eval include $(module)/module.mk))
CFLAGS += $(foreach dir,$(MODULE_INCLUDE_DIRS),-isystem $(dir))
CXXFLAGS += $(foreach dir,$(MODULE_INCLUDE_DIRS),-isystem $(dir))

# Rule for C sources
$(APP_BUILD_DIR)/objs/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule for C++ sources
$(APP_BUILD_DIR)/objs/%.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(APP_BUILD_DIR)/objs/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Rule for assembly sources
$(APP_BUILD_DIR)/objs/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(APP_BUILD_DIR)/objs/%.o: %.S
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule for startup code
$(APP_BUILD_DIR)/crt0.o: $(BSP_PATH)/crt0.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule for converting elf into bin
%.bin:%.elf
	$(OBJCOPY) -O binary $< $@

# Rule for generating `compile_commands.json`
compile_commands: $(APP_BUILD_DIR)/compile_commands.json

$(APP_BUILD_DIR)/compile_commands.json:
	@mkdir -p $(dir $@)
	python3 $(SONNET_SDK_PATH)/scripts/compile-commands.py $(CC) $(APP_BUILD_DIR) $(CFLAGS) -- $(APP_SRCS)

# Rule for building the application elf
$(APP_BUILD_DIR)/application.elf: $(APP_BUILD_DIR)/crt0.o $(APP_OBJS) $(MODULE_LIBS)
	$(MAKE) -C $(BSP_PATH) BSP_BUILD_DIR=$(BSP_BUILD_DIR) TOOLCHAIN_FILE=$(abspath $(TOOLCHAIN_FILE))
	$(LD) $(LDFLAGS) -T $(BSP_PATH)/linker.ld $(APP_BUILD_DIR)/crt0.o $(APP_OBJS) $(APP_BUILD_DIR)/bsp/libbsp.a $(MODULE_LIBS) -o $@

.PHONY: all clean clean_config clean_all compile_commands $(APP_BUILD_DIR)/compile_commands.json
