/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/28     Bernard      The unify RISC-V porting implementation
 * 2018/12/27     Jesven       Add SMP support
 * 2021/02/02     lizhirui     Add userspace support
 */
#define __ASSEMBLY__
#include "cpuport.h"
#include "stackframe.h"

    .global rt_hw_context_switch_to
    .type   rt_hw_context_switch_to, %function
rt_hw_context_switch_to:
    LOAD sp, (a0)

#ifdef RT_USING_SMP
    mv    a0, a1
    call  rt_cpus_lock_status_restore
#endif
    RESTORE_ALL
    mret

    .size   rt_hw_context_switch_to, . - rt_hw_context_switch_to

#ifdef RT_USING_SMP
/*
 * void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to, struct rt_thread *to_thread);
 *
 * a0 --> from
 * a1 --> to
 * a2 --> to_thread
 */
    .global rt_hw_context_switch
    .type   rt_hw_context_switch, %function
rt_hw_context_switch:
    /* set mstatus.mpp */
    csrr t0, mxstatus
    srli t0, t0, 30
    andi t0, t0, 0x3
    slli t0, t0, 11
    csrs mstatus, t0//if enter here,caller must be in system thread
    csrw mepc, ra//return address
    //saved from thread context
    SAVE_ALL

    STORE sp, (a0)

    //restore to thread context
    LOAD sp, (a1)

    mv   a0, a2
    call  rt_cpus_lock_status_restore

    RESTORE_ALL
    mret

    .size   rt_hw_context_switch, . - rt_hw_context_switch

/*
 * void rt_hw_context_switch_interrupt(void *context, rt_ubase_t from, rt_ubase_t to, struct rt_thread *to_thread);
 *
 * a0 --> context
 * a1 --> from
 * a2 --> to
 * a3 --> to_thread
 */
    .global rt_hw_context_switch_interrupt
    .type   rt_hw_context_switch_interrupt, %function
rt_hw_context_switch_interrupt:

    STORE a0, 0(a1)

    LOAD  sp, 0(a2)
    move  a0, a3
    call rt_cpus_lock_status_restore

    RESTORE_ALL
    mret

    .size   rt_hw_context_switch_interrupt, . - rt_hw_context_switch_interrupt
#else
/*
 * void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to);
 *
 * a0 --> from
 * a1 --> to
 */
/*
 * void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to, rt_thread_t from_thread, rt_thread_t to_thread);
 *
 * a0 --> from
 * a1 --> to
 * a2 --> from_thread
 * a3 --> to_thread
 */
    .global rt_hw_context_switch
    .type   rt_hw_context_switch, %function
    .global rt_hw_context_switch_interrupt
    .type   rt_hw_context_switch_interrupt, %function
rt_hw_context_switch:
rt_hw_context_switch_interrupt:
    /* set rt_thread_switch_interrupt_flag to 1 */
    la    t0, rt_thread_switch_interrupt_flag
    LOAD  t2, 0(t0)
    bnez  t2, _reswitch
    li    t1, 1
    STORE t1, 0(t0)

    /* set rt_interrupt_from_thread */
    la    t0, rt_interrupt_from_thread
    STORE a0, 0(t0)

_reswitch:
    /* set rt_interrupt_to_thread */
    la    t0, rt_interrupt_to_thread
    STORE a1, 0(t0)

#if CONFIG_INTC_CLIC || CONFIG_INTC_CLIC_PLIC
    /* trigger the tspend exception (causes context switch) */
    li    t0, 0xE080100C
    lb    t1, (t0)
    li    t2, 0x01
    or    t1, t1, t2
    sb    t1, (t0)

    fence
    nop
    nop
    nop
    nop
    nop

    ret
#else
    /* trigger the tspend exception (causes context switch) */
    li      t0, RISCV_VIC_TSPDR
    li      t2, 0x1
    sw      t2, 0(t0)

__loop:
    lw      t2, 0(t0)
    seqz    t1, t2
#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    csrr    t2, sip
    andi    t2, t2, 0x2
#else
    csrr    t2, mip
    andi    t2, t2, 0x8
#endif
    snez    t3, t2
    add     t2, t3, t1
    beqz    t2, __loop
    ret
#endif

    .size   rt_hw_context_switch, . - rt_hw_context_switch
    .size   rt_hw_context_switch_interrupt, . - rt_hw_context_switch_interrupt
#endif /* RT_USING_SMP */
