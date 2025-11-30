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
 *
 * Test Case Name: [smp_assigned_idle_cores]
 *
 * Test Objectives:
 * - Test whether ready threads unbound to cores can be automatically allocated
 * - to idle cores under the SMP architecture.
 *
 * Test Scenarios:
 * - Under the SMP architecture, each core spends most of its time running the
 * - idle thread after the system starts. At this point, create RT_CPUS_NR-1 cyclic
 * - tasks and observe whether these tasks can be evenly distributed across all
 * - cores for execution. Since the thread running the utest occupies one core, it
 * - is only necessary to observe whether the remaining (RT_CPUS_NR - 1) cores can
 * - be allocated the newly created threads and execute them.
 *
 * Verification Metrics:
 * - After running this test case, it is necessary to observe the printed thread
 * - list, where all threads created with names from T0 to T(RT_CPUS_NR-2) must
 * - be in the running state. RT_CPUS_NR must be greater than or equal to 2.
 *
 * Dependencies:
 * - RT_USING_SMP needs to be enabled.
 *
 * Expected Results:
 * - Print the thread list on the terminal, and observe that T0 to T(RT_CPUS_NR-2)
 * - are all in the running state, with the output "[ PASSED ] [ result ] testcase
 * - (core.smp_assigned_idle_cores)".
 */

#define THREAD_STACK_SIZE UTEST_THR_STACK_SIZE
#define THREAD_PRIORITY   20
static rt_thread_t threads[RT_CPUS_NR - 1];
static int         tick = 0, finish_flag = 0;
static int                num        = 0;
/* thread entry function */
static void thread_entry(void *parameter)
{
    int value = *(int *)parameter;
    while (1)
    {
        tick++;
        if (tick >= 100 && (finish_flag & (1 << value)) == 0)
        {
            rt_atomic_or((volatile rt_atomic_t *)&finish_flag, (1 << value));
            uassert_true(1);
        }
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

    /* Create RT_CPUS_NR-1 threads and pass the entry parameters for each thread */
    for (i = 0; i < RT_CPUS_NR - 1; i++)
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
    while (finish_flag != (1<<(RT_CPUS_NR-1))-1);
    /* Output the current core running threads */
    extern long list_thread(void);
    list_thread();
}

static rt_err_t utest_tc_init(void)
{
    finish_flag = 0;
    tick = 0;
    rt_kprintf("[Test case]: created threads are automatically assigned to run on idle cores\r\n");
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    for (num = 0; num < RT_CPUS_NR - 1; num++)
    {
        rt_thread_delete(threads[num]);
    }
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(thread_on_idle_core_tc);
}
UTEST_TC_EXPORT(testcase, "core.smp_assigned_idle_cores", utest_tc_init, utest_tc_cleanup, 10);

