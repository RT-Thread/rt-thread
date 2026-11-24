/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-10-17     Yaodong Han  boundary regression tests for devtmpfs path
 *                             components (devtmpfs_create_vnode/_path_separate
 *                             and devtmpfs_file_lookup/_get_subdir)
 * 2026-11-24     Yaodong Han  prove the creation path with O_EXCL, keep nodes
 *                             that were already there, clean up on every exit
 *                             path, collect the result of all lengths in a
 *                             single test unit, and run the filesystem calls
 *                             on a thread whose stack fits devtmpfs frames
 */

#include <rtthread.h>
#include "utest.h"

#include <fcntl.h>
#include <dfs_file.h>
#include <dfs.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef RT_USING_DFS_V2

/*
 * The devtmpfs helpers copy the last path component into char[DIRENT_NAME_MAX]
 * buffers, so a component of DIRENT_NAME_MAX bytes or more must be rejected
 * instead of overrunning the caller's stack frame. A component of
 * DIRENT_NAME_MAX - 1 bytes (plus the terminator) still fits.
 */
#define TC_NAME_MAX DIRENT_NAME_MAX

/* devtmpfs is mounted on /dev by the device filesystem, see devtmpfs_init() */
#define TC_MNT_PATH "/dev"

/*
 * Path buffer: mount point + '/' + component + '\0'.
 * Sized for the longest component the boundary sweep below uses (300 bytes),
 * which is deliberately well past DIRENT_NAME_MAX. It is static so that it
 * never lands on the calling thread's stack.
 */
#define TC_MAX_TEST_LEN  300
#define TC_PATH_BUF_SIZE (sizeof(TC_MNT_PATH) + 1 + TC_MAX_TEST_LEN + 1)

static char tc_path[TC_PATH_BUF_SIZE];

/*
 * devtmpfs_create_vnode() keeps parent_path[DFS_PATH_MAX] and
 * file_name[DIRENT_NAME_MAX] on its own frame - 4352 bytes before anything
 * else is accounted for. The utest framework runs test cases on a 4096 byte
 * thread, which cannot hold that frame, so every filesystem call below is
 * issued from a worker thread with a stack large enough for it.
 */
#define TC_WORKER_STACK_SIZE 8192

/* a fixed priority would trip the range check on kernels with few levels */
#define TC_WORKER_PRIORITY (RT_THREAD_PRIORITY_MAX / 2)

/* give up if the worker has not finished within this many milliseconds */
#define TC_WORKER_TIMEOUT_MS 5000

/* every length is exercised twice, to prove the state is clean between rounds */
#define TC_ROUNDS 2

/* rotating job slots, see tc_run_once() */
#define TC_JOB_SLOTS 4

/*
 * Caller-side stack guard. devtmpfs_create_vnode() and devtmpfs_file_lookup()
 * keep their file_name[]/subdir_name[] buffers on their own frames; if the
 * component were copied without a bounds check those frames - and the data
 * that survives in the caller after the call - would be corrupted. Keeping a
 * known pattern around the call and checking it afterwards is the observable
 * "does not modify neighbouring stack data" assertion requested in review.
 */
#define TC_GUARD_SIZE    32
#define TC_GUARD_PATTERN 0xA5
#define TC_GUARD_MAGIC   0x5A5A1234UL

static volatile rt_ubase_t tc_guard_magic;

static void tc_guard_fill(rt_uint8_t *guard)
{
    rt_memset(guard, TC_GUARD_PATTERN, TC_GUARD_SIZE);
    tc_guard_magic = TC_GUARD_MAGIC;
}

static rt_bool_t tc_guard_intact(const rt_uint8_t *guard)
{
    rt_size_t i;

    if (tc_guard_magic != TC_GUARD_MAGIC)
    {
        return RT_FALSE;
    }

    for (i = 0; i < TC_GUARD_SIZE; i++)
    {
        if (guard[i] != TC_GUARD_PATTERN)
        {
            return RT_FALSE;
        }
    }

    return RT_TRUE;
}

/*
 * Build "<mnt>/<len x 'A'>" into tc_path and return its length.
 * The mount point is fixed to /dev (TC_MNT_PATH) because devtmpfs is always
 * mounted there by devtmpfs_init(); RT_UTEST_DFS_MNT_PATH selects where the
 * generic DFS API tests mount their own filesystem and does not apply here.
 */
static rt_size_t tc_build_path(rt_size_t len)
{
    rt_size_t mnt_len = rt_strlen(TC_MNT_PATH);
    rt_size_t i;

    RT_ASSERT(len <= TC_MAX_TEST_LEN);

    rt_memcpy(tc_path, TC_MNT_PATH, mnt_len);
    tc_path[mnt_len] = '/';
    for (i = 0; i < len; i++)
    {
        tc_path[mnt_len + 1 + i] = 'A';
    }
    tc_path[mnt_len + 1 + len] = '\0';

    return mnt_len + 1 + len;
}

struct tc_case
{
    rt_size_t len;
    rt_bool_t expect_ok;
    const char *label;
};

static const struct tc_case tc_cases[] = {
    { 8, RT_TRUE, "short component" },
    { TC_NAME_MAX - 2, RT_TRUE, "254 byte component" },
    { TC_NAME_MAX - 1, RT_TRUE, "255 byte component" },
    { TC_NAME_MAX, RT_FALSE, "256 byte component" },
    { TC_NAME_MAX + 44, RT_FALSE, "300 byte component" },
};

/*
 * Exercise both entry points for one component length and one round:
 *   - devtmpfs_file_lookup()  through dfs_file_stat()
 *   - devtmpfs_create_vnode() through open(O_CREAT | O_EXCL)
 *
 * O_EXCL is what makes a round meaningful: without it open() would reopen a
 * node left behind and the creation path would never run again. A node that
 * already exists is deliberately left alone - the exclusive create reports it
 * and the test fails, instead of removing somebody else's node. The node this
 * round created is recorded in `created` and removed again on every exit path.
 *
 * Returns 0 on success, a negative code otherwise.
 */
static int tc_roundtrip(rt_size_t len, rt_bool_t expect_ok)
{
    rt_uint8_t guard[TC_GUARD_SIZE];
    struct stat st;
    rt_bool_t created = RT_FALSE;
    int fd = -1;
    int ret = 0;

    tc_build_path(len);

    tc_guard_fill(guard);

    /* lookup path first: the node does not exist yet, this must not crash */
    (void)dfs_file_stat(tc_path, &st);

    fd = open(tc_path, O_CREAT | O_EXCL | O_RDWR, 0644);

    if (!tc_guard_intact(guard))
    {
        rt_kprintf("len %u: stack guard corrupted by open()\n", (unsigned int)len);
        ret = -2;
        goto out;
    }

    if (expect_ok)
    {
        if (fd < 0)
        {
            rt_kprintf("len %u: expected creation, open() returned %d; a node "
                       "that already exists is not removed by this test\n",
                       (unsigned int)len, fd);
            ret = -3;
            goto out;
        }

        created = RT_TRUE;
        close(fd);
        fd = -1;

        /* the node must now be visible through the lookup path */
        tc_guard_fill(guard);
        if (dfs_file_stat(tc_path, &st) != 0)
        {
            rt_kprintf("len %u: node not found after creation\n", (unsigned int)len);
            ret = -4;
            goto out;
        }

        if (!tc_guard_intact(guard))
        {
            rt_kprintf("len %u: stack guard corrupted by lookup\n", (unsigned int)len);
            ret = -2;
            goto out;
        }
    }
    else
    {
        if (fd >= 0)
        {
            /* an overlong component must never create anything */
            created = RT_TRUE;
            close(fd);
            fd = -1;
            rt_kprintf("len %u: expected rejection, open() succeeded\n",
                       (unsigned int)len);
            ret = -5;
            goto out;
        }

        tc_guard_fill(guard);
        if (dfs_file_stat(tc_path, &st) == 0)
        {
            rt_kprintf("len %u: overlong component still resolved\n",
                       (unsigned int)len);
            ret = -6;
            goto out;
        }

        if (!tc_guard_intact(guard))
        {
            rt_kprintf("len %u: stack guard corrupted by lookup\n", (unsigned int)len);
            ret = -2;
            goto out;
        }
    }

out:
    /* single exit: always close the descriptor, and remove only the node this
     * round created - also when a later check already failed */
    if (fd >= 0)
    {
        close(fd);
    }

    if (created)
    {
        if (unlink(tc_path) != 0)
        {
            rt_kprintf("len %u: cannot remove the node created by this round\n",
                       (unsigned int)len);
            if (ret == 0)
            {
                ret = -7;
            }
        }
        else if (dfs_file_stat(tc_path, &st) == 0)
        {
            rt_kprintf("len %u: node still present after unlink\n", (unsigned int)len);
            if (ret == 0)
            {
                ret = -8;
            }
        }
    }

    return ret;
}

struct tc_job
{
    rt_size_t len;
    rt_bool_t expect_ok;
    rt_bool_t finished;
    int result;
};

static struct tc_job tc_jobs[TC_JOB_SLOTS];
static rt_uint32_t tc_job_seq;

static void tc_worker_entry(void *parameter)
{
    struct tc_job *job = (struct tc_job *)parameter;

    job->result = tc_roundtrip(job->len, job->expect_ok);
    job->finished = RT_TRUE;
}

/* run one round on a worker thread with room for devtmpfs' stack frames */
static int tc_run_once(rt_size_t len, rt_bool_t expect_ok)
{
    struct tc_job *job = &tc_jobs[tc_job_seq % TC_JOB_SLOTS];
    rt_thread_t tid;
    rt_int32_t waited = 0;

    /*
     * Every round takes its own slot, so a worker that overruns its timeout
     * cannot write into the result of a later round.
     */
    tc_job_seq++;

    job->len = len;
    job->expect_ok = expect_ok;
    job->finished = RT_FALSE;
    job->result = -100;

    tid = rt_thread_create("dtfstc", tc_worker_entry, job,
                           TC_WORKER_STACK_SIZE, TC_WORKER_PRIORITY, 10);
    if (tid == RT_NULL)
    {
        rt_kprintf("cannot create a worker thread with a %d byte stack\n",
                   TC_WORKER_STACK_SIZE);
        return -100;
    }

    rt_thread_startup(tid);

    while (job->finished != RT_TRUE && waited < TC_WORKER_TIMEOUT_MS)
    {
        rt_thread_mdelay(1);
        waited++;
    }

    if (job->finished != RT_TRUE)
    {
        rt_kprintf("worker did not finish within %d ms\n", TC_WORKER_TIMEOUT_MS);
        return -101;
    }

    /* the worker returns from its entry, so rt_thread_exit() puts it on the
     * defunct list and the idle thread reclaims it; nothing to delete here */

    return job->result;
}

/*
 * All component lengths are checked inside a single test unit: the utest
 * framework resets its failure counter on every UTEST_UNIT_RUN(), so spreading
 * the lengths over several units would let a later passing unit hide an
 * earlier failing one.
 */
static void test_devtmpfs_path_components(void)
{
    rt_size_t i;
    rt_size_t round;
    rt_bool_t stop = RT_FALSE;
    int failures = 0;
    int ret;

    for (i = 0; i < sizeof(tc_cases) / sizeof(tc_cases[0]) && stop == RT_FALSE; i++)
    {
        for (round = 0; round < TC_ROUNDS; round++)
        {
            ret = tc_run_once(tc_cases[i].len, tc_cases[i].expect_ok);
            if (ret != 0)
            {
                rt_kprintf("case %s, round %u failed with %d\n",
                           tc_cases[i].label, (unsigned int)(round + 1), ret);
                failures++;

                /* a worker that did not come back still owns the shared path
                 * buffer; stop here instead of starting another round */
                if (ret == -101)
                {
                    stop = RT_TRUE;
                }
                break;
            }
        }
    }

    uassert_int_equal(failures, 0);
}

static rt_err_t utest_tc_init(void)
{
    struct stat st;

    /* devfs is mounted by the system; make sure the mount point exists */
    if (dfs_file_stat(TC_MNT_PATH, &st) != 0)
    {
        rt_kprintf("mount point %s not available, devtmpfs test skipped\n",
                   TC_MNT_PATH);
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    /* every round removes the node it created; nothing is left to guess here,
     * and a node this test did not create is deliberately not touched */
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_devtmpfs_path_components);
}
UTEST_TC_EXPORT(testcase, "components.dfs.devtmpfs_path_tc", utest_tc_init, utest_tc_cleanup, 30);

#endif /* RT_USING_DFS_V2 */
