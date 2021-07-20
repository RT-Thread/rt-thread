/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/5/3       Bernard      first version
 * 2019-07-28     zdzn         add smp support
 * 2019-08-09     zhangjun     fixup the problem of smp startup and scheduling issues, 
 *                             write addr to mailbox3 to startup smp, and we use mailbox0 for ipi
 */

#include <rthw.h>
#include <rtthread.h>
#include <gic_pl400.h>
#include <board.h>
#include <armv8.h>

#define MAX_HANDLERS                72

#ifdef RT_USING_SMP
#define rt_interrupt_nest rt_cpu_self()->irq_nest
#else
extern volatile rt_uint8_t rt_interrupt_nest;
#endif

extern int system_vectors;

/* exception and interrupt handler table */
struct rt_irq_desc isr_table[MAX_HANDLERS];

rt_ubase_t rt_interrupt_from_thread;
rt_ubase_t rt_interrupt_to_thread;
rt_ubase_t rt_thread_switch_interrupt_flag;

void rt_hw_vector_init(void)
{
    rt_hw_set_current_vbar((rt_ubase_t)&system_vectors);  // cpu_gcc.S
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    initIRQController();
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

    if (vector < MAX_HANDLERS)
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

#ifdef RT_USING_SMP
void rt_hw_ipi_send(int ipi_vector, unsigned int cpu_mask)
{
    __DSB();
    if(cpu_mask & 0x1)
    {
        send_ipi_msg(0, ipi_vector);
    }
    if(cpu_mask & 0x2)
    {
    	send_ipi_msg(1, ipi_vector);
    }
    if(cpu_mask & 0x4)
    {
    	send_ipi_msg(2, ipi_vector);
    }
    if(cpu_mask & 0x8)
    {
    	send_ipi_msg(3, ipi_vector);
    }
    __DSB();
}
#endif

#ifdef RT_USING_SMP
void rt_hw_ipi_handler_install(int ipi_vector, rt_isr_handler_t ipi_isr_handler)
{
    /* note: ipi_vector maybe different with irq_vector */
    rt_hw_interrupt_install(ipi_vector, ipi_isr_handler, 0, "IPI_HANDLER");
}
#endif
