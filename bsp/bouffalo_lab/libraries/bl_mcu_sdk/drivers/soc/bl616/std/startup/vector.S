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

.section .bss.g_trap_stack

    .align 4
    .global g_trap_sp_base
    .global g_trap_sp
g_trap_sp_base:
#if defined(__riscv_flen)
    .space 1024
#else
    .space 512
#endif
g_trap_sp:
#if 0
.section .bss.g_irq_stack
    .align 4
    .global g_irq_sp_base
    .global g_irq_sp
g_irq_sp_base:
    .space 1024
g_irq_sp:
#endif
/******************************************************************************
 * Functions:
 *     void default_interrupt_handler(void);
 * default handler for all the vector mode IRQs
 ******************************************************************************/

    .section .text.vectors.default_interrupt_handler, "ax", %progbits
    .align  6
    .global default_interrupt_handler
    .weak   default_interrupt_handler
    /* FreeRTOS will define tspend_handler for context switch */
    .type   default_interrupt_handler, %function
default_interrupt_handler:
    /* ipush */
    addi  sp, sp, -76

    /* save x5 x6 then save mepc mcause */
    sw    x5, 4(sp)
    sw    x6, 8(sp)
    csrr  t0, mepc
    csrr  t1, mcause
    sw    t1, 64(sp)
    sw    t0, 68(sp)
    csrr  t0, mscratch
    sw    t0, 72(sp)
    /* save regs */
    sw      x1, 0(sp)
    sw      x7, 12(sp)
    sw      x10, 16(sp)
    sw      x11, 20(sp)
    sw      x12, 24(sp)
    sw      x13, 28(sp)
    sw      x14, 32(sp)
    sw      x15, 36(sp)
    sw      x16, 40(sp)
    sw      x17, 44(sp)
    sw      x28, 48(sp)
    sw      x29, 52(sp)
    sw      x30, 56(sp)
    sw      x31, 60(sp)

    /*
     * IRQ stack contents after ipush:
     * ~mem addr high:
     * +  0:  <--- init IRQ sp (mscratch)
     * -  4:  mepc
     * -  8:  mcause
     * - 12:  x1  (ra)
     * - 16:  x5  (t0)
     * - 20:  x6  (t1)
     * - 24:  x7  (t2)
     * - 28:  x10 (a0)
     * - 32:  x11 (a1)
     * - 36:  x12 (a2)
     * - 40:  x13 (a3)
     * - 44:  x14 (a4)
     * - 48:  x15 (a5)
     * - 52:  x16 (a6)
     * - 56:  x17 (a7)
     * - 60:  x28 (t3)
     * - 64:  x29 (t4)
     * - 68:  x30 (t5)
     * - 72:  x31 (t6)   <--- current IRQ sp
     * ~mem addr low:
     */
    /* WARNING: global IRQ enabled by ipush */
    csrs    mstatus, 8

    /* keep stack 16bytes aligned */
    addi    sp, sp, -88

    /* - 76:  mstatus  */
    csrr    t1, mstatus
    sw      t1, 84(sp)
    srli    t2, t1, 13
    andi    t2, t2, 0x3
    li      t0, 0x3
    bne     t2, t0,  .F_RegNotSave1

    fsw     ft0, 0(sp)
    fsw     ft1, 4(sp)
    fsw     ft2, 8(sp)
    fsw     ft3, 12(sp)
    fsw     ft4, 16(sp)
    fsw     ft5, 20(sp)
    fsw     ft6, 24(sp)
    fsw     ft7, 28(sp)
    fsw     fa0, 32(sp)
    fsw     fa1, 36(sp)
    fsw     fa2, 40(sp)
    fsw     fa3, 44(sp)
    fsw     fa4, 48(sp)
    fsw     fa5, 52(sp)
    fsw     fa6, 56(sp)
    fsw     fa7, 60(sp)
    fsw     ft8, 64(sp)
    fsw     ft9, 68(sp)
    fsw     ft10,72(sp)
    fsw     ft11,76(sp)
.F_RegNotSave1:

    csrr    a0, mcause
    andi    t1, a0, 0x3FF
    /* get ISR */
    la      t2, interrupt_entry
    jalr    t2

    lw      t1, 84(sp)
    srli    t2, t1, 13
    andi    t2, t2, 0x3
    li      t0, 0x3
    bne     t2, t0,  .F_RegNotLoad

    flw     ft0, 0(sp)
    flw     ft1, 4(sp)
    flw     ft2, 8(sp)
    flw     ft3, 12(sp)
    flw     ft4, 16(sp)
    flw     ft5, 20(sp)
    flw     ft6, 24(sp)
    flw     ft7, 28(sp)
    flw     fa0, 32(sp)
    flw     fa1, 36(sp)
    flw     fa2, 40(sp)
    flw     fa3, 44(sp)
    flw     fa4, 48(sp)
    flw     fa5, 52(sp)
    flw     fa6, 56(sp)
    flw     fa7, 60(sp)
    flw     ft8, 64(sp)
    flw     ft9, 68(sp)
    flw     ft10,72(sp)
    flw     ft11,76(sp)

.F_RegNotLoad:
    addi    sp, sp, 88
    /* mret included, and IRQ tail-chain may happen */
    /* ipop */

    csrc    mstatus, 8
    /* restore mepc mcause mscrath */
    lw      t0, 68(sp)
    csrw    mepc, t0
    lw      t0, 64(sp)
    csrw    mcause, t0
    lw      t0, 72(sp)
    csrw    mscratch, t0
    /* restore regs */
    lw      x1, 0(sp)
    lw      x5, 4(sp)
    lw      x6, 8(sp)
    lw      x7, 12(sp)
    lw      x10, 16(sp)
    lw      x11, 20(sp)
    lw      x12, 24(sp)
    lw      x13, 28(sp)
    lw      x14, 32(sp)
    lw      x15, 36(sp)
    lw      x16, 40(sp)
    lw      x17, 44(sp)
    lw      x28, 48(sp)
    lw      x29, 52(sp)
    lw      x30, 56(sp)
    lw      x31, 60(sp)

    addi    sp, sp, 76
    mret

    .size   default_interrupt_handler, . - default_interrupt_handler

/******************************************************************************
 * Functions:
 *     void trap(void);
 * default handler for exceptions and non-vector mode IRQs
 ******************************************************************************/
    .section .text.vectors.default_trap_handler, "ax", %progbits
    .align  6
    .global trap
    .type   trap, %function
    .weak   default_trap_handler
    .global default_trap_handler
    .type   default_trap_handler, %function
default_trap_handler:
trap:
    /* Check for interrupt */
    sw      t0, -4(sp)
    csrr    t0, mcause

    /* IRQ, but in non-vector mode */
    blt     t0, x0, .Lirq

    la      t0, g_trap_sp
    addi    t0, t0, -XCPTCONTEXT_SIZE
    sw      x1, REG_X1(t0)
    sw      x2, REG_X2(t0)
    sw      x3, REG_X3(t0)
    sw      x4, REG_X4(t0)
    sw      x6, REG_X6(t0)
    sw      x7, REG_X7(t0)
    sw      x8, REG_X8(t0)
    sw      x9, REG_X9(t0)
    sw      x10, REG_X10(t0)
    sw      x11, REG_X11(t0)
    sw      x12, REG_X12(t0)
    sw      x13, REG_X13(t0)
    sw      x14, REG_X14(t0)
    sw      x15, REG_X15(t0)
    sw      x16, REG_X16(t0)
    sw      x17, REG_X17(t0)
    sw      x18, REG_X18(t0)
    sw      x19, REG_X19(t0)
    sw      x20, REG_X20(t0)
    sw      x21, REG_X21(t0)
    sw      x22, REG_X22(t0)
    sw      x23, REG_X23(t0)
    sw      x24, REG_X24(t0)
    sw      x25, REG_X25(t0)
    sw      x26, REG_X26(t0)
    sw      x27, REG_X27(t0)
    sw      x28, REG_X28(t0)
    sw      x29, REG_X29(t0)
    sw      x30, REG_X30(t0)
    sw      x31, REG_X31(t0)
    csrr    a0, mepc
    sw      a0, REG_EPC(t0)
    csrr    a0, mstatus
    sw      a0, REG_INT_CTX(t0)

    mv      a0, t0
    lw      t0, -4(sp)
    mv      sp, a0
    sw      t0, REG_X5(sp)

    jal     exception_entry

    lw      t0, REG_INT_CTX(sp)
    csrw    mstatus, t0
    lw      t0, REG_EPC(sp)
    csrw    mepc, t0

    lw      x31, REG_X31(sp)
    lw      x30, REG_X30(sp)
    lw      x29, REG_X29(sp)
    lw      x28, REG_X28(sp)
    lw      x27, REG_X27(sp)
    lw      x26, REG_X26(sp)
    lw      x25, REG_X25(sp)
    lw      x24, REG_X24(sp)
    lw      x23, REG_X23(sp)
    lw      x22, REG_X22(sp)
    lw      x21, REG_X21(sp)
    lw      x20, REG_X20(sp)
    lw      x19, REG_X19(sp)
    lw      x18, REG_X18(sp)
    lw      x17, REG_X17(sp)
    lw      x16, REG_X16(sp)
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
    lw      t0, -4(sp)
/* MSOFT IRQ for FreeRTOS context switch
 * Config MSOFT IRQ to non-vector mode
 * tspend_handler is a weak alias to default_interrupt_handler
 */
    j       default_interrupt_handler

    .size   default_trap_handler, . - default_trap_handler