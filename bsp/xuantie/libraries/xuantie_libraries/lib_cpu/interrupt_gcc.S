/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/02     Bernard      The first version
 * 2018/12/27     Jesven       Add SMP schedule
 * 2021/02/02     lizhirui     Add userspace support
 */
#define __ASSEMBLY__
#include "stackframe.h"

.equ RISCV_MSTATUS_MIE,        (1<<3)       /*machine-level interrupt bit*/

.section      .text.entry
.align 3

#ifdef RT_USING_SMP
    .global Mcoret_Handler
    .type   Mcoret_Handler, %function
Mcoret_Handler:
    SAVE_ALL
    /* switch to interrupt stack */
    move  s0, sp

    /* get cpu id */
    csrr  t0, mhartid

    /* switch interrupt stack of current cpu */
    la    sp, g_base_irqstack
    addi  t1, t0, 1
    li    t2, CONFIG_ARCH_INTERRUPTSTACK
    mul   t1, t1, t2
    add   sp, sp, t1 /* sp = (cpuid + 1) * CONFIG_ARCH_INTERRUPTSTACK + g_base_irqstack */

    call  CORET_IRQHandler

    # /* s0 --> sp */
    mv   sp, s0
    mv   a0, s0
    call rt_scheduler_do_irq_switch

    RESTORE_ALL
    mret

    .size   Mcoret_Handler, . - Mcoret_Handler
#endif

    .global Mtspend_Handler
    .global tspend_handler
    .type   Mtspend_Handler, %function
    .type   tspend_handler, %function
Mtspend_Handler:
tspend_handler:
    SAVE_ALL
#ifdef RT_USING_SMP
    /* switch to interrupt stack */
    move  s0, sp

    /* get cpu id */
    csrr  t0, mhartid

    /* switch interrupt stack of current cpu */
    la    sp, g_base_irqstack
    addi  t1, t0, 1
    li    t2, CONFIG_ARCH_INTERRUPTSTACK
    mul   t1, t1, t2
    add   sp, sp, t1 /* sp = (cpuid + 1) * CONFIG_ARCH_INTERRUPTSTACK + g_base_irqstack */
    call  rt_interrupt_enter
    call  ipi_irq
    call  rt_interrupt_leave

    /* s0 --> sp */
    mv  sp, s0
    mv  a0, s0
    call rt_scheduler_do_irq_switch
#else
    /* get rt_thread_switch_interrupt_flag */
    la    t0, rt_thread_switch_interrupt_flag
    LOAD  t2, 0(t0)
    beqz  t2, tspend_exit       /* tspend already handled */
    /* clear rt_thread_switch_interrupt_flag to 0 */
    STORE zero, 0(t0)

    /* switch thread */
    la    t0, rt_interrupt_from_thread
    LOAD  t1, 0(t0)
    STORE sp, 0(t1)

    la    t0, rt_interrupt_to_thread
    LOAD  t1, 0(t0)
    LOAD  sp, 0(t1)

tspend_exit:
#if CONFIG_INTC_CLIC || CONFIG_INTC_CLIC_PLIC
#else
    /* clear tspend */
    li    t0, RISCV_VIC_TSPDR
    li    t2, 0x0
    sw    t2, 0(t0)
#endif
#endif /* RT_USING_SMP */

    RESTORE_ALL
    mret

    .size   Mtspend_Handler, . - Mtspend_Handler
    .size   tspend_handler, . - tspend_handler

#ifdef  RT_USING_SMP
#define rt_hw_interrupt_disable rt_hw_local_irq_disable
#define rt_hw_interrupt_enable  rt_hw_local_irq_enable
#endif

.global cpu_intrpt_restore
.type   cpu_intrpt_restore, %function
.global rt_hw_interrupt_enable
.type   rt_hw_interrupt_enable, %function
cpu_intrpt_restore:
rt_hw_interrupt_enable:
    csrs mstatus, a0    /* restore to old csr */
    jr ra

.size cpu_intrpt_restore, . - cpu_intrpt_restore
.size rt_hw_interrupt_enable, . - rt_hw_interrupt_enable

.global cpu_intrpt_save
.type   cpu_intrpt_save, %function
.global rt_hw_interrupt_disable
.type   rt_hw_interrupt_disable, %function
cpu_intrpt_save:
rt_hw_interrupt_disable:
    csrrci a0, mstatus, 8  /*  clear MIE */
    jr ra

.size cpu_intrpt_save, . - cpu_intrpt_save
.size rt_hw_interrupt_disable, . - rt_hw_interrupt_disable

.global cpu_is_irq_enable
.type   cpu_is_irq_enable, %function
cpu_is_irq_enable:
    csrr a0, mstatus
    andi a0, a0, RISCV_MSTATUS_MIE
    ret

.size cpu_is_irq_enable, . - cpu_is_irq_enable
