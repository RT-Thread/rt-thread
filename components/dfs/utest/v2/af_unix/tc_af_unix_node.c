/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "tc_af_unix.h"

static void tc_af_unix_mknod_socket(void)
{
    char path[TC_AF_UNIX_PATH_MAX];
    int result;
    struct stat file_stat;

    tc_af_unix_path(path, sizeof(path), "utafumkn");
    (void)unlink(path);

    result = dfs_file_mknod(path, FT_SOCKET, S_IRWXU | S_IRWXG | S_IRWXO);
    uassert_int_equal(result, 0);
    if (result != 0)
    {
        return;
    }

    uassert_int_equal(stat(path, &file_stat), 0);
    uassert_true(S_ISSOCK(file_stat.st_mode));

    result = dfs_file_mknod(path, FT_SOCKET, S_IRWXU | S_IRWXG | S_IRWXO);
    uassert_int_equal(result, -EEXIST);

    uassert_int_equal(unlink(path), 0);
    uassert_true(stat(path, &file_stat) < 0);
}

static void tc_af_unix_file_refs(void)
{
    char data[4];
    int installed = -1;
    int invalid_fd = -1;
    int pipe_fds[2] = { -1, -1 };
    struct dfs_file *files[1];

    files[0] = RT_NULL;
    uassert_int_equal(dfs_file_get_refs(&invalid_fd, 1, files), -EBADF);
    uassert_true(files[0] == RT_NULL);

    uassert_int_equal(pipe(pipe_fds), 0);
    if (pipe_fds[0] < 0)
    {
        return;
    }

    uassert_int_equal(write(pipe_fds[1], "abcd", 4), 4);
    uassert_int_equal(dfs_file_get_refs(&pipe_fds[0], 1, files), 0);
    uassert_true(files[0] != RT_NULL);

    dfs_file_put_ref(files[0]);
    uassert_int_equal(read(pipe_fds[0], data, 2), 2);
    uassert_buf_equal(data, "ab", 2);

    uassert_int_equal(dfs_file_get_refs(&pipe_fds[0], 1, files), 0);
    uassert_int_equal(dfs_file_install_refs(files, 1, &installed), 0);
    uassert_true(installed >= 0);
    uassert_int_equal(read(installed, data, 2), 2);
    uassert_buf_equal(data, "cd", 2);

    tc_af_unix_close(&installed);
    tc_af_unix_close(&pipe_fds[0]);
    tc_af_unix_close(&pipe_fds[1]);
}

static void tc_af_unix_node_testcase(void)
{
    UTEST_UNIT_RUN(tc_af_unix_mknod_socket);
    UTEST_UNIT_RUN(tc_af_unix_file_refs);
}

UTEST_TC_EXPORT(tc_af_unix_node_testcase, "components.dfs.v2.af_unix.node",
                RT_NULL, RT_NULL, 10);
