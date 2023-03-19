/*
 * Copyright (C) 2016-2020 Bouffalo Lab
 */

    .section .init
    .align  2
    .globl  __start
    .type   __start, %function
__start:
.option push
.option norelax
    la      gp, __global_pointer$
.option pop
    csrci   mstatus, 8

    /* mtvec: for all exceptions and non-vector mode IRQs */
    la      a0, default_trap_handler
    ori     a0, a0, 3
    csrw    mtvec, a0

    /* mtvt: for all vector mode IRQs */
    la      a0, __Vectors
    csrw    mtvt, a0
    
    .weak __StackTop
    la      sp, __StackTop
    csrw    mscratch, sp

    /* Load data section removed */

    /* Clear bss section removed */

    jal     SystemInit

    /* start load code to itcm like. */
    jal     start_load

    jal     System_Post_Init

    jal     entry

    .size   __start, . - __start

__exit:
    j      __exit

