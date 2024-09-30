/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-10     RV           the first version
 */

#include <rtthread.h>
#include "utest.h"

/**
 * @brief   Thread Preemption Test with Different Priorities.
 *
 * @note    Create multiple threads, low-priority threads run first,
 *          high-priority threads preempt low-priority threads, and
 *          print the current status of each core in the thread's entry function.
 */

#define THREAD_PRIORITY_HIGH 21
#define THREAD_PRIORITY_LOW  30
#define THREAD_STACK_SIZE UTEST_THR_STACK_SIZE

static rt_thread_t   threads[2];
static struct rt_spinlock lock;

/* High Priority Thread */
static void thread_high_entry(void *parameter)
{
    uassert_true(1);
    rt_spin_lock(&lock);
    rt_kprintf("High priority thread is running\n");
    extern long list_thread(void);
    list_thread();
    rt_spin_unlock(&lock);
}

/* Low Priority Thread */
static void thread_low_entry(void *parameter)
{
    uassert_true(1);
    rt_spin_lock(&lock);
    rt_kprintf("Low priority thread is running\n");
    extern long list_thread(void);
    list_thread();
    rt_spin_unlock(&lock);
}

static void thread_preemptions_tc(void)
{
    /* Creating low-priority thread */
    threads[0] = rt_thread_create("tlow", thread_low_entry, RT_NULL, THREAD_STACK_SIZE, THREAD_PRIORITY_LOW, 10);
    if (threads[0]  != RT_NULL)
    {
        uassert_true(1);
        rt_thread_startup(threads[0] );
    }

    rt_thread_delay(5);
    /* Creating high-priority thread */
    threads[1]  = rt_thread_create("thigh", thread_high_entry, RT_NULL, THREAD_STACK_SIZE, THREAD_PRIORITY_HIGH, 10);
    if (threads[1] != RT_NULL)
    {
        uassert_true(1);
        rt_thread_startup(threads[1]);
    }
    rt_thread_delay(50);
}

static rt_err_t utest_tc_init(void)
{
    rt_spin_lock_init(&lock);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(thread_preemptions_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.smp.thread_preemptions_tc", utest_tc_init, utest_tc_cleanup, 10);
