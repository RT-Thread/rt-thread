/*
 * File      : scheduler.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-17     Bernard      the first version
 * 2006-04-28     Bernard      fix the scheduler algorthm
 * 2006-04-30     Bernard      add SCHEDULER_DEBUG
 * 2006-05-27     Bernard      fix the scheduler algorthm for same priority thread
 *                             schedule
 * 2006-06-04     Bernard      rewrite the scheduler algorithm
 * 2006-08-03     Bernard      add hook support
 * 2006-09-05     Bernard      add 32 priority level support
 * 2006-09-24     Bernard      add rt_system_scheduler_start function
 * 2009-09-16     Bernard      fix _rt_scheduler_stack_check
 * 2010-04-11     yi.qiu       add module feature
 * 2010-07-13     Bernard      fix the maximal number of rt_scheduler_lock_nest 
 *                             issue found by kuronca
 * 2010-12-13     Bernard      add defunct list initialization even if not use heap.
 * 2011-05-10     Bernard      clean scheduler debug log.
 */

#include <rtthread.h>
#include <rthw.h>

static rt_int16_t rt_scheduler_lock_nest;
extern volatile rt_uint8_t rt_interrupt_nest;

rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
struct rt_thread *rt_current_thread;

rt_uint8_t rt_current_priority;

#if RT_THREAD_PRIORITY_MAX > 32
/* Maximum priority level, 256 */
rt_uint32_t rt_thread_ready_priority_group;
rt_uint8_t rt_thread_ready_table[32];
#else
/* Maximum priority level, 32 */
rt_uint32_t rt_thread_ready_priority_group;
#endif

rt_list_t rt_thread_defunct;

const rt_uint8_t rt_lowest_bitmap[] =
{
    /* 00 */ 0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 10 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 20 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 30 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 40 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 50 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 60 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 70 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 80 */ 7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 90 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* A0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* B0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* C0 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* D0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* E0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* F0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};

#ifdef RT_USING_HOOK
static void (*rt_scheduler_hook)(struct rt_thread *from, struct rt_thread *to);

/**
 * @addtogroup Hook
 */

/*@{*/

/**
 * This function will set a hook function, which will be invoked when thread
 * switch happens.
 *
 * @param hook the hook function
 */
void rt_scheduler_sethook(void (*hook)(struct rt_thread *from, struct rt_thread *to))
{
	rt_scheduler_hook = hook;
}

/*@}*/
#endif

#ifdef RT_USING_OVERFLOW_CHECK
static void _rt_scheduler_stack_check(struct rt_thread *thread)
{
	RT_ASSERT(thread != RT_NULL);

	if ((rt_uint32_t)thread->sp <= (rt_uint32_t)thread->stack_addr ||
			(rt_uint32_t)thread->sp >
			(rt_uint32_t)thread->stack_addr + (rt_uint32_t)thread->stack_size)
	{
		rt_uint32_t level;

		rt_kprintf("thread:%s stack overflow\n", thread->name);
		#ifdef RT_USING_FINSH
		{
			extern long list_thread(void);
			list_thread();
		}
		#endif
		level = rt_hw_interrupt_disable();
		while (level);
	}
	else if ((rt_uint32_t)thread->sp <= ((rt_uint32_t)thread->stack_addr + 32))
	{
		rt_kprintf("warning: %s stack is close to end of stack address.\n", thread->name);
	}
}
#endif

/**
 * @ingroup SystemInit
 * This function will initialize the system scheduler
 */
void rt_system_scheduler_init(void)
{
	register rt_base_t offset;

	rt_scheduler_lock_nest = 0;

	RT_DEBUG_LOG(RT_DEBUG_SCHEDULER,
		("start scheduler: max priority 0x%02x\n", RT_THREAD_PRIORITY_MAX));

	for (offset = 0; offset < RT_THREAD_PRIORITY_MAX; offset ++)
	{
		rt_list_init(&rt_thread_priority_table[offset]);
	}

	rt_current_priority = RT_THREAD_PRIORITY_MAX - 1;
	rt_current_thread = RT_NULL;

	/* initialize ready priority group */
	rt_thread_ready_priority_group = 0;

#if RT_THREAD_PRIORITY_MAX > 32
	/* initialize ready table */
	rt_memset(rt_thread_ready_table, 0, sizeof(rt_thread_ready_table));
#endif

	/* initialize thread defunct */
	rt_list_init(&rt_thread_defunct);
}

/**
 * @ingroup SystemInit
 * This function will startup scheduler. It will select one thread
 * with the highest priority level, then switch to it.
 */
void rt_system_scheduler_start(void)
{
	register struct rt_thread *to_thread;
	register rt_ubase_t highest_ready_priority;

#if RT_THREAD_PRIORITY_MAX == 8
	highest_ready_priority = rt_lowest_bitmap[rt_thread_ready_priority_group];
#else
	register rt_ubase_t number;
	/* find out the highest priority task */
	if (rt_thread_ready_priority_group & 0xff)
	{
		number = rt_lowest_bitmap[rt_thread_ready_priority_group & 0xff];
	}
	else if (rt_thread_ready_priority_group & 0xff00)
	{
		number = rt_lowest_bitmap[(rt_thread_ready_priority_group >> 8) & 0xff] + 8;
	}
	else if (rt_thread_ready_priority_group & 0xff0000)
	{
		number = rt_lowest_bitmap[(rt_thread_ready_priority_group >> 16) & 0xff] + 16;
	}
	else
	{
		number = rt_lowest_bitmap[(rt_thread_ready_priority_group >> 24) & 0xff] + 24;
	}

#if RT_THREAD_PRIORITY_MAX > 32
	highest_ready_priority = (number << 3) + rt_lowest_bitmap[rt_thread_ready_table[number]];
#else
	highest_ready_priority = number;
#endif
#endif

	/* get switch to thread */
	to_thread = rt_list_entry(rt_thread_priority_table[highest_ready_priority].next,
					struct rt_thread, tlist);

	rt_current_thread = to_thread;

	/* switch to new thread */
	rt_hw_context_switch_to((rt_uint32_t)&to_thread->sp);

	/* never come back */
}

/**
 * @addtogroup Thread
 */

/*@{*/

/**
 * This function will perform one schedule. It will select one thread
 * with the highest priority level, then switch to it.
 */
void rt_schedule(void)
{
	rt_base_t level;
	struct rt_thread *to_thread;
	struct rt_thread *from_thread;

	/* disable interrupt */
	level = rt_hw_interrupt_disable();

	/* check the scheduler is enabled or not */
	if (rt_scheduler_lock_nest == 0)
	{
		register rt_ubase_t highest_ready_priority;

#if RT_THREAD_PRIORITY_MAX == 8
		highest_ready_priority = rt_lowest_bitmap[rt_thread_ready_priority_group];
#else
		register rt_ubase_t number;
		/* find out the highest priority task */
		if (rt_thread_ready_priority_group & 0xff)
		{
			number = rt_lowest_bitmap[rt_thread_ready_priority_group & 0xff];
		}
		else if (rt_thread_ready_priority_group & 0xff00)
		{
			number = rt_lowest_bitmap[(rt_thread_ready_priority_group >> 8) & 0xff] + 8;
		}
		else if (rt_thread_ready_priority_group & 0xff0000)
		{
			number = rt_lowest_bitmap[(rt_thread_ready_priority_group >> 16) & 0xff] + 16;
		}
		else
		{
			number = rt_lowest_bitmap[(rt_thread_ready_priority_group >> 24) & 0xff] + 24;
		}

#if RT_THREAD_PRIORITY_MAX > 32
		highest_ready_priority = (number << 3) + rt_lowest_bitmap[rt_thread_ready_table[number]];
#else
		highest_ready_priority = number;
#endif
#endif
		/* get switch to thread */
		to_thread = rt_list_entry(rt_thread_priority_table[highest_ready_priority].next,
						struct rt_thread, tlist);

		/* if the destination thread is not the same as current thread */
		if (to_thread != rt_current_thread)
		{
			rt_current_priority = highest_ready_priority;
			from_thread = rt_current_thread;
			rt_current_thread = to_thread;

#ifdef RT_USING_MODULE
			rt_module_set((rt_current_thread->module_id != RT_NULL) ? 
				(rt_module_t)rt_current_thread->module_id : RT_NULL);		
#endif

			RT_OBJECT_HOOK_CALL(rt_scheduler_hook, (from_thread, to_thread));

			/* switch to new thread */
			RT_DEBUG_LOG(RT_DEBUG_SCHEDULER,
						("[%d]switch to priority#%d thread:%s\n", rt_interrupt_nest,
						highest_ready_priority, to_thread->name));

#ifdef RT_USING_OVERFLOW_CHECK
			_rt_scheduler_stack_check(to_thread);
#endif

			if (rt_interrupt_nest == 0)
			{
				rt_hw_context_switch((rt_uint32_t)&from_thread->sp, (rt_uint32_t)&to_thread->sp);
			}
			else
			{
				RT_DEBUG_LOG(RT_DEBUG_SCHEDULER, ("switch in interrupt\n"));

				rt_hw_context_switch_interrupt((rt_uint32_t)&from_thread->sp, (rt_uint32_t)&to_thread->sp);
			}
		}
	}

	/* enable interrupt */
	rt_hw_interrupt_enable(level);
}

/*
 * This function will insert a thread to system ready queue. The state of
 * thread will be set as READY and remove from suspend queue.
 *
 * @param thread the thread to be inserted
 * @note Please do not invoke this function in user application.
 */
void rt_schedule_insert_thread(struct rt_thread *thread)
{
	register rt_base_t temp;

	RT_ASSERT(thread != RT_NULL);

	/* disable interrupt */
	temp = rt_hw_interrupt_disable();

	/* change stat */
	thread->stat = RT_THREAD_READY;

	/* insert thread to ready list */
	rt_list_insert_before(&(rt_thread_priority_table[thread->current_priority]), &(thread->tlist));

	/* set priority mask */
#if RT_THREAD_PRIORITY_MAX <= 32
	RT_DEBUG_LOG(RT_DEBUG_SCHEDULER, ("insert thread[%s], the priority: %d\n", 
		thread->name, thread->current_priority));
#else
	RT_DEBUG_LOG(RT_DEBUG_SCHEDULER, ("insert thread[%s], the priority: %d 0x%x %d\n", 
		thread->name, thread->number, thread->number_mask, thread->high_mask));
#endif

#if RT_THREAD_PRIORITY_MAX > 32
	rt_thread_ready_table[thread->number] |= thread->high_mask;
#endif
	rt_thread_ready_priority_group |= thread->number_mask;

	/* enable interrupt */
	rt_hw_interrupt_enable(temp);
}

/*
 * This function will remove a thread from system ready queue.
 *
 * @param thread the thread to be removed
 *
 * @note Please do not invoke this function in user application.
 */
void rt_schedule_remove_thread(struct rt_thread *thread)
{
	register rt_base_t temp;

	RT_ASSERT(thread != RT_NULL);

	/* disable interrupt */
	temp = rt_hw_interrupt_disable();

#if RT_THREAD_PRIORITY_MAX <= 32
	RT_DEBUG_LOG(RT_DEBUG_SCHEDULER, ("remove thread[%s], the priority: %d\n", 
		thread->name, thread->current_priority));
#else
	RT_DEBUG_LOG(RT_DEBUG_SCHEDULER, ("remove thread[%s], the priority: %d 0x%x %d\n", 
		thread->name, thread->number, thread->number_mask, thread->high_mask));
#endif

	/* remove thread from ready list */
	rt_list_remove(&(thread->tlist));
	if (rt_list_isempty(&(rt_thread_priority_table[thread->current_priority])))
	{
#if RT_THREAD_PRIORITY_MAX > 32
		rt_thread_ready_table[thread->number] &= ~thread->high_mask;
		if (rt_thread_ready_table[thread->number] == 0)
		{
			rt_thread_ready_priority_group &= ~thread->number_mask;
		}
#else
		rt_thread_ready_priority_group &= ~thread->number_mask;
#endif
	}

	/* enable interrupt */
	rt_hw_interrupt_enable(temp);
}

/**
 * This function will lock the thread scheduler.
 */
void rt_enter_critical(void)
{
	register rt_base_t level;

	/* disable interrupt */
	level = rt_hw_interrupt_disable();

	/* the maximal number of nest is RT_UINT16_MAX, which is big 
	 * enough and does not check here */
	rt_scheduler_lock_nest ++;

	/* enable interrupt */
	rt_hw_interrupt_enable(level);
}

/**
 * This function will unlock the thread scheduler.
 */
void rt_exit_critical(void)
{
	register rt_base_t level;

	/* disable interrupt */
	level = rt_hw_interrupt_disable();

	rt_scheduler_lock_nest --;

	if (rt_scheduler_lock_nest <= 0)
	{
		rt_scheduler_lock_nest = 0;
		/* enable interrupt */
		rt_hw_interrupt_enable(level);

		rt_schedule();
	}
	else
	{
		/* enable interrupt */
		rt_hw_interrupt_enable(level);
	}
}

/*@}*/

