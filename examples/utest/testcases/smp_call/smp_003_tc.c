/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/10/28     Shell        Added smp.smoke
 */

#include <rtdevice.h>
#include <utest.h>
#include <utest_assert.h>
#include <smp_call.h>

#define PERCPU_TEST_COUNT 10000
#define NEWLINE_ON 80

static struct rt_semaphore _utestd_exited;
static rt_thread_t _utestd[RT_CPUS_NR];
static rt_atomic_t _entry_counts[RT_CPUS_NR];

static void _logging_progress(void)
{
    static rt_atomic_t counts;
    rt_ubase_t old;

    rt_kputs("#");
    old = rt_atomic_add(&counts, 1);
    if (old % NEWLINE_ON == 0)
    {
        rt_kputs("\n");
    }
}

static void _test_smp_cb(void *param)
{
    rt_ubase_t req_cpuid = (rt_ubase_t)param;

    if (!rt_hw_interrupt_is_disabled())
    {
        /* SYNC.004 */
        uassert_true(0);
    }
    _logging_progress();
    rt_atomic_add(&_entry_counts[req_cpuid], 1);
}

static void _utestd_entry(void *oncpu_param)
{
    rt_ubase_t oncpu = (rt_ubase_t)oncpu_param;
    volatile int cpu_mask;
    volatile int popcount = 0;
    rt_thread_t curthr = rt_thread_self();

    if (rt_hw_cpu_id() != oncpu)
    {
        /* SYNC.004 */
        uassert_true(0);
    }

    for (size_t i = 0; i < PERCPU_TEST_COUNT; i++)
    {
        cpu_mask = rand() % RT_ALL_CPU;

        rt_smp_call_cpu_mask(cpu_mask, _test_smp_cb, oncpu_param, 0);
        popcount += __builtin_popcount(cpu_mask);
    }

    for (size_t i = 0; i < RT_CPUS_NR; i++)
    {
        rt_thread_control(curthr, RT_THREAD_CTRL_BIND_CPU, (void *)i);
    }

    LOG_D("popcount %d, _entry_counts[%d] %d", popcount, oncpu, _entry_counts[oncpu]);

    /* MP.002 */
    uassert_true(popcount == rt_atomic_load(&_entry_counts[oncpu]));

    rt_sem_release(&_utestd_exited);
}

static void _async_call(void)
{
    for (size_t i = 0; i < RT_CPUS_NR; i++)
    {
        rt_thread_startup(_utestd[i]);
    }

    for (size_t i = 0; i < RT_CPUS_NR; i++)
    {
        rt_sem_take(&_utestd_exited, RT_WAITING_FOREVER);
    }
}

static rt_err_t utest_tc_init(void)
{
    for (size_t i = 0; i < RT_CPUS_NR; i++)
    {
        rt_atomic_store(&_entry_counts[i], 0);
        _utestd[i] = rt_thread_create("utestd", _utestd_entry, (void *)i,
                                      UTEST_THR_STACK_SIZE, UTEST_THR_PRIORITY,
                                      20);
        rt_thread_control(_utestd[i], RT_THREAD_CTRL_BIND_CPU, (void *)i);

        /* SYNC.001, SYNC.002, SYNC.003 */
        uassert_true(_utestd[i] != RT_NULL);
    }

    rt_sem_init(&_utestd_exited, "utestd", 0, RT_IPC_FLAG_PRIO);
    srand(rt_tick_get());

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_sem_detach(&_utestd_exited);

    return RT_EOK;
}

static void _testcase(void)
{
    UTEST_UNIT_RUN(_async_call);
}

UTEST_TC_EXPORT(_testcase, "testcase.smp.smoke.003", utest_tc_init, utest_tc_cleanup, 10);
