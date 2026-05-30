/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "wdt.rk8xx"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rk8xx.h"

struct rk8xx_watchdog
{
    rt_watchdog_t parent;

    int irq;
    rt_uint8_t timeout_idx;
    struct rk8xx *rk8xx;
};

#define raw_to_rk8xx_watchdog(raw) rt_container_of(raw, struct rk8xx_watchdog, parent)

static const unsigned int time_ms_ranges[] =
{
    [0] = 50,               /* 50 ms */
    [1] = 100,              /* 100 ms */
    [2] = 500,              /* 500 ms */
    [4] = 2 * 1000,         /* 2 s */
    [5] = 10 * 1000,        /* 10 s */
    [6] = 60 * 1000,        /* 1 min */
    [7] = 10 * 60 * 10000,  /* 10 min */
};

static rt_err_t rk8xx_watchdog_enable(struct rk8xx_watchdog *rk8xx_wdt,
        rt_bool_t enable)
{
    return rk8xx_update_bits(rk8xx_wdt->rk8xx, RK806_WDT, RK806_WDT_EN, !!enable);
}

static rt_err_t rk8xx_watchdog_keep_alive(struct rk8xx_watchdog *rk8xx_wdt)
{
    rt_err_t err;
    /*
     * Should to clear the interruption of WDT after set time,
     * otherwise the time will advance 1S.
     */
    rk8xx_watchdog_enable(rk8xx_wdt, RT_FALSE);

    err = rk8xx_update_bits(rk8xx_wdt->rk8xx, RK806_WDT, RK806_WDT_SET,
            rk8xx_wdt->timeout_idx);

    rk8xx_watchdog_enable(rk8xx_wdt, RT_TRUE);

    return err;
}

static rt_err_t rk8xx_watchdog_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}

static rt_err_t rk8xx_watchdog_control(rt_watchdog_t *wdt, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct rk8xx_watchdog *rk8xx_wdt = raw_to_rk8xx_watchdog(wdt);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *(rt_uint32_t *)args = time_ms_ranges[rk8xx_wdt->timeout_idx] / 1000;
        break;

    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        {
            rt_uint32_t timeout = *(rt_uint32_t *)args * 1000;
            err = -RT_EINVAL;

            for (int i = RT_ARRAY_SIZE(time_ms_ranges) - 1; i >= 0; --i)
            {
                if (timeout >= time_ms_ranges[i])
                {
                    rk8xx_wdt->timeout_idx = i;

                    err = RT_EOK;
                    break;
                }
            }
        }
        break;

    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        err = rk8xx_watchdog_keep_alive(rk8xx_wdt);
        break;

    case RT_DEVICE_CTRL_WDT_START:
        err = rk8xx_watchdog_enable(rk8xx_wdt, RT_TRUE);
        break;

    case RT_DEVICE_CTRL_WDT_STOP:
        err = rk8xx_watchdog_enable(rk8xx_wdt, RT_FALSE);
        break;

    default:
        err = -RT_EINVAL;
    }

    return err;
}

static const struct rt_watchdog_ops rk8xx_watchdog_ops =
{
    .init = rk8xx_watchdog_init,
    .control = rk8xx_watchdog_control,
};

static rt_err_t rk8xx_watchdog_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *dev_name;
    struct rk8xx *rk8xx = pdev->priv;
    struct rt_device *dev = &pdev->parent;
    struct rk8xx_watchdog *rk8xx_wdt = rt_calloc(1, sizeof(*rk8xx_wdt));

    if (!rk8xx_wdt)
    {
        return -RT_ENOMEM;
    }

    rk8xx_wdt->rk8xx = rk8xx;

    rk8xx_wdt->irq = rt_dm_dev_get_irq(dev, 0);

    if (rk8xx_wdt->irq < 0)
    {
        err = rk8xx_wdt->irq;
        goto _fail;
    }

    if ((err = rk8xx_update_bits(rk8xx, RK806_WDT, RK806_WDT_ACT, RK806_WDT_ACT_RESTART)))
    {
        goto _fail;
    }

    dev->user_data = rk8xx_wdt;

    rk8xx_wdt->parent.ops = &rk8xx_watchdog_ops;

    rt_dm_dev_set_name_auto(&rk8xx_wdt->parent.parent, "wdt");
    dev_name = rt_dm_dev_get_name(&rk8xx_wdt->parent.parent);

    rt_hw_watchdog_register(&rk8xx_wdt->parent, dev_name, 0, rk8xx_wdt);

    return RT_EOK;

_fail:
    rt_free(rk8xx_wdt);

    return err;
}

static rt_err_t rk8xx_watchdog_remove(struct rt_platform_device *pdev)
{
    struct rk8xx_watchdog *rk8xx_wdt = pdev->parent.user_data;

    rk8xx_watchdog_enable(rk8xx_wdt, RT_FALSE);

    rt_device_unregister(&rk8xx_wdt->parent.parent);

    rt_free(rk8xx_wdt);

    return RT_EOK;
}

static struct rt_platform_driver rk8xx_watchdog_driver =
{
    .name = "rk8xx-watchdog",
    .probe = rk8xx_watchdog_probe,
    .remove = rk8xx_watchdog_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rk8xx_watchdog_driver);
