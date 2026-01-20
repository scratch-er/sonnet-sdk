# .section .startup
.global _start

_start:
    # copy data section
    # lui a0, %hi(_sidata)
    # addi a0, a0, %lo(_sidata)
    # lui a1, %hi(_sdata)
    # addi a1, a1, %lo(_sdata)
    # lui a2, %hi(_edata)
    # addi a2, a2, %lo(_sdata)
    # li t0, 0x03000010
    # li t1, 625
    # sw t1, 0(t0)
    # li t1, 'A'
    # sw t1, 4(t0)
    la a0, _sidata
    la a1, _sdata
    la a2, _edata
    bge a1, a2, end_init_data
    loop_init_data:
    lw a3, 0(a0)
    sw a3, 0(a1)
    addi a0, a0, 4
    addi a1, a1, 4
    blt a1, a2, loop_init_data
    end_init_data:

    # zero-init bss section
    # lui a0, %hi(_sbss)
    # addi a0, a0, %lo(_sbss)
    # lui a1, %hi(_ebss)
    # addi a1, a1, %lo(_ebss)
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

    # lui t0, %hi(bsp_init)
    # addi t0, t0, %lo(bsp_init)
    # jalr ra, t0

    # lui t0, %hi(main)
    # addi t0, t0, %lo(main)
    # jalr ra, t0

    # lui t0, %hi(halt)
    # addi t0, t0, %lo(halt)
    # jalr ra, t0
