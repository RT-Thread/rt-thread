/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-02-17     Bernard      First version
 * 2018-05-17     ChenYong     Add socket abstraction layer
 */

#include <dfs.h>
#include <dfs_file.h>
#include <poll.h>
#include <dfs_net.h>
#include <sys/errno.h>
#include <sys/socket.h>

int accept(int s, struct sockaddr *addr, socklen_t *addrlen)
{
    int new_socket = -1;
    int socket = dfs_net_getsocket(s);

    new_socket = sal_accept(socket, addr, addrlen);
    if (new_socket != -1)
    {
        /* this is a new socket, create it in file system fd */
        int fd;
        struct dfs_file *d;

        /* allocate a fd */
        fd = fd_new();
        if (fd < 0)
        {
            rt_set_errno(-ENOMEM);
            sal_closesocket(new_socket);
            return -1;
        }

        d = fd_get(fd);
        if(d)
        {
#ifdef RT_USING_DFS_V2
            d->fops = dfs_net_get_fops();
#endif
            /* this is a socket fd */
            d->vnode = (struct dfs_vnode *)rt_malloc(sizeof(struct dfs_vnode));
            if (!d->vnode)
            {
                /* release fd */
                fd_release(fd);
                rt_set_errno(-ENOMEM);
                return -1;
            }

            dfs_vnode_init(d->vnode, FT_SOCKET, dfs_net_get_fops());
            d->flags = O_RDWR; /* set flags as read and write */

            /* set socket to the data of dfs_file */
            d->vnode->data = (void *)(size_t)new_socket;

            return fd;
        }

        rt_set_errno(-ENOMEM);
        sal_closesocket(new_socket);
        return -1;
    }

    return -1;
}
RTM_EXPORT(accept);

int bind(int s, const struct sockaddr *name, socklen_t namelen)
{
    int socket = dfs_net_getsocket(s);

    return sal_bind(socket, name, namelen);
}
RTM_EXPORT(bind);

int shutdown(int s, int how)
{
    int error = 0;
    int socket = -1;
    struct dfs_file *d;

    socket = dfs_net_getsocket(s);
    if (socket < 0)
    {
        rt_set_errno(-ENOTSOCK);
        return -1;
    }

    d = fd_get(s);
    if (d == NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    if (sal_shutdown(socket, how) == 0)
    {
        error = 0;
    }
    else
    {
        rt_set_errno(-ENOTSOCK);
        error = -1;
    }

    return error;
}
RTM_EXPORT(shutdown);

int getpeername(int s, struct sockaddr *name, socklen_t *namelen)
{
    int socket = dfs_net_getsocket(s);

    return sal_getpeername(socket, name, namelen);
}
RTM_EXPORT(getpeername);

int getsockname(int s, struct sockaddr *name, socklen_t *namelen)
{
    int socket = dfs_net_getsocket(s);

    return sal_getsockname(socket, name, namelen);
}
RTM_EXPORT(getsockname);

int getsockopt(int s, int level, int optname, void *optval, socklen_t *optlen)
{
    int socket = dfs_net_getsocket(s);

    return sal_getsockopt(socket, level, optname, optval, optlen);
}
RTM_EXPORT(getsockopt);

int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen)
{
    int socket = dfs_net_getsocket(s);

    return sal_setsockopt(socket, level, optname, optval, optlen);
}
RTM_EXPORT(setsockopt);

int connect(int s, const struct sockaddr *name, socklen_t namelen)
{
    int socket = dfs_net_getsocket(s);
    return sal_connect(socket, name, namelen);
}
RTM_EXPORT(connect);

int listen(int s, int backlog)
{
    int socket = dfs_net_getsocket(s);

    return sal_listen(socket, backlog);
}
RTM_EXPORT(listen);

int recv(int s, void *mem, size_t len, int flags)
{
    int socket = dfs_net_getsocket(s);

    return sal_recvfrom(socket, mem, len, flags, NULL, NULL);
}
RTM_EXPORT(recv);

int sendmsg(int s, const struct msghdr *message, int flags)
{
    int socket = dfs_net_getsocket(s);

    return sal_sendmsg(socket, message, flags);
}
RTM_EXPORT(sendmsg);

int recvmsg(int s, struct msghdr *message, int flags)
{
    int socket = dfs_net_getsocket(s);

    return sal_recvmsg(socket, message, flags);
}
RTM_EXPORT(recvmsg);

int recvfrom(int s, void *mem, size_t len, int flags,
             struct sockaddr *from, socklen_t *fromlen)
{
    int socket = dfs_net_getsocket(s);

    return sal_recvfrom(socket, mem, len, flags, from, fromlen);
}
RTM_EXPORT(recvfrom);

int send(int s, const void *dataptr, size_t size, int flags)
{
    int socket = dfs_net_getsocket(s);

    return sal_sendto(socket, dataptr, size, flags, NULL, 0);
}
RTM_EXPORT(send);

int sendto(int s, const void *dataptr, size_t size, int flags,
           const struct sockaddr *to, socklen_t tolen)
{
    int socket = dfs_net_getsocket(s);

    return sal_sendto(socket, dataptr, size, flags, to, tolen);
}
RTM_EXPORT(sendto);

int socket(int domain, int type, int protocol)
{
    /* create a BSD socket */
    int fd;
    int socket;
    struct dfs_file *d;

    /* allocate a fd */
    fd = fd_new();
    if (fd < 0)
    {
        rt_set_errno(-ENOMEM);

        return -1;
    }
    d = fd_get(fd);

#ifdef RT_USING_DFS_V2
    d->fops = dfs_net_get_fops();
#endif

    d->vnode = (struct dfs_vnode *)rt_malloc(sizeof(struct dfs_vnode));
    if (!d->vnode)
    {
        /* release fd */
        fd_release(fd);
        rt_set_errno(-ENOMEM);
        return -1;
    }

    /* create socket  and then put it to the dfs_file */
    socket = sal_socket(domain, type, protocol);
    if (socket >= 0)
    {
        dfs_vnode_init(d->vnode, FT_SOCKET, dfs_net_get_fops());
        d->flags = O_RDWR; /* set flags as read and write */

        /* set socket to the data of dfs_file */
        d->vnode->data = (void *)(size_t)socket;
    }
    else
    {
        /* release fd */
        fd_release(fd);
        rt_set_errno(-ENOMEM);
        return -1;
    }

    return fd;
}
RTM_EXPORT(socket);

int closesocket(int s)
{
    int error = 0;
    int socket = -1;
    struct dfs_file *d;

    socket = dfs_net_getsocket(s);
    if (socket < 0)
    {
        rt_set_errno(-ENOTSOCK);
        return -1;
    }

    d = fd_get(s);
    if (d == RT_NULL)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    if (!d->vnode)
    {
        rt_set_errno(-EBADF);
        return -1;
    }

    if (sal_closesocket(socket) == 0)
    {
        error = 0;
    }
    else
    {
        rt_set_errno(-ENOTSOCK);
        error = -1;
    }

    /* socket has been closed, delete it from file system fd */
    fd_release(s);

    return error;
}
RTM_EXPORT(closesocket);


int socketpair(int domain, int type, int protocol, int *fds)
{
    rt_err_t ret = 0;
    int sock_fds[2];

    fds[0] = socket(domain, type, protocol);
    if (fds[0] < 0)
    {
        fds[0] = 0;
        return -1;
    }

    fds[1] = socket(domain, type, protocol);
    if (fds[1] < 0)
    {
        closesocket(fds[0]);
        fds[0] = 0;
        fds[1] = 0;
        return -1;
    }

    sock_fds[0] = dfs_net_getsocket(fds[0]);
    sock_fds[1] = dfs_net_getsocket(fds[1]);

    ret = sal_socketpair(domain, type, protocol, sock_fds);

    if (ret < 0)
    {
        closesocket(fds[0]);
        closesocket(fds[1]);
    }

    return ret;
}
RTM_EXPORT(socketpair);

int ioctlsocket(int s, long cmd, void *arg)
{
    int socket = dfs_net_getsocket(s);

    return sal_ioctlsocket(socket, cmd, arg);
}
RTM_EXPORT(ioctlsocket);
