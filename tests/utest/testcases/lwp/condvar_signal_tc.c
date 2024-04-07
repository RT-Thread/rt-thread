/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-20     Shell        add test suites
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
