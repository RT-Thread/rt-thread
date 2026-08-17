/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#include <utest.h>

#define AF_UNIX_DGRAM_SERVER_PATH "/dev/afudgs"
#define AF_UNIX_DGRAM_CLIENT_PATH "/dev/afudgc"
#define AF_UNIX_STREAM_PATH       "/dev/afustr"
#define AF_UNIX_PENDING_PATH      "/dev/afupend"
#define AF_UNIX_PERSIST_PATH      "/var/afupath"

static void af_unix_make_address(struct sockaddr_un *address,
                                 const char *path)
{
    rt_memset(address, 0, sizeof(*address));
    address->sa_family = AF_UNIX;
    rt_strncpy(address->sun_path, path, sizeof(address->sun_path) - 1);
}

static int af_unix_send_rights(int socket_fd, const int *fds, size_t fd_count,
                               char payload)
{
    char control[CMSG_SPACE(2 * sizeof(int))];
    struct cmsghdr *cmsg;
    struct iovec iov;
    struct msghdr message;

    rt_memset(&message, 0, sizeof(message));
    rt_memset(control, 0, sizeof(control));
    iov.iov_base = &payload;
    iov.iov_len = sizeof(payload);
    message.msg_iov = &iov;
    message.msg_iovlen = 1;
    message.msg_control = control;
    message.msg_controllen = CMSG_SPACE(fd_count * sizeof(int));
    cmsg = CMSG_FIRSTHDR(&message);
    cmsg->cmsg_len = CMSG_LEN(fd_count * sizeof(int));
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    rt_memcpy(CMSG_DATA(cmsg), fds, fd_count * sizeof(int));
    return sendmsg(socket_fd, &message, 0);
}

static int af_unix_receive_rights(int socket_fd, int flags,
                                  size_t control_length, int *fds,
                                  size_t *fd_count, int *message_flags,
                                  char *payload)
{
    char control[CMSG_SPACE(2 * sizeof(int))];
    int result;
    size_t count = 0;
    struct cmsghdr *cmsg;
    struct iovec iov;
    struct msghdr message;

    rt_memset(&message, 0, sizeof(message));
    rt_memset(control, 0, sizeof(control));
    iov.iov_base = payload;
    iov.iov_len = sizeof(*payload);
    message.msg_iov = &iov;
    message.msg_iovlen = 1;
    message.msg_control = control_length != 0 ? control : RT_NULL;
    message.msg_controllen = control_length;

    result = recvmsg(socket_fd, &message, flags);
    if (result >= 0)
    {
        cmsg = CMSG_FIRSTHDR(&message);
        if (cmsg != RT_NULL && cmsg->cmsg_level == SOL_SOCKET &&
            cmsg->cmsg_type == SCM_RIGHTS &&
            cmsg->cmsg_len >= CMSG_LEN(sizeof(int)))
        {
            count = (cmsg->cmsg_len - sizeof(*cmsg)) / sizeof(int);
            rt_memcpy(fds, CMSG_DATA(cmsg), count * sizeof(int));
        }
        *fd_count = count;
        *message_flags = message.msg_flags;
    }
    return result;
}

static void af_unix_test_dgram(void)
{
    int server = -1;
    int client = -1;
    int error;
    int result;
    char buffer[16];
    const char payload[] = "datagram";
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;
    struct sockaddr_un source_address;
    socklen_t source_length;

    (void)unlink(AF_UNIX_DGRAM_SERVER_PATH);
    (void)unlink(AF_UNIX_DGRAM_CLIENT_PATH);
    af_unix_make_address(&server_address, AF_UNIX_DGRAM_SERVER_PATH);
    af_unix_make_address(&client_address, AF_UNIX_DGRAM_CLIENT_PATH);

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
    uassert_str_equal(source_address.sun_path, AF_UNIX_DGRAM_CLIENT_PATH);

    result = fcntl(server, F_SETFL, O_NONBLOCK);
    uassert_int_equal(result, 0);
    result = recv(server, buffer, sizeof(buffer), 0);
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_true(error == EAGAIN || error == EWOULDBLOCK);

__exit:
    if (client >= 0)
    {
        closesocket(client);
    }
    if (server >= 0)
    {
        closesocket(server);
    }
    (void)unlink(AF_UNIX_DGRAM_CLIENT_PATH);
    (void)unlink(AF_UNIX_DGRAM_SERVER_PATH);
}

static void af_unix_test_pathname_lifetime(void)
{
    int first = -1;
    int second = -1;
    int error;
    int result;
    struct stat file_stat;
    struct sockaddr_un address;

    (void)unlink(AF_UNIX_PERSIST_PATH);
    af_unix_make_address(&address, AF_UNIX_PERSIST_PATH);

    first = socket(AF_UNIX, SOCK_DGRAM, 0);
    uassert_true(first >= 0);
    if (first < 0)
    {
        goto __exit;
    }
    uassert_int_equal(bind(first, (struct sockaddr *)&address,
                           sizeof(address)),
                      0);
    uassert_int_equal(stat(AF_UNIX_PERSIST_PATH, &file_stat), 0);
    uassert_true(S_ISSOCK(file_stat.st_mode));

    closesocket(first);
    first = -1;
    uassert_int_equal(stat(AF_UNIX_PERSIST_PATH, &file_stat), 0);
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

    uassert_int_equal(unlink(AF_UNIX_PERSIST_PATH), 0);
    uassert_int_equal(bind(second, (struct sockaddr *)&address,
                           sizeof(address)),
                      0);

__exit:
    if (second >= 0)
    {
        closesocket(second);
    }
    if (first >= 0)
    {
        closesocket(first);
    }
    (void)unlink(AF_UNIX_PERSIST_PATH);
}

static void af_unix_test_stream(void)
{
    int listener = -1;
    int client = -1;
    int accepted = -1;
    char buffer[16];
    const char request[] = "request";
    const char response[] = "response";
    struct sockaddr_un address;

    (void)unlink(AF_UNIX_STREAM_PATH);
    af_unix_make_address(&address, AF_UNIX_STREAM_PATH);

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
    if (accepted >= 0)
    {
        closesocket(accepted);
    }
    if (client >= 0)
    {
        closesocket(client);
    }
    if (listener >= 0)
    {
        closesocket(listener);
    }
    (void)unlink(AF_UNIX_STREAM_PATH);
}

static void af_unix_test_dgram_readiness(void)
{
    int error;
    int index;
    int result;
    int sockets[2] = { -1, -1 };
    char buffer[2];
    const char payload[] = "x";
    struct pollfd poll_fd;

    result = socketpair(AF_UNIX, SOCK_DGRAM | SOCK_NONBLOCK, 0, sockets);
    uassert_int_equal(result, 0);
    if (result < 0)
    {
        return;
    }

    poll_fd.fd = sockets[1];
    poll_fd.events = POLLIN;
    poll_fd.revents = 0;
    uassert_int_equal(poll(&poll_fd, 1, 0), 0);

    for (index = 0; index < AF_UNIX_DGRAM_QUEUE_LEN; index++)
    {
        uassert_int_equal(send(sockets[0], payload, sizeof(payload), 0),
                          sizeof(payload));
    }
    result = send(sockets[0], payload, sizeof(payload), 0);
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_int_equal(error, EAGAIN);

    poll_fd.revents = 0;
    uassert_int_equal(poll(&poll_fd, 1, 0), 1);
    uassert_true((poll_fd.revents & POLLIN) != 0);
    uassert_int_equal(recv(sockets[1], buffer, sizeof(buffer), 0),
                      sizeof(payload));
    uassert_int_equal(send(sockets[0], payload, sizeof(payload), 0),
                      sizeof(payload));

    result = send(sockets[0], payload, AF_UNIX_DGRAM_MAX_SIZE + 1, 0);
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_int_equal(error, EMSGSIZE);

    closesocket(sockets[0]);
    closesocket(sockets[1]);
}

static void af_unix_test_stream_readiness(void)
{
    int result;
    int sockets[2] = { -1, -1 };
    char buffer[8];
    const char payload[] = "poll";
    struct pollfd poll_fd;

    result = socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);
    uassert_int_equal(result, 0);
    if (result < 0)
    {
        return;
    }

    poll_fd.fd = sockets[1];
    poll_fd.events = POLLIN | POLLOUT;
    poll_fd.revents = 0;
    uassert_int_equal(poll(&poll_fd, 1, 0), 1);
    uassert_true((poll_fd.revents & POLLOUT) != 0);
    uassert_true((poll_fd.revents & POLLIN) == 0);

    uassert_int_equal(send(sockets[0], payload, sizeof(payload), 0),
                      sizeof(payload));
    poll_fd.revents = 0;
    uassert_int_equal(poll(&poll_fd, 1, 0), 1);
    uassert_true((poll_fd.revents & POLLIN) != 0);
    uassert_int_equal(recv(sockets[1], buffer, sizeof(buffer), 0),
                      sizeof(payload));

    uassert_int_equal(shutdown(sockets[0], SHUT_WR), 0);
    poll_fd.revents = 0;
    uassert_int_equal(poll(&poll_fd, 1, 0), 1);
    uassert_true((poll_fd.revents & POLLIN) != 0);
    uassert_int_equal(recv(sockets[1], buffer, sizeof(buffer), 0), 0);

    closesocket(sockets[0]);
    closesocket(sockets[1]);
}

static void af_unix_test_pending_close(void)
{
    int client = -1;
    int error;
    int listener = -1;
    int result;
    const char payload[] = "pending";
    struct sockaddr_un address;

    (void)unlink(AF_UNIX_PENDING_PATH);
    af_unix_make_address(&address, AF_UNIX_PENDING_PATH);

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
    closesocket(listener);
    listener = -1;

    result = send(client, payload, sizeof(payload), 0);
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_true(error == ENOTCONN || error == EPIPE);

__exit:
    if (client >= 0)
    {
        closesocket(client);
    }
    if (listener >= 0)
    {
        closesocket(listener);
    }
    (void)unlink(AF_UNIX_PENDING_PATH);
}

static void af_unix_test_socketpair(void)
{
    int type_index;
    int types[2] = { SOCK_DGRAM, SOCK_STREAM };
    int sockets[2];
    char buffer[8];
    char first_part[3];
    char second_part[3];
    const char payload[] = "pair";
    struct iovec receive_iov[2];
    struct iovec send_iov[2];
    struct msghdr receive_message;
    struct msghdr send_message;

    for (type_index = 0; type_index < 2; type_index++)
    {
        uassert_int_equal(socketpair(AF_UNIX, types[type_index], 0,
                                     sockets),
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
        closesocket(sockets[0]);
        closesocket(sockets[1]);
    }
}

static void af_unix_test_rights_transfer(void)
{
    char data;
    char payload;
    int received_fds[2] = { -1, -1 };
    int pipe_fds[2][2] = { { -1, -1 }, { -1, -1 } };
    int send_fds[2];
    int sockets[2] = { -1, -1 };
    int type_index;
    int types[2] = { SOCK_DGRAM, SOCK_STREAM };
    size_t fd_count;
    int message_flags;

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

        uassert_int_equal(socketpair(AF_UNIX, types[type_index], 0,
                                     sockets),
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
        uassert_int_equal(af_unix_send_rights(sockets[0], send_fds, 2,
                                              'r'),
                          1);
        close(pipe_fds[0][0]);
        pipe_fds[0][0] = -1;
        close(pipe_fds[1][0]);
        pipe_fds[1][0] = -1;

        fd_count = 0;
        message_flags = 0;
        uassert_int_equal(af_unix_receive_rights(
                              sockets[1], 0,
                              CMSG_SPACE(2 * sizeof(int)), received_fds,
                              &fd_count, &message_flags, &payload),
                          1);
        uassert_int_equal(payload, 'r');
        uassert_int_equal(fd_count, 2);
        uassert_int_equal(message_flags & MSG_CTRUNC, 0);
        uassert_int_equal(read(received_fds[0], &data, 1), 1);
        uassert_int_equal(data, 'a');
        uassert_int_equal(read(received_fds[1], &data, 1), 1);
        uassert_int_equal(data, 'b');

    __iteration_exit:
        if (received_fds[0] >= 0)
        {
            close(received_fds[0]);
        }
        if (received_fds[1] >= 0)
        {
            close(received_fds[1]);
        }
        if (pipe_fds[0][0] >= 0)
        {
            close(pipe_fds[0][0]);
        }
        if (pipe_fds[0][1] >= 0)
        {
            close(pipe_fds[0][1]);
        }
        if (pipe_fds[1][0] >= 0)
        {
            close(pipe_fds[1][0]);
        }
        if (pipe_fds[1][1] >= 0)
        {
            close(pipe_fds[1][1]);
        }
        if (sockets[0] >= 0)
        {
            closesocket(sockets[0]);
        }
        if (sockets[1] >= 0)
        {
            closesocket(sockets[1]);
        }
    }
}

static void af_unix_test_rights_truncation(void)
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
    uassert_int_equal(af_unix_send_rights(sockets[0], send_fds, 2, 't'), 1);
    uassert_int_equal(af_unix_receive_rights(
                          sockets[1], 0, 0,
                          received_fds, &fd_count, &message_flags, &payload),
                      1);
    uassert_int_equal(fd_count, 0);
    uassert_true((message_flags & MSG_CTRUNC) != 0);

__exit:
    if (received_fds[0] >= 0)
    {
        close(received_fds[0]);
    }
    if (pipe_fds[0][0] >= 0)
    {
        close(pipe_fds[0][0]);
    }
    if (pipe_fds[0][1] >= 0)
    {
        close(pipe_fds[0][1]);
    }
    if (pipe_fds[1][0] >= 0)
    {
        close(pipe_fds[1][0]);
    }
    if (pipe_fds[1][1] >= 0)
    {
        close(pipe_fds[1][1]);
    }
    if (sockets[0] >= 0)
    {
        closesocket(sockets[0]);
    }
    if (sockets[1] >= 0)
    {
        closesocket(sockets[1]);
    }
}

static void af_unix_test_rights_peek_and_invalid(void)
{
    char payload;
    int error;
    int invalid_fd = -1;
    int message_flags = 0;
    int pipe_fds[2] = { -1, -1 };
    int received_fds[2] = { -1, -1 };
    int sockets[2] = { -1, -1 };
    int result;
    size_t fd_count = 0;

    uassert_int_equal(socketpair(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0,
                                 sockets),
                      0);
    uassert_int_equal(pipe(pipe_fds), 0);
    if (sockets[0] < 0 || pipe_fds[0] < 0)
    {
        goto __exit;
    }

    result = af_unix_send_rights(sockets[0], &invalid_fd, 1, 'x');
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_int_equal(error, EBADF);

    uassert_int_equal(af_unix_send_rights(sockets[0], pipe_fds, 1, 'p'), 1);
    fd_count = 0;
    uassert_int_equal(af_unix_receive_rights(
                          sockets[1], MSG_PEEK, CMSG_SPACE(sizeof(int)),
                          received_fds, &fd_count, &message_flags, &payload),
                      1);
    uassert_int_equal(payload, 'p');
    uassert_int_equal(fd_count, 0);

    fd_count = 0;
    message_flags = 0;
    uassert_int_equal(af_unix_receive_rights(
                          sockets[1], 0, CMSG_SPACE(sizeof(int)),
                          received_fds, &fd_count, &message_flags, &payload),
                      1);
    uassert_int_equal(fd_count, 1);

__exit:
    if (received_fds[0] >= 0)
    {
        close(received_fds[0]);
    }
    if (pipe_fds[0] >= 0)
    {
        close(pipe_fds[0]);
    }
    if (pipe_fds[1] >= 0)
    {
        close(pipe_fds[1]);
    }
    if (sockets[0] >= 0)
    {
        closesocket(sockets[0]);
    }
    if (sockets[1] >= 0)
    {
        closesocket(sockets[1]);
    }
}

static void af_unix_test_rights_socket(void)
{
    char payload = 0;
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

    result = af_unix_send_rights(carrier[0], &passed[1], 1, 's');
    error = rt_get_errno();
    uassert_int_equal(result, -1);
    uassert_int_equal(error, EOPNOTSUPP);

    result = af_unix_receive_rights(carrier[1], MSG_DONTWAIT,
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
    if (received_fds[0] >= 0)
    {
        closesocket(received_fds[0]);
    }
    if (passed[0] >= 0)
    {
        closesocket(passed[0]);
    }
    if (passed[1] >= 0)
    {
        closesocket(passed[1]);
    }
    if (carrier[0] >= 0)
    {
        closesocket(carrier[0]);
    }
    if (carrier[1] >= 0)
    {
        closesocket(carrier[1]);
    }
}

static void af_unix_testcase(void)
{
    UTEST_UNIT_RUN(af_unix_test_dgram);
    UTEST_UNIT_RUN(af_unix_test_stream);
    UTEST_UNIT_RUN(af_unix_test_dgram_readiness);
    UTEST_UNIT_RUN(af_unix_test_stream_readiness);
    UTEST_UNIT_RUN(af_unix_test_pending_close);
    UTEST_UNIT_RUN(af_unix_test_socketpair);
    UTEST_UNIT_RUN(af_unix_test_pathname_lifetime);
    UTEST_UNIT_RUN(af_unix_test_rights_transfer);
    UTEST_UNIT_RUN(af_unix_test_rights_truncation);
    UTEST_UNIT_RUN(af_unix_test_rights_peek_and_invalid);
    UTEST_UNIT_RUN(af_unix_test_rights_socket);
}

UTEST_TC_EXPORT(af_unix_testcase, "components.net.af_unix", RT_NULL,
                RT_NULL, 20);
