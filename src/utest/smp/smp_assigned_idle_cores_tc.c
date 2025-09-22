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
 * @note    Create multiple threads untied core threads, run them for a while on each core to see
 *          if the threads are automatically distributed evenly, run for a while to output the threads
 *          running on each core.
 */

#define THREAD_STACK_SIZE UTEST_THR_STACK_SIZE
#define THREAD_PRIORITY   20
static rt_thread_t threads[RT_CPUS_NR];
static int         tick = 0, finsh_flag = 0;
static int                num        = 0;
/* thread entry function */
static void thread_entry(void *parameter)
{
    while (1)
    {
        tick++;
        if (tick == 100)
        {
            /* Output the current core running threads */
            extern long list_thread(void);
            list_thread();
            finsh_flag = 0xA55A;
            uassert_true(1);
        }
        rt_thread_delay(5);
    }
}

static void thread_on_idle_core_tc(void)
{
    static int params[RT_CPUS_NR] = {0};
    char       thread_name[8];
    int        i;

    /* Initialise the thread entry parameters */
    for (i = 0; i < RT_CPUS_NR; i++)
    {
        params[i] = i;
    }

    /* Create RT_CPUS_NR threads and pass the entry parameters for each thread */
    for (i = 0; i < RT_CPUS_NR; i++)
    {
        rt_snprintf(thread_name, sizeof(thread_name), "T%d", i);
        threads[i] = rt_thread_create(thread_name, thread_entry, &params[i], THREAD_STACK_SIZE, THREAD_PRIORITY, 20);
        if (threads[i] != RT_NULL)
        {
            uassert_true(1);
            rt_thread_startup(threads[i]);
        }
    }
    /* Waiting for test cases to finish */
    while (finsh_flag != 0xA55A);
}

static rt_err_t utest_tc_init(void)
{
    rt_kprintf("[Test case]: created threads are automatically assigned to run on idle cores\r\n");
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
    UTEST_UNIT_RUN(thread_on_idle_core_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.smp.assigned_idle_cores_tc", utest_tc_init, utest_tc_cleanup, 10);
