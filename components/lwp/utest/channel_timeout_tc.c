/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-20     illustriousness the first version
 */

/**
 * Test Case Name: LWP Channel Thread Timer Ownership Test
 *
 * Test Objectives:
 * - Verify that LWP channel timeout callbacks release thread timer ownership.
 * - Verify that the same thread can enter a permanent channel wait after a
 *   finite wait times out and can still be woken by a channel operation.
 *
 * Test Scenarios:
 * - Let a receiver time out, then receive forever and wake it with a message.
 * - Let a sender time out waiting for a reply, then wait forever for another
 *   reply and wake it with a receiver and reply.
 *
 * Dependencies:
 * - RT_USING_SMART and RT_UTEST_SCHEDULER must be enabled.
 *
 * Expected Results:
 * - Both timeout callbacks clear sched_flag_ttmr_set.
 * - Both permanent waits complete successfully without another timeout.
 */

#define __RT_KERNEL_SOURCE__
#include <fcntl.h>
#include <rtthread.h>

#include "../lwp_ipc.h"
#include "utest.h"

#define TEST_TIMEOUT_TICKS  5
#define TEST_FINISH_TICKS   20
#define TEST_THREAD_TICK    5
#define TEST_RECEIVER_VALUE 0x1234U
#define TEST_SENDER_VALUE   0x5678U
#define TEST_REPLY_VALUE    0x9abcU

static struct rt_semaphore _timeout_sem;
static struct rt_semaphore _continue_sem;
static struct rt_semaphore _waiting_sem;
static struct rt_semaphore _done_sem;

static rt_uint8_t _thread_timer_flag(rt_thread_t thread)
{
    rt_sched_lock_level_t slvl;
    rt_uint8_t timer_flag;

    rt_sched_lock(&slvl);
    timer_flag = RT_SCHED_CTX(thread).sched_flag_ttmr_set;
    rt_sched_unlock(slvl);

    return timer_flag;
}

static void _clear_thread_timer_flag(rt_thread_t thread)
{
    rt_sched_lock_level_t slvl;

    rt_sched_lock(&slvl);
    RT_SCHED_CTX(thread).sched_flag_ttmr_set = 0;
    rt_sched_unlock(slvl);
}

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

static rt_bool_t _is_timeout_result(rt_err_t result)
{
    return result == RT_ETIMEOUT || result == -RT_ETIMEOUT;
}

static struct rt_thread _receiver_thread;
rt_align(RT_ALIGN_SIZE) static rt_uint8_t _receiver_stack[UTEST_THR_STACK_SIZE];
static rt_channel_t _receiver_channel;
static volatile rt_err_t _receiver_timeout_result;
static volatile rt_err_t _receiver_wait_result;
static volatile rt_ubase_t _receiver_value;
static volatile rt_uint8_t _receiver_timer_flag;

static void _receiver_entry(void *parameter)
{
    struct rt_channel_msg message = { 0 };

    RT_UNUSED(parameter);

    _receiver_timeout_result = rt_raw_channel_recv_timeout(_receiver_channel,
                                                           &message,
                                                           TEST_TIMEOUT_TICKS);
    _receiver_timer_flag = _thread_timer_flag(rt_thread_self());
    rt_sem_release(&_timeout_sem);

    rt_sem_take(&_continue_sem, RT_WAITING_FOREVER);
    rt_sem_release(&_waiting_sem);

    _receiver_wait_result = rt_raw_channel_recv(_receiver_channel, &message);
    if (_receiver_wait_result == RT_EOK)
    {
        _receiver_value = (rt_ubase_t)message.u.d;
    }
    rt_sem_release(&_done_sem);
}

static void _test_receiver_timeout_reuse(void)
{
    struct rt_channel_msg message = { 0 };

    _receiver_timeout_result = RT_EOK;
    _receiver_wait_result = -RT_ERROR;
    _receiver_value = 0;
    _receiver_timer_flag = 0;

    _receiver_channel = rt_raw_channel_open("to_recv", O_CREAT | O_EXCL);
    uassert_not_null(_receiver_channel);
    if (_receiver_channel == RT_NULL)
    {
        return;
    }

    uassert_int_equal(rt_thread_init(&_receiver_thread,
                                     "to_recv",
                                     _receiver_entry,
                                     RT_NULL,
                                     _receiver_stack,
                                     sizeof(_receiver_stack),
                                     UTEST_THR_PRIORITY + 1,
                                     TEST_THREAD_TICK),
                      RT_EOK);
    uassert_int_equal(rt_thread_startup(&_receiver_thread), RT_EOK);
    uassert_int_equal(rt_sem_take(&_timeout_sem, TEST_FINISH_TICKS), RT_EOK);

    uassert_true(_is_timeout_result(_receiver_timeout_result));
    uassert_int_equal(_receiver_timer_flag, 0);
    if (_receiver_timer_flag != 0)
    {
        /* Keep the negative-path test recoverable on an unfixed kernel. */
        _clear_thread_timer_flag(&_receiver_thread);
    }

    uassert_int_equal(rt_sem_release(&_continue_sem), RT_EOK);
    uassert_int_equal(rt_sem_take(&_waiting_sem, TEST_FINISH_TICKS), RT_EOK);
    uassert_true(_wait_until_suspended(&_receiver_thread));

    message.type = RT_CHANNEL_RAW;
    message.u.d = (void *)(rt_ubase_t)TEST_RECEIVER_VALUE;
    uassert_int_equal(rt_raw_channel_send(_receiver_channel, &message), RT_EOK);
    uassert_int_equal(rt_sem_take(&_done_sem, TEST_FINISH_TICKS), RT_EOK);
    uassert_int_equal(_receiver_wait_result, RT_EOK);
    uassert_int_equal(_receiver_value, TEST_RECEIVER_VALUE);
    uassert_int_equal(rt_raw_channel_close(_receiver_channel), RT_EOK);
}

static struct rt_thread _sender_thread;
rt_align(RT_ALIGN_SIZE) static rt_uint8_t _sender_stack[UTEST_THR_STACK_SIZE];
static rt_channel_t _sender_channel;
static volatile rt_err_t _sender_timeout_result;
static volatile rt_err_t _sender_wait_result;
static volatile rt_ubase_t _sender_reply_value;
static volatile rt_uint8_t _sender_timer_flag;

static void _sender_entry(void *parameter)
{
    struct rt_channel_msg request = { 0 };
    struct rt_channel_msg reply = { 0 };

    RT_UNUSED(parameter);

    request.type = RT_CHANNEL_RAW;
    request.u.d = (void *)(rt_ubase_t)TEST_SENDER_VALUE;
    _sender_timeout_result = rt_raw_channel_send_recv_timeout(_sender_channel,
                                                              &request,
                                                              &reply,
                                                              TEST_TIMEOUT_TICKS);
    _sender_timer_flag = _thread_timer_flag(rt_thread_self());
    rt_sem_release(&_timeout_sem);

    rt_sem_take(&_continue_sem, RT_WAITING_FOREVER);
    rt_sem_release(&_waiting_sem);

    _sender_wait_result = rt_raw_channel_send_recv(_sender_channel, &request, &reply);
    if (_sender_wait_result == RT_EOK)
    {
        _sender_reply_value = (rt_ubase_t)reply.u.d;
    }
    rt_sem_release(&_done_sem);
}

static void _test_sender_timeout_reuse(void)
{
    struct rt_channel_msg request = { 0 };
    struct rt_channel_msg reply = { 0 };

    _sender_timeout_result = RT_EOK;
    _sender_wait_result = -RT_ERROR;
    _sender_reply_value = 0;
    _sender_timer_flag = 0;

    _sender_channel = rt_raw_channel_open("to_send", O_CREAT | O_EXCL);
    uassert_not_null(_sender_channel);
    if (_sender_channel == RT_NULL)
    {
        return;
    }

    uassert_int_equal(rt_thread_init(&_sender_thread,
                                     "to_send",
                                     _sender_entry,
                                     RT_NULL,
                                     _sender_stack,
                                     sizeof(_sender_stack),
                                     UTEST_THR_PRIORITY + 1,
                                     TEST_THREAD_TICK),
                      RT_EOK);
    uassert_int_equal(rt_thread_startup(&_sender_thread), RT_EOK);
    uassert_int_equal(rt_sem_take(&_timeout_sem, TEST_FINISH_TICKS), RT_EOK);

    uassert_true(_is_timeout_result(_sender_timeout_result));
    uassert_int_equal(_sender_timer_flag, 0);
    if (_sender_timer_flag != 0)
    {
        /* Keep the negative-path test recoverable on an unfixed kernel. */
        _clear_thread_timer_flag(&_sender_thread);
    }

    uassert_int_equal(rt_sem_release(&_continue_sem), RT_EOK);
    uassert_int_equal(rt_sem_take(&_waiting_sem, TEST_FINISH_TICKS), RT_EOK);
    uassert_true(_wait_until_suspended(&_sender_thread));

    uassert_int_equal(rt_raw_channel_recv_timeout(_sender_channel,
                                                  &request,
                                                  TEST_FINISH_TICKS),
                      RT_EOK);
    uassert_int_equal(request.type, RT_CHANNEL_RAW);
    uassert_int_equal((rt_ubase_t)request.u.d, TEST_SENDER_VALUE);

    reply.type = RT_CHANNEL_RAW;
    reply.u.d = (void *)(rt_ubase_t)TEST_REPLY_VALUE;
    uassert_int_equal(rt_raw_channel_reply(_sender_channel, &reply), RT_EOK);
    uassert_int_equal(rt_sem_take(&_done_sem, TEST_FINISH_TICKS), RT_EOK);
    uassert_int_equal(_sender_wait_result, RT_EOK);
    uassert_int_equal(_sender_reply_value, TEST_REPLY_VALUE);
    uassert_int_equal(rt_raw_channel_close(_sender_channel), RT_EOK);
}

static rt_err_t utest_tc_init(void)
{
    rt_err_t result;

    result = rt_sem_init(&_timeout_sem, "to_tmo", 0, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        return result;
    }
    result = rt_sem_init(&_continue_sem, "to_cont", 0, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        rt_sem_detach(&_timeout_sem);
        return result;
    }
    result = rt_sem_init(&_waiting_sem, "to_wait", 0, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        rt_sem_detach(&_continue_sem);
        rt_sem_detach(&_timeout_sem);
        return result;
    }
    result = rt_sem_init(&_done_sem, "to_done", 0, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        rt_sem_detach(&_waiting_sem);
        rt_sem_detach(&_continue_sem);
        rt_sem_detach(&_timeout_sem);
    }

    return result;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_sem_detach(&_done_sem);
    rt_sem_detach(&_waiting_sem);
    rt_sem_detach(&_continue_sem);
    return rt_sem_detach(&_timeout_sem);
}

static void testcase(void)
{
    UTEST_UNIT_RUN(_test_receiver_timeout_reuse);
    UTEST_UNIT_RUN(_test_sender_timeout_reuse);
}

UTEST_TC_EXPORT(testcase,
                "components.lwp.channel_timeout_reuse",
                utest_tc_init,
                utest_tc_cleanup,
                10);
