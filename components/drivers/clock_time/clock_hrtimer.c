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

#include <drivers/clock_time.h>

#define DBG_SECTION_NAME               "drv.clock_time"
#define DBG_LEVEL                      DBG_INFO
#include <rtdbg.h>

#define CLOCK_TIME_NSEC_PER_SEC (1000000000ULL)

#ifdef ARCH_CPU_64BIT
#define _HRTIMER_MAX_CNT UINT64_MAX
#else
#define _HRTIMER_MAX_CNT UINT32_MAX
#endif

static rt_list_t          _timer_list   = RT_LIST_OBJECT_INIT(_timer_list);
static RT_DEFINE_SPINLOCK(_spinlock);

rt_inline rt_clock_hrtimer_t _first_hrtimer(void)
{
    return rt_list_isempty(&_timer_list) ? RT_NULL : rt_list_first_entry(&_timer_list, struct rt_clock_hrtimer, node);
}

rt_inline unsigned long _clock_time_get_cnt(void)
{
    return rt_clock_time_get_counter();
}

rt_inline rt_bool_t _cnt_before(unsigned long a, unsigned long b)
{
    return ((rt_base_t)(a - b)) < 0;
}

rt_inline rt_bool_t _cnt_after(unsigned long a, unsigned long b)
{
    return _cnt_before(b, a);
}

rt_weak rt_uint64_t rt_clock_hrtimer_getres(void)
{
    return rt_clock_time_get_event_res_scaled();
}

rt_weak unsigned long rt_clock_hrtimer_getfrq(void)
{
    return (unsigned long)rt_clock_time_get_event_freq();
}

static rt_tick_t _hrtimer_cnt_to_tick(unsigned long cnt)
{
    rt_uint64_t res = rt_clock_hrtimer_getres();
    rt_uint64_t ns;

    if (res == 0)
    {
        return 0;
    }

    ns = ((rt_uint64_t)cnt * res) / RT_CLOCK_TIME_RESMUL;
    if (ns == 0)
    {
        return 1;
    }

    ns = (ns * RT_TICK_PER_SECOND + CLOCK_TIME_NSEC_PER_SEC - 1) / CLOCK_TIME_NSEC_PER_SEC;
    if (ns == 0)
    {
        return 1;
    }

    return (rt_tick_t)ns;
}

rt_weak rt_err_t rt_clock_hrtimer_settimeout(unsigned long cnt)
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

static unsigned long _cnt_convert(unsigned long cnt)
{
    unsigned long count;
    rt_uint64_t src_res;
    rt_uint64_t event_res;
    rt_uint64_t result;

    count = cnt - _clock_time_get_cnt();
    if (count > (_HRTIMER_MAX_CNT / 2))
    {
        return 0;
    }

    src_res = rt_clock_time_get_res_scaled();
    event_res = rt_clock_hrtimer_getres();
    if (src_res == 0 || event_res == 0)
    {
        return 0;
    }

    result = ((rt_uint64_t)count * src_res) / event_res;

    return result == 0 ? 1 : (unsigned long)result;
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
        unsigned long now = _clock_time_get_cnt();

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
    rt_ubase_t next_timeout_cnt;
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

rt_err_t rt_clock_hrtimer_start(rt_clock_hrtimer_t timer, unsigned long delay_cnt)
{
    rt_base_t  level;

    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(delay_cnt < (_HRTIMER_MAX_CNT / 2));

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
        *(unsigned long *)arg = timer->delay_cnt;
        break;

    case RT_TIMER_CTRL_SET_TIME:
        RT_ASSERT((*(unsigned long *)arg) < (_HRTIMER_MAX_CNT / 2));
        timer->delay_cnt    = *(unsigned long *)arg;
        timer->timeout_cnt  = *(unsigned long *)arg + _clock_time_get_cnt();
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
        *(unsigned long *)arg = timer->timeout_cnt;
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

rt_err_t rt_clock_hrtimer_sleep(struct rt_clock_hrtimer *timer, unsigned long cnt)
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

rt_err_t rt_clock_hrtimer_ndelay(struct rt_clock_hrtimer *timer, unsigned long ns)
{
    rt_uint64_t res = rt_clock_time_get_res_scaled();
    if (res == 0)
    {
        return -RT_ERROR;
    }

    return rt_clock_hrtimer_sleep(timer, (ns * RT_CLOCK_TIME_RESMUL) / res);
}

rt_err_t rt_clock_hrtimer_udelay(struct rt_clock_hrtimer *timer, unsigned long us)
{
    return rt_clock_hrtimer_ndelay(timer, us * 1000);
}

rt_err_t rt_clock_hrtimer_mdelay(struct rt_clock_hrtimer *timer, unsigned long ms)
{
    return rt_clock_hrtimer_ndelay(timer, ms * 1000000);
}

void rt_clock_time_event_isr(void)
{
    rt_clock_hrtimer_process();
}
