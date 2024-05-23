/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-10     xqyjlj       The first version.
 * 2023-09-15     xqyjlj       perf rt_hw_interrupt_disable/enable
 */

#include <rtdevice.h>
#include <rthw.h>
#include <rtthread.h>

#define DBG_SECTION_NAME               "drv.ktime"
#define DBG_LEVEL                      DBG_INFO
#include <rtdbg.h>

#include "ktime.h"

#ifdef ARCH_CPU_64BIT
#define _HRTIMER_MAX_CNT UINT64_MAX
#else
#define _HRTIMER_MAX_CNT UINT32_MAX
#endif

static rt_list_t          _timer_list = RT_LIST_OBJECT_INIT(_timer_list);
static rt_ktime_hrtimer_t _current_timer   = RT_NULL;
static RT_DEFINE_SPINLOCK(_spinlock);

rt_weak unsigned long rt_ktime_hrtimer_getres(void)
{
    return ((1000UL * 1000 * 1000) * RT_KTIME_RESMUL) / RT_TICK_PER_SECOND;
}

rt_weak unsigned long rt_ktime_hrtimer_getfrq(void)
{
    return RT_TICK_PER_SECOND;
}

rt_weak unsigned long rt_ktime_hrtimer_getcnt(void)
{
    return rt_tick_get();
}

static void (*_outcb)(void *param) = RT_NULL;

static void _hrtimer_timeout(void *parameter)
{
    if (_outcb)
        _outcb(parameter);
}

rt_weak rt_err_t rt_ktime_hrtimer_settimeout(unsigned long cnt, void (*timeout)(void *param), void *param)
{
    static rt_timer_t timer = RT_NULL;

    _outcb = timeout;
    if (cnt == 0)
    {
        if (timer != RT_NULL)
        {
            if (timer->parent.flag & RT_TIMER_FLAG_ACTIVATED)
            {
                rt_timer_stop(timer);
            }
        }

        if (_outcb)
            _outcb(param);

        return RT_EOK;
    }

    if (timer == RT_NULL)
    {
        timer = rt_timer_create("shrtimer", _hrtimer_timeout, param, cnt, RT_TIMER_FLAG_ONE_SHOT);
    }
    else
    {
        rt_tick_t tick = cnt;
        rt_timer_control(timer, RT_TIMER_CTRL_SET_TIME, &tick);
        rt_timer_control(timer, RT_TIMER_CTRL_SET_PARM, param);
    }

    if (timer->parent.flag & RT_TIMER_FLAG_ACTIVATED)
    {
        rt_timer_stop(timer);
    }
    rt_timer_start(timer);
    return RT_EOK;
}

/**
 * @brief convert cnt from cputimer cnt to hrtimer cnt
 *
 * @param cnt
 * @return unsigned long
 */
static unsigned long _cnt_convert(unsigned long cnt)
{
    unsigned long rtn   = 0;
    unsigned long count = cnt - rt_ktime_cputimer_getcnt();
    if (count > (_HRTIMER_MAX_CNT / 2))
        return 0;

    rtn = (count * rt_ktime_cputimer_getres()) / rt_ktime_hrtimer_getres();
    return rtn == 0 ? 1 : rtn; /* at least 1 */
}

static void _sleep_timeout(void *parameter)
{
    struct rt_ktime_hrtimer *timer = parameter;
    rt_completion_done(&timer->completion);
}

static void _insert_timer_to_list_locked(rt_ktime_hrtimer_t timer)
{
    rt_ktime_hrtimer_t iter;

    /* remove timer from list */
    rt_list_remove(&timer->node);

    /* change status of timer */
    timer->flag &= ~RT_TIMER_FLAG_ACTIVATED;

    rt_list_for_each_entry(iter, &_timer_list, node)
    {
        if (iter->timeout_cnt > timer->timeout_cnt)
        {
            break;
        }
    }
    rt_list_insert_before(&iter->node, &(timer->node));

    timer->flag |= RT_TIMER_FLAG_ACTIVATED;
}

static void _set_next_timeout_n_unlock(rt_base_t level);
static void _timeout_callback(void *parameter)
{
    rt_ktime_hrtimer_t timer;
    timer = (rt_ktime_hrtimer_t)parameter;
    rt_base_t level;

    LOG_D("Expected wake-up in CPU time: %lu, actual wake-up in CPU time %lu", timer->timeout_cnt, rt_ktime_cputimer_getcnt());

    level     = rt_spin_lock_irqsave(&_spinlock);
    _current_timer = RT_NULL;

    if (timer->flag & RT_TIMER_FLAG_PERIODIC)
    {
        timer->timeout_cnt = timer->delay_cnt + rt_ktime_cputimer_getcnt();
        _insert_timer_to_list_locked(timer);
    }
    else
    {
        rt_list_remove(&(timer->node));
    }

    if ((timer->flag & RT_TIMER_FLAG_ACTIVATED) && timer->timeout_func)
    {
        timer->timeout_func(timer->parameter);
    }

    _set_next_timeout_n_unlock(level);
}

static void _set_next_timeout_n_unlock(rt_base_t level)
{
    rt_ktime_hrtimer_t t;

    if (&_timer_list != _timer_list.prev)
    {
        t = rt_list_entry(_timer_list.next, struct rt_ktime_hrtimer, node);
        if (_current_timer != RT_NULL)
        {
            if (t != _current_timer && t->timeout_cnt < _current_timer->timeout_cnt)
            {
                _current_timer = t;
                rt_spin_unlock_irqrestore(&_spinlock, level);
                rt_ktime_hrtimer_settimeout(_cnt_convert(_current_timer->timeout_cnt), _timeout_callback, _current_timer);
            }
            else
            {
                rt_spin_unlock_irqrestore(&_spinlock, level);
            }
        }
        else
        {
            _current_timer = t;
            rt_spin_unlock_irqrestore(&_spinlock, level);
            rt_ktime_hrtimer_settimeout(_cnt_convert(_current_timer->timeout_cnt), _timeout_callback, _current_timer);
        }
    }
    else
    {
        _current_timer = RT_NULL;
        rt_spin_unlock_irqrestore(&_spinlock, level);
        rt_ktime_hrtimer_settimeout(0, RT_NULL, RT_NULL);
    }
}

void rt_ktime_hrtimer_init(rt_ktime_hrtimer_t timer,
                           const char        *name,
                           rt_uint8_t         flag,
                           void (*timeout)(void *parameter),
                           void *parameter)
{
    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(timeout != RT_NULL);

    timer->flag = flag;
    timer->name = name;

    /* set deactivated */
    timer->flag        &= ~RT_TIMER_FLAG_ACTIVATED;
    timer->timeout_func = timeout;
    timer->parameter    = parameter;

    rt_list_init(&(timer->node));
    rt_completion_init(&timer->completion);
}

rt_err_t rt_ktime_hrtimer_start(rt_ktime_hrtimer_t timer, unsigned long delay_cnt)
{
    rt_base_t  level;

    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(delay_cnt < (_HRTIMER_MAX_CNT / 2));

    timer->delay_cnt    = delay_cnt;
    timer->timeout_cnt  = timer->delay_cnt + rt_ktime_cputimer_getcnt();

    level = rt_spin_lock_irqsave(&_spinlock);

    _insert_timer_to_list_locked(timer);

    _set_next_timeout_n_unlock(level);

    return RT_EOK;
}

rt_err_t rt_ktime_hrtimer_stop(rt_ktime_hrtimer_t timer)
{
    rt_base_t level;

    RT_ASSERT(timer != RT_NULL); /* timer check */

    level = rt_spin_lock_irqsave(&_spinlock);
    if (!(timer->flag & RT_TIMER_FLAG_ACTIVATED))
    {
        rt_spin_unlock_irqrestore(&_spinlock, level);
        return -RT_ERROR;
    }
    _current_timer = RT_NULL;
    rt_list_remove(&timer->node);
    timer->flag &= ~RT_TIMER_FLAG_ACTIVATED; /* change status */

    _set_next_timeout_n_unlock(level);

    return RT_EOK;
}

rt_err_t rt_ktime_hrtimer_control(rt_ktime_hrtimer_t timer, int cmd, void *arg)
{
    rt_base_t level;

    /* parameter check */
    RT_ASSERT(timer != RT_NULL);

    level = rt_spin_lock_irqsave(&_spinlock);
    switch (cmd)
    {
        case RT_TIMER_CTRL_GET_TIME:
            *(unsigned long *)arg = timer->delay_cnt;
            break;

        case RT_TIMER_CTRL_SET_TIME:
            RT_ASSERT((*(unsigned long *)arg) < (_HRTIMER_MAX_CNT / 2));
            timer->delay_cnt    = *(unsigned long *)arg;
            timer->timeout_cnt  = *(unsigned long *)arg + rt_ktime_cputimer_getcnt();
            break;

        case RT_TIMER_CTRL_SET_ONESHOT:
            timer->flag &= ~RT_TIMER_FLAG_PERIODIC;
            break;

        case RT_TIMER_CTRL_SET_PERIODIC:
            timer->flag |= RT_TIMER_FLAG_PERIODIC;
            break;

        case RT_TIMER_CTRL_GET_STATE:
            if (timer->flag & RT_TIMER_FLAG_ACTIVATED)
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
            *(unsigned long *)arg = timer->timeout_cnt;
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
    rt_spin_unlock_irqrestore(&_spinlock, level);

    return RT_EOK;
}

rt_err_t rt_ktime_hrtimer_detach(rt_ktime_hrtimer_t timer)
{
    rt_base_t level;

    /* parameter check */
    RT_ASSERT(timer != RT_NULL);

    /* notify the timer stop event */
    rt_completion_wakeup_by_errno(&timer->completion, RT_ERROR);

    level = rt_spin_lock_irqsave(&_spinlock);

    /* stop timer */
    timer->flag &= ~RT_TIMER_FLAG_ACTIVATED;
    /* when interrupted */
    if (timer->error == -RT_EINTR || timer->error == RT_EINTR)
    {
        _current_timer = RT_NULL;
        rt_list_remove(&timer->node);
        _set_next_timeout_n_unlock(level);
    }
    else
    {
        rt_spin_unlock_irqrestore(&_spinlock, level);
    }

    return RT_EOK;
}

/************************** delay ***************************/

void rt_ktime_hrtimer_delay_init(struct rt_ktime_hrtimer *timer)
{
    rt_ktime_hrtimer_init(timer, "hrtimer_sleep", RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_HARD_TIMER,
                          _sleep_timeout, timer);
}

void rt_ktime_hrtimer_delay_detach(struct rt_ktime_hrtimer *timer)
{
    rt_ktime_hrtimer_detach(timer);
}

rt_err_t rt_ktime_hrtimer_sleep(struct rt_ktime_hrtimer *timer, unsigned long cnt)
{
    rt_err_t err;

    if (cnt == 0)
        return -RT_EINVAL;

    rt_ktime_hrtimer_start(timer, cnt); /* reset the timeout of thread timer and start it */
    err = rt_completion_wait_flags(&(timer->completion), RT_WAITING_FOREVER,
                                   RT_INTERRUPTIBLE);
    rt_ktime_hrtimer_keep_errno(timer, err);

    return RT_EOK;
}

rt_err_t rt_ktime_hrtimer_ndelay(struct rt_ktime_hrtimer *timer, unsigned long ns)
{
    unsigned long res = rt_ktime_cputimer_getres();
    return rt_ktime_hrtimer_sleep(timer, (ns * RT_KTIME_RESMUL) / res);
}

rt_err_t rt_ktime_hrtimer_udelay(struct rt_ktime_hrtimer *timer, unsigned long us)
{
    return rt_ktime_hrtimer_ndelay(timer, us * 1000);
}

rt_err_t rt_ktime_hrtimer_mdelay(struct rt_ktime_hrtimer *timer, unsigned long ms)
{
    return rt_ktime_hrtimer_ndelay(timer, ms * 1000000);
}
