/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-25     Shell        init ver.
 */
#define __RT_KERNEL_SOURCE__
#include <rtthread.h>
#include <stdlib.h>
#include "utest.h"

#define TEST_SECONDS 10
#define TEST_LOOP_TICKS (TEST_SECONDS * RT_TICK_PER_SECOND)
#define TEST_PROGRESS_COUNTS (36)
#define TEST_PROGRESS_ON (TEST_LOOP_TICKS*2/TEST_PROGRESS_COUNTS)

static struct rt_semaphore _thr_exit_sem;
static struct rt_semaphore _ipc_sem;
static rt_atomic_t _progress_counter;
static rt_base_t _timedout_failed_times = 0;

/**
 * Test on timedout IPC with racing condition where timedout routine and producer
 * thread may race to wakeup sleeper.
 *
 * This test will fork 2 thread, one producer and one consumer. The producer will
 * looping and trigger the IPC on the edge of new tick arrives. The consumer will
 * wait on IPC with a timedout of 1 tick.
 */

static void _wait_until_edge(void)
{
    rt_tick_t entry_level, current;
    rt_base_t random_latency;

    entry_level = rt_tick_get();
    do
    {
        current = rt_tick_get();
    }
    while (current == entry_level);

    /* give a random latency for test */
    random_latency = rand();
    entry_level = current;
    for (size_t i = 0; i < random_latency; i++)
    {
        current = rt_tick_get();
        if (current != entry_level)
            break;
    }
}

static void _producer_entry(void *param)
{
    for (size_t i = 0; i < TEST_LOOP_TICKS; i++)
    {
        _wait_until_edge();

        rt_sem_release(&_ipc_sem);

        if (rt_atomic_add(&_progress_counter, 1) % TEST_PROGRESS_ON == 0)
            uassert_true(1);
    }

    rt_sem_release(&_thr_exit_sem);
    return;
}

static void _consumer_entry(void *param)
{
    int error;
    for (size_t i = 0; i < TEST_LOOP_TICKS; i++)
    {
        error = rt_sem_take_interruptible(&_ipc_sem, 1);
        if (error == -RT_ETIMEOUT)
        {
            _timedout_failed_times++;
        }
        else
        {
            if (error != RT_EOK)
                uassert_true(0);
        }

        if (rt_atomic_add(&_progress_counter, 1) % TEST_PROGRESS_ON == 0)
            uassert_true(1);
    }

    rt_sem_release(&_thr_exit_sem);
    return;
}

static void timed_sem_tc(void)
{
    rt_thread_t prod = rt_thread_create(
        "prod",
        _producer_entry,
        (void *)0,
        UTEST_THR_STACK_SIZE,
        UTEST_THR_PRIORITY + 1,
        4);

    rt_thread_t cons = rt_thread_create(
        "cons",
        _consumer_entry,
        (void *)0,
        UTEST_THR_STACK_SIZE,
        UTEST_THR_PRIORITY + 1,
        100);

    rt_thread_startup(prod);
    rt_thread_startup(cons);

    for (size_t i = 0; i < 2; i++)
    {
        rt_sem_take(&_thr_exit_sem, RT_WAITING_FOREVER);
    }

    /* Summary */
    LOG_I("Total failed times: %ld(in %d)\n", _timedout_failed_times, TEST_LOOP_TICKS);
}

static rt_err_t utest_tc_init(void)
{
    int *pseed = rt_malloc(sizeof(int));
    srand(*(int *)pseed);
    rt_free(pseed);

    rt_sem_init(&_ipc_sem, "ipc", 0, RT_IPC_FLAG_PRIO);
    rt_sem_init(&_thr_exit_sem, "test", 0, RT_IPC_FLAG_PRIO);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_sem_detach(&_ipc_sem);
    rt_sem_detach(&_thr_exit_sem);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(timed_sem_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.kernel.scheduler.timed_sem", utest_tc_init, utest_tc_cleanup, TEST_SECONDS * 2);
