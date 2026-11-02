/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-25     CYFS         add RTC time utest
 */

/**
 * Test Case Name: RTC Time Test
 *
 * Test Objectives:
 * - Verify that the RTC timestamp can be set and read back.
 * - Verify that the RTC advances across a second boundary.
 *
 * Dependencies:
 * - Requires `RT_UTEST_RTC` and `RT_USING_RTC`.
 * - The RTC device must be registered as `rtc`.
 * - No application may change the RTC during the test.
 *
 * Expected Results:
 * - Timestamp set/get and advancement checks pass.
 * - The original RTC time is restored with elapsed test time added.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/dev_rtc.h>
#include "utest.h"

#ifdef RT_UTEST_RTC

/* 2025-01-15 12:00:50 UTC, close enough to cover minute rollover. */
#define RTC_TC_BASE_TIMESTAMP         ((time_t)1736942450)
#define RTC_TC_ADVANCE_WAIT_MS        3000
#define RTC_TC_READBACK_TOLERANCE_SEC 2
#define RTC_TC_ADVANCE_TOLERANCE_SEC  5
#define RTC_TC_SUITE_TIMEOUT          10

static time_t rtc_tc_original_timestamp;
static rt_tick_t rtc_tc_original_tick;
static rt_bool_t rtc_tc_timestamp_saved;
static rt_device_t rtc_tc_device;
static rt_bool_t rtc_tc_device_opened;

static void rtc_timestamp_set_get_test(void)
{
    rt_err_t result;
    time_t first_timestamp;
    time_t second_timestamp;

    result = set_timestamp(RTC_TC_BASE_TIMESTAMP);
    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        return;
    }

    result = get_timestamp(&first_timestamp);
    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        return;
    }
    uassert_true(first_timestamp >= RTC_TC_BASE_TIMESTAMP);
    uassert_true(first_timestamp <= RTC_TC_BASE_TIMESTAMP + RTC_TC_READBACK_TOLERANCE_SEC);

    rt_thread_mdelay(RTC_TC_ADVANCE_WAIT_MS);

    result = get_timestamp(&second_timestamp);
    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        return;
    }
    LOG_I("RTC time first=%ld second=%ld",
          (long)first_timestamp,
          (long)second_timestamp);
    uassert_true(second_timestamp > first_timestamp);
    uassert_true(second_timestamp <= first_timestamp + RTC_TC_ADVANCE_TOLERANCE_SEC);
}

static rt_err_t utest_tc_init(void)
{
    rt_err_t result;
    rt_device_t rtc_device;

    rtc_tc_timestamp_saved = RT_FALSE;
    rtc_tc_device = RT_NULL;
    rtc_tc_device_opened = RT_FALSE;

    rtc_device = rt_device_find("rtc");
    if (rtc_device == RT_NULL)
    {
        LOG_E("RTC device rtc is not registered");
        return -RT_ERROR;
    }
    if (rtc_device->type != RT_Device_Class_RTC)
    {
        LOG_E("Device rtc is not an RTC device");
        return -RT_ERROR;
    }

    result = rt_device_open(rtc_device, RT_DEVICE_OFLAG_RDWR);
    if (result != RT_EOK)
    {
        return result;
    }
    rtc_tc_device = rtc_device;
    rtc_tc_device_opened = RT_TRUE;

    result = get_timestamp(&rtc_tc_original_timestamp);
    if (result != RT_EOK)
    {
        rt_device_close(rtc_tc_device);
        rtc_tc_device = RT_NULL;
        rtc_tc_device_opened = RT_FALSE;
        return result;
    }
    rtc_tc_original_tick = rt_tick_get();
    rtc_tc_timestamp_saved = RT_TRUE;

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_err_t result;
    rt_err_t operation_result;
    time_t restore_timestamp;
    rt_tick_t elapsed_tick;

    result = RT_EOK;
    if (rtc_tc_timestamp_saved)
    {
        elapsed_tick = rt_tick_get_delta(rtc_tc_original_tick);
        restore_timestamp = rtc_tc_original_timestamp + elapsed_tick / RT_TICK_PER_SECOND;
        operation_result = set_timestamp(restore_timestamp);
        if (operation_result != RT_EOK)
        {
            result = operation_result;
        }
        rtc_tc_timestamp_saved = RT_FALSE;
    }

    if (rtc_tc_device_opened)
    {
        operation_result = rt_device_close(rtc_tc_device);
        if ((result == RT_EOK) && (operation_result != RT_EOK))
        {
            result = operation_result;
        }
        rtc_tc_device = RT_NULL;
        rtc_tc_device_opened = RT_FALSE;
    }

    return result;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(rtc_timestamp_set_get_test);
}

UTEST_TC_EXPORT(testcase,
                "components.drivers.rtc.time",
                utest_tc_init,
                utest_tc_cleanup,
                RTC_TC_SUITE_TIMEOUT);

#endif /* RT_UTEST_RTC */
