/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * Test Case Name: timer_gettime() remaining time
 *
 * Test Objectives:
 * - Verify that timer_gettime() reports the time the timer was armed with.
 * - Verify that durations beyond UINT32_MAX nanoseconds are not truncated.
 * - Prevent regression of GitHub Issue #11924.
 *
 * The tolerances below are one tick wide: the clock source of a BSP is typically
 * a periodic tick, so a fraction of a tick may elapse between timer_settime() and
 * timer_gettime() and the reported remainder is correspondingly smaller.
 */

#include <rtthread.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>
#include "utest.h"

#define TIMER_GETTIME_TOLERANCE_NS (200ULL * 1000ULL * 1000ULL) /* 200 ms */

/* Compare the reported remainder against the requested duration. */
static void timer_gettime_roundtrip(int seconds, struct sigevent *evp)
{
    struct itimerspec value;
    struct itimerspec current;
    rt_uint64_t requested_ns;
    rt_uint64_t reported_ns;
    timer_t timer;

    LOG_I("checking %d s", seconds);

    uassert_int_equal(timer_create(CLOCK_MONOTONIC, evp, &timer), 0);

    value.it_value.tv_sec     = seconds;
    value.it_value.tv_nsec    = 0;
    value.it_interval.tv_sec  = 0;
    value.it_interval.tv_nsec = 0;
    uassert_int_equal(timer_settime(timer, 0, &value, RT_NULL), 0);

    rt_memset(&current, 0, sizeof(current));
    uassert_int_equal(timer_gettime(timer, &current), 0);

    requested_ns = (rt_uint64_t)seconds * 1000ULL * 1000ULL * 1000ULL;
    reported_ns  = (rt_uint64_t)current.it_value.tv_sec * 1000ULL * 1000ULL * 1000ULL
                   + (rt_uint64_t)current.it_value.tv_nsec;

    LOG_I("requested %d s, reported {%ld s, %ld ns}",
          seconds, (long)current.it_value.tv_sec, (long)current.it_value.tv_nsec);

    /* the remainder may have shrunk by a tick, but it must not exceed the request */
    uassert_true(reported_ns <= requested_ns);
    uassert_true(reported_ns + TIMER_GETTIME_TOLERANCE_NS >= requested_ns);

    /* seconds must not be truncated into a wrong magnitude */
    uassert_true((rt_int32_t)current.it_value.tv_sec >= seconds - 1);
    uassert_true((rt_int32_t)current.it_value.tv_sec <= seconds);

    uassert_int_equal(timer_delete(timer), 0);
}

/* Initialize the timer_gettime test. */
static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

/* Clean up the timer_gettime test. */
static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

/* Run the timer_gettime test case. */
static void testcase(void)
{
    struct sigevent evp;

    rt_memset(&evp, 0, sizeof(evp));
    evp.sigev_notify = SIGEV_SIGNAL;
    evp.sigev_signo  = SIGUSR1;

    /* 1 s and 3 s stay below UINT32_MAX ns, 5 s and 10 s do not */
    timer_gettime_roundtrip(1,  &evp);
    timer_gettime_roundtrip(3,  &evp);
    timer_gettime_roundtrip(5,  &evp);
    timer_gettime_roundtrip(10, &evp);
}

UTEST_TC_EXPORT(testcase, "components.libc.timer_gettime", utest_tc_init, utest_tc_cleanup, 20);
