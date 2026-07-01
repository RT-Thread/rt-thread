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
 *
 * Test Case Name: [smp_bind_affinity]
 *
 * Test Objectives:
 * - Verify that threads bound to specific cores run on those cores.
 *
 * Test Scenarios:
 * - RT_CPUS_NR threads (T0~T(RT_CPUS_NR-1)) are created, with only T0 bound to core 0.
 * - Each thread samples rt_hw_cpu_id() while running; T0 must stay on core 0.
 * - Other threads are unbound and only used to add scheduling pressure; their CPU
 * - placement is printed for observation but not asserted (platform-dependent).
 *
 * Verification Metrics:
 * - Output message: [I/utest] [ PASSED ] [ result ] testcase (core.smp_bind_affinity)
 *
 * Dependencies:
 * - Enable RT_USING_SMP, set RT_THREAD_PRIORITY_MAX = 256.
 *
 * Expected Results:
 * - You will see the relevant PASS message. Additionally, RT_CPUS_NR lines of printed information will be displayed,
 * - indicating whether each thread Tx has been running on core x all the time. The results show that only T0 has been
 * - running on core 0 consistently.
 */

/* Number of thread runs */
static int run_num = 100;
#define THREAD_STACK_SIZE UTEST_THR_STACK_SIZE
#define THREAD_PRIORITY   20
static rt_thread_t threads[RT_CPUS_NR];
static struct rt_spinlock lock;
static int thread_inc[RT_CPUS_NR] = {0};
static int thread_tic[RT_CPUS_NR] = {0};
static rt_uint32_t thread_core_mask[RT_CPUS_NR] = {0};
static rt_atomic_t finsh_flag;
static int                num        = 0;

static void thread_entry(void *parameter)
{
    int id;
    int para = *(int *)parameter;

    while (1)
    {
        if (thread_tic[para] >= run_num)
        {
            /* Spin until cleanup deletes this thread (same as other smp utests) */
            while (1);
        }

        rt_sched_lock_level_t slvl;

        /* Sample CPU and counters atomically to avoid migration skew */
        rt_sched_lock(&slvl);
        id = rt_hw_cpu_id();
        thread_tic[para]++;
        thread_core_mask[para] |= (1u << id);
        if (para == id)
        {
            thread_inc[para]++;
        }
        rt_sched_unlock(slvl);

        if (thread_tic[para] == run_num)
        {
            rt_atomic_add(&finsh_flag, 1);
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

    while (rt_atomic_load(&finsh_flag) != RT_CPUS_NR);

    /* Bound thread must always run on core 0 */
    uassert_int_equal(thread_inc[0], thread_tic[0]);
    uassert_int_equal(thread_core_mask[0], 1u);

    /* Displays per-thread CPU statistics (unbound threads: observe only) */
    for (j = 0; j < RT_CPUS_NR; j++)
    {
        rt_spin_lock(&lock);
        rt_kprintf("Total runs[%d], Number of times thread[%d] run on [core%d]: [%4d], core mask: 0x%x, always run at core%d ? %s \r\n",
                   run_num, j, j, thread_inc[j], thread_core_mask[j], j,
                   (thread_inc[j] == run_num) ? "yes" : "no");
        rt_spin_unlock(&lock);
    }
}

static rt_err_t utest_tc_init(void)
{
    int i;

    rt_spin_lock_init(&lock);
    rt_atomic_store(&finsh_flag, 0);
    for (i = 0; i < RT_CPUS_NR; i++)
    {
        threads[i] = RT_NULL;
        thread_inc[i] = 0;
        thread_tic[i] = 0;
        thread_core_mask[i] = 0;
    }
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    for (num = 0; num < RT_CPUS_NR; num++)
    {
        if (threads[num] != RT_NULL)
        {
            rt_thread_delete(threads[num]);
            threads[num] = RT_NULL;
        }
    }
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(thread_bind_affinity_tc);
}
UTEST_TC_EXPORT(testcase, "core.smp_bind_affinity", utest_tc_init, utest_tc_cleanup, 10);
