/*
Copyright 2020 Shenzhen Academy of Aerospace Technology

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Change Logs:
Date           Author       Notes
2020-10-16     Dystopia     the first version
*/

#include <rthw.h>
#include <rtthread.h>

#include "bm3803.h"
#include "interrupt.h"

#define MAX_HANDLERS 256

extern volatile rt_uint8_t rt_interrupt_nest;
struct rt_irq_desc isr_table[MAX_HANDLERS];
rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    /* init exceptions table */
    rt_memset(isr_table, 0x00, sizeof(isr_table));

    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest = 0;
    rt_interrupt_from_thread = 0;
    rt_interrupt_to_thread = 0;
    rt_thread_switch_interrupt_flag = 0;
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int vector)
{
    if (vector > 0x1F || vector < 0x11)
        return;
    volatile struct lregs *regs = (struct lregs *)PREGS;
    regs->irqmask &= ~(1 << (vector - 0x10));
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    if (vector > 0x1F || vector < 0x11)
        return;
    volatile struct lregs *regs = (struct lregs *)PREGS;
    regs->irqmask |= 1 << (vector - 0x10);
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param new_handler the interrupt service routine to be installed
 * @param old_handler the old interrupt service routine
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, const char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if (vector < MAX_HANDLERS || vector >= 0)
    {
        old_handler = isr_table[vector].handler;

        if (handler != RT_NULL)
        {
#ifdef RT_USING_INTERRUPT_INFO
            rt_strncpy(isr_table[vector].name, name, RT_NAME_MAX);
#endif /* RT_USING_INTERRUPT_INFO */
            isr_table[vector].handler = handler;
            isr_table[vector].param = param;
        }
    }

    return old_handler;
}
