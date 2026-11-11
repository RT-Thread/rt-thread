/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2026-06-18     wenzhi346     add NS800 rtc driver
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <time.h>
#include "drv_rtc.h"

struct ns800_rtc_backend
{
    const char *name;
    const struct ns800_rtc_ops *ops;
    void *user_data;
    rt_bool_t initialized;
};

static rt_rtc_dev_t g_rtc_dev;
static struct ns800_rtc_backend g_rtc_backend;

rt_err_t ns800_rtc_register(const char *name,
                            const struct ns800_rtc_ops *ops,
                            void *user_data)
{
    if ((ops == RT_NULL) || (ops->get_time == RT_NULL) || (ops->set_time == RT_NULL))
    {
        return -RT_EINVAL;
    }

    if (g_rtc_backend.ops != RT_NULL)
    {
        return -RT_EBUSY;
    }

    g_rtc_backend.name = (name != RT_NULL) ? name : "external";
    g_rtc_backend.ops = ops;
    g_rtc_backend.user_data = user_data;
    g_rtc_backend.initialized = RT_FALSE;

    return RT_EOK;
}

static rt_err_t ns800_rtc_init(void)
{
    rt_err_t ret;

    if (g_rtc_backend.ops == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    if (g_rtc_backend.initialized)
    {
        return RT_EOK;
    }

    ret = RT_EOK;
    if (g_rtc_backend.ops->init != RT_NULL)
    {
        ret = g_rtc_backend.ops->init(g_rtc_backend.user_data);
    }

    if (ret == RT_EOK)
    {
        g_rtc_backend.initialized = RT_TRUE;
    }

    return ret;
}

static rt_err_t ns800_rtc_get_secs(time_t *sec)
{
    struct tm time_struct;
    rt_err_t result;

    if (sec == RT_NULL)
    {
        return -RT_EINVAL;
    }

    result = ns800_rtc_init();
    if (result != RT_EOK)
    {
        return result;
    }

    result = g_rtc_backend.ops->get_time(g_rtc_backend.user_data, &time_struct);
    if (result == RT_EOK)
    {
        *sec = mktime(&time_struct);
    }

    return result;
}

static rt_err_t ns800_rtc_set_secs(time_t *sec)
{
    struct tm time_struct;
    rt_err_t result;

    if (sec == RT_NULL)
    {
        return -RT_EINVAL;
    }

    result = ns800_rtc_init();
    if (result != RT_EOK)
    {
        return result;
    }

    localtime_r(sec, &time_struct);

    return g_rtc_backend.ops->set_time(g_rtc_backend.user_data, &time_struct);
}

static rt_err_t ns800_rtc_get_timeval(struct timeval *tv)
{
    time_t sec;
    rt_err_t result;

    if (tv == RT_NULL)
    {
        return -RT_EINVAL;
    }

    result = ns800_rtc_get_secs(&sec);
    if (result != RT_EOK)
    {
        return result;
    }

    tv->tv_sec = sec;
    tv->tv_usec = 0;

    return RT_EOK;
}

static rt_err_t ns800_rtc_set_timeval(struct timeval *tv)
{
    time_t sec;

    if (tv == RT_NULL)
    {
        return -RT_EINVAL;
    }

    sec = tv->tv_sec;
    return ns800_rtc_set_secs(&sec);
}

static const struct rt_rtc_ops ns800_rtc_ops =
{
    ns800_rtc_init,
    ns800_rtc_get_secs,
    ns800_rtc_set_secs,
    RT_NULL,
    RT_NULL,
    ns800_rtc_get_timeval,
    ns800_rtc_set_timeval,
};

static rt_err_t ns800_rtc_try_init_device(void)
{
    rt_err_t result;

    result = rt_device_init(&g_rtc_dev.parent);
    if (result != RT_EOK)
    {
        rt_kprintf("rtc: %s init deferred, result %d\n", g_rtc_backend.name, result);
        return result;
    }

    rt_kprintf("rtc: %s ready\n", g_rtc_backend.name);
    return RT_EOK;
}

int rt_hw_rtc_init(void)
{
    rt_err_t result;

    if (g_rtc_backend.ops == RT_NULL)
    {
        rt_kprintf("rtc: no external backend registered\n");
        return -1;
    }

    g_rtc_dev.ops = &ns800_rtc_ops;

    result = rt_hw_rtc_register(&g_rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if (result != RT_EOK)
    {
        rt_kprintf("rtc: register failed, result %d\n", result);
        return -1;
    }

    ns800_rtc_try_init_device();
    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);

