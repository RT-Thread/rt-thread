#define __ASSEMBLY__
#include "irq_ctx.h"

/* Enable interrupts when returning from the handler */
#define MSTATUS_PRV1 0x0080
#define SSTATUS_PRV1 0x0020

.section .text
    .align  6
    .globl  __Vectors__
    .type   __Vectors__, @object
__Vectors__:
.option push
.option norvc
    j   exception_common		/* 0 */
    j   Stspend_Handler			/* 1 */
    j   Default_Handler			/* 2 */
#if defined(__OS_FREERTOS__)
    j   Mtspend_Handler			/* 3 */
#else
    j   M_SoftIRQ_ISR			/* 3 : Machine Software Interrupt */
#endif
    j   Default_Handler			/* 4 */
    j   Scoret_Handler			/* 5 */
    j   Default_Handler			/* 6 */
    j   Mcoret_Handler			/* 7 */
    j   Default_Handler			/* 8 */
    j   Sirq_Handler_M			/* 9 */
    j   Default_Handler			/* 10 */
    j   Default_IRQHandler		/* 11 */
    j   Default_Handler			/* 12 */
    j   Default_Handler			/* 13 */
    j   Default_Handler			/* 14 */
    j   Default_Handler			/* 15 */
    j   Default_Handler			/* 16 */
    j   HPM_OVF_IRQHandler		/* 17 */
.option pop

.section .text
    .align  6
    .globl  __Vectors_S__
    .type   __Vectors_S__, @object
__Vectors_S__:
.option push
.option norvc
    j   exception_common		/* 0 */
    j   Stspend_Handler_S		/* 1 */
    j   Default_Handler			/* 2 */
    j   M_SoftIRQ_ISR			/* 3 */
    j   Default_Handler			/* 4 */
    j   Scoret_Handler			/* 5 */
    j   Default_Handler			/* 6 */
    j   Mcoret_Handler			/* 7 */
    j   Default_Handler			/* 8 */
    j   Sirq_Handler			/* 9 */
    j   Default_Handler			/* 10 */
    j   Default_IRQHandler		/* 11 */
    j   Default_Handler			/* 12 */
    j   Default_Handler			/* 13 */
    j   Default_Handler			/* 14 */
    j   Default_Handler			/* 15 */
    j   Default_Handler			/* 16 */
    j   HPM_OVF_IRQHandler		/* 17 */
.option pop

.section .bss.vector.g_trap_stack
    .align  4
    .globl  g_trapstackalloc
    .global g_trapstackbase
    .global g_top_trapstack
g_trapstackalloc:
g_trapstackbase:
    .space 2048                /* 32I(64bit) + 32D(64bit) + 32V(128bit) */
g_top_trapstack:
g_trap_sp:

irq_nested_level:
.long 0

.text

    .align  2
    .global Scoret_Handler
    .weak   Scoret_Handler
    .type   Scoret_Handler, %function
Scoret_Handler:
    j       Stspend_Handler

    .align  2
    .global Mcoret_Handler
    .weak   Mcoret_Handler
    .type   Mcoret_Handler, %function
Mcoret_Handler:
    addi    sp, sp, -(76+76)
    sd      t0, (4+4)(sp)
    sd      t1, (8+8)(sp)
    sd      t2, (12+12)(sp)

    csrr    t0, mepc
    sd      t0, (68+68)(sp)
    sd      t2, (72+72)(sp)
    sd      ra, (0 +0 )(sp)
    sd      a0, (16+16)(sp)
    sd      a1, (20+20)(sp)
    sd      a2, (24+24)(sp)
    sd      a3, (28+28)(sp)
    sd      a4, (32+32)(sp)
    sd      a5, (36+36)(sp)
    sd      a6, (40+40)(sp)
    sd      a7, (44+44)(sp)
    sd      t3, (48+48)(sp)
    sd      t4, (52+52)(sp)
    sd      t5, (56+56)(sp)
    sd      t6, (60+60)(sp)

    addi    sp,  sp, -160
    fsd     ft0, (0 +0 )(sp)
    fsd     ft1, (4 +4 )(sp)
    fsd     ft2, (8 +8 )(sp)
    fsd     ft3, (12+12)(sp)
    fsd     ft4, (16+16)(sp)
    fsd     ft5, (20+20)(sp)
    fsd     ft6, (24+24)(sp)
    fsd     ft7, (28+28)(sp)
    fsd     fa0, (32+32)(sp)
    fsd     fa1, (36+36)(sp)
    fsd     fa2, (40+40)(sp)
    fsd     fa3, (44+44)(sp)
    fsd     fa4, (48+48)(sp)
    fsd     fa5, (52+52)(sp)
    fsd     fa6, (56+56)(sp)
    fsd     fa7, (60+60)(sp)
    fsd     ft8, (64+64)(sp)
    fsd     ft9, (68+68)(sp)
    fsd     ft10,(72+72)(sp)
    fsd     ft11,(76+76)(sp)

#if defined(__OS_FREERTOS__)
    la      t2, CORET_IRQHandler
    jalr    t2
#else
    li      a0, 7
    la      t2, interrupt_entry
    jalr    t2
#endif
    csrc    mstatus, 8

    li      t0, MSTATUS_PRV1
    csrs    mstatus, t0

    fld     ft0, (0 +0 )(sp)
    fld     ft1, (4 +4 )(sp)
    fld     ft2, (8 +8 )(sp)
    fld     ft3, (12+12)(sp)
    fld     ft4, (16+16)(sp)
    fld     ft5, (20+20)(sp)
    fld     ft6, (24+24)(sp)
    fld     ft7, (28+28)(sp)
    fld     fa0, (32+32)(sp)
    fld     fa1, (36+36)(sp)
    fld     fa2, (40+40)(sp)
    fld     fa3, (44+44)(sp)
    fld     fa4, (48+48)(sp)
    fld     fa5, (52+52)(sp)
    fld     fa6, (56+56)(sp)
    fld     fa7, (60+60)(sp)
    fld     ft8, (64+64)(sp)
    fld     ft9, (68+68)(sp)
    fld     ft10,(72+72)(sp)
    fld     ft11,(76+76)(sp)

    addi    sp, sp, 160

    ld      t0, (68+68)(sp)
    csrw    mepc, t0
    ld      ra, (0 +0 )(sp)
    ld      t0, (4 +4 )(sp)
    ld      t1, (8 +8 )(sp)
    ld      t2, (12+12)(sp)
    ld      a0, (16+16)(sp)
    ld      a1, (20+20)(sp)
    ld      a2, (24+24)(sp)
    ld      a3, (28+28)(sp)
    ld      a4, (32+32)(sp)
    ld      a5, (36+36)(sp)
    ld      a6, (40+40)(sp)
    ld      a7, (44+44)(sp)
    ld      t3, (48+48)(sp)
    ld      t4, (52+52)(sp)
    ld      t5, (56+56)(sp)
    ld      t6, (60+60)(sp)

    addi    sp, sp, (76+76)
    mret

/****************************************************************************
 * Name: Sirq_Handler
 ****************************************************************************/
    /* S-mode external IRQ handler */
    .align  2
    .global Sirq_Handler
    .weak   Sirq_Handler
    .type   Sirq_Handler, %function
Sirq_Handler:
    addi    sp, sp, -(76+76)
    sd      t0, (4+4)(sp)
    sd      t1, (8+8)(sp)
    sd      t2, (12+12)(sp)

    li      t0, 0xe0201000
    lw      t2, 4(t0)

    csrr    t0, sepc
    sd      t0, (68+68)(sp)
    sd      t2, (72+72)(sp)
    sd      ra, (0 +0 )(sp)
    sd      a0, (16+16)(sp)
    sd      a1, (20+20)(sp)
    sd      a2, (24+24)(sp)
    sd      a3, (28+28)(sp)
    sd      a4, (32+32)(sp)
    sd      a5, (36+36)(sp)
    sd      a6, (40+40)(sp)
    sd      a7, (44+44)(sp)
    sd      t3, (48+48)(sp)
    sd      t4, (52+52)(sp)
    sd      t5, (56+56)(sp)
    sd      t6, (60+60)(sp)

    addi    sp,  sp, -160
    fsd     ft0, (0 +0 )(sp)
    fsd     ft1, (4 +4 )(sp)
    fsd     ft2, (8 +8 )(sp)
    fsd     ft3, (12+12)(sp)
    fsd     ft4, (16+16)(sp)
    fsd     ft5, (20+20)(sp)
    fsd     ft6, (24+24)(sp)
    fsd     ft7, (28+28)(sp)
    fsd     fa0, (32+32)(sp)
    fsd     fa1, (36+36)(sp)
    fsd     fa2, (40+40)(sp)
    fsd     fa3, (44+44)(sp)
    fsd     fa4, (48+48)(sp)
    fsd     fa5, (52+52)(sp)
    fsd     fa6, (56+56)(sp)
    fsd     fa7, (60+60)(sp)
    fsd     ft8, (64+64)(sp)
    fsd     ft9, (68+68)(sp)
    fsd     ft10,(72+72)(sp)
    fsd     ft11,(76+76)(sp)

    andi    t2, t2, 0x3FF
    mv      a0, t2
    slli    t2, t2, 3

    la      t2, interrupt_entry
    jalr    t2

    csrc    sstatus, 2


    /* write PLIC_CLAIM and exit interrupt */
    lw      a1, (72+72+160)(sp)
    andi    a0, a1, 0x3FF

    li      a2, 0xe0201000
    sw      a0, 4(a2)

    li      t0, SSTATUS_PRV1
    csrs    sstatus, t0

    fld     ft0, (0 +0 )(sp)
    fld     ft1, (4 +4 )(sp)
    fld     ft2, (8 +8 )(sp)
    fld     ft3, (12+12)(sp)
    fld     ft4, (16+16)(sp)
    fld     ft5, (20+20)(sp)
    fld     ft6, (24+24)(sp)
    fld     ft7, (28+28)(sp)
    fld     fa0, (32+32)(sp)
    fld     fa1, (36+36)(sp)
    fld     fa2, (40+40)(sp)
    fld     fa3, (44+44)(sp)
    fld     fa4, (48+48)(sp)
    fld     fa5, (52+52)(sp)
    fld     fa6, (56+56)(sp)
    fld     fa7, (60+60)(sp)
    fld     ft8, (64+64)(sp)
    fld     ft9, (68+68)(sp)
    fld     ft10,(72+72)(sp)
    fld     ft11,(76+76)(sp)

    addi    sp, sp, 160

    ld      t0, (68+68)(sp)
    csrw    sepc, t0
    ld      ra, (0 +0 )(sp)
    ld      t0, (4 +4 )(sp)
    ld      t1, (8 +8 )(sp)
    ld      t2, (12+12)(sp)
    ld      a0, (16+16)(sp)
    ld      a1, (20+20)(sp)
    ld      a2, (24+24)(sp)
    ld      a3, (28+28)(sp)
    ld      a4, (32+32)(sp)
    ld      a5, (36+36)(sp)
    ld      a6, (40+40)(sp)
    ld      a7, (44+44)(sp)
    ld      t3, (48+48)(sp)
    ld      t4, (52+52)(sp)
    ld      t5, (56+56)(sp)
    ld      t6, (60+60)(sp)

    addi    sp, sp, (76+76)
    sret

/****************************************************************************
 * Name: Sirq_Handler_M
 ****************************************************************************/
    /* Sirq in M-Mode will be handled here */
    /* 1. IRQ is enabled in PLIC for S-Mode */
    /* 2. No IRQ delegation */
    .align  2
    .global Sirq_Handler_M
    .weak   Sirq_Handler_M
    .type   Sirq_Handler_M, %function
Sirq_Handler_M:
    addi    sp, sp, -(76+76)
    sd      t0, (4+4)(sp)
    sd      t1, (8+8)(sp)
    sd      t2, (12+12)(sp)

    csrr    t0, 0xfc1
    li      t1, 0x00201000
    add     t0, t0, t1
    lw      t2, 4(t0)

    csrr    t0, mepc
    sd      t0, (68+68)(sp)
    sd      t2, (72+72)(sp)
    sd      ra, (0 +0 )(sp)
    sd      a0, (16+16)(sp)
    sd      a1, (20+20)(sp)
    sd      a2, (24+24)(sp)
    sd      a3, (28+28)(sp)
    sd      a4, (32+32)(sp)
    sd      a5, (36+36)(sp)
    sd      a6, (40+40)(sp)
    sd      a7, (44+44)(sp)
    sd      t3, (48+48)(sp)
    sd      t4, (52+52)(sp)
    sd      t5, (56+56)(sp)
    sd      t6, (60+60)(sp)

    addi    sp,  sp, -160
    fsd     ft0, (0 +0 )(sp)
    fsd     ft1, (4 +4 )(sp)
    fsd     ft2, (8 +8 )(sp)
    fsd     ft3, (12+12)(sp)
    fsd     ft4, (16+16)(sp)
    fsd     ft5, (20+20)(sp)
    fsd     ft6, (24+24)(sp)
    fsd     ft7, (28+28)(sp)
    fsd     fa0, (32+32)(sp)
    fsd     fa1, (36+36)(sp)
    fsd     fa2, (40+40)(sp)
    fsd     fa3, (44+44)(sp)
    fsd     fa4, (48+48)(sp)
    fsd     fa5, (52+52)(sp)
    fsd     fa6, (56+56)(sp)
    fsd     fa7, (60+60)(sp)
    fsd     ft8, (64+64)(sp)
    fsd     ft9, (68+68)(sp)
    fsd     ft10,(72+72)(sp)
    fsd     ft11,(76+76)(sp)

    andi    t2, t2, 0x3FF
    mv      a0, t2
    slli    t2, t2, 3

    la      t2, interrupt_entry
    jalr    t2

    csrc    mstatus, 8


    /* write PLIC_CLAIM and exit interrupt */
    lw      a1, (72+72+160)(sp)
    andi    a0, a1, 0x3FF

    csrr    a2, 0xfc1
    li      a1, 0x00201000
    add     a2, a2, a1
    sw      a0, 4(a2)

    li      t0, MSTATUS_PRV1
    csrs    mstatus, t0

    fld     ft0, (0 +0 )(sp)
    fld     ft1, (4 +4 )(sp)
    fld     ft2, (8 +8 )(sp)
    fld     ft3, (12+12)(sp)
    fld     ft4, (16+16)(sp)
    fld     ft5, (20+20)(sp)
    fld     ft6, (24+24)(sp)
    fld     ft7, (28+28)(sp)
    fld     fa0, (32+32)(sp)
    fld     fa1, (36+36)(sp)
    fld     fa2, (40+40)(sp)
    fld     fa3, (44+44)(sp)
    fld     fa4, (48+48)(sp)
    fld     fa5, (52+52)(sp)
    fld     fa6, (56+56)(sp)
    fld     fa7, (60+60)(sp)
    fld     ft8, (64+64)(sp)
    fld     ft9, (68+68)(sp)
    fld     ft10,(72+72)(sp)
    fld     ft11,(76+76)(sp)

    addi    sp, sp, 160

    ld      t0, (68+68)(sp)
    csrw    mepc, t0
    ld      ra, (0 +0 )(sp)
    ld      t0, (4 +4 )(sp)
    ld      t1, (8 +8 )(sp)
    ld      t2, (12+12)(sp)
    ld      a0, (16+16)(sp)
    ld      a1, (20+20)(sp)
    ld      a2, (24+24)(sp)
    ld      a3, (28+28)(sp)
    ld      a4, (32+32)(sp)
    ld      a5, (36+36)(sp)
    ld      a6, (40+40)(sp)
    ld      a7, (44+44)(sp)
    ld      t3, (48+48)(sp)
    ld      t4, (52+52)(sp)
    ld      t5, (56+56)(sp)
    ld      t6, (60+60)(sp)

    addi    sp, sp, (76+76)
    mret

/****************************************************************************
 * Name: Default_IRQHandler
 ****************************************************************************/
    /* M-mode external IRQ handler */
    .align  2
    .global Default_IRQHandler
    .weak   Default_IRQHandler
    .type   Default_IRQHandler, %function
Default_IRQHandler:
    addi    sp, sp, -(76+76)
    sd      t0, (4+4)(sp)
    sd      t1, (8+8)(sp)
    sd      t2, (12+12)(sp)

    csrr    t0, 0xfc1
    li      t1, 0x00200000
    add     t0, t0, t1
    lw      t2, 4(t0)

    csrr    t0, mepc
    sd      t0, (68+68)(sp)
    sd      t2, (72+72)(sp)
    sd      ra, (0 +0 )(sp)
    sd      a0, (16+16)(sp)
    sd      a1, (20+20)(sp)
    sd      a2, (24+24)(sp)
    sd      a3, (28+28)(sp)
    sd      a4, (32+32)(sp)
    sd      a5, (36+36)(sp)
    sd      a6, (40+40)(sp)
    sd      a7, (44+44)(sp)
    sd      t3, (48+48)(sp)
    sd      t4, (52+52)(sp)
    sd      t5, (56+56)(sp)
    sd      t6, (60+60)(sp)

    addi    sp,  sp, -160
    fsd     ft0, (0 +0 )(sp)
    fsd     ft1, (4 +4 )(sp)
    fsd     ft2, (8 +8 )(sp)
    fsd     ft3, (12+12)(sp)
    fsd     ft4, (16+16)(sp)
    fsd     ft5, (20+20)(sp)
    fsd     ft6, (24+24)(sp)
    fsd     ft7, (28+28)(sp)
    fsd     fa0, (32+32)(sp)
    fsd     fa1, (36+36)(sp)
    fsd     fa2, (40+40)(sp)
    fsd     fa3, (44+44)(sp)
    fsd     fa4, (48+48)(sp)
    fsd     fa5, (52+52)(sp)
    fsd     fa6, (56+56)(sp)
    fsd     fa7, (60+60)(sp)
    fsd     ft8, (64+64)(sp)
    fsd     ft9, (68+68)(sp)
    fsd     ft10,(72+72)(sp)
    fsd     ft11,(76+76)(sp)

    la      t0, irq_nested_level
    lw      t1, 0(t0)
    addi    t1, t1, 1
    sw      t1, 0(t0)

    andi    t2, t2, 0x3FF
    mv      a0, t2
    slli    t2, t2, 3

    la      t2, interrupt_entry
    jalr    t2

    csrc    mstatus, 8


    la      t0, irq_nested_level
    lw      t1, 0(t0)
    addi    t1, t1, -1
    sw      t1, 0(t0)

    /* write PLIC_CLAIM and exit interrupt */
    lw      a1, (72+72+160)(sp)
    andi    a0, a1, 0x3FF

    csrr    a2, 0xfc1
    li      a1, 0x00200000
    add     a2, a2, a1
    sw      a0, 4(a2)

    li      t0, MSTATUS_PRV1
    csrs    mstatus, t0

    fld     ft0, (0 +0 )(sp)
    fld     ft1, (4 +4 )(sp)
    fld     ft2, (8 +8 )(sp)
    fld     ft3, (12+12)(sp)
    fld     ft4, (16+16)(sp)
    fld     ft5, (20+20)(sp)
    fld     ft6, (24+24)(sp)
    fld     ft7, (28+28)(sp)
    fld     fa0, (32+32)(sp)
    fld     fa1, (36+36)(sp)
    fld     fa2, (40+40)(sp)
    fld     fa3, (44+44)(sp)
    fld     fa4, (48+48)(sp)
    fld     fa5, (52+52)(sp)
    fld     fa6, (56+56)(sp)
    fld     fa7, (60+60)(sp)
    fld     ft8, (64+64)(sp)
    fld     ft9, (68+68)(sp)
    fld     ft10,(72+72)(sp)
    fld     ft11,(76+76)(sp)

    addi    sp, sp, 160

    ld      t0, (68+68)(sp)
    csrw    mepc, t0
    ld      ra, (0 +0 )(sp)
    ld      t0, (4 +4 )(sp)
    ld      t1, (8 +8 )(sp)
    ld      t2, (12+12)(sp)
    ld      a0, (16+16)(sp)
    ld      a1, (20+20)(sp)
    ld      a2, (24+24)(sp)
    ld      a3, (28+28)(sp)
    ld      a4, (32+32)(sp)
    ld      a5, (36+36)(sp)
    ld      a6, (40+40)(sp)
    ld      a7, (44+44)(sp)
    ld      t3, (48+48)(sp)
    ld      t4, (52+52)(sp)
    ld      t5, (56+56)(sp)
    ld      t6, (60+60)(sp)

    addi    sp, sp, (76+76)
    mret

/****************************************************************************
 * Name: exception_common
 ****************************************************************************/
    .align  6
    .weak   exception_common
    .global exception_common
    .global Default_Handler
    .type   exception_common, %function

Default_Handler:
exception_common:

    addi sp, sp, -XCPTCONTEXT_SIZE

    sd   x1,  REG_X1(sp)   /* ra */
    /* sd   x3,  REG_X3(sp) */   /* gp */
    sd   x4,  REG_X4(sp)   /* tp */
    sd   x5,  REG_X5(sp)   /* t0 */
    sd   x6,  REG_X6(sp)   /* t1 */
    sd   x7,  REG_X7(sp)   /* t2 */
    sd   x8,  REG_X8(sp)   /* s0 */
    sd   x9,  REG_X9(sp)   /* s1 */
    sd   x10, REG_X10(sp)  /* a0 */
    sd   x11, REG_X11(sp)  /* a1 */
    sd   x12, REG_X12(sp)  /* a2 */
    sd   x13, REG_X13(sp)  /* a3 */
    sd   x14, REG_X14(sp)  /* a4 */
    sd   x15, REG_X15(sp)  /* a5 */
    sd   x16, REG_X16(sp)  /* a6 */
    sd   x17, REG_X17(sp)  /* a7 */
    sd   x18, REG_X18(sp)  /* s2 */
    sd   x19, REG_X19(sp)  /* s3 */
    sd   x20, REG_X20(sp)  /* s4 */
    sd   x21, REG_X21(sp)  /* s5 */
    sd   x22, REG_X22(sp)  /* s6 */
    sd   x23, REG_X23(sp)  /* s7 */
    sd   x24, REG_X24(sp)  /* s8 */
    sd   x25, REG_X25(sp)  /* s9 */
    sd   x26, REG_X26(sp)  /* s10 */
    sd   x27, REG_X27(sp)  /* s11 */
    sd   x28, REG_X28(sp)  /* t3 */
    sd   x29, REG_X29(sp)  /* t4 */
    sd   x30, REG_X30(sp)  /* t5 */
    sd   x31, REG_X31(sp)  /* t6 */

    csrr s0, mstatus
    sd   s0, REG_INT_CTX(sp)  /* mstatus */

    addi s0, sp, XCPTCONTEXT_SIZE
    sd   s0, REG_X2(sp)       /* original SP */

    /* Setup arg0(exception cause), arg1(context) */

    csrr a0, mcause           /* exception cause */
    csrr s0, mepc
    sd   s0, REG_EPC(sp)      /* exception PC */

    mv   a1, sp      /* context = sp */

    la   sp, g_trap_sp

    /* Call interrupt handler in C */

    jal  x1, trap_c

    /* If context switch is needed, return a new sp */

    mv   sp, a0
    ld   s0, REG_EPC(sp)     /* restore mepc */
    csrw mepc, s0

    ld   s0, REG_INT_CTX(sp) /* restore mstatus */
    csrw mstatus, s0

    /* ld  x3,  REG_X3(sp) */ /* gp */
    ld  x4,  REG_X4(sp)  /* tp */
    ld  x5,  REG_X5(sp)  /* t0 */
    ld  x6,  REG_X6(sp)  /* t1 */
    ld  x7,  REG_X7(sp)  /* t2 */
    ld  x8,  REG_X8(sp)  /* s0 */
    ld  x9,  REG_X9(sp)  /* s1 */
    ld x10, REG_X10(sp)  /* a0 */
    ld x11, REG_X11(sp)  /* a1 */
    ld x12, REG_X12(sp)  /* a2 */
    ld x13, REG_X13(sp)  /* a3 */
    ld x14, REG_X14(sp)  /* a4 */
    ld x15, REG_X15(sp)  /* a5 */
    ld x16, REG_X16(sp)  /* a6 */
    ld x17, REG_X17(sp)  /* a7 */
    ld x18, REG_X18(sp)  /* s2 */
    ld x19, REG_X19(sp)  /* s3 */
    ld x20, REG_X20(sp)  /* s4 */
    ld x21, REG_X21(sp)  /* s5 */
    ld x22, REG_X22(sp)  /* s6 */
    ld x23, REG_X23(sp)  /* s7 */
    ld x24, REG_X24(sp)  /* s8 */
    ld x25, REG_X25(sp)  /* s9 */
    ld x26, REG_X26(sp)  /* s10 */
    ld x27, REG_X27(sp)  /* s11 */
    ld x28, REG_X28(sp)  /* t3 */
    ld x29, REG_X29(sp)  /* t4 */
    ld x30, REG_X30(sp)  /* t5 */
    ld x31, REG_X31(sp)  /* t6 */

    ld  x1,  REG_X1(sp)  /* ra */

    ld  sp,  REG_X2(sp)  /* restore original sp */

    /* Return from Machine Interrupt */

    mret


/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro  def_irq_handler handler_name
    .weak   \handler_name
    .globl  \handler_name
    .set    \handler_name, Default_Handler
    .endm

    def_irq_handler Stspend_Handler
    def_irq_handler Stspend_Handler_S
    def_irq_handler Mtspend_Handler
    def_irq_handler M_SoftIRQ_ISR
    def_irq_handler CORET_IRQHandler
    def_irq_handler STIM0_IRQHandler
    def_irq_handler STIM1_IRQHandler
    def_irq_handler STIM2_IRQHandler
    def_irq_handler STIM3_IRQHandler
    def_irq_handler TIM0_IRQHandler
    def_irq_handler TIM1_IRQHandler
    def_irq_handler TIM2_IRQHandler
    def_irq_handler TIM3_IRQHandler
    def_irq_handler USART_IRQHandler
    def_irq_handler GPIO0_IRQHandler
    def_irq_handler GPIO1_IRQHandler
    def_irq_handler GPIO2_IRQHandler
    def_irq_handler GPIO3_IRQHandler
    def_irq_handler GPIO4_IRQHandler
    def_irq_handler GPIO5_IRQHandler
    def_irq_handler GPIO6_IRQHandler
    def_irq_handler GPIO7_IRQHandler
    def_irq_handler PAD_IRQHandler
    def_irq_handler HPM_OVF_IRQHandler
