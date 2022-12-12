/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2012-02-13   mojingxian  first version
 */

#include <rtthread.h>

/* flag in interrupt handling */
rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/**
 * initializes stack of thread
 */
rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter,
    rt_uint8_t *stack_addr, void *texit)
{
    unsigned char i;
    unsigned long *stk;

    stk    = (unsigned long *)stack_addr;     /* Load stack pointer                                    */

                                              /* Simulate a function call to the task with an argument */
    stk   -= 3;                               /* 3 words assigned for incoming args (R0, R1, R2)       */

                                              /* Now simulating vectoring to an ISR                    */
    *--stk = (unsigned long)parameter;        /* R0 value - caller's incoming argument #1              */
    *--stk = (unsigned long)0;                /* P1 value - value irrelevant                           */

    *--stk = (unsigned long)texit;            /* RETS value - NO task should return with RTS.          */
                                              /* however OS_CPU_Invalid_Task_Return is a safety        */
                                              /* catch-allfor tasks that return with an RTS            */

    *--stk = (unsigned long)parameter;        /* R1 value - caller's incoming argument #2              */
                                              /* (not relevant in current test example)                */
    *--stk = (unsigned long)parameter;        /* R2 value - caller's incoming argument #3              */
                                              /* (not relevant in current test example)                */
    *--stk = (unsigned long)0;                /* P0 value - value irrelevant                           */
    *--stk = (unsigned long)0;                /* P2 value - value irrelevant                           */
    *--stk = (unsigned long)0;                /* ASTAT value - caller's ASTAT value - value            */
                                              /* irrelevant                                            */

    *--stk = (unsigned long)tentry;           /* RETI value- pushing the start address of the task     */

    for (i = 0; i < 35; i++)                  /* remaining reg values - R7:3, P5:3,                    */
    {                                         /* 4 words of A1:0(.W,.X), LT0, LT1,                     */
        *--stk = (unsigned long)0;            /* LC0, LC1, LB0, LB1,I3:0, M3:0, L3:0, B3:0,            */
    }                                         /* All values irrelevant                                 */

    return (rt_uint8_t *)stk;                 /* Return top-of-stack                                   */
}

void rt_hw_context_switch(rt_uint32_t from, rt_uint32_t to)
{
    if (rt_thread_switch_interrupt_flag != 1)
    {
        rt_thread_switch_interrupt_flag = 1;
        rt_interrupt_from_thread = from;
    }

    rt_interrupt_to_thread = to;
    asm("raise 14;");                     // Raise Interrupt 14 (trap)
}

void rt_hw_context_switch_interrupt(rt_uint32_t from, rt_uint32_t to)
{
    if (rt_thread_switch_interrupt_flag != 1)
    {
        rt_thread_switch_interrupt_flag = 1;
        rt_interrupt_from_thread = from;
    }

    rt_interrupt_to_thread = to;
    asm("raise 14;");                     // Raise Interrupt 14 (trap)
}

void rt_hw_context_switch_to(rt_uint32_t to)
{
    rt_thread_switch_interrupt_flag = 1;
    rt_interrupt_from_thread = 0;
    rt_interrupt_to_thread = to;
    asm("raise 14;");                     // Raise Interrupt 14 (trap)
}
