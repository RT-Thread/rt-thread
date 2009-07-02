/*
 * File      : idle.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-23     Bernard      the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "kservice.h"

#if defined (RT_USING_HOOK) || defined(RT_USING_HEAP)
#define IDLE_THREAD_STACK_SIZE	256
#else
#define IDLE_THREAD_STACK_SIZE	128
#endif

static struct rt_thread idle;
static rt_uint8_t rt_thread_stack[IDLE_THREAD_STACK_SIZE];

#ifdef RT_USING_HEAP
extern rt_list_t rt_thread_defunct;
#endif

#ifdef RT_USING_HOOK
/**
 * @addtogroup Hook
 */
/*@{*/

static void (*rt_thread_idle_hook)();

/**
 * This function will set a hook function to idle thread loop.
 *
 * @param hook the specified hook function
 *
 * @note the hook function must be simple and never be blocked or suspend.
 */
void rt_thread_idle_sethook(void (*hook)())
{
	rt_thread_idle_hook = hook;
}
/*@}*/
#endif

static void rt_thread_idle_entry(void* parameter)
{
	while (1)
	{
#ifdef RT_USING_HOOK
		/* if there is an idle thread hook */
		if (rt_thread_idle_hook != RT_NULL) rt_thread_idle_hook();
#endif

#ifdef RT_USING_HEAP
		/* check the defunct thread list */
		if (!rt_list_isempty(&rt_thread_defunct))
		{
			rt_base_t lock;

			struct rt_thread* thread = rt_list_entry(rt_thread_defunct.next, struct rt_thread, tlist);

			/* disable interrupt */
			lock = rt_hw_interrupt_disable();

			rt_list_remove(&(thread->tlist));

			/* enable interrupt */
			rt_hw_interrupt_enable(lock);

			/* release thread's stack */
			rt_free(thread->stack_addr);

			/* delete thread object */
			rt_object_delete((rt_object_t)thread);
		}
#endif
	}
}

/**
 * @addtogroup SystemInit
 */
/*@{*/

/**
 * This function will initialize idle thread, then start it.
 *
 * @note this function must be invoked when system init.
 */
void rt_thread_idle_init()
{
	/* init thread */
	rt_thread_init(&idle,
		"tidle",
		rt_thread_idle_entry, RT_NULL,
		&rt_thread_stack[0], sizeof(rt_thread_stack),
		RT_THREAD_PRIORITY_MAX - 1, 32);

	/* startup */
	rt_thread_startup(&idle);
}

/*@}*/
