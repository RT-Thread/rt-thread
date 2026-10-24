/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-10-17     seteiro      add watchdog smoke utest for #11446
 */

/**
 * Test Case Name: Watchdog Smoke Test
 *
 * Test Objectives:
 * - Verify that the watchdog device can be found and opened.
 * - Verify SET_TIMEOUT / GET_TIMEOUT round-trip.
 * - Optionally verify START / KEEPALIVE / STOP when enabled.
 *
 * Dependencies:
 * - Requires `RT_UTEST_WDT` and `RT_USING_WDT`.
 * - BSP must register a watchdog device (default name `wdt`).
 * - START path is optional (`RT_UTEST_WDT_START`); leave it off when the
 *   hardware cannot stop the WDT, otherwise the board may reset.
 *
 * Expected Results:
 * - Find/open and timeout set/get checks pass.
 * - When START is enabled, start/keepalive/stop also pass.
 *
 * Board notes:
 * - qemu-vexpress-a9 enables `RT_USING_WDT` but does not register a WDT
 *   device; enable this case on a BSP that provides `wdt` (e.g. CH32/STM32).
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/dev_watchdog.h>
#include "utest.h"

#ifdef RT_UTEST_WDT

#ifndef RT_UTEST_WDT_DEVICE_NAME
#define RT_UTEST_WDT_DEVICE_NAME "wdt"
#endif

#ifndef RT_UTEST_WDT_TIMEOUT_SEC
#define RT_UTEST_WDT_TIMEOUT_SEC 5
#endif

#define WDT_TC_SUITE_TIMEOUT 10

static rt_device_t wdt_tc_device;
static rt_bool_t wdt_tc_device_opened;

static void wdt_timeout_set_get_test(void)
{
    rt_err_t result;
    rt_uint32_t timeout;
    rt_uint32_t readback;

    timeout = RT_UTEST_WDT_TIMEOUT_SEC;
    result = rt_device_control(wdt_tc_device, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        return;
    }

    readback = 0;
    result = rt_device_control(wdt_tc_device, RT_DEVICE_CTRL_WDT_GET_TIMEOUT, &readback);
    if (result == -RT_ENOSYS)
    {
        LOG_W("GET_TIMEOUT not supported, skip readback check");
        return;
    }

    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        return;
    }

    LOG_I("WDT timeout set=%u get=%u", (unsigned)timeout, (unsigned)readback);
    uassert_int_equal(readback, timeout);
}

#ifdef RT_UTEST_WDT_START
static void wdt_start_keepalive_stop_test(void)
{
    rt_err_t result;
    rt_uint32_t timeout;

    timeout = RT_UTEST_WDT_TIMEOUT_SEC;
    result = rt_device_control(wdt_tc_device, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        return;
    }

    result = rt_device_control(wdt_tc_device, RT_DEVICE_CTRL_WDT_START, RT_NULL);
    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        return;
    }

    result = rt_device_control(wdt_tc_device, RT_DEVICE_CTRL_WDT_KEEPALIVE, RT_NULL);
    uassert_int_equal(result, RT_EOK);

    result = rt_device_control(wdt_tc_device, RT_DEVICE_CTRL_WDT_STOP, RT_NULL);
    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        LOG_E("WDT STOP failed; board may reset when timeout expires");
    }
}
#endif /* RT_UTEST_WDT_START */

static rt_err_t utest_tc_init(void)
{
    rt_err_t result;
    rt_device_t wdt_device;

    wdt_tc_device = RT_NULL;
    wdt_tc_device_opened = RT_FALSE;

    wdt_device = rt_device_find(RT_UTEST_WDT_DEVICE_NAME);
    if (wdt_device == RT_NULL)
    {
        LOG_E("Watchdog device %s is not registered", RT_UTEST_WDT_DEVICE_NAME);
        return -RT_ERROR;
    }
    if (wdt_device->type != RT_Device_Class_WDT)
    {
        LOG_E("Device %s is not a watchdog device", RT_UTEST_WDT_DEVICE_NAME);
        return -RT_ERROR;
    }

    result = rt_device_open(wdt_device, RT_DEVICE_OFLAG_RDWR);
    if (result != RT_EOK)
    {
        return result;
    }

    wdt_tc_device = wdt_device;
    wdt_tc_device_opened = RT_TRUE;
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_err_t result;

    result = RT_EOK;
    if (wdt_tc_device_opened)
    {
        result = rt_device_close(wdt_tc_device);
        wdt_tc_device = RT_NULL;
        wdt_tc_device_opened = RT_FALSE;
    }

    return result;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(wdt_timeout_set_get_test);
#ifdef RT_UTEST_WDT_START
    UTEST_UNIT_RUN(wdt_start_keepalive_stop_test);
#endif
}

UTEST_TC_EXPORT(testcase,
                "components.drivers.watchdog.smoke",
                utest_tc_init,
                utest_tc_cleanup,
                WDT_TC_SUITE_TIMEOUT);

#endif /* RT_UTEST_WDT */
