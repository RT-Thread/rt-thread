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
 */

#include "cpuport.h"
#include "encoding.h"
#include "stackframe.h"

  .section      .text.entry
  .align 2
  .global trap_entry
  .extern __stack_cpu0
  .extern get_current_thread_kernel_stack_top
trap_entry:
    //backup sp
    csrrw sp, sscratch, sp
    //load interrupt stack
    la sp, __stack_cpu0
    //backup context
    SAVE_ALL
    
    RESTORE_SYS_GP

#ifdef RT_USING_SMART
    //check syscall
    csrr t0, scause
    li t1, 8//environment call from u-mode
    beq t0, t1, syscall_entry
#endif

    csrr a0, scause
    csrrc a1, stval, zero
    csrr  a2, sepc
    mv    a3, sp

    /* scause, stval, sepc, sp */
    call  handle_trap

    /* need to switch new thread */
    la    s0, rt_thread_switch_interrupt_flag
    lw    s2, 0(s0)
    beqz  s2, spurious_interrupt
    sw    zero, 0(s0)

.global rt_hw_context_switch_interrupt_do
rt_hw_context_switch_interrupt_do:

#ifdef RT_USING_SMART
//swap to thread kernel stack
    csrr t0, sstatus
    andi t0, t0, 0x100
    beqz t0, __restore_sp_from_tcb_interrupt
#endif

__restore_sp_from_sscratch_interrupt:
    csrr t0, sscratch
    j __move_stack_context_interrupt

#ifdef RT_USING_SMART
__restore_sp_from_tcb_interrupt:
    la    s0, rt_interrupt_from_thread
    LOAD  a0, 0(s0)
    jal rt_thread_sp_to_thread
    jal get_thread_kernel_stack_top
    mv t0, a0
#endif

__move_stack_context_interrupt:
    mv t1, sp//src
    mv sp, t0//switch stack
    addi sp, sp, -CTX_REG_NR * REGBYTES
    //copy context
    li s0, CTX_REG_NR//cnt
    mv t2, sp//dst

copy_context_loop_interrupt:
    LOAD t0, 0(t1)
    STORE t0, 0(t2)
    addi s0, s0, -1
    addi t1, t1, 8
    addi t2, t2, 8
    bnez s0, copy_context_loop_interrupt

    la    s0, rt_interrupt_from_thread
    LOAD  s1, 0(s0)
    STORE sp, 0(s1)

    la    s0, rt_interrupt_to_thread
    LOAD  s1, 0(s0)
    LOAD  sp, 0(s1)

    #ifdef RT_USING_SMART
        mv a0, s1
        jal rt_thread_sp_to_thread
        jal lwp_aspace_switch
    #endif

spurious_interrupt:
    RESTORE_ALL
    sret

.global rt_hw_interrupt_enable
rt_hw_interrupt_enable:
    csrs sstatus, a0    /* restore to old csr */
    jr ra

.global rt_hw_interrupt_disable
rt_hw_interrupt_disable:
    csrrci a0, sstatus, 2   /* clear SIE */
    jr ra
