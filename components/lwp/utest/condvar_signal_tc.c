/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-20     Shell        add test suites
 * 2026-03-19     cl2t         Add standardized utest documentation block
 */

/**
 * Test Case Name: Condition Variable Signal Test
 *
 * Test Objectives:
 * - Verify that rt_condvar_signal() correctly wakes up a single thread
 *   waiting on a condition variable.
 * - Test core APIs: rt_condvar_signal(), rt_condvar_timedwait(),
 *   rt_mutex_take(), rt_mutex_release(), rt_thread_create().
 *
 * Test Scenarios:
 * - The main thread acquires a mutex, creates a waker thread, then waits
 *   on a condition variable with a 100-tick timeout.
 * - The waker thread acquires the mutex and calls rt_condvar_signal() to
 *   wake the main thread.
 * - The main thread verifies it was woken successfully and releases the
 *   mutex.
 *
 * Verification Metrics:
 * - rt_condvar_signal() must return 0 on success.
 * - rt_condvar_timedwait() must return 0 when signaled before timeout.
 * - Timeout (-ETIMEDOUT) or interrupt (-EINTR) are acceptable non-fatal
 *   outcomes.
 * - Mutex acquire and release must succeed without errors.
 *
 * Dependencies:
 * - Software configuration: RT_USING_SMART must be enabled.
 * - Environmental assumptions: The platform must support multi-threading.
 *
 * Expected Results:
 * - Final output: "[ PASSED ] [ result ] testcase (testcases.ipc.condvar.signal)"
 * - No assertion failures during test execution.
 */

#include "common.h"
#include "utest_assert.h"

#include <rtdevice.h>
#include <rtdef.h>
#define STACK_SIZE (0x2000)

static struct rt_mutex _local_mtx;
static struct rt_condvar _local_cv;

static void waker_thr(void *param)
{
    int err;
    rt_mutex_t mutex = &_local_mtx;
    rt_condvar_t cond = &_local_cv;
    rt_mutex_take(mutex, RT_WAITING_FOREVER);
    err = rt_condvar_signal(cond);

    if (err != 0)
    {
        LOG_E("errno=%d, ret=%d\n", errno, err);
        LOG_E("rt_condvar_signal() error");
        uassert_false(1);
    }
    else
    {
        uassert_false(0);
    }
    rt_mutex_release(mutex);

    return;
}

static void condvar_signal_tc(void)
{
    rt_thread_t waker;
    rt_mutex_t mutex = &_local_mtx;
    rt_condvar_t cond = &_local_cv;
    int err;

    waker = rt_thread_create("waker", waker_thr, 0, STACK_SIZE, 25, 50);
    uassert_not_null(waker);

    if (rt_mutex_take(mutex, RT_WAITING_FOREVER) != 0)
    {
        LOG_E("pthread_mutex_lock() error");
        uassert_false(1);
        return;
    }
    else
    {
        uassert_false(0);
    }

    rt_thread_startup(waker);

    err = rt_condvar_timedwait(cond, mutex, RT_KILLABLE, 100);
    if (err != 0)
    {
        if (err == -EINTR || err == -ETIMEDOUT)
        {
            puts("wait timed out");
            uassert_false(0);
        }
        else
        {
            LOG_E("errno=%d, ret=%d\n", errno, err);
            LOG_E("pthread_cond_timedwait() error");
            uassert_false(1);
        }
    }

    err = rt_mutex_release(mutex);
    if (err != 0)
    {
        LOG_E("errno=%d, ret=%d\n", errno, err);
        LOG_E("rt_mutex_release() error");
        uassert_false(1);
    }
    else
    {
        uassert_false(0);
    }

    return ;
}

static rt_err_t utest_tc_init(void)
{
    if (rt_mutex_init(&_local_mtx, "utest", RT_IPC_FLAG_PRIO) != 0)
    {
        perror("pthread_mutex_init() error");
        uassert_false(1);
        return -1;
    }

    rt_condvar_init(&_local_cv, NULL);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_mutex_detach(&_local_mtx);
    rt_condvar_detach(&_local_cv);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(condvar_signal_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.ipc.condvar.signal", utest_tc_init, utest_tc_cleanup, 10);
