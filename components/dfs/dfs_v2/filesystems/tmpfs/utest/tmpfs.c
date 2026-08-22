/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-20     Zhujiale   the first version
 */
#include <rtthread.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <msh.h>
#include "utest.h"
#include "utest_assert.h"
#include "common.h"

void run_copy()
{
    int ret = 0;
    ret     = msh_exec("cd /tmp", 7);
    if (ret != 0)
    {
        LOG_E("errno=%d, ret=%d\n", errno, ret);
        LOG_E("cd /tmp error");
        uassert_false(1);
    }
    uassert_true(1);
    ret = msh_exec("touch test", 10);
    if (ret != 0)
    {
        LOG_E("errno=%d, ret=%d\n", errno, ret);
        LOG_E("touch test error");
        uassert_false(1);
    }
    uassert_true(1);
    ret = msh_exec("echo this_is_a_test_file test", 29);
    if (ret != 0)
    {
        LOG_E("errno=%d, ret=%d\n", errno, ret);
        LOG_E("echo this_is_a_test_file test error");
        uassert_false(1);
    }
    uassert_true(1);
    ret = msh_exec("cp test test1", 13);
    if (ret != 0)
    {
        LOG_E("errno=%d, ret=%d\n", errno, ret);
        LOG_E("cp test test1 error");
        uassert_false(1);
    }

    uassert_true(1);
}



static void run_long_name(void)
{
    static const char source[] =
        "/tmp/iceoryx2_node_1234567890_abcdefghijklmnopqrstuvwxyz_shared";
    static const char destination[] =
        "/tmp/iceoryx2_node_abcdefghijklmnopqrstuvwxyz_0987654321_renamed";
    static const char payload[] = "tmpfs-long-name";
    char buffer[sizeof(payload)] = {0};
    struct stat st = {0};
    int fd;

    fd = open(source, O_CREAT | O_RDWR | O_TRUNC, 0);
    uassert_true(fd >= 0);
    uassert_int_equal(fstat(fd, &st), 0);
    uassert_int_equal(st.st_nlink, 1);
    uassert_int_equal(write(fd, payload, sizeof(payload)), sizeof(payload));
    uassert_int_equal(close(fd), 0);

    uassert_int_equal(rename(source, destination), 0);
    fd = open(destination, O_RDONLY, 0);
    uassert_true(fd >= 0);
    uassert_int_equal(read(fd, buffer, sizeof(buffer)), sizeof(buffer));
    uassert_str_equal(buffer, payload);
    uassert_int_equal(close(fd), 0);
    uassert_int_equal(unlink(destination), 0);
}

static void run_too_long_name_reject(void)
{
    static const char prefix[] = "/tmp/";
    char path[(sizeof(prefix) - 1) + DIRENT_NAME_MAX + 1];
    int fd;

    rt_memcpy(path, prefix, sizeof(prefix) - 1);
    rt_memset(path + sizeof(prefix) - 1, 'x', DIRENT_NAME_MAX);
    path[sizeof(path) - 1] = '\0';

    fd = open(path, O_CREAT | O_RDWR, 0);
    uassert_int_equal(fd, -1);

    fd = open("/tmp/tmpfs-after-long-name", O_CREAT | O_RDWR | O_TRUNC, 0);
    uassert_true(fd >= 0);
    uassert_int_equal(close(fd), 0);

    errno = 0;
    uassert_int_equal(rename("/tmp/tmpfs-after-long-name", path), -1);
    uassert_int_equal(errno, -ENAMETOOLONG);
    uassert_int_equal(unlink("/tmp/tmpfs-after-long-name"), 0);
}

static void run_mode_change(void)
{
    static const char path[] = "/tmp/tmpfs-mode-change";
    struct stat st = {0};
    int fd;

    unlink(path);
    fd = open(path, O_CREAT | O_EXCL | O_RDWR, 0700);
    uassert_true(fd >= 0);
    uassert_int_equal(fstat(fd, &st), 0);
    uassert_int_equal(st.st_mode & 0777, 0700);
    uassert_int_equal(fchmod(fd, 0400), 0);
    uassert_int_equal(fstat(fd, &st), 0);
    uassert_int_equal(st.st_mode & 0777, 0400);
    uassert_int_equal(close(fd), 0);

    errno = 0;
    uassert_int_equal(open(path, O_WRONLY, 0), -1);
    uassert_int_equal(errno, -EACCES);
    uassert_int_equal(unlink(path), 0);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}
static void testcase(void)
{
    UTEST_UNIT_RUN(run_copy);
    UTEST_UNIT_RUN(run_long_name);
    UTEST_UNIT_RUN(run_too_long_name_reject);
    UTEST_UNIT_RUN(run_mode_change);
}
UTEST_TC_EXPORT(testcase, "testcase.tfs.tmpfs", utest_tc_init, utest_tc_cleanup, 10);
