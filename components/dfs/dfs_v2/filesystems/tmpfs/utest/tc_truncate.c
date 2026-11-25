/*
 * Copyright (c) 2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <dfs_fs.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "utest.h"

#define TEST_MOUNT "/tmpfs-truncate"
#define TEST_PATH  TEST_MOUNT "/file"

static const char payload[] = "0123456789abcdef";

static int create_file(void)
{
    int fd = open(TEST_PATH, O_CREAT | O_RDWR | O_TRUNC, 0600);

    uassert_true(fd >= 0);
    if (fd < 0)
    {
        return -1;
    }

    uassert_int_equal(write(fd, payload, sizeof(payload) - 1), sizeof(payload) - 1);
    /* Closing flushes dirty pages before testing the backing buffer. */
    uassert_int_equal(close(fd), 0);
    fd = open(TEST_PATH, O_RDWR, 0);
    uassert_true(fd >= 0);
    return fd;
}

static void test_zero_length(void)
{
    struct stat st;
    char buffer[sizeof(payload)];
    int fd = create_file();

    if (fd < 0)
    {
        return;
    }

    uassert_int_equal(ftruncate(fd, 0), 0);
    uassert_int_equal(fstat(fd, &st), 0);
    uassert_int_equal(st.st_size, 0);
    uassert_int_equal(lseek(fd, 0, SEEK_SET), 0);
    uassert_int_equal(read(fd, buffer, sizeof(buffer)), 0);

    /* Truncating an already empty file must also be safe. */
    uassert_int_equal(ftruncate(fd, 0), 0);
    uassert_int_equal(write(fd, payload, sizeof(payload) - 1), sizeof(payload) - 1);
    uassert_int_equal(lseek(fd, 0, SEEK_SET), 0);
    uassert_int_equal(read(fd, buffer, sizeof(payload) - 1), sizeof(payload) - 1);
    uassert_int_equal(rt_memcmp(buffer, payload, sizeof(payload) - 1), 0);
    uassert_int_equal(close(fd), 0);
    fd = open(TEST_PATH, O_RDONLY, 0);
    uassert_true(fd >= 0);
    if (fd >= 0)
    {
        uassert_int_equal(fstat(fd, &st), 0);
        uassert_int_equal(st.st_size, sizeof(payload) - 1);
        uassert_int_equal(close(fd), 0);
    }
    uassert_int_equal(unlink(TEST_PATH), 0);
}

static void test_nonzero_length(void)
{
    struct stat st;
    char buffer[4];
    int fd = create_file();

    if (fd < 0)
    {
        return;
    }

    uassert_int_equal(ftruncate(fd, sizeof(buffer)), 0);
    uassert_int_equal(fstat(fd, &st), 0);
    uassert_int_equal(st.st_size, sizeof(buffer));
    uassert_int_equal(lseek(fd, 0, SEEK_SET), 0);
    uassert_int_equal(read(fd, buffer, sizeof(buffer)), sizeof(buffer));
    uassert_int_equal(rt_memcmp(buffer, payload, sizeof(buffer)), 0);

    uassert_int_equal(ftruncate(fd, 4096), 0);
    uassert_int_equal(fstat(fd, &st), 0);
    uassert_int_equal(st.st_size, 4096);
    uassert_int_equal(lseek(fd, 0, SEEK_SET), 0);
    uassert_int_equal(read(fd, buffer, sizeof(buffer)), sizeof(buffer));
    uassert_int_equal(rt_memcmp(buffer, payload, sizeof(buffer)), 0);
    uassert_int_equal(close(fd), 0);
    uassert_int_equal(unlink(TEST_PATH), 0);
}

static void test_allocation_failure(void)
{
    rt_size_t total, used, max_used;
    struct stat st;
    char buffer[sizeof(payload)];
    int fd = create_file();

    if (fd < 0)
    {
        return;
    }

    /* An existing allocation cannot grow to the size of the entire heap. */
    rt_memory_info(&total, &used, &max_used);
    uassert_true(total > 0);
    uassert_true((off_t)total > 0);
    errno = 0;
    uassert_int_equal(ftruncate(fd, (off_t)total), -1);
    uassert_int_equal(errno, -ENOMEM);
    uassert_int_equal(fstat(fd, &st), 0);
    uassert_int_equal(st.st_size, sizeof(payload) - 1);
    uassert_int_equal(lseek(fd, 0, SEEK_SET), 0);
    uassert_int_equal(read(fd, buffer, sizeof(payload) - 1), sizeof(payload) - 1);
    uassert_int_equal(rt_memcmp(buffer, payload, sizeof(payload) - 1), 0);
    uassert_int_equal(close(fd), 0);
    uassert_int_equal(unlink(TEST_PATH), 0);
}

static rt_err_t test_init(void)
{
    if (mkdir(TEST_MOUNT, 0700) != 0 && errno != -EEXIST)
    {
        return -RT_ERROR;
    }

    return dfs_mount(RT_NULL, TEST_MOUNT, "tmp", 0, RT_NULL) == 0 ? RT_EOK : -RT_ERROR;
}

static rt_err_t test_cleanup(void)
{
    int ret = dfs_unmount(TEST_MOUNT);

    rmdir(TEST_MOUNT);
    return ret == 0 ? RT_EOK : -RT_ERROR;
}

static void test_truncate(void)
{
    test_zero_length();
    test_nonzero_length();
    test_allocation_failure();
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_truncate);
}
UTEST_TC_EXPORT(testcase, "components.dfs.tmpfs_truncate", test_init, test_cleanup, 30);
