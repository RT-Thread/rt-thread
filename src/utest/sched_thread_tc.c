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
#include "utest.h"

#define TEST_LOOP_TIMES (100 * 1000)
#define TEST_PROGRESS_COUNTS (36)
#define TEST_THREAD_COUNT (RT_CPUS_NR * 1)
#define TEST_PROGRESS_ON (TEST_LOOP_TIMES*TEST_THREAD_COUNT/TEST_PROGRESS_COUNTS)

static struct rt_semaphore _thr_exit_sem;
static rt_atomic_t _progress_counter;

static volatile rt_thread_t threads_group[TEST_THREAD_COUNT][2];

static void _thread_entry1(void *param)
{
    rt_base_t critical_level;
    size_t idx = (size_t)param;

    for (size_t i = 0; i < TEST_LOOP_TIMES; i++)
    {
        critical_level = rt_enter_critical();

        rt_thread_suspend(rt_thread_self());
        rt_thread_resume(threads_group[idx][1]);

        rt_exit_critical_safe(critical_level);

        if (rt_atomic_add(&_progress_counter, 1) % TEST_PROGRESS_ON == 0)
            uassert_true(1);
    }

    rt_sem_release(&_thr_exit_sem);
    return;
}

static void _thread_entry2(void *param)
{
    rt_base_t critical_level;
    size_t idx = (size_t)param;

    for (size_t i = 0; i < TEST_LOOP_TIMES; i++)
    {
        critical_level = rt_enter_critical();

        rt_thread_suspend(rt_thread_self());
        rt_thread_resume(threads_group[idx][0]);

        rt_exit_critical_safe(critical_level);

        if (rt_atomic_add(&_progress_counter, 1) % TEST_PROGRESS_ON == 0)
            uassert_true(1);
    }

    rt_sem_release(&_thr_exit_sem);
    return;
}

static void scheduler_tc(void)
{
    for (size_t i = 0; i < TEST_THREAD_COUNT; i++)
    {
        rt_thread_t t1 =
            rt_thread_create(
                "t1",
                _thread_entry1,
                (void *)i,
                UTEST_THR_STACK_SIZE,
                UTEST_THR_PRIORITY + 1,
                100);
        rt_thread_t t2 =
            rt_thread_create(
                "t2",
                _thread_entry2,
                (void *)i,
                UTEST_THR_STACK_SIZE,
                UTEST_THR_PRIORITY + 1,
                100);

        threads_group[i][0] = t1;
        threads_group[i][1] = t2;
    }

    for (size_t i = 0; i < TEST_THREAD_COUNT; i++)
    {
        rt_thread_startup(threads_group[i][0]);
        rt_thread_startup(threads_group[i][1]);
    }

    for (size_t i = 0; i < TEST_THREAD_COUNT; i++)
    {
        rt_sem_take(&_thr_exit_sem, RT_WAITING_FOREVER);
    }
}

static rt_err_t utest_tc_init(void)
{
    rt_sem_init(&_thr_exit_sem, "test", 0, RT_IPC_FLAG_PRIO);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_sem_detach(&_thr_exit_sem);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(scheduler_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.kernel.scheduler.thread", utest_tc_init, utest_tc_cleanup, 10);
