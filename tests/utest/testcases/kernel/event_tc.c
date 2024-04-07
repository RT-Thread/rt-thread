/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-15     liukang     the first version
 * 2023-09-15     xqyjlj       change stack size in cpu64
 */

#include <rtthread.h>
#include "utest.h"
#include <stdlib.h>

#define THREAD_STACKSIZE UTEST_THR_STACK_SIZE
#define EVENT_FLAG3 (1 << 3)
#define EVENT_FLAG5 (1 << 5)

static struct rt_event static_event = {0};
#ifdef RT_USING_HEAP
static rt_event_t dynamic_event = RT_NULL;
static rt_uint32_t dynamic_event_recv_thread_finish = 0, dynamic_event_send_thread_finish = 0;

rt_align(RT_ALIGN_SIZE)
static char thread3_stack[UTEST_THR_STACK_SIZE];
static struct rt_thread thread3;

rt_align(RT_ALIGN_SIZE)
static char thread4_stack[UTEST_THR_STACK_SIZE];
static struct rt_thread thread4;
#endif /* RT_USING_HEAP */

static rt_uint32_t recv_event_times1 = 0, recv_event_times2 = 0;
static rt_uint32_t static_event_recv_thread_finish = 0, static_event_send_thread_finish = 0;

rt_align(RT_ALIGN_SIZE)
static char thread1_stack[UTEST_THR_STACK_SIZE];
static struct rt_thread thread1;

rt_align(RT_ALIGN_SIZE)
static char thread2_stack[UTEST_THR_STACK_SIZE];
static struct rt_thread thread2;

#define THREAD_PRIORITY      9
#define THREAD_TIMESLICE     5

static void test_event_init(void)
{
    rt_err_t result;

    result = rt_event_init(&static_event, "event", RT_IPC_FLAG_PRIO);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }
    result = rt_event_detach(&static_event);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }

    result = rt_event_init(&static_event, "event", RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }
    result = rt_event_detach(&static_event);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }

    uassert_true(1);
}

static void test_event_detach(void)
{
    rt_err_t result = RT_EOK;

    result = rt_event_init(&static_event, "event", RT_IPC_FLAG_PRIO);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }

    result = rt_event_detach(&static_event);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }

    uassert_true(1);
}

static void thread1_recv_static_event(void *param)
{
    rt_uint32_t e;

    if (rt_event_recv(&static_event, (EVENT_FLAG3 | EVENT_FLAG5),
                      RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                      RT_WAITING_FOREVER, &e) != RT_EOK)
    {
        return;
    }

    recv_event_times1 = e;

    rt_thread_mdelay(50);

    if (rt_event_recv(&static_event, (EVENT_FLAG3 | EVENT_FLAG5),
                      RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                      RT_WAITING_FOREVER, &e) != RT_EOK)
    {
        return;
    }
    recv_event_times2 = e;

    static_event_recv_thread_finish = 1;
}

static void thread2_send_static_event(void *param)
{
    rt_event_send(&static_event, EVENT_FLAG3);
    rt_thread_mdelay(10);

    rt_event_send(&static_event, EVENT_FLAG5);
    rt_thread_mdelay(10);

    rt_event_send(&static_event, EVENT_FLAG3);

    static_event_send_thread_finish = 1;
}


static void test_static_event_send_recv(void)
{
    rt_err_t result = RT_EOK;

    result  = rt_event_init(&static_event, "event", RT_IPC_FLAG_PRIO);
    if (result  != RT_EOK)
    {
        uassert_false(1);
    }

    rt_thread_init(&thread1,
                   "thread1",
                   thread1_recv_static_event,
                   RT_NULL,
                   &thread1_stack[0],
                   sizeof(thread1_stack),
                   THREAD_PRIORITY - 1, THREAD_TIMESLICE);
    rt_thread_startup(&thread1);

    rt_thread_init(&thread2,
                   "thread2",
                   thread2_send_static_event,
                   RT_NULL,
                   &thread2_stack[0],
                   sizeof(thread2_stack),
                   THREAD_PRIORITY, THREAD_TIMESLICE);
    rt_thread_startup(&thread2);

    while (static_event_recv_thread_finish != 1 || static_event_send_thread_finish != 1)
    {
        rt_thread_delay(1);
    }

    if (recv_event_times1 == EVENT_FLAG3 && recv_event_times2 == (EVENT_FLAG3 | EVENT_FLAG5))
    {
        if (rt_event_detach(&static_event) != RT_EOK)
        {
            uassert_false(1);
        }
        uassert_true(1);
    }
    else
    {
        if (rt_event_detach(&static_event) != RT_EOK)
        {
            uassert_false(1);
        }
        uassert_false(1);
    }

    return;
}

#ifdef RT_USING_HEAP
static void test_event_create(void)
{
    rt_err_t result = RT_EOK;

    dynamic_event = rt_event_create("dynamic_event", RT_IPC_FLAG_FIFO);
    if (dynamic_event == RT_NULL)
    {
        uassert_false(1);
    }

    result = rt_event_delete(dynamic_event);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }

    uassert_true(1);
}

static void test_event_delete(void)
{
    rt_err_t result;

    dynamic_event = rt_event_create("dynamic_event", RT_IPC_FLAG_FIFO);
    if (dynamic_event == RT_NULL)
    {
        uassert_false(1);
    }

    result = rt_event_delete(dynamic_event);
    if (result != RT_EOK)
    {
        uassert_false(1);
    }

    uassert_true(1);
}

static void thread3_recv_dynamic_event(void *param)
{
    rt_uint32_t e;

    if (rt_event_recv(dynamic_event, (EVENT_FLAG3 | EVENT_FLAG5),
                      RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                      RT_WAITING_FOREVER, &e) != RT_EOK)
    {
        return;
    }

    recv_event_times1 = e;

    rt_thread_mdelay(50);

    if (rt_event_recv(dynamic_event, (EVENT_FLAG3 | EVENT_FLAG5),
                      RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                      RT_WAITING_FOREVER, &e) != RT_EOK)
    {
        return;
    }
    recv_event_times2 = e;

    dynamic_event_recv_thread_finish = 1;
}

static void thread4_send_dynamic_event(void *param)
{
    rt_event_send(dynamic_event, EVENT_FLAG3);
    rt_thread_mdelay(10);

    rt_event_send(dynamic_event, EVENT_FLAG5);
    rt_thread_mdelay(10);

    rt_event_send(dynamic_event, EVENT_FLAG3);

    dynamic_event_send_thread_finish = 1;
}

static void test_dynamic_event_send_recv(void)
{
    dynamic_event = rt_event_create("dynamic_event", RT_IPC_FLAG_PRIO);
    if (dynamic_event == RT_NULL)
    {
        uassert_false(1);
    }

    rt_thread_init(&thread3,
                   "thread3",
                   thread3_recv_dynamic_event,
                   RT_NULL,
                   &thread3_stack[0],
                   sizeof(thread3_stack),
                   THREAD_PRIORITY - 1, THREAD_TIMESLICE);
    rt_thread_startup(&thread3);

    rt_thread_init(&thread4,
                   "thread4",
                   thread4_send_dynamic_event,
                   RT_NULL,
                   &thread4_stack[0],
                   sizeof(thread4_stack),
                   THREAD_PRIORITY, THREAD_TIMESLICE);
    rt_thread_startup(&thread4);

    while (dynamic_event_recv_thread_finish != 1 || dynamic_event_send_thread_finish != 1)
    {
        rt_thread_delay(1);
    }

    if (recv_event_times1 == EVENT_FLAG3 && recv_event_times2 == (EVENT_FLAG3 | EVENT_FLAG5))
    {
        if (rt_event_delete(dynamic_event) != RT_EOK)
        {
            uassert_false(1);
        }
        uassert_true(1);
    }
    else
    {
        if (rt_event_delete(dynamic_event) != RT_EOK)
        {
            uassert_false(1);
        }
        uassert_false(1);
    }

    return;
}
#endif

static rt_err_t utest_tc_init(void)
{
    static_event_recv_thread_finish = 0;
    static_event_send_thread_finish = 0;
#ifdef RT_USING_HEAP
    dynamic_event_recv_thread_finish = 0;
    dynamic_event_send_thread_finish = 0;
#endif
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_event_init);
    UTEST_UNIT_RUN(test_event_detach);
    UTEST_UNIT_RUN(test_static_event_send_recv);
#ifdef RT_USING_HEAP
    UTEST_UNIT_RUN(test_event_create);
    UTEST_UNIT_RUN(test_event_delete);
    UTEST_UNIT_RUN(test_dynamic_event_send_recv);
#endif
}
UTEST_TC_EXPORT(testcase, "src.ipc.event_tc", utest_tc_init, utest_tc_cleanup, 60);
