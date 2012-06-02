/*
 * File      : timer.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-12     Bernard      first version
 * 2006-04-29     Bernard      implement thread timer
 * 2006-06-04     Bernard      implement rt_timer_control
 * 2006-08-10     Bernard      fix the periodic timer bug
 * 2006-09-03     Bernard      implement rt_timer_detach
 * 2009-11-11     LiJin        add soft timer
 * 2010-05-12     Bernard      fix the timer check bug.
 * 2010-11-02     Charlie      re-implement tick overflow issue
 */

#include <rtthread.h>
#include <rthw.h>

/* hard timer list */
static rt_list_t rt_timer_list = RT_LIST_OBJECT_INIT(rt_timer_list);

#ifdef RT_USING_TIMER_SOFT
/* soft timer list */
static rt_list_t rt_soft_timer_list;
static struct rt_thread timer_thread;
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t timer_thread_stack[RT_TIMER_THREAD_STACK_SIZE];
#endif

#ifdef RT_USING_HOOK
extern void (*rt_object_take_hook)(struct rt_object *object);
extern void (*rt_object_put_hook)(struct rt_object *object);
static void (*rt_timer_timeout_hook)(struct rt_timer *timer);

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
void rt_timer_timeout_sethook(void (*hook)(struct rt_timer *timer))
{
	rt_timer_timeout_hook = hook;
}

/*@}*/
#endif

static void _rt_timer_init(rt_timer_t timer,
						   void (*timeout)(void *parameter), void *parameter,
						   rt_tick_t time, rt_uint8_t flag)
{
	/* set flag */
	timer->parent.flag  = flag;

	/* set deactivated */
	timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

	timer->timeout_func = timeout;
	timer->parameter    = parameter;

	timer->timeout_tick = 0;
	timer->init_tick    = time;

	/* initialize timer list */
	rt_list_init(&(timer->list));
}

static rt_tick_t rt_timer_list_next_timeout(rt_list_t *timer_list)
{
	struct rt_timer *timer;

	if (rt_list_isempty(timer_list))
		return RT_TICK_MAX;
	
	timer = rt_list_entry(timer_list->next, struct rt_timer, list);

	return timer->timeout_tick;
}

/**
 * @addtogroup Clock
 */

/*@{*/

/**
 * This function will initialize a timer, normally this function is used to
 * initialize a static timer object.
 *
 * @param timer the static timer object
 * @param name the name of timer
 * @param timeout the timeout function
 * @param parameter the parameter of timeout function
 * @param time the tick of timer
 * @param flag the flag of timer
 */
void rt_timer_init(rt_timer_t timer,
				   const char *name,
				   void (*timeout)(void *parameter), void *parameter,
				   rt_tick_t time, rt_uint8_t flag)
{
	/* timer check */
	RT_ASSERT(timer != RT_NULL);

	/* timer object initialization */
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
rt_timer_t rt_timer_create(const char *name, void (*timeout)(void *parameter),
		void *parameter, rt_tick_t time, rt_uint8_t flag)
{
	struct rt_timer *timer;

	/* allocate a object */
	timer = (struct rt_timer *)rt_object_allocate(RT_Object_Class_Timer, name);
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
 * @return the operation status, RT_EOK on OK, -RT_ERROR on error
 */
rt_err_t rt_timer_start(rt_timer_t timer)
{
	struct rt_timer *t;
	register rt_base_t level;
	rt_list_t *n, *timer_list;

	/* timer check */
	RT_ASSERT(timer != RT_NULL);
	if (timer->parent.flag & RT_TIMER_FLAG_ACTIVATED)
		return -RT_ERROR;

	RT_OBJECT_HOOK_CALL(rt_object_take_hook, (&(timer->parent)));

	/* get timeout tick, the max timeout tick shall not great than RT_TICK_MAX/2 */
	RT_ASSERT(timer->init_tick < RT_TICK_MAX/2);
	timer->timeout_tick = rt_tick_get() + timer->init_tick;

	/* disable interrupt */
	level = rt_hw_interrupt_disable();

#ifdef RT_USING_TIMER_SOFT
	if (timer->parent.flag & RT_TIMER_FLAG_SOFT_TIMER)
	{
		/* insert timer to soft timer list */
		timer_list = &rt_soft_timer_list;
	}
	else
#endif
	{
		/* insert timer to system timer list */
		timer_list = &rt_timer_list;
	}

	for (n = timer_list->next; n != timer_list; n = n->next)
	{
		t = rt_list_entry(n, struct rt_timer, list);
		
		/*
		 * It supposes that the new tick shall less than the half duration of
		 * tick max.
		 */
		if ((t->timeout_tick - timer->timeout_tick) < RT_TICK_MAX/2)
		{
			rt_list_insert_before(n, &(timer->list));
			break;
		}
	}
	/* no found suitable position in timer list */
	if (n == timer_list)
	{
		rt_list_insert_before(n, &(timer->list));
	}

	timer->parent.flag |= RT_TIMER_FLAG_ACTIVATED;

	/* enable interrupt */
	rt_hw_interrupt_enable(level);

#ifdef RT_USING_TIMER_SOFT
	if (timer->parent.flag & RT_TIMER_FLAG_SOFT_TIMER)
	{
		/* check whether timer thread is ready */
		if (timer_thread.stat != RT_THREAD_READY)
		{
			/* resume timer thread to check soft timer */
			rt_thread_resume(&timer_thread);
			rt_schedule();
		}
	}
#endif

	return -RT_EOK;
}

/**
 * This function will stop the timer
 *
 * @param timer the timer to be stopped
 *
 * @return the operation status, RT_EOK on OK, -RT_ERROR on error
 */
rt_err_t rt_timer_stop(rt_timer_t timer)
{
	register rt_base_t level;

	/* timer check */
	RT_ASSERT(timer != RT_NULL);
	if (!(timer->parent.flag & RT_TIMER_FLAG_ACTIVATED))
		return -RT_ERROR;

	RT_OBJECT_HOOK_CALL(rt_object_put_hook, (&(timer->parent)));

	/* disable interrupt */
	level = rt_hw_interrupt_disable();

	/* remove it from timer list */
	rt_list_remove(&(timer->list));

	/* enable interrupt */
	rt_hw_interrupt_enable(level);

	/* change stat */
	timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

	return RT_EOK;
}

/**
 * This function will get or set some options of the timer
 *
 * @param timer the timer to be get or set
 * @param cmd the control command
 * @param arg the argument
 *
 * @return RT_EOK
 */
rt_err_t rt_timer_control(rt_timer_t timer, rt_uint8_t cmd, void *arg)
{
	/* timer check */
	RT_ASSERT(timer != RT_NULL);

	switch (cmd)
	{
	case RT_TIMER_CTRL_GET_TIME:
		*(rt_tick_t *)arg = timer->init_tick;
		break;

	case RT_TIMER_CTRL_SET_TIME:
		timer->init_tick = *(rt_tick_t *)arg;
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
 * @note this function shall be invoked in operating system timer interrupt.
 */
void rt_timer_check(void)
{
	struct rt_timer *t;
	rt_tick_t current_tick;
	register rt_base_t level;

	RT_DEBUG_LOG(RT_DEBUG_TIMER, ("timer check enter\n"));

	current_tick = rt_tick_get();

	/* disable interrupt */
	level = rt_hw_interrupt_disable();

	while (!rt_list_isempty(&rt_timer_list))
	{
		t = rt_list_entry(rt_timer_list.next, struct rt_timer, list);

		/*
		 * It supposes that the new tick shall less than the half duration of
		 * tick max.
		 */
		if ((current_tick - t->timeout_tick) < RT_TICK_MAX/2)
		{
			RT_OBJECT_HOOK_CALL(rt_timer_timeout_hook, (t));

			/* remove timer from timer list firstly */
			rt_list_remove(&(t->list));

			/* call timeout function */
			t->timeout_func(t->parameter);

			/* re-get tick */
			current_tick = rt_tick_get();

			RT_DEBUG_LOG(RT_DEBUG_TIMER, ("current tick: %d\n", current_tick));

			if ((t->parent.flag & RT_TIMER_FLAG_PERIODIC) &&
					(t->parent.flag & RT_TIMER_FLAG_ACTIVATED))
			{
				/* start it */
				t->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
				rt_timer_start(t);
			}
			else
			{
				/* stop timer */
				t->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
			}
		}
		else
			break;
	}

	/* enable interrupt */
	rt_hw_interrupt_enable(level);

	RT_DEBUG_LOG(RT_DEBUG_TIMER, ("timer check leave\n"));
}

/**
 * This function will return the next timeout tick in the system.
 *
 * @return the next timeout tick in the system
 */
rt_tick_t rt_timer_next_timeout_tick(void)
{
	return rt_timer_list_next_timeout(&rt_timer_list);
}

#ifdef RT_USING_TIMER_SOFT
/**
 * This function will check timer list, if a timeout event happens, the
 * corresponding timeout function will be invoked.
 */
void rt_soft_timer_check(void)
{
	rt_tick_t current_tick;
	rt_list_t *n;
	struct rt_timer *t;

	RT_DEBUG_LOG(RT_DEBUG_TIMER, ("software timer check enter\n"));

	current_tick = rt_tick_get();

	for (n = rt_soft_timer_list.next; n != &(rt_soft_timer_list);)
	{
		t = rt_list_entry(n, struct rt_timer, list);

		/*
		 * It supposes that the new tick shall less than the half duration of
		 * tick max.
		 */
		if ((current_tick - t->timeout_tick) < RT_TICK_MAX/2)
		{
			RT_OBJECT_HOOK_CALL(rt_timer_timeout_hook, (t));

			/* move node to the next */
			n = n->next;

			/* remove timer from timer list firstly */
			rt_list_remove(&(t->list));

			/* call timeout function */
			t->timeout_func(t->parameter);

			/* re-get tick */
			current_tick = rt_tick_get();

			RT_DEBUG_LOG(RT_DEBUG_TIMER, ("current tick: %d\n", current_tick));

			if ((t->parent.flag & RT_TIMER_FLAG_PERIODIC) &&
					(t->parent.flag & RT_TIMER_FLAG_ACTIVATED))
			{
				/* start it */
				t->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
				rt_timer_start(t);
			}
			else
			{
				/* stop timer */
				t->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
			}
		}
		else break; /* not check anymore */
	}

	RT_DEBUG_LOG(RT_DEBUG_TIMER, ("software timer check leave\n"));
}

/* system timer thread entry */
static void rt_thread_timer_entry(void *parameter)
{
	rt_tick_t next_timeout;
	
	while (1)
	{
		next_timeout = rt_timer_list_next_timeout(&rt_soft_timer_list);
		if (next_timeout == RT_TICK_MAX)
		{
			rt_thread_suspend(rt_thread_self());
			rt_schedule();
		}
		else
		{
			rt_thread_delay(next_timeout);
		}

		/* lock scheduler */
		rt_enter_critical();
		/* check software timer */
		rt_soft_timer_check();
		/* unlock scheduler */
		rt_exit_critical();
	}
}
#endif

/**
 * @ingroup SystemInit
 *
 * This function will initialize system timer
 *
 * @deprecated since 1.1.0, this function does not need to be invoked
 * in the system initialization.
 */
void rt_system_timer_init(void)
{
}

/**
 * @ingroup SystemInit
 *
 * This function will initialize system timer thread
 */
void rt_system_timer_thread_init(void)
{
#ifdef RT_USING_TIMER_SOFT
	rt_list_init(&rt_soft_timer_list);

	/* start software timer thread */
	rt_thread_init(&timer_thread,
				   "timer",
				   rt_thread_timer_entry, RT_NULL,
				   &timer_thread_stack[0], sizeof(timer_thread_stack),
				   RT_TIMER_THREAD_PRIO, 10);

	/* startup */
	rt_thread_startup(&timer_thread);
#endif
}

/*@}*/
