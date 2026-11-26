/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-28     Sherman      the first version
 * 2023-09-15     xqyjlj       change stack size in cpu64
 *                             fix in smp
 * 2025-11-17     Ze-Hou       add standardized utest documentation block
 */

/**
 * Test Case Name: Kernel Core Message Queue Test
 *
 * Test Objectives:
 * - Validate the RT-Thread kernel message queue (rt_messagequeue) functionality
 * - Test static and dynamic message queue creation, initialization, sending,
 *   receiving, urgent send, priority send, reset, detach, and delete APIs
 *
 * Test Scenarios:
 * - Initialize a static message queue and verify correct setup
 * - Create a dynamic message queue and verify allocation
 * - Send messages to the queue until full, test blocking and non-blocking send,
 *   urgent send, and priority send (if enabled)
 * - Receive messages from the queue, verify order and data integrity, including
 *   priority receive (if enabled)
 * - Reset the message queue and verify it is empty
 * - Detach and delete message queues, ensuring resources are released
 * - Use multiple threads to simulate concurrent send/receive operations
 * - When message priority is enabled, verify an urgent handoff is not overtaken
 *   by a higher priority message queued before the receiver runs, and that a
 *   detached receiver hands an in-flight urgent handoff back to the queue
 *
 * Verification Metrics:
 * - All uassert assertions pass without failure
 * - Message queues are created, initialized, detached, and deleted successfully
 * - Messages are sent and received in correct order and with correct data
 * - Blocking and non-blocking operations behave as expected
 * - Urgent and priority send/receive functions work correctly (if enabled)
 *
 * Dependencies:
 * - Enable message queue priority (RT-Thread Kernel -> Inter-Thread communication
 *   -> Enable message queue priority)
 * - Enable Message Queue Test (RT-Thread Utestcases -> Kernel Core -> Message Queue Test)
 * - Test on any RT-Thread supported platform (e.g., qemu-virt64-riscv)
 *
 * Expected Results:
 * - After executing this test in msh, the expected output should be:
 *   "[  PASSED  ] [ result   ] testcase (core.messagequeue)"
 */

#include <rtthread.h>
#include "utest.h"

#define THREAD_STACKSIZE UTEST_THR_STACK_SIZE

#define MSG_SIZE 4
#define MAX_MSGS 5

static struct rt_messagequeue static_mq;
static rt_uint8_t mq_buf[RT_MQ_BUF_SIZE(MSG_SIZE, MAX_MSGS)];

static struct rt_thread mq_send_thread;
static struct rt_thread mq_recv_thread;
static rt_uint8_t mq_send_stack[UTEST_THR_STACK_SIZE];
static rt_uint8_t mq_recv_stack[UTEST_THR_STACK_SIZE];

static struct rt_event finish_e;
#define MQSEND_FINISH 0x01
#define MQRECV_FINIHS 0x02

#ifdef RT_USING_HEAP
static rt_mq_t dynamic_mq;
#endif /* RT_USING_HEAP */

static void test_mq_init(void)
{
    rt_err_t ret;
    ret = rt_mq_init(&static_mq, "testmq1", mq_buf, MSG_SIZE, sizeof(mq_buf), RT_IPC_FLAG_FIFO);
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
    rt_uint32_t send_buf[MAX_MSGS + 1] = { 0 };
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

#ifdef RT_USING_MESSAGEQUEUE_PRIORITY
    ret = rt_mq_send_wait_prio(testmq, &send_buf[3], sizeof(send_buf[0]), 3, 0, RT_UNINTERRUPTIBLE);
    uassert_true(ret == RT_EOK);
    ret = rt_mq_send_wait_prio(testmq, &send_buf[0], sizeof(send_buf[0]), 0, 0, RT_UNINTERRUPTIBLE);
    uassert_true(ret == RT_EOK);

    ret = rt_mq_send_wait_prio(testmq, &send_buf[2], sizeof(send_buf[0]), 1, 0, RT_UNINTERRUPTIBLE);
    uassert_true(ret == RT_EOK);
    ret = rt_mq_send_wait_prio(testmq, &send_buf[4], sizeof(send_buf[0]), 4, 0, RT_UNINTERRUPTIBLE);
    uassert_true(ret == RT_EOK);
    ret = rt_mq_send_wait_prio(testmq, &send_buf[1], sizeof(send_buf[0]), 1, 0, RT_UNINTERRUPTIBLE);
    uassert_true(ret == RT_EOK);

    while (testmq->entry != 0)
    {
        rt_thread_delay(100);
    }
#endif

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
    if (dynamic_mq != RT_NULL)
    {
        mq_send_case(dynamic_mq);
    }
#endif /* RT_USING_HEAP */

    rt_event_send(&finish_e, MQSEND_FINISH);
}

static void mq_recv_case(rt_mq_t testmq)
{
    rt_uint32_t recv_buf[MAX_MSGS + 1] = { 0 };
    rt_ssize_t ret = RT_EOK;

    for (int var = 0; var < MAX_MSGS + 1; ++var)
    {
        ret = rt_mq_recv(testmq, &recv_buf[var], sizeof(recv_buf[0]), RT_WAITING_FOREVER);
        uassert_true(ret >= 0);
        uassert_true(recv_buf[var] == (var + 1));
    }

    for (int var = 0; var < 3; ++var)
    {
        ret = rt_mq_recv(testmq, &recv_buf[var], sizeof(recv_buf[0]), RT_WAITING_FOREVER);
        uassert_true(ret >= 0);
        uassert_true(recv_buf[var] == (var + 1));
    }
#ifdef RT_USING_MESSAGEQUEUE_PRIORITY
    rt_int32_t msg_prio;
    while (testmq->entry == MAX_MSGS)
    {
        rt_thread_delay(100);
    }
    for (int var = 0; var < MAX_MSGS; ++var)
    {
        ret = rt_mq_recv_prio(testmq, &recv_buf[var], sizeof(recv_buf[0]), &msg_prio, RT_WAITING_FOREVER, RT_UNINTERRUPTIBLE);
        rt_kprintf("msg_prio = %d\r\n", msg_prio);
        uassert_true(ret >= 0);
        uassert_true(recv_buf[var] == (MAX_MSGS - var));
    }
#endif
}

static void mq_recv_entry(void *param)
{
    mq_recv_case(&static_mq);

#ifdef RT_USING_HEAP
    if (dynamic_mq != RT_NULL)
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

static struct rt_messagequeue fifo_mq;
static rt_uint8_t fifo_mq_buf[RT_MQ_BUF_SIZE(MSG_SIZE, MAX_MSGS)];
static rt_uint32_t fifo_recv_val[2];
/* Keep the receiver stack off the utest thread stack: the utest thread uses
 * UTEST_THR_STACK_SIZE itself, so a local array of that size overflows it. */
static rt_uint8_t fifo_recv_stack[UTEST_THR_STACK_SIZE];

static struct rt_thread fifo_recv_th;
static rt_uint32_t v1 = 111, v2 = 222;

static void _fifo_recv_entry(void *param)
{
    rt_mq_recv(&fifo_mq, &fifo_recv_val[0], sizeof(fifo_recv_val[0]), RT_WAITING_FOREVER);
    rt_mq_recv(&fifo_mq, &fifo_recv_val[1], sizeof(fifo_recv_val[1]), RT_WAITING_FOREVER);
}

static void test_mq_fifo_order(void)
{
    rt_err_t ret;

    ret = rt_mq_init(&fifo_mq, "mq_fifo", fifo_mq_buf, MSG_SIZE, sizeof(fifo_mq_buf), RT_IPC_FLAG_FIFO);
    uassert_true(ret == RT_EOK);

    fifo_recv_val[0] = 0;
    fifo_recv_val[1] = 0;

    ret = rt_thread_init(&fifo_recv_th, "th_recv", _fifo_recv_entry, RT_NULL, fifo_recv_stack, sizeof(fifo_recv_stack), 24, 20);
    uassert_true(ret == RT_EOK);
    rt_thread_startup(&fifo_recv_th);

    /* allow recv thread to block on empty mq */
    rt_thread_mdelay(20);

    /* send messages after receiver has blocked */
    ret = rt_mq_send(&fifo_mq, &v1, sizeof(v1));
    uassert_true(ret == RT_EOK);
    ret = rt_mq_send(&fifo_mq, &v2, sizeof(v2));
    uassert_true(ret == RT_EOK);

    rt_thread_mdelay(20);

    uassert_int_equal(fifo_recv_val[0], 111);
    uassert_int_equal(fifo_recv_val[1], 222);

    rt_mq_detach(&fifo_mq);
}

#ifdef RT_USING_MESSAGEQUEUE_PRIORITY
static struct rt_messagequeue urgent_mq;
static rt_uint8_t urgent_mq_buf[RT_MQ_BUF_SIZE(MSG_SIZE, 2)];
static rt_uint32_t urgent_recv_val[2];
static rt_int32_t urgent_recv_prio[2];
static struct rt_thread urgent_recv_th;
static rt_uint8_t urgent_recv_stack[UTEST_THR_STACK_SIZE];
static struct rt_thread urgent_cleanup_th;
static rt_uint8_t urgent_cleanup_stack[UTEST_THR_STACK_SIZE];
static rt_uint32_t urgent_cleanup_val;

static void _urgent_recv_entry(void *param)
{
    rt_mq_recv_prio(&urgent_mq, &urgent_recv_val[0], sizeof(urgent_recv_val[0]),
                    &urgent_recv_prio[0], RT_WAITING_FOREVER, RT_UNINTERRUPTIBLE);
    rt_mq_recv_prio(&urgent_mq, &urgent_recv_val[1], sizeof(urgent_recv_val[1]),
                    &urgent_recv_prio[1], RT_WAITING_FOREVER, RT_UNINTERRUPTIBLE);
}

static void _urgent_cleanup_entry(void *param)
{
    rt_mq_recv(&urgent_mq, &urgent_cleanup_val, sizeof(urgent_cleanup_val),
               RT_WAITING_FOREVER);
}

/* wait until the receiver is actually blocked on the queue */
static rt_bool_t _wait_receiver_blocked(void)
{
    int wait;

    for (wait = 0; wait < 200; wait++)
    {
        if (!rt_list_isempty(&(urgent_mq.parent.suspend_thread)))
        {
            return RT_TRUE;
        }

        rt_thread_mdelay(1);
    }

    return RT_FALSE;
}

static void test_mq_urgent_handoff_priority(void)
{
    rt_err_t ret;
    rt_err_t urgent_ret;
    rt_err_t normal_ret;
    rt_base_t critical;
    rt_ssize_t len;
    rt_uint32_t seed = 0;
    rt_uint32_t urgent_val = 111;
    rt_uint32_t normal_val = 222;
    rt_int32_t normal_prio = 7;
    int i;

    ret = rt_mq_init(&urgent_mq, "mq_urgent", urgent_mq_buf, MSG_SIZE,
                     sizeof(urgent_mq_buf), RT_IPC_FLAG_FIFO);
    uassert_true(ret == RT_EOK);
    uassert_int_equal(urgent_mq.max_msgs, 2);

    /* Leave a stale low priority on both message nodes: rt_mq_urgent() takes a
     * free node without touching its priority, so that value is what a
     * non-urgent handoff would be re-sorted with. */
    for (i = 0; i < 2; i++)
    {
        ret = rt_mq_send_wait_prio(&urgent_mq, &seed, sizeof(seed), 0, 0,
                                   RT_UNINTERRUPTIBLE);
        uassert_true(ret == RT_EOK);
    }

    for (i = 0; i < 2; i++)
    {
        len = rt_mq_recv_prio(&urgent_mq, &seed, sizeof(seed), RT_NULL,
                              RT_WAITING_FOREVER, RT_UNINTERRUPTIBLE);
        uassert_true(len >= 0);
    }
    uassert_int_equal(urgent_mq.entry, 0);

    urgent_recv_val[0] = 0;
    urgent_recv_val[1] = 0;

    ret = rt_thread_init(&urgent_recv_th, "th_urgent", _urgent_recv_entry, RT_NULL,
                         urgent_recv_stack, sizeof(urgent_recv_stack), 24, 20);
    uassert_true(ret == RT_EOK);
#ifdef RT_USING_SMP
    rt_thread_control(&urgent_recv_th, RT_THREAD_CTRL_BIND_CPU, (void *)0);
#endif
    rt_thread_startup(&urgent_recv_th);

    uassert_true(_wait_receiver_blocked());

    /* urgent handoff first, then a higher priority normal message, both before
     * the receiver can run: scheduling stays blocked on this CPU. */
    critical = rt_enter_critical();
    urgent_ret = rt_mq_urgent(&urgent_mq, &urgent_val, sizeof(urgent_val));
    normal_ret = rt_mq_send_wait_prio(&urgent_mq, &normal_val, sizeof(normal_val),
                                      normal_prio, 0, RT_UNINTERRUPTIBLE);
    rt_exit_critical_safe(critical);

    uassert_true(urgent_ret == RT_EOK);
    uassert_true(normal_ret == RT_EOK);

    rt_thread_mdelay(50);

    /* the urgent handoff must not be overtaken by the priority message */
    uassert_int_equal(urgent_recv_val[0], urgent_val);
    uassert_int_equal(urgent_recv_val[1], normal_val);

    rt_mq_detach(&urgent_mq);
}

static void test_mq_urgent_handoff_cleanup(void)
{
    rt_err_t ret;
    rt_err_t detach_ret;
    rt_base_t critical;
    rt_ssize_t len;
    rt_uint32_t urgent_val = 333;
    rt_uint32_t recv_val = 0;

    ret = rt_mq_init(&urgent_mq, "mq_uc", urgent_mq_buf, MSG_SIZE,
                     sizeof(urgent_mq_buf), RT_IPC_FLAG_FIFO);
    uassert_true(ret == RT_EOK);

    urgent_cleanup_val = 0;

    ret = rt_thread_init(&urgent_cleanup_th, "th_uc", _urgent_cleanup_entry, RT_NULL,
                         urgent_cleanup_stack, sizeof(urgent_cleanup_stack), 24, 20);
    uassert_true(ret == RT_EOK);
#ifdef RT_USING_SMP
    rt_thread_control(&urgent_cleanup_th, RT_THREAD_CTRL_BIND_CPU, (void *)0);
#endif
    rt_thread_startup(&urgent_cleanup_th);

    uassert_true(_wait_receiver_blocked());

    /* the handoff record exists before the receiver becomes ready */
    ret = rt_mq_urgent(&urgent_mq, &urgent_val, sizeof(urgent_val));
    uassert_true(ret == RT_EOK);

    /* detach the receiver before it ever runs: the thread cleanup must find the
     * record and put the urgent message back at the queue head */
    critical = rt_enter_critical();
    detach_ret = rt_thread_detach(&urgent_cleanup_th);
    rt_exit_critical_safe(critical);

    uassert_true(detach_ret == RT_EOK);

    /* let the idle thread reclaim the detached thread object */
    rt_thread_mdelay(50);

    uassert_int_equal(urgent_mq.entry, 1);

    len = rt_mq_recv(&urgent_mq, &recv_val, sizeof(recv_val), RT_WAITING_FOREVER);
    uassert_true(len >= 0);
    uassert_int_equal(recv_val, urgent_val);

    rt_mq_detach(&urgent_mq);
}
#endif /* RT_USING_MESSAGEQUEUE_PRIORITY */

static rt_err_t utest_tc_init(void)
{
    rt_err_t ret;
    ret = rt_thread_init(&mq_send_thread, "mq_send", mq_send_entry, RT_NULL, mq_send_stack, sizeof(mq_send_stack), 22, 20);
    if (ret != RT_EOK)
    {
        return -RT_ERROR;
    }

    ret = rt_thread_init(&mq_recv_thread, "mq_recv", mq_recv_entry, RT_NULL, mq_recv_stack, sizeof(mq_recv_stack), 23, 20);
    if (ret != RT_EOK)
    {
        return -RT_ERROR;
    }

#ifdef RT_USING_SMP
    rt_thread_control(&mq_send_thread, RT_THREAD_CTRL_BIND_CPU, (void *)0);
    rt_thread_control(&mq_recv_thread, RT_THREAD_CTRL_BIND_CPU, (void *)0);
#endif

    ret = rt_event_init(&finish_e, "finish", RT_IPC_FLAG_FIFO);
    if (ret != RT_EOK)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    /* wait for threads to finish */
    rt_thread_mdelay(100);
    /* detach event object */
    rt_event_detach(&finish_e);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_mq_init);
    UTEST_UNIT_RUN(test_mq_create);
    UTEST_UNIT_RUN(test_mq_testcase);
    UTEST_UNIT_RUN(test_mq_detach);
    UTEST_UNIT_RUN(test_mq_delete);
    UTEST_UNIT_RUN(test_mq_fifo_order);
#ifdef RT_USING_MESSAGEQUEUE_PRIORITY
    UTEST_UNIT_RUN(test_mq_urgent_handoff_priority);
    UTEST_UNIT_RUN(test_mq_urgent_handoff_cleanup);
#endif
}
UTEST_TC_EXPORT(testcase, "core.messagequeue", utest_tc_init, utest_tc_cleanup, 1000);
