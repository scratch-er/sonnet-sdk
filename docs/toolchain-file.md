# Toolchain Files

This SDK uses toolchain files to define the cross-compilation environment (it is a similar concept with CMake's toolchain file, or Meson's crossfile). It specifies the compiler, assembler, linker, and other tools along with their flags. A toolchain file is a Makefile segment that is included by the main Makefile.

Please see `scripts/toolchains` for some examples of toolchain files. Note that these files are only examples that work out of the box. They are not necessarily suitable for your scenario. Users are encouraged to modify the examples or write their own toolchain files. For example, `rv32im-clang.mk` uses `-O3` and `-flto` for aggressive optimization for speed, which can also produce larger code (aggressive loop unrolling, function inlining, etc.). If you are building applications for an embedded RISC-V device with very limited ROM, you might want to use `-Os`, and enable compressed instructions (if supported) for a smaller code size.

## Toolchain File Specification

In a toolchain file, the following variables need to be defined:

```makefile
CC := YOUR_C_COMPILER
AS := YOUR_ASSEMBLER
AR := YOUR_ARCHIVER
LD := YOUR_LINKER # Can be the C compiler with extra flags
OBJCOPY := YOUR_OBJCOPY_PROGRAM
OBJDUMP := YOUR_OBJDUMP_PROGRAM

CFLAGS += C COMPILER FLAGS
LDFLAGS += LINKER FLAGS
```

Note that, you should define each executable name with `:=` and append to toolchain flags with `+=`, since the executables need to be specified once and remain unchanged, while other parts of the build system can add new toolchain flags. Please refer to Makefile reference materials if you have any questions about this.
