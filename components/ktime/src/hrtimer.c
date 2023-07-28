/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-10     xqyjlj       The first version.
 */

#include <rtdevice.h>
#include <rthw.h>
#include <rtthread.h>

#include "ktime.h"

#ifdef ARCH_CPU_64BIT
#define _HRTIMER_MAX_CNT UINT64_MAX
#else
#define _HRTIMER_MAX_CNT UINT32_MAX
#endif

static rt_list_t          _timer_list = RT_LIST_OBJECT_INIT(_timer_list);
static rt_ktime_hrtimer_t _nowtimer   = RT_NULL;
static struct rt_spinlock _spinlock;

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
    struct rt_semaphore *sem;
    sem = (struct rt_semaphore *)parameter;
    rt_sem_release(sem);
}

static void _set_next_timeout(void);
static void _timeout_callback(void *parameter)
{
    rt_ktime_hrtimer_t timer;
    timer = (rt_ktime_hrtimer_t)parameter;
    rt_base_t level;

    level     = rt_spin_lock_irqsave(&_spinlock);
    _nowtimer = RT_NULL;
    rt_list_remove(&(timer->row));
    if (timer->parent.flag & RT_TIMER_FLAG_ACTIVATED)
    {
        rt_spin_unlock_irqrestore(&_spinlock, level);
        timer->timeout_func(timer->parameter);
    }
    else
    {
        rt_spin_unlock_irqrestore(&_spinlock, level);
    }

    _set_next_timeout();
}

static void _set_next_timeout(void)
{
    rt_ktime_hrtimer_t t;
    rt_base_t          level;

    level = rt_spin_lock_irqsave(&_spinlock);
    if (&_timer_list != _timer_list.prev)
    {
        t = rt_list_entry((&_timer_list)->next, struct rt_ktime_hrtimer, row);
        if (_nowtimer != RT_NULL)
        {
            if (t != _nowtimer && t->timeout_cnt < _nowtimer->timeout_cnt)
            {
                _nowtimer = t;
                rt_spin_unlock_irqrestore(&_spinlock, level);
                rt_ktime_hrtimer_settimeout(_cnt_convert(t->timeout_cnt), _timeout_callback, t);
            }
            else
            {
                rt_spin_unlock_irqrestore(&_spinlock, level);
            }
        }
        else
        {
            _nowtimer = t;
            rt_spin_unlock_irqrestore(&_spinlock, level);
            rt_ktime_hrtimer_settimeout(_cnt_convert(t->timeout_cnt), _timeout_callback, t);
        }
    }
    else
    {
        _nowtimer = RT_NULL;
        rt_spin_unlock_irqrestore(&_spinlock, level);
        rt_ktime_hrtimer_settimeout(0, RT_NULL, RT_NULL);
    }
}

void rt_ktime_hrtimer_init(rt_ktime_hrtimer_t timer,
                           const char        *name,
                           unsigned long      cnt,
                           rt_uint8_t         flag,
                           void (*timeout)(void *parameter),
                           void *parameter)
{
    /* parameter check */
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(timeout != RT_NULL);
    RT_ASSERT(cnt < (_HRTIMER_MAX_CNT / 2));

    /* set flag */
    timer->parent.flag = flag;

    /* set deactivated */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
    timer->timeout_func = timeout;
    timer->parameter    = parameter;
    timer->timeout_cnt  = cnt + rt_ktime_cputimer_getcnt();
    timer->init_cnt     = cnt;

    rt_list_init(&(timer->row));
    rt_sem_init(&(timer->sem), "hrtimer", 0, RT_IPC_FLAG_PRIO);
}

rt_err_t rt_ktime_hrtimer_start(rt_ktime_hrtimer_t timer)
{
    rt_list_t *timer_list;
    rt_base_t  level;

    /* parameter check */
    RT_ASSERT(timer != RT_NULL);

    level = rt_spin_lock_irqsave(&_spinlock);
    rt_list_remove(&timer->row); /* remove timer from list */
    /* change status of timer */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
    timer_list = &_timer_list;
    for (; timer_list != _timer_list.prev; timer_list = timer_list->next)
    {
        rt_ktime_hrtimer_t t;
        rt_list_t         *p = timer_list->next;

        t = rt_list_entry(p, struct rt_ktime_hrtimer, row);

        if ((t->timeout_cnt - timer->timeout_cnt) == 0)
        {
            continue;
        }
        else if ((t->timeout_cnt - timer->timeout_cnt) < (_HRTIMER_MAX_CNT / 2))
        {
            break;
        }
    }
    rt_list_insert_after(timer_list, &(timer->row));
    timer->parent.flag |= RT_TIMER_FLAG_ACTIVATED;
    rt_spin_unlock_irqrestore(&_spinlock, level);

    _set_next_timeout();

    return RT_EOK;
}

rt_err_t rt_ktime_hrtimer_stop(rt_ktime_hrtimer_t timer)
{
    rt_base_t level;

    RT_ASSERT(timer != RT_NULL); /* timer check */

    level = rt_spin_lock_irqsave(&_spinlock);
    if (!(timer->parent.flag & RT_TIMER_FLAG_ACTIVATED))
    {
        rt_spin_unlock_irqrestore(&_spinlock, level);
        return -RT_ERROR;
    }
    _nowtimer = RT_NULL;
    rt_list_remove(&timer->row);
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED; /* change status */
    rt_spin_unlock_irqrestore(&_spinlock, level);

    _set_next_timeout();

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
            *(unsigned long *)arg = timer->init_cnt;
            break;

        case RT_TIMER_CTRL_SET_TIME:
            RT_ASSERT((*(unsigned long *)arg) < (_HRTIMER_MAX_CNT / 2));
            timer->init_cnt    = *(unsigned long *)arg;
            timer->timeout_cnt = *(unsigned long *)arg + rt_ktime_cputimer_getcnt();
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

    level = rt_spin_lock_irqsave(&_spinlock);

    /* stop timer */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
    /* when interrupted */
    if (timer->error == -RT_EINTR || timer->error == RT_EINTR)
    {
        _nowtimer = RT_NULL;
        rt_list_remove(&timer->row);
        rt_spin_unlock_irqrestore(&_spinlock, level);
        _set_next_timeout();
    }
    else
    {
        rt_spin_unlock_irqrestore(&_spinlock, level);
    }
    rt_sem_detach(&(timer->sem));

    return RT_EOK;
}

/************************** delay ***************************/

rt_err_t rt_ktime_hrtimer_sleep(unsigned long cnt)
{
    struct rt_ktime_hrtimer timer;
    rt_err_t err;

    if (cnt == 0)
        return -RT_EINVAL;

    rt_ktime_hrtimer_init(&timer, "hrtimer_sleep", cnt, RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_HARD_TIMER,
                          _sleep_timeout, &(timer.sem));

    rt_ktime_hrtimer_start(&timer); /* reset the timeout of thread timer and start it */
    err = rt_sem_take_interruptible(&(timer.sem), RT_WAITING_FOREVER);
    rt_ktime_hrtimer_keep_errno(&timer, err);

    rt_ktime_hrtimer_detach(&timer);
    return RT_EOK;
}

rt_err_t rt_ktime_hrtimer_ndelay(unsigned long ns)
{
    unsigned long res = rt_ktime_cputimer_getres();
    return rt_ktime_hrtimer_sleep((ns * RT_KTIME_RESMUL) / res);
}

rt_err_t rt_ktime_hrtimer_udelay(unsigned long us)
{
    return rt_ktime_hrtimer_ndelay(us * 1000);
}

rt_err_t rt_ktime_hrtimer_mdelay(unsigned long ms)
{
    return rt_ktime_hrtimer_ndelay(ms * 1000000);
}

static int rt_ktime_hrtimer_lock_init(void)
{
    RT_UNUSED(_spinlock);
    rt_spin_lock_init(&_spinlock);
    return 0;
}
INIT_BOARD_EXPORT(rt_ktime_hrtimer_lock_init);
