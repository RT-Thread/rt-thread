/*
 * File      : context_gcc.S
 * Change Logs:
 * Date           Author       Notes
 * 2010-05-17     swkyer       first version
 * 2010-09-11     bernard      port to Jz4755
 */
#include "../common/mips.inc"
#include "../common/stackframe.h"
#include "stack.h"

    .section ".text", "ax"
    .set noreorder

/*
 * rt_base_t rt_hw_interrupt_disable()
 */
    .globl rt_hw_interrupt_disable
rt_hw_interrupt_disable:
    mfc0    v0, CP0_STATUS
    and     v1, v0, 0xfffffffe
    mtc0    v1, CP0_STATUS
    jr      ra
    nop

/*
 * void rt_hw_interrupt_enable(rt_base_t level)
 */
    .globl rt_hw_interrupt_enable
rt_hw_interrupt_enable:
    mtc0    a0, CP0_STATUS
    jr      ra
    nop

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to)
 * a0 --> from
 * a1 --> to
 */
    .globl rt_hw_context_switch
rt_hw_context_switch:
    mtc0    ra, CP0_EPC
    SAVE_ALL

    sw      sp, 0(a0)       /* store sp in preempted tasks TCB */
    lw      sp, 0(a1)       /* get new task stack pointer */

    RESTORE_ALL_AND_RET

/*
 * void rt_hw_context_switch_to(rt_uint32 to)/*
 * a0 --> to
 */
    .globl rt_hw_context_switch_to
rt_hw_context_switch_to:
    lw      sp, 0(a0)       /* get new task stack pointer */

    RESTORE_ALL_AND_RET

/*
 * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to)/*
 */
    .globl rt_thread_switch_interrupt_flag
    .globl rt_interrupt_from_thread
    .globl rt_interrupt_to_thread
    .globl rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
    la      t0, rt_thread_switch_interrupt_flag
    lw      t1, 0(t0)
    nop
    bnez    t1, _reswitch
    nop
    li      t1, 0x01                       /* set rt_thread_switch_interrupt_flag to 1 */
    sw      t1, 0(t0)
    la      t0, rt_interrupt_from_thread   /* set rt_interrupt_from_thread */
    sw      a0, 0(t0)
_reswitch:
    la      t0, rt_interrupt_to_thread     /* set rt_interrupt_to_thread */
    sw      a1, 0(t0)
    jr      ra
    nop

    .globl system_dump

/*
 * void rt_hw_context_switch_interrupt_do(rt_base_t flag)
 */
    .globl rt_interrupt_enter
    .globl rt_interrupt_leave
    .globl mips_irq_handle
mips_irq_handle:
    SAVE_ALL

    mfc0    t0, CP0_CAUSE
    mfc0    t1, CP0_STATUS
    and     t0, t1

    andi    t0, 0xff00
    beqz    t0, spurious_interrupt
    nop

    /* let k0 keep the current context sp */
    move    k0, sp 
    /* switch to kernel stack */
    li      sp, SYSTEM_STACK

    jal     rt_interrupt_enter
    nop
    jal     rt_interrupt_dispatch
    nop
    jal     rt_interrupt_leave
    nop

    /* switch sp back to thread's context */
    move    sp, k0

    /*
     * if rt_thread_switch_interrupt_flag set, jump to
     * rt_hw_context_switch_interrupt_do and don't return
     */
    la      k0, rt_thread_switch_interrupt_flag
    lw      k1, 0(k0)
    beqz    k1, spurious_interrupt
    nop
    sw      zero, 0(k0)                     /* clear flag */
    nop

    /*
     * switch to the new thread
     */
    la      k0, rt_interrupt_from_thread
    lw      k1, 0(k0)
    nop
    sw      sp, 0(k1)                       /* store sp in preempted tasks's TCB */

    la      k0, rt_interrupt_to_thread
    lw      k1, 0(k0)
    nop
    lw      sp, 0(k1)                       /* get new task's stack pointer */
    j       spurious_interrupt
    nop

spurious_interrupt:
    RESTORE_ALL_AND_RET

    .set reorder
