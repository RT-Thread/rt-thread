/*
 * Copyright (c) 2023-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-01     Yaochenger   The first version
 * 2023-03-19     flyingcys    Add support for rv32e
 * 2023-03-29     flyingcys    return old handler when install new one for rt_hw_interrupt_install
 * 2023-06-08     Liu,Yuan     remove unused variables
 * 2025-01-27     Chen Wang    fix build warnings
 * 2025-12-11     HPMicro      allow overriding the ISR numbers
 */
#include <rthw.h>
#include <rtthread.h>
#include "riscv-ops.h"
#include "rt_hw_stack_frame.h"

#ifndef RT_HW_ISR_NUM
#define RT_HW_ISR_NUM 32
#endif
static volatile rt_hw_stack_frame_t *s_stack_frame;
static struct rt_irq_desc rv32irq_table[RT_HW_ISR_NUM];
void rt_show_stack_frame(void);

/**
 * Temporary interrupt entry function
 *
 * @param mcause Machine Cause Register
 * @return RT_NULL
 */
rt_weak rt_isr_handler_t rt_hw_interrupt_handle(rt_uint32_t mcause)
{
    rt_kprintf("UN-handled interrupt %d occurred!!!\n", mcause);
    return RT_NULL;
}

/**
 * Interrupt entry function initialization
 */
rt_weak void rt_hw_interrupt_init(void)
{
    int idx = 0;

    for (idx = 0; idx < RT_HW_ISR_NUM; idx++)
    {
        rv32irq_table[idx].handler = (rt_isr_handler_t)rt_hw_interrupt_handle;
        rv32irq_table[idx].param = RT_NULL;
    }
}

/**
 * Break Entry Function Binding
 *
 * @param vector  interrupt number
 * @param handler Break-in function requiring binding
 * @param param   NULL
 * @param name    NULL
 * @return old handler
 */
rt_weak rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, const char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if(vector < RT_HW_ISR_NUM)
    {
        old_handler = rv32irq_table[vector].handler;
        if (handler != RT_NULL)
        {
            rv32irq_table[vector].handler = (rt_isr_handler_t)handler;
            rv32irq_table[vector].param = param;
        }
    }

    return old_handler;
}

/**
 * Query and Distribution Entry for Exception and Interrupt Sources
 *
 * @param mcause Machine Cause Register
 */
rt_weak void rt_rv32_system_irq_handler(rt_uint32_t mcause)
{
    rt_uint32_t mscratch = read_csr(0x340);
    rt_uint32_t irq_id = (mcause & 0x1F);
    rt_uint32_t exception = !(mcause & 0x80000000);
    if(exception)
    {
        s_stack_frame = (volatile rt_hw_stack_frame_t *)(uintptr_t)mscratch;
        rt_show_stack_frame();
    }
    else
    {
        rv32irq_table[irq_id].handler(irq_id, rv32irq_table[irq_id].param);
    }
}

/**
 * Register Print on Exception
 */
rt_weak void rt_show_stack_frame(void)
{
    rt_kprintf("Stack frame:\r\n----------------------------------------\r\n");
    rt_kprintf("ra      : 0x%08x\r\n", s_stack_frame->ra);
    rt_kprintf("mstatus : 0x%08x\r\n", read_csr(0x300));//mstatus
    rt_kprintf("t0      : 0x%08x\r\n", s_stack_frame->t0);
    rt_kprintf("t1      : 0x%08x\r\n", s_stack_frame->t1);
    rt_kprintf("t2      : 0x%08x\r\n", s_stack_frame->t2);
    rt_kprintf("a0      : 0x%08x\r\n", s_stack_frame->a0);
    rt_kprintf("a1      : 0x%08x\r\n", s_stack_frame->a1);
    rt_kprintf("a2      : 0x%08x\r\n", s_stack_frame->a2);
    rt_kprintf("a3      : 0x%08x\r\n", s_stack_frame->a3);
    rt_kprintf("a4      : 0x%08x\r\n", s_stack_frame->a4);
    rt_kprintf("a5      : 0x%08x\r\n", s_stack_frame->a5);
#ifndef __riscv_32e
    rt_kprintf("a6      : 0x%08x\r\n", s_stack_frame->a6);
    rt_kprintf("a7      : 0x%08x\r\n", s_stack_frame->a7);
    rt_kprintf("t3      : 0x%08x\r\n", s_stack_frame->t3);
    rt_kprintf("t4      : 0x%08x\r\n", s_stack_frame->t4);
    rt_kprintf("t5      : 0x%08x\r\n", s_stack_frame->t5);
    rt_kprintf("t6      : 0x%08x\r\n", s_stack_frame->t6);
#endif
}
