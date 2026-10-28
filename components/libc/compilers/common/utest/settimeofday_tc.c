/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * Test Case Name: settimeofday() field validation
 *
 * Test Objectives:
 * - Verify that timestamps above INT32_MAX are accepted on time64/long32 targets.
 * - Verify that a negative tv_usec is still rejected.
 * - Prevent regression of GitHub Issue #11922.
 *
 * Note: the rejections exercised here only happen when time_t is wider than long,
 * which is the time64/long32 configuration. On targets where the two are the same
 * width the old narrowing cast could not change the result, so the case would not
 * prove anything; it reports that and skips.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>
#include <errno.h>
#include "utest.h"

/* Run settimeofday() against the boundary values, then restore the clock. */
static void settimeofday_time64_test(void)
{
    struct timeval tv;
    struct timeval saved = { 0, 0 };
    rt_device_t rtc;
    int ret;

    rtc = rt_device_find("rtc");
    if (rtc == RT_NULL)
    {
        LOG_I("no rtc device, skipping");
        return;
    }

    if (sizeof(time_t) <= sizeof(long))
    {
        LOG_I("sizeof(time_t)=%d is not wider than sizeof(long)=%d, skipping",
              (int)sizeof(time_t), (int)sizeof(long));
        return;
    }

    /* remember the current time so the rtc can be put back afterwards */
    if (gettimeofday(&saved, RT_NULL) != 0)
    {
        saved.tv_sec  = 0;
        saved.tv_usec = 0;
    }

    /* INT32_MAX + 1: the first value the old (long) cast turned negative */
    tv.tv_sec  = (time_t)2147483647 + 1;
    tv.tv_usec = 0;
    LOG_I("tv_sec = INT32_MAX + 1");
    uassert_int_equal(settimeofday(&tv, RT_NULL), 0);

    /* 2040-01-01, the value reported in #11922 */
    tv.tv_sec  = (time_t)2208988800;
    tv.tv_usec = 0;
    LOG_I("tv_sec = 2208988800 (2040-01-01)");
    uassert_int_equal(settimeofday(&tv, RT_NULL), 0);

    /* 2106-02-07, UINT32_MAX */
    tv.tv_sec  = (time_t)4294967295U;
    tv.tv_usec = 0;
    LOG_I("tv_sec = 4294967295 (2106-02-07)");
    uassert_int_equal(settimeofday(&tv, RT_NULL), 0);

    /* a negative tv_usec is still invalid and must keep being rejected */
    tv.tv_sec  = (time_t)1000000000;
    tv.tv_usec = -1;
    LOG_I("tv_usec = -1 must be rejected");
    errno = 0;
    ret = settimeofday(&tv, RT_NULL);
    uassert_int_equal(ret, -1);
    uassert_int_equal(errno, EINVAL);

    /* put the clock back */
    if (settimeofday(&saved, RT_NULL) != 0)
    {
        LOG_W("failed to restore the rtc");
    }
}

/* Initialize the settimeofday test. */
static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

/* Clean up the settimeofday test. */
static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

/* Run the settimeofday test case. */
static void testcase(void)
{
    UTEST_UNIT_RUN(settimeofday_time64_test);
}

UTEST_TC_EXPORT(testcase, "components.libc.settimeofday", utest_tc_init, utest_tc_cleanup, 10);
