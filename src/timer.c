/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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
 * 2012-12-15     Bernard      fix the next timeout issue in soft timer
 * 2014-07-12     Bernard      does not lock scheduler when invoking soft-timer
 *                             timeout function.
 * 2021-08-15     supperthomas add the comment
 * 2022-01-07     Gabriel      Moving __on_rt_xxxxx_hook to timer.c
 * 2022-04-19     Stanley      Correct descriptions
 * 2023-09-15     xqyjlj       perf rt_hw_interrupt_disable/enable
 * 2024-01-25     Shell        add RT_TIMER_FLAG_THREAD_TIMER for timer to sync with sched
 * 2024-05-01     wdfk-prog    The rt_timer_check and _soft_timer_check functions are merged
 */

#include <rtthread.h>
#include <rthw.h>

#define DBG_TAG           "kernel.timer"
#define DBG_LVL           DBG_INFO
#include <rtdbg.h>

#ifndef RT_USING_TIMER_ALL_SOFT
/* hard timer list */
static rt_list_t _timer_list[RT_TIMER_SKIP_LIST_LEVEL];
static struct rt_spinlock _htimer_lock;
#endif

#ifdef RT_USING_TIMER_SOFT

#ifndef RT_TIMER_THREAD_STACK_SIZE
#define RT_TIMER_THREAD_STACK_SIZE     512
#endif /* RT_TIMER_THREAD_STACK_SIZE */

#ifndef RT_TIMER_THREAD_PRIO
#define RT_TIMER_THREAD_PRIO           0
#endif /* RT_TIMER_THREAD_PRIO */

/* soft timer list */
static rt_list_t _soft_timer_list[RT_TIMER_SKIP_LIST_LEVEL];
static struct rt_spinlock _stimer_lock;
static struct rt_thread _timer_thread;
static struct rt_semaphore _soft_timer_sem;
rt_align(RT_ALIGN_SIZE)
static rt_uint8_t _timer_thread_stack[RT_TIMER_THREAD_STACK_SIZE];
#endif /* RT_USING_TIMER_SOFT */

#if defined(RT_USING_HOOK) && defined(RT_HOOK_USING_FUNC_PTR)
extern void (*rt_object_take_hook)(struct rt_object *object);
extern void (*rt_object_put_hook)(struct rt_object *object);
static void (*rt_timer_enter_hook)(struct rt_timer *timer);
static void (*rt_timer_exit_hook)(struct rt_timer *timer);

/**
 * @addtogroup Hook
 */

/**@{*/

/**
 * @brief This function will set a hook function on timer,
 *        which will be invoked when enter timer timeout callback function.
 *
 * @param hook is the function point of timer
 */
void rt_timer_enter_sethook(void (*hook)(struct rt_timer *timer))
{
    rt_timer_enter_hook = hook;
}

/**
 * @brief This function will set a hook function, which will be
 *        invoked when exit timer timeout callback function.
 *
 * @param hook is the function point of timer
 */
void rt_timer_exit_sethook(void (*hook)(struct rt_timer *timer))
{
    rt_timer_exit_hook = hook;
}

/**@}*/
#endif /* RT_USING_HOOK */

rt_inline struct rt_spinlock* _timerlock_idx(struct rt_timer *timer)
{
#ifdef RT_USING_TIMER_ALL_SOFT
    return &_stimer_lock;
#else
#ifdef RT_USING_TIMER_SOFT
    if (timer->parent.flag & RT_TIMER_FLAG_SOFT_TIMER)
    {
        return &_stimer_lock;
    }
    else
#endif /* RT_USING_TIMER_SOFT */
    {
        return &_htimer_lock;
    }
#endif
}

/**
 * @brief [internal] The init funtion of timer
 *
 *        The internal called function of rt_timer_init
 *
 * @see rt_timer_init
 *
 * @param timer is timer object
 *
 * @param timeout is the timeout function
 *
 * @param parameter is the parameter of timeout function
 *
 * @param time is the tick of timer
 *
 * @param flag the flag of timer
 */
static void _timer_init(rt_timer_t timer,
                        void (*timeout)(void *parameter),
                        void      *parameter,
                        rt_tick_t  time,
                        rt_uint8_t flag)
{
    int i;

#ifdef RT_USING_TIMER_ALL_SOFT
    flag               |= RT_TIMER_FLAG_SOFT_TIMER;
#endif

    /* set flag */
    timer->parent.flag  = flag;

    /* set deactivated */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    timer->timeout_func = timeout;
    timer->parameter    = parameter;

    timer->timeout_tick = 0;
    timer->init_tick    = time;

    /* initialize timer list */
    for (i = 0; i < RT_TIMER_SKIP_LIST_LEVEL; i++)
    {
        rt_list_init(&(timer->row[i]));
    }
}

/**
 * @brief  Find the next emtpy timer ticks
 *
 * @param timer_list is the array of time list
 *
 * @param timeout_tick is the next timer's ticks
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
static rt_err_t _timer_list_next_timeout(rt_list_t timer_list[], rt_tick_t *timeout_tick)
{
    struct rt_timer *timer;

    if (!rt_list_isempty(&timer_list[RT_TIMER_SKIP_LIST_LEVEL - 1]))
    {
        timer = rt_list_entry(timer_list[RT_TIMER_SKIP_LIST_LEVEL - 1].next,
                              struct rt_timer, row[RT_TIMER_SKIP_LIST_LEVEL - 1]);
        *timeout_tick = timer->timeout_tick;
        return RT_EOK;
    }
    return -RT_ERROR;
}

/**
 * @brief Remove the timer
 *
 * @param timer the point of the timer
 */
rt_inline void _timer_remove(rt_timer_t timer)
{
    int i;

    for (i = 0; i < RT_TIMER_SKIP_LIST_LEVEL; i++)
    {
        rt_list_remove(&timer->row[i]);
    }
}

#if (DBG_LVL == DBG_LOG)
/**
 * @brief The number of timer
 *
 * @param timer the head of timer
 *
 * @return count of timer
 */
static int _timer_count_height(struct rt_timer *timer)
{
    int i, cnt = 0;

    for (i = 0; i < RT_TIMER_SKIP_LIST_LEVEL; i++)
    {
        if (!rt_list_isempty(&timer->row[i]))
            cnt++;
    }
    return cnt;
}
/**
 * @brief dump the all timer information
 *
 * @param timer_heads the head of timer
 */
void rt_timer_dump(rt_list_t timer_heads[])
{
    rt_list_t *list;

    for (list = timer_heads[RT_TIMER_SKIP_LIST_LEVEL - 1].next;
         list != &timer_heads[RT_TIMER_SKIP_LIST_LEVEL - 1];
         list = list->next)
    {
        struct rt_timer *timer = rt_list_entry(list,
                                               struct rt_timer,
                                               row[RT_TIMER_SKIP_LIST_LEVEL - 1]);
        rt_kprintf("%d", _timer_count_height(timer));
    }
    rt_kprintf("\n");
}
#endif /* (DBG_LVL == DBG_LOG) */

/**
 * @addtogroup Clock
 */

/**@{*/

/**
 * @brief This function will initialize a timer
 *        normally this function is used to initialize a static timer object.
 *
 * @param timer is the point of timer
 *
 * @param name is a pointer to the name of the timer
 *
 * @param timeout is the callback of timer
 *
 * @param parameter is the param of the callback
 *
 * @param time is timeout ticks of timer
 *
 *             NOTE: The max timeout tick should be no more than (RT_TICK_MAX/2 - 1).
 *
 * @param flag is the flag of timer
 *
 */
void rt_timer_init(rt_timer_t  timer,
                   const char *name,
                   void (*timeout)(void *parameter),
                   void       *parameter,
                   rt_tick_t   time,
                   rt_uint8_t  flag)
{
    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(timeout != RT_NULL);
    RT_ASSERT(time < RT_TICK_MAX / 2);

    /* timer object initialization */
    rt_object_init(&(timer->parent), RT_Object_Class_Timer, name);

    _timer_init(timer, timeout, parameter, time, flag);
}
RTM_EXPORT(rt_timer_init);

/**
 * @brief This function will detach a timer from timer management.
 *
 * @param timer is the timer to be detached
 *
 * @return the status of detach
 */
rt_err_t rt_timer_detach(rt_timer_t timer)
{
    rt_base_t level;
    struct rt_spinlock *spinlock;

    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(rt_object_get_type(&timer->parent) == RT_Object_Class_Timer);
    RT_ASSERT(rt_object_is_systemobject(&timer->parent));

    spinlock = _timerlock_idx(timer);
    level = rt_spin_lock_irqsave(spinlock);

    _timer_remove(timer);
    /* stop timer */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    rt_spin_unlock_irqrestore(spinlock, level);
    rt_object_detach(&(timer->parent));

    return RT_EOK;
}
RTM_EXPORT(rt_timer_detach);

#ifdef RT_USING_HEAP
/**
 * @brief This function will create a timer
 *
 * @param name is the name of timer
 *
 * @param timeout is the timeout function
 *
 * @param parameter is the parameter of timeout function
 *
 * @param time is timeout ticks of the timer
 *
 *        NOTE: The max timeout tick should be no more than (RT_TICK_MAX/2 - 1).
 *
 * @param flag is the flag of timer. Timer will invoke the timeout function according to the selected values of flag, if one or more of the following flags is set.
 *
 *          RT_TIMER_FLAG_ONE_SHOT          One shot timing
 *          RT_TIMER_FLAG_PERIODIC          Periodic timing
 *
 *          RT_TIMER_FLAG_HARD_TIMER        Hardware timer
 *          RT_TIMER_FLAG_SOFT_TIMER        Software timer
 *          RT_TIMER_FLAG_THREAD_TIMER      Thread timer
 *
 *        NOTE:
 *        You can use multiple values with "|" logical operator.  By default, system will use the RT_TIME_FLAG_HARD_TIMER.
 *
 * @return the created timer object
 */
rt_timer_t rt_timer_create(const char *name,
                           void (*timeout)(void *parameter),
                           void       *parameter,
                           rt_tick_t   time,
                           rt_uint8_t  flag)
{
    struct rt_timer *timer;

    /* parameter check */
    RT_ASSERT(timeout != RT_NULL);
    RT_ASSERT(time < RT_TICK_MAX / 2);

    /* allocate a object */
    timer = (struct rt_timer *)rt_object_allocate(RT_Object_Class_Timer, name);
    if (timer == RT_NULL)
    {
        return RT_NULL;
    }

    _timer_init(timer, timeout, parameter, time, flag);

    return timer;
}
RTM_EXPORT(rt_timer_create);

/**
 * @brief This function will delete a timer and release timer memory
 *
 * @param timer the timer to be deleted
 *
 * @return the operation status, RT_EOK on OK; -RT_ERROR on error
 */
rt_err_t rt_timer_delete(rt_timer_t timer)
{
    rt_base_t level;
    struct rt_spinlock *spinlock;

    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(rt_object_get_type(&timer->parent) == RT_Object_Class_Timer);
    RT_ASSERT(rt_object_is_systemobject(&timer->parent) == RT_FALSE);

    spinlock = _timerlock_idx(timer);

    level = rt_spin_lock_irqsave(spinlock);

    _timer_remove(timer);
    /* stop timer */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
    rt_spin_unlock_irqrestore(spinlock, level);
    rt_object_delete(&(timer->parent));

    return RT_EOK;
}
RTM_EXPORT(rt_timer_delete);
#endif /* RT_USING_HEAP */

/**
 * @brief This function will start the timer
 *
 * @param timer the timer to be started
 *
 * @return the operation status, RT_EOK on OK, -RT_ERROR on error
 */
static rt_err_t _timer_start(rt_list_t *timer_list, rt_timer_t timer)
{
    unsigned int row_lvl;
    rt_list_t *row_head[RT_TIMER_SKIP_LIST_LEVEL];
    unsigned int tst_nr;
    static unsigned int random_nr;

    /* remove timer from list */
    _timer_remove(timer);
    /* change status of timer */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    RT_OBJECT_HOOK_CALL(rt_object_take_hook, (&(timer->parent)));

    timer->timeout_tick = rt_tick_get() + timer->init_tick;

    row_head[0]  = &timer_list[0];
    for (row_lvl = 0; row_lvl < RT_TIMER_SKIP_LIST_LEVEL; row_lvl++)
    {
        for (; row_head[row_lvl] != timer_list[row_lvl].prev;
             row_head[row_lvl]  = row_head[row_lvl]->next)
        {
            struct rt_timer *t;
            rt_list_t *p = row_head[row_lvl]->next;

            /* fix up the entry pointer */
            t = rt_list_entry(p, struct rt_timer, row[row_lvl]);

            /* If we have two timers that timeout at the same time, it's
             * preferred that the timer inserted early get called early.
             * So insert the new timer to the end the the some-timeout timer
             * list.
             */
            if ((t->timeout_tick - timer->timeout_tick) == 0)
            {
                continue;
            }
            else if ((t->timeout_tick - timer->timeout_tick) < RT_TICK_MAX / 2)
            {
                break;
            }
        }
        if (row_lvl != RT_TIMER_SKIP_LIST_LEVEL - 1)
            row_head[row_lvl + 1] = row_head[row_lvl] + 1;
    }

    /* Interestingly, this super simple timer insert counter works very very
     * well on distributing the list height uniformly. By means of "very very
     * well", I mean it beats the randomness of timer->timeout_tick very easily
     * (actually, the timeout_tick is not random and easy to be attacked). */
    random_nr++;
    tst_nr = random_nr;

    rt_list_insert_after(row_head[RT_TIMER_SKIP_LIST_LEVEL - 1],
                         &(timer->row[RT_TIMER_SKIP_LIST_LEVEL - 1]));
    for (row_lvl = 2; row_lvl <= RT_TIMER_SKIP_LIST_LEVEL; row_lvl++)
    {
        if (!(tst_nr & RT_TIMER_SKIP_LIST_MASK))
            rt_list_insert_after(row_head[RT_TIMER_SKIP_LIST_LEVEL - row_lvl],
                                 &(timer->row[RT_TIMER_SKIP_LIST_LEVEL - row_lvl]));
        else
            break;
        /* Shift over the bits we have tested. Works well with 1 bit and 2
         * bits. */
        tst_nr >>= (RT_TIMER_SKIP_LIST_MASK + 1) >> 1;
    }

    timer->parent.flag |= RT_TIMER_FLAG_ACTIVATED;

    return RT_EOK;
}

/**
 * @brief This function will check timer list, if a timeout event happens,
 *        the corresponding timeout function will be invoked.
 *
 * @param timer_list The timer list to check.
 * @param lock The lock for the timer list.
 */
static void _timer_check(rt_list_t *timer_list, struct rt_spinlock *lock)
{
    struct rt_timer *t;
    rt_tick_t current_tick;
    rt_base_t level;
    rt_list_t list;

    level = rt_spin_lock_irqsave(lock);

    current_tick = rt_tick_get();

    rt_list_init(&list);

    while (!rt_list_isempty(&timer_list[RT_TIMER_SKIP_LIST_LEVEL - 1]))
    {
        t = rt_list_entry(timer_list[RT_TIMER_SKIP_LIST_LEVEL - 1].next,
                          struct rt_timer, row[RT_TIMER_SKIP_LIST_LEVEL - 1]);

        /* re-get tick */
        current_tick = rt_tick_get();

        /*
         * It supposes that the new tick shall less than the half duration of
         * tick max.
         */
        if ((current_tick - t->timeout_tick) < RT_TICK_MAX / 2)
        {
            RT_OBJECT_HOOK_CALL(rt_timer_enter_hook, (t));

            /* remove timer from timer list firstly */
            _timer_remove(t);
            if (!(t->parent.flag & RT_TIMER_FLAG_PERIODIC))
            {
                t->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
            }

            /* add timer to temporary list  */
            rt_list_insert_after(&list, &(t->row[RT_TIMER_SKIP_LIST_LEVEL - 1]));

            rt_spin_unlock_irqrestore(lock, level);

            /* call timeout function */
            t->timeout_func(t->parameter);

            RT_OBJECT_HOOK_CALL(rt_timer_exit_hook, (t));

            level = rt_spin_lock_irqsave(lock);

            /* Check whether the timer object is detached or started again */
            if (rt_list_isempty(&list))
            {
                continue;
            }
            rt_list_remove(&(t->row[RT_TIMER_SKIP_LIST_LEVEL - 1]));
            if ((t->parent.flag & RT_TIMER_FLAG_PERIODIC) &&
                (t->parent.flag & RT_TIMER_FLAG_ACTIVATED))
            {
                /* start it */
                t->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
                _timer_start(timer_list, t);
            }
        }
        else break;
    }
    rt_spin_unlock_irqrestore(lock, level);
}

/**
 * @brief This function will start the timer
 *
 * @param timer the timer to be started
 *
 * @return the operation status, RT_EOK on OK, -RT_ERROR on error
 */
rt_err_t rt_timer_start(rt_timer_t timer)
{
    rt_sched_lock_level_t slvl;
    int is_thread_timer = 0;
    struct rt_spinlock *spinlock;
    rt_list_t *timer_list;
    rt_base_t level;
    rt_err_t err;

    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(rt_object_get_type(&timer->parent) == RT_Object_Class_Timer);

#ifdef RT_USING_TIMER_ALL_SOFT
    timer_list = _soft_timer_list;
    spinlock = &_stimer_lock;
#else
#ifdef RT_USING_TIMER_SOFT
    if (timer->parent.flag & RT_TIMER_FLAG_SOFT_TIMER)
    {
        timer_list = _soft_timer_list;
        spinlock = &_stimer_lock;
    }
    else
#endif /* RT_USING_TIMER_SOFT */
    {
        timer_list = _timer_list;
        spinlock = &_htimer_lock;
    }
#endif

    if (timer->parent.flag & RT_TIMER_FLAG_THREAD_TIMER)
    {
        rt_thread_t thread;
        is_thread_timer = 1;
        rt_sched_lock(&slvl);

        thread = rt_container_of(timer, struct rt_thread, thread_timer);
        RT_ASSERT(rt_object_get_type(&thread->parent) == RT_Object_Class_Thread);
        rt_sched_thread_timer_start(thread);
    }

    level = rt_spin_lock_irqsave(spinlock);

    err = _timer_start(timer_list, timer);

    rt_spin_unlock_irqrestore(spinlock, level);

    if (is_thread_timer)
    {
        rt_sched_unlock(slvl);
    }

    return err;
}
RTM_EXPORT(rt_timer_start);

/**
 * @brief This function will stop the timer
 *
 * @param timer the timer to be stopped
 *
 * @return the operation status, RT_EOK on OK, -RT_ERROR on error
 */
rt_err_t rt_timer_stop(rt_timer_t timer)
{
    rt_base_t level;
    struct rt_spinlock *spinlock;

    /* timer check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(rt_object_get_type(&timer->parent) == RT_Object_Class_Timer);

    spinlock = _timerlock_idx(timer);

    level = rt_spin_lock_irqsave(spinlock);

    if (!(timer->parent.flag & RT_TIMER_FLAG_ACTIVATED))
    {
        rt_spin_unlock_irqrestore(spinlock, level);
        return -RT_ERROR;
    }
    RT_OBJECT_HOOK_CALL(rt_object_put_hook, (&(timer->parent)));

    _timer_remove(timer);
    /* change status */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    rt_spin_unlock_irqrestore(spinlock, level);

    return RT_EOK;
}
RTM_EXPORT(rt_timer_stop);

/**
 * @brief This function will get or set some options of the timer
 *
 * @param timer the timer to be get or set
 * @param cmd the control command
 * @param arg the argument
 *
 * @return the statu of control
 */
rt_err_t rt_timer_control(rt_timer_t timer, int cmd, void *arg)
{
    struct rt_spinlock *spinlock;
    rt_base_t level;

    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(rt_object_get_type(&timer->parent) == RT_Object_Class_Timer);

    spinlock = _timerlock_idx(timer);

    level = rt_spin_lock_irqsave(spinlock);
    switch (cmd)
    {
    case RT_TIMER_CTRL_GET_TIME:
        *(rt_tick_t *)arg = timer->init_tick;
        break;

    case RT_TIMER_CTRL_SET_TIME:
        RT_ASSERT((*(rt_tick_t *)arg) < RT_TICK_MAX / 2);
        if (timer->parent.flag & RT_TIMER_FLAG_ACTIVATED)
        {
            _timer_remove(timer);
            timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
        }
        timer->init_tick = *(rt_tick_t *)arg;
        break;

    case RT_TIMER_CTRL_SET_ONESHOT:
        timer->parent.flag &= ~RT_TIMER_FLAG_PERIODIC;
        break;

    case RT_TIMER_CTRL_SET_PERIODIC:
        timer->parent.flag |= RT_TIMER_FLAG_PERIODIC;
        break;

    case RT_TIMER_CTRL_GET_STATE:
        if(timer->parent.flag & RT_TIMER_FLAG_ACTIVATED)
        {
            /*timer is start and run*/
            *(rt_uint32_t *)arg = RT_TIMER_FLAG_ACTIVATED;
        }
        else
        {
            /*timer is stop*/
            *(rt_uint32_t *)arg = RT_TIMER_FLAG_DEACTIVATED;
        }
        break;

    case RT_TIMER_CTRL_GET_REMAIN_TIME:
        *(rt_tick_t *)arg =  timer->timeout_tick;
        break;
    case RT_TIMER_CTRL_GET_FUNC:
        *(void **)arg = (void *)timer->timeout_func;
        break;

    case RT_TIMER_CTRL_SET_FUNC:
        timer->timeout_func = (void (*)(void*))arg;
        break;

    case RT_TIMER_CTRL_GET_PARM:
        *(void **)arg = timer->parameter;
        break;

    case RT_TIMER_CTRL_SET_PARM:
        timer->parameter = arg;
        break;

    default:
        break;
    }
    rt_spin_unlock_irqrestore(spinlock, level);

    return RT_EOK;
}
RTM_EXPORT(rt_timer_control);

/**
 * @brief This function will check timer list, if a timeout event happens,
 *        the corresponding timeout function will be invoked.
 *
 * @note This function shall be invoked in operating system timer interrupt.
 */
void rt_timer_check(void)
{
    RT_ASSERT(rt_interrupt_get_nest() > 0);

#ifdef RT_USING_SMP
    /* Running on core 0 only */
    if (rt_cpu_get_id() != 0)
    {
        return;
    }
#endif

#ifdef RT_USING_TIMER_SOFT
    rt_err_t ret = RT_ERROR;
    rt_tick_t next_timeout;

    ret = _timer_list_next_timeout(_soft_timer_list, &next_timeout);
    if ((ret == RT_EOK) && (next_timeout <= rt_tick_get()))
    {
        rt_sem_release(&_soft_timer_sem);
    }
#endif
#ifndef RT_USING_TIMER_ALL_SOFT
    _timer_check(_timer_list, &_htimer_lock);
#endif
}

/**
 * @brief This function will return the next timeout tick in the system.
 *
 * @return the next timeout tick in the system
 */
rt_tick_t rt_timer_next_timeout_tick(void)
{
    rt_base_t level;
    rt_tick_t htimer_next_timeout = RT_TICK_MAX, stimer_next_timeout = RT_TICK_MAX;

#ifndef RT_USING_TIMER_ALL_SOFT
    level = rt_spin_lock_irqsave(&_htimer_lock);
    _timer_list_next_timeout(_timer_list, &htimer_next_timeout);
    rt_spin_unlock_irqrestore(&_htimer_lock, level);
#endif

#ifdef RT_USING_TIMER_SOFT
    level = rt_spin_lock_irqsave(&_stimer_lock);
    _timer_list_next_timeout(_soft_timer_list, &stimer_next_timeout);
    rt_spin_unlock_irqrestore(&_stimer_lock, level);
#endif

    return htimer_next_timeout < stimer_next_timeout ? htimer_next_timeout : stimer_next_timeout;
}

#ifdef RT_USING_TIMER_SOFT
/**
 * @brief System timer thread entry
 *
 * @param parameter is the arg of the thread
 */
static void _timer_thread_entry(void *parameter)
{
    RT_UNUSED(parameter);

    while (1)
    {
        _timer_check(_soft_timer_list, &_stimer_lock); /* check software timer */
        rt_sem_take(&_soft_timer_sem, RT_WAITING_FOREVER);
    }
}
#endif /* RT_USING_TIMER_SOFT */

/**
 * @ingroup SystemInit
 *
 * @brief This function will initialize system timer
 */
void rt_system_timer_init(void)
{
#ifndef RT_USING_TIMER_ALL_SOFT
    rt_size_t i;

    for (i = 0; i < sizeof(_timer_list) / sizeof(_timer_list[0]); i++)
    {
        rt_list_init(_timer_list + i);
    }

    rt_spin_lock_init(&_htimer_lock);
#endif
}

/**
 * @ingroup SystemInit
 *
 * @brief This function will initialize system timer thread
 */
void rt_system_timer_thread_init(void)
{
#ifdef RT_USING_TIMER_SOFT
    int i;

    for (i = 0;
         i < sizeof(_soft_timer_list) / sizeof(_soft_timer_list[0]);
         i++)
    {
        rt_list_init(_soft_timer_list + i);
    }
    rt_spin_lock_init(&_stimer_lock);
    rt_sem_init(&_soft_timer_sem, "stimer", 0, RT_IPC_FLAG_PRIO);
    rt_sem_control(&_soft_timer_sem, RT_IPC_CMD_SET_VLIMIT, (void*)1);
    /* start software timer thread */
    rt_thread_init(&_timer_thread,
                   "timer",
                   _timer_thread_entry,
                   RT_NULL,
                   &_timer_thread_stack[0],
                   sizeof(_timer_thread_stack),
                   RT_TIMER_THREAD_PRIO,
                   10);

    /* startup */
    rt_thread_startup(&_timer_thread);
#endif /* RT_USING_TIMER_SOFT */
}

/**@}*/
