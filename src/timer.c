/*
 * File      : timer.c
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
 * 2006-04-29     Bernard      implement thread timer
 * 2006-06-04     Bernard      implement rt_timer_control
 * 2006-08-10     Bernard      fix the periodic timer bug
 * 2006-09-03     Bernard      implement rt_timer_detach
 */

#include <rtthread.h>
#include <rthw.h>

#include "kservice.h"

/* #define TIMER_DEBUG */
static rt_list_t rt_timer_list;

#ifdef RT_USING_HOOK
extern void (*rt_object_take_hook)(struct rt_object* object);
extern void (*rt_object_put_hook)(struct rt_object* object);
static void (*rt_timer_timeout_hook)(struct rt_timer* timer);

/**
 * @addtogroup Hook
 */
/*@{*/

/**
 * This function will set a hook function, which will be invoked when timer
 * is timeout.
 * 
 * @param hook the hook function
 */
void rt_timer_timeout_sethook(void (*hook)(struct rt_timer* timer))
{
	rt_timer_timeout_hook = hook;
}

/*@}*/
#endif

/**
 * @ingroup SystemInit
 *
 * This function will init system timer
 *
 */
void rt_system_timer_init()
{
	rt_list_init(&rt_timer_list);
}

static void _rt_timer_init(rt_timer_t timer, 
	void (*timeout)(void* parameter), void* parameter, 
	rt_tick_t time, rt_uint8_t flag)
{
	/* set flag */
	timer->parent.flag 	= flag;

	/* set deactivated */
	timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

	timer->timeout_func = timeout;
	timer->parameter   	= parameter;

	timer->timeout_tick	= 0;
	timer->init_tick 	= time;

	/* init timer list */
	rt_list_init(&(timer->list));
}

/**
 * @addtogroup Clock
 */
/*@{*/

/**
 * This function will init a timer, normally this function is used to initialize 
 * a static timer object.
 *
 * @param timer the static timer object
 * @param name the name of timer
 * @param timeout the timeout function
 * @param parameter the parameter of timeout function
 * @param time the tick of timer
 * @param flag the flag of timer
 */
void rt_timer_init(rt_timer_t timer, 
	const char* name, 
	void (*timeout)(void* parameter), void* parameter, 
	rt_tick_t time, rt_uint8_t flag)
{
	/* timer check */
	RT_ASSERT(timer != RT_NULL);

	/* timer object init */
	rt_object_init((rt_object_t)timer, RT_Object_Class_Timer, name);

	_rt_timer_init(timer, timeout, parameter, time, flag);
}

/** 
 * This function will detach a timer from timer management.
 *
 * @param timer the static timer object
 * 
 * @return the operation status, RT_EOK on OK; RT_ERROR on error
 */
rt_err_t rt_timer_detach(rt_timer_t timer)
{
	register rt_base_t level;
	
	/* timer check */
	RT_ASSERT(timer != RT_NULL);

	/* disable interrupt */
	level = rt_hw_interrupt_disable();

	/* remove it from timer list */
	rt_list_remove(&(timer->list));

	/* enable interrupt */
	rt_hw_interrupt_enable(level);

	rt_object_detach((rt_object_t)timer);

	return -RT_EOK;
}

#ifdef RT_USING_HEAP
/**
 * This function will create a timer
 *
 * @param name the name of timer
 * @param timeout the timeout function
 * @param parameter the parameter of timeout function
 * @param time the tick of timer
 * @param flag the flag of timer
 *
 * @return the created timer object
 */
rt_timer_t rt_timer_create(const char* name, void (*timeout)(void* parameter), void* parameter, rt_tick_t time, rt_uint8_t flag)
{
	struct rt_timer* timer;

	/* allocate a object */
	timer = (struct rt_timer*)rt_object_allocate(RT_Object_Class_Timer, name);
	if (timer == RT_NULL)
	{
		return RT_NULL;
	}

	_rt_timer_init(timer, timeout, parameter, time, flag);

	return timer;
}

/**
 * This function will delete a timer and release timer memory
 *
 * @param timer the timer to be deleted
 *
 * @return the operation status, RT_EOK on OK; RT_ERROR on error
 *
 */
rt_err_t rt_timer_delete(rt_timer_t timer)
{
	register rt_base_t level;
	
	/* timer check */
	RT_ASSERT(timer != RT_NULL);

	/* disable interrupt */
	level = rt_hw_interrupt_disable();

	/* remove it from timer list */
	rt_list_remove(&(timer->list));

	/* enable interrupt */
	rt_hw_interrupt_enable(level);

	rt_object_delete((rt_object_t)timer);

	return -RT_EOK;
}
#endif

/**
 * This function will start the timer
 *
 * @param timer the timer to be started
 *
 * @return the operation status, RT_EOK on OK; RT_ERROR on error
 *
 */
rt_err_t rt_timer_start(rt_timer_t timer)
{
	rt_list_t *n;
	struct rt_timer* t;
	register rt_base_t level;

	/* timer check */
	RT_ASSERT(timer != RT_NULL);
	if (timer->parent.flag & RT_TIMER_FLAG_ACTIVATED) return -RT_ERROR;

#ifdef RT_USING_HOOK
	if (rt_object_take_hook != RT_NULL) rt_object_take_hook(&(timer->parent));
#endif

	timer->timeout_tick = rt_tick_get() + timer->init_tick;

	/* disable interrupt */
	level = rt_hw_interrupt_disable();

	/* insert timer to system timer list */	
	for (n = rt_timer_list.next; n != &rt_timer_list; n = n->next)
	{
		t = rt_list_entry(n, struct rt_timer, list);
		if (t->timeout_tick > timer->timeout_tick)
		{
			rt_list_insert_before(n, &(timer->list));
			break;
		}
	}

	/* no found suitable position in timer list */
	if (n == &rt_timer_list)
	{
		rt_list_insert_before(n, &(timer->list));
	}

	timer->parent.flag |= RT_TIMER_FLAG_ACTIVATED;

	/* enable interrupt */
	rt_hw_interrupt_enable(level);

	return -RT_EOK;
}

/**
 * This function will stop the timer
 *
 * @param timer the timer to be stopped
 *
 * @return the operation status, RT_EOK on OK; RT_ERROR on error
 *
 */
rt_err_t rt_timer_stop(rt_timer_t timer)
{
	register rt_base_t level;

	/* timer check */
	RT_ASSERT(timer != RT_NULL);
	if(!(timer->parent.flag & RT_TIMER_FLAG_ACTIVATED)) return -RT_ERROR;

#ifdef RT_USING_HOOK
	if (rt_object_put_hook != RT_NULL) rt_object_put_hook(&(timer->parent));
#endif

	/* disable interrupt */
	level = rt_hw_interrupt_disable();

	/* remove it from timer list */
	rt_list_remove(&(timer->list));

	/* enable interrupt */
	rt_hw_interrupt_enable(level);

	return RT_EOK;
}

/**
 * This function will get or set some options of the timer
 *
 * @param timer the timer to be get or set
 * @param cmd the control command
 * @param arg the argument
 *
 * @return the operation status, RT_EOK on OK; RT_ERROR on error
 *
 */
rt_err_t rt_timer_control(rt_timer_t timer, rt_uint8_t cmd, void* arg)
{
	/* timer check */
	RT_ASSERT(timer != RT_NULL);

	switch (cmd)
	{
	case RT_TIMER_CTRL_GET_TIME:
		*(rt_tick_t*)arg = timer->init_tick;
		break;

	case RT_TIMER_CTRL_SET_TIME:
		timer->init_tick = *(rt_tick_t*)arg;
		break;

	case RT_TIMER_CTRL_SET_ONESHOT:
		timer->parent.flag &= ~(1 << RT_TIMER_FLAG_PERIODIC);
		break;

	case RT_TIMER_CTRL_SET_PERIODIC:
		timer->parent.flag |= (1 << RT_TIMER_FLAG_PERIODIC);
		break;
	}

	return RT_EOK;
}

/**
 * This function will check timer list, if a timeout event happens, the 
 * corresponding timeout function will be invoked.
 *
 */
void rt_timer_check()
{
	rt_tick_t current_tick;
	rt_list_t *n;
	struct rt_timer *t;
	register rt_base_t level;

#ifdef TIMER_DEBUG
	rt_kprintf("timer check enter\n");
#endif

	current_tick = rt_tick_get();

	/* disable interrupt */
	level = rt_hw_interrupt_disable();

	for (n = rt_timer_list.next; n != &(rt_timer_list); )
	{
		t = rt_list_entry(n, struct rt_timer, list);
		if (current_tick >= t->timeout_tick)
		{
#ifdef RT_USING_HOOK
			if (rt_timer_timeout_hook != RT_NULL) rt_timer_timeout_hook(t);
#endif
			/* move node to the next */
			n = n->next;

			/* remove timer from timer list firstly */
			rt_list_remove(&(t->list));

			/* call timeout function */
			t->timeout_func(t->parameter);

			/* reget tick */
			current_tick = rt_tick_get();

#ifdef TIMER_DEBUG
			rt_kprintf("current tick: %d\n", current_tick);
#endif

			/* change timer state */
			t->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

			if (t->parent.flag & RT_TIMER_FLAG_PERIODIC)
			{
				/* start it */
				rt_timer_start(t);
			}
		}
		else break;
	}

	/* enable interrupt */
	rt_hw_interrupt_enable(level);

#ifdef TIMER_DEBUG
	rt_kprintf("timer check leave\n");
#endif
}

/*@}*/
