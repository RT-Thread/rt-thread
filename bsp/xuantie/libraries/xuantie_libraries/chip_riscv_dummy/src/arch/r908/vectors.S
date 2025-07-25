 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "riscv_asm_macro.h"

#ifndef CONFIG_NR_CPUS
#define CONFIG_NR_CPUS 1
#endif

.section .stack
    .align  4
    .global g_trapstackbase
    .global g_top_trapstack
g_trapstackbase:
    .space CONFIG_ARCH_INTERRUPTSTACK
g_top_trapstack:

#if CONFIG_INTC_CLIC_PLIC

/* Enable interrupts when returning from the handler */
#define MSTATUS_PRV1 0x1880

#if CONFIG_SUPPORT_IRQ_NESTED
#define IRQ_NESTED_MAX  (6)

.section .bss
.align  3
.global irq_nested_level
irq_nested_level:
    .space 8 * CONFIG_NR_CPUS
irq_nested_level_end:

irq_nested_mcause:
    .space 8 * CONFIG_NR_CPUS * IRQ_NESTED_MAX
irq_nested_mcause_end:
#endif

.text

#if !CONFIG_SUPPORT_IRQ_NESTED
    .align  3
    .weak   Default_IRQHandler
    .type   Default_IRQHandler, %function
Default_IRQHandler:
    addi    sp, sp, -16
    sd      t0, (0)(sp)
    sd      t1, (8)(sp)
#if CONFIG_PROFILING_PERF && CONFIG_PERF_BACKTRACE_USE_FP
    addi    sp, sp, -8
    sd      s0, (sp)
#endif
    csrw    mscratch, sp

    csrr    t0, mhartid
    la      sp, g_base_irqstack
    addi    t1, t0, 1
    li      t0, CONFIG_ARCH_INTERRUPTSTACK
    mul     t1, t1, t0
    add     sp, sp, t1 /* sp = (cpuid + 1) * CONFIG_ARCH_INTERRUPTSTACK + g_base_irqstack */

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    addi    sp, sp, -(76+76)
#else
    addi    sp, sp, -(72+72)
#endif
    sd      t0, (4+4)(sp)
    sd      t1, (8+8)(sp)
    csrr    t0, mepc
    sd      t1, (64+64)(sp)
    sd      t0, (68+68)(sp)
#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    csrr    t0, mstatus
    sd      t0, (72+72)(sp)
#endif
    sd      ra, (0)(sp)
    sd      t2, (12+12)(sp)
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

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    csrr    t3, mstatus
#endif
    SAVE_FLOAT_REGISTERS
    SAVE_VECTOR_REGISTERS

    la      t0, do_irq
    jalr    t0

    csrr    a1, mcause
    andi    a0, a1, 0x3FF
    slli    a0, a0, 2

    /* clic clear pending */
    li      a2, 0x0c011000  /* clic base address */
    add     a2, a2, a0
    lb      a3, 0(a2)
    li      a4, 1
    not     a4, a4
    and     a5, a4, a3
    sb      a5, 0(a2)

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    RESTORE_MSTATUS
#endif
    li      t0, MSTATUS_PRV1
    csrs    mstatus, t0

    RESTORE_VECTOR_REGISTERS
    RESTORE_FLOAT_REGISTERS

    ld      t0, (68+68)(sp)
    csrw    mepc, t0
    ld      ra, (0)(sp)
    ld      t0, (4+4)(sp)
    ld      t1, (8+8)(sp)
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

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    addi    sp, sp, (76+76)
#else
    addi    sp, sp, (72+72)
#endif
    csrr    sp, mscratch
#if CONFIG_PROFILING_PERF && CONFIG_PERF_BACKTRACE_USE_FP
    addi    sp, sp, 8
#endif
    ld      t0, (0)(sp)
    ld      t1, (8)(sp)
    addi    sp, sp, 16
    mret
#else /* CONFIG_SUPPORT_IRQ_NESTED */
    .align  3
    .weak   Default_IRQHandler
    .type   Default_IRQHandler, %function
Default_IRQHandler:
    addi    sp, sp, -(8+8+8+8)
    sd      t0, 0(sp)
    sd      t1, (4+4)(sp)
    sd      t2, (8+8)(sp)
    sd      t3, (12+12)(sp)

    csrr    t3, mhartid

    la      t0, irq_nested_level
    slli    t2, t3, 3    /* mhartid * 8 */
    add     t0, t0, t2
    ld      t1, (t0)
    addi    t1, t1, 1
    sd      t1, (t0)

    li      t0, IRQ_NESTED_MAX
    /* nested too deeply, may be error happens */
    bgt     t1, t0, Default_Handler

    addi    t1, t1, -1
    la      t0, irq_nested_mcause
    li      t2, 8 * IRQ_NESTED_MAX
    mul     t2, t2, t3
    slli    t1, t1, 3
    add     t2, t2, t1
    add     t0, t0, t2

    csrr    t1, mcause
    sd      t1, (t0)

    la      t0, irq_nested_level
    slli    t2, t3, 3    /* mhartid * 8 */
    add     t0, t0, t2
    ld      t1, (t0)
    li      t0, 1
    bgt     t1, t0, .Lnested1

#if CONFIG_PROFILING_PERF && CONFIG_PERF_BACKTRACE_USE_FP
    addi    sp, sp, -16
    sd      s0, (sp)
    csrr    t0, mepc
    sd      t0, 8(sp)
#endif
    csrw    mscratch, sp
    la      sp, g_base_irqstack
    addi    t1, t3, 1
    li      t2, CONFIG_ARCH_INTERRUPTSTACK
    mul     t1, t1, t2
    add     sp, sp, t1 /* sp = (cpuid + 1) * CONFIG_ARCH_INTERRUPTSTACK + g_base_irqstack */

    j       .Lnested2
.Lnested1:
    ld      t0, 0(sp)
    ld      t1, (4+4)(sp)
    ld      t2, (8+8)(sp)
    ld      t3, (12+12)(sp)
    addi    sp, sp, (8+8+8+8)
.Lnested2:
#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    addi    sp, sp, -(76+76)
#else
    addi    sp, sp, -(72+72)
#endif
    sd      t0, (4+4)(sp)
    sd      t1, (8+8)(sp)
    csrr    t0, mepc
    sd      t1, (64+64)(sp)
    sd      t0, (68+68)(sp)
#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    csrr    t0, mstatus
    sd      t0, (72+72)(sp)
#endif
    csrs    mstatus, 8

    sd      ra, 0(sp)
    sd      t2, (12+12)(sp)
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

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    csrr    t3, mstatus
#endif
    SAVE_FLOAT_REGISTERS
    SAVE_VECTOR_REGISTERS

    la      t0, do_irq
    jalr    t0

    csrc    mstatus, 8

    /* get mcause from irq_nested_mcause */
    csrr    t3, mhartid
    la      t0, irq_nested_level
    slli    t2, t3, 3    /* mhartid * 8 */
    add     t0, t0, t2
    ld      t1, (t0)
    addi    t1, t1, -1
    la      t0, irq_nested_mcause
    li      t2, 8 * IRQ_NESTED_MAX
    mul     t2, t2, t3
    slli    t1, t1, 3
    add     t2, t2, t1
    add     t0, t0, t2

    ld      a1, (t0)
    andi    a0, a1, 0x3FF
    slli    a0, a0, 2

    /* clic clear pending */
    li      a2, 0x0c011000  /* clic base address */
    add     a2, a2, a0
    lb      a3, 0(a2)
    li      a4, 1
    not     a4, a4
    and     a5, a4, a3
    sb      a5, 0(a2)

    la      t0, irq_nested_level
    slli    t2, t3, 3    /* mhartid * 8 */
    add     t0, t0, t2
    ld      t1, (t0)
    addi    t1, t1, -1
    sd      t1, (t0)
    bgt     t1, zero, .Lnested3

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    RESTORE_MSTATUS
#endif
    li      t0, MSTATUS_PRV1
    csrs    mstatus, t0
    csrw    mcause, a1

    RESTORE_VECTOR_REGISTERS
    RESTORE_FLOAT_REGISTERS

    ld      t0, (68+68)(sp)
    csrw    mepc, t0
    ld      ra, 0(sp)
    ld      t0, (4+4)(sp)
    ld      t1, (8+8)(sp)
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

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    addi    sp, sp, (76+76)
#else
    addi    sp, sp, (72+72)
#endif
    csrr    sp, mscratch
#if CONFIG_PROFILING_PERF && CONFIG_PERF_BACKTRACE_USE_FP
    addi    sp, sp, 16
#endif
    ld      t0, 0(sp)
    ld      t1, (4+4)(sp)
    ld      t2, (8+8)(sp)
    ld      t3, (12+12)(sp)
    addi    sp, sp, (8+8+8+8)
    mret

.Lnested3:
    /* keep mpil in current mcause & load exception code before */
    addi    t1, t1, -1
    la      t0, irq_nested_mcause
    li      t2, 8 * IRQ_NESTED_MAX
    mul     t2, t2, t3
    slli    t1, t1, 3
    add     t2, t2, t1
    add     t0, t0, t2
    mv      t1, t0

    ld      t0, (t1)
    andi    t0, t0, 0x3FF
    srli    a0, a1, 11
    slli    a0, a0, 11
    or      t0, a0, t0
    csrw    mcause, t0

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    RESTORE_MSTATUS
#endif
    RESTORE_VECTOR_REGISTERS
    RESTORE_FLOAT_REGISTERS

    ld      t0, (68+68)(sp)
    csrw    mepc, t0

    li      t0, MSTATUS_PRV1
    csrs    mstatus, t0

    ld      ra, 0(sp)
    ld      t0, (4+4)(sp)
    ld      t1, (8+8)(sp)
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

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    addi    sp, sp, (76+76)
#else
    addi    sp, sp, (72+72)
#endif
    mret
#endif /* CONFIG_SUPPORT_IRQ_NESTED */

    .align  3
    .weak   Mcoret_Handler
    .type   Mcoret_Handler, %function
Mcoret_Handler:
    j   Default_IRQHandler

/******************************************************************************
 * Functions:
 *     void trap(void);
 * default exception handler
 ******************************************************************************/
    .align  3
    .global trap
    .type   trap, %function
trap:
    csrw    mscratch, sp
    la      sp, g_top_trapstack
    addi    sp, sp, -(140+140)
    sd      x1, ( 0 )(sp)
    sd      x3, ( 8+8)(sp)
    sd      x4, ( 12+12)(sp)
    sd      x5, ( 16+16)(sp)
    sd      x6, ( 20+20)(sp)
    sd      x7, ( 24+24)(sp)
    sd      x8, ( 28+28)(sp)
    sd      x9, ( 32+32)(sp)
    sd      x10,( 36+36)(sp)
    sd      x11,( 40+40)(sp)
    sd      x12,( 44+44)(sp)
    sd      x13,( 48+48)(sp)
    sd      x14,( 52+52)(sp)
    sd      x15,( 56+56)(sp)
    sd      x16,( 60+60)(sp)
    sd      x17,( 64+64)(sp)
    sd      x18,( 68+68)(sp)
    sd      x19,( 72+72)(sp)
    sd      x20,( 76+76)(sp)
    sd      x21,( 80+80)(sp)
    sd      x22,( 84+84)(sp)
    sd      x23,( 88+88)(sp)
    sd      x24,( 92+92)(sp)
    sd      x25,( 96+96)(sp)
    sd      x26,(100+100)(sp)
    sd      x27,(104+104)(sp)
    sd      x28,(108+108)(sp)
    sd      x29,(112+112)(sp)
    sd      x30,(116+116)(sp)
    sd      x31,(120+120)(sp)
    csrr    a0, mepc
    sd      a0, (124+124)(sp)
    csrr    a0, mstatus
    sd      a0, (128+128)(sp)
    csrr    a0, mcause
    sd      a0, (132+132)(sp)
    csrr    a0, mtval
    sd      a0, (136+136)(sp)
    csrr    a0, mscratch
    sd      a0, ( 4+4)(sp)

    mv      a0, sp
    la      a1, exceptionHandler
    jalr    a1


    .align  6
    .weak   Default_Handler
    .type   Default_Handler, %function
Default_Handler:
    j      trap

    .size   Default_Handler, . - Default_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro  def_irq_handler handler_name
    .weak   \handler_name
    .set    \handler_name, Default_Handler
    .endm

    def_irq_handler tspend_handler

#else /* !CONFIG_INTC_CLIC_PLIC */

.text
.global _interrupt_return_address

    .align  3
    .weak   Scoret_Handler
    .type   Scoret_Handler, %function
Scoret_Handler:
    csrw    sscratch, sp
    la      sp, g_top_irqstack

    addi    sp, sp, -(76+76)
    sd      t0, (4+4)(sp)
    sd      t1, (8+8)(sp)
    sd      t2, (12+12)(sp)

    csrr    t0, sepc
    sd      t0, (68+68)(sp)
    csrr    t0, sstatus
    sd      t0, (72+72)(sp)

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

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    csrr    t3, sstatus
#endif
    SAVE_FLOAT_REGISTERS
    SAVE_VECTOR_REGISTERS

    la      t2, CORET_IRQHandler
    jalr    t2

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    RESTORE_SSTATUS
#endif
    RESTORE_VECTOR_REGISTERS
    RESTORE_FLOAT_REGISTERS

    ld      t0, (72+72)(sp)
    csrw    sstatus, t0
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
    csrr    sp, sscratch
    sret


    .align  3
    .weak   Mcoret_Handler
    .type   Mcoret_Handler, %function
Mcoret_Handler:
    addi    sp, sp, -16
    sd      t0, (0)(sp)
    sd      t1, (8)(sp)
    csrw    mscratch, sp

    csrr    t0, mhartid
    la      sp, g_base_irqstack
    addi    t1, t0, 1
    li      t0, CONFIG_ARCH_INTERRUPTSTACK
    mul     t1, t1, t0
    add     sp, sp, t1 /* sp = (cpuid + 1) * CONFIG_ARCH_INTERRUPTSTACK + g_base_irqstack */

    addi    sp, sp, -(76+76)
    sd      t0, (4+4)(sp)
    sd      t1, (8+8)(sp)
    sd      t2, (12+12)(sp)

    csrr    t0, mepc
    sd      t0, (68+68)(sp)
    csrr    t0, mstatus
    sd      t0, (72+72)(sp)

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

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    csrr    t3, mstatus
#endif
    SAVE_FLOAT_REGISTERS
    SAVE_VECTOR_REGISTERS

    la      t2, CORET_IRQHandler
    jalr    t2

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    RESTORE_MSTATUS
#endif
    RESTORE_VECTOR_REGISTERS
    RESTORE_FLOAT_REGISTERS

    ld      t0, (72+72)(sp)
    csrw    mstatus, t0
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
    csrr    sp, mscratch

    ld      t0, (0)(sp)
    ld      t1, (8)(sp)
    addi    sp, sp, 16
    mret

    .align  3
    .weak   Sirq_Handler
    .type   Sirq_Handler, %function
Sirq_Handler:
    csrw    sscratch, sp
    la      sp, g_top_irqstack
    addi    sp, sp, -(76+76)
    sd      t0, (4+4)(sp)
    sd      t1, (8+8)(sp)
    sd      t2, (12+12)(sp)

    csrr    t0, sepc
    sd      t0, (68+68)(sp)
    csrr    t0, sstatus
    sd      t0, (72+72)(sp)

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

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    csrr    t3, sstatus
#endif
    SAVE_FLOAT_REGISTERS
    SAVE_VECTOR_REGISTERS

    la      t2, do_irq
    jalr    t2
#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    RESTORE_SSTATUS
#endif
    RESTORE_VECTOR_REGISTERS
    RESTORE_FLOAT_REGISTERS

    ld      t0, (72+72)(sp)
    csrw    sstatus, t0
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
    csrr    sp, sscratch
    sret


    .align  3
    .weak   Mirq_Handler
    .type   Mirq_Handler, %function
Mirq_Handler:
    addi    sp, sp, -16
    sd      t0, (0)(sp)
    sd      t1, (8)(sp)
#if CONFIG_PROFILING_PERF && CONFIG_PERF_BACKTRACE_USE_FP
    addi    sp, sp, -8
    sd      s0, (sp)
#endif
    csrw    mscratch, sp

    csrr    t0, mhartid
    la      sp, g_base_irqstack
    addi    t1, t0, 1
    li      t0, CONFIG_ARCH_INTERRUPTSTACK
    mul     t1, t1, t0
    add     sp, sp, t1 /* sp = (cpuid + 1) * CONFIG_ARCH_INTERRUPTSTACK + g_base_irqstack */

    addi    sp, sp, -(76+76)
    sd      t0, (4+4)(sp)
    sd      t1, (8+8)(sp)
    sd      t2, (12+12)(sp)

    csrr    t0, mepc
    sd      t0, (68+68)(sp)
    csrr    t0, mstatus
    sd      t0, (72+72)(sp)

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

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    csrr    t3, mstatus
#endif
    SAVE_FLOAT_REGISTERS
    SAVE_VECTOR_REGISTERS

    la      t2, do_irq
    jalr    t2
_interrupt_return_address:
#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    RESTORE_MSTATUS
#endif
    RESTORE_VECTOR_REGISTERS
    RESTORE_FLOAT_REGISTERS

    ld      t0, (72+72)(sp)
    csrw    mstatus, t0
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
    csrr    sp, mscratch

#if CONFIG_PROFILING_PERF && CONFIG_PERF_BACKTRACE_USE_FP
    addi    sp, sp, 8
#endif
    ld      t0, (0)(sp)
    ld      t1, (8)(sp)
    addi    sp, sp, 16
    mret


/******************************************************************************
 * Functions:
 *     void trap(void);
 * default exception handler
 ******************************************************************************/
    .align  3
    .global trap
    .type   trap, %function
trap:
    csrw    mscratch, sp
    la      sp, g_top_trapstack
    addi    sp, sp, -(140+140)
    sd      x1, ( 0 + 0 )(sp)
    sd      x3, ( 8 + 8 )(sp)
    sd      x4, ( 12+ 12)(sp)
    sd      x5, ( 16+ 16)(sp)
    sd      x6, ( 20+ 20)(sp)
    sd      x7, ( 24+ 24)(sp)
    sd      x8, ( 28+ 28)(sp)
    sd      x9, ( 32+ 32)(sp)
    sd      x10,( 36+ 36)(sp)
    sd      x11,( 40+ 40)(sp)
    sd      x12,( 44+ 44)(sp)
    sd      x13,( 48+ 48)(sp)
    sd      x14,( 52+ 52)(sp)
    sd      x15,( 56+ 56)(sp)
    sd      x16,( 60+ 60)(sp)
    sd      x17,( 64+ 64)(sp)
    sd      x18,( 68+ 68)(sp)
    sd      x19,( 72+ 72)(sp)
    sd      x20,( 76+ 76)(sp)
    sd      x21,( 80+ 80)(sp)
    sd      x22,( 84+ 84)(sp)
    sd      x23,( 88+ 88)(sp)
    sd      x24,( 92+ 92)(sp)
    sd      x25,( 96+ 96)(sp)
    sd      x26,(100+100)(sp)
    sd      x27,(104+104)(sp)
    sd      x28,(108+108)(sp)
    sd      x29,(112+112)(sp)
    sd      x30,(116+116)(sp)
    sd      x31,(120+120)(sp)
    csrr    a0, mepc
    sd      a0, (124+124)(sp)
    csrr    a0, mstatus
    sd      a0, (128+128)(sp)
    csrr    a0, mcause
    sd      a0, (132+132)(sp)
    csrr    a0, mtval
    sd      a0, (136+136)(sp)
    csrr    a0, mscratch
    sd      a0, ( 4 + 4 )(sp)

    mv      a0, sp
    la      a1, exceptionHandler
    jalr    a1

    .align  3
    .weak   Default_Handler
    .type   Default_Handler, %function
Default_Handler:
    j       trap

    .size   Default_Handler, . - Default_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro  def_irq_handler handler_name
    .weak   \handler_name
    .set    \handler_name, Default_Handler
    .endm

    def_irq_handler Stspend_Handler
    def_irq_handler Mtspend_Handler
    def_irq_handler CORET_IRQHandler
#endif

#if CONFIG_ECC_L1_ENABLE || CONFIG_ECC_ITCM_ENABLE || CONFIG_ECC_DTCM_ENABLE
.text
    .align  3
    .weak   ECC_L1_Handler
    .type   ECC_L1_Handler, %function
ECC_L1_Handler:
    addi    sp, sp, -16
    sd      t0, (0)(sp)
    sd      t1, (8)(sp)
    csrw    mscratch, sp

    csrr    t0, mhartid
    la      sp, g_base_irqstack
    addi    t1, t0, 1
    li      t0, CONFIG_ARCH_INTERRUPTSTACK
    mul     t1, t1, t0
    add     sp, sp, t1 /* sp = (cpuid + 1) * CONFIG_ARCH_INTERRUPTSTACK + g_base_irqstack */

    addi    sp, sp, -(76+76)
    sd      t0, (4+4)(sp)
    sd      t1, (8+8)(sp)
    sd      t2, (12+12)(sp)

    csrr    t0, mepc
    sd      t0, (68+68)(sp)
    csrr    t0, mstatus
    sd      t0, (72+72)(sp)

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

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    csrr    t3, mstatus
#endif
    SAVE_FLOAT_REGISTERS
    SAVE_VECTOR_REGISTERS

    la      t2, ECC_L1_IRQHandler
    jalr    t2

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY
    RESTORE_MSTATUS
#endif
    RESTORE_VECTOR_REGISTERS
    RESTORE_FLOAT_REGISTERS

    ld      t0, (72+72)(sp)
    csrw    mstatus, t0
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
    csrr    sp, mscratch

    ld      t0, (0)(sp)
    ld      t1, (8)(sp)
    addi    sp, sp, 16
    mret

    .size   ECC_L1_Handler, . - ECC_L1_Handler
#endif /* CONFIG_INTC_CLIC_PLIC */
