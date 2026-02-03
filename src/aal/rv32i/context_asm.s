.global get_stack_pointer
.global switch_to_context

get_stack_pointer:
    mv a0, sp
    ret

switch_to_context:
    # saves the pointer to the context to be saved
    # if the second argument `context** save` is not NULL
    beq a1, zero, 1f
    # the starting address of the context to be saved will be sp - 128
    addi sp, sp, -128
    sw sp, 0(a1)
    # restore the sp so original sp will be saved
    addi sp, sp, 128
1:
    # save the context to the stack
    # the first slot is meant for pc
    # for a context saved in a trap service routine
    # it is mepc that is saved here
    # pc is not saved for user-mode context switching
    # however, if the context is switched back
    # it should be as if the it returns from `switch_to_context`
    sw ra, -128(sp)
    # we have to save ra again
    # we never know whether this context will be restored
    # from user-mode or from trap service
    sw x1, -124(sp)
    # save other registers
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
    # now restore the context to switch to
    # storing its address in t0
    # since will be corrupted anyways
    addi t0, a0, 0
    lw x1, 4(t0)
    lw x2, 8(t0)
    lw x3, 12(t0)
    lw x4, 16(t0)
    # t0 is busy at this time
    lw x6, 24(t0)
    lw x7, 28(t0)
    lw x8, 32(t0)
    lw x9, 36(t0)
    lw x10, 40(t0)
    lw x11, 44(t0)
    lw x12, 48(t0)
    lw x13, 52(t0)
    lw x14, 56(t0)
    lw x15, 60(t0)
    lw x16, 64(t0)
    lw x17, 68(t0)
    lw x18, 72(t0)
    lw x19, 76(t0)
    lw x20, 80(t0)
    lw x21, 84(t0)
    lw x22, 88(t0)
    lw x23, 92(t0)
    lw x24, 96(t0)
    lw x25, 100(t0)
    lw x26, 104(t0)
    lw x27, 108(t0)
    lw x28, 112(t0)
    lw x29, 116(t0)
    lw x30, 120(t0)
    lw x31, 124(t0)
    # now load the pc of the new context into t0
    # note that t0 will always be corruptted in this way
    # but this is the architectural limitation of user-mode contexts
    lw t0, 0(t0)
    # return to the context like a normal funcion return
    # since ra and sp have been replaced
    jalr x0, t0, 0
