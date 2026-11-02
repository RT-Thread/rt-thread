/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "tc_af_unix.h"

static void tc_af_unix_rights_transfer(void)
{
    char data;
    char payload;
    int message_flags;
    int pipe_fds[2][2];
    int received_fds[2];
    int send_fds[2];
    int sockets[2];
    int type_index;
    int types[2] = { SOCK_DGRAM, SOCK_STREAM };
    size_t fd_count;

    for (type_index = 0; type_index < 2; type_index++)
    {
        received_fds[0] = -1;
        received_fds[1] = -1;
        pipe_fds[0][0] = -1;
        pipe_fds[0][1] = -1;
        pipe_fds[1][0] = -1;
        pipe_fds[1][1] = -1;
        sockets[0] = -1;
        sockets[1] = -1;

        uassert_int_equal(socketpair(AF_UNIX, types[type_index], 0, sockets),
                          0);
        uassert_int_equal(pipe(pipe_fds[0]), 0);
        uassert_int_equal(pipe(pipe_fds[1]), 0);
        if (sockets[0] < 0 || pipe_fds[0][0] < 0 || pipe_fds[1][0] < 0)
        {
            goto __iteration_exit;
        }

        uassert_int_equal(write(pipe_fds[0][1], "a", 1), 1);
        uassert_int_equal(write(pipe_fds[1][1], "b", 1), 1);
        send_fds[0] = pipe_fds[0][0];
        send_fds[1] = pipe_fds[1][0];
        uassert_int_equal(tc_af_unix_send_rights(sockets[0], send_fds, 2, 'r'),
                          1);
        tc_af_unix_close(&pipe_fds[0][0]);
        tc_af_unix_close(&pipe_fds[1][0]);

        fd_count = 0;
        message_flags = 0;
        uassert_int_equal(tc_af_unix_receive_rights(
                              sockets[1], 0, CMSG_SPACE(2 * sizeof(int)),
                              received_fds, &fd_count, &message_flags,
                              &payload),
                          1);
        uassert_int_equal(payload, 'r');
        uassert_int_equal(fd_count, 2);
        uassert_int_equal(message_flags & MSG_CTRUNC, 0);
        uassert_int_equal(read(received_fds[0], &data, 1), 1);
        uassert_int_equal(data, 'a');
        uassert_int_equal(read(received_fds[1], &data, 1), 1);
        uassert_int_equal(data, 'b');

    __iteration_exit:
        tc_af_unix_close(&received_fds[0]);
        tc_af_unix_close(&received_fds[1]);
        tc_af_unix_close(&pipe_fds[0][0]);
        tc_af_unix_close(&pipe_fds[0][1]);
        tc_af_unix_close(&pipe_fds[1][0]);
        tc_af_unix_close(&pipe_fds[1][1]);
        tc_af_unix_closesocket(&sockets[0]);
        tc_af_unix_closesocket(&sockets[1]);
    }
}

static void tc_af_unix_rights_truncation(void)
{
    char payload;
    int message_flags = 0;
    int pipe_fds[2][2] = { { -1, -1 }, { -1, -1 } };
    int received_fds[2] = { -1, -1 };
    int send_fds[2];
    int sockets[2] = { -1, -1 };
    size_t fd_count = 0;

    uassert_int_equal(socketpair(AF_UNIX, SOCK_DGRAM, 0, sockets), 0);
    uassert_int_equal(pipe(pipe_fds[0]), 0);
    uassert_int_equal(pipe(pipe_fds[1]), 0);
    if (sockets[0] < 0 || pipe_fds[0][0] < 0 || pipe_fds[1][0] < 0)
    {
        goto __exit;
    }

    send_fds[0] = pipe_fds[0][0];
    send_fds[1] = pipe_fds[1][0];
    uassert_int_equal(tc_af_unix_send_rights(sockets[0], send_fds, 2, 't'), 1);
    uassert_int_equal(tc_af_unix_receive_rights(sockets[1], 0, 0, received_fds,
                                                &fd_count, &message_flags,
                                                &payload),
                      1);
    uassert_int_equal(fd_count, 0);
    uassert_true((message_flags & MSG_CTRUNC) != 0);

__exit:
    tc_af_unix_close(&received_fds[0]);
    tc_af_unix_close(&pipe_fds[0][0]);
    tc_af_unix_close(&pipe_fds[0][1]);
    tc_af_unix_close(&pipe_fds[1][0]);
    tc_af_unix_close(&pipe_fds[1][1]);
    tc_af_unix_closesocket(&sockets[0]);
    tc_af_unix_closesocket(&sockets[1]);
}

static void tc_af_unix_rights_peek_and_invalid(void)
{
    char payload;
    int error;
    int invalid_fd = -1;
    int message_flags = 0;
    int pipe_fds[2] = { -1, -1 };
    int received_fds[2] = { -1, -1 };
    int result;
    int sockets[2] = { -1, -1 };
    size_t fd_count = 0;

    uassert_int_equal(socketpair(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0,
                                 sockets),
                      0);
    uassert_int_equal(pipe(pipe_fds), 0);
    if (sockets[0] < 0 || pipe_fds[0] < 0)
    {
        goto __exit;
    }

    result = tc_af_unix_send_rights(sockets[0], &invalid_fd, 1, 'x');
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_int_equal(error, EBADF);

    uassert_int_equal(tc_af_unix_send_rights(sockets[0], pipe_fds, 1, 'p'), 1);
    fd_count = 0;
    uassert_int_equal(tc_af_unix_receive_rights(
                          sockets[1], MSG_PEEK, CMSG_SPACE(sizeof(int)),
                          received_fds, &fd_count, &message_flags, &payload),
                      1);
    uassert_int_equal(payload, 'p');
    uassert_int_equal(fd_count, 0);

    fd_count = 0;
    message_flags = 0;
    uassert_int_equal(tc_af_unix_receive_rights(
                          sockets[1], 0, CMSG_SPACE(sizeof(int)),
                          received_fds, &fd_count, &message_flags, &payload),
                      1);
    uassert_int_equal(fd_count, 1);

__exit:
    tc_af_unix_close(&received_fds[0]);
    tc_af_unix_close(&pipe_fds[0]);
    tc_af_unix_close(&pipe_fds[1]);
    tc_af_unix_closesocket(&sockets[0]);
    tc_af_unix_closesocket(&sockets[1]);
}

static void tc_af_unix_rights_reject_socket(void)
{
    char payload;
    int carrier[2] = { -1, -1 };
    int error;
    int message_flags = 0;
    int passed[2] = { -1, -1 };
    int received_fds[2] = { -1, -1 };
    int result;
    size_t fd_count = 0;

    uassert_int_equal(socketpair(AF_UNIX, SOCK_STREAM, 0, carrier), 0);
    uassert_int_equal(socketpair(AF_UNIX, SOCK_DGRAM, 0, passed), 0);
    if (carrier[0] < 0 || passed[0] < 0)
    {
        goto __exit;
    }

    result = tc_af_unix_send_rights(carrier[0], &passed[1], 1, 's');
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_int_equal(error, EOPNOTSUPP);

    result = tc_af_unix_receive_rights(carrier[1], MSG_DONTWAIT,
                                       CMSG_SPACE(sizeof(int)), received_fds,
                                       &fd_count, &message_flags, &payload);
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_true(error == EAGAIN || error == EWOULDBLOCK);
    uassert_int_equal(fd_count, 0);

    uassert_int_equal(send(passed[0], "q", 1, 0), 1);
    uassert_int_equal(recv(passed[1], &payload, 1, 0), 1);
    uassert_int_equal(payload, 'q');

__exit:
    tc_af_unix_close(&received_fds[0]);
    tc_af_unix_closesocket(&passed[0]);
    tc_af_unix_closesocket(&passed[1]);
    tc_af_unix_closesocket(&carrier[0]);
    tc_af_unix_closesocket(&carrier[1]);
}

static void tc_af_unix_rights_testcase(void)
{
    UTEST_UNIT_RUN(tc_af_unix_rights_transfer);
    UTEST_UNIT_RUN(tc_af_unix_rights_truncation);
    UTEST_UNIT_RUN(tc_af_unix_rights_peek_and_invalid);
    UTEST_UNIT_RUN(tc_af_unix_rights_reject_socket);
}

UTEST_TC_EXPORT(tc_af_unix_rights_testcase, "components.dfs.v2.af_unix.rights",
                RT_NULL, RT_NULL, 15);
