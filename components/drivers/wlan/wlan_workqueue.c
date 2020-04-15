/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-19     tyx          the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <wlan_workqueue.h>
#include <ipc/workqueue.h>

#define DBG_TAG "WLAN.work"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_WLAN_WORK_THREAD_ENABLE

struct rt_wlan_work
{
    struct rt_work work;
    void (*fun)(void *parameter);
    void *parameter;
};

static struct rt_workqueue *wlan_workqueue;

static void rt_wlan_workqueue_fun(struct rt_work *work, void *work_data)
{
    struct rt_wlan_work *wlan_work = work_data;

    wlan_work->fun(wlan_work->parameter);
    rt_free(wlan_work);
}

struct rt_workqueue *rt_wlan_get_workqueue(void)
{
    return wlan_workqueue;
}

rt_err_t rt_wlan_workqueue_dowork(void (*func)(void *parameter), void *parameter)
{
    struct rt_wlan_work *wlan_work;
    rt_err_t err = RT_EOK;

    LOG_D("F:%s is run", __FUNCTION__);
    if (func == RT_NULL)
    {
        LOG_E("F:%s L:%d func is null", __FUNCTION__, __LINE__);
        return -RT_EINVAL;
    }

    if (wlan_workqueue == RT_NULL)
    {
        LOG_E("F:%s L:%d not init wlan work queue", __FUNCTION__, __LINE__);
        return -RT_ERROR;
    }

    wlan_work = rt_malloc(sizeof(struct rt_wlan_work));
    if (wlan_work == RT_NULL)
    {
        LOG_E("F:%s L:%d create work failed", __FUNCTION__, __LINE__);
        return -RT_ENOMEM;
    }
    wlan_work->fun = func;
    wlan_work->parameter = parameter;
    rt_work_init(&wlan_work->work, rt_wlan_workqueue_fun, wlan_work);
    err = rt_workqueue_dowork(wlan_workqueue, &wlan_work->work);
    if (err != RT_EOK)
    {
        LOG_E("F:%s L:%d do work failed", __FUNCTION__, __LINE__);
        rt_free(wlan_work);
        return err;
    }
    return err;
}

int rt_wlan_workqueue_init(void)
{
    static rt_int8_t _init_flag = 0;

    if (_init_flag == 0)
    {
        wlan_workqueue = rt_workqueue_create(RT_WLAN_WORKQUEUE_THREAD_NAME, RT_WLAN_WORKQUEUE_THREAD_SIZE,
                                             RT_WLAN_WORKQUEUE_THREAD_PRIO);
        if (wlan_workqueue == RT_NULL)
        {
            LOG_E("F:%s L:%d wlan work queue create failed", __FUNCTION__, __LINE__);
            return -1;
        }
        _init_flag = 1;
        return 0;
    }
    return 0;
}
INIT_PREV_EXPORT(rt_wlan_workqueue_init);

#endif
