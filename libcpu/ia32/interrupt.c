/*
 * File      : interrupt.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2015, RT-Thread Development Team
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
 * 2015/9/15      Bernard      Update to new interrupt framework.
 */
 
#include <rtthread.h>
#include <rthw.h>

#include <bsp.h>

extern rt_uint32_t rt_interrupt_nest;
extern void rt_hw_idt_init(void);

rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/* exception and interrupt handler table */
struct rt_irq_desc irq_desc[MAX_HANDLERS];

rt_uint16_t irq_mask_8259A = 0xFFFF;

void rt_hw_interrupt_handle(int vector, void* param);

/**
 * @addtogroup I386
 */
/*@{*/

/**
 * This function initializes 8259 interrupt controller
 */
void rt_hw_pic_init()
{
	outb(IO_PIC1, 0x11);
	outb(IO_PIC1+1, IRQ_OFFSET);
	outb(IO_PIC1+1, 1<<IRQ_SLAVE);
	outb(IO_PIC1+1, 0x3);
	outb(IO_PIC1+1, 0xff);
	outb(IO_PIC1, 0x68);
	outb(IO_PIC1, 0x0a);
	outb(IO_PIC2, 0x11);
	outb(IO_PIC2+1, IRQ_OFFSET + 8);
	outb(IO_PIC2+1, IRQ_SLAVE);
	outb(IO_PIC2+1, 0x3);
	outb(IO_PIC2+1, 0xff);
	outb(IO_PIC2, 0x68);
	outb(IO_PIC2, 0x0a);

	if (irq_mask_8259A != 0xFFFF)
	{
		outb(IO_PIC1+1, (char)irq_mask_8259A);
		outb(IO_PIC2+1, (char)(irq_mask_8259A >> 8));
	}

	/* init interrupt nest, and context */
	rt_interrupt_nest = 0;
	rt_interrupt_from_thread = 0;
	rt_interrupt_to_thread = 0;
	rt_thread_switch_interrupt_flag = 0;
}

void rt_hw_interrupt_handle(int vector, void* param)
{
	rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
}

void rt_hw_isr(int vector)
{
	if (vector < MAX_HANDLERS)
	{
		irq_desc[vector].handler(vector, irq_desc[vector].param);
	}
}

/**
 * This function initializes interrupt descript table and 8259 interrupt controller
 *
 */
void rt_hw_interrupt_init(void)
{
	int idx;
	
	rt_hw_idt_init();
	rt_hw_pic_init();

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
}

void rt_hw_interrupt_umask(int vector)
{
	irq_mask_8259A = irq_mask_8259A&~(1<<vector);
	outb(IO_PIC1+1, (char)irq_mask_8259A);
	outb(IO_PIC2+1, (char)(irq_mask_8259A >> 8));
}

void rt_hw_interrupt_mask(int vector)
{
	irq_mask_8259A = irq_mask_8259A | (1<<vector);
	outb(IO_PIC1+1, (char)irq_mask_8259A);
	outb(IO_PIC2+1, (char)(irq_mask_8259A >> 8));
}

rt_isr_handler_t rt_hw_interrupt_install(int              vector,
                                         rt_isr_handler_t handler,
                                         void            *param,
                                         char            *name)
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

rt_base_t rt_hw_interrupt_disable(void)
{
	rt_base_t level;

	__asm__ __volatile__("pushfl ; popl %0 ; cli":"=g" (level): :"memory");
	return level;
}

void rt_hw_interrupt_enable(rt_base_t level)
{
	__asm__ __volatile__("pushl %0 ; popfl": :"g" (level):"memory", "cc");
}

/*@}*/
