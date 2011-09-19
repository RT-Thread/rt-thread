/*
 * File      : trap.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-12-11     XuXinming    first version
 */

#include <rtthread.h>
#include "LPC24xx.h"

#define MAX_HANDLERS	32

extern rt_uint32_t rt_interrupt_nest;

/* exception and interrupt handler table */
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;


/**
 * @addtogroup LPC2478
 */
/*@{*/

void rt_hw_interrupt_handle(int vector)
{
	rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
}

void rt_hw_interrupt_init()
{
	register int i;

	rt_uint32_t *vect_addr, *vect_cntl;
    
	/* initialize VIC*/
	VICIntEnClr = 0xffffffff;
	VICVectAddr = 0;
	VICIntSelect = 0;

    for ( i = 0; i < 32; i++ )
    {
		vect_addr = (rt_uint32_t *)(VIC_BASE_ADDR + 0x100 + i*4);
		vect_cntl = (rt_uint32_t *)(VIC_BASE_ADDR + 0x200 + i*4);
		*vect_addr = 0x0;	
		*vect_cntl = 0xF;
    }
	
	/* init interrupt nest, and context in thread sp */
	rt_interrupt_nest = 0;
	rt_interrupt_from_thread = 0;
	rt_interrupt_to_thread = 0;
	rt_thread_switch_interrupt_flag = 0;
}

void rt_hw_interrupt_mask(int vector)
{
	VICIntEnClr = (1 << vector);
}

void rt_hw_interrupt_umask(int vector)
{
	VICIntEnable = (1 << vector);
}

void rt_hw_interrupt_install(int vector, rt_isr_handler_t new_handler, rt_isr_handler_t *old_handler)
{
	rt_uint32_t *vect_addr;
	
	if(vector < MAX_HANDLERS)
	{
		/* find first un-assigned VIC address for the handler */
		vect_addr = (rt_uint32_t *)(VIC_BASE_ADDR + 0x100 + vector*4);

		/* get old handler */
		if (old_handler != RT_NULL) *old_handler = (rt_isr_handler_t)*vect_addr; 

		*vect_addr = (rt_uint32_t)new_handler;	/* set interrupt vector */
	}
}

/*@}*/
