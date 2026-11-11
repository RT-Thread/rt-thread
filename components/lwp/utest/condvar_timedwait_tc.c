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
 * Test Case Name: Condition Variable Timed Wait Test
 *
 * Test Objectives:
 * - Verify that rt_condvar_timedwait() correctly times out when no signal
 *   is received within the specified timeout period.
 * - Test core APIs: rt_condvar_timedwait(), rt_mutex_take(),
 *   rt_mutex_init(), rt_condvar_init().
 *
 * Test Scenarios:
 * - The main thread acquires a mutex and calls rt_condvar_timedwait()
 *   with a 100-tick timeout.
 * - Since no other thread signals the condition variable, the call is
 *   expected to time out with -ETIMEDOUT or be interrupted with -EINTR.
 *
 * Verification Metrics:
 * - rt_condvar_timedwait() must return -ETIMEDOUT or -EINTR when no
 *   signal is received.
 * - Any other non-zero return value indicates a test failure.
 * - Mutex initialization and acquisition must succeed.
 *
 * Dependencies:
 * - Software configuration: RT_USING_SMART must be enabled.
 * - Environmental assumptions: The platform must support condition
 *   variables and mutexes.
 *
 * Expected Results:
 * - Final output: "[ PASSED ] [ result ] testcase (testcases.ipc.condvar.timedwait)"
 * - No assertion failures during test execution.
 */

#include "common.h"
#include "utest_assert.h"

#include <rtdevice.h>
#include <rtdef.h>

static struct rt_mutex _local_mtx;
static struct rt_condvar _local_cv;

static void condvar_timedwait_tc(void)
{
    rt_mutex_t mutex = &_local_mtx;
    rt_condvar_t cond = &_local_cv;
    int err;

    if (rt_mutex_take(mutex, RT_WAITING_FOREVER) != 0)
    {
        LOG_E("pthread_mutex_lock() error");
        uassert_false(1);
        return;
    }

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
    UTEST_UNIT_RUN(condvar_timedwait_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.ipc.condvar.timedwait", utest_tc_init, utest_tc_cleanup, 10);
