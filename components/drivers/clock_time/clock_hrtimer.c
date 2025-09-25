/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-01     RT-Thread    Clock time hrtimer
 */

#include <rtdevice.h>
#include <rthw.h>
#include <rtthread.h>
#include <sys/time.h>

#include <drivers/clock_time.h>

#define DBG_SECTION_NAME               "drv.clock_time"
#define DBG_LEVEL                      DBG_INFO
#include <rtdbg.h>

static rt_list_t          _timer_list   = RT_LIST_OBJECT_INIT(_timer_list);
static RT_DEFINE_SPINLOCK(_spinlock);

rt_inline rt_clock_hrtimer_t _first_hrtimer(void)
{
    return rt_list_isempty(&_timer_list) ? RT_NULL : rt_list_first_entry(&_timer_list, struct rt_clock_hrtimer, node);
}

rt_inline rt_tick_t _clock_time_get_cnt(void)
{
    return (rt_tick_t)rt_clock_time_get_counter();
}

rt_inline rt_bool_t _cnt_before(rt_tick_t a, rt_tick_t b)
{
    return ((rt_base_t)(a - b)) < 0;
}

rt_inline rt_bool_t _cnt_after(rt_tick_t a, rt_tick_t b)
{
    return _cnt_before(b, a);
}

rt_weak rt_uint64_t rt_clock_hrtimer_getfrq(void)
{
    return rt_clock_time_get_event_freq();
}

static rt_tick_t _hrtimer_cnt_to_tick(rt_uint64_t cnt)
{
    rt_uint64_t freq = rt_clock_hrtimer_getfrq();
    rt_uint64_t rem = 0;
    rt_uint64_t tick;

    if (freq == 0)
    {
        return 0;
    }

    tick = rt_muldiv_u64(cnt, RT_TICK_PER_SECOND, freq, &rem);
    if (rem != 0)
    {
        tick += 1; /* round up so a non-zero cnt never collapses to a 0-tick timeout */
    }
    if (tick == 0)
    {
        tick = 1; /* at least one tick */
    }

    return (rt_tick_t)tick;
}

rt_weak rt_err_t rt_clock_hrtimer_settimeout(rt_uint64_t cnt)
{
    static rt_timer_t timer = RT_NULL;
    static struct rt_timer _sh_rtimer;
    rt_tick_t tick;

    RT_ASSERT(cnt > 0);

    if (rt_clock_time_set_timeout(cnt) == RT_EOK)
    {
        return RT_EOK;
    }

    tick = _hrtimer_cnt_to_tick(cnt);
    if (tick == 0)
    {
        return -RT_ERROR;
    }

    if (timer == RT_NULL)
    {
        timer = &_sh_rtimer;
        rt_timer_init(timer, "shrtimer", (void (*)(void *))rt_clock_hrtimer_process, RT_NULL,
                      tick, RT_TIMER_FLAG_ONE_SHOT);
    }
    else
    {
        rt_timer_control(timer, RT_TIMER_CTRL_SET_TIME, &tick);
        rt_timer_control(timer, RT_TIMER_CTRL_SET_PARM, RT_NULL);
    }

    if (timer->parent.flag & RT_TIMER_FLAG_ACTIVATED)
    {
        rt_timer_stop(timer);
    }

    rt_timer_start(timer);
    return RT_EOK;
}

static rt_uint64_t _cnt_convert(rt_tick_t cnt)
{
    rt_uint64_t rtn = 0;
    rt_tick_t count = cnt - _clock_time_get_cnt();

    if (count > (RT_TICK_MAX / 2))
    {
        return 0;
    }

    rtn = rt_muldiv_u64(count, rt_clock_hrtimer_getfrq(), rt_clock_time_get_freq(), NULL);
    return rtn == 0 ? 1 : rtn;
}

static void _sleep_timeout(void *parameter)
{
    struct rt_clock_hrtimer *timer = parameter;
    rt_completion_done(&timer->completion);
}

static void _insert_timer_to_list_locked(rt_clock_hrtimer_t timer)
{
    rt_clock_hrtimer_t iter;

    rt_list_for_each_entry(iter, &_timer_list, node)
    {
        if (_cnt_before(timer->timeout_cnt, iter->timeout_cnt))
        {
            break;
        }
    }
    rt_list_insert_before(&iter->node, &(timer->node));

    timer->flag |= RT_TIMER_FLAG_ACTIVATED;
}

static void _hrtimer_process_locked(void)
{
    rt_clock_hrtimer_t timer;

    while ((timer = _first_hrtimer()) != RT_NULL)
    {
        rt_tick_t now = _clock_time_get_cnt();

        if (_cnt_before(now, timer->timeout_cnt))
        {
            break;
        }

        rt_list_remove(&(timer->node));

        if (timer->flag & RT_TIMER_FLAG_PERIODIC)
        {
            timer->timeout_cnt = timer->delay_cnt + now;
            _insert_timer_to_list_locked(timer);
        }
        else
        {
            timer->flag &= ~RT_TIMER_FLAG_ACTIVATED;
        }

        if (timer->timeout_func)
        {
            timer->timeout_func(timer->parameter);
        }
    }
}

static void _set_next_timeout_locked(void)
{
    rt_clock_hrtimer_t timer;
    rt_uint64_t next_timeout_cnt;
    rt_bool_t find_next;

    do
    {
        find_next = RT_FALSE;
        if ((timer = _first_hrtimer()) != RT_NULL)
        {
            next_timeout_cnt = _cnt_convert(timer->timeout_cnt);
            if (next_timeout_cnt > 0)
            {
                rt_clock_hrtimer_settimeout(next_timeout_cnt);
            }
            else
            {
                _hrtimer_process_locked();
                find_next = RT_TRUE;
            }
        }
    }
    while (find_next);
}

void rt_clock_hrtimer_process(void)
{
    rt_base_t level = rt_spin_lock_irqsave(&_spinlock);

    _hrtimer_process_locked();
    _set_next_timeout_locked();

    rt_spin_unlock_irqrestore(&_spinlock, level);
}

void rt_clock_hrtimer_init(rt_clock_hrtimer_t timer,
                           const char        *name,
                           rt_uint8_t         flag,
                           void (*timeout)(void *parameter),
                           void *parameter)
{
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(timeout != RT_NULL);

    rt_memset(timer, 0, sizeof(struct rt_clock_hrtimer));

    timer->flag         = flag & ~RT_TIMER_FLAG_ACTIVATED;
    timer->timeout_func = timeout;
    timer->parameter    = parameter;
    rt_strncpy(timer->name, name, RT_NAME_MAX - 1);
    rt_list_init(&(timer->node));
    rt_completion_init(&timer->completion);
}

rt_err_t rt_clock_hrtimer_start(rt_clock_hrtimer_t timer, rt_tick_t delay_cnt)
{
    rt_base_t  level;

    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(delay_cnt < (RT_TICK_MAX / 2));

    timer->delay_cnt    = delay_cnt;
    timer->timeout_cnt  = timer->delay_cnt + _clock_time_get_cnt();

    level = rt_spin_lock_irqsave(&_spinlock);

    if (timer->flag & RT_TIMER_FLAG_ACTIVATED)
    {
        rt_spin_unlock_irqrestore(&_spinlock, level);
        return -RT_ERROR;
    }

    _insert_timer_to_list_locked(timer);
    _set_next_timeout_locked();

    rt_spin_unlock_irqrestore(&_spinlock, level);

    return RT_EOK;
}

rt_err_t rt_clock_hrtimer_stop(rt_clock_hrtimer_t timer)
{
    rt_base_t level;

    RT_ASSERT(timer != RT_NULL);

    level = rt_spin_lock_irqsave(&_spinlock);

    if (!(timer->flag & RT_TIMER_FLAG_ACTIVATED))
    {
        rt_spin_unlock_irqrestore(&_spinlock, level);
        return -RT_ERROR;
    }

    rt_list_remove(&timer->node);
    timer->flag &= ~RT_TIMER_FLAG_ACTIVATED;
    _set_next_timeout_locked();

    rt_spin_unlock_irqrestore(&_spinlock, level);

    return RT_EOK;
}

rt_err_t rt_clock_hrtimer_control(rt_clock_hrtimer_t timer, int cmd, void *arg)
{
    rt_base_t level;

    RT_ASSERT(timer != RT_NULL);

    level = rt_spin_lock_irqsave(&_spinlock);
    switch (cmd)
    {
    case RT_TIMER_CTRL_GET_TIME:
        *(rt_tick_t *)arg = timer->delay_cnt;
        break;

    case RT_TIMER_CTRL_SET_TIME:
        RT_ASSERT((*(rt_tick_t *)arg) < (RT_TICK_MAX / 2));
        timer->delay_cnt    = *(rt_tick_t *)arg;
        timer->timeout_cnt  = *(rt_tick_t *)arg + _clock_time_get_cnt();
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
            *(rt_uint32_t *)arg = RT_TIMER_FLAG_ACTIVATED;
        }
        else
        {
            *(rt_uint32_t *)arg = RT_TIMER_FLAG_DEACTIVATED;
        }
        break;

    case RT_TIMER_CTRL_GET_REMAIN_TIME:
        *(rt_tick_t *)arg = timer->timeout_cnt;
        break;
    case RT_TIMER_CTRL_GET_FUNC:
        if (arg != RT_NULL)
        {
            *(void **)arg = (void *)timer->timeout_func;
        }
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

rt_err_t rt_clock_hrtimer_detach(rt_clock_hrtimer_t timer)
{
    rt_base_t level;

    RT_ASSERT(timer != RT_NULL);

    rt_completion_wakeup_by_errno(&timer->completion, RT_ERROR);

    level = rt_spin_lock_irqsave(&_spinlock);

    timer->flag &= ~RT_TIMER_FLAG_ACTIVATED;
    if (timer->error == -RT_EINTR || timer->error == RT_EINTR)
    {
        rt_list_remove(&timer->node);
        _set_next_timeout_locked();
    }

    rt_spin_unlock_irqrestore(&_spinlock, level);

    return RT_EOK;
}

void rt_clock_hrtimer_delay_init(struct rt_clock_hrtimer *timer)
{
    rt_clock_hrtimer_init(timer, "hrtimer_sleep", RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_HARD_TIMER,
                          _sleep_timeout, timer);
}

void rt_clock_hrtimer_delay_detach(struct rt_clock_hrtimer *timer)
{
    rt_clock_hrtimer_detach(timer);
}

rt_err_t rt_clock_hrtimer_sleep(struct rt_clock_hrtimer *timer, rt_tick_t cnt)
{
    rt_err_t err;

    if (cnt == 0)
    {
        return -RT_EINVAL;
    }

    err = rt_clock_hrtimer_start(timer, cnt);
    if (err)
    {
        return err;
    }

    err = rt_completion_wait_flags(&(timer->completion), RT_WAITING_FOREVER,
                                   RT_INTERRUPTIBLE);
    rt_clock_hrtimer_keep_errno(timer, err);

    return err;
}

rt_err_t rt_clock_hrtimer_ndelay(struct rt_clock_hrtimer *timer, rt_uint64_t ns)
{
    rt_tick_t cputimer_tick = (rt_tick_t)rt_muldiv_u64(ns, rt_clock_time_get_freq(), NANOSECOND_PER_SECOND, NULL);

    return rt_clock_hrtimer_sleep(timer, cputimer_tick);
}

rt_err_t rt_clock_hrtimer_udelay(struct rt_clock_hrtimer *timer, rt_uint64_t us)
{
    return rt_clock_hrtimer_ndelay(timer, us * 1000);
}

rt_err_t rt_clock_hrtimer_mdelay(struct rt_clock_hrtimer *timer, rt_uint64_t ms)
{
    return rt_clock_hrtimer_ndelay(timer, ms * 1000000);
}

void rt_clock_time_event_isr(void)
{
    rt_clock_hrtimer_process();
}
