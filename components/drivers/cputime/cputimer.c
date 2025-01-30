/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-02-13     zhkag             first version
 * 2023-04-03     xqyjlj            fix cputimer in multithreading
 * 2025-01-30     wumingzi          add doxygen comment
 */

#include <rtdevice.h>
#include <rthw.h>
#include <rtthread.h>

/**
 * @addtogroup  Drivers                 RTTHREAD Driver
 * @defgroup    cputimer                cputimer
 * @brief       cputimer driver api
 * @ingroup     Drivers
 * @addtogroup  cputimer
 * @{
 */

static rt_list_t           _cputimer_list     = RT_LIST_OBJECT_INIT(_cputimer_list);
static struct rt_cputimer *_cputimer_nowtimer = RT_NULL;

/**
 * @brief   When cpu timeout,it will release relative semphore
 *
 * @param   parameter
 *
 */
static void _cputime_sleep_timeout(void *parameter)
{
    struct rt_semaphore *sem;
    sem = (struct rt_semaphore *)parameter;
    rt_sem_release(sem);
}

/**
 * @brief   Set callback function for next timeout cputimer
 *
 * @param   parameter       point to struct rt_cputimer where callback
                            function needs to be set
 * @note    The function isn't recursively to call callback function, instead
            set asynchronously next callback function after executing callback function, function when call current
            callback function,
 */
static void _cputime_timeout_callback(void *parameter)
{
    struct rt_cputimer *timer;
    timer = (struct rt_cputimer *)parameter;
    rt_base_t level;
    level              = rt_hw_interrupt_disable();
    _cputimer_nowtimer = RT_NULL;
    rt_list_remove(&(timer->row));
    rt_hw_interrupt_enable(level);
    timer->timeout_func(timer->parameter);

    if (&_cputimer_list != _cputimer_list.prev)
    {
        struct rt_cputimer *t;
        t = rt_list_entry(_cputimer_list.next, struct rt_cputimer, row);
        clock_cpu_settimeout(t->timeout_tick, _cputime_timeout_callback, t);
    }
    else
    {
        clock_cpu_settimeout(RT_NULL, RT_NULL, RT_NULL);
    }
}

/**
 * @brief   Set next the earliest timeout cputimer and its callback function
 *
 */
static void _set_next_timeout()
{
    struct rt_cputimer *t;

    if (&_cputimer_list != _cputimer_list.prev)
    {
        t = rt_list_entry((&_cputimer_list)->next, struct rt_cputimer, row);
        if (_cputimer_nowtimer != RT_NULL)
        {
            if (t != _cputimer_nowtimer && t->timeout_tick < _cputimer_nowtimer->timeout_tick)
            {
                _cputimer_nowtimer = t;
                clock_cpu_settimeout(t->timeout_tick, _cputime_timeout_callback, t);
            }
        }
        else
        {
            _cputimer_nowtimer = t;
            clock_cpu_settimeout(t->timeout_tick, _cputime_timeout_callback, t);
        }
    }
    else
    {
        _cputimer_nowtimer = RT_NULL;
        clock_cpu_settimeout(RT_NULL, RT_NULL, RT_NULL);
    }
}

/**
 * @brief   Init cputimer
 *
 * @param   timer           memeory space of cputimer
 * @param   name            name of cputimer
 * @param   timeout         callback function that is called when timeout
 * @param   parameter       parameter of callback function
 * @param   tick            number of ticks left until next timeout
 * @param   flag            flag of cputimer
 *
 * @note    Config RT_USING_HEAP option will be vital if you want to using this function.
 */
void rt_cputimer_init(rt_cputimer_t timer,
                      const char   *name,
                      void (*timeout)(void *parameter),
                      void       *parameter,
                      rt_uint64_t tick,
                      rt_uint8_t  flag)
{
    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(timeout != RT_NULL);
    RT_ASSERT(clock_cpu_issettimeout() != RT_FALSE);

    /* set flag */
    timer->parent.flag = flag;

    /* set deactivated */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
    timer->timeout_func = timeout;
    timer->parameter    = parameter;
    timer->timeout_tick = tick + clock_cpu_gettime();
    timer->init_tick    = tick;

    rt_list_init(&(timer->row));
    rt_sem_init(&(timer->sem), "cputime", 0, RT_IPC_FLAG_PRIO);
}

/**
 * @brief   Delete cputimer object
 *
 * @param   timer           deleted cputimer
 *
 * @note    Config RT_USING_HEAP option will be vital if you want to using this function.
 * @return  return RT_EOK forever
 */
rt_err_t rt_cputimer_delete(rt_cputimer_t timer)
{
    rt_base_t level;

    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(clock_cpu_issettimeout() != RT_FALSE);

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    rt_list_remove(&timer->row);
    /* stop timer */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    _set_next_timeout();

    return RT_EOK;
}

/**
 * @brief   Insert timer to timer list and start it.
 *
 * @param   timer           timer to be inserted
 *
 * @return  return RT_EOK forever
 */
rt_err_t rt_cputimer_start(rt_cputimer_t timer)
{
    rt_list_t *timer_list;
    rt_base_t  level;

    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(clock_cpu_issettimeout() != RT_FALSE);

    /* stop timer firstly */
    level = rt_hw_interrupt_disable();
    /* remove timer from list */

    rt_list_remove(&timer->row);
    /* change status of timer */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    timer_list = &_cputimer_list;

    for (; timer_list != _cputimer_list.prev;
         timer_list = timer_list->next)
    {
        struct rt_cputimer *t;
        rt_list_t *p = timer_list->next;

        t = rt_list_entry(p, struct rt_cputimer, row);

        if ((t->timeout_tick - timer->timeout_tick) == 0)
        {
            continue;
        }
        else if ((t->timeout_tick - timer->timeout_tick) < 0x7fffffffffffffff)
        {
            break;
        }
    }

    rt_list_insert_after(timer_list, &(timer->row));

    timer->parent.flag |= RT_TIMER_FLAG_ACTIVATED;

    _set_next_timeout();
    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

/**
 * @brief   Stop cputimer
 *
 * @param   timer           stopped cputimer
 *
 * @return  return RT_EOK forever
 */
rt_err_t rt_cputimer_stop(rt_cputimer_t timer)
{
    rt_base_t level;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /* timer check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(clock_cpu_issettimeout() != RT_FALSE);

    if (!(timer->parent.flag & RT_TIMER_FLAG_ACTIVATED))
    {
        rt_hw_interrupt_enable(level);
        return -RT_ERROR;
    }

    rt_list_remove(&timer->row);
    /* change status */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    _set_next_timeout();
    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

/**
 * @brief   Control cputimer by cmd
 *
 * @param   timer           controlled cputimer
 * @param   cmd             the command of cputimer. It can be one of:
                            | Options                            | Description                                       |
                            |------------------------------------|---------------------------------------------------|
                            | `RT_TIMER_CTRL_GET_TIME`:          | Get number of init ticks.                         |
                            | `RT_TIMER_CTRL_SET_TIME`:          | Set number of init ticks.                         |
                            | `RT_TIMER_CTRL_SET_ONESHOT`:       | Set flag of timer to ONESHOT.                     |
                            | `RT_TIMER_CTRL_SET_PERIODIC`:      | Set flag of timer to PERIODIC.                    |
                            | `RT_TIMER_CTRL_GET_STATE`:         | Get state of timer.                               |
                            | `RT_TIMER_CTRL_GET_REMAIN_TIME`:   | Get number of ticks left.                         |
                            | `RT_TIMER_CTRL_GET_FUNC`:          | Get of timeout callback function.                 |
                            | `RT_TIMER_CTRL_SET_FUNC`:          | Set of timeout callback function.                 |
                            | `RT_TIMER_CTRL_GET_PARM`:          | Get parameters of callback function.              |
                            | `RT_TIMER_CTRL_SET_PARM`:          | Set parameters of callback function.              |
 * @param   arg             point to user data. It will depands on  vary of cmd parameter:
                            | Cmd options                        | Description                                       |
                            |------------------------------------|---------------------------------------------------|
                            | `RT_TIMER_CTRL_GET_TIME`:          | Arg will be a pointer to rt_uint64_t type.        |
                            | `RT_TIMER_CTRL_SET_TIME`:          | Arg shall be a pointer to rt_uint64_t type.       |
                            | `RT_TIMER_CTRL_SET_ONESHOT`:       | Arg is useless parameter.                         |
                            | `RT_TIMER_CTRL_SET_PERIODIC`:      | Arg is useless parameter.                         |
                            | `RT_TIMER_CTRL_GET_STATE`:         | Arg shall be a pointer to rt_uint32_t type.       |
                            | `RT_TIMER_CTRL_GET_REMAIN_TIME`:   | Arg shall be a pointer to rt_uint64_t type..      |
                            | `RT_TIMER_CTRL_GET_FUNC`:          | Arg will be a pointer to void (*)(void*) type.    |
                            | `RT_TIMER_CTRL_SET_FUNC`:          | Arg shall be a pointer to void (*)(void*) type.   |
                            | `RT_TIMER_CTRL_GET_PARM`:          | Arg will be a pointer to void* type.              |
                            | `RT_TIMER_CTRL_SET_PARM`:          | Arg shall be a pointer to void* type.             |
 *
 * @return  rt_err_t        return RT_EOK forever
 */
rt_err_t rt_cputimer_control(rt_cputimer_t timer, int cmd, void *arg)
{
    rt_base_t level;

    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(clock_cpu_issettimeout() != RT_FALSE);

    level = rt_hw_interrupt_disable();
    switch (cmd)
    {
    case RT_TIMER_CTRL_GET_TIME:
        *(rt_uint64_t *)arg = timer->init_tick;
        break;

    case RT_TIMER_CTRL_SET_TIME:
        RT_ASSERT((*(rt_uint64_t *)arg) < 0x7fffffffffffffff);
        timer->init_tick    = *(rt_uint64_t *)arg;
        timer->timeout_tick = *(rt_uint64_t *)arg + clock_cpu_gettime();
        break;

    case RT_TIMER_CTRL_SET_ONESHOT:
        timer->parent.flag &= ~RT_TIMER_FLAG_PERIODIC;
        break;

    case RT_TIMER_CTRL_SET_PERIODIC:
        timer->parent.flag |= RT_TIMER_FLAG_PERIODIC;
        break;

    case RT_TIMER_CTRL_GET_STATE:
        if (timer->parent.flag & RT_TIMER_FLAG_ACTIVATED)
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
        *(rt_uint64_t *)arg = timer->timeout_tick;
        break;
    case RT_TIMER_CTRL_GET_FUNC:
        arg = (void *)timer->timeout_func;
        break;

    case RT_TIMER_CTRL_SET_FUNC:
        timer->timeout_func = (void (*)(void *))arg;
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
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

/**
 * @brief   Detach cputimer
 *
 * @param   timer           deteched cputimer
 *
 * @return  rt_err_t        return RT_EOK forever
 */
rt_err_t rt_cputimer_detach(rt_cputimer_t timer)
{
    rt_base_t level;

    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(clock_cpu_issettimeout() != RT_FALSE);

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    rt_list_remove(&timer->row);
    /* stop timer */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    _set_next_timeout();
    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    rt_sem_detach(&(timer->sem));

    return RT_EOK;
}

/**
 * @brief   Let cpu to sleep a number of ticks
 *
 * @param   tick            number of ticks to sleep
 *
 * @return  rt_err_t        returns RT_EOK if the delay is successful;
                            otherwise, returns a value indicating failure.
 */
rt_err_t rt_cputime_sleep(rt_uint64_t tick)
{
    rt_base_t          level;
    struct rt_cputimer cputimer;

    if (!clock_cpu_issettimeout())
    {
        rt_int32_t ms = clock_cpu_millisecond(tick);
        return rt_thread_delay(rt_tick_from_millisecond(ms));
    }

    if (tick == 0)
    {
        return -RT_EINVAL;
    }

    rt_cputimer_init(&cputimer, "cputime_sleep", _cputime_sleep_timeout, &(cputimer.sem), tick,
                     RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_SOFT_TIMER);

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    rt_cputimer_start(&cputimer); /* reset the timeout of thread timer and start it */
    rt_hw_interrupt_enable(level);
    rt_sem_take_interruptible(&(cputimer.sem), RT_WAITING_FOREVER);

    rt_cputimer_detach(&cputimer);
    return RT_EOK;
}

/**
 * @brief   Let cpu to sleep a number of nanosecond
 *
 * @param   ns              time of sleep
 *
 * @return  rt_err_t        returns RT_EOK if the delay is successful;
                            otherwise, returns a value indicating failure.
 */
rt_err_t rt_cputime_ndelay(rt_uint64_t ns)
{
    uint64_t unit = clock_cpu_getres();
    return rt_cputime_sleep(ns * (1000UL * 1000) / unit);
}

/**
 * @brief   Let cpu to sleep a number of microsecond
 *
 * @param   us              time of sleep
 *
 * @return  rt_err_t        returns RT_EOK if the delay is successful;
                            otherwise, returns a value indicating failure.
 */
rt_err_t rt_cputime_udelay(rt_uint64_t us)
{
    return rt_cputime_ndelay(us * 1000);
}

/**
 * @brief   Let cpu to sleep a number of millisecond
 *
 * @param   ms              time of sleep
 *
 * @return  rt_err_t        returns RT_EOK if the delay is successful;
                            otherwise, returns a value indicating failure.
 */
rt_err_t rt_cputime_mdelay(rt_uint64_t ms)
{
    return rt_cputime_ndelay(ms * 1000000);
}
/*! @}*/