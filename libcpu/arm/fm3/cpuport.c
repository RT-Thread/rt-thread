/*
 * File      : hwport.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-23     Bernard      the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <mb9bf506r.h>
#include <core_cm3.h>

/* switch flag on interrupt and thread pointer to save switch record */
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrput_flag;

/* stack context in ARM Cortex-M3 */
struct stack_context
{
	rt_uint32_t r0;
	rt_uint32_t r1;
	rt_uint32_t r2;
	rt_uint32_t r3;
	rt_uint32_t r12;
	rt_uint32_t lr;
	rt_uint32_t pc;
	rt_uint32_t psr;
};

extern void rt_hw_interrupt_thread_switch(void);
extern void list_thread(void);
extern rt_thread_t rt_current_thread;
void rt_hw_hard_fault_exception(struct stack_context* contex)
{
	rt_kprintf("psr: 0x%08x\n", contex->psr);
	rt_kprintf(" pc: 0x%08x\n", contex->pc);
	rt_kprintf(" lr: 0x%08x\n", contex->lr);
	rt_kprintf("r12: 0x%08x\n", contex->r12);
	rt_kprintf("r03: 0x%08x\n", contex->r3);
	rt_kprintf("r02: 0x%08x\n", contex->r2);
	rt_kprintf("r01: 0x%08x\n", contex->r1);
	rt_kprintf("r00: 0x%08x\n", contex->r0);

	if (rt_current_thread != RT_NULL)
	{
		rt_kprintf("hard fault on thread: %s\n", rt_current_thread->name);
#ifdef RT_USING_FINSH
		list_thread();
#endif
		while (1);
	}
	else
	{
		rt_kprintf("hard fault on initialization\n");
	}
}

/**
 * reset MCU
 *
 */
void rt_hw_cpu_reset()
{
	NVIC_SystemReset();
}

/**
 *  shutdown CPU
 *
 */
void rt_hw_cpu_shutdown()
{
	rt_kprintf("shutdown...\n");

	RT_ASSERT(0);
}

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
	*(stk)   = 0x01000000L;					/* PSR */
	*(--stk) = (unsigned long)tentry;		/* entry point, pc */
	*(--stk) = (unsigned long)texit;		/* lr */
	*(--stk) = 0;							/* r12 */
	*(--stk) = 0;							/* r3 */
	*(--stk) = 0;							/* r2 */
	*(--stk) = 0;							/* r1 */
	*(--stk) = (unsigned long)parameter;	/* r0 : argument */

	*(--stk) = 0;							/* r11 */
	*(--stk) = 0;							/* r10 */
	*(--stk) = 0;							/* r9 */
	*(--stk) = 0;							/* r8 */
	*(--stk) = 0;							/* r7 */
	*(--stk) = 0;							/* r6 */
	*(--stk) = 0;							/* r5 */
	*(--stk) = 0;							/* r4 */

	/* return task's current stack address */
	return (rt_uint8_t *)stk;
}
