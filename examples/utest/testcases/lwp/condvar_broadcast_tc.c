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
 * Test Case Name: Condition Variable Broadcast Test
 *
 * Test Objectives:
 * - Verify that rt_condvar_broadcast() correctly wakes up all threads
 *   waiting on a condition variable.
 * - Test core APIs: rt_condvar_broadcast(), rt_condvar_timedwait(),
 *   rt_mutex_take(), rt_mutex_release(), rt_mutex_get_owner().
 *
 * Test Scenarios:
 * - Creates 8 worker threads, each acquiring a mutex and then waiting on
 *   a condition variable via rt_condvar_timedwait().
 * - The main thread calls rt_condvar_broadcast() to wake all waiters.
 * - Each woken thread verifies it re-acquired the mutex, increments a
 *   counter, and releases the mutex.
 * - The main thread verifies all 8 threads were successfully woken.
 *
 * Verification Metrics:
 * - All waiting threads must be woken after broadcast (waken_num == THREAD_NUM).
 * - Each woken thread must hold the mutex (verified via rt_mutex_get_owner()).
 * - rt_condvar_timedwait() must return 0 on successful wake.
 * - Mutex release must succeed for each woken thread.
 *
 * Dependencies:
 * - Software configuration: RT_USING_SMART must be enabled.
 * - Environmental assumptions: The platform must support multi-threading
 *   with at least 8 concurrent threads.
 *
 * Expected Results:
 * - Final output: "[ PASSED ] [ result ] testcase (testcases.ipc.condvar.broadcast)"
 * - No assertion failures during test execution.
 */

#include "common.h"
#include "rtconfig.h"
#include "utest_assert.h"

#include <rtdevice.h>
#include <rtdef.h>

static struct rt_mutex _local_mtx;
static struct rt_condvar _local_cv;
#define THREAD_NUM 8
#define STACK_SIZE (0x2000)

static volatile int start_num;
static volatile int waken_num;

static void thr_func(void *arg)
{
    int rc;
    rt_mutex_t mutex = &_local_mtx;
    rt_condvar_t cond = &_local_cv;
    rt_mutex_take(mutex, RT_WAITING_FOREVER);

    start_num++;
    rc = rt_condvar_timedwait(cond, mutex, RT_KILLABLE, RT_WAITING_FOREVER);
    if (rc != 0)
    {
        LOG_E("cond_wait returned %d\n", rc);
        uassert_false(1);
        return;
    }

    if (rt_mutex_get_owner(mutex) != rt_thread_self())
    {
        LOG_E("Should not be able to lock the mutex again");
        uassert_false(1);
        return;
    }
    else
    {
        uassert_true(1);
    }
    LOG_I("Thread was wakened and acquired the mutex again");
    waken_num++;

    if (rt_mutex_release(mutex) != 0)
    {
        LOG_E("Failed to release the mutex");
        uassert_false(1);
        return;
    }
    else
    {
        uassert_true(1);
    }

    return ;
}

static void *stack_addr[THREAD_NUM];

static void condvar_broadcast_tc(void)
{
    rt_mutex_t mutex = &_local_mtx;
    rt_condvar_t cond = &_local_cv;
    struct rt_thread thread[THREAD_NUM];

    for (size_t i = 0; i < THREAD_NUM; i++)
    {
        if (rt_thread_init(&thread[i], "utest", thr_func, RT_NULL,
                           stack_addr[i], STACK_SIZE, 25, 100) != 0)
        {
            LOG_E("Fail to create thread[%d]\n", i);
            return;
        }
        rt_thread_startup(&thread[i]);
    }

    while (start_num < THREAD_NUM)
        rt_thread_mdelay(1);

    rt_mutex_take(mutex, RT_WAITING_FOREVER);
    if (rt_condvar_broadcast(cond))
    {
        uassert_false(1);
        return ;
    }
    rt_mutex_release(mutex);

    rt_thread_mdelay(1);

    if (waken_num < THREAD_NUM)
    {
        LOG_E("[Main thread] Not all waiters were wakened\n");
        uassert_false(1);
        return ;
    }
    else
    {
        utest_int_equal(waken_num, THREAD_NUM);
    }
    LOG_I("[Main thread] all waiters were wakened\n");

    return;
}

static rt_err_t utest_tc_init(void)
{
    start_num = 0;
    waken_num = 0;
    if (rt_mutex_init(&_local_mtx, "utest", RT_IPC_FLAG_PRIO) != 0)
    {
        perror("pthread_mutex_init() error");
        uassert_false(1);
        return -1;
    }

    rt_condvar_init(&_local_cv, NULL);

    for (size_t i = 0; i < THREAD_NUM; i++)
    {
        stack_addr[i] =
            rt_pages_alloc_ext(rt_page_bits(STACK_SIZE), PAGE_ANY_AVAILABLE);
        utest_int_not_equal(stack_addr[i], RT_NULL);
    }
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_mutex_detach(&_local_mtx);
    rt_condvar_detach(&_local_cv);

    for (size_t i = 0; i < THREAD_NUM; i++)
    {
        rt_pages_free(stack_addr[i], rt_page_bits(STACK_SIZE));
        stack_addr[i] = 0;
    }
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(condvar_broadcast_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.ipc.condvar.broadcast", utest_tc_init,
                utest_tc_cleanup, 10);
