/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-28     Bernard      first version
 * 2006-04-29     Bernard      implement thread timer
 * 2006-04-30     Bernard      added THREAD_DEBUG
 * 2006-05-27     Bernard      fixed the rt_thread_yield bug
 * 2006-06-03     Bernard      fixed the thread timer init bug
 * 2006-08-10     Bernard      fixed the timer bug in thread_sleep
 * 2006-09-03     Bernard      changed rt_timer_delete to rt_timer_detach
 * 2006-09-03     Bernard      implement rt_thread_detach
 * 2008-02-16     Bernard      fixed the rt_thread_timeout bug
 * 2010-03-21     Bernard      change the errno of rt_thread_delay/sleep to
 *                             RT_EOK.
 * 2010-11-10     Bernard      add cleanup callback function in thread exit.
 * 2011-09-01     Bernard      fixed rt_thread_exit issue when the current
 *                             thread preempted, which reported by Jiaxing Lee.
 * 2011-09-08     Bernard      fixed the scheduling issue in rt_thread_startup.
 * 2012-12-29     Bernard      fixed compiling warning.
 * 2016-08-09     ArdaFu       add thread suspend and resume hook.
 * 2017-04-10     armink       fixed the rt_thread_delete and rt_thread_detach
 *                             bug when thread has not startup.
 * 2018-11-22     Jesven       yield is same to rt_schedule
 *                             add support for tasks bound to cpu
 * 2021-02-24     Meco Man     rearrange rt_thread_control() - schedule the thread when close it
 * 2021-11-15     THEWON       Remove duplicate work between idle and _thread_exit
 * 2021-12-27     Meco Man     remove .init_priority
 * 2022-01-07     Gabriel      Moving __on_rt_xxxxx_hook to thread.c
 * 2022-01-24     THEWON       let _thread_sleep return thread->error when using signal
 * 2022-10-15     Bernard      add nested mutex feature
 * 2023-09-15     xqyjlj       perf rt_hw_interrupt_disable/enable
 * 2023-12-10     xqyjlj       fix thread_exit/detach/delete
 *                             fix rt_thread_delay
 */

#include <rthw.h>
#include <rtthread.h>
#include <stddef.h>

#define DBG_TAG           "kernel.thread"
#define DBG_LVL           DBG_INFO
#include <rtdbg.h>

#if defined(RT_USING_HOOK) && defined(RT_HOOK_USING_FUNC_PTR)
static void (*rt_thread_suspend_hook)(rt_thread_t thread);
static void (*rt_thread_resume_hook) (rt_thread_t thread);

/**
 * @brief   This function sets a hook function when the system suspend a thread.
 *
 * @note    The hook function must be simple and never be blocked or suspend.
 *
 * @param   hook is the specified hook function.
 */
void rt_thread_suspend_sethook(void (*hook)(rt_thread_t thread))
{
    rt_thread_suspend_hook = hook;
}

/**
 * @brief   This function sets a hook function when the system resume a thread.
 *
 * @note    The hook function must be simple and never be blocked or suspend.
 *
 * @param   hook is the specified hook function.
 */
void rt_thread_resume_sethook(void (*hook)(rt_thread_t thread))
{
    rt_thread_resume_hook = hook;
}

RT_OBJECT_HOOKLIST_DEFINE(rt_thread_inited);
#endif /* defined(RT_USING_HOOK) && defined(RT_HOOK_USING_FUNC_PTR) */

static void _thread_exit(void)
{
    struct rt_thread *thread;
    rt_sched_lock_level_t slvl;
    rt_base_t critical_level;

    /* get current thread */
    thread = rt_thread_self();

    critical_level = rt_enter_critical();
    rt_sched_lock(&slvl);

    /* remove from schedule */
    rt_sched_remove_thread(thread);

    /* remove it from timer list */
    rt_timer_detach(&thread->thread_timer);

    /* change stat */
    rt_sched_thread_close(thread);

    rt_sched_unlock(slvl);

    /* insert to defunct thread list */
    rt_thread_defunct_enqueue(thread);

    rt_exit_critical_safe(critical_level);

    /* switch to next task */
    rt_schedule();
}

/**
 * @brief   This function is the timeout function for thread, normally which is invoked
 *          when thread is timeout to wait some resource.
 *
 * @param   parameter is the parameter of thread timeout function
 */
static void _thread_timeout(void *parameter)
{
    struct rt_thread *thread;
    rt_sched_lock_level_t slvl;

    thread = (struct rt_thread *)parameter;

    /* parameter check */
    RT_ASSERT(thread != RT_NULL);
    RT_ASSERT(rt_object_get_type((rt_object_t)thread) == RT_Object_Class_Thread);

    rt_sched_lock(&slvl);

    /**
     * resume of the thread and stop of the thread timer should be an atomic
     * operation. So we don't expected that thread had resumed.
     */
    RT_ASSERT(rt_sched_thread_is_suspended(thread));

    /* set error number */
    thread->error = -RT_ETIMEOUT;

    /* remove from suspend list */
    rt_list_remove(&RT_THREAD_LIST_NODE(thread));
    /* insert to schedule ready list */
    rt_sched_insert_thread(thread);
    /* do schedule and release the scheduler lock */
    rt_sched_unlock_n_resched(slvl);
}

#ifdef RT_USING_MUTEX
static void _thread_detach_from_mutex(rt_thread_t thread)
{
    rt_list_t *node;
    rt_list_t *tmp_list;
    struct rt_mutex *mutex;
    rt_base_t level;

    level = rt_spin_lock_irqsave(&thread->spinlock);

    /* check if thread is waiting on a mutex */
    if ((thread->pending_object) &&
        (rt_object_get_type(thread->pending_object) == RT_Object_Class_Mutex))
    {
        /* remove it from its waiting list */
        struct rt_mutex *mutex = (struct rt_mutex*)thread->pending_object;
        rt_mutex_drop_thread(mutex, thread);
        thread->pending_object = RT_NULL;
    }

    /* free taken mutex after detaching from waiting, so we don't lost mutex just got */
    rt_list_for_each_safe(node, tmp_list, &(thread->taken_object_list))
    {
        mutex = rt_list_entry(node, struct rt_mutex, taken_list);
        rt_mutex_release(mutex);
    }

    rt_spin_unlock_irqrestore(&thread->spinlock, level);
}

#else

static void _thread_detach_from_mutex(rt_thread_t thread) {}
#endif

static rt_err_t _thread_init(struct rt_thread *thread,
                             const char       *name,
                             void (*entry)(void *parameter),
                             void             *parameter,
                             void             *stack_start,
                             rt_uint32_t       stack_size,
                             rt_uint8_t        priority,
                             rt_uint32_t       tick)
{
    RT_UNUSED(name);

    rt_sched_thread_init_ctx(thread, tick, priority);

#ifdef RT_USING_MEM_PROTECTION
    thread->mem_regions = RT_NULL;
#endif

#ifdef RT_USING_SMART
    thread->wakeup_handle.func = RT_NULL;
#endif

    thread->entry = (void *)entry;
    thread->parameter = parameter;

    /* stack init */
    thread->stack_addr = stack_start;
    thread->stack_size = stack_size;

    /* init thread stack */
    rt_memset(thread->stack_addr, '#', thread->stack_size);
#ifdef RT_USING_HW_STACK_GUARD
    rt_hw_stack_guard_init(thread);
#endif
#ifdef ARCH_CPU_STACK_GROWS_UPWARD
    thread->sp = (void *)rt_hw_stack_init(thread->entry, thread->parameter,
                                          (void *)((char *)thread->stack_addr),
                                          (void *)_thread_exit);
#else
    thread->sp = (void *)rt_hw_stack_init(thread->entry, thread->parameter,
                                          (rt_uint8_t *)((char *)thread->stack_addr + thread->stack_size - sizeof(rt_ubase_t)),
                                          (void *)_thread_exit);
#endif /* ARCH_CPU_STACK_GROWS_UPWARD */

#ifdef RT_USING_MUTEX
    rt_list_init(&thread->taken_object_list);
    thread->pending_object = RT_NULL;
#endif

#ifdef RT_USING_EVENT
    thread->event_set = 0;
    thread->event_info = 0;
#endif /* RT_USING_EVENT */

    /* error and flags */
    thread->error = RT_EOK;

    /* lock init */
#ifdef RT_USING_SMP
    rt_atomic_store(&thread->cpus_lock_nest, 0);
#endif

    /* initialize cleanup function and user data */
    thread->cleanup   = 0;
    thread->user_data = 0;

    /* initialize thread timer */
    rt_timer_init(&(thread->thread_timer),
                  thread->parent.name,
                  _thread_timeout,
                  thread,
                  0,
                  RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_THREAD_TIMER);

    /* initialize signal */
#ifdef RT_USING_SIGNALS
    thread->sig_mask    = 0x00;
    thread->sig_pending = 0x00;

#ifndef RT_USING_SMP
    thread->sig_ret     = RT_NULL;
#endif /* RT_USING_SMP */
    thread->sig_vectors = RT_NULL;
    thread->si_list     = RT_NULL;
#endif /* RT_USING_SIGNALS */

#ifdef RT_USING_SMART
    thread->tid_ref_count = 0;
    thread->lwp = RT_NULL;
    thread->susp_recycler = RT_NULL;
    thread->robust_list = RT_NULL;
    rt_list_init(&(thread->sibling));

    /* lwp thread-signal init */
    rt_memset(&thread->signal.sigset_mask, 0, sizeof(lwp_sigset_t));
    rt_memset(&thread->signal.sig_queue.sigset_pending, 0, sizeof(lwp_sigset_t));
    rt_list_init(&thread->signal.sig_queue.siginfo_list);

    rt_memset(&thread->user_ctx, 0, sizeof thread->user_ctx);

    /* initialize user_time and system_time */
    thread->user_time = 0;
    thread->system_time = 0;
#endif

#ifdef RT_USING_CPU_USAGE
    thread->duration_tick = 0;
#endif /* RT_USING_CPU_USAGE */

#ifdef RT_USING_PTHREADS
    thread->pthread_data = RT_NULL;
#endif /* RT_USING_PTHREADS */

#ifdef RT_USING_MODULE
    thread->parent.module_id = 0;
#endif /* RT_USING_MODULE */

    rt_spin_lock_init(&thread->spinlock);

    RT_OBJECT_HOOKLIST_CALL(rt_thread_inited, (thread));

    return RT_EOK;
}

/**
 * @addtogroup Thread
 */

/**@{*/

/**
 * @brief   This function will initialize a thread. It's used to initialize a
 *          static thread object.
 *
 * @param   thread is the static thread object.
 *
 * @param   name is the name of thread, which shall be unique.
 *
 * @param   entry is the entry function of thread.
 *
 * @param   parameter is the parameter of thread enter function.
 *
 * @param   stack_start is the start address of thread stack.
 *
 * @param   stack_size is the size of thread stack.
 *
 * @param   priority is the priority of thread.
 *
 * @param   tick is the time slice if there are same priority thread.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_thread_init(struct rt_thread *thread,
                        const char       *name,
                        void (*entry)(void *parameter),
                        void             *parameter,
                        void             *stack_start,
                        rt_uint32_t       stack_size,
                        rt_uint8_t        priority,
                        rt_uint32_t       tick)
{
    /* parameter check */
    RT_ASSERT(thread != RT_NULL);
    RT_ASSERT(stack_start != RT_NULL);
    RT_ASSERT(tick != 0);

    /* initialize thread object */
    rt_object_init((rt_object_t)thread, RT_Object_Class_Thread, name);

    return _thread_init(thread,
                        name,
                        entry,
                        parameter,
                        stack_start,
                        stack_size,
                        priority,
                        tick);
}
RTM_EXPORT(rt_thread_init);

/**
 * @brief   This function will return self thread object.
 *
 * @return  The self thread object.
 */
rt_thread_t rt_thread_self(void)
{
#ifdef RT_USING_SMP
    rt_base_t lock;
    rt_thread_t self;

    lock = rt_hw_local_irq_disable();
    self = rt_cpu_self()->current_thread;
    rt_hw_local_irq_enable(lock);
    return self;
#else
    extern rt_thread_t rt_current_thread;

    return rt_current_thread;
#endif /* RT_USING_SMP */
}
RTM_EXPORT(rt_thread_self);

/**
 * @brief   This function will start a thread and put it to system ready queue.
 *
 * @param   thread is the thread to be started.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_thread_startup(rt_thread_t thread)
{
    /* parameter check */
    RT_ASSERT(thread != RT_NULL);
    RT_ASSERT((RT_SCHED_CTX(thread).stat & RT_THREAD_STAT_MASK) == RT_THREAD_INIT);
    RT_ASSERT(rt_object_get_type((rt_object_t)thread) == RT_Object_Class_Thread);

    LOG_D("startup a thread:%s with priority:%d",
          thread->parent.name, thread->current_priority);

    /* calculate priority attribute and reset thread stat to suspend */
    rt_sched_thread_startup(thread);

    /* resume and do a schedule if scheduler is available */
    rt_thread_resume(thread);

    return RT_EOK;
}
RTM_EXPORT(rt_thread_startup);

static rt_err_t _thread_detach(rt_thread_t thread);

/**
 * @brief   This function will detach a thread. The thread object will be removed from
 *          thread queue and detached/deleted from the system object management.
 *
 * @param   thread is the thread to be deleted.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_thread_detach(rt_thread_t thread)
{
    /* parameter check */
    RT_ASSERT(thread != RT_NULL);
    RT_ASSERT(rt_object_get_type((rt_object_t)thread) == RT_Object_Class_Thread);
    RT_ASSERT(rt_object_is_systemobject((rt_object_t)thread));

    return _thread_detach(thread);
}
RTM_EXPORT(rt_thread_detach);

static rt_err_t _thread_detach(rt_thread_t thread)
{
    rt_err_t error;
    rt_sched_lock_level_t slvl;
    rt_uint8_t thread_status;
    rt_base_t critical_level;

    /**
     * forbid scheduling on current core before returning since current thread
     * may be detached from scheduler.
     */
    critical_level = rt_enter_critical();

    /* before checking status of scheduler */
    rt_sched_lock(&slvl);

    /* check if thread is already closed */
    thread_status = rt_sched_thread_get_stat(thread);
    if (thread_status != RT_THREAD_CLOSE)
    {
        if (thread_status != RT_THREAD_INIT)
        {
            /* remove from schedule */
            rt_sched_remove_thread(thread);
        }

        /* release thread timer */
        rt_timer_detach(&(thread->thread_timer));

        /* change stat */
        rt_sched_thread_close(thread);

        /* scheduler works are done */
        rt_sched_unlock(slvl);

        _thread_detach_from_mutex(thread);

        /* insert to defunct thread list */
        rt_thread_defunct_enqueue(thread);

        error = RT_EOK;
    }
    else
    {
        rt_sched_unlock(slvl);

        /* already closed */
        error = RT_EOK;
    }

    rt_exit_critical_safe(critical_level);
    return error;
}

#ifdef RT_USING_HEAP
/**
 * @brief   This function will create a thread object and allocate thread object memory.
 *          and stack.
 *
 * @param   name is the name of thread, which shall be unique.
 *
 * @param   entry is the entry function of thread.
 *
 * @param   parameter is the parameter of thread enter function.
 *
 * @param   stack_size is the size of thread stack.
 *
 * @param   priority is the priority of thread.
 *
 * @param   tick is the time slice if there are same priority thread.
 *
 * @return  If the return value is a rt_thread structure pointer, the function is successfully executed.
 *          If the return value is RT_NULL, it means this operation failed.
 */
rt_thread_t rt_thread_create(const char *name,
                             void (*entry)(void *parameter),
                             void       *parameter,
                             rt_uint32_t stack_size,
                             rt_uint8_t  priority,
                             rt_uint32_t tick)
{
    /* parameter check */
    RT_ASSERT(tick != 0);

    struct rt_thread *thread;
    void *stack_start;

    thread = (struct rt_thread *)rt_object_allocate(RT_Object_Class_Thread,
                                                    name);
    if (thread == RT_NULL)
        return RT_NULL;

    stack_start = (void *)RT_KERNEL_MALLOC(stack_size);
    if (stack_start == RT_NULL)
    {
        /* allocate stack failure */
        rt_object_delete((rt_object_t)thread);

        return RT_NULL;
    }

    _thread_init(thread,
                 name,
                 entry,
                 parameter,
                 stack_start,
                 stack_size,
                 priority,
                 tick);

    return thread;
}
RTM_EXPORT(rt_thread_create);

/**
 * @brief   This function will delete a thread. The thread object will be removed from
 *          thread queue and deleted from system object management in the idle thread.
 *
 * @param   thread is the thread to be deleted.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_thread_delete(rt_thread_t thread)
{
    /* parameter check */
    RT_ASSERT(thread != RT_NULL);
    RT_ASSERT(rt_object_get_type((rt_object_t)thread) == RT_Object_Class_Thread);
    RT_ASSERT(rt_object_is_systemobject((rt_object_t)thread) == RT_FALSE);

    return _thread_detach(thread);
}
RTM_EXPORT(rt_thread_delete);
#endif /* RT_USING_HEAP */

/**
 * @brief   This function will let current thread yield processor, and scheduler will
 *          choose the highest thread to run. After yield processor, the current thread
 *          is still in READY state.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_thread_yield(void)
{
    rt_sched_lock_level_t slvl;
    rt_sched_lock(&slvl);

    rt_sched_thread_yield(rt_thread_self());

    rt_sched_unlock_n_resched(slvl);

    return RT_EOK;
}
RTM_EXPORT(rt_thread_yield);

/**
 * @brief   This function will let current thread sleep for some ticks. Change current thread state to suspend,
 *          when the thread timer reaches the tick value, scheduler will awaken this thread.
 *
 * @param   tick is the sleep ticks.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
static rt_err_t _thread_sleep(rt_tick_t tick)
{
    struct rt_thread *thread;
    rt_base_t critical_level;
    int err;

    if (tick == 0)
    {
        return -RT_EINVAL;
    }

    /* set to current thread */
    thread = rt_thread_self();
    RT_ASSERT(thread != RT_NULL);
    RT_ASSERT(rt_object_get_type((rt_object_t)thread) == RT_Object_Class_Thread);

    /* current context checking */
    RT_DEBUG_SCHEDULER_AVAILABLE(RT_TRUE);

    /* reset thread error */
    thread->error = RT_EOK;

    /* lock scheduler since current thread may be suspended */
    critical_level = rt_enter_critical();

    /* suspend thread */
    err = rt_thread_suspend_with_flag(thread, RT_INTERRUPTIBLE);

    /* reset the timeout of thread timer and start it */
    if (err == RT_EOK)
    {
        rt_timer_control(&(thread->thread_timer), RT_TIMER_CTRL_SET_TIME, &tick);
        rt_timer_start(&(thread->thread_timer));

        thread->error = -RT_EINTR;

        /* notify a pending rescheduling */
        rt_schedule();

        /* exit critical and do a rescheduling */
        rt_exit_critical_safe(critical_level);

        /* clear error number of this thread to RT_EOK */
        if (thread->error == -RT_ETIMEOUT)
            thread->error = RT_EOK;
    }
    else
    {
        rt_exit_critical_safe(critical_level);
    }

    return err;
}

/**
 * @brief   This function will let current thread delay for some ticks.
 *
 * @param   tick is the delay ticks.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_thread_delay(rt_tick_t tick)
{
    return _thread_sleep(tick);
}
RTM_EXPORT(rt_thread_delay);

/**
 * @brief   This function will let current thread delay until (*tick + inc_tick).
 *
 * @param   tick is the tick of last wakeup.
 *
 * @param   inc_tick is the increment tick.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_thread_delay_until(rt_tick_t *tick, rt_tick_t inc_tick)
{
    struct rt_thread *thread;
    rt_tick_t cur_tick;
    rt_base_t critical_level;

    RT_ASSERT(tick != RT_NULL);

    /* set to current thread */
    thread = rt_thread_self();
    RT_ASSERT(thread != RT_NULL);
    RT_ASSERT(rt_object_get_type((rt_object_t)thread) == RT_Object_Class_Thread);

    /* reset thread error */
    thread->error = RT_EOK;

    /* disable interrupt */
    critical_level = rt_enter_critical();

    cur_tick = rt_tick_get();
    if (cur_tick - *tick < inc_tick)
    {
        rt_tick_t left_tick;

        *tick += inc_tick;
        left_tick = *tick - cur_tick;

        /* suspend thread */
        rt_thread_suspend_with_flag(thread, RT_UNINTERRUPTIBLE);

        /* reset the timeout of thread timer and start it */
        rt_timer_control(&(thread->thread_timer), RT_TIMER_CTRL_SET_TIME, &left_tick);
        rt_timer_start(&(thread->thread_timer));

        rt_exit_critical_safe(critical_level);

        rt_schedule();

        /* clear error number of this thread to RT_EOK */
        if (thread->error == -RT_ETIMEOUT)
        {
            thread->error = RT_EOK;
        }
    }
    else
    {
        *tick = cur_tick;
        rt_exit_critical_safe(critical_level);
    }

    return thread->error;
}
RTM_EXPORT(rt_thread_delay_until);

/**
 * @brief   This function will let current thread delay for some milliseconds.
 *
 * @param   ms is the delay ms time.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_thread_mdelay(rt_int32_t ms)
{
    rt_tick_t tick;

    tick = rt_tick_from_millisecond(ms);

    return _thread_sleep(tick);
}
RTM_EXPORT(rt_thread_mdelay);

#ifdef RT_USING_SMP
#endif

/**
 * @brief   This function will control thread behaviors according to control command.
 *
 * @param   thread is the specified thread to be controlled.
 *
 * @param   cmd is the control command, which includes.
 *
 *              RT_THREAD_CTRL_CHANGE_PRIORITY for changing priority level of thread.
 *
 *              RT_THREAD_CTRL_STARTUP for starting a thread.
 *
 *              RT_THREAD_CTRL_CLOSE for delete a thread.
 *
 *              RT_THREAD_CTRL_BIND_CPU for bind the thread to a CPU.
 *
 * @param   arg is the argument of control command.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_thread_control(rt_thread_t thread, int cmd, void *arg)
{
    /* parameter check */
    RT_ASSERT(thread != RT_NULL);
    RT_ASSERT(rt_object_get_type((rt_object_t)thread) == RT_Object_Class_Thread);

    switch (cmd)
    {
        case RT_THREAD_CTRL_CHANGE_PRIORITY:
        {
            rt_err_t error;
            rt_sched_lock_level_t slvl;
            rt_sched_lock(&slvl);
            error = rt_sched_thread_change_priority(thread, *(rt_uint8_t *)arg);
            rt_sched_unlock(slvl);
            return error;
        }

        case RT_THREAD_CTRL_STARTUP:
        {
            return rt_thread_startup(thread);
        }

        case RT_THREAD_CTRL_CLOSE:
        {
            rt_err_t rt_err = -RT_EINVAL;

            if (rt_object_is_systemobject((rt_object_t)thread) == RT_TRUE)
            {
                rt_err = rt_thread_detach(thread);
            }
    #ifdef RT_USING_HEAP
            else
            {
                rt_err = rt_thread_delete(thread);
            }
    #endif /* RT_USING_HEAP */
            rt_schedule();
            return rt_err;
        }

        case RT_THREAD_CTRL_BIND_CPU:
        {
            rt_uint8_t cpu;

            cpu = (rt_uint8_t)(size_t)arg;
            return rt_sched_thread_bind_cpu(thread, cpu);
        }

    default:
        break;
    }

    return RT_EOK;
}
RTM_EXPORT(rt_thread_control);

#ifdef RT_USING_SMART
#include <lwp_signal.h>
#endif

static void _thread_set_suspend_state(struct rt_thread *thread, int suspend_flag)
{
    rt_uint8_t stat = RT_THREAD_SUSPEND_UNINTERRUPTIBLE;

    RT_ASSERT(thread != RT_NULL);
    switch (suspend_flag)
    {
    case RT_INTERRUPTIBLE:
        stat = RT_THREAD_SUSPEND_INTERRUPTIBLE;
        break;
    case RT_KILLABLE:
        stat = RT_THREAD_SUSPEND_KILLABLE;
        break;
    case RT_UNINTERRUPTIBLE:
        stat = RT_THREAD_SUSPEND_UNINTERRUPTIBLE;
        break;
    default:
        RT_ASSERT(0);
        break;
    }
    RT_SCHED_CTX(thread).stat = stat | (RT_SCHED_CTX(thread).stat & ~RT_THREAD_STAT_MASK);
}

/**
 * @brief   This function will suspend the specified thread and change it to suspend state.
 *
 * @note    This function ONLY can suspend current thread itself.
 *              rt_thread_suspend(rt_thread_self());
 *
 *          Do not use the rt_thread_suspend to suspend other threads. You have no way of knowing what code a
 *          thread is executing when you suspend it. If you suspend a thread while sharing a resouce with
 *          other threads and occupying this resouce, starvation can occur very easily.
 *
 * @param   thread the thread to be suspended.
 * @param   susp_list the list thread enqueued to. RT_NULL if no list.
 * @param   ipc_flags is a flag for the thread object to be suspended. It determines how the thread is suspended.
 *          The flag can be ONE of the following values:
 *              RT_IPC_FLAG_PRIO          The pending threads will queue in order of priority.
 *              RT_IPC_FLAG_FIFO          The pending threads will queue in the first-in-first-out method
 *                                         (also known as first-come-first-served (FCFS) scheduling strategy).
 *          NOTE: RT_IPC_FLAG_FIFO is a non-real-time scheduling mode. It is strongly recommended to use
 *          RT_IPC_FLAG_PRIO to ensure the thread is real-time UNLESS your applications concern about
 *          the first-in-first-out principle, and you clearly understand that all threads involved in
 *          this semaphore will become non-real-time threads.
 * @param   suspend_flag status flag of the thread to be suspended.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_thread_suspend_to_list(rt_thread_t thread, rt_list_t *susp_list, int ipc_flags, int suspend_flag)
{
    rt_base_t stat;
    rt_sched_lock_level_t slvl;

    /* parameter check */
    RT_ASSERT(thread != RT_NULL);
    RT_ASSERT(rt_object_get_type((rt_object_t)thread) == RT_Object_Class_Thread);
    RT_ASSERT(thread == rt_thread_self());

    LOG_D("thread suspend:  %s", thread->parent.name);

    rt_sched_lock(&slvl);

    stat = rt_sched_thread_get_stat(thread);
    if ((stat != RT_THREAD_READY) && (stat != RT_THREAD_RUNNING))
    {
        LOG_D("thread suspend: thread disorder, 0x%2x", thread->stat);
        rt_sched_unlock(slvl);
        return -RT_ERROR;
    }

    if (stat == RT_THREAD_RUNNING)
    {
        /* not suspend running status thread on other core */
        RT_ASSERT(thread == rt_thread_self());
    }

#ifdef RT_USING_SMART
    rt_sched_unlock(slvl);

    /* check pending signals for thread before suspend */
    if (lwp_thread_signal_suspend_check(thread, suspend_flag) == 0)
    {
        /* not to suspend */
        return -RT_EINTR;
    }

    rt_sched_lock(&slvl);
    if (stat == RT_THREAD_READY)
    {
        stat = rt_sched_thread_get_stat(thread);

        if (stat != RT_THREAD_READY)
        {
            /* status updated while we check for signal */
            rt_sched_unlock(slvl);
            return -RT_ERROR;
        }
    }
#endif

    /* change thread stat */
    rt_sched_remove_thread(thread);
    _thread_set_suspend_state(thread, suspend_flag);

    if (susp_list)
    {
        /**
         * enqueue thread on the push list before leaving critical region of
         * scheduler, so we won't miss notification of async events.
         */
        rt_susp_list_enqueue(susp_list, thread, ipc_flags);
    }

    /* stop thread timer anyway */
    rt_sched_thread_timer_stop(thread);

    rt_sched_unlock(slvl);

    RT_OBJECT_HOOK_CALL(rt_thread_suspend_hook, (thread));
    return RT_EOK;
}
RTM_EXPORT(rt_thread_suspend_to_list);

/**
 * @brief   This function will suspend the specified thread and change it to suspend state.
 *
 * @note    This function ONLY can suspend current thread itself.
 *              rt_thread_suspend(rt_thread_self());
 *
 *          Do not use the rt_thread_suspend to suspend other threads. You have no way of knowing what code a
 *          thread is executing when you suspend it. If you suspend a thread while sharing a resouce with
 *          other threads and occupying this resouce, starvation can occur very easily.
 *
 * @param   thread the thread to be suspended.
 * @param   suspend_flag status flag of the thread to be suspended.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_thread_suspend_with_flag(rt_thread_t thread, int suspend_flag)
{
    return rt_thread_suspend_to_list(thread, RT_NULL, 0, suspend_flag);
}
RTM_EXPORT(rt_thread_suspend_with_flag);

rt_err_t rt_thread_suspend(rt_thread_t thread)
{
    return rt_thread_suspend_with_flag(thread, RT_UNINTERRUPTIBLE);
}
RTM_EXPORT(rt_thread_suspend);

/**
 * @brief   This function will resume a thread and put it to system ready queue.
 *
 * @param   thread is the thread to be resumed.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_thread_resume(rt_thread_t thread)
{
    rt_sched_lock_level_t slvl;
    rt_err_t error;

    /* parameter check */
    RT_ASSERT(thread != RT_NULL);
    RT_ASSERT(rt_object_get_type((rt_object_t)thread) == RT_Object_Class_Thread);

    LOG_D("thread resume: %s", thread->parent.name);

    rt_sched_lock(&slvl);

    error = rt_sched_thread_ready(thread);

    if (!error)
    {
        error = rt_sched_unlock_n_resched(slvl);
    }
    else
    {
        rt_sched_unlock(slvl);
    }

    RT_OBJECT_HOOK_CALL(rt_thread_resume_hook, (thread));

    return error;
}
RTM_EXPORT(rt_thread_resume);

#ifdef RT_USING_SMART
/**
 * This function will wakeup a thread with customized operation.
 *
 * @param thread the thread to be resumed
 *
 * @return the operation status, RT_EOK on OK, -RT_ERROR on error
 */
rt_err_t rt_thread_wakeup(rt_thread_t thread)
{
    rt_sched_lock_level_t slvl;
    rt_err_t ret;
    rt_wakeup_func_t func = RT_NULL;

    RT_ASSERT(thread != RT_NULL);
    RT_ASSERT(rt_object_get_type((rt_object_t)thread) == RT_Object_Class_Thread);

    rt_sched_lock(&slvl);
    func = thread->wakeup_handle.func;
    thread->wakeup_handle.func = RT_NULL;
    rt_sched_unlock(slvl);

    if (func)
    {
        ret = func(thread->wakeup_handle.user_data, thread);
    }
    else
    {
        ret = rt_thread_resume(thread);
    }
    return ret;
}
RTM_EXPORT(rt_thread_wakeup);

void rt_thread_wakeup_set(struct rt_thread *thread, rt_wakeup_func_t func, void* user_data)
{
    rt_sched_lock_level_t slvl;

    RT_ASSERT(thread != RT_NULL);
    RT_ASSERT(rt_object_get_type((rt_object_t)thread) == RT_Object_Class_Thread);

    rt_sched_lock(&slvl);
    thread->wakeup_handle.func = func;
    thread->wakeup_handle.user_data = user_data;
    rt_sched_unlock(slvl);
}
RTM_EXPORT(rt_thread_wakeup_set);
#endif
/**
 * @brief   This function will find the specified thread.
 *
 * @note    Please don't invoke this function in interrupt status.
 *
 * @param   name is the name of thread finding.
 *
 * @return  If the return value is a rt_thread structure pointer, the function is successfully executed.
 *          If the return value is RT_NULL, it means this operation failed.
 */
rt_thread_t rt_thread_find(char *name)
{
    return (rt_thread_t)rt_object_find(name, RT_Object_Class_Thread);
}

RTM_EXPORT(rt_thread_find);

/**
 * @brief   This function will return the name of the specified thread
 *
 * @note    Please don't invoke this function in interrupt status
 *
 * @param   thread the thread to retrieve thread name
 * @param   name buffer to store the thread name string
 * @param   name_size maximum size of the buffer to store the thread name
 *
 * @return  If the return value is RT_EOK, the function is successfully executed
 *          If the return value is -RT_EINVAL, it means this operation failed
 */
rt_err_t rt_thread_get_name(rt_thread_t thread, char *name, rt_uint8_t name_size)
{
    return (thread == RT_NULL) ? -RT_EINVAL : rt_object_get_name(&thread->parent, name, name_size);
}
RTM_EXPORT(rt_thread_get_name);

/**@}*/
