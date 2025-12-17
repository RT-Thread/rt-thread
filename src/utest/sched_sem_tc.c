/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-17     Shell        the first version
 * 2025-12-12     lhxj         Add standardized utest documentation block
 */

/**
 * Test Case Name: Priority Based Semaphore Synchronization Test (core.scheduler_sem)
 *
 * Test Objectives:
 * - Verify the stability and correctness of the scheduler under high concurrency.
 * - Verify thread synchronization and execution order using Semaphore chains across different priority levels.
 * - Verify SMP (Symmetric Multiprocessing) load balancing and atomic operations in a multi-core environment.
 * - List specific functions or APIs to be tested:
 * - rt_sem_init
 * - rt_sem_take
 * - rt_sem_release
 * - rt_thread_create
 * - rt_thread_startup
 * - rt_atomic_add
 *
 * Test Scenarios:
 * - **Semaphore Chained Scheduling:**
 * 1. Initialize a "thread matrix" where threads are created across multiple priority levels (`TEST_LEVEL_COUNTS`).
 * 2. For each priority level, create multiple concurrent threads (`RT_CPUS_NR * 2`).
 * 3. Establish a dependency chain (Ring Topology):
 * - **Level 0 threads:** Notify Level 1, then wait for their own resource.
 * - **Middle Level threads:** Wait for their resource (notified by Level N-1), then notify Level N+1.
 * - **Last Level threads:** Wait for their resource, print status (CPU ID), delay, then notify Level 0.
 * 4. Each thread increments an atomic load counter for the specific CPU it is running on.
 * 5. The main test thread waits for all sub-threads to signal completion via `_thr_exit_sem`.
 *
 * Verification Metrics:
 * - **Pass:** All created threads must complete their execution loops without deadlocking.
 * - **Pass:** The sum of execution counts across all CPUs (`_load_average`) must equal the calculated expected total (`KERN_TEST_CONFIG_LOOP_TIMES * TEST_LEVEL_COUNTS * KERN_TEST_CONCURRENT_THREADS`).
 *
 * Dependencies:
 * - Hardware requirements
 * - No specific peripherals required, but multi-core CPU is recommended for SMP verification.
 * (This is met by the qemu-virt64-riscv BSP).
 * - Software configuration
 * - `RT_USING_UTEST` must be enabled (`RT-Thread Utestcases`).
 * - `Scheduler Test` must be enabled (`RT-Thread Utestcases` -> `Kernel Core` -> 'Scheduler Test').
 * - (Optional) Enable SMP for parallel testing (Highly Recommended):
 * - Go to `RT-Thread Kernel` -> `Enable SMP (Symmetric multiprocessing)`.
 * - Set `Number of CPUs` to > 1 (e.g., 2 or 4).
 * - Environmental assumptions
 * - The system must support enough valid priority levels (`RT_THREAD_PRIORITY_MAX`) to accommodate `TEST_LEVEL_COUNTS`.
 * - Run the test case from the msh prompt:
 * `utest_run core.scheduler_sem`
 *
 * Expected Results:
 * - The console should print character patterns (e.g., `*0*1...`) indicating thread activity on specific CPUs.
 * - The final load statistics per CPU should be printed.
 * - Final Output: `[ PASSED ] [ result ] testcase (core.scheduler_sem)`
 */

#define __RT_IPC_SOURCE__

#include <rtthread.h>
#include "rthw.h"
#include "utest.h"

#define KERN_TEST_CONFIG_LOOP_TIMES     160
#define KERN_TEST_CONCURRENT_THREADS    (RT_CPUS_NR * 2)
#define KERN_TEST_CONFIG_HIGHEST_PRIO   3
#define KERN_TEST_CONFIG_LOWEST_PRIO    (RT_THREAD_PRIORITY_MAX - 2)

#define TEST_LEVEL_COUNTS (KERN_TEST_CONFIG_LOWEST_PRIO - KERN_TEST_CONFIG_HIGHEST_PRIO + 1)
#if TEST_LEVEL_COUNTS <= RT_CPUS_NR
#warning for the best of this test, TEST_LEVEL_COUNTS should greater than RT_CPUS_NR
#endif
#if KERN_TEST_CONCURRENT_THREADS < RT_CPUS_NR
#warning for the best of this test, KERN_TEST_CONCURRENT_THREADS should greater than RT_CPUS_NR
#endif
#if KERN_TEST_CONFIG_LOWEST_PRIO >= RT_THREAD_PRIORITY_MAX - 1
#error the thread priority should at least be greater than idle
#endif

static rt_atomic_t _star_counter;
static struct rt_semaphore _thr_exit_sem;
static struct rt_semaphore _level_waiting[TEST_LEVEL_COUNTS];
static rt_thread_t _thread_matrix[TEST_LEVEL_COUNTS][KERN_TEST_CONCURRENT_THREADS];
static rt_atomic_t _load_average[RT_CPUS_NR];

static void _print_char(rt_thread_t thr_self, int character)
{
    rt_base_t current_counter;

#ifdef RT_USING_SMP
    rt_kprintf("%c%d", character, RT_SCHED_CTX(thr_self).oncpu);
#else
    rt_kprintf("%c0", character);
#endif /* RT_USING_SMP */

    current_counter = rt_atomic_add(&_star_counter, 1);
    if (current_counter % 30 == 0)
    {
        rt_kprintf("\n");
    }
}

static void _stats_load_avg_inc(void)
{
    int cpuid;

    cpuid = rt_hw_cpu_id();
    rt_atomic_add(&_load_average[cpuid], 1);
}

static void _stats_load_avg_print(void)
{
    rt_base_t counts = 0;
    const rt_base_t total_test_counts = KERN_TEST_CONFIG_LOOP_TIMES * TEST_LEVEL_COUNTS * KERN_TEST_CONCURRENT_THREADS;

    for (size_t i = 0; i < RT_CPUS_NR; i++)
    {
        rt_kprintf("%ld ", _load_average[i]);
        counts += _load_average[i];
    }

    rt_kprintf("\n");
    uassert_int_equal(counts, total_test_counts);
}

static void _thread_entry(void *param)
{
    int level = (rt_ubase_t)param;
    rt_thread_t thr_self = rt_thread_self();

    if (level == 0)
    {
        /* always the first to execute among other working threads */
        for (size_t i = 0; i < KERN_TEST_CONFIG_LOOP_TIMES; i++)
        {
            /* notify our consumer */
            rt_sem_release(&_level_waiting[level + 1]);

            _stats_load_avg_inc();

            /* waiting for resource of ours */
            rt_sem_take(&_level_waiting[level], RT_WAITING_FOREVER);
        }
    }
    else if (level == TEST_LEVEL_COUNTS - 1)
    {

        for (size_t i = 0; i < KERN_TEST_CONFIG_LOOP_TIMES; i++)
        {
            /* waiting for our resource first */
            rt_sem_take(&_level_waiting[level], RT_WAITING_FOREVER);

            _stats_load_avg_inc();

            _print_char(thr_self, '*');

            rt_thread_delay(1);

            /* produce for level 0 worker */
            rt_sem_release(&_level_waiting[0]);
        }
    }
    else
    {
        for (size_t i = 0; i < KERN_TEST_CONFIG_LOOP_TIMES; i++)
        {
            /* waiting for resource of ours */
            rt_sem_take(&_level_waiting[level], RT_WAITING_FOREVER);

            _stats_load_avg_inc();

            /* notify our consumer */
            rt_sem_release(&_level_waiting[level + 1]);
        }
    }

    uassert_true(1);
    rt_sem_release(&_thr_exit_sem);

    return;
}

static void scheduler_tc(void)
{
    LOG_I("Test starts...");
    for (size_t i = 0; i < TEST_LEVEL_COUNTS; i++)
    {
        for (size_t j = 0; j < KERN_TEST_CONCURRENT_THREADS; j++)
        {
            rt_thread_startup(_thread_matrix[i][j]);
        }
    }
    LOG_I("%d threads startup...", TEST_LEVEL_COUNTS * KERN_TEST_CONCURRENT_THREADS);

    /* waiting for sub-threads to exit */
    for (size_t i = 0; i < TEST_LEVEL_COUNTS * KERN_TEST_CONCURRENT_THREADS; i++)
    {
        rt_sem_take(&_thr_exit_sem, RT_WAITING_FOREVER);
    }

    /* print load average */
    _stats_load_avg_print();
}

static rt_err_t utest_tc_init(void)
{
    LOG_I("Setup environment...");
    _star_counter = 1;
    rt_memset(_load_average, 0, sizeof(_load_average));
    rt_sem_init(&_thr_exit_sem, "test", 0, RT_IPC_FLAG_PRIO);

    for (size_t i = 0; i < TEST_LEVEL_COUNTS; i++)
    {
        rt_sem_init(&_level_waiting[i], "test", 0, RT_IPC_FLAG_PRIO);

        for (size_t j = 0; j < KERN_TEST_CONCURRENT_THREADS; j++)
        {
            _thread_matrix[i][j] =
                rt_thread_create("test",
                                 _thread_entry,
                                 (void *)i,
                                 UTEST_THR_STACK_SIZE,
                                 KERN_TEST_CONFIG_HIGHEST_PRIO+i,
                                 5);
            if (!_thread_matrix[i][j])
                uassert_not_null(_thread_matrix[i][j]);
        }
    }
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_sem_detach(&_thr_exit_sem);
    for (size_t i = 0; i < TEST_LEVEL_COUNTS; i++)
    {
        rt_sem_detach(&_level_waiting[i]);
    }
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(scheduler_tc);
}
UTEST_TC_EXPORT(testcase, "core.scheduler_sem", utest_tc_init, utest_tc_cleanup, 10);
