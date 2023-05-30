/*
 * File      : stack.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2021, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-14     Fred         first implementation for
 */

#include <rtthread.h>

/**
 * @addtogroup PowerPC
 */
/*@{*/

/**
 * This function will initialize thread stack
 *
 * @param tentry the entry of thread
 * @param parameter the parameter of entry
 * @param stack_addr the beginning stack address
 * @param texit the function will be called when thread exit
 *
 * @return stack address
 */
rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter,
    rt_uint8_t *stack_addr, void *texit)
{
    unsigned long *stk;
    rt_uint32_t msr;

    __asm__ __volatile__("mfmsr %0\n" : "=r" (msr));
    msr |= 0x00028000;

    stk      = (unsigned long *)stack_addr;
    --stk;
    *(--stk) = msr;                 /* srr0: machine status register */
    *(--stk) = (rt_uint32_t)tentry; /* srr1: entry point */
    *(--stk) = (rt_uint32_t)texit;  /* lr: link register */
    *(--stk) = 0x0F0F0F0F;          /* ctr: counter register */
    *(--stk) = 0x0F0F0F0F;          /* xer: fixed-point exception register */
    *(--stk) = 0x0F0F0F0F;          /* cr : condition register */
    *(--stk) = 0x00;                /* usprg0 */

    *(--stk) = 0x31;            /* r31 */
    *(--stk) = 0x30;            /* r30 */
    *(--stk) = 0x29;            /* r29 */
    *(--stk) = 0x28;            /* r28 */
    *(--stk) = 0x27;            /* r27 */
    *(--stk) = 0x26;            /* r26 */
    *(--stk) = 0x25;            /* r25 */
    *(--stk) = 0x24;            /* r24 */
    *(--stk) = 0x23;            /* r23 */
    *(--stk) = 0x22;            /* r22 */
    *(--stk) = 0x21;            /* r21 */
    *(--stk) = 0x20;            /* r20 */
    *(--stk) = 0x19;            /* r19 */
    *(--stk) = 0x18;            /* r18 */
    *(--stk) = 0x17;            /* r17 */
    *(--stk) = 0x16;            /* r16 */
    *(--stk) = 0x15;            /* r15 */
    *(--stk) = 0x14;            /* r14 */
    *(--stk) = 0x13;            /* r13: thread id */
    *(--stk) = 0x12;            /* r12 */
    *(--stk) = 0x11;            /* r11 */
    *(--stk) = 0x10;            /* r10 */
    *(--stk) = 0x09;            /* r09 */
    *(--stk) = 0x08;            /* r08 */
    *(--stk) = 0x07;            /* r07 */
    *(--stk) = 0x06;            /* r06 */
    *(--stk) = 0x05;            /* r05 */
    *(--stk) = 0x04;            /* r04 */
    *(--stk) = (rt_uint32_t)parameter;  /* r03: parameter and return  */
    *(--stk) = 0x02;            /* r02: toc */
                                /* r01: sp */
    *(--stk) = 0x0;             /* r00 */

    /* return task's current stack address */
    return (rt_uint8_t *)stk;
}

/*@}*/
