/*
 * File      : context_gcc.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-14     aozima       first implementation for Nios II.
 * 2011-02-20     aozima       fix context&switch bug.
 */

/**
 * @addtogroup NIOS_II
 */
/*@{*/

.text

.set noat

/*
 * rt_base_t rt_hw_interrupt_disable();
 */
.global rt_hw_interrupt_disable
.type rt_hw_interrupt_disable, %function
rt_hw_interrupt_disable:
    rdctl r2, status       /* return status */
    wrctl status, zero     /* disable interrupt */
    ret

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
.global rt_hw_interrupt_enable
.type rt_hw_interrupt_enable, %function
rt_hw_interrupt_enable:
    wrctl status, r4       /* enable interrupt by argument */
    ret

/* void rt_hw_context_switch_interrupt_do(void) */
.global rt_hw_context_switch_interrupt_do
.type rt_hw_context_switch_interrupt_do, %function
rt_hw_context_switch_interrupt_do:
    /* save from thread */
    addi sp,sp,-72

    /* frist save r2,so that save status */
    stw r2,   4(sp)

    /* save status */
    /* when the interrupt happen,the interrupt is enable */
    movi r2, 1
    stw  r2, 68(sp)  /* status */

    stw r3,   8(sp)
    stw r4,  12(sp)

    /* get & save from thread pc */
    ldw r4,%gprel(rt_current_thread_entry)(gp)
    stw r4,   0(sp)  /* thread pc */

    stw r5,  16(sp)
    stw r6,  20(sp)
    stw r7,  24(sp)

    stw r16, 28(sp)
    stw r17, 32(sp)
    stw r18, 36(sp)
    stw r19, 40(sp)
    stw r20, 44(sp)
    stw r21, 48(sp)
    stw r22, 52(sp)
    stw r23, 56(sp)

    stw fp,  60(sp)
    stw ra,  64(sp)

    /* save from thread sp */
    /* rt_interrupt_from_thread = &from_thread->sp */
    ldw r4, %gprel(rt_interrupt_from_thread)(gp)
    /* *r4(from_thread->sp) = sp */
    stw sp, (r4)

    /* clear rt_thread_switch_interrupt_flag */
    /* rt_thread_switch_interrupt_flag = 0 */
    stw zero,%gprel(rt_thread_switch_interrupt_flag)(gp)

    /* load to thread sp */
    /* r4 = rt_interrupt_to_thread(&to_thread->sp) */
    ldw r4, %gprel(rt_interrupt_to_thread)(gp)
    /* sp = to_thread->sp */
    ldw sp, (r4)

    ldw r2,  68(sp)  /* status */
    wrctl estatus, r2

    ldw ea,   0(sp)  /* thread pc */
    ldw r2,   4(sp)
    ldw r3,   8(sp)
    ldw r4,  12(sp)
    ldw r5,  16(sp)
    ldw r6,  20(sp)
    ldw r7,  24(sp)

    ldw r16, 28(sp)
    ldw r17, 32(sp)
    ldw r18, 36(sp)
    ldw r19, 40(sp)
    ldw r20, 44(sp)
    ldw r21, 48(sp)
    ldw r22, 52(sp)
    ldw r23, 56(sp)

    ldw fp,  60(sp)
    ldw ra,  64(sp)

    addi sp, sp, 72

    /* estatus --> status,ea --> pc */
    eret

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
 * r4: from
 * r5: to
 */
.global rt_hw_context_switch
.type rt_hw_context_switch, %function
rt_hw_context_switch:
    /* save from thread */
    addi sp,sp,-72

    /* frist save r2,so that save status */
    stw r2,   4(sp)

    /* save status */
    rdctl r2, status
    stw r2,  68(sp)  /* status */

    stw ra,   0(sp)  /* return from rt_hw_context_switch */
    stw r3,   8(sp)
    stw r4,  12(sp)
    stw r5,  16(sp)
    stw r6,  20(sp)
    stw r7,  24(sp)

    stw r16, 28(sp)
    stw r17, 32(sp)
    stw r18, 36(sp)
    stw r19, 40(sp)
    stw r20, 44(sp)
    stw r21, 48(sp)
    stw r22, 52(sp)
    stw r23, 56(sp)

    stw fp,  60(sp)
    stw ra,  64(sp)

    /* save form thread sp */
    /* from_thread->sp(r4) = sp */
    stw sp, (r4)

    /* update rt_interrupt_from_thread */
    /* rt_interrupt_from_thread = r4(from_thread->sp) */
    stw r4,%gprel(rt_interrupt_from_thread)(gp)

    /* update rt_interrupt_to_thread */
    /* rt_interrupt_to_thread = r5 */
    stw r5,%gprel(rt_interrupt_to_thread)(gp)

    /* get to thread sp */
    /* sp = rt_interrupt_to_thread(r5:to_thread->sp) */
    ldw sp, (r5)

    ldw r2,  68(sp)  /* status */
    wrctl estatus, r2

    ldw ea, 0(sp)    /* thread pc */

    ldw r2,   4(sp)
    ldw r3,   8(sp)
    ldw r4,  12(sp)
    ldw r5,  16(sp)
    ldw r6,  20(sp)
    ldw r7,  24(sp)

    ldw r16, 28(sp)
    ldw r17, 32(sp)
    ldw r18, 36(sp)
    ldw r19, 40(sp)
    ldw r20, 44(sp)
    ldw r21, 48(sp)
    ldw r22, 52(sp)
    ldw r23, 56(sp)

    ldw fp,  60(sp)
    ldw ra,  64(sp)

    addi sp, sp, 72

    /* estatus --> status,ea --> pc */
    eret

/*
 * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to);
 * r4: from
 * r5: to
 */
.global rt_hw_context_switch_interrupt
.type rt_hw_context_switch_interrupt, %function
rt_hw_context_switch_interrupt:
    /* if( rt_thread_switch_interrupt_flag != 0 ) _from_thread_not_change */
    ldw r2,%gprel(rt_thread_switch_interrupt_flag)(gp)
    bne r2,zero,_from_thread_not_change

_from_thread_change:
    /* save ea -> rt_current_thread_entry */
    addi ea,ea,-4
    stw ea,%gprel(rt_current_thread_entry)(gp)

    /* set rt_thread_switch_interrupt_flag to 1 */
    movi r2, 1
    stw r2,%gprel(rt_thread_switch_interrupt_flag)(gp)

    /* update rt_interrupt_from_thread */
    stw r4,%gprel(rt_interrupt_from_thread)(gp)

_from_thread_not_change:
    /* update rt_interrupt_to_thread */
    stw r5,%gprel(rt_interrupt_to_thread)(gp)

    ret

/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 * r4: to
 */
.global rt_hw_context_switch_to
.type rt_hw_context_switch_to, %function
rt_hw_context_switch_to:
    /* save to thread */
    stw r4,%gprel(rt_interrupt_to_thread)(gp)

    /* get sp */
    ldw sp, (r4) // sp = *r4

    ldw r2,  68(sp)  /* status */
    wrctl estatus, r2

    ldw ea, 0(sp)    /* thread entry */

    ldw r2,   4(sp)
    ldw r3,   8(sp)
    ldw r4,  12(sp)
    ldw r5,  16(sp)
    ldw r6,  20(sp)
    ldw r7,  24(sp)

    ldw r16, 28(sp)
    ldw r17, 32(sp)
    ldw r18, 36(sp)
    ldw r19, 40(sp)
    ldw r20, 44(sp)
    ldw r21, 48(sp)
    ldw r22, 52(sp)
    ldw r23, 56(sp)

    ldw fp,  60(sp)
    ldw ra,  64(sp)

    addi sp, sp, 72

    /* estatus --> status,ea --> pc */
    eret

/*@}*/
