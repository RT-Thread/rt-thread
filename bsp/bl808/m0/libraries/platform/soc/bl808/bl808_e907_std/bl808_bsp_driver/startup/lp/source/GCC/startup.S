/*
 * Copyright (C) 2016-2020 Bouffalo Lab
 */

_start:
    .text
    .align  2
    .globl  Reset_Handler
    .type   Reset_Handler, %function
Reset_Handler:
.option push
.option norelax
    la      gp, __global_pointer$
.option pop
    /* disable global IRQ */
    csrci   mstatus, 8
    csrw    mcycle, zero
    csrw    minstret, zero

    la      a0, Default_Handler
    ori     a0, a0, 3
    csrw    mtvec, a0

    la      a0, __Vectors
    csrw    mtvt, a0

    .weak __StackTop
    la      sp, __StackTop
    csrw    mscratch, sp

    /* Load data section removed */
    
    /* Clear bss section removed */

#ifndef __NO_SYSTEM_INIT
    jal     System_Init
#endif
  
    /* start load code to itcm like. */
    jal     start_load

#ifndef __NO_BOARD_INIT
    jal     System_Post_Init
#endif

    jal     main

    .size   Reset_Handler, . - Reset_Handler

__exit:
    j      __exit

