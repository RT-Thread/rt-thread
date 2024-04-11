/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-17     Bernard      the first version
 * 2006-04-28     Bernard      fix the scheduler algorthm
 * 2006-04-30     Bernard      add SCHEDULER_DEBUG
 * 2006-05-27     Bernard      fix the scheduler algorthm for same priority
 *                             thread schedule
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
 * 2013-12-21     Grissiom     add rt_critical_level
 * 2018-11-22     Jesven       remove the current task from ready queue
 *                             add per cpu ready queue
 *                             add _scheduler_get_highest_priority_thread to find highest priority task
 *                             rt_schedule_insert_thread won't insert current task to ready queue
 *                             in smp version, rt_hw_context_switch_interrupt maybe switch to
 *                             new task directly
 * 2022-01-07     Gabriel      Moving __on_rt_xxxxx_hook to scheduler.c
 * 2023-03-27     rose_man     Split into scheduler upc and scheduler_mp.c
 * 2023-10-17     ChuShicheng  Modify the timing of clearing RT_THREAD_STAT_YIELD flag bits
 */

#include <rtthread.h>
#include <rthw.h>

#define DBG_TAG           "kernel.scheduler"
#define DBG_LVL           DBG_INFO
#include <rtdbg.h>

rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
rt_uint32_t rt_thread_ready_priority_group;
#if RT_THREAD_PRIORITY_MAX > 32
/* Maximum priority level, 256 */
rt_uint8_t rt_thread_ready_table[32];
#endif /* RT_THREAD_PRIORITY_MAX > 32 */

extern volatile rt_uint8_t rt_interrupt_nest;
static rt_int16_t rt_scheduler_lock_nest;
struct rt_thread *rt_current_thread = RT_NULL;
rt_uint8_t rt_current_priority;

#if defined(RT_USING_HOOK) && defined(RT_HOOK_USING_FUNC_PTR)
static void (*rt_scheduler_hook)(struct rt_thread *from, struct rt_thread *to);
static void (*rt_scheduler_switch_hook)(struct rt_thread *tid);

/**
 * @addtogroup Hook
 */

/**@{*/

/**
 * @brief This function will set a hook function, which will be invoked when thread
 *        switch happens.
 *
 * @param hook is the hook function.
 */
void rt_scheduler_sethook(void (*hook)(struct rt_thread *from, struct rt_thread *to))
{
    rt_scheduler_hook = hook;
}

/**
 * @brief This function will set a hook function, which will be invoked when context
 *        switch happens.
 *
 * @param hook is the hook function.
 */
void rt_scheduler_switch_sethook(void (*hook)(struct rt_thread *tid))
{
    rt_scheduler_switch_hook = hook;
}

/**@}*/
#endif /* RT_USING_HOOK */

static struct rt_thread* _scheduler_get_highest_priority_thread(rt_ubase_t *highest_prio)
{
    struct rt_thread *highest_priority_thread;
    rt_ubase_t highest_ready_priority;

#if RT_THREAD_PRIORITY_MAX > 32
    rt_ubase_t number;

    number = __rt_ffs(rt_thread_ready_priority_group) - 1;
    highest_ready_priority = (number << 3) + __rt_ffs(rt_thread_ready_table[number]) - 1;
#else
    highest_ready_priority = __rt_ffs(rt_thread_ready_priority_group) - 1;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */

    /* get highest ready priority thread */
    highest_priority_thread = RT_THREAD_LIST_NODE_ENTRY(rt_thread_priority_table[highest_ready_priority].next);

    *highest_prio = highest_ready_priority;

    return highest_priority_thread;
}

rt_err_t rt_sched_lock(rt_sched_lock_level_t *plvl)
{
    rt_base_t level;
    if (!plvl)
        return -RT_EINVAL;

    level = rt_hw_interrupt_disable();
    *plvl = level;

    return RT_EOK;
}

rt_err_t rt_sched_unlock(rt_sched_lock_level_t level)
{
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t rt_sched_unlock_n_resched(rt_sched_lock_level_t level)
{
    if (rt_thread_self())
    {
        /* if scheduler is available */
        rt_schedule();
    }
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

/**
 * @brief This function will initialize the system scheduler.
 */
void rt_system_scheduler_init(void)
{
    rt_base_t offset;
    rt_scheduler_lock_nest = 0;

    LOG_D("start scheduler: max priority 0x%02x",
          RT_THREAD_PRIORITY_MAX);

    for (offset = 0; offset < RT_THREAD_PRIORITY_MAX; offset ++)
    {
        rt_list_init(&rt_thread_priority_table[offset]);
    }

    /* initialize ready priority group */
    rt_thread_ready_priority_group = 0;

#if RT_THREAD_PRIORITY_MAX > 32
    /* initialize ready table */
    rt_memset(rt_thread_ready_table, 0, sizeof(rt_thread_ready_table));
#endif /* RT_THREAD_PRIORITY_MAX > 32 */
}

/**
 * @brief This function will startup the scheduler. It will select one thread
 *        with the highest priority level, then switch to it.
 */
void rt_system_scheduler_start(void)
{
    struct rt_thread *to_thread;
    rt_ubase_t highest_ready_priority;

    to_thread = _scheduler_get_highest_priority_thread(&highest_ready_priority);

    rt_current_thread = to_thread;

    rt_sched_remove_thread(to_thread);
    RT_SCHED_CTX(to_thread).stat = RT_THREAD_RUNNING;

    /* switch to new thread */

    rt_hw_context_switch_to((rt_ubase_t)&to_thread->sp);

    /* never come back */
}

/**
 * @addtogroup Thread
 * @cond
 */

/**@{*/

/**
 * @brief This function will perform scheduling once. It will select one thread
 *        with the highest priority, and switch to it immediately.
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
        rt_ubase_t highest_ready_priority;

        if (rt_thread_ready_priority_group != 0)
        {
            /* need_insert_from_thread: need to insert from_thread to ready queue */
            int need_insert_from_thread = 0;

            to_thread = _scheduler_get_highest_priority_thread(&highest_ready_priority);

            if ((RT_SCHED_CTX(rt_current_thread).stat & RT_THREAD_STAT_MASK) == RT_THREAD_RUNNING)
            {
                if (RT_SCHED_PRIV(rt_current_thread).current_priority < highest_ready_priority)
                {
                    to_thread = rt_current_thread;
                }
                else if (RT_SCHED_PRIV(rt_current_thread).current_priority == highest_ready_priority && (RT_SCHED_CTX(rt_current_thread).stat & RT_THREAD_STAT_YIELD_MASK) == 0)
                {
                    to_thread = rt_current_thread;
                }
                else
                {
                    need_insert_from_thread = 1;
                }
            }

            if (to_thread != rt_current_thread)
            {
                /* if the destination thread is not the same as current thread */
                rt_current_priority = (rt_uint8_t)highest_ready_priority;
                from_thread         = rt_current_thread;
                rt_current_thread   = to_thread;

                RT_OBJECT_HOOK_CALL(rt_scheduler_hook, (from_thread, to_thread));

                if (need_insert_from_thread)
                {
                    rt_sched_insert_thread(from_thread);
                }

                if ((RT_SCHED_CTX(from_thread).stat & RT_THREAD_STAT_YIELD_MASK) != 0)
                {
                    RT_SCHED_CTX(from_thread).stat &= ~RT_THREAD_STAT_YIELD_MASK;
                }

                rt_sched_remove_thread(to_thread);
                RT_SCHED_CTX(to_thread).stat = RT_THREAD_RUNNING | (RT_SCHED_CTX(to_thread).stat & ~RT_THREAD_STAT_MASK);

                /* switch to new thread */
                LOG_D("[%d]switch to priority#%d "
                         "thread:%.*s(sp:0x%08x), "
                         "from thread:%.*s(sp: 0x%08x)",
                         rt_interrupt_nest, highest_ready_priority,
                         RT_NAME_MAX, to_thread->parent.name, to_thread->sp,
                         RT_NAME_MAX, from_thread->parent.name, from_thread->sp);

                RT_SCHEDULER_STACK_CHECK(to_thread);

                if (rt_interrupt_nest == 0)
                {
                    extern void rt_thread_handle_sig(rt_bool_t clean_state);

                    RT_OBJECT_HOOK_CALL(rt_scheduler_switch_hook, (from_thread));

                    rt_hw_context_switch((rt_ubase_t)&from_thread->sp,
                            (rt_ubase_t)&to_thread->sp);

                    /* enable interrupt */
                    rt_hw_interrupt_enable(level);

#ifdef RT_USING_SIGNALS
                    /* check stat of thread for signal */
                    level = rt_hw_interrupt_disable();
                    if (RT_SCHED_CTX(rt_current_thread).stat & RT_THREAD_STAT_SIGNAL_PENDING)
                    {
                        extern void rt_thread_handle_sig(rt_bool_t clean_state);

                        RT_SCHED_CTX(rt_current_thread).stat &= ~RT_THREAD_STAT_SIGNAL_PENDING;

                        rt_hw_interrupt_enable(level);

                        /* check signal status */
                        rt_thread_handle_sig(RT_TRUE);
                    }
                    else
                    {
                        rt_hw_interrupt_enable(level);
                    }
#endif /* RT_USING_SIGNALS */
                    goto __exit;
                }
                else
                {
                    LOG_D("switch in interrupt");

                    rt_hw_context_switch_interrupt((rt_ubase_t)&from_thread->sp,
                            (rt_ubase_t)&to_thread->sp, from_thread, to_thread);
                }
            }
            else
            {
                rt_sched_remove_thread(rt_current_thread);
                RT_SCHED_CTX(rt_current_thread).stat = RT_THREAD_RUNNING | (RT_SCHED_CTX(rt_current_thread).stat & ~RT_THREAD_STAT_MASK);
            }
        }
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

__exit:
    return;
}

/* Normally, there isn't anyone racing with us so this operation is lockless */
void rt_sched_thread_startup(struct rt_thread *thread)
{
#if RT_THREAD_PRIORITY_MAX > 32
    RT_SCHED_PRIV(thread).number = RT_SCHED_PRIV(thread).current_priority >> 3;            /* 5bit */
    RT_SCHED_PRIV(thread).number_mask = 1L << RT_SCHED_PRIV(thread).number;
    RT_SCHED_PRIV(thread).high_mask = 1L << (RT_SCHED_PRIV(thread).current_priority & 0x07);  /* 3bit */
#else
    RT_SCHED_PRIV(thread).number_mask = 1L << RT_SCHED_PRIV(thread).current_priority;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */

    /* change thread stat, so we can resume it */
    RT_SCHED_CTX(thread).stat = RT_THREAD_SUSPEND;
}

void rt_sched_thread_init_priv(struct rt_thread *thread, rt_uint32_t tick, rt_uint8_t priority)
{
    rt_list_init(&RT_THREAD_LIST_NODE(thread));

    /* priority init */
    RT_ASSERT(priority < RT_THREAD_PRIORITY_MAX);
    RT_SCHED_PRIV(thread).init_priority    = priority;
    RT_SCHED_PRIV(thread).current_priority = priority;

    /* don't add to scheduler queue as init thread */
    RT_SCHED_PRIV(thread).number_mask = 0;
#if RT_THREAD_PRIORITY_MAX > 32
    RT_SCHED_PRIV(thread).number = 0;
    RT_SCHED_PRIV(thread).high_mask = 0;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */

    /* tick init */
    RT_SCHED_PRIV(thread).init_tick = tick;
    RT_SCHED_PRIV(thread).remaining_tick = tick;
}

/**
 * @brief This function will insert a thread to the system ready queue. The state of
 *        thread will be set as READY and the thread will be removed from suspend queue.
 *
 * @param thread is the thread to be inserted.
 *
 * @note  Please do not invoke this function in user application.
 */
void rt_sched_insert_thread(struct rt_thread *thread)
{
    rt_base_t level;

    RT_ASSERT(thread != RT_NULL);

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /* it's current thread, it should be RUNNING thread */
    if (thread == rt_current_thread)
    {
        RT_SCHED_CTX(thread).stat = RT_THREAD_RUNNING | (RT_SCHED_CTX(thread).stat & ~RT_THREAD_STAT_MASK);
        goto __exit;
    }

    /* READY thread, insert to ready queue */
    RT_SCHED_CTX(thread).stat = RT_THREAD_READY | (RT_SCHED_CTX(thread).stat & ~RT_THREAD_STAT_MASK);
    /* there is no time slices left(YIELD), inserting thread before ready list*/
    if((RT_SCHED_CTX(thread).stat & RT_THREAD_STAT_YIELD_MASK) != 0)
    {
        rt_list_insert_before(&(rt_thread_priority_table[RT_SCHED_PRIV(thread).current_priority]),
                              &RT_THREAD_LIST_NODE(thread));
    }
    /* there are some time slices left, inserting thread after ready list to schedule it firstly at next time*/
    else
    {
        rt_list_insert_after(&(rt_thread_priority_table[RT_SCHED_PRIV(thread).current_priority]),
                              &RT_THREAD_LIST_NODE(thread));
    }

    LOG_D("insert thread[%.*s], the priority: %d",
          RT_NAME_MAX, thread->parent.name, RT_SCHED_PRIV(rt_current_thread).current_priority);

    /* set priority mask */
#if RT_THREAD_PRIORITY_MAX > 32
    rt_thread_ready_table[RT_SCHED_PRIV(thread).number] |= RT_SCHED_PRIV(thread).high_mask;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */
    rt_thread_ready_priority_group |= RT_SCHED_PRIV(thread).number_mask;

__exit:
    /* enable interrupt */
    rt_hw_interrupt_enable(level);
}

/**
 * @brief This function will remove a thread from system ready queue.
 *
 * @param thread is the thread to be removed.
 *
 * @note  Please do not invoke this function in user application.
 */
void rt_sched_remove_thread(struct rt_thread *thread)
{
    rt_base_t level;

    RT_ASSERT(thread != RT_NULL);

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    LOG_D("remove thread[%.*s], the priority: %d",
          RT_NAME_MAX, thread->parent.name,
          RT_SCHED_PRIV(rt_current_thread).current_priority);

    /* remove thread from ready list */
    rt_list_remove(&RT_THREAD_LIST_NODE(thread));
    if (rt_list_isempty(&(rt_thread_priority_table[RT_SCHED_PRIV(thread).current_priority])))
    {
#if RT_THREAD_PRIORITY_MAX > 32
        rt_thread_ready_table[RT_SCHED_PRIV(thread).number] &= ~RT_SCHED_PRIV(thread).high_mask;
        if (rt_thread_ready_table[RT_SCHED_PRIV(thread).number] == 0)
        {
            rt_thread_ready_priority_group &= ~RT_SCHED_PRIV(thread).number_mask;
        }
#else
        rt_thread_ready_priority_group &= ~RT_SCHED_PRIV(thread).number_mask;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);
}

#ifdef RT_USING_DEBUG

static volatile int _critical_error_occurred = 0;

void rt_exit_critical_safe(rt_base_t critical_level)
{
    rt_base_t level;
    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    if (!_critical_error_occurred)
    {
        if (critical_level != rt_scheduler_lock_nest)
        {
            int dummy = 1;
            _critical_error_occurred = 1;

            rt_kprintf("%s: un-compatible critical level\n" \
                       "\tCurrent %d\n\tCaller %d\n",
                       __func__, rt_scheduler_lock_nest,
                       critical_level);
            rt_backtrace();

            while (dummy) ;
        }
    }
    rt_hw_interrupt_enable(level);

    rt_exit_critical();
}

#else

void rt_exit_critical_safe(rt_base_t critical_level)
{
    rt_exit_critical();
}

#endif
RTM_EXPORT(rt_exit_critical_safe);

/**
 * @brief This function will lock the thread scheduler.
 */
rt_base_t rt_enter_critical(void)
{
    rt_base_t level;
    rt_base_t critical_level;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /*
     * the maximal number of nest is RT_UINT16_MAX, which is big
     * enough and does not check here
     */
    rt_scheduler_lock_nest ++;
    critical_level = rt_scheduler_lock_nest;

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    return critical_level;
}
RTM_EXPORT(rt_enter_critical);

/**
 * @brief This function will unlock the thread scheduler.
 */
void rt_exit_critical(void)
{
    rt_base_t level;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    rt_scheduler_lock_nest --;
    if (rt_scheduler_lock_nest <= 0)
    {
        rt_scheduler_lock_nest = 0;
        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        if (rt_current_thread)
        {
            /* if scheduler is started, do a schedule */
            rt_schedule();
        }
    }
    else
    {
        /* enable interrupt */
        rt_hw_interrupt_enable(level);
    }
}
RTM_EXPORT(rt_exit_critical);

/**
 * @brief Get the scheduler lock level.
 *
 * @return the level of the scheduler lock. 0 means unlocked.
 */
rt_uint16_t rt_critical_level(void)
{
    return rt_scheduler_lock_nest;
}
RTM_EXPORT(rt_critical_level);

rt_err_t rt_sched_thread_bind_cpu(struct rt_thread *thread, int cpu)
{
    return -RT_EINVAL;
}

/**@}*/
/**@endcond*/
