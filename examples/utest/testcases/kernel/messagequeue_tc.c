/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-28     Sherman      the first version
 */

#include <rtthread.h>
#include "utest.h"

#define MSG_SIZE    4
#define MAX_MSGS    5

static struct rt_messagequeue static_mq;
static rt_uint8_t mq_buf[(MSG_SIZE + 4) * MAX_MSGS];

static struct rt_thread mq_send_thread;
static struct rt_thread mq_recv_thread;
static rt_uint8_t mq_send_stack[512];
static rt_uint8_t mq_recv_stack[512];

static struct rt_event finish_e;
#define MQSEND_FINISH   0x01
#define MQRECV_FINIHS   0x02

#ifdef RT_USING_HEAP
static rt_mq_t dynamic_mq;
#endif /* RT_USING_HEAP */

static void test_mq_init(void)
{
    rt_err_t ret;
    ret = rt_mq_init(&static_mq,"testmq1", mq_buf, MSG_SIZE, sizeof(mq_buf), RT_IPC_FLAG_FIFO);
    uassert_true(ret == RT_EOK);
}

static void test_mq_create(void)
{
#ifdef RT_USING_HEAP
    dynamic_mq = rt_mq_create("testmq2", MSG_SIZE, MAX_MSGS, RT_IPC_FLAG_FIFO);
    uassert_true(dynamic_mq != RT_NULL);
#endif /* RT_USING_HEAP */
}

static void mq_send_case(rt_mq_t testmq)
{
    rt_uint32_t send_buf[MAX_MSGS+1] = {0};
    rt_err_t ret = RT_EOK;

    for (int var = 0; var < MAX_MSGS; ++var)
    {
        send_buf[var] = var + 1;
        ret = rt_mq_send_wait(testmq, &send_buf[var], sizeof(send_buf[0]), RT_WAITING_FOREVER);
        uassert_true(ret == RT_EOK);
    }
    send_buf[MAX_MSGS] = MAX_MSGS + 1;
    ret = rt_mq_send(testmq, &send_buf[MAX_MSGS], sizeof(send_buf[0]));
    uassert_true(ret == -RT_EFULL);

    ret = rt_mq_send_wait(testmq, &send_buf[MAX_MSGS], sizeof(send_buf[0]), RT_WAITING_FOREVER);
    uassert_true(ret == RT_EOK);

    while (testmq->entry != 0)
    {
        rt_thread_delay(100);
    }

    ret = rt_mq_send(testmq, &send_buf[1], sizeof(send_buf[0]));
    uassert_true(ret == RT_EOK);

    ret = rt_mq_send(testmq, &send_buf[2], sizeof(send_buf[0]));
    uassert_true(ret == RT_EOK);

    ret = rt_mq_urgent(testmq, &send_buf[0], sizeof(send_buf[0]));
    uassert_true(ret == RT_EOK);

    while (testmq->entry != 0)
    {
        rt_thread_delay(100);
    }

    ret = rt_mq_send(testmq, &send_buf[1], sizeof(send_buf[0]));
    uassert_true(ret == RT_EOK);
    ret = rt_mq_control(testmq, RT_IPC_CMD_RESET, RT_NULL);
    uassert_true(ret == RT_EOK);
    uassert_true(testmq->entry == 0);
}

static void mq_send_entry(void *param)
{
    mq_send_case(&static_mq);

#ifdef RT_USING_HEAP
    if(dynamic_mq != RT_NULL)
    {
        mq_send_case(dynamic_mq);
    }
#endif /* RT_USING_HEAP */

    rt_event_send(&finish_e, MQSEND_FINISH);
}

static void mq_recv_case(rt_mq_t testmq)
{
    rt_uint32_t recv_buf[MAX_MSGS+1] = {0};
    rt_err_t ret = RT_EOK;

    for (int var = 0; var < MAX_MSGS + 1; ++var)
    {
        ret = rt_mq_recv(testmq, &recv_buf[var], sizeof(recv_buf[0]), RT_WAITING_FOREVER);
        uassert_true(ret == RT_EOK);
        uassert_true(recv_buf[var] == (var + 1));
    }

    for (int var = 0; var < 3; ++var)
    {
        ret = rt_mq_recv(testmq, &recv_buf[var], sizeof(recv_buf[0]), RT_WAITING_FOREVER);
        uassert_true(ret == RT_EOK);
        uassert_true(recv_buf[var] == (var + 1));
    }
}

static void mq_recv_entry(void *param)
{
    mq_recv_case(&static_mq);

#ifdef RT_USING_HEAP
    if(dynamic_mq != RT_NULL)
    {
        mq_recv_case(dynamic_mq);
    }
#endif /* RT_USING_HEAP */
    rt_event_send(&finish_e, MQRECV_FINIHS);
}

static void test_mq_testcase(void)
{
    rt_thread_startup(&mq_send_thread);
    rt_thread_startup(&mq_recv_thread);

    rt_event_recv(&finish_e, MQSEND_FINISH | MQRECV_FINIHS, RT_EVENT_FLAG_AND, RT_WAITING_FOREVER, RT_NULL);
}

static void test_mq_detach(void)
{
    rt_err_t ret = rt_mq_detach(&static_mq);
    uassert_true(ret == RT_EOK);
}

static void test_mq_delete(void)
{
#ifdef RT_USING_HEAP
    rt_err_t ret = rt_mq_delete(dynamic_mq);
    uassert_true(ret == RT_EOK);
#endif /* RT_USING_HEAP */
}

static rt_err_t utest_tc_init(void)
{
    rt_err_t ret ;
    ret = rt_thread_init(&mq_send_thread, "mq_send", mq_send_entry, RT_NULL, mq_send_stack, sizeof(mq_send_stack), 22, 20);
    if(ret != RT_EOK)
        return -RT_ERROR;

    ret = rt_thread_init(&mq_recv_thread, "mq_recv", mq_recv_entry, RT_NULL, mq_recv_stack, sizeof(mq_recv_stack), 23, 20);
    if(ret != RT_EOK)
        return -RT_ERROR;

    ret = rt_event_init(&finish_e, "finish", RT_IPC_FLAG_FIFO);
    if(ret != RT_EOK)
            return -RT_ERROR;

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_mq_init);
    UTEST_UNIT_RUN(test_mq_create);
    UTEST_UNIT_RUN(test_mq_testcase);
    UTEST_UNIT_RUN(test_mq_detach);
    UTEST_UNIT_RUN(test_mq_delete);
}
UTEST_TC_EXPORT(testcase, "testcases.kernel.messagequeue_tc", utest_tc_init, utest_tc_cleanup, 1000);
