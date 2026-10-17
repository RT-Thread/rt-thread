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
 */

#include <rtthread.h>
#include "utest.h"

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
#define TC_NAME_MAX         DIRENT_NAME_MAX

/* devtmpfs is mounted on /dev by the device filesystem, see devtmpfs_init() */
#define TC_MNT_PATH         "/dev"

/* Path buffer: mount point + '/' + component + '\0'.
 * Sized for the longest component the boundary sweep below uses (300 bytes),
 * which is deliberately well past DIRENT_NAME_MAX. */
#define TC_MAX_TEST_LEN     300
#define TC_PATH_BUF_SIZE    (sizeof(TC_MNT_PATH) + 1 + TC_MAX_TEST_LEN + 1)

static char tc_path[TC_PATH_BUF_SIZE];

/*
 * Caller-side stack guard. devtmpfs_create_vnode() and devtmpfs_file_lookup()
 * keep their file_name[]/subdir_name[] buffers on their own frames; if the
 * component were copied without a bounds check those frames - and the data
 * that survives in the caller after the call - would be corrupted. Keeping a
 * known pattern around the call and checking it afterwards is the observable
 * "does not modify neighbouring stack data" assertion requested in review.
 */
#define TC_GUARD_SIZE       32
#define TC_GUARD_PATTERN    0xA5
#define TC_GUARD_MAGIC      0x5A5A1234UL

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
 * The mount point is taken from RT_UTEST_DFS_MNT_PATH so the test works for
 * whatever filesystem/mount point the utest configuration uses.
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

/*
 * Exercise both entry points for one component length:
 *   - devtmpfs_file_lookup()  through dfs_file_stat()
 *   - devtmpfs_create_vnode() through open(O_CREAT)
 * and verify that neither one touches neighbouring stack data.
 *
 * Returns the open() result (-1 on failure).
 */
static int tc_roundtrip(rt_size_t len, rt_bool_t expect_ok)
{
    rt_uint8_t guard[TC_GUARD_SIZE];
    struct stat st;
    int fd;

    tc_build_path(len);
    tc_guard_fill(guard);

    /* lookup path first: the node does not exist yet, this must not crash */
    (void)dfs_file_stat(tc_path, &st);

    /* creation path: this is where _path_separate() runs */
    fd = open(tc_path, O_CREAT | O_RDWR, 0644);

    if (!tc_guard_intact(guard))
    {
        rt_kprintf("guard corrupted for component length %u\n",
                   (unsigned int)len);
        return -2;
    }

    if (expect_ok)
    {
        if (fd < 0)
        {
            rt_kprintf("expected success for component length %u, got %d\n",
                       (unsigned int)len, fd);
            return -3;
        }
        close(fd);

        /* the node must now be visible through the lookup path */
        tc_guard_fill(guard);
        if (dfs_file_stat(tc_path, &st) != 0)
        {
            if (tc_guard_intact(guard))
            {
                rt_kprintf("node not found after creation, len %u\n",
                           (unsigned int)len);
                return -4;
            }
            return -2;
        }
    }
    else
    {
        if (fd >= 0)
        {
            close(fd);
            rt_kprintf("expected rejection for component length %u\n",
                       (unsigned int)len);
            return -5;
        }

        /* a rejected component must not have created anything either */
        tc_guard_fill(guard);
        if (dfs_file_stat(tc_path, &st) == 0)
        {
            if (tc_guard_intact(guard))
            {
                rt_kprintf("overlong component still resolved, len %u\n",
                           (unsigned int)len);
                return -6;
            }
            return -2;
        }
    }

    return tc_guard_intact(guard) ? 0 : -2;
}

/* len == DIRENT_NAME_MAX - 2: comfortably inside the buffer */
static void test_devtmpfs_component_254(void)
{
    uassert_int_equal(tc_roundtrip(TC_NAME_MAX - 2, RT_TRUE), 0);
}

/* len == DIRENT_NAME_MAX - 1: the last length that still fits (+ terminator) */
static void test_devtmpfs_component_255(void)
{
    uassert_int_equal(tc_roundtrip(TC_NAME_MAX - 1, RT_TRUE), 0);
}

/* len == DIRENT_NAME_MAX: no room for the terminator, must be rejected */
static void test_devtmpfs_component_256(void)
{
    uassert_int_equal(tc_roundtrip(TC_NAME_MAX, RT_FALSE), 0);
}

/* well past the buffer: must be rejected as well */
static void test_devtmpfs_component_300(void)
{
    uassert_int_equal(tc_roundtrip(TC_NAME_MAX + 44, RT_FALSE), 0);
}

/* a normal, short component must keep working (no regression) */
static void test_devtmpfs_component_short(void)
{
    uassert_int_equal(tc_roundtrip(8, RT_TRUE), 0);
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
    /* the successful cases only create device nodes; nothing is persisted */
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_devtmpfs_component_short);
    UTEST_UNIT_RUN(test_devtmpfs_component_254);
    UTEST_UNIT_RUN(test_devtmpfs_component_255);
    UTEST_UNIT_RUN(test_devtmpfs_component_256);
    UTEST_UNIT_RUN(test_devtmpfs_component_300);
}
UTEST_TC_EXPORT(testcase, "components.dfs.devtmpfs_path_tc", utest_tc_init, utest_tc_cleanup, 30);

#endif /* RT_USING_DFS_V2 */
