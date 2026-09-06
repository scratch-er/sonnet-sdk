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
#ifdef __riscv_e
    li a5, -1
#else
    li a7, -1
#endif
    ecall
    ret

#if __riscv_e
#define N_REGS 16
#define XLAST x15
#else
#define N_REGS 32
#define XLAST x31
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

__irq_handler:
    // save the context to the stack
    STORE x1, -(CTX_SIZE-1*XSIZE)(sp)
    STORE x2, -(CTX_SIZE-2*XSIZE)(sp)
    STORE x3, -(CTX_SIZE-3*XSIZE)(sp)
    STORE x4, -(CTX_SIZE-4*XSIZE)(sp)
    STORE x5, -(CTX_SIZE-5*XSIZE)(sp)
    STORE x6, -(CTX_SIZE-6*XSIZE)(sp)
    STORE x7, -(CTX_SIZE-7*XSIZE)(sp)
    STORE x8, -(CTX_SIZE-8*XSIZE)(sp)
    STORE x9, -(CTX_SIZE-9*XSIZE)(sp)
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
    // the first slot is meant for pc
    csrr a0, mepc
    STORE a0, -CTX_SIZE(sp)
    // call the event handler wrapper
    // it should return a pointer to the context to restore
    addi sp, sp, -CTX_SIZE
    mv a0, sp
    csrr a1, mcause
    csrr a2, mtval
    call __event_handler_wrapper
    // now restore the context to switch to
    // XLAST is the last to be restored
    // so use it to hold the address
    mv XLAST, a0
    // first restore mepc
    LOAD a0, 0(XLAST)
    csrw mepc, a0
    // restore all registers
    LOAD x0,  (0*XSIZE)(XLAST)
    LOAD x1,  (1*XSIZE)(XLAST)
    LOAD x2,  (2*XSIZE)(XLAST)
    LOAD x3,  (3*XSIZE)(XLAST)
    LOAD x4,  (4*XSIZE)(XLAST)
    LOAD x5,  (5*XSIZE)(XLAST)
    LOAD x6,  (6*XSIZE)(XLAST)
    LOAD x7,  (7*XSIZE)(XLAST)
    LOAD x8,  (8*XSIZE)(XLAST)
    LOAD x9,  (9*XSIZE)(XLAST)
    LOAD x10, (10*XSIZE)(XLAST)
    LOAD x11, (11*XSIZE)(XLAST)
    LOAD x12, (12*XSIZE)(XLAST)
    LOAD x13, (13*XSIZE)(XLAST)
    LOAD x14, (14*XSIZE)(XLAST)
    LOAD x15, (15*XSIZE)(XLAST)
#ifndef __riscv_e
    LOAD x16, (16*XSIZE)(XLAST)
    LOAD x17, (17*XSIZE)(XLAST)
    LOAD x18, (18*XSIZE)(XLAST)
    LOAD x19, (19*XSIZE)(XLAST)
    LOAD x20, (20*XSIZE)(XLAST)
    LOAD x21, (21*XSIZE)(XLAST)
    LOAD x22, (22*XSIZE)(XLAST)
    LOAD x23, (23*XSIZE)(XLAST)
    LOAD x24, (24*XSIZE)(XLAST)
    LOAD x25, (25*XSIZE)(XLAST)
    LOAD x26, (26*XSIZE)(XLAST)
    LOAD x27, (27*XSIZE)(XLAST)
    LOAD x28, (28*XSIZE)(XLAST)
    LOAD x29, (29*XSIZE)(XLAST)
    LOAD x30, (30*XSIZE)(XLAST)
    LOAD x31, (31*XSIZE)(XLAST)
#endif
    mret
