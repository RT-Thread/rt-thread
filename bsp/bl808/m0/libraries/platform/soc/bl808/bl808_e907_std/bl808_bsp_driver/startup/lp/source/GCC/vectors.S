/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 */
 /******************************************************************************
 * @file     vectors.S
 * @brief    define default vector handlers. Should use with
 *           GCC for CSKY Embedded Processors
 * @version  V1.0
 * @date     28. Nove 2017
 ******************************************************************************/
#define __ASSEMBLY__
#include "irq_ctx.h"

/* Enable interrupts when returning from the handler */
#define MSTATUS_PRV1 0x1880

.section .bss
    .align  2
    .globl  g_trapstackalloc
    .global g_trapstackbase
    .global g_top_trapstack
g_trapstackalloc:
g_trapstackbase:
    .space 512
g_top_trapstack:

    .align 2
    .globl g_trap_sp
    .type  g_trap_sp, object
g_trap_sp:
    .long 0
    .size g_trap_sp, .-g_trap_sp

irq_nested_level:
.long 0

.text

#ifndef CONFIG_OS_SUPPORT
    .align  2
    .global Default_IRQHandler
    .weak   Default_IRQHandler
    .type   Default_IRQHandler, %function
Default_IRQHandler:
    addi    sp, sp, -48
    sw      t0, 4(sp)
    sw      t1, 8(sp)
    csrr    t0, mepc
    csrr    t1, mcause
    sw      t1, 40(sp)
    sw      t0, 44(sp)
    csrs    mstatus, 8

    sw      ra, 0(sp)
    sw      t2, 12(sp)
    sw      a0, 16(sp)
    sw      a1, 20(sp)
    sw      a2, 24(sp)
    sw      a3, 28(sp)
    sw      a4, 32(sp)
    sw      a5, 36(sp)

    andi    t1, t1, 0x3FF
    csrw    mscratch, t1
    slli    t1, t1, 2

    la      t0, g_irqvector
    add     t0, t0, t1
    lw      t2, (t0)
    jalr    t2

    /* deal N+32 irq */
    csrr    t1, mscratch
    add     t1, t1,32
    slli    t1, t1, 2
    
    la      t0, g_irqvector
    add     t0, t0, t1
    lw      t2, (t0)
    jalr    t2

    csrc    mstatus, 8

    lw      a1, 40(sp)
    andi    a0, a1, 0x3FF
    slli    a0, a0, 2

    /* clear pending */
    li      a2, 0xE0801000
    add     a2, a2, a0
    sb      zero, 0(a2)

    li      t0, MSTATUS_PRV1
    csrs    mstatus, t0
    csrw    mcause, a1
    lw      t0, 44(sp)
    csrw    mepc, t0
    lw      ra, 0(sp)
    lw      t0, 4(sp)
    lw      t1, 8(sp)
    lw      t2, 12(sp)
    lw      a0, 16(sp)
    lw      a1, 20(sp)
    lw      a2, 24(sp)
    lw      a3, 28(sp)
    lw      a4, 32(sp)
    lw      a5, 36(sp)

    addi    sp, sp, 48
    mret
#else
    .align  2
    .global Default_IRQHandler
    .weak   Default_IRQHandler
    .type   Default_IRQHandler, %function
Default_IRQHandler:
    addi    sp, sp, -8
    sw      t0, 0(sp)
    sw      t1, 4(sp)

    la      t0, irq_nested_level
    lw      t1, (t0)
    addi    t1, t1, 1
    sw      t1, (t0)
    li      t0, 1
    bgt     t1, t0, .Lnested1

    lw      t0, 0(sp)
    lw      t1, 4(sp)
    addi    sp, sp, 8

    csrw    mscratch, sp
    la      sp, __StackTop
    j       .Lnested2
.Lnested1:
    lw      t0, 0(sp)
    lw      t1, 4(sp)
    addi    sp, sp, 8
.Lnested2:
    addi    sp, sp, -48
    sw      t0, 4(sp)
    sw      t1, 8(sp)
    csrr    t0, mepc
    csrr    t1, mcause
    sw      t1, 40(sp)
    sw      t0, 44(sp)

    csrs    mstatus, 8

    sw      ra, 0(sp)
    sw      t2, 12(sp)
    sw      a0, 16(sp)
    sw      a1, 20(sp)
    sw      a2, 24(sp)
    sw      a3, 28(sp)
    sw      a4, 32(sp)
    sw      a5, 36(sp)

    andi    t1, t1, 0x3FF
    slli    t1, t1, 2

    la      t0, g_irqvector
    add     t0, t0, t1
    lw      t2, (t0)
    jalr    t2

    csrc    mstatus, 8

    lw      a1, 40(sp)
    andi    a0, a1, 0x3FF

    /* clear pending */
    li      a2, 0xE000E100
    add     a2, a2, a0
    lb      a3, 0(a2)
    li      a4, 1
    not     a4, a4
    and     a5, a4, a3
    sb      a5, 0(a2)

    la      t0, irq_nested_level
    lw      t1, (t0)
    addi    t1, t1, -1
    sw      t1, (t0)
    bgt     t1, zero, .Lnested3

    li      t0, MSTATUS_PRV1
    csrs    mstatus, t0
    csrw    mcause, a1
    lw      t0, 44(sp)
    csrw    mepc, t0
    lw      ra, 0(sp)
    lw      t0, 4(sp)
    lw      t1, 8(sp)
    lw      t2, 12(sp)
    lw      a0, 16(sp)
    lw      a1, 20(sp)
    lw      a2, 24(sp)
    lw      a3, 28(sp)
    lw      a4, 32(sp)
    lw      a5, 36(sp)

    csrr    sp, mscratch
    mret

.Lnested3:
    li      t0, MSTATUS_PRV1
    csrs    mstatus, t0
    csrw    mcause, a1
    lw      t0, 44(sp)
    csrw    mepc, t0
    lw      ra, 0(sp)
    lw      t0, 4(sp)
    lw      t1, 8(sp)
    lw      t2, 12(sp)
    lw      a0, 16(sp)
    lw      a1, 20(sp)
    lw      a2, 24(sp)
    lw      a3, 28(sp)
    lw      a4, 32(sp)
    lw      a5, 36(sp)

    addi    sp, sp, 48
    mret
#endif

/******************************************************************************
 * Functions:
 *     void trap(void);
 * default exception handler
 ******************************************************************************/
    .align  2
    .global trap
    .type   trap, %function
trap:
    /* Check for interrupt */
    addi    sp, sp, -4
    sw      t0, 0x0(sp)
    csrr    t0, mcause

    blt     t0, x0, .Lirq

    addi    sp, sp, 4

    la      t0,  g_trap_sp
    addi    t0,  t0, -XCPTCONTEXT_SIZE
    sw      x1,  REG_X1(t0)
    sw      x2,  REG_X2(t0)
    sw      x3,  REG_X3(t0)
    sw      x4,  REG_X4(t0)
    sw      x6,  REG_X6(t0)
    sw      x7,  REG_X7(t0)
    sw      x8,  REG_X8(t0)
    sw      x9,  REG_X9(t0)
    sw      x10, REG_X10(t0)
    sw      x11, REG_X11(t0)
    sw      x12, REG_X12(t0)
    sw      x13, REG_X13(t0)
    sw      x14, REG_X14(t0)
    sw      x15, REG_X15(t0)
    csrr    a0,  mepc
    sw      a0,  REG_EPC(t0)
    csrr    a0,  mstatus
    sw      a0,  REG_INT_CTX(t0)

    mv      a0, t0
    lw      t0, -4(sp)
    mv      sp, a0
    sw      t0, REG_X5(sp)

    jal     trap_c

    lw      t0, REG_INT_CTX(sp)
    csrw    mstatus, t0
    lw      t0, REG_EPC(sp)
    csrw    mepc, t0

    lw      x15, REG_X15(sp)
    lw      x14, REG_X14(sp)
    lw      x13, REG_X13(sp)
    lw      x12, REG_X12(sp)
    lw      x11, REG_X11(sp)
    lw      x10, REG_X10(sp)
    lw      x9,  REG_X9(sp)
    lw      x8,  REG_X8(sp)
    lw      x7,  REG_X7(sp)
    lw      x6,  REG_X6(sp)
    lw      x5,  REG_X5(sp)
    lw      x4,  REG_X4(sp)
    lw      x3,  REG_X3(sp)
    lw      x1,  REG_X1(sp)
    lw      x2,  REG_X2(sp)

    mret

.Lirq:
    lw      t0, 0x0(sp)
    addi    sp, sp, 4
    j       Default_IRQHandler

    .align  6
    .weak   Default_Handler
    .global Default_Handler
    .type   Default_Handler, %function
Default_Handler:
    j      trap
    .size   Default_Handler, . - Default_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro  def_irq_handler handler_name
    .weak   \handler_name
    .globl  \handler_name
    .set    \handler_name, Default_Handler
    .endm

    def_irq_handler Mtspend_Handler
