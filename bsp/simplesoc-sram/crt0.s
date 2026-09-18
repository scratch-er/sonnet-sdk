# .section .startup
.global _start

_start:
    la sp, _stack_top

    # zero-init bss section
    # (.data and .text are loaded into initialized RAM by the FPGA bitstream)
    la a0, _sbss
    la a1, _ebss
    bge a0, a1, end_init_bss
    loop_init_bss:
    sw zero, 0(a0)
    addi a0, a0, 4
    blt a0, a1, loop_init_bss
    end_init_bss:

    call bsp_init
    call main
    call halt
