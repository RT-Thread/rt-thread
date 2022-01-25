/*
 * File      : stack.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-17     nl1031       first implementation for MicroBlaze.
 *
 */
#include <rtthread.h>
extern   void  *_SDA_BASE_;
extern   void  *_SDA2_BASE_;



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

    stk      = (unsigned long *)stack_addr;
    stk--;
    stk--;
    *stk-- = 0;                             /* r31 */
    *stk-- = 0;                             /* r30 */
    *stk-- = 0;                             /* r29 */
    *stk-- = 0;                             /* r28 */
    *stk-- = 0;                             /* r27 */
    *stk-- = 0;                             /* r26 */
    *stk-- = 0;                             /* r25 */
    *stk-- = 0;                             /* r24 */
    *stk-- = 0;                             /* r23 */
    *stk-- = 0;                             /* r22 */
    *stk-- = 0;                             /* r21 */
    *stk-- = 0;                             /* r20 */
    *stk-- = 0;                             /* r19 */
    *stk-- = 0;                             /* r18 */
    *stk-- = 0;                             /* r17 */
    *stk-- = (unsigned long)texit - 8;      /* r15 = task return address*/
    *stk-- = (unsigned long)tentry;     /* r14 = entry address*/
    *stk-- = (unsigned long)&_SDA_BASE_;    /* r13 */
    *stk-- = 0;                             /* r12 */
    *stk-- = 0;                             /* r11 */
    *stk-- = 0;                             /* r10 */
    *stk-- = 0;                             /* r09 */
    *stk-- = 0;                             /* r08 */
    *stk-- = 0;                             /* r07 */
    *stk-- = 0;                             /* r06 */
    *stk-- = (unsigned long) parameter; /* r05 */
    *stk-- = 0;                             /* r04 */
    *stk-- = 0;                             /* r03 */
    *stk-- = (unsigned long)&_SDA2_BASE_;   /* r02 */
    *stk   = 2;                             /* enable interrupt */
    return (rt_uint8_t *)stk;
}

