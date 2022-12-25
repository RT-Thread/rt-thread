/*
 * Copyright (C) 2016-2020 Bouffalo Lab
 */
    /* stack for IRQs */
    .extern g_irq_sp

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
    csrci   mstatus, 8
    /* TODO: debug */
    csrw    mcycle, zero
    csrw    mcycleh, zero
    csrw    minstret, zero
    csrw    minstreth, zero
#ifndef __NO_HBN_RECV_IN_STARTUP
    /* clear hbn ram ret/slp */
    /* 0x2000F034[7:6] = 0 */
    li  a0, 0x2000F034
    li  a2, 0xFFFFFF3F
    lw  a1, 0(a0)
    and a1, a1, a2
    sw  a1, 0(a0)
    
    /* clear pds ram ret/slp */
    /* 0x2000E020[31:30][7:0] = 0 */
    li  a0, 0x2000E020
    li  a2, 0x3FFFFF00
    lw  a1, 0(a0)
    and a1, a1, a2
    sw  a1, 0(a0)
    /* 0x2000E028[19:0] = 0 */
    li  a0, 0x2000E028
    li  a2, 0xFFF00000
    lw  a1, 0(a0)
    and a1, a1, a2
    sw  a1, 0(a0)
    
    /* load efuse value:if bit[31] is 1,can not jump */
    li a0, 0x2005605C
    lw a0, 0(a0)
    srli a0, a0, 0x1b
    andi a0, a0, 0x10
    li t0, 0x10
    beq t0, a0,  .HBN_NOT_JUMP

    /* check hbn mode */
    li a0, 0x2000f100
    lw a0, 0(a0)
    li t0, 0x4e424845
    bne t0, a0,  .HBN_NOT_JUMP
    li a1, 0x4e424857
    li a2, 0x2000f100
    sw a1, 0(a2)

    /* we can jump unless it's not 0 or 0xffffffff */
    li a0, 0x2000f104
    lw a0, 0(a0)
    addi t0, a0, -1
    li	t1, -3
    bltu t1, t0, .HBN_NOT_JUMP
    jalr a0

.HBN_NOT_JUMP:
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    /*
    li a0, 0x40000060
    li t0, 0x00206F00
    sw t0, 0(a0)
    */
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
#endif

    /* mtvec: for all exceptions and non-vector mode IRQs */
    la      a0, Default_Handler
    ori     a0, a0, 3
    csrw    mtvec, a0

    /* mtvt: for all vector mode IRQs */
    la      a0, __Vectors
    csrw    mtvt, a0

#if defined(__riscv_flen)
    /* FP: initial state */
    csrr    t0, mstatus
    li      t1, ~0x6000
    and     t0, t0, t1
    li      t1, 0x2000
    or      t0, t0, t1
    csrw    mstatus, t0
    /* csrwi   fcsr, 0 */
#endif

    .weak __StackTop
    la      sp, __StackTop
    /* stack: 16-byte aligned */
    andi    sp, sp, -16
    la      t0, g_irq_sp
    /* utilizes the stack point auto-exchange feature */
    csrw    mscratch, t0

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

