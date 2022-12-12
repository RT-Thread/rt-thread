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
 * 2021/12/24     JasonHu      Add user setting save/restore
 * 2022/10/22     WangXiaoyao  Support kernel mode RVV;
 *                             Rewrite trap handling routine
 */

#include "cpuport.h"
#include "encoding.h"
#include "stackframe.h"

    .align 2
    .global trap_entry
    .global debug_check_sp
trap_entry:
    // distingush exception from kernel or user
    csrrw   sp, sscratch, sp
    bnez    sp, _save_context

    // BE REALLY careful with sscratch,
    // if it's wrong, we could looping here forever
    // or accessing random memory and seeing things totally
    // messy after a long time and don't even know why
_from_kernel:
    csrr    sp, sscratch
    j _save_context

_save_context:
    SAVE_ALL
    // clear sscratch to say 'now in kernel mode'
    csrw    sscratch, zero

    RESTORE_SYS_GP

    // now we are ready to enter interrupt / excepiton handler
_distinguish_syscall:
    csrr    t0, scause
#ifdef RT_USING_SMART
    // TODO swap 8 with config macro name
    li      t1, 8
    beq     t0, t1, syscall_entry
    // syscall never return here
#endif

_handle_interrupt_and_exception:
    mv      a0, t0
    csrrc   a1, stval, zero
    csrr    a2, sepc
    // sp as exception frame pointer
    mv      a3, sp
    call    handle_trap

_interrupt_exit:
    la      s0, rt_thread_switch_interrupt_flag
    lw      s2, 0(s0)
    beqz    s2, _resume_execution
    sw      zero, 0(s0)

_context_switch:
    la      t0, rt_interrupt_from_thread
    LOAD    a0, 0(t0)
    la      t0, rt_interrupt_to_thread
    LOAD    a1, 0(t0)
    jal     rt_hw_context_switch

_resume_execution:
#ifdef RT_USING_SMART
    LOAD    t0, FRAME_OFF_SSTATUS(sp)
    andi    t0, t0, SSTATUS_SPP
    beqz    t0, arch_ret_to_user
#endif

_resume_kernel:
    RESTORE_ALL
    csrw    sscratch, zero
    sret

.global rt_hw_interrupt_enable
rt_hw_interrupt_enable:
    csrs sstatus, a0    /* restore to old csr */
    jr ra

.global rt_hw_interrupt_disable
rt_hw_interrupt_disable:
    csrrci a0, sstatus, 2   /* clear SIE */
    jr ra
