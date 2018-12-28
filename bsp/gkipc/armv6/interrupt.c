/*
 * File      : interrupt.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rthw.h>
#include "gk7101.h"

#define MAX_HANDLERS    (64)

extern rt_uint32_t rt_interrupt_nest;

/* exception and interrupt handler table */
struct rt_irq_desc irq_desc[MAX_HANDLERS];

rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;


/* --------------------------------------------------------------------
 *  Interrupt initialization
 * -------------------------------------------------------------------- */



void rt_hw_interrupt_mask(int irq);
void rt_hw_interrupt_umask(int irq);

rt_isr_handler_t rt_hw_interrupt_handle(rt_uint32_t vector, void *param)
{
    rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
    return RT_NULL;
}



/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    //rt_int32_t i;
    //register rt_uint32_t idx;


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
void rt_hw_interrupt_mask(int irq)
{

}


/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int irq)
{

}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param handler the interrupt service routine to be installed
 * @param param the interrupt service function parameter
 * @param name the interrupt name
 * @return old handler
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
                                    void *param, const char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if(vector < MAX_HANDLERS)
    {
        old_handler = irq_desc[vector].handler;
        if (handler != RT_NULL)
        {

#ifdef RT_USING_INTERRUPT_INFO
            rt_snprintf(irq_desc[vector].name, RT_NAME_MAX - 1, "%s", name);
            irq_desc[vector].counter = 0;
#endif
            irq_desc[vector].handler = (rt_isr_handler_t)handler;
            irq_desc[vector].param = param;
        }
    }

    return old_handler;
}

/*@}*/



#ifdef RT_USING_FINSH
void list_irq(void)
{
    int irq;

#ifdef RT_USING_INTERRUPT_INFO
    rt_kprintf("number\tcount\tname\n");
    for (irq = 0; irq < MAX_HANDLERS; irq++)
    {
        if (rt_strncmp(irq_desc[irq].name, "default", sizeof("default")))
        {
            rt_kprintf("%02ld: %10ld  %s\n", irq, irq_desc[irq].counter, irq_desc[irq].name);
        }
    }
#endif
}

#include <finsh.h>
FINSH_FUNCTION_EXPORT(list_irq, list system irq);

#endif


