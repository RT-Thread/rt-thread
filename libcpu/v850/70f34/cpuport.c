/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-23     Bernard      the first version
 * 2012-09-23     lgnq         set the texit to R31
 */

#include <rtthread.h>

extern volatile rt_atomic_t rt_interrupt_nest;

/* switch flag on interrupt and thread pointer to save switch record */
rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest               = 0;
    rt_interrupt_from_thread        = 0;
    rt_interrupt_to_thread          = 0;
    rt_thread_switch_interrupt_flag = 0;
}

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
rt_uint8_t *rt_hw_stack_init(void       *tentry,
                             void       *parameter,
                             rt_uint8_t *stack_addr,
                             void       *texit)
{
    rt_uint32_t *stk;

    stk      = (rt_uint32_t *)stack_addr;    /* Load stack pointer */

    *(--stk) = (rt_uint32_t)0x23232323;      /* r23 */
    *(--stk) = (rt_uint32_t)0x24242424;      /* r24 */
    *(--stk) = (rt_uint32_t)0x25252525;      /* r25 */
    *(--stk) = (rt_uint32_t)0x26262626;      /* r26 */
    *(--stk) = (rt_uint32_t)0x27272727;      /* r27 */
    *(--stk) = (rt_uint32_t)0x28282828;      /* r28 */
    *(--stk) = (rt_uint32_t)0x29292929;      /* r29 */
    *(--stk) = (rt_uint32_t)0x30303030;      /* r30 */
    *(--stk) = (rt_uint32_t)texit;           /* r31 */
    *(--stk) = (rt_uint32_t)0x00000000;      /* Task PSW = Interrupts enabled */
    *(--stk) = (rt_uint32_t)tentry;          /* Task's PC */
    *(--stk) = (rt_uint32_t)0x16161616;      /* r16 */
    *(--stk) = (rt_uint32_t)0x15151515;      /* r15 */
    *(--stk) = (rt_uint32_t)0x14141414;      /* r14 */
    *(--stk) = (rt_uint32_t)0x13131313;      /* r13 */
    *(--stk) = (rt_uint32_t)0x12121212;      /* r12 */
    *(--stk) = (rt_uint32_t)0x11111111;      /* r11 */
    *(--stk) = (rt_uint32_t)0x10101010;      /* r10 */
    *(--stk) = (rt_uint32_t)0x09090909;      /* r9 */
    *(--stk) = (rt_uint32_t)0x08080808;      /* r8 */
    *(--stk) = (rt_uint32_t)0x07070707;      /* r7 */
    *(--stk) = (rt_uint32_t)0x06060606;      /* r6 */
    *(--stk) = (rt_uint32_t)0x05050505;      /* r5 */
    *(--stk) = (rt_uint32_t)0x02020202;      /* r2 */
    *(--stk) = (rt_uint32_t)parameter;       /* r1 */

    return ((rt_uint8_t *)stk);
}

void rt_hw_context_switch(rt_uint32_t from, rt_uint32_t to)
{
    rt_interrupt_from_thread = from;
    rt_interrupt_to_thread = to;
    asm("trap 0x10");
}

void rt_hw_context_switch_interrupt(rt_uint32_t from, rt_uint32_t to)
{
    if (rt_thread_switch_interrupt_flag != 1)
    {
        rt_thread_switch_interrupt_flag = 1;
        rt_interrupt_from_thread = from;
    }
    rt_interrupt_to_thread = to;
}
