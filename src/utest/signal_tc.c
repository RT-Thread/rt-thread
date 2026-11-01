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
 * case 10:rt_signal_kill, a thread blocked in rt_thread_mdelay() receives a signal
 *         from another thread, should be woken up and run its handler.
 * case 11:rt_signal_kill, the same thread but with the signal masked, should not run
 *         the handler and should only wake up when its delay expires.
 * case 12:rt_signal_kill, masked again but the sending thread is scheduled late, the
 *         verdict must stay the same because the delay is measured inside the worker.
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
static struct rt_semaphore _worker_ready;
static struct rt_semaphore _worker_exit;
static struct rt_semaphore _worker_done;

#ifdef RT_USING_MUSLLIBC
#define UTEST_SIGNAL_MIN 1
#else
#define UTEST_SIGNAL_MIN 0
#endif

void sig_handle_default(int signo)
{
    receive_sig = signo;
}

static void rt_signal_install_test(void)
{
    int signo;
    rt_sighandler_t result;

    /* case 1:rt_signal_install, install all available signal. */
    for (signo = UTEST_SIGNAL_MIN; signo < RT_SIG_MAX; signo++)
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
    for (signo = UTEST_SIGNAL_MIN; signo < RT_SIG_MAX; signo++)
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
    for (signo = UTEST_SIGNAL_MIN; signo < RT_SIG_MAX; signo++)
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
    for (signo = UTEST_SIGNAL_MIN; signo < RT_SIG_MAX; signo++)
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
    sigset_t selectset;
    siginfo_t recive_si;

    rt_signal_install(SIGUSR1, sig_handle_default);
    rt_signal_unmask(SIGUSR1);

    (void)sigemptyset(&selectset);
    (void)sigaddset(&selectset, SIGUSR1);

    /* case 5:rt_signal_wait, two thread, thread1: install and unmask, then wait 1s; thread2: kill, should received. */
    if (rt_signal_wait((void *)&selectset, &recive_si, RT_TICK_PER_SECOND) != RT_EOK)
    {
        return;
    }

    receive_sig = recive_si.si_signo;

    LOG_I("received signal %d", receive_sig);
    rt_sem_release(&_received_signal);
}

static void rt_signal_wait_test(void)
{
    rt_thread_t t1;

    receive_sig = -1;
    t1 = rt_thread_create("sig_t1", rt_signal_wait_thread, 0, 4096, 14, 10);
    if (t1)
    {
        rt_thread_startup(t1);
    }

    rt_thread_mdelay(1);
    /* case 5:rt_signal_wait, two thread, thread1: install and unmask, then wait 1s; thread2: kill, should received. */
    uassert_int_equal(rt_thread_kill(t1, SIGUSR1), RT_EOK);
    rt_sem_take(&_received_signal, RT_WAITING_FOREVER);
    uassert_int_equal(receive_sig, SIGUSR1);

    return;
}

static void rt_signal_wait_test2(void)
{
    rt_thread_t t1;

    receive_sig = -1;
    t1 = rt_thread_create("sig_t1", rt_signal_wait_thread, 0, 4096, 14, 10);
    if (t1)
    {
        rt_thread_startup(t1);
    }

    /* case 6:rt_signal_wait, two thread, thread1: install and unmask, then wait 1s; thread2: sleep 2s then kill, should can't received. */
    rt_thread_mdelay(2000);
    uassert_int_equal(rt_thread_kill(t1, SIGUSR1), RT_EOK);
    uassert_int_not_equal(
        rt_sem_take(&_received_signal, 1),
        RT_EOK);
    uassert_int_not_equal(receive_sig, SIGUSR1);

    return;
}

static rt_bool_t signal_masked;
static volatile rt_tick_t delay_start_tick;
static volatile rt_tick_t delay_end_tick;
static rt_thread_t delay_worker;
static rt_bool_t worker_pending;

static void rt_signal_delay_thread(void *parm)
{
    rt_signal_install(SIGUSR1, sig_handle_default);
    rt_signal_unmask(SIGUSR1);

    if (signal_masked)
    {
        /* keep the signal pending: the handler must not run, the delay expires */
        rt_signal_mask(SIGUSR1);
    }

    /* The delay window is measured inside the worker. Measuring it from the test
     * thread would already miss the time spent before the signal was sent, which
     * makes the expected value depend on the tick frequency. */
    delay_start_tick = rt_tick_get();
    rt_sem_release(&_worker_ready);

    /* blocked here until a signal wakes this thread up, or the delay expires */
    rt_thread_mdelay(1000);
    delay_end_tick = rt_tick_get();

    rt_sem_release(&_received_signal);

    /* Stay alive until the testcase is done, so rt_thread_kill() never targets an
     * already deleted thread and both semaphores stay valid. */
    rt_sem_take(&_worker_exit, RT_WAITING_FOREVER);

    /* Last access to the shared state: the test waits for this before it detaches
     * anything, so a worker that finishes late can never touch a destroyed object. */
    rt_sem_release(&_worker_done);
}

/* Unified finalization of one case: let the worker leave, wait until it has really
 * passed the delay and the exit handshake, then drop notifications that arrived after a
 * wait had already timed out. Returns RT_TRUE only when the worker acknowledged. */
static rt_bool_t rt_signal_delay_finish(void)
{
    rt_bool_t acked;

    /* Releasing _worker_exit only permits the exit; the acknowledgement is what proves
     * the worker no longer touches the shared objects. */
    rt_sem_release(&_worker_exit);
    acked = (rt_sem_take(&_worker_done, rt_tick_from_millisecond(5000)) == RT_EOK) ? RT_TRUE : RT_FALSE;

    /* A late ready/completion notification would otherwise be consumed by the next case
     * as if it belonged to that case's worker. */
    while (rt_sem_take(&_received_signal, 0) == RT_EOK)
    {
    }
    while (rt_sem_take(&_worker_ready, 0) == RT_EOK)
    {
    }

    if (acked == RT_TRUE)
    {
        worker_pending = RT_FALSE;
        delay_worker = RT_NULL;
    }

    return acked;
}

static rt_bool_t rt_signal_delay_wait(rt_bool_t masked, rt_int32_t send_delay_ms)
{
    rt_thread_t t1;
    rt_err_t ready_result;
    rt_err_t result = -RT_ETIMEOUT;
    rt_tick_t full_delay;
    rt_tick_t margin;
    rt_tick_t elapsed;

    receive_sig = -1;
    signal_masked = masked;
    delay_start_tick = 0;
    delay_end_tick = 0;

    t1 = rt_thread_create("sig_t2", rt_signal_delay_thread, 0, 4096, 14, 10);
    if (t1 == RT_NULL)
    {
        /* uassert_true() only records the failure, it does not return, so bail out
         * here instead of starting a thread that does not exist */
        uassert_true(t1 != RT_NULL);
        return RT_FALSE;
    }
    rt_thread_startup(t1);
    delay_worker = t1;
    worker_pending = RT_TRUE;

    /* explicit handshake: the worker is inside the delay now, no fixed guess */
    ready_result = rt_sem_take(&_worker_ready, rt_tick_from_millisecond(1000));
    uassert_int_equal(ready_result, RT_EOK);

    if (ready_result == RT_EOK)
    {
        /* Defensive yield: with the default UTEST_THR_PRIORITY (20) the worker (14) enters
         * rt_thread_mdelay() before this thread runs, but a BSP that raises the utest
         * priority above the worker could send the signal first. One tick is enough for the
         * worker to reach the delay, and it does not affect the verdict because the delay
         * window is measured inside the worker. */
        rt_thread_mdelay(1);

        if (send_delay_ms > 0)
        {
            /* the sending thread may be scheduled late: the verdict must not change */
            rt_thread_mdelay(send_delay_ms);
        }

        uassert_int_equal(rt_thread_kill(t1, SIGUSR1), RT_EOK);

        /* rt_sem_take() takes ticks, so convert the timeout explicitly */
        result = rt_sem_take(&_received_signal, rt_tick_from_millisecond(3000));
        uassert_int_equal(result, RT_EOK);
    }

    elapsed = delay_end_tick - delay_start_tick;
    full_delay = rt_tick_from_millisecond(1000);
    margin = rt_tick_from_millisecond(100);

    uassert_true(delay_end_tick != 0);

    /* Without the end tick the difference above is meaningless (it underflows), so the
     * timing checks only run when the worker really reported both ends of the delay. */
    if (delay_end_tick != 0 && ready_result == RT_EOK && result == RT_EOK)
    {
        if (masked)
        {
            /* the signal stays pending: no handler call, the whole delay must elapse */
            uassert_int_not_equal(receive_sig, SIGUSR1);
            uassert_true(elapsed + margin >= full_delay);
            uassert_true(elapsed <= full_delay + margin);
        }
        else
        {
            /* delivered: the handler ran in that thread and it woke up well before
             * the 1 s delay expired */
            uassert_int_equal(receive_sig, SIGUSR1);
            uassert_true(elapsed + margin < full_delay);
        }
    }

    /* One shared finalization for the normal path and for every failure path. When the
     * worker cannot be confirmed the caller must not start another case on top of the
     * same semaphores. */
    if (rt_signal_delay_finish() != RT_TRUE)
    {
        uassert_true(RT_FALSE);
        return RT_FALSE;
    }

    return (ready_result == RT_EOK && result == RT_EOK) ? RT_TRUE : RT_FALSE;
}

static void rt_signal_delay_thread_test(void)
{
    /* case 10: signal delivered to a thread blocked in rt_thread_mdelay() */
    if (rt_signal_delay_wait(RT_FALSE, 0) != RT_TRUE)
    {
        return;
    }
    /* case 11: signal masked, the thread must only wake up when the delay expires */
    if (rt_signal_delay_wait(RT_TRUE, 0) != RT_TRUE)
    {
        return;
    }
    /* case 12: masked again, but the sending thread is scheduled late: the verdict
     * must stay the same, which is what the in-worker timing guarantees */
    rt_signal_delay_wait(RT_TRUE, 450);
}

static rt_err_t utest_tc_init(void)
{
    rt_sem_init(&_received_signal, "utest", 0, RT_IPC_FLAG_PRIO);
    rt_sem_init(&_worker_ready, "uwork", 0, RT_IPC_FLAG_PRIO);
    rt_sem_init(&_worker_exit, "uexit", 0, RT_IPC_FLAG_PRIO);
    rt_sem_init(&_worker_done, "udone", 0, RT_IPC_FLAG_PRIO);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    if (worker_pending == RT_TRUE)
    {
        /* A worker that its case could not confirm is still alive and may touch the
         * semaphores. Give it one last bounded chance, then remove it, so nothing is
         * detached underneath a thread that is still running. */
        if (rt_sem_take(&_worker_done, rt_tick_from_millisecond(20000)) != RT_EOK)
        {
#ifdef RT_USING_HEAP
            if (delay_worker != RT_NULL)
            {
                rt_thread_delete(delay_worker);
                rt_thread_mdelay(2);
            }
#endif
        }

        while (rt_sem_take(&_received_signal, 0) == RT_EOK)
        {
        }
        while (rt_sem_take(&_worker_ready, 0) == RT_EOK)
        {
        }

        delay_worker = RT_NULL;
        worker_pending = RT_FALSE;
    }

    rt_sem_detach(&_received_signal);
    rt_sem_detach(&_worker_ready);
    rt_sem_detach(&_worker_exit);
    rt_sem_detach(&_worker_done);
    return RT_EOK;
}

static void testcase(void)
{
#ifdef RT_USING_HEAP
    UTEST_UNIT_RUN(rt_signal_install_test);
    UTEST_UNIT_RUN(rt_signal_mask_test);
    UTEST_UNIT_RUN(rt_signal_unmask_test);
    UTEST_UNIT_RUN(rt_signal_kill_test);
    UTEST_UNIT_RUN(rt_signal_wait_test);
    UTEST_UNIT_RUN(rt_signal_wait_test2);
    UTEST_UNIT_RUN(rt_signal_delay_thread_test);
#endif /* RT_USING_HEAP */
}
UTEST_TC_EXPORT(testcase, "core.signal", utest_tc_init, utest_tc_cleanup, 1000);

/*********************** end of file ****************************/
