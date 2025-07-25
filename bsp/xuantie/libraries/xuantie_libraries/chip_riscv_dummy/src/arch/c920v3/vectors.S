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

.section .stack
    .align  4
    .global g_trapstackbase
    .global g_top_trapstack
g_trapstackbase:
    .space CONFIG_ARCH_INTERRUPTSTACK
g_top_trapstack:

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

#if (!CONFIG_CHECK_FPU_DIRTY) && (!CONFIG_CHECK_VECTOR_DIRTY)
    ld      t0, (72+72)(sp)
    csrw    sstatus, t0
#endif
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

#if (!CONFIG_CHECK_FPU_DIRTY) && (!CONFIG_CHECK_VECTOR_DIRTY)
    ld      t0, (72+72)(sp)
    csrw    mstatus, t0
#endif
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

#if CONFIG_ECC_L1_ENABLE
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

#if (!CONFIG_CHECK_FPU_DIRTY) && (!CONFIG_CHECK_VECTOR_DIRTY)
    ld      t0, (72+72)(sp)
    csrw    mstatus, t0
#endif
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
#endif

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

#if (!CONFIG_CHECK_FPU_DIRTY) && (!CONFIG_CHECK_VECTOR_DIRTY)
    ld      t0, (72+72)(sp)
    csrw    sstatus, t0
#endif
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

#if (!CONFIG_CHECK_FPU_DIRTY) && (!CONFIG_CHECK_VECTOR_DIRTY)
    ld      t0, (72+72)(sp)
    csrw    mstatus, t0
#endif
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
