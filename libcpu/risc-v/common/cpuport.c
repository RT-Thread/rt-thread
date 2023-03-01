/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/28     Bernard      The unify RISC-V porting code.
 * 2020/11/20     BalanceTWK   Add FPU support
 * 2023/01/04     WangShun     Adapt to CH32
 */

#include <rthw.h>
#include <rtthread.h>

#include "cpuport.h"
#include "rt_hw_stack_frame.h"

#ifndef RT_USING_SMP
volatile rt_ubase_t  rt_interrupt_from_thread = 0;
volatile rt_ubase_t  rt_interrupt_to_thread   = 0;
volatile rt_uint32_t rt_thread_switch_interrupt_flag = 0;
#endif

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
    struct rt_hw_stack_frame *frame;
    rt_uint8_t         *stk;
    int                i;

    stk  = stack_addr + sizeof(rt_ubase_t);
    stk  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_ubase_t)stk, REGBYTES);
    stk -= sizeof(struct rt_hw_stack_frame);

    frame = (struct rt_hw_stack_frame *)stk;

    for (i = 0; i < sizeof(struct rt_hw_stack_frame) / sizeof(rt_ubase_t); i++)
    {
        ((rt_ubase_t *)frame)[i] = 0xdeadbeef;
    }

    frame->ra      = (rt_ubase_t)texit;
    frame->a0      = (rt_ubase_t)parameter;
    frame->epc     = (rt_ubase_t)tentry;

    /* force to machine mode(MPP=11) and set MPIE to 1 */
#ifdef ARCH_RISCV_FPU
    frame->mstatus = 0x7880;
#else
    frame->mstatus = 0x1880;
#endif

    return stk;
}

rt_weak void rt_trigger_software_interrupt(void)
{
    while (0);
}

rt_weak void rt_hw_do_after_save_above(void)
{
    while (1);
}

/*
 * #ifdef RT_USING_SMP
 * void rt_hw_context_switch_interrupt(void *context, rt_ubase_t from, rt_ubase_t to, struct rt_thread *to_thread);
 * #else
 * void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to);
 * #endif
 */
#ifndef RT_USING_SMP
rt_weak void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to, rt_thread_t from_thread, rt_thread_t to_thread)
{
    if (rt_thread_switch_interrupt_flag == 0)
        rt_interrupt_from_thread = from;

    rt_interrupt_to_thread = to;
    rt_thread_switch_interrupt_flag = 1;

    rt_trigger_software_interrupt();

    return ;
}
#endif /* end of RT_USING_SMP */

/** shutdown CPU */
rt_weak void rt_hw_cpu_shutdown()
{
    rt_base_t level;
    rt_kprintf("shutdown...\n");

    level = rt_hw_interrupt_disable();
    while (level)
    {
        RT_ASSERT(0);
    }
}
