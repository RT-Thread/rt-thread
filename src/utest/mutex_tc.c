/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09.01     luckyzjq     the first version
 * 2023-09-15     xqyjlj       change stack size in cpu64
 * 2026-07-15     meng-plus    add cross-thread delete owner regression (#11619)
 */

/**
 * Test Case Name: RT-Thread Mutex Functional and Scheduling Validation
 * Test Objectives:
 * - Verify correctness of static and dynamic mutex operations
 * - Validate priority inheritance, recursive locking, timeout handling, and error cases
 * - Test core mutex APIs: rt_mutex_init/detach, rt_mutex_create/delete,
 *   rt_mutex_take/trytake/release, and related thread scheduling functions
 * Test Scenarios:
 * - Mutex acquisition under contention with multi-thread scheduling
 * - Try-take on locked mutex, timeout-based take, recursive take sequence
 * - Priority inheritance when high-priority threads are blocked by lower-priority holders
 * - Behavior differences between static and dynamic mutexes
 * - Mutex release error handling, invalid release, and cleanup
 * - Cross-thread delete of a mutex owner must release the lock and wake waiters
 * Verification Metrics:
 * - Correct return codes for all mutex operations (RT_EOK, timeouts, error states)
 * - Proper priority inheritance and restoration during contention
 * - Expected thread wake-up and state transition behavior
 * - Successful thread synchronization via _sync_flag
 * Dependencies:
 * - RT-Thread kernel with IPC and mutex support enabled
 * - Heap availability when testing dynamic mutex creation
 * - Scheduler operating normally with multi-thread preemption
 * - Accurate system tick for timeout and delay validation
 * Expected Results:
 * - All mutex APIs behave according to RT-Thread specifications
 * - Static and dynamic mutex tests complete successfully
 * - Priority inversion resolved via priority inheritance
 * - Console/log output indicates all UTEST cases pass
 */

#define __RT_IPC_SOURCE__

#include <rtthread.h>
#include <rtsched.h>
#include <stdlib.h>
#include "utest.h"

#ifdef ARCH_CPU_64BIT
#define THREAD_STACKSIZE 8192
#else
#define THREAD_STACKSIZE 4096
#endif

static struct rt_mutex static_mutex;

#ifdef RT_USING_HEAP
static rt_mutex_t dynamic_mutex;
#endif /* RT_USING_HEAP */

static volatile int _sync_flag;

/* init test */
static void test_static_mutex_init(void)
{
    rt_err_t result = -RT_ERROR;

    result = rt_mutex_init(&static_mutex, "static_mutex", RT_IPC_FLAG_PRIO);
    if (RT_EOK != result)
    {
        uassert_true(RT_FALSE);
    }

    result = rt_mutex_detach(&static_mutex);
    if (RT_EOK != result)
    {
        uassert_true(RT_FALSE);
    }

    result = rt_mutex_init(&static_mutex, "static_mutex", RT_IPC_FLAG_PRIO);
    if (RT_EOK != result)
    {
        uassert_true(RT_FALSE);
    }

    result = rt_mutex_detach(&static_mutex);
    if (RT_EOK != result)
    {
        uassert_true(RT_FALSE);
    }

    uassert_true(RT_TRUE);
}

/* static take test */
static void static_mutex_take_entry(void *param)
{
    rt_err_t result;
    rt_mutex_t mutex;

    int rand_num = rand() % 0x1000;
    mutex = (rt_mutex_t)param;

    result = rt_mutex_take(mutex, rand_num);
    if (RT_EOK == result)
    {
        uassert_true(RT_FALSE);
    }
    _sync_flag++;
}

static void test_static_mutex_take(void)
{
    rt_err_t result;

    _sync_flag = 0;

    result = rt_mutex_init(&static_mutex, "static_mutex", RT_IPC_FLAG_PRIO);
    if (RT_EOK != result)
    {
        uassert_true(RT_FALSE);
        return;
    }

    /* take mutex and not release */
    result = rt_mutex_take(&static_mutex, RT_WAITING_FOREVER);
    if (RT_EOK != result)
        uassert_true(RT_FALSE);

    rt_thread_t tid = rt_thread_create("mutex_th",
                                       static_mutex_take_entry,
                                       &static_mutex,
                                       THREAD_STACKSIZE,
                                       10,
                                       10);
    if (RT_NULL == tid)
    {
        uassert_true(RT_FALSE);
        return;
    }

    /* startup thread take second */
    rt_thread_startup(tid);

    while (_sync_flag != 1)
    {
        rt_thread_mdelay(10);
    }

    result = rt_mutex_detach(&static_mutex);
    if (RT_EOK != result)
        uassert_true(RT_FALSE);

    uassert_true(RT_TRUE);
}

/* static release test */
static void static_mutex_release_entry(void *param)
{
    rt_err_t result;
    rt_mutex_t mutex;

    int rand_num = rand() % 0x1000;
    mutex = (rt_mutex_t)param;

    result = rt_mutex_take(mutex, rand_num);
    if (RT_EOK != result)
    {
        uassert_true(RT_FALSE);
    }
    _sync_flag++;
}
static void test_static_mutex_release(void)
{
    rt_err_t result;

    _sync_flag = 0;

    result = rt_mutex_init(&static_mutex, "static_mutex", RT_IPC_FLAG_PRIO);
    if (RT_EOK != result)
    {
        uassert_true(RT_FALSE);
        return;
    }

    result = rt_mutex_release(&static_mutex);
    uassert_true(result < 0);

    /* take mutex */
    result = rt_mutex_take(&static_mutex, RT_WAITING_FOREVER);
    if (RT_EOK != result)
        uassert_true(RT_FALSE);

    /* release mutex */
    result = rt_mutex_release(&static_mutex);
    if (RT_EOK != result)
        uassert_true(RT_FALSE);

    rt_thread_t tid = rt_thread_create("mutex_th",
                                       static_mutex_release_entry,
                                       &static_mutex,
                                       THREAD_STACKSIZE,
                                       10,
                                       10);
    if (RT_NULL == tid)
    {
        uassert_true(RT_FALSE);
        return;
    }

    /* startup thread and take mutex second */
    rt_thread_startup(tid);

    while (_sync_flag != 1)
    {
        rt_thread_mdelay(10);
    }

    result = rt_mutex_detach(&static_mutex);
    if (RT_EOK != result)
        uassert_true(RT_FALSE);

    uassert_true(RT_TRUE);
}

/* static trytake test */
static void static_mutex_trytake_entry(void *param)
{
    rt_err_t result;
    rt_mutex_t mutex;

    mutex = (rt_mutex_t)param;

    result = rt_mutex_trytake(mutex);
    if (RT_EOK == result)
    {
        uassert_true(RT_FALSE);
    }
    _sync_flag++;
}
static void test_static_mutex_trytake(void)
{
    rt_err_t result;

    _sync_flag = 0;

    result = rt_mutex_init(&static_mutex, "static_mutex", RT_IPC_FLAG_PRIO);
    if (RT_EOK != result)
    {
        uassert_true(RT_FALSE);
        return;
    }

    /* take mutex and not release */
    result = rt_mutex_take(&static_mutex, RT_WAITING_FOREVER);
    if (RT_EOK != result)
        uassert_true(RT_FALSE);

    rt_thread_t tid = rt_thread_create("mutex_th",
                                       static_mutex_trytake_entry,
                                       &static_mutex,
                                       THREAD_STACKSIZE,
                                       10,
                                       10);
    if (RT_NULL == tid)
    {
        uassert_true(RT_FALSE);
        return;
    }

    /* startup thread and trytake mutex second */
    rt_thread_startup(tid);

    while (_sync_flag != 1)
    {
        rt_thread_mdelay(10);
    }

    result = rt_mutex_detach(&static_mutex);
    if (RT_EOK != result)
        uassert_true(RT_FALSE);

    uassert_true(RT_TRUE);
}

static rt_thread_t tid1 = RT_NULL;
static rt_thread_t tid2 = RT_NULL;
static rt_thread_t tid3 = RT_NULL;

/* static mutex priority reverse test */
static void static_thread1_entry(void *param)
{
    /* let system schedule */
    rt_thread_mdelay(100);

    /*  thread3 hode mutex  thread2 take mutex */
    /* check thread2 and thread3 priority */
    if (RT_SCHED_PRIV(tid2).current_priority != RT_SCHED_PRIV(tid3).current_priority)
    {
        uassert_true(RT_FALSE);
    }
    else
    {
        uassert_true(RT_TRUE);
    }
    _sync_flag++;
}

static void static_thread2_entry(void *param)
{
    rt_err_t result;
    rt_mutex_t mutex = (rt_mutex_t)param;

    /* let system schedule */
    rt_thread_mdelay(50);

    result = rt_mutex_take(mutex, RT_WAITING_FOREVER);
    if (result == RT_EOK)
    {
        rt_mutex_release(mutex);
    }
    _sync_flag++;
}
static void static_thread3_entry(void *param)
{
    rt_tick_t tick;
    rt_err_t result;
    rt_mutex_t mutex = (rt_mutex_t)param;

    result = rt_mutex_take(mutex, RT_WAITING_FOREVER);
    if (result != RT_EOK)
    {
        uassert_true(RT_FALSE);
    }

    tick = rt_tick_get();
    while (rt_tick_get() - tick < (RT_TICK_PER_SECOND / 2));

    rt_mutex_release(mutex);
    _sync_flag++;
}

static void test_static_pri_reverse(void)
{
    rt_err_t result;
    tid1 = RT_NULL;
    tid2 = RT_NULL;
    tid3 = RT_NULL;

    _sync_flag = 0;

    result = rt_mutex_init(&static_mutex, "static_mutex", RT_IPC_FLAG_PRIO);
    if (RT_EOK != result)
    {
        uassert_true(RT_FALSE);
        return;
    }

    /* thread1 */
    tid1 = rt_thread_create("thread1",
                            static_thread1_entry,
                            &static_mutex,
                            UTEST_THR_STACK_SIZE,
                            10 - 1,
                            10);
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    /* thread2 */
    tid2 = rt_thread_create("thread2",
                            static_thread2_entry,
                            &static_mutex,
                            UTEST_THR_STACK_SIZE,
                            10,
                            10);
    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);

    /* thread3 */
    tid3 = rt_thread_create("thread3",
                            static_thread3_entry,
                            &static_mutex,
                            UTEST_THR_STACK_SIZE,
                            10 + 1,
                            10);
    if (tid3 != RT_NULL)
        rt_thread_startup(tid3);

    while (_sync_flag != 3)
    {
        rt_thread_mdelay(10);
    }

    result = rt_mutex_detach(&static_mutex);
    if (RT_EOK != result)
        uassert_true(RT_FALSE);

    uassert_true(RT_TRUE);
}

/* create test */
static void test_dynamic_mutex_create(void)
{
    rt_err_t result = -RT_ERROR;

    /* PRIO mode */
    dynamic_mutex = rt_mutex_create("dynamic_mutex", RT_IPC_FLAG_PRIO);
    if (RT_NULL == dynamic_mutex)
    {
        uassert_true(RT_FALSE);
    }

    result = rt_mutex_delete(dynamic_mutex);
    if (RT_EOK != result)
    {
        uassert_true(RT_FALSE);
    }

    /* FIFO mode */
    dynamic_mutex = rt_mutex_create("dynamic_mutex", RT_IPC_FLAG_PRIO);
    if (RT_NULL == dynamic_mutex)
    {
        uassert_true(RT_FALSE);
    }

    result = rt_mutex_delete(dynamic_mutex);
    if (RT_EOK != result)
    {
        uassert_true(RT_FALSE);
    }

    uassert_true(RT_TRUE);
}

/* dynamic take test */
static void dynamic_mutex_take_entry(void *param)
{
    rt_err_t result;
    rt_mutex_t mutex;

    int rand_num = rand() % 0x1000;
    mutex = (rt_mutex_t)param;

    result = rt_mutex_take(mutex, rand_num);
    if (RT_EOK == result)
    {
        uassert_true(RT_FALSE);
    }
    _sync_flag++;
}

static void test_dynamic_mutex_take(void)
{
    rt_err_t result;

    _sync_flag = 0;

    dynamic_mutex = rt_mutex_create("dynamic_mutex", RT_IPC_FLAG_PRIO);
    if (RT_NULL == dynamic_mutex)
    {
        uassert_true(RT_FALSE);
        return;
    }

    /* take mutex and not release */
    result = rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);
    if (RT_EOK != result)
        uassert_true(RT_FALSE);

    rt_thread_t tid = rt_thread_create("mutex_th",
                                       dynamic_mutex_take_entry,
                                       dynamic_mutex,
                                       THREAD_STACKSIZE,
                                       10,
                                       10);
    if (RT_NULL == tid)
    {
        uassert_true(RT_FALSE);
        return;
    }

    /* startup thread take second */
    rt_thread_startup(tid);

    while (_sync_flag != 1)
    {
        rt_thread_mdelay(10);
    }

    result = rt_mutex_delete(dynamic_mutex);
    if (RT_EOK != result)
        uassert_true(RT_FALSE);

    uassert_true(RT_TRUE);
}

/* dynamic release test */
static void dynamic_mutex_release_entry(void *param)
{
    rt_err_t result;
    rt_mutex_t mutex;

    int rand_num = rand() % 0x1000;
    mutex = (rt_mutex_t)param;

    result = rt_mutex_take(mutex, rand_num);
    if (RT_EOK != result)
    {
        uassert_true(RT_FALSE);
    }
    _sync_flag++;
}
static void test_dynamic_mutex_release(void)
{
    rt_err_t result;

    _sync_flag = 0;
    dynamic_mutex = rt_mutex_create("dynamic_mutex", RT_IPC_FLAG_PRIO);
    if (RT_NULL == dynamic_mutex)
    {
        uassert_true(RT_FALSE);
        return;
    }

    result = rt_mutex_release(dynamic_mutex);
    uassert_true(result < 0);

    /* take mutex */
    result = rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);
    if (RT_EOK != result)
        uassert_true(RT_FALSE);

    /* release mutex */
    result = rt_mutex_release(dynamic_mutex);
    if (RT_EOK != result)
        uassert_true(RT_FALSE);

    rt_thread_t tid = rt_thread_create("mutex_th",
                                       dynamic_mutex_release_entry,
                                       dynamic_mutex,
                                       THREAD_STACKSIZE,
                                       10,
                                       10);
    if (RT_NULL == tid)
    {
        uassert_true(RT_FALSE);
        return;
    }

    /* startup thread and take mutex second */
    rt_thread_startup(tid);

    while (_sync_flag != 1)
    {
        rt_thread_mdelay(10);
    }

    result = rt_mutex_delete(dynamic_mutex);
    if (RT_EOK != result)
        uassert_true(RT_FALSE);

    uassert_true(RT_TRUE);
}

/* dynamic trytake test */
static void dynamic_mutex_trytake_entry(void *param)
{
    rt_err_t result;
    rt_mutex_t mutex;

    mutex = (rt_mutex_t)param;

    result = rt_mutex_trytake(mutex);
    if (RT_EOK == result)
    {
        uassert_true(RT_FALSE);
    }
    _sync_flag++;
}
static void test_dynamic_mutex_trytake(void)
{
    rt_err_t result;

    _sync_flag = 0;
    dynamic_mutex = rt_mutex_create("dynamic_mutex", RT_IPC_FLAG_PRIO);
    if (RT_NULL == dynamic_mutex)
    {
        uassert_true(RT_FALSE);
        return;
    }

    /* take mutex and not release */
    result = rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);
    if (RT_EOK != result)
        uassert_true(RT_FALSE);

    rt_thread_t tid = rt_thread_create("mutex_th",
                                       dynamic_mutex_trytake_entry,
                                       dynamic_mutex,
                                       THREAD_STACKSIZE,
                                       10,
                                       10);
    if (RT_NULL == tid)
    {
        uassert_true(RT_FALSE);
        return;
    }

    /* startup thread and trytake mutex second */
    rt_thread_startup(tid);

    while (_sync_flag != 1)
    {
        rt_thread_mdelay(10);
    }

    result = rt_mutex_delete(dynamic_mutex);
    if (RT_EOK != result)
        uassert_true(RT_FALSE);

    uassert_true(RT_TRUE);
}

/* dynamic mutex priority reverse test */
static void dynamic_thread1_entry(void *param)
{
    /* let system schedule */
    rt_thread_mdelay(100);

    /*  thread3 hode mutex  thread2 take mutex */
    /* check thread2 and thread3 priority */
    if (RT_SCHED_PRIV(tid2).current_priority != RT_SCHED_PRIV(tid3).current_priority)
    {
        uassert_true(RT_FALSE);
    }
    else
    {
        uassert_true(RT_TRUE);
    }
    _sync_flag++;
}

static void dynamic_thread2_entry(void *param)
{
    rt_err_t result;
    rt_mutex_t mutex = (rt_mutex_t)param;

    /* let system schedule */
    rt_thread_mdelay(50);

    result = rt_mutex_take(mutex, RT_WAITING_FOREVER);
    if (result == RT_EOK)
    {
        rt_mutex_release(mutex);
    }
    _sync_flag++;
}
static void dynamic_thread3_entry(void *param)
{
    rt_tick_t tick;
    rt_err_t result;
    rt_mutex_t mutex = (rt_mutex_t)param;

    result = rt_mutex_take(mutex, RT_WAITING_FOREVER);
    if (result != RT_EOK)
    {
        uassert_true(RT_FALSE);
    }

    tick = rt_tick_get();
    while (rt_tick_get() - tick < (RT_TICK_PER_SECOND / 2));

    rt_mutex_release(mutex);
    _sync_flag++;
}

static void test_dynamic_pri_reverse(void)
{
    rt_err_t result;
    tid1 = RT_NULL;
    tid2 = RT_NULL;
    tid3 = RT_NULL;

    _sync_flag = 0;
    dynamic_mutex = rt_mutex_create("dynamic_mutex", RT_IPC_FLAG_PRIO);
    if (RT_NULL == dynamic_mutex)
    {
        uassert_true(RT_FALSE);
        return;
    }

    /* thread1 */
    tid1 = rt_thread_create("thread1",
                            dynamic_thread1_entry,
                            dynamic_mutex,
                            UTEST_THR_STACK_SIZE,
                            10 - 1,
                            10);
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    /* thread2 */
    tid2 = rt_thread_create("thread2",
                            dynamic_thread2_entry,
                            dynamic_mutex,
                            UTEST_THR_STACK_SIZE,
                            10,
                            10);
    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);

    /* thread3 */
    tid3 = rt_thread_create("thread3",
                            dynamic_thread3_entry,
                            dynamic_mutex,
                            UTEST_THR_STACK_SIZE,
                            10 + 1,
                            10);
    if (tid3 != RT_NULL)
        rt_thread_startup(tid3);

    while (_sync_flag != 3)
    {
        rt_thread_mdelay(10);
    }

    result = rt_mutex_delete(dynamic_mutex);
    if (RT_EOK != result)
        uassert_true(RT_FALSE);

    uassert_true(RT_TRUE);
}

static void recursive_lock_test_entry(void *param)
{
    rt_err_t result;
    rt_mutex_t mutex = (rt_mutex_t)param;

    result = rt_mutex_take(mutex, RT_WAITING_FOREVER);
    uassert_true(result == RT_EOK);
    uassert_true(_sync_flag == 0);
    result = rt_mutex_take(mutex, RT_WAITING_FOREVER);
    uassert_true(result == RT_EOK);
    _sync_flag++;
}

static void test_recurse_lock(void)
{
    rt_err_t result;

    _sync_flag = 0;
    result = rt_mutex_init(&static_mutex, "static_mutex", RT_IPC_FLAG_PRIO);
    uassert_true(result == RT_EOK);

    /* take mutex and not release */
    result = rt_mutex_take(&static_mutex, RT_WAITING_FOREVER);
    uassert_true(result == RT_EOK);

    /* take mutex twice */
    result = rt_mutex_take(&static_mutex, RT_WAITING_FOREVER);
    uassert_true(result == RT_EOK);

    rt_thread_t tid = rt_thread_create("mutex_th",
                                       recursive_lock_test_entry,
                                       &static_mutex,
                                       THREAD_STACKSIZE,
                                       10,
                                       10);
    _sync_flag = -1;

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    result = rt_mutex_release(&static_mutex);
    uassert_true(result == RT_EOK);

    _sync_flag = 0;

    result = rt_mutex_release(&static_mutex);
    uassert_true(result == RT_EOK);

    while (_sync_flag != 1)
    {
        rt_thread_mdelay(10);
    }

    result = rt_mutex_take(&static_mutex, RT_WAITING_FOREVER);
    uassert_true(result == RT_EOK);

    result = rt_mutex_detach(&static_mutex);
    uassert_true(result == RT_EOK);
}

#ifdef RT_USING_HEAP
/*
 * Issue #11619: deleting a thread that still holds a mutex must not leave an
 * orphan lock; waiters blocked on that mutex must be woken and acquire ownership.
 */
static volatile int _holder_ready;
static volatile int _waiter_got;

static void orphan_mutex_holder_entry(void *param)
{
    rt_mutex_t mutex = (rt_mutex_t)param;

    if (rt_mutex_take(mutex, RT_WAITING_FOREVER) != RT_EOK)
    {
        uassert_true(RT_FALSE);
        return;
    }

    _holder_ready = 1;

    /* Hold forever until deleted by another thread */
    while (1)
    {
        rt_thread_mdelay(1000);
    }
}

static void orphan_mutex_waiter_entry(void *param)
{
    rt_err_t result;
    rt_mutex_t mutex = (rt_mutex_t)param;

    result = rt_mutex_take(mutex, RT_WAITING_FOREVER);
    uassert_true(result == RT_EOK);

    result = rt_mutex_release(mutex);
    uassert_true(result == RT_EOK);

    /* Signal after release so the main thread can take without racing */
    _waiter_got = 1;
}

static void test_cross_thread_delete_mutex_owner(void)
{
    rt_err_t result;
    rt_thread_t holder;
    rt_thread_t waiter;
    int timeout;

    _holder_ready = 0;
    _waiter_got = 0;

    result = rt_mutex_init(&static_mutex, "orphan_mtx", RT_IPC_FLAG_PRIO);
    uassert_true(result == RT_EOK);

    /* Lower priority holder takes the mutex and keeps it */
    holder = rt_thread_create("mtx_hold",
                              orphan_mutex_holder_entry,
                              &static_mutex,
                              THREAD_STACKSIZE,
                              12,
                              10);
    uassert_true(holder != RT_NULL);
    rt_thread_startup(holder);

    timeout = 100;
    while ((_holder_ready == 0) && (timeout-- > 0))
    {
        rt_thread_mdelay(10);
    }
    uassert_true(_holder_ready == 1);

    /* Higher priority waiter blocks on the held mutex */
    waiter = rt_thread_create("mtx_wait",
                              orphan_mutex_waiter_entry,
                              &static_mutex,
                              THREAD_STACKSIZE,
                              10,
                              10);
    uassert_true(waiter != RT_NULL);
    rt_thread_startup(waiter);

    /* Ensure waiter is pending before cross-thread delete */
    rt_thread_mdelay(50);
    uassert_true(_waiter_got == 0);

    result = rt_thread_delete(holder);
    uassert_true(result == RT_EOK);

    timeout = 100;
    while ((_waiter_got == 0) && (timeout-- > 0))
    {
        rt_thread_mdelay(10);
    }
    uassert_true(_waiter_got == 1);

    /* After waiter releases, mutex must be acquirable again */
    result = rt_mutex_take(&static_mutex, rt_tick_from_millisecond(500));
    uassert_true(result == RT_EOK);
    uassert_true(rt_mutex_get_hold(&static_mutex) == 1);

    result = rt_mutex_release(&static_mutex);
    uassert_true(result == RT_EOK);

    result = rt_mutex_detach(&static_mutex);
    uassert_true(result == RT_EOK);

    /* Let waiter thread exit cleanly */
    rt_thread_mdelay(50);
}
#endif /* RT_USING_HEAP */

#ifdef RT_USING_HEAP
static struct rt_semaphore mutex_delete_ready;
static struct rt_semaphore mutex_delete_done;
static struct rt_semaphore mutex_delete_restart;
static struct rt_semaphore mutex_delete_restart_done;
static rt_mutex_t mutex_delete_dynamic;
static void *mutex_delete_replacement_memory;
static struct rt_mutex mutex_delete_static;
static volatile rt_err_t mutex_delete_wait_result;
static volatile rt_err_t mutex_delete_next_wait_result;
static volatile rt_err_t mutex_delete_restart_result;
static rt_thread_t mutex_delete_waiter;
static rt_int32_t mutex_delete_wait_timeout;
static rt_bool_t mutex_delete_semaphores_initialized;

static void mutex_delete_bind_waiter(rt_thread_t thread)
{
#ifdef RT_USING_SMP
    uassert_int_equal(rt_thread_control(thread,
                                        RT_THREAD_CTRL_BIND_CPU,
                                        (void *)(rt_ubase_t)rt_cpu_get_id()),
                      RT_EOK);
#else
    RT_UNUSED(thread);
#endif /* RT_USING_SMP */
}

/* Record the result returned by a waiter after its mutex is deleted. */
static void mutex_delete_waiter_entry(void *parameter)
{
    rt_sem_release(&mutex_delete_ready);
    mutex_delete_wait_result =
        rt_mutex_take((rt_mutex_t)parameter, mutex_delete_wait_timeout);
    rt_sem_release(&mutex_delete_done);
}

static void mutex_delete_next_waiter_entry(void *parameter)
{
    rt_mutex_t mutex = (rt_mutex_t)parameter;

    rt_sem_release(&mutex_delete_ready);
    mutex_delete_next_wait_result =
        rt_mutex_take(mutex, mutex_delete_wait_timeout);
    if (mutex_delete_next_wait_result == RT_EOK)
    {
        mutex_delete_next_wait_result = rt_mutex_release(mutex);
    }
    rt_sem_release(&mutex_delete_done);
}

/* Restart a timeout after release has observed timer ownership. */
static void mutex_delete_restart_timeout_entry(void *parameter)
{
    rt_thread_t thread = (rt_thread_t)parameter;
    rt_tick_t timeout = 1;

    rt_sem_take(&mutex_delete_restart, RT_WAITING_FOREVER);
    mutex_delete_restart_result =
        rt_timer_control(&thread->thread_timer,
                         RT_TIMER_CTRL_SET_TIME,
                         &timeout);
    if (mutex_delete_restart_result == RT_EOK)
    {
        mutex_delete_restart_result = rt_timer_start(&thread->thread_timer);
    }
    rt_sem_release(&mutex_delete_restart_done);
}

/* Wait until the mutex waiter enters the suspend list. */
static void mutex_delete_wait_until_suspended(rt_thread_t thread)
{
    rt_sched_lock_level_t slvl;

    for (;;)
    {
        rt_sched_lock(&slvl);
        if ((RT_SCHED_CTX(thread).stat & RT_THREAD_SUSPEND_MASK) ==
            RT_THREAD_SUSPEND_MASK)
        {
            rt_sched_unlock(slvl);
            break;
        }
        rt_sched_unlock(slvl);
        rt_thread_delay(1);
    }
}

/* Wait until timeout cleanup is complete while keeping the waiter READY. */
static rt_bool_t mutex_delete_wait_until_timeout(rt_thread_t thread)
{
    rt_tick_t start;
    rt_tick_t timeout = rt_tick_from_millisecond(1000);

    start = rt_tick_get();
    for (;;)
    {
        rt_sched_lock_level_t slvl;
        rt_bool_t ready;
        rt_bool_t cleaned;

        rt_sched_lock(&slvl);
        ready = ((RT_SCHED_CTX(thread).stat & RT_THREAD_STAT_MASK) ==
                 RT_THREAD_READY);
        cleaned = ((thread->pending_object == RT_NULL) &&
                   (thread->error == -RT_ETIMEOUT));
        rt_sched_unlock(slvl);

        if (ready && cleaned)
        {
            return RT_TRUE;
        }

        if ((rt_tick_get() - start) >= timeout)
        {
            return RT_FALSE;
        }

        /* The controller has higher priority than the waiter. */
        rt_thread_yield();
    }
}

/* Verify that deleted mutex waiters do not access stale objects. */
static void test_mutex_delete_waiter(void)
{
    mutex_delete_wait_timeout = RT_WAITING_FOREVER;
    mutex_delete_dynamic = rt_mutex_create("delmtx", RT_IPC_FLAG_PRIO);
    uassert_true(mutex_delete_dynamic != RT_NULL);
    uassert_int_equal(rt_mutex_take(mutex_delete_dynamic,
                                    RT_WAITING_FOREVER),
                      RT_EOK);

    mutex_delete_wait_result = -RT_ERROR;

    mutex_delete_waiter = rt_thread_create("mtxwait",
                                           mutex_delete_waiter_entry,
                                           mutex_delete_dynamic,
                                           UTEST_THR_STACK_SIZE,
                                           UTEST_THR_PRIORITY + 1,
                                           10);
    uassert_true(mutex_delete_waiter != RT_NULL);
    mutex_delete_bind_waiter(mutex_delete_waiter);
    uassert_int_equal(rt_thread_startup(mutex_delete_waiter), RT_EOK);

    uassert_int_equal(rt_sem_take(&mutex_delete_ready,
                                  RT_WAITING_FOREVER),
                      RT_EOK);
    mutex_delete_wait_until_suspended(mutex_delete_waiter);

    uassert_int_equal(rt_mutex_delete(mutex_delete_dynamic), RT_EOK);
    mutex_delete_dynamic = RT_NULL;

    mutex_delete_replacement_memory =
        rt_malloc(sizeof(struct rt_mutex));
    uassert_true(mutex_delete_replacement_memory != RT_NULL);
    if (mutex_delete_replacement_memory ==
        (void *)mutex_delete_waiter->parameter)
    {
        rt_memset(mutex_delete_replacement_memory,
                  0xA5,
                  sizeof(struct rt_mutex));
    }

    uassert_int_equal(rt_sem_take(&mutex_delete_done,
                                  rt_tick_from_millisecond(1000)),
                      RT_EOK);
    uassert_int_equal(mutex_delete_wait_result, -RT_ERROR);
    rt_free(mutex_delete_replacement_memory);
    mutex_delete_replacement_memory = RT_NULL;

    uassert_int_equal(rt_mutex_init(&mutex_delete_static,
                                    "detmtx",
                                    RT_IPC_FLAG_PRIO),
                      RT_EOK);
    uassert_int_equal(rt_mutex_take(&mutex_delete_static,
                                    RT_WAITING_FOREVER),
                      RT_EOK);

    mutex_delete_waiter = rt_thread_create("mtxwait2",
                                           mutex_delete_waiter_entry,
                                           &mutex_delete_static,
                                           UTEST_THR_STACK_SIZE,
                                           UTEST_THR_PRIORITY + 1,
                                           10);
    uassert_true(mutex_delete_waiter != RT_NULL);
    mutex_delete_bind_waiter(mutex_delete_waiter);
    uassert_int_equal(rt_thread_startup(mutex_delete_waiter), RT_EOK);

    uassert_int_equal(rt_sem_take(&mutex_delete_ready,
                                  RT_WAITING_FOREVER),
                      RT_EOK);
    mutex_delete_wait_until_suspended(mutex_delete_waiter);

    uassert_int_equal(rt_mutex_detach(&mutex_delete_static), RT_EOK);
    rt_memset(&mutex_delete_static, 0xA5, sizeof(mutex_delete_static));

    uassert_int_equal(rt_sem_take(&mutex_delete_done,
                                  rt_tick_from_millisecond(1000)),
                      RT_EOK);
    uassert_int_equal(mutex_delete_wait_result, -RT_ERROR);
}

/* Verify a timed out waiter does not access a detached mutex. */
static void test_mutex_timeout_delete_waiter(void)
{
    rt_sched_lock_level_t slvl;
    rt_thread_t waiter;
    rt_thread_t restart_thread;
    rt_bool_t suspended;
    rt_err_t stop_result;

    mutex_delete_wait_timeout = rt_tick_from_millisecond(1000);
    mutex_delete_restart_result = -RT_ERROR;
    uassert_int_equal(rt_mutex_init(&mutex_delete_static,
                                    "timemtx",
                                    RT_IPC_FLAG_PRIO),
                      RT_EOK);
    uassert_int_equal(rt_mutex_take(&mutex_delete_static,
                                    RT_WAITING_FOREVER),
                      RT_EOK);

    mutex_delete_waiter = rt_thread_create("mtxwait3",
                                           mutex_delete_waiter_entry,
                                           &mutex_delete_static,
                                           UTEST_THR_STACK_SIZE,
                                           UTEST_THR_PRIORITY + 1,
                                           10);
    uassert_true(mutex_delete_waiter != RT_NULL);
    waiter = mutex_delete_waiter;
    mutex_delete_bind_waiter(waiter);
    uassert_int_equal(rt_thread_startup(waiter), RT_EOK);

    uassert_int_equal(rt_sem_take(&mutex_delete_ready,
                                  RT_WAITING_FOREVER),
                      RT_EOK);
    mutex_delete_wait_until_suspended(waiter);

    /* Stop the timer without clearing the scheduler timer ownership flag. */
    rt_sched_lock(&slvl);
    suspended = rt_sched_thread_is_suspended(waiter);
    stop_result = rt_timer_stop(&waiter->thread_timer);
    rt_sched_unlock(slvl);
    uassert_true(suspended);
    uassert_int_equal(stop_result, RT_EOK);

    restart_thread = rt_thread_create("mtxrst2",
                                      mutex_delete_restart_timeout_entry,
                                      waiter,
                                      UTEST_THR_STACK_SIZE,
                                      UTEST_THR_PRIORITY + 3,
                                      10);
    uassert_true(restart_thread != RT_NULL);
    mutex_delete_bind_waiter(restart_thread);
    uassert_int_equal(rt_thread_startup(restart_thread), RT_EOK);
    uassert_int_equal(rt_sem_release(&mutex_delete_restart), RT_EOK);

    /* Delete owns bookkeeping; the timeout callback still owns wakeup. */
    uassert_int_equal(rt_mutex_detach(&mutex_delete_static), RT_EOK);
    rt_sched_lock(&slvl);
    suspended = rt_sched_thread_is_suspended(waiter);
    rt_sched_unlock(slvl);
    uassert_true(suspended);
    uassert_true(waiter->pending_object == RT_NULL);

    /* Make a stale mutex dereference fail deterministically. */
    rt_memset(&mutex_delete_static, 0xA5, sizeof(mutex_delete_static));

    uassert_int_equal(rt_sem_take(&mutex_delete_restart_done,
                                  rt_tick_from_millisecond(1000)),
                      RT_EOK);
    uassert_int_equal(mutex_delete_restart_result, RT_EOK);
    uassert_int_equal(rt_sem_take(&mutex_delete_done,
                                  rt_tick_from_millisecond(1000)),
                      RT_EOK);
    uassert_int_equal(mutex_delete_wait_result, -RT_ETIMEOUT);
    mutex_delete_wait_timeout = RT_WAITING_FOREVER;
}

/* Verify a completed timeout cannot leave a stale mutex reference in READY. */
static void test_mutex_timeout_ready_delete_waiter(void)
{
    rt_sched_lock_level_t slvl;
    rt_thread_t waiter;
    rt_bool_t ready;
    rt_bool_t cleaned;

    mutex_delete_wait_timeout = rt_tick_from_millisecond(20);
    mutex_delete_wait_result = -RT_ERROR;
    uassert_int_equal(rt_mutex_init(&mutex_delete_static,
                                    "rdymtx",
                                    RT_IPC_FLAG_PRIO),
                      RT_EOK);
    uassert_int_equal(rt_mutex_take(&mutex_delete_static,
                                    RT_WAITING_FOREVER),
                      RT_EOK);

    waiter = rt_thread_create("mtxwait4",
                              mutex_delete_waiter_entry,
                              &mutex_delete_static,
                              UTEST_THR_STACK_SIZE,
                              UTEST_THR_PRIORITY + 1,
                              10);
    uassert_true(waiter != RT_NULL);
    mutex_delete_bind_waiter(waiter);
    uassert_int_equal(rt_thread_startup(waiter), RT_EOK);
    uassert_int_equal(rt_sem_take(&mutex_delete_ready,
                                  RT_WAITING_FOREVER),
                      RT_EOK);
    mutex_delete_wait_until_suspended(waiter);

    /* The high-priority controller keeps the timed-out waiter from running. */
    uassert_true(mutex_delete_wait_until_timeout(waiter));
    rt_sched_lock(&slvl);
    ready = ((RT_SCHED_CTX(waiter).stat & RT_THREAD_STAT_MASK) ==
             RT_THREAD_READY);
    cleaned = ((waiter->pending_object == RT_NULL) &&
               (waiter->error == -RT_ETIMEOUT));
    rt_sched_unlock(slvl);
    uassert_true(ready);
    uassert_true(cleaned);

    uassert_int_equal(rt_mutex_detach(&mutex_delete_static), RT_EOK);
    rt_memset(&mutex_delete_static, 0xA5, sizeof(mutex_delete_static));

    uassert_int_equal(rt_sem_take(&mutex_delete_done,
                                  rt_tick_from_millisecond(1000)),
                      RT_EOK);
    uassert_int_equal(mutex_delete_wait_result, -RT_ETIMEOUT);
    mutex_delete_wait_timeout = RT_WAITING_FOREVER;
}

/* Verify a timed out head waiter does not starve later mutex waiters. */
static void test_mutex_release_timeout_waiter(void)
{
    rt_sched_lock_level_t slvl;
    rt_thread_t timeout_waiter;
    rt_thread_t next_waiter;
    rt_thread_t restart_thread;
    rt_bool_t suspended;
    rt_err_t stop_result;

    mutex_delete_wait_timeout = rt_tick_from_millisecond(1000);
    mutex_delete_wait_result = -RT_ERROR;
    mutex_delete_next_wait_result = -RT_ERROR;
    mutex_delete_restart_result = -RT_ERROR;

    uassert_int_equal(rt_mutex_init(&mutex_delete_static,
                                    "relmtx",
                                    RT_IPC_FLAG_PRIO),
                      RT_EOK);
    uassert_int_equal(rt_mutex_take(&mutex_delete_static,
                                    RT_WAITING_FOREVER),
                      RT_EOK);

    timeout_waiter = rt_thread_create("mtxwait5",
                                      mutex_delete_waiter_entry,
                                      &mutex_delete_static,
                                      UTEST_THR_STACK_SIZE,
                                      UTEST_THR_PRIORITY + 1,
                                      10);
    uassert_true(timeout_waiter != RT_NULL);
    mutex_delete_bind_waiter(timeout_waiter);
    uassert_int_equal(rt_thread_startup(timeout_waiter), RT_EOK);
    uassert_int_equal(rt_sem_take(&mutex_delete_ready,
                                  RT_WAITING_FOREVER),
                      RT_EOK);
    mutex_delete_wait_until_suspended(timeout_waiter);

    next_waiter = rt_thread_create("mtxwait6",
                                   mutex_delete_next_waiter_entry,
                                   &mutex_delete_static,
                                   UTEST_THR_STACK_SIZE,
                                   UTEST_THR_PRIORITY + 2,
                                   10);
    uassert_true(next_waiter != RT_NULL);
    mutex_delete_bind_waiter(next_waiter);
    uassert_int_equal(rt_thread_startup(next_waiter), RT_EOK);
    uassert_int_equal(rt_sem_take(&mutex_delete_ready,
                                  RT_WAITING_FOREVER),
                      RT_EOK);
    mutex_delete_wait_until_suspended(next_waiter);

    /* Stop the timer without clearing the scheduler timer ownership flag. */
    rt_sched_lock(&slvl);
    suspended = rt_sched_thread_is_suspended(timeout_waiter);
    stop_result = rt_timer_stop(&timeout_waiter->thread_timer);
    rt_sched_unlock(slvl);
    uassert_true(suspended);
    uassert_int_equal(stop_result, RT_EOK);

    restart_thread = rt_thread_create("mtxrst",
                                      mutex_delete_restart_timeout_entry,
                                      timeout_waiter,
                                      UTEST_THR_STACK_SIZE,
                                      UTEST_THR_PRIORITY + 3,
                                      10);
    uassert_true(restart_thread != RT_NULL);
    mutex_delete_bind_waiter(restart_thread);
    uassert_int_equal(rt_thread_startup(restart_thread), RT_EOK);
    uassert_int_equal(rt_sem_release(&mutex_delete_restart), RT_EOK);

    uassert_int_equal(rt_mutex_release(&mutex_delete_static), RT_EOK);
    uassert_int_equal(rt_sem_take(&mutex_delete_restart_done,
                                  rt_tick_from_millisecond(1000)),
                      RT_EOK);
    uassert_int_equal(mutex_delete_restart_result, RT_EOK);

    uassert_int_equal(rt_sem_take(&mutex_delete_done,
                                  rt_tick_from_millisecond(1000)),
                      RT_EOK);
    uassert_int_equal(rt_sem_take(&mutex_delete_done,
                                  rt_tick_from_millisecond(1000)),
                      RT_EOK);
    uassert_int_equal(mutex_delete_wait_result, -RT_ETIMEOUT);
    uassert_int_equal(mutex_delete_next_wait_result, RT_EOK);
    uassert_int_equal(rt_mutex_detach(&mutex_delete_static), RT_EOK);
    mutex_delete_wait_timeout = RT_WAITING_FOREVER;
}

#endif /* RT_USING_HEAP */

static rt_err_t utest_tc_init(void)
{
#ifdef RT_USING_HEAP
    rt_err_t result;

    dynamic_mutex = RT_NULL;
    mutex_delete_dynamic = RT_NULL;
    mutex_delete_replacement_memory = RT_NULL;
    mutex_delete_wait_timeout = RT_WAITING_FOREVER;
    mutex_delete_semaphores_initialized = RT_FALSE;

    result = rt_sem_init(&mutex_delete_ready,
                         "mtxready",
                         0,
                         RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        return result;
    }

    result = rt_sem_init(&mutex_delete_done,
                         "mtxdone",
                         0,
                         RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        rt_sem_detach(&mutex_delete_ready);
        return result;
    }

    result = rt_sem_init(&mutex_delete_restart,
                         "mtxrst",
                         0,
                         RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        rt_sem_detach(&mutex_delete_ready);
        rt_sem_detach(&mutex_delete_done);
        return result;
    }

    result = rt_sem_init(&mutex_delete_restart_done,
                         "mtxrdone",
                         0,
                         RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        rt_sem_detach(&mutex_delete_ready);
        rt_sem_detach(&mutex_delete_done);
        rt_sem_detach(&mutex_delete_restart);
        return result;
    }

    mutex_delete_semaphores_initialized = RT_TRUE;
#endif /* RT_USING_HEAP */

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
#ifdef RT_USING_HEAP
    if (mutex_delete_semaphores_initialized)
    {
        rt_sem_detach(&mutex_delete_ready);
        rt_sem_detach(&mutex_delete_done);
        rt_sem_detach(&mutex_delete_restart);
        rt_sem_detach(&mutex_delete_restart_done);
        mutex_delete_semaphores_initialized = RT_FALSE;
    }
    dynamic_mutex = RT_NULL;
#endif /* RT_USING_HEAP */

    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_static_mutex_init);
    UTEST_UNIT_RUN(test_static_mutex_take);
    UTEST_UNIT_RUN(test_static_mutex_release);
    UTEST_UNIT_RUN(test_static_mutex_trytake);
    UTEST_UNIT_RUN(test_static_pri_reverse);
#ifdef RT_USING_HEAP
    UTEST_UNIT_RUN(test_dynamic_mutex_create);
    UTEST_UNIT_RUN(test_dynamic_mutex_take);
    UTEST_UNIT_RUN(test_dynamic_mutex_release);
    UTEST_UNIT_RUN(test_dynamic_mutex_trytake);
    UTEST_UNIT_RUN(test_dynamic_pri_reverse);
    UTEST_UNIT_RUN(test_cross_thread_delete_mutex_owner);
    UTEST_UNIT_RUN(test_mutex_delete_waiter);
    UTEST_UNIT_RUN(test_mutex_timeout_delete_waiter);
    UTEST_UNIT_RUN(test_mutex_timeout_ready_delete_waiter);
    UTEST_UNIT_RUN(test_mutex_release_timeout_waiter);
#endif
    UTEST_UNIT_RUN(test_recurse_lock);
}
UTEST_TC_EXPORT(testcase, "core.mutex", utest_tc_init, utest_tc_cleanup, 1000);

/********************* end of file ************************/
