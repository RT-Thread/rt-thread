/*
 * File      : interrupt.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <rthw.h>

#include <bsp.h>

extern rt_uint32_t rt_interrupt_nest;
extern void rt_hw_idt_init(void);

rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/* exception and interrupt handler table */
rt_isr_handler_t isr_table[MAX_HANDLERS];
rt_uint16_t irq_mask_8259A = 0xFFFF;

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

void rt_hw_interrupt_handle(int vector)
{
	rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
}

/**
 * This function initializes interrupt descript table and 8259 interrupt controller
 *
 */
void rt_hw_interrupt_init(void)
{
	rt_hw_idt_init();
	rt_hw_pic_init();
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

void rt_hw_interrupt_install(int vector, rt_isr_handler_t new_handler, rt_isr_handler_t *old_handler)
{
	if(vector < MAX_HANDLERS)
	{
		if (*old_handler != RT_NULL) *old_handler = isr_table[vector];
		if (new_handler != RT_NULL) isr_table[vector] = new_handler;
	}
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
