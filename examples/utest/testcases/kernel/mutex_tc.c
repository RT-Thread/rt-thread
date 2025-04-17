/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09.01     luckyzjq     the first version
 * 2023-09-15     xqyjlj       change stack size in cpu64
 */
#define __RT_IPC_SOURCE__

#include <rtthread.h>
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

static rt_err_t utest_tc_init(void)
{
#ifdef RT_USING_HEAP
    dynamic_mutex = RT_NULL;
#endif /* RT_USING_HEAP */

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
#ifdef RT_USING_HEAP
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
#endif
    UTEST_UNIT_RUN(test_recurse_lock);
}
UTEST_TC_EXPORT(testcase, "testcases.kernel.mutex_tc", utest_tc_init, utest_tc_cleanup, 1000);

/********************* end of file ************************/
