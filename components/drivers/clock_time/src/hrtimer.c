/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-04     RT-Thread    Unified clock_time subsystem - hrtimer implementation
 */

#include <rtdevice.h>
#include <rthw.h>

#define DBG_TAG "clock_hrtimer"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef ARCH_CPU_64BIT
#define _HRTIMER_MAX_CNT UINT64_MAX
#else
#define _HRTIMER_MAX_CNT UINT32_MAX
#endif

static rt_list_t _timer_list = RT_LIST_OBJECT_INIT(_timer_list);
static RT_DEFINE_SPINLOCK(_spinlock);

rt_inline rt_clock_hrtimer_t _first_hrtimer(void)
{
    return rt_list_isempty(&_timer_list) ? RT_NULL : 
           rt_list_first_entry(&_timer_list, struct rt_clock_hrtimer, node);
}

static rt_err_t _set_hardware_timeout(rt_uint64_t cnt)
{
    struct rt_clock_time_device *dev = rt_clock_time_get_default();
    
    if (dev == RT_NULL || !(dev->caps & RT_CLOCK_TIME_CAP_CLOCKEVENT))
    {
        /* Fallback to software timer */
        static rt_timer_t timer = RT_NULL;
        static struct rt_timer _fallback_timer;
        
        RT_ASSERT(cnt > 0);
        
        if (timer == RT_NULL)
        {
            timer = &_fallback_timer;
            rt_timer_init(timer, "hrtimer_fb", 
                         (void (*)(void *))rt_clock_hrtimer_process, 
                         RT_NULL, cnt, RT_TIMER_FLAG_ONE_SHOT);
        }
        else
        {
            rt_tick_t tick = cnt;
            rt_timer_control(timer, RT_TIMER_CTRL_SET_TIME, &tick);
        }
        
        if (timer->parent.flag & RT_TIMER_FLAG_ACTIVATED)
        {
            rt_timer_stop(timer);
        }
        
        rt_timer_start(timer);
        return RT_EOK;
    }
    
    return dev->ops->set_timeout(cnt);
}

static void _insert_timer_to_list_locked(rt_clock_hrtimer_t timer)
{
    rt_clock_hrtimer_t iter;
    
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
    rt_clock_hrtimer_t timer;
    rt_uint64_t current_cnt = rt_clock_time_getcnt();
    
    for (timer = _first_hrtimer();
         (timer != RT_NULL) && (timer->timeout_cnt <= current_cnt);
         timer = _first_hrtimer())
    {
        rt_list_remove(&(timer->node));
        
        if (timer->flag & RT_TIMER_FLAG_PERIODIC)
        {
            timer->timeout_cnt = timer->delay_cnt + rt_clock_time_getcnt();
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

static rt_uint64_t _cnt_convert_to_hardware(rt_uint64_t target_cnt)
{
    rt_uint64_t current_cnt = rt_clock_time_getcnt();
    rt_uint64_t delta = target_cnt - current_cnt;
    
    /* Check for overflow or already expired */
    if (delta > (_HRTIMER_MAX_CNT / 2))
    {
        return 0;
    }
    
    /* Return delta, at least 1 */
    return delta == 0 ? 1 : delta;
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
            next_timeout_cnt = _cnt_convert_to_hardware(timer->timeout_cnt);
            if (next_timeout_cnt > 0)
            {
                _set_hardware_timeout(next_timeout_cnt);
            }
            else
            {
                /* Timer already expired, process it */
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
                          const char *name,
                          rt_uint8_t flag,
                          void (*timeout)(void *parameter),
                          void *parameter)
{
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(timeout != RT_NULL);
    
    rt_memset(timer, 0, sizeof(struct rt_clock_hrtimer));
    
    timer->flag = flag & ~RT_TIMER_FLAG_ACTIVATED;
    timer->timeout_func = timeout;
    timer->parameter = parameter;
    rt_strncpy(timer->name, name, RT_NAME_MAX - 1);
    rt_list_init(&(timer->node));
    rt_completion_init(&timer->completion);
}

rt_err_t rt_clock_hrtimer_start(rt_clock_hrtimer_t timer, rt_uint64_t delay_cnt)
{
    rt_base_t level;
    
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(delay_cnt < (_HRTIMER_MAX_CNT / 2));
    
    timer->delay_cnt = delay_cnt;
    timer->timeout_cnt = timer->delay_cnt + rt_clock_time_getcnt();
    
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
        *(rt_uint64_t *)arg = timer->delay_cnt;
        break;
        
    case RT_TIMER_CTRL_SET_TIME:
        RT_ASSERT((*(rt_uint64_t *)arg) < (_HRTIMER_MAX_CNT / 2));
        timer->delay_cnt = *(rt_uint64_t *)arg;
        timer->timeout_cnt = *(rt_uint64_t *)arg + rt_clock_time_getcnt();
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
        *(rt_uint64_t *)arg = timer->timeout_cnt;
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
        rt_spin_unlock_irqrestore(&_spinlock, level);
        return -RT_ERROR;
    }
    
    rt_spin_unlock_irqrestore(&_spinlock, level);
    
    return RT_EOK;
}

rt_err_t rt_clock_hrtimer_detach(rt_clock_hrtimer_t timer)
{
    rt_base_t level;
    
    RT_ASSERT(timer != RT_NULL);
    
    level = rt_spin_lock_irqsave(&_spinlock);
    
    if (timer->flag & RT_TIMER_FLAG_ACTIVATED)
    {
        rt_list_remove(&timer->node);
        timer->flag &= ~RT_TIMER_FLAG_ACTIVATED;
        _set_next_timeout_locked();
    }
    
    rt_spin_unlock_irqrestore(&_spinlock, level);
    
    rt_completion_detach(&timer->completion);
    
    return RT_EOK;
}

/* Delay functions */

static void _sleep_timeout(void *parameter)
{
    struct rt_clock_hrtimer *timer = parameter;
    rt_completion_done(&timer->completion);
}

rt_err_t rt_clock_hrtimer_sleep(rt_clock_hrtimer_t timer, rt_uint64_t cnt)
{
    RT_ASSERT(timer != RT_NULL);
    
    if (cnt == 0)
    {
        return -RT_EINVAL;
    }
    
    rt_clock_hrtimer_init(timer, "hrt_sleep", RT_TIMER_FLAG_ONE_SHOT, 
                         _sleep_timeout, timer);
    
    rt_err_t result = rt_clock_hrtimer_start(timer, cnt);
    if (result != RT_EOK)
    {
        return result;
    }
    
    rt_completion_wait(&timer->completion, RT_WAITING_FOREVER);
    rt_clock_hrtimer_detach(timer);
    
    return RT_EOK;
}

rt_err_t rt_clock_hrtimer_ndelay(rt_clock_hrtimer_t timer, rt_uint64_t ns)
{
    rt_uint64_t cnt = rt_clock_time_ns_to_cnt(ns);
    return rt_clock_hrtimer_sleep(timer, cnt);
}

rt_err_t rt_clock_hrtimer_udelay(rt_clock_hrtimer_t timer, rt_uint64_t us)
{
    return rt_clock_hrtimer_ndelay(timer, us * 1000);
}

rt_err_t rt_clock_hrtimer_mdelay(rt_clock_hrtimer_t timer, rt_uint64_t ms)
{
    return rt_clock_hrtimer_ndelay(timer, ms * 1000 * 1000);
}

/* Simple delay functions with internal timer */

rt_err_t rt_clock_ndelay(rt_uint64_t ns)
{
    struct rt_clock_hrtimer timer;
    return rt_clock_hrtimer_ndelay(&timer, ns);
}

rt_err_t rt_clock_udelay(rt_uint64_t us)
{
    struct rt_clock_hrtimer timer;
    return rt_clock_hrtimer_udelay(&timer, us);
}

rt_err_t rt_clock_mdelay(rt_uint64_t ms)
{
    struct rt_clock_hrtimer timer;
    return rt_clock_hrtimer_mdelay(&timer, ms);
}
