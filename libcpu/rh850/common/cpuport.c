/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-06     Parthiban    first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "rh850_cpu.h"
#include "rh850_core.h"

#ifdef RT_USING_FPU
#define THREAD_PSW (RH850_PSW_EBV | RH850_PSW_CU0)
#else
#define THREAD_PSW RH850_PSW_EBV
#endif

volatile rt_ubase_t rt_interrupt_from_thread;
volatile rt_ubase_t rt_interrupt_to_thread;
volatile rt_ubase_t rt_thread_switch_interrupt_flag;

rt_uint32_t rh850_irq_nest;
rt_ubase_t rh850_thread_sp;

rt_weak int rt_hw_cpu_id(void)
{
    return 0;
}

rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter,
                             rt_uint8_t *stack_addr, void *texit)
{
    struct rt_hw_stack_frame *frame;
    rt_ubase_t stk;

    stk = RT_ALIGN_DOWN((rt_ubase_t)stack_addr + sizeof(rt_ubase_t), 8);
    frame = (struct rt_hw_stack_frame *)(stk - sizeof(*frame));
    rt_memset(frame, 0, sizeof(*frame));

    frame->eipc = (rt_ubase_t)tentry;
    frame->eipsw = THREAD_PSW;
#ifdef RT_USING_FPU
    frame->fpsr = RH850_FPSR_FS;
#endif
    frame->FRAME_GPR(6) = (rt_ubase_t)parameter;
    frame->FRAME_GPR(31) = (rt_ubase_t)texit;

    return (rt_uint8_t *)frame;
}

void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to,
                                    rt_thread_t from_thread,
                                    rt_thread_t to_thread)
{
    RT_UNUSED(from_thread);
    RT_UNUSED(to_thread);

    if (rt_thread_switch_interrupt_flag == 0)
    {
        rt_interrupt_from_thread = from;
        rt_thread_switch_interrupt_flag = 1;
    }
    rt_interrupt_to_thread = to;
}

void rh850_irq_handle(rt_uint32_t eiic)
{
    rt_interrupt_enter();
    rh850_ei();
    rt_hw_interrupt_dispatch(eiic);
    rh850_di();
    rt_interrupt_leave();
}
