.global get_stack_pointer
.global switch_to_context

get_stack_pointer:
    mv a0, sp
    ret

#if __riscv_e
#define N_REGS 16
#else
#define N_REGS 32
#endif

#if __riscv_xlen == 32
#define LOAD  lw
#define STORE sw
#define XSIZE 4
#endif

#if __riscv_xlen == 64
#define LOAD  ld
#define STORE sd
#define XSIZE 8
#endif

#define CTX_SIZE (XSIZE*N_REGS)

switch_to_context:
    // saves the pointer to the context to be saved
    // if the second argument `context** save` is not NULL
    beq a1, zero, 1f
    // the starting address of the context to be saved will be sp - 128
    addi sp, sp, -CTX_SIZE
    STORE sp, 0(a1)
    // restore the sp so original sp will be saved
    addi sp, sp, CTX_SIZE
1:
    // save the context to the stack
    // the first slot is meant for pc
    // for a context saved in a trap service routine
    // it is mepc that is saved here
    // pc is not saved for user-mode context switching
    // however, if the context is switched back
    // it should be as if the it returns from `switch_to_context`
    STORE ra,  -(CTX_SIZE-0*XSIZE)(sp)
    // we have to save ra again
    // we never know whether this context will be restored
    // from user-mode or from trap service
    STORE x1,  -(CTX_SIZE-1*XSIZE)(sp)
    // save other registers
    STORE x2,  -(CTX_SIZE-2*XSIZE)(sp)
    STORE x3,  -(CTX_SIZE-3*XSIZE)(sp)
    STORE x4,  -(CTX_SIZE-4*XSIZE)(sp)
    STORE x5,  -(CTX_SIZE-5*XSIZE)(sp)
    STORE x6,  -(CTX_SIZE-6*XSIZE)(sp)
    STORE x7,  -(CTX_SIZE-7*XSIZE)(sp)
    STORE x8,  -(CTX_SIZE-8*XSIZE)(sp)
    STORE x9,  -(CTX_SIZE-9*XSIZE)(sp)
    STORE x10, -(CTX_SIZE-10*XSIZE)(sp)
    STORE x11, -(CTX_SIZE-11*XSIZE)(sp)
    STORE x12, -(CTX_SIZE-12*XSIZE)(sp)
    STORE x13, -(CTX_SIZE-13*XSIZE)(sp)
    STORE x14, -(CTX_SIZE-14*XSIZE)(sp)
    STORE x15, -(CTX_SIZE-15*XSIZE)(sp)
#ifndef __riscv_e
    STORE x16, -(CTX_SIZE-16*XSIZE)(sp)
    STORE x17, -(CTX_SIZE-17*XSIZE)(sp)
    STORE x18, -(CTX_SIZE-18*XSIZE)(sp)
    STORE x19, -(CTX_SIZE-19*XSIZE)(sp)
    STORE x20, -(CTX_SIZE-20*XSIZE)(sp)
    STORE x21, -(CTX_SIZE-21*XSIZE)(sp)
    STORE x22, -(CTX_SIZE-22*XSIZE)(sp)
    STORE x23, -(CTX_SIZE-23*XSIZE)(sp)
    STORE x24, -(CTX_SIZE-24*XSIZE)(sp)
    STORE x25, -(CTX_SIZE-25*XSIZE)(sp)
    STORE x26, -(CTX_SIZE-26*XSIZE)(sp)
    STORE x27, -(CTX_SIZE-27*XSIZE)(sp)
    STORE x28, -(CTX_SIZE-28*XSIZE)(sp)
    STORE x29, -(CTX_SIZE-29*XSIZE)(sp)
    STORE x30, -(CTX_SIZE-30*XSIZE)(sp)
    STORE x31, -(CTX_SIZE-31*XSIZE)(sp)
#endif
    // now restore the context to switch to
    // storing its address in t0
    // since will be corrupted anyways
    mv t0, a0
    LOAD x1,  (1*XSIZE)(t0)
    LOAD x2,  (2*XSIZE)(t0)
    LOAD x3,  (3*XSIZE)(t0)
    LOAD x4,  (4*XSIZE)(t0)
    // t0 is busy at this time
    LOAD x6,  (6*XSIZE)(t0)
    LOAD x7,  (7*XSIZE)(t0)
    LOAD x8,  (8*XSIZE)(t0)
    LOAD x9,  (9*XSIZE)(t0)
    LOAD x10, (10*XSIZE)(t0)
    LOAD x11, (11*XSIZE)(t0)
    LOAD x12, (12*XSIZE)(t0)
    LOAD x13, (13*XSIZE)(t0)
    LOAD x14, (14*XSIZE)(t0)
    LOAD x15, (15*XSIZE)(t0)
#ifndef __riscv_e
    LOAD x16, (16*XSIZE)(t0)
    LOAD x17, (17*XSIZE)(t0)
    LOAD x18, (18*XSIZE)(t0)
    LOAD x19, (19*XSIZE)(t0)
    LOAD x20, (20*XSIZE)(t0)
    LOAD x21, (21*XSIZE)(t0)
    LOAD x22, (22*XSIZE)(t0)
    LOAD x23, (23*XSIZE)(t0)
    LOAD x24, (24*XSIZE)(t0)
    LOAD x25, (25*XSIZE)(t0)
    LOAD x26, (26*XSIZE)(t0)
    LOAD x27, (27*XSIZE)(t0)
    LOAD x28, (28*XSIZE)(t0)
    LOAD x29, (29*XSIZE)(t0)
    LOAD x30, (30*XSIZE)(t0)
    LOAD x31, (31*XSIZE)(t0)
#endif
    // now load the pc of the new context into t0
    // note that t0 will always be corruptted in this way
    // but this is the architectural limitation of user-mode contexts
    LOAD t0, 0(t0)
    // return to the context like a normal funcion return
    // since ra and sp have been replaced
    jalr x0, t0, 0
