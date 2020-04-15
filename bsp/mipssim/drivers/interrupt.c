/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 */

/**
 * @addtogroup mipssim
 */

/*@{*/

#include <rtthread.h>
#include <rthw.h>
#include <exception.h>

#define MAX_INTR 32

static struct rt_irq_desc irq_handle_table[MAX_INTR];

static void rt_hw_interrupt_handler(int vector, void *param)
{
    rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    rt_uint32_t idx;
    rt_memset(irq_handle_table, 0x00, sizeof(irq_handle_table));
    for (idx = 0; idx < MAX_INTR; idx ++)
    {
        irq_handle_table[idx].handler = rt_hw_interrupt_handler;
    }
}

rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
                                         void *param, const char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if (vector >= 0 && vector < MAX_INTR)
    {
        old_handler = irq_handle_table[vector].handler;

#ifdef RT_USING_INTERRUPT_INFO
        rt_strncpy(irq_handle_table[vector].name, name, RT_NAME_MAX);
#endif /* RT_USING_INTERRUPT_INFO */
        irq_handle_table[vector].handler = handler;
        irq_handle_table[vector].param = param;
    }

    return old_handler;
}

void rt_hw_timer_handler(void);

void rt_do_mips_cpu_irq(rt_uint32_t ip)
{
    void *param;
    rt_isr_handler_t irq_func;

    if (ip == 7) {
        rt_hw_timer_handler();
    } else {
        irq_func = irq_handle_table[ip].handler;
                param = irq_handle_table[ip].param;

                /* do interrupt */
                irq_func(ip, param);
    }
}

void rt_hw_interrupt_umask(int irq)
{
    mips_unmask_cpu_irq(irq);
}

void rt_hw_interrupt_mask(int irq)
{
    mips_mask_cpu_irq(irq);
}
/*@}*/
