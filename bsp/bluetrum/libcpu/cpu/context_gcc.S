/*
 * Copyright (c) 2020-2020, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/11/18     greedyhao    The first version.
 */

#include "ab32vg1.h"

.global  rt_interrupt_from_thread
.global  rt_interrupt_to_thread
.global  rt_cur_thread_sp
.global  rt_thread_switch_interrupt_flag
.global  rt_interrupt_nest

/*
 * rt_base_t rt_hw_interrupt_disable();
 * a0 -> return
 */
    .global rt_hw_interrupt_disable
rt_hw_interrupt_disable:
    lw      a5, PICCON(zero)
    mv      a0, a5
    andi    a5, a5, -2
    sw      a5, PICCON(zero)
    ret

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 * a0 -> level
 */
    .global rt_hw_interrupt_enable
rt_hw_interrupt_enable:
    andi    a0, a0, 1
    beqz    a0,enable_int_ret
    lw      a5, PICCON(zero)
    ori     a5, a5, 1
    sw      a5,PICCON(zero)
enable_int_ret:
    ret

/* Macro for saving task context */
.macro save_context
    addi    sp, sp, -124

    /* Save Context */
    sw      x1, 0(sp)
    sw      x4, 4(sp)
    sw      x5, 8(sp)
    sw      x6, 12(sp)
    sw      x7, 16(sp)
    sw      x8, 20(sp)
    sw      x9, 24(sp)
    sw      x10, 28(sp)
    sw      x11, 32(sp)
    sw      x12, 36(sp)
    sw      x13, 40(sp)
    sw      x14, 44(sp)
    sw      x15, 48(sp)
    sw      x16, 52(sp)
    sw      x17, 56(sp)
    sw      x18, 60(sp)
    sw      x19, 64(sp)
    sw      x20, 68(sp)
    sw      x21, 72(sp)
    sw      x22, 76(sp)
    sw      x23, 80(sp)
    sw      x24, 84(sp)
    sw      x25, 88(sp)
    sw      x26, 92(sp)
    sw      x27, 96(sp)
    sw      x28, 100(sp)
    sw      x29, 104(sp)
    sw      x30, 108(sp)
    sw      x31, 112(sp)

    lw      a5, EPC(zero)                                       //Saves current program counter (EPC) as task program counter
    sw      a5, 116(sp)
    lw      a5, EPICCON(zero)
    sw      a5, 120(sp)

    sw      sp, rt_cur_thread_sp, a4                            //store sp in preempted tasks tcb
    .endm


/* Macro for restoring task context */
.macro restore_context

    la      a5, rt_cur_thread_sp
    lw      sp, 0(a5)                                           //get new task stack pointer

    /* Load task program counter  EPC*/
    lw      a5, 116(sp)
    sw      a5, EPC(zero)
    lw      a5, 120(sp)
    sw      a5, EPICCON(zero)

    /* Restore registers,
       Skip global pointer because that does not change */
    lw      x1, 0(sp)
    lw      x4, 4(sp)
    lw      x5, 8(sp)
    lw      x6, 12(sp)
    lw      x7, 16(sp)
    lw      x8, 20(sp)
    lw      x9, 24(sp)
    lw      x10, 28(sp)
    lw      x11, 32(sp)
    lw      x12, 36(sp)
    lw      x13, 40(sp)
    lw      x14, 44(sp)
    lw      x15, 48(sp)
    lw      x16, 52(sp)
    lw      x17, 56(sp)
    lw      x18, 60(sp)
    lw      x19, 64(sp)
    lw      x20, 68(sp)
    lw      x21, 72(sp)
    lw      x22, 76(sp)
    lw      x23, 80(sp)
    lw      x24, 84(sp)
    lw      x25, 88(sp)
    lw      x26, 92(sp)
    lw      x27, 96(sp)
    lw      x28, 100(sp)
    lw      x29, 104(sp)
    lw      x30, 108(sp)
    lw      x31, 112(sp)

    addi    sp, sp, 124
    mret
    .endm

/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 * r0 --> to
 */
    .globl rt_hw_context_switch_to
rt_hw_context_switch_to:
    sw      zero, rt_interrupt_from_thread, a4                      /*set from thread to 0*/
    sw      a0, rt_interrupt_to_thread, a4                          /*set rt_interrupt_to_thread*/

    sb      zero, rt_interrupt_nest, a4                             /*rt_interrupt_nest = 0*/

    li      a5, 1
    sw      a5, rt_thread_switch_interrupt_flag, a4                 // rt_thread_switch_interrupt_flag = 1;

    SWINT                                                           /*kick soft interrupt*/
    lw      a5, PICCON(zero)                                        /*enable interrupt*/
    ori     a5, a5, 1
    sw      a5, PICCON(zero)
    ret

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
 * a0 --> from
 * a1 --> to
 */
    .globl rt_hw_context_switch
rt_hw_context_switch:
    sw      a0, rt_interrupt_from_thread, a4                        /*set rt_interrupt_from_thread*/
    sw      a1, rt_interrupt_to_thread, a4                          /*set rt_interrupt_to_thread*/
    li      a5, 1
    sw      a5, rt_thread_switch_interrupt_flag, a4                 /*rt_thread_switch_interrupt_flag = 1*/
    SWINT                                                           /*kick soft interrupt*/
    ret

 /*
 * void rt_switch_to_thread(void);
 * r0 --> to
 */
    .globl rt_switch_to_thread
rt_switch_to_thread:
    lw     a0, rt_interrupt_from_thread
    lw     a5, rt_cur_thread_sp
    sw     a5, 0(a0)

    lw     a0, rt_interrupt_to_thread
    lw     a5, 0(a0)
    sw     a5, rt_cur_thread_sp, a4
    ret

/*
 * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to);
 * a0 --> from
 * a1 --> to
 */
    .global rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
    lw      a5, rt_thread_switch_interrupt_flag
    bnez    a5, _reswitch
    li      a5, 0x01
    sw      a5, rt_thread_switch_interrupt_flag, a4
    sw      a0, rt_interrupt_from_thread, a4                      	/*set rt_interrupt_from_thread*/
_reswitch:
    sw      a1, rt_interrupt_to_thread, a4                        	/*set rt_interrupt_to_thread*/
    ret

    //软中断服务
    .global rt_soft_isr
rt_soft_isr:
    li      a5, 0x4                                       			// PICPND = BIT(IRQ_SW_VECTOR); 清软中断Pending
    sw      a5, PICPND(zero)
    ret

    .globl low_prio_irq
low_prio_irq:
    save_context

    lw      a5, rt_interrupt_nest
    bnez    a5, _low_prio_irq_exit

    lw      a5, cpu_irq_comm_hook
    jalr    a5

    lw      a5, rt_thread_switch_interrupt_flag
    beqz    a5, _low_prio_irq_exit                                  // if (rt_thread_switch_interrupt_flag)
    jal     rt_switch_to_thread
    sw      zero, rt_thread_switch_interrupt_flag, a4               // rt_thread_switch_interrupt_flag = 0;

    _low_prio_irq_exit:
    restore_context

