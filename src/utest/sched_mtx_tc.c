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
 * Test Case Name: Scheduler Mutex Stress Test (core.scheduler_mutex)
 *
 * Test Objectives:
 * - Validate the stability of the Mutex subsystem under high contention (Stress Test).
 * - Ensure priority inheritance (if supported) or basic blocking/waking works correctly.
 * - In multi-core systems, verify data consistency and spinlock mechanisms when multiple cores contend for a single kernel object simultaneously.
 * - List specific functions or APIs to be tested:
 * - rt_mutex_take()
 * - rt_mutex_release()
 * - rt_thread_create()
 *
 * Test Scenarios:
 * - **Stress Test (mutex_stress_tc):**
 * 1. Create `RT_CPUS_NR` threads (e.g., 4 threads in a Quad-Core setup).
 * 2. Assign **staggered priorities** to these threads (`priority_base + i % range`) to simulate contention between high and low priority tasks.
 * 3. All tester threads execute a tight loop: attempting to take and immediately release the *same* global mutex (`_racing_lock`).
 * - In SMP, this simulates true parallel contention.
 * 4. The main test thread sleeps for `TEST_SECONDS` (30s), periodically printing progress.
 * 5. After time is up, signal threads to exit (`_exit_flag`) and wait for them using a semaphore (`_thr_exit_sem`).
 *
 * Verification Metrics:
 * - **Pass:** The system must remain responsive (no deadlocks, hard faults, or RCU stalls) during the 30-second run.
 * - **Pass:** The main thread must successfully wait for all tester threads to exit (`rt_sem_take` returns `RT_EOK`).
 * - **Pass:** `uassert_true(1)` is executed periodically, confirming the main loop is alive.
 *
 * Dependencies:
 * - Hardware requirements (e.g., specific peripherals)
 * - No specific peripherals required, but Multi-core CPU recommended for SMP testing.
 * (This is met by the qemu-virt64-riscv BSP).
 * - Software configuration (e.g., kernel options, driver initialization)
 * - `RT_USING_UTEST` must be enabled (`RT-Thread Utestcases`).
 * - `Scheduler Test` must be enabled (`RT-Thread Utestcases` -> `Kernel Core` -> 'Scheduler Test').
 * - (Optional) Enable SMP for parallel testing:
 * - Go to `RT-Thread Kernel` -> `Enable SMP (Symmetric multiprocessing)`.
 * - Set `Number of CPUs` to > 1 (e.g., 4).
 * - Environmental assumptions
 * - Requires sufficient heap memory to allocate stacks for `RT_CPUS_NR` threads.
 * - Run the test case from the msh prompt:
 * `utest_run core.scheduler_mutex`
 *
 * Expected Results:
 * - The test continues for approximately 30 seconds.
 * - The console logs periodic success assertions.
 * - Final Output: `[ PASSED ] [ result ] testcase (core.scheduler_mutex)`
 */

#include <rtthread.h>
#include <stdlib.h>
#include "utest.h"

/**
 * Stressful Test for Mutex
 */

#define TEST_SECONDS 30
#define TEST_LOOP_TICKS (TEST_SECONDS * RT_TICK_PER_SECOND)
#define TEST_THREAD_COUNTS (RT_CPUS_NR)
#define TEST_PROGRESS_COUNTS (36)
#define TEST_PROGRESS_ON (TEST_LOOP_TICKS/TEST_PROGRESS_COUNTS)
#define TEST_PRIORITY_HIGHEST (UTEST_THR_PRIORITY+1)
#define TEST_RANDOM_LATENCY_MAX (1000 * 1000)

static struct rt_semaphore _thr_exit_sem;
static rt_atomic_t _progress_counter;
static rt_atomic_t _exit_flag;
static struct rt_mutex _racing_lock;

static void test_thread_entry(void *param)
{
    while (1)
    {
        rt_mutex_take(&_racing_lock, RT_WAITING_FOREVER);
        rt_mutex_release(&_racing_lock);

        if (rt_atomic_load(&_exit_flag))
        {
            break;
        }
    }

    rt_sem_release(&_thr_exit_sem);
}

static void mutex_stress_tc(void)
{
    rt_err_t error;
    rt_thread_t tester;
    const rt_base_t priority_base = TEST_PRIORITY_HIGHEST;

    for (size_t i = 0; i < TEST_THREAD_COUNTS; i++)
    {
        tester = rt_thread_create(
            "tester",
            test_thread_entry,
            (void *)0,
            UTEST_THR_STACK_SIZE,
            priority_base + (i % (RT_THREAD_PRIORITY_MAX - TEST_PRIORITY_HIGHEST)),
            1);

        rt_thread_startup(tester);
    }

    for (size_t i = 0; i < TEST_LOOP_TICKS; i++)
    {
        rt_thread_delay(1);

        if (rt_atomic_add(&_progress_counter, 1) % TEST_PROGRESS_ON == 0)
            uassert_true(1);
    }

    /* trigger exit request for all sub-threads */
    rt_atomic_store(&_exit_flag, 1);

    /* waiting for sub-threads to exit */
    for (size_t i = 0; i < TEST_THREAD_COUNTS; i++)
    {
        error = rt_sem_take(&_thr_exit_sem, RT_WAITING_FOREVER);
        uassert_int_equal(error, RT_EOK);
    }
}

static rt_err_t utest_tc_init(void)
{
    int *pseed = rt_malloc(sizeof(int));
    srand(*(int *)pseed);
    rt_free(pseed);

    rt_sem_init(&_thr_exit_sem, "test", 0, RT_IPC_FLAG_PRIO);
    rt_mutex_init(&_racing_lock, "ipc", RT_IPC_FLAG_PRIO);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_sem_detach(&_thr_exit_sem);
    rt_mutex_detach(&_racing_lock);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(mutex_stress_tc);
}
UTEST_TC_EXPORT(testcase, "core.scheduler_mutex", utest_tc_init, utest_tc_cleanup, TEST_SECONDS);
