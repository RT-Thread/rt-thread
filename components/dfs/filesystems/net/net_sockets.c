/*
 * File      : lwip_sockets.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-02-17     Bernard      First version
 */

#include <dfs.h>
#include <dfs_posix.h>
#include <dfs_poll.h>
#include <sys/socket.h>

#include "dfs_net.h"

static void event_callback(struct netconn *conn, enum netconn_evt evt, u16_t len)
{
    int s;
    struct lwip_sock *sock;
    uint32_t event = 0;
    SYS_ARCH_DECL_PROTECT(lev);

    LWIP_UNUSED_ARG(len);

    /* Get socket */
    if (conn)
    {
        s = conn->socket;
        if (s < 0)
        {
            /* Data comes in right away after an accept, even though
             * the server task might not have created a new socket yet.
             * Just count down (or up) if that's the case and we
             * will use the data later. Note that only receive events
             * can happen before the new socket is set up. */
            SYS_ARCH_PROTECT(lev);
            if (conn->socket < 0)
            {
                if (evt == NETCONN_EVT_RCVPLUS)
                {
                    conn->socket--;
                }
                SYS_ARCH_UNPROTECT(lev);
                return;
            }
            s = conn->socket;
            SYS_ARCH_UNPROTECT(lev);
        }

        sock = lwip_tryget_socket(s);
        if (!sock)
        {
            return;
        }
    }
    else
    {
        return;
    }

    SYS_ARCH_PROTECT(lev);
    /* Set event as required */
    switch (evt)
    {
    case NETCONN_EVT_RCVPLUS:
        sock->rcvevent++;
        break;
    case NETCONN_EVT_RCVMINUS:
        sock->rcvevent--;
        break;
    case NETCONN_EVT_SENDPLUS:
        sock->sendevent = 1;
        break;
    case NETCONN_EVT_SENDMINUS:
        sock->sendevent = 0;
        break;
    case NETCONN_EVT_ERROR:
        sock->errevent = 1;
        break;
    default:
        LWIP_ASSERT("unknown event", 0);
        break;
    }

    if (sock->lastdata || sock->rcvevent > 0) event |= POLLIN;
    if (sock->sendevent) event |= POLLOUT;
    if (sock->errevent)  event |= POLLERR;

    SYS_ARCH_UNPROTECT(lev);

    if (event)
    {
        rt_wqueue_wakeup(&sock->wait_head, (void*)event);
    }
}

int accept(int s, struct sockaddr *addr, socklen_t *addrlen)
{
    int new_client = -1;
    int sock = dfs_net_getsocket(s);

    new_client = lwip_accept(sock, addr, addrlen);
    if (new_client != -1)
    {
        /* this is a new socket, create it in file system fd */
        int fd;
        struct dfs_fd *d;
        struct lwip_sock *lwsock;
        
        /* allocate a fd */
        fd = fd_new();
        if (fd < 0)
        {
            rt_set_errno(-ENOMEM);
            lwip_close(sock);

            return -1;
        }
        d = fd_get(fd);

        /* this is a socket fd */
        d->type = FT_SOCKET;
        d->path = RT_NULL;

        d->fops = dfs_net_get_fops();
        /* initialize wait head */
        lwsock = lwip_tryget_socket(new_client);
        rt_list_init(&(lwsock->wait_head));

        d->flags = O_RDWR; /* set flags as read and write */
        d->size = 0;
        d->pos  = 0;

        /* set socket to the data of dfs_fd */
        d->data = (void *) new_client;

        /* release the ref-count of fd */
        fd_put(d);

        return fd;
    }

    return new_client;
}
RTM_EXPORT(accept);

int bind(int s, const struct sockaddr *name, socklen_t namelen)
{
    int sock = dfs_net_getsocket(s);

    return lwip_bind(sock, name, namelen);
}
RTM_EXPORT(bind);

int shutdown(int s, int how)
{
    int sock;
    struct dfs_fd *d;

    d = fd_get(s);
    if (d == RT_NULL)
    {
        rt_set_errno(-EBADF);

        return -1;
    }

    sock = dfs_net_getsocket(s);
    if (lwip_shutdown(sock, how) == 0)
    {
        /* socket has been closed, delete it from file system fd */
        fd_put(d);
        fd_put(d);

        return 0;
    }

    return -1;
}
RTM_EXPORT(shutdown);

int getpeername(int s, struct sockaddr *name, socklen_t *namelen)
{
    int sock = dfs_net_getsocket(s);

    return lwip_getpeername(sock, name, namelen);
}
RTM_EXPORT(getpeername);

int getsockname(int s, struct sockaddr *name, socklen_t *namelen)
{
    int sock = dfs_net_getsocket(s);

    return lwip_getsockname(sock, name, namelen);
}
RTM_EXPORT(getsockname);

int getsockopt(int s, int level, int optname, void *optval, socklen_t *optlen)
{
    int sock = dfs_net_getsocket(s);

    return lwip_getsockopt(sock, level, optname, optval, optlen);
}
RTM_EXPORT(getsockopt);

int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen)
{
    int sock = dfs_net_getsocket(s);

#if LWIP_VERSION_MAJOR < 2U
#error "Your lwIP version is not supported. Please using lwIP 2.0.0+."
#endif

    return lwip_setsockopt(sock, level, optname, optval, optlen);
}
RTM_EXPORT(setsockopt);

int connect(int s, const struct sockaddr *name, socklen_t namelen)
{
    int sock = dfs_net_getsocket(s);

    return lwip_connect(sock, name, namelen);
}
RTM_EXPORT(connect);

int listen(int s, int backlog)
{
    int sock = dfs_net_getsocket(s);

    return lwip_listen(sock, backlog);
}
RTM_EXPORT(listen);

int recv(int s, void *mem, size_t len, int flags)
{
    int sock = dfs_net_getsocket(s);

    return lwip_recv(sock, mem, len, flags);
}
RTM_EXPORT(recv);

int recvfrom(int s, void *mem, size_t len, int flags,
             struct sockaddr *from, socklen_t *fromlen)
{
    int sock = dfs_net_getsocket(s);

    return lwip_recvfrom(sock, mem, len, flags, from, fromlen);
}
RTM_EXPORT(recvfrom);

int send(int s, const void *dataptr, size_t size, int flags)
{
    int sock = dfs_net_getsocket(s);

    return lwip_send(sock, dataptr, size, flags);
}
RTM_EXPORT(send);

int sendto(int s, const void *dataptr, size_t size, int flags,
           const struct sockaddr *to, socklen_t tolen)
{
    int sock = dfs_net_getsocket(s);

    return lwip_sendto(sock, dataptr, size, flags, to, tolen);
}
RTM_EXPORT(sendto);

int socket(int domain, int type, int protocol)
{
    /* create a BSD socket */
    int fd;
    int sock;
    struct dfs_fd *d;
    struct lwip_sock *lwsock;

    /* allocate a fd */
    fd = fd_new();
    if (fd < 0)
    {
        rt_set_errno(-ENOMEM);

        return -1;
    }
    d = fd_get(fd);

    /* create socket in lwip and then put it to the dfs_fd */
    sock = lwip_socket(domain, type, protocol);
    if (sock >= 0)
    {
        /* this is a socket fd */
        d->type  = FT_SOCKET;
        d->path  = NULL;

        d->fops  = dfs_net_get_fops();

        d->flags = O_RDWR; /* set flags as read and write */
        d->size  = 0;
        d->pos   = 0;

        /* set socket to the data of dfs_fd */
        d->data = (void *) sock;

        lwsock = lwip_tryget_socket(sock);
        rt_list_init(&(lwsock->wait_head));
        lwsock->conn->callback = event_callback;
    }
    else
    {
        /* release fd */
        fd_put(d);
        fd_put(d);
        
        rt_set_errno(-ENOMEM);

    	return -1;
    }

    /* release the ref-count of fd */
    fd_put(d);

    return fd;
}
RTM_EXPORT(socket);

int closesocket(int s)
{
    int sock = dfs_net_getsocket(s);
    struct dfs_fd *d;

    d = fd_get(s);

    /* socket has been closed, delete it from file system fd */
    fd_put(d);
    fd_put(d);

    return lwip_close(sock);
}
RTM_EXPORT(closesocket);

int ioctlsocket(int s, long cmd, void *arg)
{
    int sock = dfs_net_getsocket(s);

    return lwip_ioctl(sock, cmd, arg);
}
RTM_EXPORT(ioctlsocket);
