/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-25     CYFS         add RTC alarm utest
 */

/**
 * Test Case Name: RTC Alarm Test
 *
 * Test Objectives:
 * - Verify that a one-shot alarm reaches the RT-Thread alarm callback.
 * - Verify the callback timestamp and one-shot state.
 *
 * Dependencies:
 * - Requires `RT_UTEST_RTC_ALARM`, `RT_USING_RTC`, and `RT_USING_ALARM`.
 * - The RTC device must be registered as `rtc` and support hardware alarms.
 * - No application may use the RTC or alarm service during the test.
 *
 * Expected Results:
 * - The one-shot alarm callback arrives before the configured timeout.
 * - The alarm is stopped and deleted after the test.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/dev_alarm.h>
#include <drivers/dev_rtc.h>
#include "utest.h"

#ifdef RT_UTEST_RTC_ALARM

#define RTC_ALARM_TC_LATE_TOLERANCE_SEC 5
#define RTC_ALARM_TC_SUITE_TIMEOUT      (RT_RTC_TC_ALARM_TIMEOUT_SEC + 10)

static struct rt_semaphore rtc_alarm_tc_sem;
static rt_bool_t rtc_alarm_tc_sem_inited;
static rt_device_t rtc_alarm_tc_device;
static rt_bool_t rtc_alarm_tc_device_opened;
static rt_alarm_t rtc_alarm_tc_alarm;
static volatile rt_uint32_t rtc_alarm_tc_count;
static volatile time_t rtc_alarm_tc_timestamp;

static void rtc_alarm_tc_record_cleanup_error(rt_err_t *result, rt_err_t operation_result)
{
    if ((*result == RT_EOK) && (operation_result != RT_EOK))
    {
        *result = operation_result;
    }
}

static rt_err_t rtc_alarm_tc_timestamp_to_tm(time_t timestamp, struct tm *time)
{
#ifdef RT_ALARM_USING_LOCAL_TIME
    return localtime_r(&timestamp, time) != RT_NULL ? RT_EOK : -RT_ERROR;
#else
    return gmtime_r(&timestamp, time) != RT_NULL ? RT_EOK : -RT_ERROR;
#endif
}

static time_t rtc_alarm_tc_tm_to_timestamp(const struct tm *time)
{
    struct tm alarm_time;

    alarm_time = *time;
#ifdef RT_ALARM_USING_LOCAL_TIME
    return mktime(&alarm_time);
#else
    return timegm(&alarm_time);
#endif
}

static void rtc_alarm_tc_callback(rt_alarm_t alarm, time_t timestamp)
{
    RT_UNUSED(alarm);

    rtc_alarm_tc_timestamp = timestamp;
    rtc_alarm_tc_count++;
    rt_sem_release(&rtc_alarm_tc_sem);
}

static void rtc_oneshot_alarm_test(void)
{
    rt_err_t result;
    rt_tick_t timeout;
    time_t current_timestamp;
    time_t requested_timestamp;
    time_t effective_timestamp;
    time_t timeout_timestamp;
    struct rt_alarm_setup setup;

    rtc_alarm_tc_count = 0;
    rtc_alarm_tc_timestamp = 0;

    result = get_timestamp(&current_timestamp);
    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        return;
    }

    /* First open may initialize the RTC clock source with its counter stopped. */
    result = set_timestamp(current_timestamp);
    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        return;
    }

    result = get_timestamp(&current_timestamp);
    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        return;
    }

    rt_memset(&setup, 0, sizeof(setup));
    setup.flag = RT_ALARM_ONESHOT;
    requested_timestamp = current_timestamp + RT_RTC_TC_ALARM_DELAY_SEC;
    result = rtc_alarm_tc_timestamp_to_tm(requested_timestamp, &setup.wktime);
    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        return;
    }

    rtc_alarm_tc_alarm = rt_alarm_create(rtc_alarm_tc_callback, &setup);
    uassert_not_null(rtc_alarm_tc_alarm);
    if (rtc_alarm_tc_alarm == RT_NULL)
    {
        return;
    }

    result = rt_alarm_start(rtc_alarm_tc_alarm);
    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        return;
    }

    effective_timestamp = rtc_alarm_tc_tm_to_timestamp(&rtc_alarm_tc_alarm->wktime);
    uassert_true(effective_timestamp != (time_t)-1);
    if (effective_timestamp == (time_t)-1)
    {
        return;
    }

    LOG_I("RTC alarm current=%ld requested=%ld effective=%ld",
          (long)current_timestamp,
          (long)requested_timestamp,
          (long)effective_timestamp);

    timeout = rt_tick_from_millisecond(RT_RTC_TC_ALARM_TIMEOUT_SEC * 1000);
    if (timeout == 0)
    {
        timeout = 1;
    }
    result = rt_sem_take(&rtc_alarm_tc_sem, timeout);
    if (result != RT_EOK)
    {
        if (get_timestamp(&timeout_timestamp) == RT_EOK)
        {
            LOG_E("RTC alarm timeout: result=%d current=%ld count=%u",
                  result,
                  (long)timeout_timestamp,
                  rtc_alarm_tc_count);
        }
        else
        {
            LOG_E("RTC alarm timeout: result=%d, current time unavailable, count=%u",
                  result,
                  rtc_alarm_tc_count);
        }
    }
    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        return;
    }

    uassert_int_equal((int)rtc_alarm_tc_count, 1);
    uassert_true(rtc_alarm_tc_timestamp >= effective_timestamp);
    uassert_true(rtc_alarm_tc_timestamp <= effective_timestamp + RTC_ALARM_TC_LATE_TOLERANCE_SEC);
    uassert_true((rtc_alarm_tc_alarm->flag & RT_ALARM_STATE_START) == 0);
}

static rt_err_t utest_tc_init(void)
{
    rt_err_t result;
    rt_device_t rtc_device;

    rtc_alarm_tc_sem_inited = RT_FALSE;
    rtc_alarm_tc_device = RT_NULL;
    rtc_alarm_tc_device_opened = RT_FALSE;
    rtc_alarm_tc_alarm = RT_NULL;

    if (RT_RTC_TC_ALARM_TIMEOUT_SEC <= RT_RTC_TC_ALARM_DELAY_SEC)
    {
        LOG_E("RTC alarm timeout must be greater than alarm delay");
        return -RT_EINVAL;
    }

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
    rtc_alarm_tc_device = rtc_device;
    rtc_alarm_tc_device_opened = RT_TRUE;

    result = rt_sem_init(&rtc_alarm_tc_sem, "rtctc", 0, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        rt_device_close(rtc_alarm_tc_device);
        rtc_alarm_tc_device = RT_NULL;
        rtc_alarm_tc_device_opened = RT_FALSE;
        return result;
    }
    rtc_alarm_tc_sem_inited = RT_TRUE;

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_err_t result;
    rt_err_t operation_result;

    result = RT_EOK;
    if (rtc_alarm_tc_alarm != RT_NULL)
    {
        operation_result = rt_alarm_stop(rtc_alarm_tc_alarm);
        rtc_alarm_tc_record_cleanup_error(&result, operation_result);
        operation_result = rt_alarm_delete(rtc_alarm_tc_alarm);
        rtc_alarm_tc_record_cleanup_error(&result, operation_result);
        rtc_alarm_tc_alarm = RT_NULL;
    }

    if (rtc_alarm_tc_sem_inited)
    {
        operation_result = rt_sem_detach(&rtc_alarm_tc_sem);
        rtc_alarm_tc_record_cleanup_error(&result, operation_result);
        rtc_alarm_tc_sem_inited = RT_FALSE;
    }

    if (rtc_alarm_tc_device_opened)
    {
        operation_result = rt_device_close(rtc_alarm_tc_device);
        rtc_alarm_tc_record_cleanup_error(&result, operation_result);
        rtc_alarm_tc_device = RT_NULL;
        rtc_alarm_tc_device_opened = RT_FALSE;
    }

    return result;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(rtc_oneshot_alarm_test);
}

UTEST_TC_EXPORT(testcase,
                "components.drivers.rtc.alarm",
                utest_tc_init,
                utest_tc_cleanup,
                RTC_ALARM_TC_SUITE_TIMEOUT);

#endif /* RT_UTEST_RTC_ALARM */
