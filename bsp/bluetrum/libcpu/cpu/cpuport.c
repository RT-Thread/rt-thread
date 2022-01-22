/*
 * Copyright (c) 2020-2020, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/11/18     greedyhao    Bluetrum RISC-V porting code.
 */

#include <rthw.h>
#include <rtthread.h>

volatile rt_ubase_t  rt_interrupt_from_thread = 0;
volatile rt_ubase_t  rt_interrupt_to_thread   = 0;
volatile rt_uint32_t rt_thread_switch_interrupt_flag = 0;
rt_uint32_t rt_cur_thread_sp = 0;

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
    register int *tp asm("x3");

    stack_addr += sizeof(rt_uint32_t);
    stack_addr  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stack_addr, 8);
    stk  = (rt_uint32_t *)stack_addr;

    stk--;
    *stk = (rt_uint32_t)0x10003;         /* Start address */
    stk--;
    *stk = (rt_uint32_t)tentry;         /* Start address */
    stk -= 22;
    *stk = (rt_uint32_t)parameter;      /* Register a0  parameter*/
    stk -= 6;
    *stk = (rt_uint32_t)tp;             /* Register thread pointer */
    stk --;
    *stk = (rt_uint32_t)texit;          /* Register ra   texit*/

    /* return task's current stack address */
    return (rt_uint8_t *)stk;
}

/** shutdown CPU */
void rt_hw_cpu_shutdown(void)
{
    rt_uint32_t level;
    rt_kprintf("shutdown...\n");

    level = rt_hw_interrupt_disable();
    while (level)
    {
        RT_ASSERT(0);
    }
}
