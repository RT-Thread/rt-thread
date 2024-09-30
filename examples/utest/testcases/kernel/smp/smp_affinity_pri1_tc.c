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
 * @brief   Test that threads with low-priority bound cores do not preempt high-priority threads.
 *
 * @note    Create RT_CPUS_NR threads, thread 0 is bound to core 0, lower priority, the priority of the other threads
 *          for the system's highest and the thread entry function does not let out the CPU control, run the specified
 *          number of times in thread 0 to create a high-priority not bound to the core of the thread, the thread will
 *          be preempted by the core 0 is running on the thread!
 */

/* Number of thread runs */
static int run_num = 10;
#define THREAD_STACK_SIZE UTEST_THR_STACK_SIZE
#define THREAD_PRIORITY   2
#define LOW_PRIORITY  50
#define THIGH_PRIORITY  10
static rt_thread_t        threads[RT_CPUS_NR];
static rt_thread_t        temp_thread;
static struct rt_spinlock lock;
static int                thread_inc = 0;
static int                num        = 0;

static void thread_temp_entry(void *parameter)
{
    int id = 0;
    while (1)
    {
        id = rt_hw_cpu_id();
        uassert_int_equal(id, 0);
        extern long list_thread(void);
        list_thread();
        rt_thread_delete(temp_thread);
    }
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
                extern long list_thread(void);
                list_thread();
                /* Creating high-priority untied core threads */
                temp_thread = rt_thread_create("Tn", thread_temp_entry, RT_NULL, THREAD_STACK_SIZE, THIGH_PRIORITY, 20);

                if (temp_thread != RT_NULL)
                {
                    rt_thread_startup(temp_thread);
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

static void smp_affinity_pri1_tc(void)
{
    static int params[RT_CPUS_NR] = {0};
    char thread_name[8];
    int  i;

    for (i = 0; i < RT_CPUS_NR; i++)
    {
        params[i] = i;
    }

    /*  Creating threads with low priority bindings to core 0 */
    threads[0] = rt_thread_create("T0", thread_entry, (int *)&params[0], THREAD_STACK_SIZE, LOW_PRIORITY, 20);

    if (threads[0] != RT_NULL)
    {
        rt_thread_control(threads[0], RT_THREAD_CTRL_BIND_CPU, (void *)0);
        rt_thread_startup(threads[0]);
    }

    /* Create high-priority unbound threads with thread functions that don't let out CPU control */
    for (i = 1; i < RT_CPUS_NR; i++)
    {
        rt_snprintf(thread_name, sizeof(thread_name), "T%d", i);
        threads[i] = rt_thread_create(thread_name, thread_entry, (int *)&params[i], THREAD_STACK_SIZE, THREAD_PRIORITY, 20);

        if (threads[i] != RT_NULL)
        {
            rt_thread_control(threads[i], RT_THREAD_CTRL_BIND_CPU, (void *)i);
            rt_thread_startup(threads[i]);
        }
    }
    rt_thread_delay(100);
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
    UTEST_UNIT_RUN(smp_affinity_pri1_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.smp.affinity_pri1_tc", utest_tc_init, utest_tc_cleanup, 10);
