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
 */

#include <rtthread.h>
#include "utest.h"

static volatile int recive_sig = 0;
static struct rt_semaphore _received_signal;

void sig_handle_default(int signo)
{
    recive_sig = signo;
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

static void rt_signal_mask_test(void)
{
    int signo;
    rt_sighandler_t result;

    /* case 3:rt_signal_mask/unmask, one thread self, install and unmask, then kill, should received. */
    for (signo = 0; signo < RT_SIG_MAX; signo++)
    {
        recive_sig = -1;
        result = rt_signal_install(signo, sig_handle_default);
        uassert_true(result != SIG_ERR);
        rt_signal_unmask(signo);
        uassert_int_equal(rt_thread_kill(rt_thread_self(), signo), RT_EOK);
        rt_thread_mdelay(1);
        uassert_int_equal(recive_sig, signo);
    }

    return;
}

static void rt_signal_unmask_test(void)
{
    int signo;
    rt_sighandler_t result;

    /* case 4:rt_signal_mask/unmask, one thread self, install and unmask and mask, then kill, should can't received. */
    for (signo = 0; signo < RT_SIG_MAX; signo++)
    {
        recive_sig = -1;
        result = rt_signal_install(signo, sig_handle_default);
        uassert_true(result != SIG_ERR);
        rt_signal_unmask(signo);
        rt_signal_mask(signo);
        uassert_int_equal(rt_thread_kill(rt_thread_self(), signo), RT_EOK);
        rt_thread_mdelay(1);
        uassert_int_not_equal(recive_sig, signo);
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
        recive_sig = -1;
        result = rt_signal_install(signo, sig_handle_default);
        uassert_true(result != SIG_ERR);
        rt_signal_unmask(signo);
        uassert_int_equal(rt_thread_kill(rt_thread_self(), signo), RT_EOK);
        rt_thread_mdelay(1);
        uassert_int_equal(recive_sig, signo);
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

    recive_sig = recive_si.si_signo;

    LOG_I("received signal %d", recive_sig);
    rt_sem_release(&_received_signal);
}

static void rt_signal_wait_test(void)
{
    rt_thread_t t1;

    recive_sig = -1;
    t1 = rt_thread_create("sig_t1", rt_signal_wait_thread, 0, 4096, 14, 10);
    if (t1)
    {
        rt_thread_startup(t1);
    }

    rt_thread_mdelay(1);
    /* case 5:rt_signal_wait, two thread, thread1: install and unmask, then wait 1s; thread2: kill, should received. */
    uassert_int_equal(rt_thread_kill(t1, SIGUSR1), RT_EOK);
    rt_sem_take(&_received_signal, RT_WAITING_FOREVER);
    uassert_int_equal(recive_sig, SIGUSR1);

    return;
}

static void rt_signal_wait_test2(void)
{
    rt_thread_t t1;

    recive_sig = -1;
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
    uassert_int_not_equal(recive_sig, SIGUSR1);

    return;
}

static rt_err_t utest_tc_init(void)
{
    rt_sem_init(&_received_signal, "utest", 0, RT_IPC_FLAG_PRIO);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_sem_detach(&_received_signal);
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
#endif /* RT_USING_HEAP */
}
UTEST_TC_EXPORT(testcase, "testcases.kernel.signal_tc", utest_tc_init, utest_tc_cleanup, 1000);

/*********************** end of file ****************************/
