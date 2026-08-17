/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "tc_af_unix.h"

static void tc_af_unix_dgram_ipc(void)
{
    char buffer[16];
    char client_path[TC_AF_UNIX_PATH_MAX];
    char server_path[TC_AF_UNIX_PATH_MAX];
    const char payload[] = "datagram";
    int client = -1;
    int error;
    int result;
    int server = -1;
    socklen_t source_length;
    struct sockaddr_un client_address;
    struct sockaddr_un server_address;
    struct sockaddr_un source_address;

    tc_af_unix_path(server_path, sizeof(server_path), "utafudgs");
    tc_af_unix_path(client_path, sizeof(client_path), "utafudgc");
    (void)unlink(server_path);
    (void)unlink(client_path);
    tc_af_unix_make_address(&server_address, server_path);
    tc_af_unix_make_address(&client_address, client_path);

    server = socket(AF_UNIX, SOCK_DGRAM, 0);
    client = socket(AF_UNIX, SOCK_DGRAM, 0);
    uassert_true(server >= 0);
    uassert_true(client >= 0);
    if (server < 0 || client < 0)
    {
        goto __exit;
    }

    uassert_int_equal(bind(server, (struct sockaddr *)&server_address,
                           sizeof(server_address)),
                      0);
    uassert_int_equal(bind(client, (struct sockaddr *)&client_address,
                           sizeof(client_address)),
                      0);
    uassert_int_equal(connect(client, (struct sockaddr *)&server_address,
                              sizeof(server_address)),
                      0);
    uassert_int_equal(send(client, payload, sizeof(payload), 0),
                      sizeof(payload));

    source_length = sizeof(source_address);
    result = recvfrom(server, buffer, sizeof(buffer), 0,
                      (struct sockaddr *)&source_address, &source_length);
    uassert_int_equal(result, sizeof(payload));
    uassert_buf_equal(buffer, payload, sizeof(payload));
    uassert_str_equal(source_address.sun_path, client_path);

    result = fcntl(server, F_SETFL, O_NONBLOCK);
    uassert_int_equal(result, 0);
    result = recv(server, buffer, sizeof(buffer), 0);
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_true(error == EAGAIN || error == EWOULDBLOCK);

    result = listen(server, 1);
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_int_equal(error, EOPNOTSUPP);

__exit:
    tc_af_unix_closesocket(&client);
    tc_af_unix_closesocket(&server);
    (void)unlink(client_path);
    (void)unlink(server_path);
}

static void tc_af_unix_stream_ipc(void)
{
    char accepted_path[TC_AF_UNIX_PATH_MAX];
    char buffer[16];
    const char request[] = "request";
    const char response[] = "response";
    int accepted = -1;
    int client = -1;
    int listener = -1;
    struct sockaddr_un address;
    struct sockaddr_un local_address;
    struct sockaddr_un peer_address;
    socklen_t local_length;
    socklen_t peer_length;

    tc_af_unix_path(accepted_path, sizeof(accepted_path), "utafustr");
    (void)unlink(accepted_path);
    tc_af_unix_make_address(&address, accepted_path);

    listener = socket(AF_UNIX, SOCK_STREAM, 0);
    client = socket(AF_UNIX, SOCK_STREAM, 0);
    uassert_true(listener >= 0);
    uassert_true(client >= 0);
    if (listener < 0 || client < 0)
    {
        goto __exit;
    }

    uassert_int_equal(bind(listener, (struct sockaddr *)&address,
                           sizeof(address)),
                      0);
    uassert_int_equal(listen(listener, 2), 0);
    uassert_int_equal(connect(client, (struct sockaddr *)&address,
                              sizeof(address)),
                      0);
    accepted = accept(listener, RT_NULL, RT_NULL);
    uassert_true(accepted >= 0);
    if (accepted < 0)
    {
        goto __exit;
    }

    local_length = sizeof(local_address);
    peer_length = sizeof(peer_address);
    uassert_int_equal(getsockname(accepted, (struct sockaddr *)&local_address,
                                  &local_length),
                      0);
    uassert_int_equal(getpeername(client, (struct sockaddr *)&peer_address,
                                  &peer_length),
                      0);
    uassert_str_equal(local_address.sun_path, accepted_path);
    uassert_str_equal(peer_address.sun_path, accepted_path);

    uassert_int_equal(send(client, request, sizeof(request), 0),
                      sizeof(request));
    uassert_int_equal(recv(accepted, buffer, sizeof(buffer), 0),
                      sizeof(request));
    uassert_buf_equal(buffer, request, sizeof(request));
    uassert_int_equal(send(accepted, response, sizeof(response), 0),
                      sizeof(response));
    uassert_int_equal(recv(client, buffer, sizeof(buffer), 0),
                      sizeof(response));
    uassert_buf_equal(buffer, response, sizeof(response));

    uassert_int_equal(shutdown(client, SHUT_WR), 0);
    uassert_int_equal(recv(accepted, buffer, sizeof(buffer), 0), 0);

__exit:
    tc_af_unix_closesocket(&accepted);
    tc_af_unix_closesocket(&client);
    tc_af_unix_closesocket(&listener);
    (void)unlink(accepted_path);
}

static void tc_af_unix_socketpair_msg(void)
{
    char buffer[8];
    char first_part[3];
    char second_part[3];
    const char payload[] = "pair";
    int sockets[2] = { -1, -1 };
    int type_index;
    int types[2] = { SOCK_DGRAM, SOCK_STREAM };
    struct iovec receive_iov[2];
    struct iovec send_iov[2];
    struct msghdr receive_message;
    struct msghdr send_message;

    for (type_index = 0; type_index < 2; type_index++)
    {
        uassert_int_equal(socketpair(AF_UNIX, types[type_index], 0, sockets),
                          0);
        uassert_int_equal(send(sockets[0], payload, sizeof(payload), 0),
                          sizeof(payload));
        uassert_int_equal(recv(sockets[1], buffer, sizeof(buffer), 0),
                          sizeof(payload));
        uassert_buf_equal(buffer, payload, sizeof(payload));

        rt_memset(&send_message, 0, sizeof(send_message));
        send_iov[0].iov_base = (void *)payload;
        send_iov[0].iov_len = 2;
        send_iov[1].iov_base = (void *)(payload + 2);
        send_iov[1].iov_len = sizeof(payload) - 2;
        send_message.msg_iov = send_iov;
        send_message.msg_iovlen = 2;
        send_message.msg_name = RT_NULL;
        send_message.msg_namelen = sizeof(struct sockaddr_un);
        uassert_int_equal(sendmsg(sockets[0], &send_message, 0),
                          sizeof(payload));

        rt_memset(&receive_message, 0, sizeof(receive_message));
        receive_iov[0].iov_base = first_part;
        receive_iov[0].iov_len = sizeof(first_part);
        receive_iov[1].iov_base = second_part;
        receive_iov[1].iov_len = sizeof(second_part);
        receive_message.msg_iov = receive_iov;
        receive_message.msg_iovlen = 2;
        uassert_int_equal(recvmsg(sockets[1], &receive_message, 0),
                          sizeof(payload));
        uassert_buf_equal(first_part, payload, sizeof(first_part));
        uassert_buf_equal(second_part, payload + sizeof(first_part),
                          sizeof(payload) - sizeof(first_part));

        send_message.msg_control = RT_NULL;
        send_message.msg_controllen = CMSG_SPACE(sizeof(int));
        uassert_int_equal(sendmsg(sockets[0], &send_message, 0), -1);
        uassert_int_equal(rt_get_errno(), EINVAL);

        tc_af_unix_closesocket(&sockets[0]);
        tc_af_unix_closesocket(&sockets[1]);
    }
}

static void tc_af_unix_connect_missing(void)
{
    char path[TC_AF_UNIX_PATH_MAX];
    int client = -1;
    int error;
    int result;
    struct sockaddr_un address;

    tc_af_unix_path(path, sizeof(path), "utafumiss");
    (void)unlink(path);
    tc_af_unix_make_address(&address, path);

    client = socket(AF_UNIX, SOCK_STREAM, 0);
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
}

static void tc_af_unix_pending_close(void)
{
    char path[TC_AF_UNIX_PATH_MAX];
    const char payload[] = "pending";
    int client = -1;
    int error;
    int listener = -1;
    int result;
    struct sockaddr_un address;

    tc_af_unix_path(path, sizeof(path), "utafupend");
    (void)unlink(path);
    tc_af_unix_make_address(&address, path);

    listener = socket(AF_UNIX, SOCK_STREAM, 0);
    client = socket(AF_UNIX, SOCK_STREAM, 0);
    uassert_true(listener >= 0);
    uassert_true(client >= 0);
    if (listener < 0 || client < 0)
    {
        goto __exit;
    }

    uassert_int_equal(bind(listener, (struct sockaddr *)&address,
                           sizeof(address)),
                      0);
    uassert_int_equal(listen(listener, 1), 0);
    uassert_int_equal(connect(client, (struct sockaddr *)&address,
                              sizeof(address)),
                      0);
    tc_af_unix_closesocket(&listener);

    result = send(client, payload, sizeof(payload), 0);
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_true(error == ENOTCONN || error == EPIPE);

__exit:
    tc_af_unix_closesocket(&client);
    tc_af_unix_closesocket(&listener);
    (void)unlink(path);
}

static void tc_af_unix_ipc_testcase(void)
{
    UTEST_UNIT_RUN(tc_af_unix_dgram_ipc);
    UTEST_UNIT_RUN(tc_af_unix_stream_ipc);
    UTEST_UNIT_RUN(tc_af_unix_socketpair_msg);
    UTEST_UNIT_RUN(tc_af_unix_connect_missing);
    UTEST_UNIT_RUN(tc_af_unix_pending_close);
}

UTEST_TC_EXPORT(tc_af_unix_ipc_testcase, "components.dfs.v2.af_unix.ipc",
                RT_NULL, RT_NULL, 15);
