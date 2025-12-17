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
 * @brief   Threads are automatically balanced across cores.
 *
 * @note    Create RT_CPUS_NR threads, thread 0 is not bound to core 0, higher priority, the priority of the other
 *          threads for the system's highest and the thread entry function does not let out the CPU control, run the
 *          specified number of times after the creation of thread 0 in thread 0, a low-priority bound to the core 0,
 *          the thread will not preempt the core 0 is running on threads
 *
 * Test Case Name: [smp_affinity_pri2]
 *
 * Test Objectives:
 * - Verify that a low-priority thread bound to a core does not preempt a higher-priority thread running on the same core.
 *
 * Test Scenarios:
 * - RT_CPUS_NR threads (T0~T(RT_CPUS_NR-1)) are created. T0 is unbound with medium priority (THIGH_PRIORITY), while
 * - threads T1~T(RT_CPUS_NR-1) are each bound to their respective cores with the highest priority (THREAD_PRIORITY).
 * - All threads share a common entry function thread_entry. In thread_entry, only the threads running on non-core-0 cores
 * - execute an infinite loop (i.e., they do not release core ownership). After running for a certain period of time,
 * - the thread on core 0 checks whether run_flag equals 0 after creating a low-priority (LOW_PRIORITY) thread Tn. The entry
 * - function of Tn is thread_temp_entry, and Tn will be destroyed after setting run_flag = 1.
 *
 * Verification Metrics:
 * - Output message: [I/utest] [ PASSED ] [ result ] testcase (core.smp_affinity_pri2)
 *
 * Dependencies:
 * - Enable RT_USING_SMP, set RT_THREAD_PRIORITY_MAX = 256.
 *
 * Expected Results:
 * - After T0 creates Tn, no scheduling occurs. T0 immediately checks whether run_flag is not equal to 1, and if this condition
 * - is true, it indicates that Tn has failed to preempt T0.
 */

/* Number of thread runs */
static int run_num = 10;
#define THREAD_STACK_SIZE UTEST_THR_STACK_SIZE
#define THREAD_PRIORITY   2
#define LOW_PRIORITY 30
#define THIGH_PRIORITY  10
static rt_thread_t        threads[RT_CPUS_NR];
static rt_thread_t        temp_thread;
static struct rt_spinlock lock;
static int                thread_inc = 0;
static int                run_flag = 0;
static int                num        = 0;

static void thread_temp_entry(void *parameter)
{
    run_flag = 1;
    rt_thread_delete(temp_thread);
}

static void thread_entry(void *parameter)
{
    int id   = 0;
    int para = *(int *)parameter;
    while (1)
    {
        thread_inc++;
        id = rt_hw_cpu_id();
        if (para == 0)
        {
            if (thread_inc == run_num)
            {
                uassert_int_equal(id, 0);
                temp_thread = rt_thread_create("Tn", thread_temp_entry, RT_NULL, THREAD_STACK_SIZE, LOW_PRIORITY, 20);

                if (temp_thread != RT_NULL)
                {
                    rt_thread_control(temp_thread, RT_THREAD_CTRL_BIND_CPU, (void *)0);
                    rt_thread_startup(temp_thread);
                    uassert_int_not_equal(run_flag, 1);
                }
            }
            rt_thread_delay(5);
        }
        else
        {
            uassert_int_not_equal(id, 0);
            while (1);
        }
    }
}

static void smp_affinity_pri2_tc(void)
{
    static int params[RT_CPUS_NR] = {0};
    char thread_name[8];
    int  i;

    for (i = 0; i < RT_CPUS_NR; i++)
    {
        params[i] = i;
    }

    threads[0] = rt_thread_create("T0", thread_entry, (int *)&params[0], THREAD_STACK_SIZE, THIGH_PRIORITY, 20);

    if (threads[0] != RT_NULL)
    {
        uassert_true(1);
        rt_thread_startup(threads[0]);
    }

    /* Create high-priority unbound threads with thread functions that don't let out CPU control */
    for (i = 1; i < RT_CPUS_NR; i++)
    {
        rt_snprintf(thread_name, sizeof(thread_name), "T%d", i);
        threads[i] = rt_thread_create(thread_name, thread_entry, (int *)&params[i], THREAD_STACK_SIZE, THREAD_PRIORITY, 20);

        if (threads[i] != RT_NULL)
        {
            uassert_true(1);
            rt_thread_control(threads[i], RT_THREAD_CTRL_BIND_CPU, (void *)(rt_ubase_t)i);
            rt_thread_startup(threads[i]);
        }
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
    for (num = 0; num < RT_CPUS_NR; num++)
    {
        rt_thread_delete(threads[num]);
    }
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(smp_affinity_pri2_tc);
}
UTEST_TC_EXPORT(testcase, "core.smp_affinity_pri2", utest_tc_init, utest_tc_cleanup, 10);
