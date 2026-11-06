/*
 * Copyright (c) 2006-2026 Real Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-10-17     seteiro      add watchdog smoke utest for #11446
 * 2026-11-05     seteiro      tolerate timeout quantize, handle non-stoppable WDT
 *                             in cleanup (review feedback from Rbb666)
 */

/**
 * Test Case Name: Watchdog Smoke Test
 *
 * Test Objectives:
 * - Verify that the watchdog device can be found and opened.
 * - Verify SET_TIMEOUT / GET_TIMEOUT round-trip, tolerant to hardware
 *   quantization of the timeout value (e.g. STM32 LSI 32kHz, LSI-based
 *   prescaler: setting 5s may read back 4s).
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
 *
 * Cleanup notes:
 * - `rt_watchdog_close()` (the framework `close` hook) issues
 *   `RT_DEVICE_CTRL_WDT_STOP` and returns -RT_ERROR when the underlying
 *   driver cannot stop the watchdog. Some drivers (e.g. STM32 IWDG) have no
 *   STOP at all, so `rt_device_close()` would fail *and* leave the
 *   reference count incremented, making a second run of the suite fail in
 *   `rt_device_open()`.
 * - The test therefore probes STOP support once, and skips `rt_device_close()`
 *   for devices that cannot be stopped, releasing only its own handle. The
 *   device is shared/hardware-global anyway, so leaving it "opened" from the
 *   device framework's point of view is harmless and keeps repeated runs
 *   stable (no ref-count accumulation).
 * - Setting `RT_UTEST_WDT_STOPPABLE=n` (default) forces the non-closing path
 *   even if the probe is inconclusive; set `=y` on BSPs whose WDT really can
 *   be stopped to exercise the close path.
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

/*
 * Accepted absolute difference between the programmed timeout and the value
 * read back from the hardware. Watchdog timeouts are derived from a divided
 * low-speed clock (LSI/LSE), so the representable values are quantized and the
 * readback is normally <= the requested value.
 */
#ifndef RT_UTEST_WDT_TIMEOUT_TOL
#define RT_UTEST_WDT_TIMEOUT_TOL 1
#endif

#define WDT_TC_SUITE_TIMEOUT 10

static rt_device_t wdt_tc_device;
static rt_bool_t wdt_tc_device_opened;
/* RT_TRUE when the handle is currently opened by this test case */
static rt_bool_t wdt_tc_stop_supported;

static rt_err_t wdt_tc_probe_stop(rt_device_t dev)
{
#ifdef RT_UTEST_WDT_STOPPABLE
    if (!RT_UTEST_WDT_STOPPABLE)
    {
        LOG_I("WDT STOP disabled by config, assuming non-stoppable device");
        return -RT_ENOSYS;
    }
#endif

    /*
     * Do not actually stop a running watchdog while probing: probe before the
     * test ever starts it. If the driver does not implement STOP it returns
     * -RT_ENOSYS (or a driver specific error), which is exactly what we want to
     * learn here.
     */
    return rt_device_control(dev, RT_DEVICE_CTRL_WDT_STOP, RT_NULL);
}

static void wdt_timeout_set_get_test(void)
{
    rt_err_t result;
    rt_uint32_t timeout;
    rt_uint32_t readback;
    rt_int32_t diff;

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

    /*
     * The hardware can only represent timeouts that are a multiple of its
     * clock divider step, so an exact match is not guaranteed. Accept the
     * readback as long as it is positive and within the tolerance window.
     */
    diff = (rt_int32_t)readback - (rt_int32_t)timeout;
    if (diff < 0)
    {
        diff = -diff;
    }

    if (readback == 0 || diff > RT_UTEST_WDT_TIMEOUT_TOL)
    {
        LOG_E("WDT timeout readback %u out of tolerance (+-%d) for requested %u",
              (unsigned)readback, (int)RT_UTEST_WDT_TIMEOUT_TOL, (unsigned)timeout);
    }

    uassert_true(readback > 0);
    uassert_true(diff <= RT_UTEST_WDT_TIMEOUT_TOL);
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
        /* STOP was requested explicitly, so remember not to retry it in cleanup */
        wdt_tc_stop_supported = RT_FALSE;
    }
}
#endif /* RT_UTEST_WDT_START */

static rt_err_t utest_tc_init(void)
{
    rt_err_t result;
    rt_device_t wdt_device;

    wdt_tc_device = RT_NULL;
    wdt_tc_device_opened = RT_FALSE;
    wdt_tc_stop_supported = RT_FALSE;

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

    /*
     * The device may already be opened (framework refcount > 0) by an earlier
     * run of this suite when its cleanup could not close it. Reuse the open
     * handle instead of opening again, otherwise the refcount would keep
     * growing on every run.
     */
    if (wdt_device->ref_count > 0)
    {
        LOG_I("Watchdog device %s already open (ref_count=%d), reuse it",
              RT_UTEST_WDT_DEVICE_NAME, (int)wdt_device->ref_count);
    }
    else
    {
        result = rt_device_open(wdt_device, RT_DEVICE_OFLAG_RDWR);
        if (result != RT_EOK)
        {
            LOG_E("Watchdog device %s open failed: %d",
                  RT_UTEST_WDT_DEVICE_NAME, (int)result);
            return result;
        }
        wdt_tc_device_opened = RT_TRUE;
    }

    wdt_tc_device = wdt_device;

    result = wdt_tc_probe_stop(wdt_tc_device);
    if (result == RT_EOK || result == -RT_EBUSY)
    {
        wdt_tc_stop_supported = RT_TRUE;
    }
    else
    {
        LOG_W("Watchdog device %s cannot be stopped (%d); cleanup will not close it",
              RT_UTEST_WDT_DEVICE_NAME, (int)result);
    }

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_err_t result;

    result = RT_EOK;

    if (wdt_tc_device == RT_NULL)
    {
        return RT_EOK;
    }

    /*
     * rt_device_close() on a watchdog device issues RT_DEVICE_CTRL_WDT_STOP
     * first. For a driver without STOP support the framework returns
     * -RT_ERROR and, more importantly, rt_device_close() bails out before
     * decrementing ref_count, so a repeated suite would accumulate opens.
     * On such devices keep the handle open and only drop our pointer: the WDT
     * is a hardware-global singleton, so there is nothing to leak.
     */
    if (!wdt_tc_stop_supported)
    {
        LOG_W("Watchdog %s is not stoppable; keeping it open (no rt_device_close)",
              RT_UTEST_WDT_DEVICE_NAME);
        result = RT_EOK;
    }
    else if (wdt_tc_device_opened)
    {
        result = rt_device_close(wdt_tc_device);
        if (result != RT_EOK)
        {
            /* Keep the framework state consistent: our open is still counted */
            LOG_W("rt_device_close(%s) failed: %d",
                  RT_UTEST_WDT_DEVICE_NAME, (int)result);
            result = RT_EOK;
        }
    }

    wdt_tc_device = RT_NULL;
    wdt_tc_device_opened = RT_FALSE;
    wdt_tc_stop_supported = RT_FALSE;

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
