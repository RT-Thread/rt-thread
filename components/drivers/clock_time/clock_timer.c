/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2015-08-31     heyuanjie87    first version
 */

#include <rtdevice.h>
#include <rthw.h>
#include <drivers/clock_time.h>

#define DBG_TAG "clock_timer"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_DM
void (*rt_clock_timer_us_delay)(rt_uint32_t us) = RT_NULL;

rt_weak void rt_hw_us_delay(rt_uint32_t us)
{
    if (rt_clock_timer_us_delay)
    {
        rt_clock_timer_us_delay(us);
    }
    else
    {
        LOG_E("Implemented at least in the libcpu");

        RT_ASSERT(0);
    }
}
#endif /* RT_USING_DM */

static struct rt_clock_time_device _clock_timer_clock_dev;
static rt_clock_timer_t *_clock_timer_owner = RT_NULL;

static rt_uint64_t _clock_timer_clock_get_freq(struct rt_clock_time_device *dev)
{
    RT_UNUSED(dev);
    if (_clock_timer_owner == RT_NULL)
    {
        return 0;
    }

    return (rt_uint64_t)_clock_timer_owner->freq;
}

static rt_uint64_t _clock_timer_clock_get_counter(struct rt_clock_time_device *dev)
{
    RT_UNUSED(dev);
    if (_clock_timer_owner == RT_NULL ||
        _clock_timer_owner->ops == RT_NULL ||
        _clock_timer_owner->ops->count_get == RT_NULL)
    {
        return 0;
    }

    return (rt_uint64_t)_clock_timer_owner->ops->count_get(_clock_timer_owner);
}

static rt_err_t _clock_timer_clock_set_timeout(struct rt_clock_time_device *dev, rt_uint64_t delta)
{
    RT_UNUSED(dev);
    if (_clock_timer_owner == RT_NULL ||
        _clock_timer_owner->ops == RT_NULL ||
        _clock_timer_owner->ops->start == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    if (delta == 0)
    {
        if (_clock_timer_owner->ops->stop)
        {
            _clock_timer_owner->ops->stop(_clock_timer_owner);
        }
        return RT_EOK;
    }

    if (_clock_timer_owner->ops->stop)
    {
        _clock_timer_owner->ops->stop(_clock_timer_owner);
    }

    _clock_timer_owner->mode = CLOCK_TIMER_MODE_ONESHOT;

    if (delta > (rt_uint64_t)RT_UINT32_MAX)
    {
        delta = RT_UINT32_MAX;
    }

    return _clock_timer_owner->ops->start(_clock_timer_owner, (rt_uint32_t)delta, CLOCK_TIMER_MODE_ONESHOT);
}

static const struct rt_clock_time_ops _clock_timer_clock_ops =
{
    _clock_timer_clock_get_freq,
    _clock_timer_clock_get_counter,
    _clock_timer_clock_set_timeout,
};

rt_inline rt_uint32_t timeout_calc(rt_clock_timer_t *timer, rt_clock_timerval_t *tv)
{
    float overflow;
    float timeout;
    rt_uint32_t counter;
    int i, index = 0;
    float tv_sec;
    float devi_min = 1;
    float devi;

    /* changed to second */
    overflow = timer->info->maxcnt/(float)timer->freq;
    tv_sec = tv->sec + tv->usec/(float)1000000;

    if (tv_sec < (1/(float)timer->freq))
    {
        /* little timeout */
        i = 0;
        timeout = 1/(float)timer->freq;
    }
    else
    {
        for (i = 1; i > 0; i ++)
        {
            timeout = tv_sec/i;

            if (timeout <= overflow)
            {
                counter = (rt_uint32_t)(timeout * timer->freq);
                devi = tv_sec - (counter / (float)timer->freq) * i;
                /* Minimum calculation error */
                if (devi > devi_min)
                {
                    i = index;
                    timeout = tv_sec/i;
                    break;
                }
                else if (devi == 0)
                {
                    break;
                }
                else if (devi < devi_min)
                {
                    devi_min = devi;
                    index = i;
                }
            }
        }
    }

    timer->cycles = i;
    timer->reload = i;
    timer->period_sec = timeout;
    counter = (rt_uint32_t)(timeout * timer->freq);

    return counter;
}

static rt_err_t rt_clock_timer_init(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;
    rt_clock_timer_t *timer;

    timer = (rt_clock_timer_t *)dev;
    /* try to change to 1MHz */
    if ((1000000 <= timer->info->maxfreq) && (1000000 >= timer->info->minfreq))
    {
        timer->freq = 1000000;
    }
    else
    {
        timer->freq = timer->info->minfreq;
    }
    timer->mode = CLOCK_TIMER_MODE_ONESHOT;
    timer->cycles = 0;
    timer->overflow = 0;

    if (timer->ops->init)
    {
        timer->ops->init(timer, 1);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}

static rt_err_t rt_clock_timer_open(struct rt_device *dev, rt_uint16_t oflag)
{
    rt_err_t result = RT_EOK;
    rt_clock_timer_t *timer;

    timer = (rt_clock_timer_t *)dev;
    if (timer->ops->control != RT_NULL)
    {
        timer->ops->control(timer, CLOCK_TIMER_CTRL_FREQ_SET, &timer->freq);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}

static rt_err_t rt_clock_timer_close(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;
    rt_clock_timer_t *timer;

    timer = (rt_clock_timer_t*)dev;
    if (timer->ops->init != RT_NULL)
    {
        timer->ops->init(timer, 0);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    dev->flag &= ~RT_DEVICE_FLAG_ACTIVATED;
    dev->rx_indicate = RT_NULL;

    return result;
}

static rt_ssize_t rt_clock_timer_read(struct rt_device *dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_clock_timer_t *timer;
    rt_clock_timerval_t tv;
    rt_uint32_t cnt;
    rt_base_t level;
    rt_int32_t overflow;
    float t;

    timer = (rt_clock_timer_t *)dev;
    if (timer->ops->count_get == RT_NULL)
        return 0;

    level = rt_hw_interrupt_disable();
    cnt = timer->ops->count_get(timer);
    overflow = timer->overflow;
    rt_hw_interrupt_enable(level);

    if (timer->info->cntmode == CLOCK_TIMER_CNTMODE_DW)
    {
        cnt = (rt_uint32_t)(timer->freq * timer->period_sec) - cnt;
    }
    if (timer->mode == CLOCK_TIMER_MODE_ONESHOT)
    {
        overflow = 0;
    }

    t = overflow * timer->period_sec + cnt/(float)timer->freq;
    tv.sec = (rt_int32_t)t;
    tv.usec = (rt_int32_t)((t - tv.sec) * 1000000);
    size = size > sizeof(tv)? sizeof(tv) : size;
    rt_memcpy(buffer, &tv, size);

    return size;
}

static rt_ssize_t rt_clock_timer_write(struct rt_device *dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_base_t level;
    rt_uint32_t t;
    rt_clock_timer_mode_t opm = CLOCK_TIMER_MODE_PERIOD;
    rt_clock_timer_t *timer;

    timer = (rt_clock_timer_t *)dev;
    if ((timer->ops->start == RT_NULL) || (timer->ops->stop == RT_NULL))
        return 0;

    if (size != sizeof(rt_clock_timerval_t))
        return 0;

    timer->ops->stop(timer);

    level = rt_hw_interrupt_disable();
    timer->overflow = 0;
    rt_hw_interrupt_enable(level);

    t = timeout_calc(timer, (rt_clock_timerval_t*)buffer);
    if ((timer->cycles <= 1) && (timer->mode == CLOCK_TIMER_MODE_ONESHOT))
    {
        opm = CLOCK_TIMER_MODE_ONESHOT;
    }

    if (timer->ops->start(timer, t, opm) != RT_EOK)
        size = 0;

    return size;
}

static rt_err_t rt_clock_timer_control(struct rt_device *dev, int cmd, void *args)
{
    rt_base_t level;
    rt_err_t result = RT_EOK;
    rt_clock_timer_t *timer;

    timer = (rt_clock_timer_t *)dev;

    switch (cmd)
    {
    case CLOCK_TIMER_CTRL_STOP:
    {
        if (timer->ops->stop != RT_NULL)
        {
            timer->ops->stop(timer);
        }
        else
        {
            result = -RT_ENOSYS;
        }
    }
    break;
    case CLOCK_TIMER_CTRL_FREQ_SET:
    {
        rt_int32_t *f;

        if (args == RT_NULL)
        {
            result = -RT_EEMPTY;
            break;
        }

        f = (rt_int32_t*)args;
        if ((*f > timer->info->maxfreq) || (*f < timer->info->minfreq))
        {
            LOG_W("frequency setting out of range! It will maintain at %d Hz", timer->freq);
            result = -RT_EINVAL;
            break;
        }

        if (timer->ops->control != RT_NULL)
        {
            result = timer->ops->control(timer, cmd, args);
            if (result == RT_EOK)
            {
                level = rt_hw_interrupt_disable();
                timer->freq = *f;
                rt_hw_interrupt_enable(level);
            }
        }
        else
        {
            result = -RT_ENOSYS;
        }
    }
    break;
    case CLOCK_TIMER_CTRL_INFO_GET:
    {
        if (args == RT_NULL)
        {
            result = -RT_EEMPTY;
            break;
        }

        *((struct rt_clock_timer_info*)args) = *timer->info;
    }
    break;
    case CLOCK_TIMER_CTRL_MODE_SET:
    {
        rt_clock_timer_mode_t *m;

        if (args == RT_NULL)
        {
            result = -RT_EEMPTY;
            break;
        }

        m = (rt_clock_timer_mode_t*)args;

        if ((*m != CLOCK_TIMER_MODE_ONESHOT) && (*m != CLOCK_TIMER_MODE_PERIOD))
        {
            result = -RT_ERROR;
            break;
        }
        level = rt_hw_interrupt_disable();
        timer->mode = *m;
        rt_hw_interrupt_enable(level);
    }
    break;
    default:
    {
        if (timer->ops->control != RT_NULL)
        {
            result = timer->ops->control(timer, cmd, args);
        }
        else
        {
            result = -RT_ENOSYS;
        }
    }
    break;
    }

    return result;
}

void rt_clock_timer_isr(rt_clock_timer_t *timer)
{
    rt_base_t level;

    RT_ASSERT(timer != RT_NULL);

    level = rt_hw_interrupt_disable();

    timer->overflow ++;

    if (timer->cycles != 0)
    {
        timer->cycles --;
    }

    if (timer->cycles == 0)
    {
        timer->cycles = timer->reload;

        rt_hw_interrupt_enable(level);

        if (timer->mode == CLOCK_TIMER_MODE_ONESHOT)
        {
            if (timer->ops->stop != RT_NULL)
            {
                timer->ops->stop(timer);
            }
        }

    if (timer == _clock_timer_owner)
        {
            rt_clock_time_event_isr();
        }

        if (timer->parent.rx_indicate != RT_NULL)
        {
            timer->parent.rx_indicate(&timer->parent, sizeof(struct rt_clock_timerval));
        }
    }
    else
    {
        rt_hw_interrupt_enable(level);
    }
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops clock_timer_ops =
{
    rt_clock_timer_init,
    rt_clock_timer_open,
    rt_clock_timer_close,
    rt_clock_timer_read,
    rt_clock_timer_write,
    rt_clock_timer_control
};
#endif

rt_err_t rt_clock_timer_register(rt_clock_timer_t *timer, const char *name, void *user_data)
{
    struct rt_device *device;
    rt_err_t result;
    rt_uint8_t caps = 0;

    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(timer->ops != RT_NULL);
    RT_ASSERT(timer->info != RT_NULL);

    device = &(timer->parent);

    device->type        = RT_Device_Class_Timer;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &clock_timer_ops;
#else
    device->init        = rt_clock_timer_init;
    device->open        = rt_clock_timer_open;
    device->close       = rt_clock_timer_close;
    device->read        = rt_clock_timer_read;
    device->write       = rt_clock_timer_write;
    device->control     = rt_clock_timer_control;
#endif
    device->user_data   = user_data;

    result = rt_device_register(device, name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
    if (result != RT_EOK)
    {
        return result;
    }

    if (timer->ops->start)
    {
        caps |= RT_CLOCK_TIME_CAP_EVENT;
    }

    if (caps && _clock_timer_owner == RT_NULL)
    {
        char ct_name[RT_NAME_MAX];

        _clock_timer_owner = timer;
        _clock_timer_clock_dev.ops = &_clock_timer_clock_ops;
        _clock_timer_clock_dev.res_scale = RT_CLOCK_TIME_RESMUL;
        _clock_timer_clock_dev.caps = caps;

        rt_snprintf(ct_name, sizeof(ct_name), "clock_time_%s", name);
        rt_clock_time_device_register(&_clock_timer_clock_dev, ct_name, caps);

        if ((caps & RT_CLOCK_TIME_CAP_EVENT) && rt_clock_time_get_default_event() == RT_NULL)
        {
            rt_clock_time_set_default_event(&_clock_timer_clock_dev);
            if (!(device->flag & RT_DEVICE_FLAG_ACTIVATED))
            {
                rt_device_init(device);
                rt_device_open(device, RT_DEVICE_OFLAG_RDWR);
            }
        }
    }

    return RT_EOK;
}
