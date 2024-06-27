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

static rt_list_t          _timer_list   = RT_LIST_OBJECT_INIT(_timer_list);
static RT_DEFINE_SPINLOCK(_spinlock);

rt_inline rt_ktime_hrtimer_t _first_hrtimer(void)
{
    return rt_list_isempty(&_timer_list) ? RT_NULL : rt_list_first_entry(&_timer_list, struct rt_ktime_hrtimer, node);
}

rt_weak rt_uint64_t rt_ktime_hrtimer_getres(void)
{
    return ((1000ULL * 1000 * 1000) * RT_KTIME_RESMUL) / RT_TICK_PER_SECOND;
}

rt_weak unsigned long rt_ktime_hrtimer_getfrq(void)
{
    return RT_TICK_PER_SECOND;
}

rt_weak unsigned long rt_ktime_hrtimer_getcnt(void)
{
    return rt_tick_get();
}

rt_weak rt_err_t rt_ktime_hrtimer_settimeout(unsigned long cnt)
{
    static rt_timer_t timer = RT_NULL;
    static struct rt_timer _sh_rtimer;

    RT_ASSERT(cnt > 0);

    if (timer == RT_NULL)
    {
        timer = &_sh_rtimer;
        rt_timer_init(timer, "shrtimer", (void (*)(void *))rt_ktime_hrtimer_process, RT_NULL, cnt, RT_TIMER_FLAG_ONE_SHOT);
    }
    else
    {
        rt_tick_t tick = cnt;
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

static void _hrtimer_process_locked(void)
{
    rt_ktime_hrtimer_t timer;

    for (timer = _first_hrtimer();
        (timer != RT_NULL) && (timer->timeout_cnt <= rt_ktime_cputimer_getcnt());
        timer = _first_hrtimer())
    {
        rt_list_remove(&(timer->node));

        if (timer->flag & RT_TIMER_FLAG_PERIODIC)
        {
            timer->timeout_cnt = timer->delay_cnt + rt_ktime_cputimer_getcnt();
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
    rt_ktime_hrtimer_t timer;
    rt_ubase_t next_timeout_hrtimer_cnt;
    rt_bool_t find_next;

    do
    {
        find_next = RT_FALSE;
        if ((timer = _first_hrtimer()) != RT_NULL)
        {
            next_timeout_hrtimer_cnt = _cnt_convert(timer->timeout_cnt);
            if (next_timeout_hrtimer_cnt > 0)
            {
                rt_ktime_hrtimer_settimeout(next_timeout_hrtimer_cnt);
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

void rt_ktime_hrtimer_process(void)
{
    rt_base_t level = rt_spin_lock_irqsave(&_spinlock);

    _hrtimer_process_locked();
    _set_next_timeout_locked();

    rt_spin_unlock_irqrestore(&_spinlock, level);
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

    rt_memset(timer, 0, sizeof(struct rt_ktime_hrtimer));

    timer->flag         = flag & ~RT_TIMER_FLAG_ACTIVATED;
    timer->timeout_func = timeout;
    timer->parameter    = parameter;
    rt_strncpy(timer->name, name, RT_NAME_MAX - 1);
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

    rt_list_remove(&timer->node);
    timer->flag &= ~RT_TIMER_FLAG_ACTIVATED;
    _set_next_timeout_locked();

    rt_spin_unlock_irqrestore(&_spinlock, level);

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
        rt_list_remove(&timer->node);
        _set_next_timeout_locked();
    }

    rt_spin_unlock_irqrestore(&_spinlock, level);

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

    err = rt_ktime_hrtimer_start(timer, cnt);
    if (err)
        return err;

    err = rt_completion_wait_flags(&(timer->completion), RT_WAITING_FOREVER,
                                   RT_INTERRUPTIBLE);
    rt_ktime_hrtimer_keep_errno(timer, err);

    return err;
}

rt_err_t rt_ktime_hrtimer_ndelay(struct rt_ktime_hrtimer *timer, unsigned long ns)
{
    rt_uint64_t res = rt_ktime_cputimer_getres();
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
