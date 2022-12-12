/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-12-11     XuXinming    first version
 * 2013-03-29     aozima       Modify the interrupt interface implementations.
 */

#include <rtthread.h>
#include <rthw.h>

#include <sys_vim.h>
#include <system.h>

#include "armv7.h"

#define MAX_HANDLERS    96

/* exception and interrupt handler table */
struct rt_irq_desc irq_desc[MAX_HANDLERS];

extern volatile rt_uint8_t rt_interrupt_nest;

/* exception and interrupt handler table */
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/**
 * @addtogroup RM48x50
 */

/*@{*/

static void rt_hw_int_not_handle(int vector, void *param)
{
    rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
}

#define vimRAM (0xFFF82000U)

void rt_hw_interrupt_init(void)
{
    register int i;

    rt_uint32_t *vect_addr;

    /* the initialization is done in sys_startup.c */

    /* init exceptions table */
    rt_memset(irq_desc, 0x00, sizeof(irq_desc));
    for(i=0; i < MAX_HANDLERS; i++)
    {
        irq_desc[i].handler = rt_hw_int_not_handle;

        vect_addr  = (rt_uint32_t *)(vimRAM + i*4);
        *vect_addr = (rt_uint32_t)&irq_desc[i];
    }

    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest = 0;
    rt_interrupt_from_thread = 0;
    rt_interrupt_to_thread = 0;
    rt_thread_switch_interrupt_flag = 0;
}

void rt_hw_interrupt_mask(int vector)
{
    vimDisableInterrupt(vector);
}

void rt_hw_interrupt_umask(int vector)
{
    vimEnableInterrupt(vector, SYS_IRQ);
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param handler the interrupt service routine to be installed
 * @param param the parameter for interrupt service routine
 * @name unused.
 *
 * @return the old handler
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
                                    void *param, const char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if(vector >= 0 && vector < MAX_HANDLERS)
    {
        old_handler = irq_desc[vector].handler;
        if (handler != RT_NULL)
        {
            irq_desc[vector].handler = handler;
            irq_desc[vector].param = param;
        }
    }

    return old_handler;
}

/*@}*/
