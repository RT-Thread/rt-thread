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
 */

#include <rtthread.h>
#include <rthw.h>

#include <bsp.h>

/* Interrupt descriptor table.  (Must be built at run time because
 * shifted function addresses can't be represented in relocation records.)
 */
struct Gatedesc idt[256] = { {0}, };
struct Pseudodesc idt_pd =
{
	0, sizeof(idt) - 1, (unsigned long) idt,
};

/* exception and interrupt handler table */
extern rt_isr_handler_t isr_table[];
extern rt_isr_handler_t trap_func[];
extern rt_isr_handler_t hdinterrupt_func[];

/**
 * @addtogroup I386
 */
/*@{*/

/**
 * this function initializes the interrupt descript table
 *
 */
void rt_hw_idt_init(void)
{	
	extern void Xdefault;
	int i, j, func;

	for(i=0; i<MAX_HANDLERS; i++)
	{
		isr_table[i] = rt_hw_interrupt_handle;
	}

	// install a default handler
	for (i = 0; i < sizeof(idt)/sizeof(idt[0]); i++)
		SETGATE(idt[i], 0, GD_KT, &Xdefault, 0);

	/*install trap handler*/
	for(i = 0; i < 16; i++)
	{
		func = (int)trap_func[i];
		SETGATE(idt[i], 0, GD_KT, func, 0);
	}

	func = (int)trap_func[3];
	SETGATE(idt[3], 0, GD_KT, func, 3);

	i = 0;
	
	/*install exteral interrupt handler*/
	for(j = IRQ_OFFSET; j < IRQ_OFFSET + MAX_HANDLERS; j++)
	{	
		func = (int)hdinterrupt_func[i];
		SETGATE(idt[j], 0, GD_KT, func, 0);
		i++;
	}
	
	// Load the IDT
	asm volatile("lidt idt_pd + 2");
}

/**
 * this function will deal with all kinds of kernel trap
 *
 *@param trapno the trap number
 *
 */
void rt_hw_trap_irq(int trapno)
{
	switch(trapno)
	{
		case T_DIVIDE:
			rt_kprintf("Divide error interrupt\n");
			RT_ASSERT(0);
		case T_PGFLT:
			rt_kprintf("Page fault interrupt\n");
			RT_ASSERT(0);
		case T_GPFLT:
			rt_kprintf("General protection interrupt\n");
			RT_ASSERT(0);
		case T_DEFAULT:
			rt_hw_interrupt_handle(T_DEFAULT);
			return;
	}

	/*kernel bug if run here*/
	RT_ASSERT(0);
}

/*@}*/
