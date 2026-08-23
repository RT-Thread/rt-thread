/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-23     Bernard      POSIX record-lock coverage on tmpfs
 */

#include <rtthread.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#ifdef RT_USING_SIGNALS
#include <signal.h>
#endif

#ifdef RT_USING_SMART
#include <lwp.h>
rt_err_t sys_dup2(int oldfd, int newfd);
#endif

#include "utest.h"
#include "utest_assert.h"

#define LOCK_PATH "/tmp/record-lock-utest"
#define LOCK_PAYLOAD "0123456789abcdef"

struct lock_waiter_arg
{
    struct flock fl;
    int result;
    int err;
    rt_sem_t started;
    rt_sem_t done;
};

static void fill_lock(struct flock *fl, short type, short whence, off_t start, off_t len)
{
    rt_memset(fl, 0, sizeof(*fl));
    fl->l_type = type;
    fl->l_whence = whence;
    fl->l_start = start;
    fl->l_len = len;
}

static int set_lock(int fd, int cmd, short type, short whence, off_t start, off_t len)
{
    struct flock fl;

    fill_lock(&fl, type, whence, start, len);
    return fcntl(fd, cmd, &fl);
}

static int get_lock(int fd, struct flock *fl, short type, short whence, off_t start, off_t len)
{
    fill_lock(fl, type, whence, start, len);
    return fcntl(fd, F_GETLK, fl);
}

static int create_lock_file(void)
{
    int fd;

    unlink(LOCK_PATH);
    fd = open(LOCK_PATH, O_CREAT | O_RDWR | O_TRUNC, 0666);
    uassert_true(fd >= 0);
    uassert_int_equal(write(fd, LOCK_PAYLOAD, sizeof(LOCK_PAYLOAD) - 1),
                      sizeof(LOCK_PAYLOAD) - 1);
    uassert_int_equal(lseek(fd, 0, SEEK_SET), 0);
    return fd;
}

#ifdef RT_USING_SMART
static struct rt_lwp *bind_owner(void)
{
    struct rt_lwp *lwp = lwp_create(LWP_CREATE_FLAG_ALLOC_PID);

    uassert_not_null(lwp);
    rt_thread_self()->lwp = lwp;
    return lwp;
}

static void unbind_owner(struct rt_lwp *lwp)
{
    rt_thread_self()->lwp = RT_NULL;
    if (lwp)
    {
        /* Drop create() + pid-table references; leftover pid slots are test-only. */
        lwp_ref_dec(lwp);
        lwp_ref_dec(lwp);
    }
}
#endif

static void test_positive_negative_len(void)
{
    int fd = create_lock_file();
    struct flock fl;

    uassert_int_equal(set_lock(fd, F_SETLK, F_WRLCK, SEEK_SET, 0, 4), 0);
    uassert_int_equal(get_lock(fd, &fl, F_WRLCK, SEEK_SET, 0, 4), 0);
    uassert_int_equal(fl.l_type, F_UNLCK);

    uassert_int_equal(set_lock(fd, F_SETLK, F_UNLCK, SEEK_SET, 4, -4), 0);
    uassert_int_equal(set_lock(fd, F_SETLK, F_RDLCK, SEEK_SET, 8, -4), 0);
    uassert_int_equal(set_lock(fd, F_SETLK, F_UNLCK, SEEK_SET, 0, 0), 0);
    uassert_int_equal(close(fd), 0);
    uassert_int_equal(unlink(LOCK_PATH), 0);
}

static void test_conflict_and_getlk(void)
{
#ifdef RT_USING_SMART
    int fd_a;
    int fd_b;
    struct flock fl;
    struct rt_lwp *owner_a;
    struct rt_lwp *owner_b;

    owner_a = bind_owner();
    fd_a = create_lock_file();
    uassert_int_equal(set_lock(fd_a, F_SETLK, F_WRLCK, SEEK_SET, 0, 8), 0);

    owner_b = lwp_create(LWP_CREATE_FLAG_ALLOC_PID);
    uassert_not_null(owner_b);
    rt_thread_self()->lwp = owner_b;
    fd_b = open(LOCK_PATH, O_RDWR, 0);
    uassert_true(fd_b >= 0);

    errno = 0;
    uassert_int_equal(set_lock(fd_b, F_SETLK, F_RDLCK, SEEK_SET, 0, 4), -1);
    uassert_int_equal(errno, -EAGAIN);

    uassert_int_equal(get_lock(fd_b, &fl, F_WRLCK, SEEK_SET, 0, 4), 0);
    uassert_int_equal(fl.l_type, F_WRLCK);
    uassert_int_equal(fl.l_whence, SEEK_SET);
    uassert_int_equal(fl.l_start, 0);
    uassert_int_equal(fl.l_len, 8);
    uassert_int_equal(fl.l_pid, owner_a->pid);

    rt_thread_self()->lwp = owner_a;
    uassert_int_equal(set_lock(fd_a, F_SETLK, F_UNLCK, SEEK_SET, 0, 0), 0);

    rt_thread_self()->lwp = owner_b;
    uassert_int_equal(set_lock(fd_b, F_SETLK, F_RDLCK, SEEK_SET, 0, 4), 0);
    uassert_int_equal(set_lock(fd_b, F_SETLK, F_UNLCK, SEEK_SET, 0, 0), 0);
    uassert_int_equal(close(fd_b), 0);

    rt_thread_self()->lwp = owner_a;
    uassert_int_equal(close(fd_a), 0);
    unbind_owner(owner_a);
    unbind_owner(owner_b);
    uassert_int_equal(unlink(LOCK_PATH), 0);
#else
    uassert_true(1);
#endif
}

static void waiter_entry(void *parameter)
{
    struct lock_waiter_arg *arg = (struct lock_waiter_arg *)parameter;
    int fd;
#ifdef RT_USING_SMART
    struct rt_lwp *owner = bind_owner();
#endif

#ifdef RT_USING_SIGNALS
    rt_signal_install(SIGUSR1, RT_NULL);
    rt_signal_unmask(SIGUSR1);
#endif
    fd = open(LOCK_PATH, O_RDWR, 0);
    if (fd < 0)
    {
        arg->result = -1;
        arg->err = errno;
        rt_sem_release(arg->started);
        rt_sem_release(arg->done);
#ifdef RT_USING_SMART
        unbind_owner(owner);
#endif
        return;
    }

    rt_sem_release(arg->started);
    arg->result = fcntl(fd, F_SETLKW, &arg->fl);
    arg->err = errno;
    close(fd);
#ifdef RT_USING_SMART
    unbind_owner(owner);
#endif
    rt_sem_release(arg->done);
}

static void test_interrupted_setlkw(void)
{
#if defined(RT_USING_SMART) && defined(RT_USING_SIGNALS)
    int fd_a;
    rt_thread_t waiter;
    struct lock_waiter_arg arg;
    struct rt_semaphore started;
    struct rt_semaphore done;
    struct rt_lwp *owner;

    owner = bind_owner();
    fd_a = create_lock_file();
    uassert_int_equal(set_lock(fd_a, F_SETLK, F_WRLCK, SEEK_SET, 0, 4), 0);

    rt_sem_init(&started, "rlks", 0, RT_IPC_FLAG_FIFO);
    rt_sem_init(&done, "rlkw", 0, RT_IPC_FLAG_FIFO);
    fill_lock(&arg.fl, F_WRLCK, SEEK_SET, 0, 4);
    arg.result = 0;
    arg.err = 0;
    arg.started = &started;
    arg.done = &done;

    waiter = rt_thread_create("rlkw", waiter_entry, &arg, 4096,
                              RT_SCHED_PRIV(rt_thread_self()).current_priority + 1, 10);
    uassert_not_null(waiter);
    rt_thread_startup(waiter);
    uassert_int_equal(rt_sem_take(&started, RT_TICK_PER_SECOND), RT_EOK);
    rt_thread_mdelay(10);
    uassert_int_equal(rt_thread_kill(waiter, SIGUSR1), RT_EOK);
    uassert_int_equal(rt_sem_take(&done, RT_TICK_PER_SECOND), RT_EOK);
    uassert_int_equal(arg.result, -1);
    uassert_int_equal(arg.err, -EINTR);

    uassert_int_equal(set_lock(fd_a, F_SETLK, F_UNLCK, SEEK_SET, 0, 0), 0);
    uassert_int_equal(close(fd_a), 0);
    unbind_owner(owner);
    rt_sem_detach(&started);
    rt_sem_detach(&done);
    uassert_int_equal(unlink(LOCK_PATH), 0);
#else
    uassert_true(1);
#endif
}

static void test_split_merge(void)
{
    int fd = create_lock_file();
    struct flock fl;

    uassert_int_equal(set_lock(fd, F_SETLK, F_WRLCK, SEEK_SET, 0, 16), 0);
    uassert_int_equal(set_lock(fd, F_SETLK, F_UNLCK, SEEK_SET, 4, 4), 0);
    uassert_int_equal(set_lock(fd, F_SETLK, F_WRLCK, SEEK_SET, 4, 4), 0);

    uassert_int_equal(get_lock(fd, &fl, F_WRLCK, SEEK_SET, 0, 16), 0);
    uassert_int_equal(fl.l_type, F_UNLCK);

    uassert_int_equal(set_lock(fd, F_SETLK, F_UNLCK, SEEK_SET, 0, 0), 0);
    uassert_int_equal(close(fd), 0);
    uassert_int_equal(unlink(LOCK_PATH), 0);
}

static void test_close_and_dup_release(void)
{
#ifdef RT_USING_SMART
    int fd_a;
    int fd_b;
    int fd_replace;
    struct flock fl;
    struct rt_lwp *owner_a;
    struct rt_lwp *owner_b;

    owner_a = bind_owner();
    fd_a = create_lock_file();
    uassert_int_equal(set_lock(fd_a, F_SETLK, F_WRLCK, SEEK_SET, 0, 8), 0);

    owner_b = lwp_create(LWP_CREATE_FLAG_ALLOC_PID);
    uassert_not_null(owner_b);
    rt_thread_self()->lwp = owner_b;
    fd_b = open(LOCK_PATH, O_RDWR, 0);
    uassert_true(fd_b >= 0);
    uassert_int_equal(set_lock(fd_b, F_SETLK, F_RDLCK, SEEK_SET, 0, 8), -1);

    rt_thread_self()->lwp = owner_a;
    uassert_int_equal(close(fd_a), 0);

    rt_thread_self()->lwp = owner_b;
    uassert_int_equal(set_lock(fd_b, F_SETLK, F_WRLCK, SEEK_SET, 0, 8), 0);

    rt_thread_self()->lwp = owner_a;
    fd_a = open(LOCK_PATH, O_RDWR, 0);
    uassert_true(fd_a >= 0);
    uassert_int_equal(set_lock(fd_a, F_SETLK, F_WRLCK, SEEK_SET, 0, 8), -1);

    rt_thread_self()->lwp = owner_b;
    fd_replace = open(LOCK_PATH, O_RDWR, 0);
    uassert_true(fd_replace >= 0);
    uassert_int_equal(sys_dup2(fd_replace, fd_b), fd_b);

    rt_thread_self()->lwp = owner_a;
    uassert_int_equal(set_lock(fd_a, F_SETLK, F_WRLCK, SEEK_SET, 0, 8), 0);
    uassert_int_equal(get_lock(fd_a, &fl, F_WRLCK, SEEK_SET, 0, 8), 0);
    uassert_int_equal(fl.l_type, F_UNLCK);

    uassert_int_equal(close(fd_a), 0);
    rt_thread_self()->lwp = owner_b;
    uassert_int_equal(close(fd_b), 0);
    uassert_int_equal(close(fd_replace), 0);

    unbind_owner(owner_a);
    unbind_owner(owner_b);
    uassert_int_equal(unlink(LOCK_PATH), 0);
#else
    int fd = create_lock_file();

    uassert_int_equal(set_lock(fd, F_SETLK, F_WRLCK, SEEK_SET, 0, 8), 0);
    uassert_int_equal(close(fd), 0);
    fd = open(LOCK_PATH, O_RDWR, 0);
    uassert_true(fd >= 0);
    uassert_int_equal(set_lock(fd, F_SETLK, F_WRLCK, SEEK_SET, 0, 8), 0);
    uassert_int_equal(close(fd), 0);
    uassert_int_equal(unlink(LOCK_PATH), 0);
#endif
}

static rt_err_t utest_tc_init(void)
{
    unlink(LOCK_PATH);
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    unlink(LOCK_PATH);
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_positive_negative_len);
    UTEST_UNIT_RUN(test_conflict_and_getlk);
    UTEST_UNIT_RUN(test_interrupted_setlkw);
    UTEST_UNIT_RUN(test_split_merge);
    UTEST_UNIT_RUN(test_close_and_dup_release);
}
UTEST_TC_EXPORT(testcase, "components.dfs.record_lock", utest_tc_init, utest_tc_cleanup, 30);
