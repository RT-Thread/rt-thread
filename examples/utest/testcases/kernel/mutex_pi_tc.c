/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
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

#define MUTEX_NUM 3
#define THREAD_NUM 5

static struct rt_mutex _mutex[MUTEX_NUM];
static volatile int _sync_flag;

static void test_thread_entry(void *para)
{
    while (!_sync_flag)
    {
        rt_thread_delay(1);
    }

    rt_ubase_t thread_id = (rt_ubase_t)para;
    rt_err_t ret;
    rt_thread_mdelay(50 + thread_id * 100);
    ret = rt_mutex_take(&_mutex[thread_id % MUTEX_NUM], RT_WAITING_FOREVER);
    uassert_true(ret == RT_EOK);
    uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == RT_SCHED_PRIV(rt_thread_self()).init_priority);

    if (thread_id == 1)
    {
        rt_thread_mdelay(100); // wait for main thread re-get _mutex[1]
        uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == 8);
    }

    ret = rt_mutex_release(&_mutex[thread_id % MUTEX_NUM]);
    uassert_true(ret == RT_EOK);
    uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == RT_SCHED_PRIV(rt_thread_self()).init_priority);

    _sync_flag ++;
}

static void test_main_thread_entry(void *para)
{
    while (!_sync_flag)
    {
        rt_thread_delay(1);
    }

    rt_err_t ret;

    ret = rt_mutex_take(&_mutex[0], RT_WAITING_FOREVER);
    uassert_true(ret == RT_EOK);
    uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == 12);
    rt_thread_mdelay(100);         // wait for t0 take mutex0
    uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == 12);

    ret = rt_mutex_take(&_mutex[1], RT_WAITING_FOREVER);
    uassert_true(ret == RT_EOK);
    uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == 12);
    rt_thread_mdelay(100);         // wait for t1 take mutex1
    uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == 9);

    ret = rt_mutex_take(&_mutex[2], RT_WAITING_FOREVER);
    uassert_true(ret == RT_EOK);
    uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == 9);
    rt_thread_mdelay(100);         // wait for t2 take mutex2
    uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == 8);

    rt_thread_mdelay(100);         // wait for t3 take mutex0
    uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == 7);

    rt_thread_mdelay(100);         // wait for t4 take mutex1
    uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == 7);

    rt_thread_mdelay(100);
    rt_mutex_release(&_mutex[0]);   // give _mutex0 to t3
    uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == 8);

    rt_thread_mdelay(100);
    rt_mutex_release(&_mutex[1]);   // give _mutex1 to t1
    uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == 8);

    rt_thread_mdelay(50);
    rt_mutex_take(&_mutex[1], RT_WAITING_FOREVER);   // re-get _mutex1, which is hold by t1
    uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == 8);
    rt_mutex_release(&_mutex[1]);   // give _mutex1 to thread t1
    uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == 8);

    rt_thread_mdelay(100);
    rt_mutex_release(&_mutex[2]);
    uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == 12);

    _sync_flag ++;
}

static void test_mutex_pi(void)
{
    rt_thread_t t_main;
    rt_thread_t t[THREAD_NUM];
    rt_uint8_t prio[THREAD_NUM] = {13, 9, 8, 7, 11}; // prio of threads

    for (int i = 0; i < MUTEX_NUM; i++)
    {
        rt_mutex_init(&_mutex[i], "test1", 0);
    }

    _sync_flag  = 0;

    t_main = rt_thread_create("t_main", test_main_thread_entry, RT_NULL, THREAD_STACKSIZE, 12, 10000);
    uassert_true(t_main != RT_NULL);
    rt_thread_startup(t_main);

    for (rt_ubase_t i = 0; i < THREAD_NUM; i++)
    {
        t[i] = rt_thread_create("t", test_thread_entry, (void *)i, THREAD_STACKSIZE, prio[i], 10000);
        uassert_true(t[i] != RT_NULL);
        rt_thread_startup(t[i]);
    }

    _sync_flag = 1;

    while (_sync_flag != THREAD_NUM + 1 + 1)
    {
        rt_thread_mdelay(100);
    }

    for (int i = 0; i < MUTEX_NUM; i++)
    {
        rt_mutex_detach(&_mutex[i]);
    }
}

static struct rt_mutex _timeout_mutex;

static void test_main_timeout_entry(void *para)
{
    rt_err_t ret;

    ret = rt_mutex_take(&_timeout_mutex, RT_WAITING_FOREVER);
    uassert_true(ret == -RT_EOK);
    rt_thread_mdelay(100);
    uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == 10);
    rt_thread_mdelay(100);
    uassert_true(RT_SCHED_PRIV(rt_thread_self()).current_priority == 12);
    rt_mutex_release(&_timeout_mutex);
    _sync_flag ++;
}

static void test_timeout_entry(void *para)
{
    rt_err_t ret;

    rt_thread_mdelay(50);
    ret = rt_mutex_take(&_timeout_mutex, rt_tick_from_millisecond(100));
    uassert_true(ret == -RT_ETIMEOUT);
    _sync_flag ++;
}

static void test_mutex_pi_timeout(void)
{
    _sync_flag = 0;

    rt_mutex_init(&_timeout_mutex, "_timeout_mutex", 0);

    rt_thread_t t1 = rt_thread_create("t1", test_main_timeout_entry, RT_NULL, THREAD_STACKSIZE, 12, 10000);
    uassert_true(t1 != RT_NULL);
    rt_thread_startup(t1);

    rt_thread_t t2 = rt_thread_create("t2", test_timeout_entry, (void *)t1, THREAD_STACKSIZE, 10, 10000);
    uassert_true(t2 != RT_NULL);
    rt_thread_startup(t2);

    while (_sync_flag != 2)
    {
        rt_thread_mdelay(100);
    }

    rt_mutex_detach(&_timeout_mutex);
}

#define TC_THREAD_NUM 4
#define TC_MUTEX_NUM TC_THREAD_NUM
static rt_thread_t t[TC_THREAD_NUM], t_hi_prio;
static struct rt_mutex m[TC_MUTEX_NUM];

static void test_recursive_mutex_depend_entry(void *para)
{
    rt_ubase_t id = (rt_ubase_t)para;

    rt_mutex_take(&m[id], RT_WAITING_FOREVER);

    rt_thread_mdelay(50);

    if (id != 0)
    {
        rt_mutex_take(&m[id - 1], RT_WAITING_FOREVER);
    }

    if (id == 0)
    {
        rt_thread_mdelay(250);
        rt_mutex_release(&m[id]);
    }
    else
    {
        rt_mutex_release(&m[id - 1]);
        rt_mutex_release(&m[id]);
    }
    _sync_flag ++;
}

static void test_recursive_mutex_depend_hi_pri_entry(void *para)
{
    rt_thread_mdelay(100);
    rt_err_t err = rt_mutex_take(&m[TC_MUTEX_NUM - 1], rt_tick_from_millisecond(100));
    uassert_true(err == -RT_ETIMEOUT);
    _sync_flag ++;
}

static void test_mutex_pi_recursive_prio_update(void)
{
    _sync_flag = 0;

    for (int i = 0; i < TC_MUTEX_NUM; i++)
    {
        rt_mutex_init(&m[i], "test", 0);
    }

    for (rt_ubase_t i = 0; i < TC_THREAD_NUM; i++)
    {
        t[i] = rt_thread_create("t", test_recursive_mutex_depend_entry, (void *)i, THREAD_STACKSIZE, 10, 10000);
        rt_thread_startup(t[i]);
    }
    t_hi_prio = rt_thread_create("t", test_recursive_mutex_depend_hi_pri_entry, (void *)RT_NULL, THREAD_STACKSIZE, 3, 10000);
    rt_thread_startup(t_hi_prio);

    rt_thread_mdelay(150);

    for (int i = 0; i < TC_THREAD_NUM; i++)
    {
        uassert_true(RT_SCHED_PRIV(t[i]).current_priority == 3);
    }

    rt_thread_mdelay(100);

    for (int i = 0; i < TC_THREAD_NUM; i++)
    {
        uassert_true(RT_SCHED_PRIV(t[i]).current_priority == 10);
    }

    while (_sync_flag != TC_THREAD_NUM + 1)
    {
        rt_thread_mdelay(100);
    }

    for (int i = 0; i < TC_MUTEX_NUM; i++)
    {
        rt_mutex_detach(&m[i]);
    }
    _sync_flag ++;
}

static void test_mutex_waiter_to_wakeup_entry(void *para)
{
    rt_thread_mdelay(100);
    rt_err_t err = rt_mutex_take(&m[TC_MUTEX_NUM - 1], RT_WAITING_FOREVER);
    uassert_true(err == -RT_EINTR);
    _sync_flag ++;
}

static void wakeup_func(void *para)
{
    rt_thread_resume(t_hi_prio);
}
static void test_mutex_pi_wakeup_mutex_waiter(void)
{
    struct rt_timer wakeup_timer;

    _sync_flag = 0;

    for (int i = 0; i < TC_MUTEX_NUM; i++)
    {
        rt_mutex_init(&m[i], "test", 0);
    }

    for (rt_ubase_t i = 0; i < TC_THREAD_NUM; i++)
    {
        t[i] = rt_thread_create("t", test_recursive_mutex_depend_entry, (void *)i, THREAD_STACKSIZE, 10, 10000);
        rt_thread_startup(t[i]);
    }
    t_hi_prio = rt_thread_create("t", test_mutex_waiter_to_wakeup_entry, (void *)RT_NULL, THREAD_STACKSIZE, 3, 10000);
    rt_thread_startup(t_hi_prio);

    rt_timer_init(&wakeup_timer, "wakeup_timer", wakeup_func, RT_NULL, rt_tick_from_millisecond(200), RT_TIMER_FLAG_ONE_SHOT);
    rt_timer_start(&wakeup_timer);
    rt_thread_mdelay(150);

    for (int i = 0; i < TC_THREAD_NUM; i++)
    {
        uassert_true(RT_SCHED_PRIV(t[i]).current_priority == 3);
    }

    rt_thread_mdelay(100);

    for (int i = 0; i < TC_THREAD_NUM; i++)
    {
        uassert_true(RT_SCHED_PRIV(t[i]).current_priority == 10);
    }

    while (_sync_flag != TC_THREAD_NUM + 1)
    {
        rt_thread_mdelay(100);
    }

    for (int i = 0; i < TC_MUTEX_NUM; i++)
    {
        rt_mutex_detach(&m[i]);
    }
    rt_timer_detach(&wakeup_timer);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_mutex_pi);
    UTEST_UNIT_RUN(test_mutex_pi_recursive_prio_update);
    UTEST_UNIT_RUN(test_mutex_pi_timeout);
    UTEST_UNIT_RUN(test_mutex_pi_wakeup_mutex_waiter);
}
UTEST_TC_EXPORT(testcase, "testcases.kernel.mutex_pi_tc", utest_tc_init, utest_tc_cleanup, 1000);

/********************* end of file ************************/
