/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-12     flybreak     the first version
 *
 * case 1:rt_signal_install, install all available signal
 * case 2:rt_signal_install, install illegal signal
 * case 3:rt_signal_mask/unmask, one thread self, install and unmask, then kill, should received.
 * case 4:rt_signal_mask/unmask, one thread self, install and unmask and mask, then kill, should can't received.
 * case 5:rt_signal_wait, two thread, thread1: install and unmask, then wait 1s; thread2: kill, should received.
 * case 6:rt_signal_wait, two thread, thread1: install and unmask, then wait 1s; thread2: sleep 2s then kill, should can't received.
 * case 7:rt_signal_kill, kill legal thread, return 0;
 * case 8:rt_signal_kill, kill illegal thread, return failed (unused);
 * case 9:rt_signal_kill, kill illegal signo, return -RT_EINVAL;
 *
 *
 * Test Case Name: [rt_signal_tc]
 *
 * Test Objectives:
 * - [rt_signal_install_test]: Verify the correctness of the rt_signal_install function's
 * - functionality. The registration of the signal handler should be completed correctly.
 * - Include Case1 and Case2.
 *
 * - [rt_signal_unmask_test]: Verify the correctness of the rt_signal_unmask functions's
 * - functionality. The signal handler will only be triggered when the signal is unmasked.
 * - Include Case3.
 *
 * - [rt_signal_mask_test]: Verify the correctness of the rt_signal_mask functions's
 * - functionality. The signal handler will not be triggered when the signal is masked.
 * - Include Case4.
 *
 * - [rt_signal_kill_test]: Verify the correctness of the rt_signal_kill function's
 * - functionality. Signals should be sent to the specified thread correctly. Include
 * - Case7, Case8 and Case9. But Case8 is currently unused.
 *
 * - [rt_signal_wait_test]: Verify signal delivery to a waiting thread. Include Case5.
 *
 * - [rt_signal_wait_test2]: Verify timeout behavior when waiting for a signal.
 *
 * Test Scenarios:
 *
 * - [rt_signal_install_test]: When the signal signo is greater than 0 and less than RT_SIG_MAX,
 * - the rt_signal_install function can register the signal handler normally (i.e., the return
 * - value is not equal to SIG_ERR). However, if signo is not within the above range, the
 * - rt_signal_install function returns SIG_ERR.
 *
 * - [rt_signal_unmask_test]: When signo is valid, the signal handler will first be successfully
 * - registered via rt_signal_install, where receive_sig is assigned the value of the triggered
 * - signal signo. After successful registration, the specified signal mask is unmasked using
 * - rt_signal_unmask, and a signal is sent to rt_thread_self via rt_thread_kill. After a 1ms
 * - delay, the signal callback function is triggered successfully, and the value of receive_sig
 * - equals the value of signo.
 *
 * - [rt_signal_mask_test]: When signo is valid, the signal handler will first be successfully
 * - registered via rt_signal_install, where receive_sig is assigned the value of the triggered
 * - signal signo. After successful registration, the specified signal mask is unmasked using
 * - rt_signal_unmask, then masked again using rt_signal_mask. A signal is then sent to rt_thread_self
 * - via rt_thread_kill. After a 1ms delay, the signal callback function is not triggered, and the
 * - value of receive_sig does not equal the value of signo.
 *
 * - [rt_signal_kill_test]: Case7(the for Loop) is the same as the loop in [rt_signal_mask_test].
 * - Case9 Verifies that when an invalid signal is sent using rt_signal_kill, the function returns
 * - -RT_EINVAL.
 *
 * - [rt_signal_wait_test]: In this test case, a new thread("sig_t1") is created to execute the
 * - rt_signal_wait_thread function. Inside the new thread, the SIGUSR1 signal handler is
 * - installed and unmasked. The thread then waits for the SIGUSR1 signal with a timeout of
 * - RT_TICK_PER_SECOND ticks. Meanwhile, the main test case thread sleeps for 1ms to ensure that
 * - "sig_t1" is waiting for the signal, and then sends the SIGUSR1 signal to "sig_t1" using
 * - rt_thread_kill. The main thread then waits on the _received_signal semaphore, which will be
 * - released by "sig_t1" upon receiving the signal. Finally, the test case verifies that the
 * - receive_sig variable is set to SIGUSR1, confirming that the signal was successfully
 * - received by the waiting thread.
 *
 * - [rt_signal_wait_test2]: Similar to [rt_signal_wait_test], a new thread("sig_t1") is created
 * - to execute the rt_signal_wait_thread function. But in this case, after creating the thread,
 * - the main test case thread sleeps for 2000ms, which is longer than the 1-second timeout
 * - specified in rt_signal_wait_thread. After waking up, the main thread sends the SIGUSR1 signal
 * - to "sig_t1" using rt_thread_kill. Since "sig_t1" has already timed out waiting for the signal,
 * - it will not receive the signal. The main thread then attempts to take the _received_signal
 * - semaphore with a timeout of 1 tick, which should fail since "sig_t1" did not receive the signal
 * - and thus did not release the semaphore. Finally, the test case verifies that the receive_sig
 * - variable is not equal to SIGUSR1, confirming that the signal was not received by the waiting thread
 * - due to the timeout.
 *
 * Verification Metrics:
 *
 * - [rt_signal_install_test]: Case 1 (i.e., the rt_signal_install inside the for loop)
 * - will not return SIG_ERR. Case 2 (i.e., the rt_signal_install outside the for loop)
 * - will return SIG_ERR.
 *
 * - [rt_signal_unmask_test]: Every signo shall correctly trigger the signal handler, such
 * - that receive_sig equals signo.
 *
 * - [rt_signal_mask_test]: Every signo shall not trigger the signal handler after masking,
 * - such that receive_sig does not equal signo.
 *
 * - [rt_signal_kill_test]: In Case7, every signo shall correctly trigger the signal handler,
 * - such that receive_sig equals signo. In Case9, rt_signal_kill shall return -RT_EINVAL.
 *
 * - [rt_signal_wait_test]: In Case5, receive_sig shall equal SIGUSR1, indicating that the waiting
 * - thread successfully received the signal. And main thread can take the semaphore.
 *
 * - [rt_signal_wait_test2]: In Case6, receive_sig shall not equal SIGUSR1, indicating that the waiting
 * - thread did not receive the signal due to timeout. And main thread fails to take the semaphore.
 *
 * Dependencies:
 * - Case1-9: Enable RT_USING_SIGNALS and RT_USING_HEAP.
 *
 * Expected Results:
 * - [rt_signal_install_test]: Handlers installed successfully for all valid signals,
 * - installation fails for invalid signal.
 *
 * - [rt_signal_unmask_test]: Signals are received when unmasked.
 *
 * - [rt_signal_mask_test]: Signals are not received when masked.
 *
 * - [rt_signal_kill_test]: Signals are sent and received correctly for valid cases,
 * - errors returned for invalid cases.
 *
 * - [rt_signal_wait_test]: Signals are correctly received by waiting threads and semaphore
 * - is released as expected.
 *
 * - [rt_signal_wait_test2]: Signals are not received after timeout and semaphore take fails.
 */

#include <rtthread.h>
#include "utest.h"

static volatile int receive_sig = 0;
static struct rt_semaphore _received_signal;
static struct rt_semaphore _signal_wait_done;
static struct rt_semaphore _sem_signal_wait;
static struct rt_semaphore _sem_signal_ready;
static struct rt_semaphore _sem_signal_done;
static struct rt_semaphore _signal_wait_repeat_ready;
static volatile rt_err_t _sem_signal_result;
static volatile rt_int32_t _sem_signal_timeout;
static volatile rt_err_t _signal_wait_result;
static volatile int _signal_wait_repeat_count;
static volatile rt_bool_t _signal_handler_delay;

/* Record the native signal received by the worker thread. */
static void signal_sem_handler(int signo)
{
    receive_sig = signo;

    if (_signal_handler_delay)
    {
        rt_thread_delay(1);
    }
}

/* Count signals handled after a signal-wait operation returns. */
static void signal_wait_repeat_handler(int signo)
{
    RT_UNUSED(signo);
    _signal_wait_repeat_count++;
}

/* Wait on a semaphore with the requested signal interruption mode. */
static void signal_sem_wait_thread(void *parameter)
{
    int suspend_flag;

    suspend_flag = (int)(rt_ubase_t)parameter;
    rt_signal_install(SIGUSR1, signal_sem_handler);
    rt_signal_install(SIGKILL, signal_sem_handler);
    rt_signal_install(SIGSTOP, signal_sem_handler);
    rt_signal_unmask(SIGUSR1);
    rt_signal_unmask(SIGKILL);
    rt_signal_unmask(SIGSTOP);
    rt_sem_release(&_sem_signal_ready);

    if (suspend_flag == RT_INTERRUPTIBLE)
    {
        _sem_signal_result = rt_sem_take_interruptible(&_sem_signal_wait,
                                                       _sem_signal_timeout);
    }
    else if (suspend_flag == RT_KILLABLE)
    {
        _sem_signal_result = rt_sem_take_killable(&_sem_signal_wait,
                                                  _sem_signal_timeout);
    }
    else
    {
        _sem_signal_result = rt_sem_take(&_sem_signal_wait,
                                         _sem_signal_timeout);
    }

    rt_sem_release(&_sem_signal_done);
}

/* Wait until the worker thread is suspended on the semaphore. */
static rt_bool_t signal_sem_wait_until_suspended(rt_thread_t thread)
{
    rt_sched_lock_level_t slvl;
    rt_bool_t suspended;
    int count;

    for (count = 0; count < RT_TICK_PER_SECOND; count++)
    {
        rt_sched_lock(&slvl);
        suspended = ((RT_SCHED_CTX(thread).stat & RT_THREAD_SUSPEND_MASK) ==
                     RT_THREAD_SUSPEND_MASK);
        rt_sched_unlock(slvl);

        if (suspended)
        {
            return RT_TRUE;
        }

        rt_thread_mdelay(1);
    }

    return RT_FALSE;
}

/* Wait until a thread is suspended while waiting for a signal. */
static rt_bool_t signal_wait_until_signal_wait(rt_thread_t thread)
{
    rt_sched_lock_level_t slvl;
    rt_bool_t waiting;
    int count;

    for (count = 0; count < RT_TICK_PER_SECOND; count++)
    {
        rt_sched_lock(&slvl);
        waiting = ((RT_SCHED_CTX(thread).stat & RT_THREAD_SUSPEND_MASK) ==
                   RT_THREAD_SUSPEND_MASK) &&
                  ((RT_SCHED_CTX(thread).stat & RT_THREAD_STAT_SIGNAL_WAIT) != 0);
        rt_sched_unlock(slvl);

        if (waiting)
        {
            return RT_TRUE;
        }

        rt_thread_mdelay(1);
    }

    return RT_FALSE;
}

void sig_handle_default(int signo)
{
    receive_sig = signo;
}

static void rt_signal_install_test(void)
{
    int signo;
    rt_sighandler_t result;

    /* case 1:rt_signal_install, install all available signal. */
    for (signo = 0; signo < RT_SIG_MAX; signo++)
    {
        result = rt_signal_install(signo, sig_handle_default);
        uassert_true(result != SIG_ERR);
    }
    /* case 2:rt_signal_install, install illegal signal. */
    result = rt_signal_install(signo, sig_handle_default);
    uassert_true(result == SIG_ERR);

    return;
}

static void rt_signal_unmask_test(void)
{
    int signo;
    rt_sighandler_t result;

    /* case 3:rt_signal_mask/unmask, one thread self, install and unmask, then kill, should received. */
    for (signo = 0; signo < RT_SIG_MAX; signo++)
    {
        receive_sig = -1;
        result = rt_signal_install(signo, sig_handle_default);
        uassert_true(result != SIG_ERR);
        rt_signal_unmask(signo);
        uassert_int_equal(rt_thread_kill(rt_thread_self(), signo), RT_EOK);
        rt_thread_mdelay(1);
        uassert_int_equal(receive_sig, signo);
    }

    return;
}

static void rt_signal_mask_test(void)
{
    int signo;
    rt_sighandler_t result;

    /* case 4:rt_signal_mask/unmask, one thread self, install and unmask and mask, then kill, should can't received. */
    for (signo = 0; signo < RT_SIG_MAX; signo++)
    {
        receive_sig = -1;
        result = rt_signal_install(signo, sig_handle_default);
        uassert_true(result != SIG_ERR);
        rt_signal_unmask(signo);
        rt_signal_mask(signo);
        uassert_int_equal(rt_thread_kill(rt_thread_self(), signo), RT_EOK);
        rt_thread_mdelay(1);
        uassert_int_not_equal(receive_sig, signo);
        /* unmask to allow pending signal to be delivered and released */
        rt_signal_unmask(signo);
    }

    return;
}

static void rt_signal_kill_test(void)
{
    int signo;
    rt_sighandler_t result;

    /* case 7:rt_signal_kill, kill legal thread, return 0; */
    for (signo = 0; signo < RT_SIG_MAX; signo++)
    {
        receive_sig = -1;
        result = rt_signal_install(signo, sig_handle_default);
        uassert_true(result != SIG_ERR);
        rt_signal_unmask(signo);
        uassert_int_equal(rt_thread_kill(rt_thread_self(), signo), RT_EOK);
        rt_thread_mdelay(1);
        uassert_int_equal(receive_sig, signo);
    }
    /* case 8:rt_signal_kill, kill illegal thread, return failed; */
//    uassert_true(rt_thread_kill((rt_thread_t)-1, signo) == -RT_ERROR);

    /* case 9:rt_signal_kill, kill illegal signo, return -RT_EINVAL; */
    uassert_true(rt_thread_kill(rt_thread_self(), -1) == -RT_EINVAL);

    return;
}

void rt_signal_wait_thread(void *parm)
{
    rt_sigset_t selectset;
    rt_siginfo_t recive_si;
    rt_int32_t timeout;

    timeout = (rt_int32_t)(rt_ubase_t)parm;

    rt_signal_install(SIGUSR1, sig_handle_default);
    rt_signal_install(SIGUSR2, sig_handle_default);
    rt_signal_unmask(SIGUSR1);
    rt_signal_unmask(SIGUSR2);

    selectset = RT_SIG_MASK(SIGUSR1);

    /* Wait for the configured signal timeout or until SIGUSR1 is received. */
    _signal_wait_result = rt_signal_wait(&selectset, &recive_si, timeout);
    if (_signal_wait_result != RT_EOK)
    {
        rt_sem_release(&_signal_wait_done);
        return;
    }

    receive_sig = recive_si.si_signo;

    LOG_I("received signal %d", receive_sig);
    rt_sem_release(&_received_signal);
    rt_sem_release(&_signal_wait_done);
}

/* Wait for a masked signal without requiring a signal handler. */
static void rt_signal_wait_masked_thread(void *parameter)
{
    rt_sigset_t selectset;

    RT_UNUSED(parameter);
    selectset = RT_SIG_MASK(SIGUSR1);
    _signal_wait_result = rt_signal_wait(&selectset,
                                         RT_NULL,
                                         RT_WAITING_FOREVER);
    rt_sem_release(&_signal_wait_done);
}

static void rt_signal_wait_test(void)
{
    rt_thread_t t1;

    receive_sig = -1;
    t1 = rt_thread_create("sig_t1", rt_signal_wait_thread,
                          (void *)(rt_ubase_t)RT_WAITING_FOREVER,
                          4096, 14, 10);
    if (t1)
    {
        rt_thread_startup(t1);
    }

    uassert_true(t1 != RT_NULL);
    if (t1 == RT_NULL)
    {
        return;
    }
    uassert_true(signal_wait_until_signal_wait(t1));
    /* Verify that SIGUSR1 wakes a thread waiting for the signal. */
    uassert_int_equal(rt_thread_kill(t1, SIGUSR1), RT_EOK);
    rt_sem_take(&_received_signal, RT_WAITING_FOREVER);
    uassert_int_equal(rt_sem_take(&_signal_wait_done,
                                  RT_TICK_PER_SECOND),
                      RT_EOK);
    uassert_int_equal(receive_sig, SIGUSR1);
    uassert_int_equal(_signal_wait_result, RT_EOK);

    return;
}

static void rt_signal_wait_test2(void)
{
    rt_thread_t t1;

    receive_sig = -1;
    t1 = rt_thread_create("sig_t1", rt_signal_wait_thread,
                          (void *)(rt_ubase_t)RT_TICK_PER_SECOND,
                          4096, 14, 10);
    if (t1)
    {
        rt_thread_startup(t1);
    }

    /* Verify that a non-matching signal does not cancel the timed wait. */
    uassert_true(t1 != RT_NULL);
    if (t1 == RT_NULL)
    {
        return;
    }
    uassert_true(signal_wait_until_signal_wait(t1));
    uassert_int_equal(rt_thread_kill(t1, SIGUSR2), RT_EOK);
    uassert_int_equal(rt_sem_take(&_signal_wait_done,
                                  RT_TICK_PER_SECOND / 10),
                      -RT_ETIMEOUT);
    uassert_int_equal(rt_sem_take(&_signal_wait_done,
                                  2 * RT_TICK_PER_SECOND),
                      RT_EOK);
    uassert_int_equal(_signal_wait_result, -RT_ETIMEOUT);
    /* The non-matching unmasked signal is delivered after the wait returns. */
    uassert_int_equal(receive_sig, SIGUSR2);
    uassert_int_equal(rt_thread_kill(t1, SIGUSR1), RT_EOK);
    uassert_int_not_equal(
        rt_sem_take(&_received_signal, 1),
        RT_EOK);
    uassert_int_not_equal(receive_sig, SIGUSR1);

    return;
}

/* Verify that signal_wait accepts a masked signal and a NULL siginfo pointer. */
static void rt_signal_wait_masked_test(void)
{
    rt_thread_t thread;

    _signal_wait_result = -RT_ERROR;
    thread = rt_thread_create("sigmask",
                              rt_signal_wait_masked_thread,
                              RT_NULL,
                              2048,
                              UTEST_THR_PRIORITY - 1,
                              10);
    uassert_true(thread != RT_NULL);
    if (thread == RT_NULL)
    {
        return;
    }

    rt_thread_startup(thread);
    uassert_true(signal_wait_until_signal_wait(thread));
    uassert_int_equal(rt_thread_kill(thread, SIGUSR1), RT_EOK);
    uassert_int_equal(rt_sem_take(&_signal_wait_done,
                                  2 * RT_TICK_PER_SECOND),
                      RT_EOK);
    uassert_int_equal(_signal_wait_result, RT_EOK);
}

/* Wait for one signal and verify deferred signal delivery after returning. */
static void signal_wait_repeat_thread(void *parameter)
{
    rt_sigset_t selectset;
    rt_siginfo_t receive_info;
    rt_uint8_t priority;

    RT_UNUSED(parameter);
    rt_signal_install(SIGUSR1, signal_wait_repeat_handler);
    rt_signal_install(SIGUSR2, signal_wait_repeat_handler);
    rt_signal_unmask(SIGUSR1);
    rt_signal_unmask(SIGUSR2);
    selectset = RT_SIG_MASK(SIGUSR1);

    if (rt_signal_wait(&selectset, &receive_info, RT_WAITING_FOREVER) ==
        RT_EOK)
    {
        priority = UTEST_THR_PRIORITY + 1;
        rt_thread_control(rt_thread_self(),
                          RT_THREAD_CTRL_CHANGE_PRIORITY,
                          &priority);
        rt_sem_release(&_signal_wait_repeat_ready);
    }
}

/* Verify deferred non-matching signals are delivered after signal_wait returns. */
static void rt_signal_wait_repeat_test(void)
{
    rt_thread_t thread;

    _signal_wait_repeat_count = 0;
    uassert_int_equal(rt_sem_init(&_signal_wait_repeat_ready,
                                  "sigrep_r",
                                  0,
                                  RT_IPC_FLAG_PRIO),
                      RT_EOK);

    thread = rt_thread_create("sigrep",
                              signal_wait_repeat_thread,
                              RT_NULL,
                              2048,
                              UTEST_THR_PRIORITY - 1,
                              10);
    uassert_true(thread != RT_NULL);
    if (thread == RT_NULL)
    {
        goto __cleanup;
    }

    rt_thread_startup(thread);
    uassert_true(signal_wait_until_signal_wait(thread));
    uassert_int_equal(rt_thread_kill(thread, SIGUSR2), RT_EOK);
    uassert_int_equal(rt_sem_take(&_signal_wait_repeat_ready,
                                  RT_TICK_PER_SECOND / 10),
                      -RT_ETIMEOUT);
    uassert_int_equal(_signal_wait_repeat_count, 0);
    uassert_int_equal(rt_thread_kill(thread, SIGUSR1), RT_EOK);
    uassert_int_equal(rt_sem_take(&_signal_wait_repeat_ready,
                                  2 * RT_TICK_PER_SECOND),
                      RT_EOK);
    uassert_int_equal(_signal_wait_repeat_count, 1);

__cleanup:
    rt_sem_detach(&_signal_wait_repeat_ready);
}

/* Verify native signal wakeup behavior for each semaphore wait mode. */
static void signal_sem_case(int suspend_flag,
                            int signo,
                            rt_err_t expected_result,
                            rt_bool_t expect_early_wakeup,
                            rt_bool_t release_semaphore,
                            rt_int32_t timeout)
{
    rt_thread_t thread = RT_NULL;
    rt_err_t early_result;
    rt_err_t done_result;
    rt_bool_t thread_done = RT_FALSE;

    receive_sig = -1;
    _sem_signal_result = -RT_ERROR;
    _sem_signal_timeout = timeout;
    uassert_int_equal(rt_sem_init(&_sem_signal_wait,
                                  "sigsem",
                                  0,
                                  RT_IPC_FLAG_PRIO),
                      RT_EOK);
    uassert_int_equal(rt_sem_init(&_sem_signal_ready,
                                  "sigready",
                                  0,
                                  RT_IPC_FLAG_PRIO),
                      RT_EOK);
    uassert_int_equal(rt_sem_init(&_sem_signal_done,
                                  "sigd",
                                  0,
                                  RT_IPC_FLAG_PRIO),
                      RT_EOK);

    thread = rt_thread_create("sigsem_t",
                              signal_sem_wait_thread,
                              (void *)(rt_ubase_t)suspend_flag,
                              2048,
                              UTEST_THR_PRIORITY - 1,
                              10);
    uassert_true(thread != RT_NULL);
    if (thread == RT_NULL)
    {
        goto __cleanup;
    }

    if (rt_thread_startup(thread) != RT_EOK)
    {
        uassert_true(RT_FALSE);
        goto __cleanup;
    }

    if (rt_sem_take(&_sem_signal_ready,
                    2 * RT_TICK_PER_SECOND) != RT_EOK)
    {
        uassert_true(RT_FALSE);
        goto __cleanup;
    }

    if (!signal_sem_wait_until_suspended(thread))
    {
        uassert_true(RT_FALSE);
        goto __cleanup;
    }

    uassert_int_equal(rt_thread_kill(thread, signo), RT_EOK);

    early_result = rt_sem_take(
        &_sem_signal_done,
        expect_early_wakeup ? 2 * RT_TICK_PER_SECOND : RT_TICK_PER_SECOND / 20 + 1);
    uassert_int_equal(early_result,
                      expect_early_wakeup ? RT_EOK : -RT_ETIMEOUT);
    if (early_result == RT_EOK)
    {
        thread_done = RT_TRUE;
    }
    else
    {
        if (release_semaphore)
        {
            rt_sem_release(&_sem_signal_wait);
        }
        done_result = rt_sem_take(&_sem_signal_done,
                                  2 * RT_TICK_PER_SECOND);
        uassert_int_equal(done_result, RT_EOK);
        if (done_result == RT_EOK)
        {
            thread_done = RT_TRUE;
        }
    }

    LOG_I("signal sem mode=%d, result=%d, signal=%d, early=%d",
          suspend_flag,
          _sem_signal_result,
          receive_sig,
          early_result);
    uassert_int_equal(receive_sig, signo);
    uassert_int_equal(_sem_signal_result, expected_result);

__cleanup:
    if (thread != RT_NULL && !thread_done)
    {
        if (release_semaphore)
        {
            rt_sem_release(&_sem_signal_wait);
        }
        if (rt_sem_take(&_sem_signal_done,
                        2 * RT_TICK_PER_SECOND) == RT_EOK)
        {
            thread_done = RT_TRUE;
        }
    }

    /* Detach the semaphores only after the worker stops using them. */
    if (thread_done)
    {
        rt_sem_detach(&_sem_signal_wait);
        rt_sem_detach(&_sem_signal_ready);
        rt_sem_detach(&_sem_signal_done);
    }
}

/* Verify signal wakeup behavior for uninterruptible waits. */
static void rt_signal_uninterruptible_sem_test(void)
{
    signal_sem_case(RT_UNINTERRUPTIBLE,
                    SIGUSR1,
                    RT_EOK,
                    RT_FALSE,
                    RT_TRUE,
                    RT_WAITING_FOREVER);
    signal_sem_case(RT_UNINTERRUPTIBLE,
                    SIGUSR1,
                    -RT_ETIMEOUT,
                    RT_FALSE,
                    RT_FALSE,
                    10);
}

/* Verify that a normal signal interrupts an interruptible wait. */
static void rt_signal_interruptible_sem_test(void)
{
    signal_sem_case(RT_INTERRUPTIBLE,
                    SIGUSR1,
                    -RT_EINTR,
                    RT_TRUE,
                    RT_FALSE,
                    RT_WAITING_FOREVER);
}

/* Verify that a handler cannot overwrite the interrupted wait result. */
static void rt_signal_interruptible_handler_error_test(void)
{
    _signal_handler_delay = RT_TRUE;
    signal_sem_case(RT_INTERRUPTIBLE,
                    SIGUSR1,
                    -RT_EINTR,
                    RT_TRUE,
                    RT_FALSE,
                    RT_WAITING_FOREVER);
    _signal_handler_delay = RT_FALSE;
}

/* Verify that killable waits defer normal signals and accept SIGKILL. */
static void rt_signal_killable_sem_test(void)
{
    signal_sem_case(RT_KILLABLE,
                    SIGUSR1,
                    RT_EOK,
                    RT_FALSE,
                    RT_TRUE,
                    RT_WAITING_FOREVER);
    signal_sem_case(RT_KILLABLE,
                    SIGKILL,
                    -RT_EINTR,
                    RT_TRUE,
                    RT_FALSE,
                    RT_WAITING_FOREVER);
    signal_sem_case(RT_KILLABLE,
                    SIGSTOP,
                    -RT_EINTR,
                    RT_TRUE,
                    RT_FALSE,
                    RT_WAITING_FOREVER);
}

static rt_err_t utest_tc_init(void)
{
    rt_sem_init(&_received_signal, "utest", 0, RT_IPC_FLAG_PRIO);
    rt_sem_init(&_signal_wait_done, "sigwait_d", 0, RT_IPC_FLAG_PRIO);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_sem_detach(&_received_signal);
    rt_sem_detach(&_signal_wait_done);
    return RT_EOK;
}

/* Run native signal tests. */
static void testcase(void)
{
#ifdef RT_USING_HEAP
    UTEST_UNIT_RUN(rt_signal_install_test);
    UTEST_UNIT_RUN(rt_signal_mask_test);
    UTEST_UNIT_RUN(rt_signal_unmask_test);
    UTEST_UNIT_RUN(rt_signal_kill_test);
    UTEST_UNIT_RUN(rt_signal_wait_test);
    UTEST_UNIT_RUN(rt_signal_wait_masked_test);
    UTEST_UNIT_RUN(rt_signal_wait_test2);
    UTEST_UNIT_RUN(rt_signal_wait_repeat_test);
    UTEST_UNIT_RUN(rt_signal_uninterruptible_sem_test);
    UTEST_UNIT_RUN(rt_signal_interruptible_sem_test);
    UTEST_UNIT_RUN(rt_signal_interruptible_handler_error_test);
    UTEST_UNIT_RUN(rt_signal_killable_sem_test);
#endif /* RT_USING_HEAP */
}
UTEST_TC_EXPORT(testcase, "core.signal", utest_tc_init, utest_tc_cleanup, 1000);

/*********************** end of file ****************************/
