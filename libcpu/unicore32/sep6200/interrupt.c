/*
 * File      : interrupt.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
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
 * 2013-7-14      Peng Fan     sep6200 implementation
 */

#include <rtthread.h>
#include <rthw.h>
#include <sep6200.h>

#define MAX_HANDLERS	64


#define SEP6200_IRQ_TYPE 0
#define SEP6200_FIQ_TYPE 1

#define int_enable_all() 					  \
	do {							  \
		*(volatile unsigned long*)SEP6200_VIC_INT_EN_L = ~0x0;\
		*(volatile unsigned long*)SEP6200_VIC_INT_EN_H = ~0x0;\
	}while(0)
#define int_disable_all() 					 \
	do {							 \
		*(volatile unsigned long*)SEP6200_VIC_INT_EN_L = 0x0;\
		*(volatile unsigned long*)SEP6200_VIC_INT_EN_H = 0x0;\
	}while(0)
#define mask_all_int(int_type)					 \
	do {							 \
		if (int_type == SEP6200_IRQ_TYPE){		 \
		*(volatile unsigned long*)SEP6200_VIC_INT_MSK_ALL = 0x1;\
		} else if (int_type == SEP6200_FIQ_TYPE) {\
		*(volatile unsigned long*)SEP6200_VIC_INT_MSK_ALL = 0x2;\
		}\
	}while(0)
#define unmask_all_int(int_type)\
	do {							 \
		if (int_type == SEP6200_IRQ_TYPE){		 \
		*(volatile unsigned long*)SEP6200_VIC_INT_MSK_ALL = ~0x1;\
		} else if (int_type == SEP6200_FIQ_TYPE) {\
		*(volatile unsigned long*)SEP6200_VIC_INT_MSK_ALL = ~0x2;\
		}\
	}while(0)

#define SEP6200_INT_SET(intnum)                                     \
do{                                                                 \
    if(intnum < 32)                                                 \
        *(volatile unsigned long*)SEP6200_VIC_SFT_INT_L |= (1 << intnum); \
    else                                                            \
        *(volatile unsigned long*)SEP6200_VIC_SFT_INT_H |= (1 << (intnum - 32));  \
}while(0)

#define SEP6200_INT_CLR(intnum)   \
do{                               \
    if(intnum < 32)               \
        *(volatile unsigned long*)SEP6200_VIC_SFT_INT_L &= ~(1 << intnum);\
    else                          \
        *(volatile unsigned long*)SEP6200_VIC_SFT_INT_H &= ~(1 << (intnum - 32)); \
}while(0)

#define SEP6200_INT_ENABLE(intnum)\
do{                               \
    if(intnum < 32)               \
        *(volatile unsigned long*)SEP6200_VIC_INT_EN_L |= (1 << intnum);  \
    else                          \
        *(volatile unsigned long*)SEP6200_VIC_INT_EN_H |= (1 << (intnum - 32));   \
}while(0)

#define SEP6200_INT_DISABLE(intnum)                                 \
do{                                                                 \
    if(intnum < 32)                                                 \
        *(volatile unsigned long*)SEP6200_VIC_INT_EN_L &= ~(1 << intnum); \
    else                                                            \
        *(volatile unsigned long*)SEP6200_VIC_INT_EN_H &= ~(1 << (intnum - 32));  \
}while(0)


extern rt_uint32_t rt_interrupt_nest;
/* exception and interrupt handler table */
struct rt_irq_desc isr_table[MAX_HANDLERS];
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;


/* --------------------------------------------------------------------
 *  Interrupt initialization
 * -------------------------------------------------------------------- */

/**
 * @addtogroup sep6200
 */
/*@{*/

void rt_hw_interrupt_mask(int irq);
void rt_hw_interrupt_umask(int irq);

rt_inline void sep6200_irq_enable(rt_uint32_t irq)
{
	SEP6200_INT_ENABLE(irq);
}

rt_inline void sep6200_irq_disable(rt_uint32_t irq)
{
	SEP6200_INT_DISABLE(irq);
}

rt_inline void sep6200_irq_unmask(rt_uint32_t irq)
{
	SEP6200_INT_ENABLE(irq);
}

rt_inline void sep6200_irq_mask(rt_uint32_t irq)
{
	SEP6200_INT_DISABLE(irq);
}
rt_isr_handler_t rt_hw_interrupt_handle(rt_uint32_t vector)
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


	/* init exceptions table */
	for(idx=0; idx < MAX_HANDLERS; idx++)
	{
		isr_table[idx].handler = (rt_isr_handler_t)rt_hw_interrupt_handle;
	}
	int_disable_all();
	mask_all_int(SEP6200_FIQ_TYPE);

	//int_enable_all();
	unmask_all_int(SEP6200_IRQ_TYPE);

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
	if (irq >= MAX_HANDLERS) {
		rt_kprintf("Wrong irq num to mask\n");
	} else {
		sep6200_irq_mask(irq);
	}

}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int irq)
{
	if (irq >= MAX_HANDLERS) {
		rt_kprintf("Wrong irq num to unmask\n");
	} else {
		sep6200_irq_unmask(irq);
	}
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

    if(vector < MAX_HANDLERS)
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

/*@}*/
