/*
 * File      : clock.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-12     Bernard      first version
 * 2006-05-27     Bernard      add support for same priority thread schedule
 * 2006-08-10     Bernard      remove the last rt_schedule in rt_tick_increase
 */

#include <rtthread.h>

static rt_tick_t rt_tick;
static rt_time_t rt_passed_second;

extern void rt_timer_check(void);

/**
 * This function will init system tick and set it to zero.
 * @ingroup SystemInit
 *
 */
void rt_system_tick_init()
{
	rt_tick = 0;
	rt_passed_second = 0;
}

/**
 * @addtogroup Clock
 */

/*@{*/

/**
 * This function will return current tick from operating system startup
 *
 * @return current tick
 */
rt_tick_t rt_tick_get()
{
	/* return the global tick */
	return rt_tick;
}

/**
 * This function will notify kernel there is one tick passed. Normally, 
 * this function is invoked by clock ISR.
 */
void rt_tick_increase()
{
	struct rt_thread* thread;

	/* increase the global tick */
	++ rt_tick;

	if (rt_tick % RT_TICK_PER_SECOND == 0)
	{
		++rt_passed_second;
	}

	/* check timer  */
	rt_timer_check();

	/* check time slice */
	thread = rt_thread_self();

	-- thread->remaining_tick;
	if (thread->remaining_tick == 0)
	{
		/* change to initialized tick */
		thread->remaining_tick = thread->init_tick;

		/* yield */
	    rt_thread_yield();
	}
}

/**
 * This function will calculate the tick from millisecond.
 *
 * @param ms the specified millisecond
 *
 * @return the calculated tick
 */
rt_tick_t rt_tick_from_millisecond(rt_uint32_t ms)
{
	/* return the calculated tick */
	return RT_TICK_PER_SECOND * (ms / 1000);
}

/*@}*/

