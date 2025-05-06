/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-01-25     Bernard      first version
 * 2012-05-31     aozima       Merge all of the C source code into cpuport.c
 * 2012-08-17     aozima       fixed bug: store r8 - r11.
 * 2012-12-23     aozima       stack addr align to 8byte.
 * 2019-03-31     xuzhuoyi     port to Cortex-M23.
 */

#include <rtthread.h>

#include "cpuport.h"

/* flag in interrupt handling */
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

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
    struct stack_frame *stack_frame;
    rt_uint8_t         *stk;
    unsigned long       i;

    stk  = stack_addr + sizeof(rt_uint32_t);
    stk  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stk, 8);
    stk -= sizeof(struct stack_frame);

    stack_frame = (struct stack_frame *)stk;

    /* init all register */
    for (i = 0; i < sizeof(struct stack_frame) / sizeof(rt_uint32_t); i ++)
    {
        ((rt_uint32_t *)stack_frame)[i] = 0xdeadbeef;
    }

    stack_frame->exception_stack_frame.r0  = (unsigned long)parameter; /* r0 : argument */
    stack_frame->exception_stack_frame.r1  = 0;                        /* r1 */
    stack_frame->exception_stack_frame.r2  = 0;                        /* r2 */
    stack_frame->exception_stack_frame.r3  = 0;                        /* r3 */
    stack_frame->exception_stack_frame.r12 = 0;                        /* r12 */
    stack_frame->exception_stack_frame.lr  = (unsigned long)texit;     /* lr */
    stack_frame->exception_stack_frame.pc  = (unsigned long)tentry;    /* entry point, pc */
    stack_frame->exception_stack_frame.psr = 0x01000000L;              /* PSR */

    /* return task's current stack address */
    return stk;
}

#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
extern long list_thread(void);
#endif
extern rt_thread_t rt_current_thread;
/**
 * fault exception handling
 */
void rt_hw_hard_fault_exception(struct exception_stack_frame *contex)
{
    rt_kprintf("psr: 0x%08x\n", contex->psr);
    rt_kprintf(" pc: 0x%08x\n", contex->pc);
    rt_kprintf(" lr: 0x%08x\n", contex->lr);
    rt_kprintf("r12: 0x%08x\n", contex->r12);
    rt_kprintf("r03: 0x%08x\n", contex->r3);
    rt_kprintf("r02: 0x%08x\n", contex->r2);
    rt_kprintf("r01: 0x%08x\n", contex->r1);
    rt_kprintf("r00: 0x%08x\n", contex->r0);

    rt_kprintf("hard fault on thread: %s\n", rt_current_thread->parent.name);

#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
    list_thread();
#endif

    while (1);
}

