/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
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
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */

/*****************************************************************************
 *  Include Section
 *  add all #include here
 *****************************************************************************/

#include "interrupt.h"
#include "fh_def.h"
#include "fh_arch.h"
#include "libraries/inc/fh_ictl.h"

/*****************************************************************************
 * Define section
 * add all #define here
 *****************************************************************************/
#define MAX_HANDLERS    (NR_INTERNAL_IRQS+NR_EXTERNAL_IRQS)


/****************************************************************************
 * ADT section
 *  add definition of user defined Data Type that only be used in this file  here
 ***************************************************************************/

/******************************************************************************
 * Function prototype section
 * add prototypes for all functions called by this file,execepting those
 * declared in header file
 *****************************************************************************/



/*****************************************************************************
 * Global variables section - Exported
 * add declaration of global variables that will be exported here
 * e.g.
 *  int8_t foo;
 ****************************************************************************/
extern rt_uint32_t rt_interrupt_nest;
struct rt_irq_desc irq_desc[MAX_HANDLERS];
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;
/*****************************************************************************
 * Global variables section - Local
 * define global variables(will be refered only in this file) here,
 * static keyword should be used to limit scope of local variable to this file
 * e.g.
 *  static uint8_t ufoo;
 *****************************************************************************/



 /* function body */






/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/
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
    rt_int32_t i;
    register rt_uint32_t idx;
	fh_intc *p = (fh_intc *)INTC_REG_BASE;


	ictl_close_all_isr(p);
    /* init exceptions table */
    for(idx=0; idx < MAX_HANDLERS; idx++)
    {

        irq_desc[idx].handler = (rt_isr_handler_t)rt_hw_interrupt_handle;
        irq_desc[idx].param = RT_NULL;
#ifdef RT_USING_INTERRUPT_INFO
        rt_snprintf(irq_desc[idx].name, RT_NAME_MAX - 1, "default");
        irq_desc[idx].counter = 0;
#endif

    }

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

	fh_intc *p = (fh_intc *)INTC_REG_BASE;
    /* Disable irq on AIC */
	ictl_mask_isr(p,irq);

//	if (irq < 32)
//    	p->IRQ_EN_L &= ~(1 << irq);
//	else
//		p->IRQ_EN_H &= ~(1 << (irq - 32));
}


void rt_hw_interrupt_umask(int irq)
{

	fh_intc *p = (fh_intc *)INTC_REG_BASE;
    /* Enable irq on AIC */
	ictl_unmask_isr(p,irq);
//    if (irq < 32)
//    	p->IRQ_EN_L |= 1 << irq;
//	else
//		p->IRQ_EN_H |= 1 << (irq - 32);
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
            irq_desc[vector].handler = (rt_isr_handler_t)handler;
            irq_desc[vector].param = param;
#ifdef RT_USING_INTERRUPT_INFO
            rt_snprintf(irq_desc[vector].name, RT_NAME_MAX - 1, "%s", name);
			irq_desc[vector].counter = 0;
#endif
        }
    }

    return old_handler;
}

#ifdef RT_USING_FINSH
void list_irq(void)
{

#ifdef RT_USING_INTERRUPT_INFO
	int irq;
    rt_kprintf("number\tcount\tname\n");
    for (irq = 0; irq < MAX_HANDLERS; irq++)
    {
        if (rt_strncmp(irq_desc[irq].name, "default", sizeof("default")))
        {
            rt_kprintf("%02ld: %10ld  %s\n", irq, irq_desc[irq].counter, irq_desc[irq].name);
        }
    }
#else
    rt_kprintf("please open 'RT_USING_INTERRUPT_INFO'\n");

#endif
}
#include <finsh.h>
FINSH_FUNCTION_EXPORT(list_irq, list system irq);

#endif

