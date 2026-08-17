/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "tc_af_unix.h"

void tc_af_unix_path(char *buf, rt_size_t size, const char *name)
{
    rt_snprintf(buf, size, "%s/%s", RT_UTEST_DFS_V2_AF_UNIX_DIR, name);
}

void tc_af_unix_make_address(struct sockaddr_un *address, const char *path)
{
    rt_memset(address, 0, sizeof(*address));
    address->sa_family = AF_UNIX;
    rt_strncpy(address->sun_path, path, sizeof(address->sun_path) - 1);
}

void tc_af_unix_closesocket(int *fd)
{
    if (*fd >= 0)
    {
        closesocket(*fd);
        *fd = -1;
    }
}

void tc_af_unix_close(int *fd)
{
    if (*fd >= 0)
    {
        close(*fd);
        *fd = -1;
    }
}

int tc_af_unix_send_rights(int socket_fd, const int *fds, size_t fd_count,
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

int tc_af_unix_receive_rights(int socket_fd, int flags, size_t control_length,
                              int *fds, size_t *fd_count, int *message_flags,
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
