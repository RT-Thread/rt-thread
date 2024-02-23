/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-25     Shell        init ver.
 */
#define __RT_KERNEL_SOURCE__
#include <rtthread.h>
#include <stdlib.h>
#include "utest.h"

#define TEST_SECONDS 10
#define TEST_LOOP_TICKS (TEST_SECONDS * RT_TICK_PER_SECOND)
#define TEST_PROGRESS_COUNTS (36)
#define TEST_PROGRESS_ON (TEST_LOOP_TICKS*2/TEST_PROGRESS_COUNTS)

static struct rt_semaphore _thr_exit_sem;
static struct rt_mutex _ipc_primitive;
static struct rt_semaphore _cons_can_take_mtx;
static struct rt_semaphore _prod_can_take_mtx;
static rt_atomic_t _progress_counter;
#define CONSUMER_MAGIC 0x11223344
#define PRODUCER_MAGIC 0x44332211
static rt_atomic_t _last_holder_flag = CONSUMER_MAGIC;
static rt_base_t _timedout_failed_times = 0;

/**
 * Test on timedout IPC with racing condition where timedout routine and producer
 * thread may race to wakeup sleeper.
 *
 * This test will fork 2 thread, one producer and one consumer. The producer will
 * looping and trigger the IPC on the edge of new tick arrives. The consumer will
 * wait on IPC with a timedout of 1 tick.
 */

static void _wait_until_edge(void)
{
    rt_tick_t entry_level, current;
    rt_base_t random_latency;

    entry_level = rt_tick_get();
    do
    {
        current = rt_tick_get();
    }
    while (current == entry_level);

    /* give a random latency for test */
    random_latency = rand() % 1000 * 1000;
    entry_level = current;
    for (size_t i = 0; i < random_latency; i++)
    {
        current = rt_tick_get();
        if (current != entry_level)
            break;
    }
}

static void _producer_entry(void *param)
{
    rt_err_t error;
    for (size_t i = 0; i < TEST_LOOP_TICKS; i++)
    {
        /**
         * only try to take mutex after consumer have taken it after last
         * release from us.
         */
        error = rt_sem_take(&_prod_can_take_mtx, RT_WAITING_FOREVER);
        if (error)
        {
            uassert_true(0);
            break;
        }

        error = rt_mutex_take(&_ipc_primitive, RT_WAITING_FOREVER);
        if (error)
        {
            uassert_true(0);
            break;
        }

        /* ensure that mutex should be held in round-robin method */
        if (rt_atomic_load(&_last_holder_flag) != CONSUMER_MAGIC)
        {
            uassert_true(0);
            break;
        }
        else
        {
            rt_atomic_store(&_last_holder_flag, PRODUCER_MAGIC);
            rt_sem_release(&_cons_can_take_mtx);
        }

        _wait_until_edge();

        rt_mutex_release(&_ipc_primitive);

        if (rt_atomic_add(&_progress_counter, 1) % TEST_PROGRESS_ON == 0)
            uassert_true(1);
    }

    rt_sem_release(&_thr_exit_sem);
    return;
}

static void _consumer_entry(void *param)
{
    rt_err_t error;
    for (size_t i = 0; i < TEST_LOOP_TICKS; i++)
    {
        /**
         * only try to take mutex after producer have taken it after last
         * release from us.
         */
        error = rt_sem_take(&_cons_can_take_mtx, RT_WAITING_FOREVER);
        if (error)
        {
            uassert_true(0);
            break;
        }

        while (1)
        {
            error = rt_mutex_take_interruptible(&_ipc_primitive, 1);
            if (error == -RT_ETIMEOUT)
            {
                _timedout_failed_times++;
                if (rt_mutex_get_owner(&_ipc_primitive) == rt_thread_self())
                {
                    uassert_true(0);
                    break;
                }
            }
            else
            {
                break;
            }
        }

        if (error != RT_EOK)
        {
            uassert_true(0);
            break;
        }

        /* ensure that mutex should be held in round-robin method */
        if (rt_atomic_load(&_last_holder_flag) != PRODUCER_MAGIC)
        {
            uassert_true(0);
            break;
        }
        else
        {
            rt_atomic_store(&_last_holder_flag, CONSUMER_MAGIC);
            rt_sem_release(&_prod_can_take_mtx);
        }

        rt_mutex_release(&_ipc_primitive);
        if (rt_mutex_get_owner(&_ipc_primitive) == rt_thread_self())
        {
            uassert_true(0);
            break;
        }

        if (rt_atomic_add(&_progress_counter, 1) % TEST_PROGRESS_ON == 0)
            uassert_true(1);
    }

    rt_sem_release(&_thr_exit_sem);
    return;
}

static void timed_mtx_tc(void)
{
    rt_thread_t prod = rt_thread_create(
        "prod",
        _producer_entry,
        (void *)0,
        UTEST_THR_STACK_SIZE,
        UTEST_THR_PRIORITY + 1,
        4);

    rt_thread_t cons = rt_thread_create(
        "cons",
        _consumer_entry,
        (void *)0,
        UTEST_THR_STACK_SIZE,
        UTEST_THR_PRIORITY + 1,
        100);

    rt_thread_startup(prod);
    rt_thread_startup(cons);

    for (size_t i = 0; i < 2; i++)
    {
        uassert_int_equal(
            rt_sem_take(&_thr_exit_sem, 2 * TEST_LOOP_TICKS),
            RT_EOK);
    }

    /* Summary */
    LOG_I("Total failed times: %ld(in %d)\n", _timedout_failed_times, TEST_LOOP_TICKS);
}

static rt_err_t utest_tc_init(void)
{
    _timedout_failed_times = 0;

    rt_mutex_init(&_ipc_primitive, "ipc", RT_IPC_FLAG_PRIO);
    rt_sem_init(&_cons_can_take_mtx, "test", 0, RT_IPC_FLAG_PRIO);
    rt_sem_init(&_prod_can_take_mtx, "test", 1, RT_IPC_FLAG_PRIO);
    rt_sem_init(&_thr_exit_sem, "test", 0, RT_IPC_FLAG_PRIO);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_mutex_detach(&_ipc_primitive);
    rt_sem_detach(&_cons_can_take_mtx);
    rt_sem_detach(&_prod_can_take_mtx);
    rt_sem_detach(&_thr_exit_sem);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(timed_mtx_tc);
}
UTEST_TC_EXPORT(testcase, "testcases.kernel.scheduler.timed_mtx", utest_tc_init, utest_tc_cleanup, TEST_SECONDS * 2);
