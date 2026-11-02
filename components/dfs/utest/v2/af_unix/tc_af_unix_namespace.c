/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "tc_af_unix.h"

#define TC_AF_UNIX_NAMESPACE_REPEAT 8

static void tc_af_unix_pathname_lifetime(void)
{
    char path[TC_AF_UNIX_PATH_MAX];
    int error;
    int first = -1;
    int result;
    int second = -1;
    struct sockaddr_un address;
    struct stat file_stat;

    tc_af_unix_path(path, sizeof(path), "utafupath");
    (void)unlink(path);
    tc_af_unix_make_address(&address, path);

    first = socket(AF_UNIX, SOCK_DGRAM, 0);
    uassert_true(first >= 0);
    if (first < 0)
    {
        goto __exit;
    }
    uassert_int_equal(bind(first, (struct sockaddr *)&address, sizeof(address)),
                      0);
    uassert_int_equal(stat(path, &file_stat), 0);
    uassert_true(S_ISSOCK(file_stat.st_mode));

    tc_af_unix_closesocket(&first);
    uassert_int_equal(stat(path, &file_stat), 0);
    uassert_true(S_ISSOCK(file_stat.st_mode));

    second = socket(AF_UNIX, SOCK_DGRAM, 0);
    uassert_true(second >= 0);
    if (second < 0)
    {
        goto __exit;
    }
    result = bind(second, (struct sockaddr *)&address, sizeof(address));
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_int_equal(error, EADDRINUSE);

    uassert_int_equal(unlink(path), 0);
    uassert_int_equal(bind(second, (struct sockaddr *)&address,
                           sizeof(address)),
                      0);

__exit:
    tc_af_unix_closesocket(&second);
    tc_af_unix_closesocket(&first);
    (void)unlink(path);
}

static void tc_af_unix_lookup_after_close(void)
{
    char path[TC_AF_UNIX_PATH_MAX];
    int client = -1;
    int error;
    int result;
    int server = -1;
    struct sockaddr_un address;

    tc_af_unix_path(path, sizeof(path), "utafuref");
    (void)unlink(path);
    tc_af_unix_make_address(&address, path);

    server = socket(AF_UNIX, SOCK_STREAM, 0);
    client = socket(AF_UNIX, SOCK_STREAM, 0);
    uassert_true(server >= 0);
    uassert_true(client >= 0);
    if (server < 0 || client < 0)
    {
        goto __exit;
    }

    uassert_int_equal(bind(server, (struct sockaddr *)&address,
                           sizeof(address)),
                      0);
    uassert_int_equal(listen(server, 1), 0);
    tc_af_unix_closesocket(&server);

    result = connect(client, (struct sockaddr *)&address, sizeof(address));
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_int_equal(error, ECONNREFUSED);

    uassert_int_equal(unlink(path), 0);
    result = connect(client, (struct sockaddr *)&address, sizeof(address));
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_int_equal(error, ENOENT);

__exit:
    tc_af_unix_closesocket(&client);
    tc_af_unix_closesocket(&server);
    (void)unlink(path);
}

static void tc_af_unix_namespace_reuse(void)
{
    char name[16];
    char path[TC_AF_UNIX_PATH_MAX];
    int client = -1;
    int error;
    int index;
    int result;
    int sock = -1;
    struct sockaddr_un address;

    for (index = 0; index < TC_AF_UNIX_NAMESPACE_REPEAT; index++)
    {
        rt_snprintf(name, sizeof(name), "utafuns%d", index);
        tc_af_unix_path(path, sizeof(path), name);
        (void)unlink(path);
        tc_af_unix_make_address(&address, path);

        sock = socket(AF_UNIX, SOCK_DGRAM, 0);
        uassert_true(sock >= 0);
        if (sock < 0)
        {
            return;
        }
        uassert_int_equal(bind(sock, (struct sockaddr *)&address,
                               sizeof(address)),
                          0);
        tc_af_unix_closesocket(&sock);
        uassert_int_equal(unlink(path), 0);
    }

    tc_af_unix_path(path, sizeof(path), "utafuns0");
    tc_af_unix_make_address(&address, path);
    client = socket(AF_UNIX, SOCK_DGRAM, 0);
    uassert_true(client >= 0);
    if (client < 0)
    {
        return;
    }
    result = connect(client, (struct sockaddr *)&address, sizeof(address));
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_int_equal(error, ENOENT);
    tc_af_unix_closesocket(&client);

    tc_af_unix_path(path, sizeof(path), "utafunew");
    (void)unlink(path);
    tc_af_unix_make_address(&address, path);
    sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    uassert_true(sock >= 0);
    if (sock < 0)
    {
        return;
    }
    uassert_int_equal(bind(sock, (struct sockaddr *)&address, sizeof(address)),
                      0);
    tc_af_unix_closesocket(&sock);
    (void)unlink(path);
}

static void tc_af_unix_namespace_testcase(void)
{
    UTEST_UNIT_RUN(tc_af_unix_pathname_lifetime);
    UTEST_UNIT_RUN(tc_af_unix_lookup_after_close);
    UTEST_UNIT_RUN(tc_af_unix_namespace_reuse);
}

UTEST_TC_EXPORT(tc_af_unix_namespace_testcase,
                "components.dfs.v2.af_unix.namespace", RT_NULL, RT_NULL, 15);
