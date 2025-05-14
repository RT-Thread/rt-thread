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

#if __riscv_xlen == 64
    addi    sp, sp, -(76+76)
    store_x t0, (4+4)(sp)
    store_x t1, (8+8)(sp)
    store_x t2, (12+12)(sp)

    csrr    t0, sepc
    store_x t0, (68+68)(sp)
    csrr    t0, sstatus
    store_x t0, (72+72)(sp)

    store_x ra, (0 +0 )(sp)
    store_x a0, (16+16)(sp)
    store_x a1, (20+20)(sp)
    store_x a2, (24+24)(sp)
    store_x a3, (28+28)(sp)
    store_x a4, (32+32)(sp)
    store_x a5, (36+36)(sp)
    store_x a6, (40+40)(sp)
    store_x a7, (44+44)(sp)
    store_x t3, (48+48)(sp)
    store_x t4, (52+52)(sp)
    store_x t5, (56+56)(sp)
    store_x t6, (60+60)(sp)
#else
    addi    sp, sp, -76
    store_x t0, (4)(sp)
    store_x t1, (8)(sp)
    store_x t2, (12)(sp)

    csrr    t0, sepc
    store_x t0, (68)(sp)
    csrr    t0, sstatus
    store_x t0, (72)(sp)

    store_x ra, (0)(sp)
    store_x a0, (16)(sp)
    store_x a1, (20)(sp)
    store_x a2, (24)(sp)
    store_x a3, (28)(sp)
    store_x a4, (32)(sp)
    store_x a5, (36)(sp)
    store_x a6, (40)(sp)
    store_x a7, (44)(sp)
    store_x t3, (48)(sp)
    store_x t4, (52)(sp)
    store_x t5, (56)(sp)
    store_x t6, (60)(sp)
#endif

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY || CONFIG_CHECK_MATRIX_DIRTY
    csrr    t3, sstatus
#endif
    SAVE_FLOAT_REGISTERS
    SAVE_VECTOR_REGISTERS
    SAVE_MATRIX_REGISTERS

    la      t2, CORET_IRQHandler
    jalr    t2

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY || CONFIG_CHECK_MATRIX_DIRTY
    RESTORE_SSTATUS
#endif
    RESTORE_MATRIX_REGISTERS
    RESTORE_VECTOR_REGISTERS
    RESTORE_FLOAT_REGISTERS

#if __riscv_xlen == 64
#if (!CONFIG_CHECK_FPU_DIRTY) && (!CONFIG_CHECK_VECTOR_DIRTY) && (!CONFIG_CHECK_MATRIX_DIRTY)
    load_x  t0, (72+72)(sp)
    csrw    sstatus, t0
#endif
    load_x  t0, (68+68)(sp)
    csrw    sepc, t0

    load_x  ra, (0 +0 )(sp)
    load_x  t0, (4 +4 )(sp)
    load_x  t1, (8 +8 )(sp)
    load_x  t2, (12+12)(sp)
    load_x  a0, (16+16)(sp)
    load_x  a1, (20+20)(sp)
    load_x  a2, (24+24)(sp)
    load_x  a3, (28+28)(sp)
    load_x  a4, (32+32)(sp)
    load_x  a5, (36+36)(sp)
    load_x  a6, (40+40)(sp)
    load_x  a7, (44+44)(sp)
    load_x  t3, (48+48)(sp)
    load_x  t4, (52+52)(sp)
    load_x  t5, (56+56)(sp)
    load_x  t6, (60+60)(sp)
    addi    sp, sp, (76+76)
#else
#if (!CONFIG_CHECK_FPU_DIRTY) && (!CONFIG_CHECK_VECTOR_DIRTY) && (!CONFIG_CHECK_MATRIX_DIRTY)
    load_x  t0, (72)(sp)
    csrw    sstatus, t0
#endif
    load_x  t0, (68)(sp)
    csrw    sepc, t0

    load_x  ra, (0)(sp)
    load_x  t0, (4)(sp)
    load_x  t1, (8)(sp)
    load_x  t2, (12)(sp)
    load_x  a0, (16)(sp)
    load_x  a1, (20)(sp)
    load_x  a2, (24)(sp)
    load_x  a3, (28)(sp)
    load_x  a4, (32)(sp)
    load_x  a5, (36)(sp)
    load_x  a6, (40)(sp)
    load_x  a7, (44)(sp)
    load_x  t3, (48)(sp)
    load_x  t4, (52)(sp)
    load_x  t5, (56)(sp)
    load_x  t6, (60)(sp)
    addi    sp, sp, (76)
#endif

    csrr    sp, sscratch
    sret


    .align  3
    .weak   Mcoret_Handler
    .type   Mcoret_Handler, %function
Mcoret_Handler:
    addi    sp, sp, -16
    store_x t0, (0)(sp)
    store_x t1, (8)(sp)
    csrw    mscratch, sp

    csrr    t0, mhartid
    la      sp, g_base_irqstack
    addi    t1, t0, 1
    li      t0, CONFIG_ARCH_INTERRUPTSTACK
    mul     t1, t1, t0
    add     sp, sp, t1 /* sp = (cpuid + 1) * CONFIG_ARCH_INTERRUPTSTACK + g_base_irqstack */

#if __riscv_xlen == 64
    addi    sp, sp, -(76+76)
    store_x t0, (4+4)(sp)
    store_x t1, (8+8)(sp)
    store_x t2, (12+12)(sp)

    csrr    t0, mepc
    store_x t0, (68+68)(sp)
    csrr    t0, mstatus
    store_x t0, (72+72)(sp)

    store_x ra, (0 +0 )(sp)
    store_x a0, (16+16)(sp)
    store_x a1, (20+20)(sp)
    store_x a2, (24+24)(sp)
    store_x a3, (28+28)(sp)
    store_x a4, (32+32)(sp)
    store_x a5, (36+36)(sp)
    store_x a6, (40+40)(sp)
    store_x a7, (44+44)(sp)
    store_x t3, (48+48)(sp)
    store_x t4, (52+52)(sp)
    store_x t5, (56+56)(sp)
    store_x t6, (60+60)(sp)
#else
    addi    sp, sp, -76
    store_x t0, (4)(sp)
    store_x t1, (8)(sp)
    store_x t2, (12)(sp)

    csrr    t0, mepc
    store_x t0, (68)(sp)
    csrr    t0, mstatus
    store_x t0, (72)(sp)

    store_x ra, (0)(sp)
    store_x a0, (16)(sp)
    store_x a1, (20)(sp)
    store_x a2, (24)(sp)
    store_x a3, (28)(sp)
    store_x a4, (32)(sp)
    store_x a5, (36)(sp)
    store_x a6, (40)(sp)
    store_x a7, (44)(sp)
    store_x t3, (48)(sp)
    store_x t4, (52)(sp)
    store_x t5, (56)(sp)
    store_x t6, (60)(sp)
#endif

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY || CONFIG_CHECK_MATRIX_DIRTY
    csrr    t3, mstatus
#endif
    SAVE_FLOAT_REGISTERS
    SAVE_VECTOR_REGISTERS
    SAVE_MATRIX_REGISTERS

    la      t2, CORET_IRQHandler
    jalr    t2
#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY || CONFIG_CHECK_MATRIX_DIRTY
    RESTORE_MSTATUS
#endif

    RESTORE_MATRIX_REGISTERS
    RESTORE_VECTOR_REGISTERS
    RESTORE_FLOAT_REGISTERS

#if __riscv_xlen == 64
#if (!CONFIG_CHECK_FPU_DIRTY) && (!CONFIG_CHECK_VECTOR_DIRTY) && (!CONFIG_CHECK_MATRIX_DIRTY)
    load_x  t0, (72+72)(sp)
    csrw    mstatus, t0
#endif
    load_x  t0, (68+68)(sp)
    csrw    mepc, t0

    load_x  ra, (0 +0 )(sp)
    load_x  t0, (4 +4 )(sp)
    load_x  t1, (8 +8 )(sp)
    load_x  t2, (12+12)(sp)
    load_x  a0, (16+16)(sp)
    load_x  a1, (20+20)(sp)
    load_x  a2, (24+24)(sp)
    load_x  a3, (28+28)(sp)
    load_x  a4, (32+32)(sp)
    load_x  a5, (36+36)(sp)
    load_x  a6, (40+40)(sp)
    load_x  a7, (44+44)(sp)
    load_x  t3, (48+48)(sp)
    load_x  t4, (52+52)(sp)
    load_x  t5, (56+56)(sp)
    load_x  t6, (60+60)(sp)
    addi    sp, sp, (76+76)
#else
#if (!CONFIG_CHECK_FPU_DIRTY) && (!CONFIG_CHECK_VECTOR_DIRTY) && (!CONFIG_CHECK_MATRIX_DIRTY)
    load_x  t0, (72)(sp)
    csrw    mstatus, t0
#endif
    load_x  t0, (68)(sp)
    csrw    mepc, t0

    load_x  ra, (0)(sp)
    load_x  t0, (4)(sp)
    load_x  t1, (8)(sp)
    load_x  t2, (12)(sp)
    load_x  a0, (16)(sp)
    load_x  a1, (20)(sp)
    load_x  a2, (24)(sp)
    load_x  a3, (28)(sp)
    load_x  a4, (32)(sp)
    load_x  a5, (36)(sp)
    load_x  a6, (40)(sp)
    load_x  a7, (44)(sp)
    load_x  t3, (48)(sp)
    load_x  t4, (52)(sp)
    load_x  t5, (56)(sp)
    load_x  t6, (60)(sp)
    addi    sp, sp, (76)
#endif
    csrr    sp, mscratch

    load_x  t0, (0)(sp)
    load_x  t1, (8)(sp)
    addi    sp, sp, 16
    mret


    .align  3
    .weak   Sirq_Handler
    .type   Sirq_Handler, %function
Sirq_Handler:
    csrw    sscratch, sp
    la      sp, g_top_irqstack

#if __riscv_xlen == 64
    addi    sp, sp, -(76+76)
    store_x t0, (4+4)(sp)
    store_x t1, (8+8)(sp)
    store_x t2, (12+12)(sp)

    csrr    t0, sepc
    store_x t0, (68+68)(sp)
    csrr    t0, sstatus
    store_x t0, (72+72)(sp)

    store_x ra, (0 +0 )(sp)
    store_x a0, (16+16)(sp)
    store_x a1, (20+20)(sp)
    store_x a2, (24+24)(sp)
    store_x a3, (28+28)(sp)
    store_x a4, (32+32)(sp)
    store_x a5, (36+36)(sp)
    store_x a6, (40+40)(sp)
    store_x a7, (44+44)(sp)
    store_x t3, (48+48)(sp)
    store_x t4, (52+52)(sp)
    store_x t5, (56+56)(sp)
    store_x t6, (60+60)(sp)
#else
    addi    sp, sp, -76
    store_x t0, (4)(sp)
    store_x t1, (8)(sp)
    store_x t2, (12)(sp)

    csrr    t0, sepc
    store_x t0, (68)(sp)
    csrr    t0, sstatus
    store_x t0, (72)(sp)

    store_x ra, (0)(sp)
    store_x a0, (16)(sp)
    store_x a1, (20)(sp)
    store_x a2, (24)(sp)
    store_x a3, (28)(sp)
    store_x a4, (32)(sp)
    store_x a5, (36)(sp)
    store_x a6, (40)(sp)
    store_x a7, (44)(sp)
    store_x t3, (48)(sp)
    store_x t4, (52)(sp)
    store_x t5, (56)(sp)
    store_x t6, (60)(sp)
#endif

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY || CONFIG_CHECK_MATRIX_DIRTY
    csrr    t3, sstatus
#endif
    SAVE_FLOAT_REGISTERS
    SAVE_VECTOR_REGISTERS
    SAVE_MATRIX_REGISTERS

    la      t2, do_irq
    jalr    t2
#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY || CONFIG_CHECK_MATRIX_DIRTY
    RESTORE_SSTATUS
#endif
    RESTORE_MATRIX_REGISTERS
    RESTORE_VECTOR_REGISTERS
    RESTORE_FLOAT_REGISTERS

#if __riscv_xlen == 64
#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY || CONFIG_CHECK_MATRIX_DIRTY
    load_x  t0, (72+72)(sp)
    csrw    sstatus, t0
#endif
    load_x  t0, (68+68)(sp)
    csrw    sepc, t0

    load_x  ra, (0 +0 )(sp)
    load_x  t0, (4 +4 )(sp)
    load_x  t1, (8 +8 )(sp)
    load_x  t2, (12+12)(sp)
    load_x  a0, (16+16)(sp)
    load_x  a1, (20+20)(sp)
    load_x  a2, (24+24)(sp)
    load_x  a3, (28+28)(sp)
    load_x  a4, (32+32)(sp)
    load_x  a5, (36+36)(sp)
    load_x  a6, (40+40)(sp)
    load_x  a7, (44+44)(sp)
    load_x  t3, (48+48)(sp)
    load_x  t4, (52+52)(sp)
    load_x  t5, (56+56)(sp)
    load_x  t6, (60+60)(sp)
    addi    sp, sp, (76+76)
#else
#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY || CONFIG_CHECK_MATRIX_DIRTY
    load_x  t0, (72)(sp)
    csrw    sstatus, t0
#endif
    load_x  t0, (68)(sp)
    csrw    sepc, t0

    load_x  ra, (0)(sp)
    load_x  t0, (4)(sp)
    load_x  t1, (8)(sp)
    load_x  t2, (12)(sp)
    load_x  a0, (16)(sp)
    load_x  a1, (20)(sp)
    load_x  a2, (24)(sp)
    load_x  a3, (28)(sp)
    load_x  a4, (32)(sp)
    load_x  a5, (36)(sp)
    load_x  a6, (40)(sp)
    load_x  a7, (44)(sp)
    load_x  t3, (48)(sp)
    load_x  t4, (52)(sp)
    load_x  t5, (56)(sp)
    load_x  t6, (60)(sp)
    addi    sp, sp, (76)
#endif
    csrr    sp, sscratch
    sret

#if CONFIG_ECC_L1_ENABLE
    .align  3
    .weak   ECC_L1_Handler
    .type   ECC_L1_Handler, %function
ECC_L1_Handler:
    addi    sp, sp, -16
    store_x t0, (0)(sp)
    store_x t1, (8)(sp)
    csrw    mscratch, sp

    csrr    t0, mhartid
    la      sp, g_base_irqstack
    addi    t1, t0, 1
    li      t0, CONFIG_ARCH_INTERRUPTSTACK
    mul     t1, t1, t0
    add     sp, sp, t1 /* sp = (cpuid + 1) * CONFIG_ARCH_INTERRUPTSTACK + g_base_irqstack */

#if __riscv_xlen == 64
    addi    sp, sp, -(76+76)
    store_x t0, (4+4)(sp)
    store_x t1, (8+8)(sp)
    store_x t2, (12+12)(sp)

    csrr    t0, mepc
    store_x t0, (68+68)(sp)
    csrr    t0, mstatus
    store_x t0, (72+72)(sp)

    store_x ra, (0 +0 )(sp)
    store_x a0, (16+16)(sp)
    store_x a1, (20+20)(sp)
    store_x a2, (24+24)(sp)
    store_x a3, (28+28)(sp)
    store_x a4, (32+32)(sp)
    store_x a5, (36+36)(sp)
    store_x a6, (40+40)(sp)
    store_x a7, (44+44)(sp)
    store_x t3, (48+48)(sp)
    store_x t4, (52+52)(sp)
    store_x t5, (56+56)(sp)
    store_x t6, (60+60)(sp)
#else
    addi    sp, sp, -76
    store_x t0, (4)(sp)
    store_x t1, (8)(sp)
    store_x t2, (12)(sp)

    csrr    t0, mepc
    store_x t0, (68)(sp)
    csrr    t0, mstatus
    store_x t0, (72)(sp)

    store_x ra, (0)(sp)
    store_x a0, (16)(sp)
    store_x a1, (20)(sp)
    store_x a2, (24)(sp)
    store_x a3, (28)(sp)
    store_x a4, (32)(sp)
    store_x a5, (36)(sp)
    store_x a6, (40)(sp)
    store_x a7, (44)(sp)
    store_x t3, (48)(sp)
    store_x t4, (52)(sp)
    store_x t5, (56)(sp)
    store_x t6, (60)(sp)
#endif

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY || CONFIG_CHECK_MATRIX_DIRTY
    csrr    t3, mstatus
#endif
    SAVE_FLOAT_REGISTERS
    SAVE_VECTOR_REGISTERS
    SAVE_MATRIX_REGISTERS

    la      t2, ECC_L1_IRQHandler
    jalr    t2
#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY || CONFIG_CHECK_MATRIX_DIRTY
    RESTORE_MSTATUS
#endif
    RESTORE_MATRIX_REGISTERS
    RESTORE_VECTOR_REGISTERS
    RESTORE_FLOAT_REGISTERS

#if __riscv_xlen == 64
#if (!CONFIG_CHECK_FPU_DIRTY) && (!CONFIG_CHECK_VECTOR_DIRTY) && (!CONFIG_CHECK_MATRIX_DIRTY)
    load_x  t0, (72+72)(sp)
    csrw    mstatus, t0
#endif
    load_x  t0, (68+68)(sp)
    csrw    mepc, t0

    load_x  ra, (0 +0 )(sp)
    load_x  t0, (4 +4 )(sp)
    load_x  t1, (8 +8 )(sp)
    load_x  t2, (12+12)(sp)
    load_x  a0, (16+16)(sp)
    load_x  a1, (20+20)(sp)
    load_x  a2, (24+24)(sp)
    load_x  a3, (28+28)(sp)
    load_x  a4, (32+32)(sp)
    load_x  a5, (36+36)(sp)
    load_x  a6, (40+40)(sp)
    load_x  a7, (44+44)(sp)
    load_x  t3, (48+48)(sp)
    load_x  t4, (52+52)(sp)
    load_x  t5, (56+56)(sp)
    load_x  t6, (60+60)(sp)
    addi    sp, sp, (76+76)
#else
#if (!CONFIG_CHECK_FPU_DIRTY) && (!CONFIG_CHECK_VECTOR_DIRTY) && (!CONFIG_CHECK_MATRIX_DIRTY)
    load_x  t0, (72)(sp)
    csrw    mstatus, t0
#endif
    load_x  t0, (68)(sp)
    csrw    mepc, t0

    load_x  ra, (0)(sp)
    load_x  t0, (4)(sp)
    load_x  t1, (8)(sp)
    load_x  t2, (12)(sp)
    load_x  a0, (16)(sp)
    load_x  a1, (20)(sp)
    load_x  a2, (24)(sp)
    load_x  a3, (28)(sp)
    load_x  a4, (32)(sp)
    load_x  a5, (36)(sp)
    load_x  a6, (40)(sp)
    load_x  a7, (44)(sp)
    load_x  t3, (48)(sp)
    load_x  t4, (52)(sp)
    load_x  t5, (56)(sp)
    load_x  t6, (60)(sp)
    addi    sp, sp, (76)
#endif
    csrr    sp, mscratch

    load_x  t0, (0)(sp)
    load_x  t1, (8)(sp)
    addi    sp, sp, 16
    mret
#endif

    .align  3
    .weak   Mirq_Handler
    .type   Mirq_Handler, %function
Mirq_Handler:
    addi    sp, sp, -16
    store_x t0, (0)(sp)
    store_x t1, (8)(sp)
#if CONFIG_PROFILING_PERF && CONFIG_PERF_BACKTRACE_USE_FP
    addi    sp, sp, -8
    store_x s0, (sp)
#endif
    csrw    mscratch, sp

    csrr    t0, mhartid
    la      sp, g_base_irqstack
    addi    t1, t0, 1
    li      t0, CONFIG_ARCH_INTERRUPTSTACK
    mul     t1, t1, t0
    add     sp, sp, t1 /* sp = (cpuid + 1) * CONFIG_ARCH_INTERRUPTSTACK + g_base_irqstack */

#if __riscv_xlen == 64
    addi    sp, sp, -(76+76)
    store_x t0, (4+4)(sp)
    store_x t1, (8+8)(sp)
    store_x t2, (12+12)(sp)

    csrr    t0, mepc
    store_x t0, (68+68)(sp)
    csrr    t0, mstatus
    store_x t0, (72+72)(sp)

    store_x ra, (0 +0 )(sp)
    store_x a0, (16+16)(sp)
    store_x a1, (20+20)(sp)
    store_x a2, (24+24)(sp)
    store_x a3, (28+28)(sp)
    store_x a4, (32+32)(sp)
    store_x a5, (36+36)(sp)
    store_x a6, (40+40)(sp)
    store_x a7, (44+44)(sp)
    store_x t3, (48+48)(sp)
    store_x t4, (52+52)(sp)
    store_x t5, (56+56)(sp)
    store_x t6, (60+60)(sp)
#else
    addi    sp, sp, -76
    store_x t0, (4)(sp)
    store_x t1, (8)(sp)
    store_x t2, (12)(sp)

    csrr    t0, mepc
    store_x t0, (68)(sp)
    csrr    t0, mstatus
    store_x t0, (72)(sp)

    store_x ra, (0)(sp)
    store_x a0, (16)(sp)
    store_x a1, (20)(sp)
    store_x a2, (24)(sp)
    store_x a3, (28)(sp)
    store_x a4, (32)(sp)
    store_x a5, (36)(sp)
    store_x a6, (40)(sp)
    store_x a7, (44)(sp)
    store_x t3, (48)(sp)
    store_x t4, (52)(sp)
    store_x t5, (56)(sp)
    store_x t6, (60)(sp)
#endif

#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY || CONFIG_CHECK_MATRIX_DIRTY
    csrr    t3, mstatus
#endif
    SAVE_FLOAT_REGISTERS
    SAVE_VECTOR_REGISTERS
    SAVE_MATRIX_REGISTERS

    la      t2, do_irq
    jalr    t2
_interrupt_return_address:
#if CONFIG_CHECK_FPU_DIRTY || CONFIG_CHECK_VECTOR_DIRTY || CONFIG_CHECK_MATRIX_DIRTY
    RESTORE_MSTATUS
#endif
    RESTORE_MATRIX_REGISTERS
    RESTORE_VECTOR_REGISTERS
    RESTORE_FLOAT_REGISTERS

#if __riscv_xlen == 64
#if (!CONFIG_CHECK_FPU_DIRTY) && (!CONFIG_CHECK_VECTOR_DIRTY) && (!CONFIG_CHECK_MATRIX_DIRTY)
    load_x  t0, (72+72)(sp)
    csrw    mstatus, t0
#endif
    load_x  t0, (68+68)(sp)
    csrw    mepc, t0

    load_x  ra, (0 +0 )(sp)
    load_x  t0, (4 +4 )(sp)
    load_x  t1, (8 +8 )(sp)
    load_x  t2, (12+12)(sp)
    load_x  a0, (16+16)(sp)
    load_x  a1, (20+20)(sp)
    load_x  a2, (24+24)(sp)
    load_x  a3, (28+28)(sp)
    load_x  a4, (32+32)(sp)
    load_x  a5, (36+36)(sp)
    load_x  a6, (40+40)(sp)
    load_x  a7, (44+44)(sp)
    load_x  t3, (48+48)(sp)
    load_x  t4, (52+52)(sp)
    load_x  t5, (56+56)(sp)
    load_x  t6, (60+60)(sp)
    addi    sp, sp, (76+76)
#else
#if (!CONFIG_CHECK_FPU_DIRTY) && (!CONFIG_CHECK_VECTOR_DIRTY) && (!CONFIG_CHECK_MATRIX_DIRTY)
    load_x  t0, (72)(sp)
    csrw    mstatus, t0
#endif
    load_x  t0, (68)(sp)
    csrw    mepc, t0

    load_x  ra, (0)(sp)
    load_x  t0, (4)(sp)
    load_x  t1, (8)(sp)
    load_x  t2, (12)(sp)
    load_x  a0, (16)(sp)
    load_x  a1, (20)(sp)
    load_x  a2, (24)(sp)
    load_x  a3, (28)(sp)
    load_x  a4, (32)(sp)
    load_x  a5, (36)(sp)
    load_x  a6, (40)(sp)
    load_x  a7, (44)(sp)
    load_x  t3, (48)(sp)
    load_x  t4, (52)(sp)
    load_x  t5, (56)(sp)
    load_x  t6, (60)(sp)
    addi    sp, sp, (76)
#endif
    csrr    sp, mscratch

#if CONFIG_PROFILING_PERF && CONFIG_PERF_BACKTRACE_USE_FP
    addi    sp, sp, 8
#endif
    load_x  t0, (0)(sp)
    load_x  t1, (8)(sp)
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

#if __riscv_xlen == 64
    addi    sp, sp, -(140+140)
    store_x x1, ( 0 + 0 )(sp)
    store_x x3, ( 8 + 8 )(sp)
    store_x x4, ( 12+ 12)(sp)
    store_x x5, ( 16+ 16)(sp)
    store_x x6, ( 20+ 20)(sp)
    store_x x7, ( 24+ 24)(sp)
    store_x x8, ( 28+ 28)(sp)
    store_x x9, ( 32+ 32)(sp)
    store_x x10,( 36+ 36)(sp)
    store_x x11,( 40+ 40)(sp)
    store_x x12,( 44+ 44)(sp)
    store_x x13,( 48+ 48)(sp)
    store_x x14,( 52+ 52)(sp)
    store_x x15,( 56+ 56)(sp)
    store_x x16,( 60+ 60)(sp)
    store_x x17,( 64+ 64)(sp)
    store_x x18,( 68+ 68)(sp)
    store_x x19,( 72+ 72)(sp)
    store_x x20,( 76+ 76)(sp)
    store_x x21,( 80+ 80)(sp)
    store_x x22,( 84+ 84)(sp)
    store_x x23,( 88+ 88)(sp)
    store_x x24,( 92+ 92)(sp)
    store_x x25,( 96+ 96)(sp)
    store_x x26,(100+100)(sp)
    store_x x27,(104+104)(sp)
    store_x x28,(108+108)(sp)
    store_x x29,(112+112)(sp)
    store_x x30,(116+116)(sp)
    store_x x31,(120+120)(sp)
    csrr    a0, mepc
    store_x a0, (124+124)(sp)
    csrr    a0, mstatus
    store_x a0, (128+128)(sp)
    csrr    a0, mcause
    store_x a0, (132+132)(sp)
    csrr    a0, mtval
    store_x a0, (136+136)(sp)
    csrr    a0, mscratch
    store_x a0, ( 4 + 4 )(sp)
#else
    addi    sp, sp, -140
    store_x x1, ( 0 )(sp)
    store_x x3, ( 8 )(sp)
    store_x x4, ( 12)(sp)
    store_x x5, ( 16)(sp)
    store_x x6, ( 20)(sp)
    store_x x7, ( 24)(sp)
    store_x x8, ( 28)(sp)
    store_x x9, ( 32)(sp)
    store_x x10,( 36)(sp)
    store_x x11,( 40)(sp)
    store_x x12,( 44)(sp)
    store_x x13,( 48)(sp)
    store_x x14,( 52)(sp)
    store_x x15,( 56)(sp)
    store_x x16,( 60)(sp)
    store_x x17,( 64)(sp)
    store_x x18,( 68)(sp)
    store_x x19,( 72)(sp)
    store_x x20,( 76)(sp)
    store_x x21,( 80)(sp)
    store_x x22,( 84)(sp)
    store_x x23,( 88)(sp)
    store_x x24,( 92)(sp)
    store_x x25,( 96)(sp)
    store_x x26,(100)(sp)
    store_x x27,(104)(sp)
    store_x x28,(108)(sp)
    store_x x29,(112)(sp)
    store_x x30,(116)(sp)
    store_x x31,(120)(sp)
    csrr    a0, mepc
    store_x a0, (124)(sp)
    csrr    a0, mstatus
    store_x a0, (128)(sp)
    csrr    a0, mcause
    store_x a0, (132)(sp)
    csrr    a0, mtval
    store_x a0, (136)(sp)
    csrr    a0, mscratch
    store_x a0, ( 4 )(sp)
#endif

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
