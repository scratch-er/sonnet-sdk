CC := clang
AS := clang
AR := llvm-ar
# Use clang in linking for LTO
LD := clang --target=riscv32-unknown-elf -mabi=ilp32 -march=rv32im -flto -O3 -g
OBJCOPY := llvm-objcopy
OBJDUMP := llvm-objdump

# Use LLVM IR as the object file format to enable better LTO
CFLAGS += -emit-llvm --target=riscv32-unknown-elf -mabi=ilp32 -march=rv32im -ffreestanding -nostdlib -O3 -g
LDFLAGS += -Bstatic -nostdlib
