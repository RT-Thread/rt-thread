/*
 * Copyright (C) 2016-2020 Bouffalo Lab
 */
#include <risc-v/csr.h>

    .section .init
    .align  2
    .globl  __start
    .type   __start, %function
__start:
.option push
.option norelax
    la      gp, __global_pointer$
.option pop

    li      t0, MSTATUS_MIE | MSTATUS_SIE
    csrc    mstatus, t0

    /* mapbaddr */
    /* ? clear PLIC ?*/
    csrr    t1, 0xfc1
    li      t2, 0x00200004
    add     t2, t2, t1
    lw      t3, 0(t2)
    sw      t3, 0(t2)
    li      t4, 0x00201004
    add     t2, t4, t1
    lw      t3, 0(t2)
    sw      t3, 0(t2)

    csrw    mie, zero
    csrw    mip, zero

	/* invalid all MMU TLB Entry */
    sfence.vma x0,x0

    /* TODO: debug */
    csrw    mcycle, zero
    csrw    minstret, zero

    /*
     * enable thead ISA extension:
     * THEADISAEE = 1, MM = 1,
     */
    csrr    t0, mxstatus
    li      t1, (1 << 22) | (1 << 15)
    or      t1, t1, t0
    csrw    mxstatus, t1

    /* FP: initial state */
    csrr    t0, mstatus
    li      t1, ~0x6000
    and     t0, t0, t1
    li      t1, 0x2000
    or      t0, t0, t1
    csrw    mstatus, t0
    /* csrwi   fcsr, 0 */

    /* RVV: initial state */
    li    t0, ~(3 << 23)
    csrr  t1, mstatus
    and   t2, t1, t0
    li    t0, 1 << 23
    or    t2, t2, t0
    csrw  mstatus, t2

    la      a0, __Vectors__
    ori     a0, a0, 1
    csrw    mtvec, a0

    la      a0, __Vectors_S__
    ori     a0, a0, 1
    csrw    stvec, a0

    .weak __StackTop
    la      sp, __StackTop
    csrw    mscratch, sp

    jal     SystemInit

    /* start load code to itcm like. */
    jal     start_load

    jal     System_Post_Init

    jal     main

    .size   __start, . - __start

__exit:
    j      __exit
