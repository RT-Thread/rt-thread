/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
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
 */

#include <rtthread.h>
#include <rthw.h>

#define DBG_TAG           "kernel.timer"
#define DBG_LVL           DBG_INFO
#include <rtdbg.h>

/* hard timer list */
static rt_list_t _timer_list[RT_TIMER_SKIP_LIST_LEVEL];
static struct rt_spinlock _hard_spinlock;

#ifdef RT_USING_TIMER_SOFT

#define RT_SOFT_TIMER_IDLE              1
#define RT_SOFT_TIMER_BUSY              0

#ifndef RT_TIMER_THREAD_STACK_SIZE
#define RT_TIMER_THREAD_STACK_SIZE     512
#endif /* RT_TIMER_THREAD_STACK_SIZE */

#ifndef RT_TIMER_THREAD_PRIO
#define RT_TIMER_THREAD_PRIO           0
#endif /* RT_TIMER_THREAD_PRIO */

/* soft timer status */
static rt_uint8_t _soft_timer_status = RT_SOFT_TIMER_IDLE;
/* soft timer list */
static rt_list_t _soft_timer_list[RT_TIMER_SKIP_LIST_LEVEL];
static struct rt_spinlock _soft_spinlock;
static struct rt_thread _timer_thread;
static struct rt_semaphore _soft_timer_sem;
rt_align(RT_ALIGN_SIZE)
static rt_uint8_t _timer_thread_stack[RT_TIMER_THREAD_STACK_SIZE];
#endif /* RT_USING_TIMER_SOFT */

#ifndef __on_rt_object_take_hook
    #define __on_rt_object_take_hook(parent)        __ON_HOOK_ARGS(rt_object_take_hook, (parent))
#endif
#ifndef __on_rt_object_put_hook
    #define __on_rt_object_put_hook(parent)         __ON_HOOK_ARGS(rt_object_put_hook, (parent))
#endif
#ifndef __on_rt_timer_enter_hook
    #define __on_rt_timer_enter_hook(t)             __ON_HOOK_ARGS(rt_timer_enter_hook, (t))
#endif
#ifndef __on_rt_timer_exit_hook
    #define __on_rt_timer_exit_hook(t)              __ON_HOOK_ARGS(rt_timer_exit_hook, (t))
#endif

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

#ifdef RT_USING_TIMER_SOFT
    if (timer->parent.flag & RT_TIMER_FLAG_SOFT_TIMER)
    {
        spinlock = &_soft_spinlock;
    }
    else
#endif /* RT_USING_TIMER_SOFT */
    {
        spinlock = &_hard_spinlock;
    }

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

#ifdef RT_USING_TIMER_SOFT
    if (timer->parent.flag & RT_TIMER_FLAG_SOFT_TIMER)
    {
        spinlock = &_soft_spinlock;
    }
    else
#endif /* RT_USING_TIMER_SOFT */
    {
        spinlock = &_hard_spinlock;
    }

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
 * @brief This function will start the timer
 *
 * @param timer the timer to be started
 *
 * @return the operation status, RT_EOK on OK, -RT_ERROR on error
 */
rt_err_t rt_timer_start(rt_timer_t timer)
{
    struct rt_spinlock *spinlock;
    rt_list_t *timer_list;
    rt_base_t level;
    rt_err_t err;

    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(rt_object_get_type(&timer->parent) == RT_Object_Class_Timer);

#ifdef RT_USING_TIMER_SOFT
    if (timer->parent.flag & RT_TIMER_FLAG_SOFT_TIMER)
    {
        timer_list = _soft_timer_list;
        spinlock = &_soft_spinlock;
    }
    else
#endif /* RT_USING_TIMER_SOFT */
    {
        timer_list = _timer_list;
        spinlock = &_hard_spinlock;
    }

    level = rt_spin_lock_irqsave(spinlock);

    err = _timer_start(timer_list, timer);

#ifdef RT_USING_TIMER_SOFT
    if (err == RT_EOK)
    {
        if (timer->parent.flag & RT_TIMER_FLAG_SOFT_TIMER)
        {
            rt_sem_release(&_soft_timer_sem);
        }
    }
#endif /* RT_USING_TIMER_SOFT */

    rt_spin_unlock_irqrestore(spinlock, level);

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

#ifdef RT_USING_TIMER_SOFT
    if (timer->parent.flag & RT_TIMER_FLAG_SOFT_TIMER)
    {
        spinlock = &_soft_spinlock;
    }
    else
#endif /* RT_USING_TIMER_SOFT */
    {
        spinlock = &_hard_spinlock;
    }
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
    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(rt_object_get_type(&timer->parent) == RT_Object_Class_Timer);

    switch (cmd)
    {
    case RT_TIMER_CTRL_GET_TIME:
        *(rt_tick_t *)arg = timer->init_tick;
        break;

    case RT_TIMER_CTRL_SET_TIME:
        RT_ASSERT((*(rt_tick_t *)arg) < RT_TICK_MAX / 2);
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
    struct rt_timer *t;
    rt_tick_t current_tick;
    rt_base_t level;
    rt_list_t list;

#ifdef RT_USING_SMP
    if (rt_hw_cpu_id() != 0)
    {
        return;
    }
#endif

    rt_list_init(&list);

    LOG_D("timer check enter");

    current_tick = rt_tick_get();

    level = rt_spin_lock_irqsave(&_hard_spinlock);

    while (!rt_list_isempty(&_timer_list[RT_TIMER_SKIP_LIST_LEVEL - 1]))
    {
        t = rt_list_entry(_timer_list[RT_TIMER_SKIP_LIST_LEVEL - 1].next,
                          struct rt_timer, row[RT_TIMER_SKIP_LIST_LEVEL - 1]);

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
            rt_spin_unlock_irqrestore(&_hard_spinlock, level);
            /* call timeout function */
            t->timeout_func(t->parameter);

            /* re-get tick */
            current_tick = rt_tick_get();

            RT_OBJECT_HOOK_CALL(rt_timer_exit_hook, (t));
            LOG_D("current tick: %d", current_tick);
            level = rt_spin_lock_irqsave(&_hard_spinlock);
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
                _timer_start(_timer_list, t);
            }
        }
        else break;
    }
    rt_spin_unlock_irqrestore(&_hard_spinlock, level);
    LOG_D("timer check leave");
}

/**
 * @brief This function will return the next timeout tick in the system.
 *
 * @return the next timeout tick in the system
 */
rt_tick_t rt_timer_next_timeout_tick(void)
{
    rt_base_t level;
    rt_tick_t next_timeout = RT_TICK_MAX;

    level = rt_spin_lock_irqsave(&_hard_spinlock);
    _timer_list_next_timeout(_timer_list, &next_timeout);
    rt_spin_unlock_irqrestore(&_hard_spinlock, level);

    return next_timeout;
}

#ifdef RT_USING_TIMER_SOFT
/**
 * @brief This function will check software-timer list, if a timeout event happens, the
 *        corresponding timeout function will be invoked.
 */
void rt_soft_timer_check(void)
{
    rt_tick_t current_tick;
    struct rt_timer *t;
    rt_base_t level;
    rt_list_t list;

    rt_list_init(&list);
    LOG_D("software timer check enter");
    level = rt_spin_lock_irqsave(&_soft_spinlock);

    while (!rt_list_isempty(&_soft_timer_list[RT_TIMER_SKIP_LIST_LEVEL - 1]))
    {
        t = rt_list_entry(_soft_timer_list[RT_TIMER_SKIP_LIST_LEVEL - 1].next,
                            struct rt_timer, row[RT_TIMER_SKIP_LIST_LEVEL - 1]);

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

            _soft_timer_status = RT_SOFT_TIMER_BUSY;

            rt_spin_unlock_irqrestore(&_soft_spinlock, level);

            /* call timeout function */
            t->timeout_func(t->parameter);

            RT_OBJECT_HOOK_CALL(rt_timer_exit_hook, (t));
            LOG_D("current tick: %d", current_tick);

            level = rt_spin_lock_irqsave(&_soft_spinlock);

            _soft_timer_status = RT_SOFT_TIMER_IDLE;
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
                _timer_start(_soft_timer_list, t);
            }
        }
        else break; /* not check anymore */
    }

    rt_spin_unlock_irqrestore(&_soft_spinlock, level);

    LOG_D("software timer check leave");
}

/**
 * @brief System timer thread entry
 *
 * @param parameter is the arg of the thread
 */
static void _timer_thread_entry(void *parameter)
{
    rt_err_t ret = RT_ERROR;
    rt_tick_t next_timeout;
    rt_base_t level;

    rt_sem_control(&_soft_timer_sem, RT_IPC_CMD_SET_VLIMIT, (void*)1);

    while (1)
    {
        /* get the next timeout tick */
        level = rt_spin_lock_irqsave(&_soft_spinlock);
        ret = _timer_list_next_timeout(_soft_timer_list, &next_timeout);
        rt_spin_unlock_irqrestore(&_soft_spinlock, level);

        if (ret != RT_EOK)
        {
            rt_sem_take(&_soft_timer_sem, RT_WAITING_FOREVER);
        }
        else
        {
            rt_tick_t current_tick;

            /* get current tick */
            current_tick = rt_tick_get();

            if ((next_timeout - current_tick) < RT_TICK_MAX / 2)
            {
                /* get the delta timeout tick */
                next_timeout = next_timeout - current_tick;
                rt_sem_take(&_soft_timer_sem, next_timeout);
            }
        }

        /* check software timer */
        rt_soft_timer_check();
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
    rt_size_t i;

    for (i = 0; i < sizeof(_timer_list) / sizeof(_timer_list[0]); i++)
    {
        rt_list_init(_timer_list + i);
    }
    rt_spin_lock_init(&_hard_spinlock);
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
    rt_spin_lock_init(&_soft_spinlock);
    rt_sem_init(&_soft_timer_sem, "stimer", 0, RT_IPC_FLAG_PRIO);
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
