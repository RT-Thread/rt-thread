/*
 * File      : cpuport.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date         Author      Notes
 * 2009-01-05   Bernard     first version
 * 2011-02-14   onelife     Modify for EFM32
 * 2011-06-17   onelife     Merge all of the C source code into cpuport.c
 * 2012-12-23   aozima      stack addr align to 8byte.
 * 2012-12-29   Bernard     Add exception hook.
 */

#include <rtthread.h>

struct exception_stack_frame
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

struct stack_frame
{
    /* r4 ~ r11 register */
    rt_uint32_t r4;
    rt_uint32_t r5;
    rt_uint32_t r6;
    rt_uint32_t r7;
    rt_uint32_t r8;
    rt_uint32_t r9;
    rt_uint32_t r10;
    rt_uint32_t r11;

    struct exception_stack_frame exception_stack_frame;
};

/* flag in interrupt handling */
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;
/* exception hook */
static rt_err_t (*rt_exception_hook)(void *context) = RT_NULL;

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
rt_uint8_t *rt_hw_stack_init(void       *tentry,
                             void       *parameter,
                             rt_uint8_t *stack_addr,
                             void       *texit)
{
    struct stack_frame *stack_frame;
    rt_uint8_t         *stk;
    unsigned long       i;

    stk  = stack_addr + sizeof(rt_uint32_t);
    stk  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stk, 8);
    stk -= sizeof(struct stack_frame);

    stack_frame = (struct stack_frame *)stk;

    /* init all register */
    for (i = 0; i < sizeof(struct stack_frame) / sizeof(rt_uint32_t); i ++)
    {
        ((rt_uint32_t *)stack_frame)[i] = 0xdeadbeef;
    }

    stack_frame->exception_stack_frame.r0  = (unsigned long)parameter; /* r0 : argument */
    stack_frame->exception_stack_frame.r1  = 0;                        /* r1 */
    stack_frame->exception_stack_frame.r2  = 0;                        /* r2 */
    stack_frame->exception_stack_frame.r3  = 0;                        /* r3 */
    stack_frame->exception_stack_frame.r12 = 0;                        /* r12 */
    stack_frame->exception_stack_frame.lr  = (unsigned long)texit;     /* lr */
    stack_frame->exception_stack_frame.pc  = (unsigned long)tentry;    /* entry point, pc */
    stack_frame->exception_stack_frame.psr = 0x01000000L;              /* PSR */

    /* return task's current stack address */
    return stk;
}

/**
 * This function set the hook, which is invoked on fault exception handling.
 *
 * @param exception_handle the exception handling hook function.
 */
void rt_hw_exception_install(rt_err_t (*exception_handle)(void* context))
{
	rt_exception_hook = exception_handle;
}

/*
 * fault exception handler
 */
void rt_hw_hard_fault_exception(struct exception_stack_frame* context)
{
	extern long list_thread(void);

	if (rt_exception_hook != RT_NULL)
	{
		rt_err_t result;

		result = rt_exception_hook(context);
		if (result == RT_EOK) return;
	}

    rt_kprintf("psr: 0x%08x\n", context->psr);
    rt_kprintf(" pc: 0x%08x\n", context->pc);
    rt_kprintf(" lr: 0x%08x\n", context->lr);
    rt_kprintf("r12: 0x%08x\n", context->r12);
    rt_kprintf("r03: 0x%08x\n", context->r3);
    rt_kprintf("r02: 0x%08x\n", context->r2);
    rt_kprintf("r01: 0x%08x\n", context->r1);
    rt_kprintf("r00: 0x%08x\n", context->r0);

    rt_kprintf("hard fault on thread: %s\n", rt_thread_self()->name);

#ifdef RT_USING_FINSH
    list_thread();
#endif

    while (1);
}

/**
 * shutdown CPU
 */
void rt_hw_cpu_shutdown(void)
{
    rt_kprintf("shutdown...\n");

    RT_ASSERT(0);
}

