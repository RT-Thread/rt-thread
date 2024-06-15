/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021/02/19     Bernard      Implement rt_hw_context_switch_interrupt in C
 */

#include <rthw.h>
#include <rtthread.h>

volatile rt_ubase_t  rt_interrupt_from_thread = 0;
volatile rt_ubase_t  rt_interrupt_to_thread = 0;
volatile rt_uint32_t rt_thread_switch_interrupt_flag = 0;

rt_base_t rt_hw_interrupt_disable(void)
{
    rt_base_t level;

    __asm__ __volatile__("pushfl ; popl %0 ; cli":"=g" (level): :"memory");
    return level;
}

void rt_hw_interrupt_enable(rt_base_t level)
{
    __asm__ __volatile__("pushl %0 ; popfl": :"g" (level):"memory", "cc");
}

void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to, rt_thread_t from_thread, rt_thread_t to_thread)
{
    if (rt_thread_switch_interrupt_flag == 0)
        rt_interrupt_from_thread = from;

    rt_interrupt_to_thread = to;
    rt_thread_switch_interrupt_flag = 1;

    return ;
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
rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter,
    rt_uint8_t *stack_addr, void *texit)
{
    unsigned long *stk;

    stk = (unsigned long *)stack_addr;
    *(--stk) = (unsigned long)parameter;
    *(--stk) = (unsigned long)texit;
    *(--stk) = 0x200;                       /*flags*/
    *(--stk) = 0x08;                        /*cs*/
    *(--stk) = (unsigned long)tentry;       /*eip*/
    *(--stk) = 0;                           /*irqno*/
    *(--stk) = 0x10;                        /*ds*/
    *(--stk) = 0x10;                        /*es*/
    *(--stk) = 0;                           /*eax*/
    *(--stk) = 0;                           /*ecx*/
    *(--stk) = 0;                           /*edx*/
    *(--stk) = 0;                           /*ebx*/
    *(--stk) = 0;                           /*esp*/
    *(--stk) = 0;                           /*ebp*/
    *(--stk) = 0;                           /*esi*/
    *(--stk) = 0;                           /*edi*/

    /* return task's current stack address */
    return (rt_uint8_t *)stk;
}
