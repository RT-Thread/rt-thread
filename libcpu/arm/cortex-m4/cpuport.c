/*
 * File      : cpuport.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-23     Bernard      the first version
 * 2011-06-03     Bernard      merge all of C source code into cpuport.c
 */
#include <rtthread.h>

/* exception and interrupt handler table */
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

struct stack_contex
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

struct stack_contex_fpu
{
	rt_uint32_t r0;
	rt_uint32_t r1;
	rt_uint32_t r2;
	rt_uint32_t r3;
	rt_uint32_t r12;
	rt_uint32_t lr;
	rt_uint32_t pc;
	rt_uint32_t psr;
	/* FPU register */
	rt_uint32_t S0;
	rt_uint32_t S1;
	rt_uint32_t S2;
	rt_uint32_t S3;
	rt_uint32_t S4;
	rt_uint32_t S5;
	rt_uint32_t S6;
	rt_uint32_t S7;
	rt_uint32_t S8;
	rt_uint32_t S9;
	rt_uint32_t S10;
	rt_uint32_t S11;
	rt_uint32_t S12;
	rt_uint32_t S13;
	rt_uint32_t S14;
	rt_uint32_t S15;
	rt_uint32_t FPSCR;
	rt_uint32_t NO_NAME;
};

rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter,
	rt_uint8_t *stack_addr, void *texit)
{
	unsigned long *stk;
	struct stack_contex_fpu * stack_contex_fpu;

	stk 	 = (unsigned long *)stack_addr;

	stk -= sizeof(struct stack_contex_fpu);
	stack_contex_fpu = (struct stack_contex_fpu *)stk;
	stack_contex_fpu->r0 = (unsigned long)parameter; /* r0 : argument */
	stack_contex_fpu->r1 = 0;                        /* r1 */
	stack_contex_fpu->r2 = 0;                        /* r2 */
	stack_contex_fpu->r3 = 0;                        /* r3 */
	stack_contex_fpu->r12 = 0;                       /* r12 */
	stack_contex_fpu->lr = (unsigned long)texit;     /* lr */
	stack_contex_fpu->pc = (unsigned long)tentry;    /* entry point, pc */
	stack_contex_fpu->psr = 0x01000000L;             /* PSR */

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

extern void rt_hw_interrupt_thread_switch(void);
extern void list_thread(void);
extern rt_thread_t rt_current_thread;
void rt_hw_hard_fault_exception(struct stack_contex* contex)
{
	rt_kprintf("psr: 0x%08x\n", contex->psr);
	rt_kprintf(" pc: 0x%08x\n", contex->pc);
	rt_kprintf(" lr: 0x%08x\n", contex->lr);
	rt_kprintf("r12: 0x%08x\n", contex->r12);
	rt_kprintf("r03: 0x%08x\n", contex->r3);
	rt_kprintf("r02: 0x%08x\n", contex->r2);
	rt_kprintf("r01: 0x%08x\n", contex->r1);
	rt_kprintf("r00: 0x%08x\n", contex->r0);

	rt_kprintf("hard fault on thread: %s\n", rt_current_thread->name);
#ifdef RT_USING_FINSH
	list_thread();
#endif
	while (1);
}

void rt_hw_cpu_shutdown()
{
	rt_kprintf("shutdown...\n");

	RT_ASSERT(0);
}
