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
 * @brief   Binding core affinity testcase.
 *
 * @note    Create RT_CPUS_NR threads, thread 0 is bound to core 0, other threads are not bound to specific cores,
 *          after running for a set number of times, count the number of times each core is run on the corresponding core,
 *          thread 0 should always be run on core 0, other threads will be run on different cores.
 */

/* Number of thread runs */
static int run_num = 100;
#define THREAD_STACK_SIZE UTEST_THR_STACK_SIZE
#define THREAD_PRIORITY   20
static rt_thread_t threads[RT_CPUS_NR];
static struct rt_spinlock lock;
static int thread_inc[RT_CPUS_NR] = {0};
static int thread_tic[RT_CPUS_NR] = {0};
static int finsh_flag = 0;
static int                num        = 0;

static void thread_entry(void *parameter)
{
    int id   = 0;
    int para = *(int *)parameter;
    while (1)
    {
        thread_tic[para]++;
        id = rt_hw_cpu_id();
        if (para == id)
        {
            thread_inc[para]++;
        }

        if (thread_tic[para] == run_num)
        {
            if (para == 0)
                uassert_int_equal(thread_inc[para], thread_tic[para]);
            else
                uassert_int_not_equal(thread_inc[para], thread_tic[para]);
            finsh_flag ++;
        }
        rt_thread_delay(5);
    }
}

static void thread_bind_affinity_tc(void)
{
    static int params[RT_CPUS_NR] = {0};
    char       thread_name[8];
    int        i, j;

    for (i = 0; i < RT_CPUS_NR; i++)
    {
        params[i] = i;
    }

    /* Create RT_CPUS_NR threads Thread 0 is bound to core 0 Other threads are not bound */
    for (i = 0; i < RT_CPUS_NR; i++)
    {
        rt_snprintf(thread_name, sizeof(thread_name), "thread%d", i);
        threads[i] = rt_thread_create(thread_name, thread_entry, (int *)&params[i], THREAD_STACK_SIZE, THREAD_PRIORITY, 20);
        if (i == 0)
        {
            rt_thread_control(threads[0], RT_THREAD_CTRL_BIND_CPU, (void *)0);
        }
        if (threads[i] != RT_NULL)
        {
            rt_thread_startup(threads[i]);
        }
    }

    while (finsh_flag != RT_CPUS_NR);

    /* Displays the number of times a thread was executed on the relevant core */
    for (j = 0; j < RT_CPUS_NR; j++)
    {
        rt_spin_lock(&lock);
        rt_kprintf("Total runs[%d], Number of times thread[%d] run on [core%d]: [%4d], always run at core%d ? %s \r\n", run_num, j, j, thread_inc[j], j, (thread_inc[j] == run_num) ? "yes" : "no");
        rt_spin_unlock(&lock);
    }
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
    UTEST_UNIT_RUN(thread_bind_affinity_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.smp.bind_affinity_tc", utest_tc_init, utest_tc_cleanup, 10);
