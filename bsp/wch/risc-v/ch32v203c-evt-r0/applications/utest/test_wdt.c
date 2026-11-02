/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-23     seteiro      CH32V203: independent watchdog utest
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <utest.h>

#define WDT_TIMEOUT_SECONDS  5
#define WDT_FEED_WAIT_MS     8000
#define WDT_NOFEED_WAIT_MS   8000

static rt_device_t wdg_dev;
static int feed;

static void idle_hook(void)
{
    if (feed && wdg_dev != RT_NULL)
    {
        rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, RT_NULL);
    }
}

static void test_wdt(void)
{
    rt_uint32_t timeout = WDT_TIMEOUT_SECONDS;
    rt_err_t err;

    wdg_dev = rt_device_find("wdt");
    uassert_not_null(wdg_dev);
    if (wdg_dev == RT_NULL)
    {
        return;
    }

    err = rt_device_init(wdg_dev);
    uassert_int_equal(err, RT_EOK);
    if (err != RT_EOK)
    {
        return;
    }

    err = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    uassert_int_equal(err, RT_EOK);
    if (err != RT_EOK)
    {
        return;
    }

    feed = 1;
    err = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_START, RT_NULL);
    uassert_int_equal(err, RT_EOK);
    if (err != RT_EOK)
    {
        feed = 0;
        return;
    }

    /* Keep feeding longer than the timeout. The shell is still up if this returns. */
    rt_thread_mdelay(WDT_FEED_WAIT_MS);

    /* This IWDG cannot be stopped. Clearing the hook should reset the board. */
    feed = 0;
    rt_thread_mdelay(WDT_NOFEED_WAIT_MS);
    uassert_true(0);
}

static rt_err_t utest_tc_init(void)
{
    feed = 0;
    wdg_dev = RT_NULL;
    rt_thread_idle_sethook(idle_hook);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    feed = 0;
    rt_thread_idle_delhook(idle_hook);
    return RT_EOK;
}

UTEST_TC_EXPORT(test_wdt, "bsp.ch32v203.drivers.wdt", utest_tc_init, utest_tc_cleanup, 20);
