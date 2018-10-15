/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-06-15     aozima       the first version for lpc214x
 * 2013-03-29     aozima       Modify the interrupt interface implementations.
 */

#include <rtthread.h>
#include <rthw.h>
#include "lpc214x.h"

#define MAX_HANDLERS	32
#define SVCMODE		    0x13

extern rt_uint32_t rt_interrupt_nest;

/* exception and interrupt handler table */
struct rt_irq_desc irq_desc[MAX_HANDLERS]; 

/**
 * @addtogroup LPC214x
 */
/*@{*/

/**
 * This function will initialize thread stack
 *
 * @param tentry the entry of thread
 * @param parameter the parameter of entry
 * @param stack_addr the beginning stack address
 * @param texit the function will be called when thread exit
 *
 * @return stack address
 */
rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter,
	rt_uint8_t *stack_addr, void *texit)
{
	unsigned long *stk;

	stk 	 = (unsigned long *)stack_addr;
	*(stk) 	 = (unsigned long)tentry;		/* entry point */
	*(--stk) = (unsigned long)texit;		/* lr */
	*(--stk) = 0;							/* r12 */
	*(--stk) = 0;							/* r11 */
	*(--stk) = 0;							/* r10 */
	*(--stk) = 0;							/* r9 */
	*(--stk) = 0;							/* r8 */
	*(--stk) = 0;							/* r7 */
	*(--stk) = 0;							/* r6 */
	*(--stk) = 0;							/* r5 */
	*(--stk) = 0;							/* r4 */
	*(--stk) = 0;							/* r3 */
	*(--stk) = 0;							/* r2 */
	*(--stk) = 0;							/* r1 */
	*(--stk) = (unsigned long)parameter;	/* r0 : argument */

	/* cpsr */
	if ((rt_uint32_t)tentry & 0x01)
		*(--stk) = SVCMODE | 0x20;			/* thumb mode */
	else
		*(--stk) = SVCMODE;					/* arm mode   */

	/* return task's current stack address */
	return (rt_uint8_t *)stk;
}

/* exception and interrupt handler table */
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

void rt_hw_interrupt_handler(int vector, void *param)
{
	rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
	rt_base_t index;
	rt_uint32_t *vect_addr, *vect_ctl;

	/* initialize VIC*/
	VICIntEnClr = 0xffffffff;
	VICVectAddr = 0;
	/* set all to IRQ */
	VICIntSelect = 0;

    rt_memset(irq_desc, 0x00, sizeof(irq_desc));
	for (index = 0; index < MAX_HANDLERS; index ++)
	{
        irq_desc[index].handler = rt_hw_interrupt_handler;

		vect_addr 	= (rt_uint32_t *)(VIC_BASE_ADDR + 0x100 + (index << 2));
		vect_ctl 	= (rt_uint32_t *)(VIC_BASE_ADDR + 0x200 + (index << 2));

		*vect_addr 	= (rt_uint32_t)&irq_desc[index];
		*vect_ctl 	= 0xF;
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
void rt_hw_interrupt_mask(int vector)
{
	VICIntEnClr = (1 << vector);
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
	VICIntEnable = (1 << vector);
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
                                         void *param, char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if(vector >= 0 && vector < MAX_HANDLERS)
    {
        rt_uint32_t* vect_ctl 	= (rt_uint32_t *)(VIC_BASE_ADDR + 0x200 + (vector << 2));

        /* assign IRQ slot and enable this slot */
        *vect_ctl = 0x20 | (vector & 0x1F);

        old_handler = irq_desc[vector].handler;
		if (handler != RT_NULL)
		{
			irq_desc[vector].handler = handler;
			irq_desc[vector].param = param;
		}
    }

    return old_handler;
}

/**
 * this function will reset CPU
 *
 */
void rt_hw_cpu_reset(void)
{
}

/**
 * this function will shutdown CPU
 *
 */
void rt_hw_cpu_shutdown()
{
	rt_kprintf("shutdown...\n");

	while (1);
}

void rt_hw_trap_irq(void)
{
    int irqno;
	struct rt_irq_desc* irq;
    extern struct rt_irq_desc irq_desc[];

	irq = (struct rt_irq_desc*) VICVectAddr;
	irqno = ((rt_uint32_t) irq - (rt_uint32_t) &irq_desc[0])/sizeof(struct rt_irq_desc);

	/* invoke isr */
	irq->handler(irqno, irq->param);

    /* acknowledge Interrupt */
    // VICVectAddr = 0;
}

void rt_hw_trap_fiq(void)
{
    rt_kprintf("fast interrupt request\n");
}

/*@}*/
