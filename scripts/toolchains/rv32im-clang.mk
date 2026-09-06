CC := clang
CXX := clang++
AS := clang
AR := llvm-ar
# Use clang in linking for LTO
LD := clang --target=riscv32-unknown-elf -mabi=ilp32 -march=rv32im -flto -O3 -g -fuse-ld=lld
OBJCOPY := llvm-objcopy
OBJDUMP := llvm-objdump

CFLAGS += -flto --target=riscv32-unknown-elf -mabi=ilp32 -march=rv32im -ffreestanding -nostdlib -O3 -g -ffunction-sections -fdata-sections
CXXFLAGS += -flto --target=riscv32-unknown-elf -mabi=ilp32 -march=rv32im -ffreestanding -nostdlib -O3 -g -ffunction-sections -fdata-sections
LDFLAGS += -Bstatic -nostdlib -Wl,--gc-sections
