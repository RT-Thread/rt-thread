/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-08     liukang     the first version
 */

#include <rtthread.h>
#include "utest.h"
#include <stdlib.h>

static struct rt_mailbox test_static_mb;
static char mb_pool[128];

static rt_mailbox_t test_dynamic_mb;

static uint8_t static_mb_recv_thread_finish, static_mb_send_thread_finish;
static uint8_t dynamic_mb_recv_thread_finish, dynamic_mb_send_thread_finish;

ALIGN(RT_ALIGN_SIZE)
static char thread1_stack[1024];
static struct rt_thread thread1;

ALIGN(RT_ALIGN_SIZE)
static char thread2_stack[1024];
static struct rt_thread thread2;

#define THREAD_PRIORITY      9
#define THREAD_TIMESLICE     5

static rt_thread_t mb_send = RT_NULL;
static rt_thread_t mb_recv = RT_NULL;

static rt_uint8_t mb_send_str1[] = "this is first mail!";
static rt_uint8_t mb_send_str2[] = "this is second mail!";
static rt_uint8_t mb_send_str3[] = "this is thirdy mail!";

static rt_uint8_t *mb_recv_str1;
static rt_uint8_t *mb_recv_str2;
static rt_uint8_t *mb_recv_str3;

static void test_mailbox_init(void)
{
    rt_err_t result;

    result = rt_mb_init(&test_static_mb, "mbt", &mb_pool[0], sizeof(mb_pool) / 4, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }
    result = rt_mb_detach(&test_static_mb);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }

    result = rt_mb_init(&test_static_mb, "mbt", &mb_pool[0], sizeof(mb_pool) / 4, RT_IPC_FLAG_PRIO);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }

    result = rt_mb_detach(&test_static_mb);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }

    uassert_true(1);
}

static void test_mailbox_deatch(void)
{
    rt_err_t result;

    result = rt_mb_init(&test_static_mb, "mbt", &mb_pool[0], sizeof(mb_pool) / 4, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }
    result = rt_mb_detach(&test_static_mb);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }

    result = rt_mb_init(&test_static_mb, "mbt", &mb_pool[0], sizeof(mb_pool) / 4, RT_IPC_FLAG_PRIO);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }
    result = rt_mb_detach(&test_static_mb);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }

    uassert_true(1);
}

static void test_mailbox_create(void)
{
    rt_err_t result;

    test_dynamic_mb = rt_mb_create("test_dynamic_mb", sizeof(mb_pool) / 4, RT_IPC_FLAG_FIFO);
    if (test_dynamic_mb == RT_NULL)
    {
        uassert_false(1);
    }
    result = rt_mb_delete(test_dynamic_mb);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }

    test_dynamic_mb = rt_mb_create("test_dynamic_mb", sizeof(mb_pool) / 4, RT_IPC_FLAG_PRIO);
    if (test_dynamic_mb == RT_NULL)
    {
        uassert_false(1);
    }
    result = rt_mb_delete(test_dynamic_mb);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }

    uassert_true(1);
}

static void test_mailbox_delete(void)
{
    rt_err_t result;

    test_dynamic_mb = rt_mb_create("test_dynamic_mb", sizeof(mb_pool) / 4, RT_IPC_FLAG_FIFO);
    if (test_dynamic_mb == RT_NULL)
    {
        uassert_false(1);
    }
    result = rt_mb_delete(test_dynamic_mb);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }

    test_dynamic_mb = rt_mb_create("test_dynamic_mb", sizeof(mb_pool) / 4, RT_IPC_FLAG_PRIO);
    if (test_dynamic_mb == RT_NULL)
    {
        uassert_false(1);
    }
    result = rt_mb_delete(test_dynamic_mb);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }

    uassert_true(1);
}

static void thread2_send_static_mb(void *arg)
{
    rt_err_t res = RT_EOK;

    res = rt_mb_send(&test_static_mb, (rt_ubase_t)&mb_send_str1);
    if (res != RT_EOK)
    {
        uassert_false(1);
    }
    rt_thread_mdelay(100);

    res = rt_mb_send_wait(&test_static_mb, (rt_ubase_t)&mb_send_str2, 10);
    if (res != RT_EOK)
    {
        uassert_false(1);
    }
    rt_thread_mdelay(100);

    res = rt_mb_urgent(&test_static_mb, (rt_ubase_t)&mb_send_str3);
    if (res != RT_EOK)
    {
        uassert_false(1);
    }

    static_mb_send_thread_finish = 1;
}

static void thread1_recv_static_mb(void *arg)
{
    rt_err_t result = RT_EOK;

    result = rt_mb_recv(&test_static_mb, (rt_ubase_t *)&mb_recv_str1, RT_WAITING_FOREVER);
    if (result != RT_EOK || strcmp(mb_recv_str1, mb_send_str1) != 0)
    {
        uassert_false(1);
    }

    result = rt_mb_recv(&test_static_mb, (rt_ubase_t *)&mb_recv_str2, RT_WAITING_FOREVER);
    if (result != RT_EOK || strcmp(mb_recv_str2, mb_send_str2) != 0)
    {
        uassert_false(1);
    }

    result = rt_mb_recv(&test_static_mb, (rt_ubase_t *)&mb_recv_str3, RT_WAITING_FOREVER);
    if (result != RT_EOK || strcmp(mb_recv_str3, mb_send_str3) != 0)
    {
        uassert_false(1);
    }

    static_mb_recv_thread_finish = 1;
}

static void test_static_mailbox_send_recv(void)
{
    rt_err_t result;

    result = rt_mb_init(&test_static_mb, "mbt", &mb_pool[0], sizeof(mb_pool) / 4, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }

    rt_thread_init(&thread1,
                   "thread1",
                   thread1_recv_static_mb,
                   RT_NULL,
                   &thread1_stack[0],
                   sizeof(thread1_stack),
                   THREAD_PRIORITY - 1, THREAD_TIMESLICE);
    rt_thread_startup(&thread1);

    rt_thread_init(&thread2,
                   "thread2",
                   thread2_send_static_mb,
                   RT_NULL,
                   &thread2_stack[0],
                   sizeof(thread2_stack),
                   THREAD_PRIORITY, THREAD_TIMESLICE);
    rt_thread_startup(&thread2);

    while (static_mb_recv_thread_finish != 1 || static_mb_send_thread_finish != 1)
    {
        rt_thread_delay(1);
    }

    if (rt_mb_detach(&test_static_mb) != RT_EOK)
    {
        uassert_false(1);
    }

    uassert_true(1);
}

static void thread4_send_dynamic_mb(void *arg)
{
    rt_err_t res = RT_EOK;

    res = rt_mb_send(test_dynamic_mb, (rt_ubase_t)&mb_send_str1);
    if (res != RT_EOK)
    {
        uassert_false(1);
    }
    rt_thread_mdelay(100);

    res = rt_mb_send_wait(test_dynamic_mb, (rt_ubase_t)&mb_send_str2, 10);
    if (res != RT_EOK)
    {
        uassert_false(1);
    }
    rt_thread_mdelay(100);

    res = rt_mb_urgent(test_dynamic_mb, (rt_ubase_t)&mb_send_str3);
    if (res != RT_EOK)
    {
        uassert_false(1);
    }

    dynamic_mb_send_thread_finish = 1;
}

static void thread3_recv_dynamic_mb(void *arg)
{
    rt_err_t result = RT_EOK;

    result = rt_mb_recv(test_dynamic_mb, (rt_ubase_t *)&mb_recv_str1, RT_WAITING_FOREVER);
    if (result != RT_EOK || strcmp(mb_recv_str1, mb_send_str1) != 0)
    {
        uassert_false(1);
    }

    result = rt_mb_recv(test_dynamic_mb, (rt_ubase_t *)&mb_recv_str2, RT_WAITING_FOREVER);
    if (result != RT_EOK || strcmp(mb_recv_str2, mb_send_str2) != 0)
    {
        uassert_false(1);
    }

    result = rt_mb_recv(test_dynamic_mb, (rt_ubase_t *)&mb_recv_str3, RT_WAITING_FOREVER);
    if (result != RT_EOK || strcmp(mb_recv_str3, mb_send_str3) != 0)
    {
        uassert_false(1);
    }

    dynamic_mb_recv_thread_finish = 1;
}

static void test_dynamic_mailbox_send_recv(void)
{
    test_dynamic_mb = rt_mb_create("mbt", sizeof(mb_pool) / 4, RT_IPC_FLAG_FIFO);
    if (test_dynamic_mb == RT_NULL)
    {
        uassert_false(1);
    }

    mb_recv = rt_thread_create("mb_recv_thread",
                                thread3_recv_dynamic_mb,
                                RT_NULL,
                                1024,
                                THREAD_PRIORITY - 1,
                                THREAD_TIMESLICE);
    if (mb_recv == RT_NULL)
    {
        uassert_false(1);
    }
    rt_thread_startup(mb_recv);

    mb_send = rt_thread_create("mb_send_thread",
                                thread4_send_dynamic_mb,
                                RT_NULL,
                                1024,
                                THREAD_PRIORITY - 1,
                                THREAD_TIMESLICE);
    if (mb_send == RT_NULL)
    {
        uassert_false(1);
    }
    rt_thread_startup(mb_send);

    while (dynamic_mb_recv_thread_finish != 1 || dynamic_mb_send_thread_finish != 1)
    {
        rt_thread_delay(1);
    }

    if (rt_mb_delete(test_dynamic_mb) != RT_EOK)
    {
        uassert_false(1);
    }

    uassert_true(1);
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
    UTEST_UNIT_RUN(test_mailbox_init);
    UTEST_UNIT_RUN(test_mailbox_deatch);
    UTEST_UNIT_RUN(test_mailbox_create);
    UTEST_UNIT_RUN(test_mailbox_delete);
    UTEST_UNIT_RUN(test_static_mailbox_send_recv);
    UTEST_UNIT_RUN(test_dynamic_mailbox_send_recv);
}
UTEST_TC_EXPORT(testcase, "src.ipc.mailbox_tc", utest_tc_init, utest_tc_cleanup, 60);
