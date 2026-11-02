/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-17     illustriousness the first version
 */

/**
 * Test Case Name: Scheduler IPC Timeout Ownership Race Test
 *
 * Test Objectives:
 * - Verify that an in-flight timeout remains the only owner of a suspended
 *   thread after its timer has been removed from the timer list.
 * - Verify that competing IPC producers do not resume the same thread twice.
 * - Verify that IPC resources are retained when the timeout wins the race.
 *
 * Test Scenarios:
 * - Suspend a thread on an IPC object with a finite timeout.
 * - Stop its thread timer directly, reproducing the state after timer expiry
 *   removal and before the timeout callback executes.
 * - Produce two events, semaphore tokens, mailbox messages, or queue messages.
 * - Restart the thread timer to let the timeout callback complete normally.
 * - Verify that the waiter times out once and all produced resources remain.
 *
 * Dependencies:
 * - RT_UTEST_SCHEDULER must be enabled.
 * - The individual IPC tests are compiled when their IPC feature is enabled.
 *
 * Expected Results:
 * - No kernel assertion or duplicate thread resume occurs.
 * - The final output reports a passed core.scheduler_timeout_race testcase.
 */

#define __RT_KERNEL_SOURCE__
#include <rtthread.h>
#include "utest.h"

#define TEST_WAIT_TICKS   100
#define TEST_FINISH_TICKS 10
#define TEST_THREAD_TICK  5
#define TEST_EVENT_FLAG   0x01
#define TEST_MQ_MSG_SIZE  sizeof(rt_uint32_t)
#define TEST_MQ_MSG_COUNT 2

static struct rt_semaphore _exit_sem;

static rt_bool_t _thread_is_suspended(rt_thread_t thread)
{
    rt_sched_lock_level_t slvl;
    rt_bool_t suspended;

    rt_sched_lock(&slvl);
    suspended = rt_sched_thread_is_suspended(thread);
    rt_sched_unlock(slvl);

    return suspended;
}

static rt_bool_t _wait_until_suspended(rt_thread_t thread)
{
    rt_tick_t deadline;

    deadline = rt_tick_get() + TEST_FINISH_TICKS;
    do
    {
        if (_thread_is_suspended(thread))
        {
            return RT_TRUE;
        }
        rt_thread_delay(1);
    } while ((rt_int32_t)(deadline - rt_tick_get()) > 0);

    return RT_FALSE;
}

static void _take_timeout_ownership(rt_thread_t thread)
{
    rt_sched_lock_level_t slvl;
    rt_bool_t suspended;
    rt_err_t stop_result;
    rt_uint8_t timer_flag;

    rt_sched_lock(&slvl);
    suspended = rt_sched_thread_is_suspended(thread);
    stop_result = rt_timer_stop(&thread->thread_timer);
    timer_flag = RT_SCHED_CTX(thread).sched_flag_ttmr_set;
    rt_sched_unlock(slvl);

    uassert_true(suspended);
    uassert_int_equal(stop_result, RT_EOK);
    uassert_int_equal(timer_flag, 1);
}

static void _complete_timeout(rt_thread_t thread)
{
    rt_tick_t timeout = 1;

    uassert_int_equal(rt_timer_control(&thread->thread_timer,
                                       RT_TIMER_CTRL_SET_TIME,
                                       &timeout),
                      RT_EOK);
    uassert_int_equal(rt_timer_start(&thread->thread_timer), RT_EOK);
    uassert_int_equal(rt_sem_take(&_exit_sem, TEST_FINISH_TICKS), RT_EOK);
}

#ifdef RT_USING_EVENT
static struct rt_event _event;
static struct rt_thread _event_waiter;
rt_align(RT_ALIGN_SIZE) static rt_uint8_t _event_waiter_stack[UTEST_THR_STACK_SIZE];
static volatile rt_err_t _event_wait_result;

static void _event_waiter_entry(void *parameter)
{
    rt_uint32_t received;

    RT_UNUSED(parameter);
    _event_wait_result = rt_event_recv(&_event,
                                       TEST_EVENT_FLAG,
                                       RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                                       TEST_WAIT_TICKS,
                                       &received);
    rt_sem_release(&_exit_sem);
}

static void _test_event_timeout_ownership(void)
{
    rt_uint32_t received = 0;

    _event_wait_result = RT_EOK;
    uassert_int_equal(rt_event_init(&_event, "to_evt", RT_IPC_FLAG_FIFO), RT_EOK);
    uassert_int_equal(rt_thread_init(&_event_waiter,
                                     "to_evt",
                                     _event_waiter_entry,
                                     RT_NULL,
                                     _event_waiter_stack,
                                     sizeof(_event_waiter_stack),
                                     UTEST_THR_PRIORITY + 1,
                                     TEST_THREAD_TICK),
                      RT_EOK);
    uassert_int_equal(rt_thread_startup(&_event_waiter), RT_EOK);
    uassert_true(_wait_until_suspended(&_event_waiter));

    _take_timeout_ownership(&_event_waiter);
    uassert_int_equal(rt_event_send(&_event, TEST_EVENT_FLAG), RT_EOK);
    uassert_int_equal(rt_event_send(&_event, TEST_EVENT_FLAG), RT_EOK);
    uassert_true(_thread_is_suspended(&_event_waiter));

    _complete_timeout(&_event_waiter);
    uassert_int_equal(_event_wait_result, -RT_ETIMEOUT);
    uassert_int_equal(rt_event_recv(&_event,
                                    TEST_EVENT_FLAG,
                                    RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                                    RT_WAITING_NO,
                                    &received),
                      RT_EOK);
    uassert_int_equal(received, TEST_EVENT_FLAG);
    uassert_int_equal(rt_event_detach(&_event), RT_EOK);
}
#endif /* RT_USING_EVENT */

#ifdef RT_USING_SEMAPHORE
static struct rt_semaphore _sem;
static struct rt_thread _sem_waiter;
rt_align(RT_ALIGN_SIZE) static rt_uint8_t _sem_waiter_stack[UTEST_THR_STACK_SIZE];
static volatile rt_err_t _sem_wait_result;

static void _sem_waiter_entry(void *parameter)
{
    RT_UNUSED(parameter);
    _sem_wait_result = rt_sem_take(&_sem, TEST_WAIT_TICKS);
    rt_sem_release(&_exit_sem);
}

static void _test_sem_timeout_ownership(void)
{
    _sem_wait_result = RT_EOK;
    uassert_int_equal(rt_sem_init(&_sem, "to_sem", 0, RT_IPC_FLAG_FIFO), RT_EOK);
    uassert_int_equal(rt_thread_init(&_sem_waiter,
                                     "to_sem",
                                     _sem_waiter_entry,
                                     RT_NULL,
                                     _sem_waiter_stack,
                                     sizeof(_sem_waiter_stack),
                                     UTEST_THR_PRIORITY + 1,
                                     TEST_THREAD_TICK),
                      RT_EOK);
    uassert_int_equal(rt_thread_startup(&_sem_waiter), RT_EOK);
    uassert_true(_wait_until_suspended(&_sem_waiter));

    _take_timeout_ownership(&_sem_waiter);
    uassert_int_equal(rt_sem_release(&_sem), RT_EOK);
    uassert_int_equal(rt_sem_release(&_sem), RT_EOK);
    uassert_true(_thread_is_suspended(&_sem_waiter));
    uassert_int_equal(_sem.value, 2);

    _complete_timeout(&_sem_waiter);
    uassert_int_equal(_sem_wait_result, -RT_ETIMEOUT);
    uassert_int_equal(rt_sem_trytake(&_sem), RT_EOK);
    uassert_int_equal(rt_sem_trytake(&_sem), RT_EOK);
    uassert_int_equal(rt_sem_trytake(&_sem), -RT_ETIMEOUT);
    uassert_int_equal(rt_sem_detach(&_sem), RT_EOK);
}
#endif /* RT_USING_SEMAPHORE */

#ifdef RT_USING_MAILBOX
static struct rt_mailbox _mailbox;
static rt_ubase_t _mailbox_pool[TEST_MQ_MSG_COUNT];
static struct rt_thread _mailbox_waiter;
rt_align(RT_ALIGN_SIZE) static rt_uint8_t _mailbox_waiter_stack[UTEST_THR_STACK_SIZE];
static volatile rt_err_t _mailbox_wait_result;

static void _mailbox_waiter_entry(void *parameter)
{
    rt_ubase_t value;

    RT_UNUSED(parameter);
    _mailbox_wait_result = rt_mb_recv(&_mailbox, &value, TEST_WAIT_TICKS);
    rt_sem_release(&_exit_sem);
}

static void _test_mailbox_timeout_ownership(void)
{
    rt_ubase_t value;

    _mailbox_wait_result = RT_EOK;
    uassert_int_equal(rt_mb_init(&_mailbox,
                                 "to_mb",
                                 _mailbox_pool,
                                 sizeof(_mailbox_pool) / sizeof(_mailbox_pool[0]),
                                 RT_IPC_FLAG_FIFO),
                      RT_EOK);
    uassert_int_equal(rt_thread_init(&_mailbox_waiter,
                                     "to_mb",
                                     _mailbox_waiter_entry,
                                     RT_NULL,
                                     _mailbox_waiter_stack,
                                     sizeof(_mailbox_waiter_stack),
                                     UTEST_THR_PRIORITY + 1,
                                     TEST_THREAD_TICK),
                      RT_EOK);
    uassert_int_equal(rt_thread_startup(&_mailbox_waiter), RT_EOK);
    uassert_true(_wait_until_suspended(&_mailbox_waiter));

    _take_timeout_ownership(&_mailbox_waiter);
    uassert_int_equal(rt_mb_send(&_mailbox, 1), RT_EOK);
    uassert_int_equal(rt_mb_send(&_mailbox, 2), RT_EOK);
    uassert_true(_thread_is_suspended(&_mailbox_waiter));
    uassert_int_equal(_mailbox.entry, 2);

    _complete_timeout(&_mailbox_waiter);
    uassert_int_equal(_mailbox_wait_result, -RT_ETIMEOUT);
    uassert_int_equal(rt_mb_recv(&_mailbox, &value, RT_WAITING_NO), RT_EOK);
    uassert_int_equal(value, 1);
    uassert_int_equal(rt_mb_recv(&_mailbox, &value, RT_WAITING_NO), RT_EOK);
    uassert_int_equal(value, 2);
    uassert_int_equal(rt_mb_detach(&_mailbox), RT_EOK);
}
#endif /* RT_USING_MAILBOX */

#ifdef RT_USING_MESSAGEQUEUE
static struct rt_messagequeue _messagequeue;
static rt_uint8_t _messagequeue_pool[RT_MQ_BUF_SIZE(TEST_MQ_MSG_SIZE, TEST_MQ_MSG_COUNT)];
static struct rt_thread _messagequeue_waiter;
rt_align(RT_ALIGN_SIZE) static rt_uint8_t _messagequeue_waiter_stack[UTEST_THR_STACK_SIZE];
static volatile rt_ssize_t _messagequeue_wait_result;

static void _messagequeue_waiter_entry(void *parameter)
{
    rt_uint32_t value;

    RT_UNUSED(parameter);
    _messagequeue_wait_result = rt_mq_recv(&_messagequeue,
                                           &value,
                                           sizeof(value),
                                           TEST_WAIT_TICKS);
    rt_sem_release(&_exit_sem);
}

static void _test_messagequeue_timeout_ownership(void)
{
    rt_uint32_t value;
    rt_uint32_t first = 1;
    rt_uint32_t second = 2;

    _messagequeue_wait_result = 0;
    uassert_int_equal(rt_mq_init(&_messagequeue,
                                 "to_mq",
                                 _messagequeue_pool,
                                 TEST_MQ_MSG_SIZE,
                                 sizeof(_messagequeue_pool),
                                 RT_IPC_FLAG_FIFO),
                      RT_EOK);
    uassert_int_equal(rt_thread_init(&_messagequeue_waiter,
                                     "to_mq",
                                     _messagequeue_waiter_entry,
                                     RT_NULL,
                                     _messagequeue_waiter_stack,
                                     sizeof(_messagequeue_waiter_stack),
                                     UTEST_THR_PRIORITY + 1,
                                     TEST_THREAD_TICK),
                      RT_EOK);
    uassert_int_equal(rt_thread_startup(&_messagequeue_waiter), RT_EOK);
    uassert_true(_wait_until_suspended(&_messagequeue_waiter));

    _take_timeout_ownership(&_messagequeue_waiter);
    uassert_int_equal(rt_mq_send(&_messagequeue, &first, sizeof(first)), RT_EOK);
    uassert_int_equal(rt_mq_send(&_messagequeue, &second, sizeof(second)), RT_EOK);
    uassert_true(_thread_is_suspended(&_messagequeue_waiter));
    uassert_int_equal(_messagequeue.entry, 2);

    _complete_timeout(&_messagequeue_waiter);
    uassert_int_equal(_messagequeue_wait_result, -RT_ETIMEOUT);
    uassert_int_equal(rt_mq_recv(&_messagequeue, &value, sizeof(value), RT_WAITING_NO),
                      sizeof(value));
    uassert_int_equal(value, first);
    uassert_int_equal(rt_mq_recv(&_messagequeue, &value, sizeof(value), RT_WAITING_NO),
                      sizeof(value));
    uassert_int_equal(value, second);
    uassert_int_equal(rt_mq_detach(&_messagequeue), RT_EOK);
}
#endif /* RT_USING_MESSAGEQUEUE */

static rt_err_t utest_tc_init(void)
{
    return rt_sem_init(&_exit_sem, "to_exit", 0, RT_IPC_FLAG_FIFO);
}

static rt_err_t utest_tc_cleanup(void)
{
    return rt_sem_detach(&_exit_sem);
}

static void testcase(void)
{
#ifdef RT_USING_EVENT
    UTEST_UNIT_RUN(_test_event_timeout_ownership);
#endif
#ifdef RT_USING_SEMAPHORE
    UTEST_UNIT_RUN(_test_sem_timeout_ownership);
#endif
#ifdef RT_USING_MAILBOX
    UTEST_UNIT_RUN(_test_mailbox_timeout_ownership);
#endif
#ifdef RT_USING_MESSAGEQUEUE
    UTEST_UNIT_RUN(_test_messagequeue_timeout_ownership);
#endif
}

UTEST_TC_EXPORT(testcase,
                "core.scheduler_timeout_race",
                utest_tc_init,
                utest_tc_cleanup,
                10);
