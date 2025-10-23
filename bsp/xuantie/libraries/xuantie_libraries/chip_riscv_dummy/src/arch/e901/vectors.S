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

#define RISCV_MCAUSE_IRQ_POS 31
#define MSTATUS_IEN 8

.section .stack, "aw", @nobits
    .align  2
    .global g_trapstackbase
    .global g_top_trapstack
g_trapstackbase:
    .space CONFIG_ARCH_INTERRUPTSTACK
g_top_trapstack:

#if CONFIG_SUPPORT_IRQ_NESTED
#define IRQ_NESTED_MAX  (6)
.section .bss
    .align 2
    irq_nested_level:
    .long 0

    irq_nested_mcause:
    .long 0, 0, 0, 0, 0, 0
#endif

/* for interrupt tail-chaining debug */
#if CONFIG_DEBUG_TAIL_CHAINING
    .global g_irq_tailchain_loops
g_irq_tailchain_loops:
    .long 0
#endif

.text

#if !CONFIG_SUPPORT_IRQ_NESTED
    .align  2
    .weak   Default_IRQHandler
    .type   Default_IRQHandler, %function
Default_IRQHandler:
#if CONFIG_PROFILING_PERF && CONFIG_PERF_BACKTRACE_USE_FP
    addi    sp, sp, -4
    sw      s0, (sp)
#endif
    csrw    mscratch, sp
    la      sp, g_top_irqstack
    addi    sp, sp, -52
    sw      t0, 4(sp)
    sw      t1, 8(sp)
    sw      t2, 12(sp)
    csrr    t0, mepc
    csrr    t1, mcause
    csrr    t2, mstatus
    sw      t1, 40(sp)
    sw      t0, 44(sp)
    sw      t2, 48(sp)

    sw      ra, 0(sp)
    sw      a0, 16(sp)
    sw      a1, 20(sp)
    sw      a2, 24(sp)
    sw      a3, 28(sp)
    sw      a4, 32(sp)
    sw      a5, 36(sp)

    la      t0, do_irq
    jalr    t0

    lw      a1, 40(sp)
    andi    a0, a1, 0x3FF
    slli    a0, a0, 2

    /* clear pending */
    li      a2, 0xE0801000
    add     a2, a2, a0
    lb      a3, 0(a2)
    li      a4, 1
    not     a4, a4
    and     a5, a4, a3
    sb      a5, 0(a2)

    csrw    mcause, a1

    lw      t0, 44(sp)
    lw      t1, 48(sp)
    csrw    mepc, t0
    csrw    mstatus, t1
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

    addi    sp, sp, 52
    csrr    sp, mscratch

#if CONFIG_PROFILING_PERF && CONFIG_PERF_BACKTRACE_USE_FP
    addi    sp, sp, 4
#endif

    mret
#else
    .align  2
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

    li      t0, IRQ_NESTED_MAX
	/* nested too deeply, may be error happens */
    bgt     t1, t0, Default_Handler

    addi    t1, t1, -1
    la      t0, irq_nested_mcause
    slli    t1, t1, 2
    add     t0, t0, t1
    csrr    t1, mcause
    sw      t1, (t0)

    la      t0, irq_nested_level
    lw      t1, (t0)
    li      t0, 1
    bgt     t1, t0, .Lnested1

#if CONFIG_PROFILING_PERF && CONFIG_PERF_BACKTRACE_USE_FP
    addi    sp, sp, -8
    sw      s0, (sp)
    csrr    t0, mepc
    sw      t0, 4(sp)
#endif

    csrw    mscratch, sp
    la      sp, g_top_irqstack
    j       .Lnested2
.Lnested1:
    lw      t0, 0(sp)
    lw      t1, 4(sp)
    addi    sp, sp, 8
.Lnested2:
    addi    sp, sp, -52
    sw      t0, 4(sp)
    sw      t1, 8(sp)
    sw      t2, 12(sp)
    csrr    t0, mepc
    csrr    t1, mcause
    csrr    t2, mstatus
    sw      t1, 40(sp)
    sw      t0, 44(sp)
    sw      t2, 48(sp)

    csrs    mstatus, 8

    sw      ra, 0(sp)
    sw      a0, 16(sp)
    sw      a1, 20(sp)
    sw      a2, 24(sp)
    sw      a3, 28(sp)
    sw      a4, 32(sp)
    sw      a5, 36(sp)

    la      t0, do_irq
    jalr    t0

    csrc    mstatus, 8

    lw      a1, 40(sp)
    andi    a0, a1, 0x3FF
    slli    a0, a0, 2

    /* clear pending */
    li      a2, 0xE0801000
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

    csrw    mcause, a1

    lw      t0, 44(sp)
    lw      t1, 48(sp)
    csrw    mepc, t0
    csrw    mstatus, t1
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

    addi    sp, sp, 52
    csrr    sp, mscratch
#if CONFIG_PROFILING_PERF && CONFIG_PERF_BACKTRACE_USE_FP
    addi    sp, sp, 8
#endif
    lw      t0, 0(sp)
    lw      t1, 4(sp)
    addi    sp, sp, 8
    mret

.Lnested3:
    /* keep mpil in current mcause & load exception code before */
    addi    t1, t1, -1
    la      t0, irq_nested_mcause
    slli    t1, t1, 2
    add     t1, t0, t1
    lw      t0, (t1)
    andi    t0, t0, 0x3FF
    andi    a0, a1, 0xFFFFFC00
    or      t0, a0, t0
    csrw    mcause, t0
    lw      t0, 44(sp)
    lw      t1, 48(sp)
    csrw    mepc, t0
    csrw    mstatus, t1

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

    addi    sp, sp, 52
    mret
#endif

    .size   Default_IRQHandler, . - Default_IRQHandler

/******************************************************************************
 * Functions:
 *     void trap(void);
 * default exception handler
 ******************************************************************************/
    .align  2
    .global trap
    .type   trap, %function
trap:
    csrw    mscratch, sp
    la      sp, g_top_trapstack
    addi    sp, sp, -76
    sw      x1, (0 )(sp)
    sw      x3, (8 )(sp)
    sw      x4, (12)(sp)
    sw      x5, (16)(sp)
    sw      x6, (20)(sp)
    sw      x7, (24)(sp)
    sw      x8, (28)(sp)
    sw      x9, (32)(sp)
    sw      x10,(36)(sp)
    sw      x11,(40)(sp)
    sw      x12,(44)(sp)
    sw      x13,(48)(sp)
    sw      x14,(52)(sp)
    sw      x15,(56)(sp)
    csrr    a0, mepc
    sw      a0, (60)(sp)
    csrr    a0, mstatus
    sw      a0, (64)(sp)
    csrr    a0, mcause
    sw      a0, (68)(sp)
    csrr    a0, mtval
    sw      a0, (72)(sp)
    csrr    a0, mscratch
    sw      a0, (4 )(sp)

    mv      a0, sp
    la      a1, exceptionHandler
    jalr    a1

    .size   trap, . - trap

    .align  6
    .weak   Default_Handler
    .type   Default_Handler, %function
Default_Handler:
    /* Check for nmi */
    addi    sp, sp, -8
    sw      t0, 0x0(sp)
    sw      t1, 0x4(sp)
    csrr    t0, mcause
#if (CONFIG_SUPPORT_NON_VECTOR_IRQ) && (!CONFIG_SUPPORT_IRQ_NESTED)
    srli    t1, t0, RISCV_MCAUSE_IRQ_POS
    bnez    t1, is_interrupt
#endif
    andi    t0, t0, 0x3FF
    li      t1, 24
    beq     t0, t1, .NMI_Handler
    lw      t0, 0x0(sp)
    lw      t1, 0x4(sp)
    addi    sp, sp, 8
    j      trap
#if (CONFIG_SUPPORT_NON_VECTOR_IRQ) && (!CONFIG_SUPPORT_IRQ_NESTED)
is_interrupt:
    lw      t0, 0x0(sp)
    lw      t1, 0x4(sp)
    addi    sp, sp, 8
    csrw    mscratch, sp
    la      sp, g_top_irqstack
    addi    sp, sp, -52
    sw      t0, 4(sp)
    sw      t1, 8(sp)
    sw      t2, 12(sp)
    csrr    t0, mepc
    csrr    t1, mcause
    csrr    t2, mstatus
    sw      t1, 40(sp)
    sw      t0, 44(sp)
    sw      t2, 48(sp)

    sw      ra, 0(sp)
    sw      a0, 16(sp)
    sw      a1, 20(sp)
    sw      a2, 24(sp)
    sw      a3, 28(sp)
    sw      a4, 32(sp)
    sw      a5, 36(sp)

#if CONFIG_DEBUG_TAIL_CHAINING
    li       t2, 0
    la       t1, g_irq_tailchain_loops
    sw       t2, 0(t1)
#endif

    csrrsi   t0, mnxti, MSTATUS_IEN
    beqz     t0, irq_done

irq_loop:
#if CONFIG_DEBUG_TAIL_CHAINING
    la       t2, g_irq_tailchain_loops
    lw       t1, 0(t2)
    addi     t1, t1, 1
    sw       t1, 0(t2)
#endif
    lw       t1, 0(t0)
    jalr     t1
    csrrsi   t0, mnxti, MSTATUS_IEN
    bnez     t0, irq_loop

#if CONFIG_DEBUG_TAIL_CHAINING
    li       t2, 0
    la       a1, g_irq_tailchain_loops
    sw       t2, 0(a1)
#endif

irq_done:
    lw      t0, 40(sp)
    lw      t1, 44(sp)
    lw      t2, 48(sp)
    csrw    mcause, t0
    csrw    mepc, t1
    csrw    mstatus, t2

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

    addi    sp, sp, 52
    csrr    sp, mscratch
    mret
#endif /* (CONFIG_SUPPORT_NON_VECTOR_IRQ) && (!CONFIG_SUPPORT_IRQ_NESTED) */
.NMI_Handler:
    /* mscratch may be used before */
    addi    sp, sp, -4
    csrr    t0, mscratch
    sw      t0, 0x0(sp)

    csrw    mscratch, sp
    la      sp, g_top_trapstack
    addi    sp, sp, -52
    sw      t0, 4(sp)
    sw      t1, 8(sp)
    sw      t2, 12(sp)
    csrr    t0, mepc
    csrr    t1, mcause
    csrr    t2, mstatus
    sw      t1, 40(sp)
    sw      t0, 44(sp)
    sw      t2, 48(sp)

    sw      ra, 0(sp)
    sw      a0, 16(sp)
    sw      a1, 20(sp)
    sw      a2, 24(sp)
    sw      a3, 28(sp)
    sw      a4, 32(sp)
    sw      a5, 36(sp)

    la      t0, handle_nmi_exception
    jalr    t0

    lw      a1, 40(sp)
    andi    a0, a1, 0x3FF
    slli    a0, a0, 2

    /* clear pending */
    li      a2, 0xE0801000
    add     a2, a2, a0
    lb      a3, 0(a2)
    li      a4, 1
    not     a4, a4
    and     a5, a4, a3
    sb      a5, 0(a2)

    csrw    mcause, a1

    lw      t0, 44(sp)
    lw      t1, 48(sp)
    csrw    mepc, t0
    csrw    mstatus, t1
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

    addi    sp, sp, 52
    csrr    sp, mscratch

    /* restore mscratch */
    lw      t0, 0x0(sp)
    csrw    mscratch, t0
    addi    sp, sp, 4

    lw      t0, 0x0(sp)
    lw      t1, 0x4(sp)
    addi    sp, sp, 8

    mret

    .size   Default_Handler, . - Default_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro  def_irq_handler handler_name
    .weak   \handler_name
    .set    \handler_name, Default_Handler
    .endm

    def_irq_handler tspend_handler
