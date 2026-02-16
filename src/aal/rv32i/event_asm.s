.global ienabled
.global iset
.global yield
.global __irq_handler

ienabled:
    csrr a0, mstatus
    andi a0, a0, 1<<3
    srl a0, a0, 3

iset:
    beq a0, zero, 1f
    csrsi mstatus, 1<<3
    ret
1:
    csrci mstatus, 1<<3
    ret

yield:
    li a7, -1
    ecall
    ret

__irq_handler:
    # save the context to the stack
    sw x1, -124(sp)
    sw x2, -120(sp)
    sw x3, -116(sp)
    sw x4, -112(sp)
    sw x5, -108(sp)
    sw x6, -104(sp)
    sw x7, -100(sp)
    sw x8, -96(sp)
    sw x9, -92(sp)
    sw x10, -88(sp)
    sw x11, -84(sp)
    sw x12, -80(sp)
    sw x13, -76(sp)
    sw x14, -72(sp)
    sw x15, -68(sp)
    sw x16, -64(sp)
    sw x17, -60(sp)
    sw x18, -56(sp)
    sw x19, -52(sp)
    sw x20, -48(sp)
    sw x21, -44(sp)
    sw x22, -40(sp)
    sw x23, -36(sp)
    sw x24, -32(sp)
    sw x25, -28(sp)
    sw x26, -24(sp)
    sw x27, -20(sp)
    sw x28, -16(sp)
    sw x29, -12(sp)
    sw x30, -8(sp)
    sw x31, -4(sp)
    # the first slot is meant for pc
    csrr a0, mepc
    sw a0, -128(sp)
    # call the event handler wrapper
    # it should return a pointer to the context to restore
    addi sp, sp, -128
    mv a0, sp
    csrr a1, mcause
    csrr a2, mtval
    call __event_handler_wrapper
    # now restore the context to switch to
    # x31 is the last to be restored
    # so use it to hold the address
    mv x31, a0
    # first restore mepc
    lw a0, 0(x31)
    csrw mepc, a0
    # restore all registers
    lw x1, 4(x31)
    lw x2, 8(x31)
    lw x3, 12(x31)
    lw x4, 16(x31)
    lw x5, 16(x31)
    lw x6, 24(x31)
    lw x7, 28(x31)
    lw x8, 32(x31)
    lw x9, 36(x31)
    lw x10, 40(x31)
    lw x11, 44(x31)
    lw x12, 48(x31)
    lw x13, 52(x31)
    lw x14, 56(x31)
    lw x15, 60(x31)
    lw x16, 64(x31)
    lw x17, 68(x31)
    lw x18, 72(x31)
    lw x19, 76(x31)
    lw x20, 80(x31)
    lw x21, 84(x31)
    lw x22, 88(x31)
    lw x23, 92(x31)
    lw x24, 96(x31)
    lw x25, 100(x31)
    lw x26, 104(x31)
    lw x27, 108(x31)
    lw x28, 112(x31)
    lw x29, 116(x31)
    lw x30, 120(x31)
    lw x31, 124(x31)
    mret
