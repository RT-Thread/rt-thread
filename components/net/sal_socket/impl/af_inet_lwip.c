/*
 * File      : af_inet_lwip.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
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
 * 2018-05-17     ChenYong     First version
 */

#include <rtthread.h>

#include <lwip/sockets.h>
#include <lwip/netdb.h>
#include <lwip/api.h>
#include <lwip/init.h>

#ifdef SAL_USING_POSIX
#include <dfs_poll.h>
#endif

#include <sal.h>
#include <af_inet.h>

#if LWIP_VERSION < 0x2000000
#define SELWAIT_T int
#else
#ifndef SELWAIT_T
#define SELWAIT_T u8_t
#endif
#endif

#ifdef SAL_USING_POSIX
/*
 * Re-define lwip socket
 *
 * NOTE: please make sure the definitions same in lwip::net_socket.c
 */
struct lwip_sock {
    /** sockets currently are built on netconns, each socket has one netconn */
    struct netconn *conn;
    /** data that was left from the previous read */
    void *lastdata;
    /** offset in the data that was left from the previous read */
    u16_t lastoffset;
    /** number of times data was received, set by event_callback(),
     tested by the receive and select functions */
    s16_t rcvevent;
    /** number of times data was ACKed (free send buffer), set by event_callback(),
     tested by select */
    u16_t sendevent;
    /** error happened for this socket, set by event_callback(), tested by select */
    u16_t errevent;
   /** last error that occurred on this socket */
#if LWIP_VERSION < 0x2000000
   int err;
#else
   u8_t err;
#endif
    /** counter of how many threads are waiting for this socket using select */
    SELWAIT_T select_waiting;

    rt_wqueue_t wait_head;
};

extern struct lwip_sock *lwip_tryget_socket(int s);

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

    if (sock->lastdata || sock->rcvevent > 0)
        event |= POLLIN;
    if (sock->sendevent)
        event |= POLLOUT;
    if (sock->errevent)
        event |= POLLERR;

    SYS_ARCH_UNPROTECT(lev);

    if (event)
    {
        rt_wqueue_wakeup(&sock->wait_head, (void*) event);
    }
}
#endif /* SAL_USING_POSIX */

static int inet_socket(int domain, int type, int protocol)
{
#ifdef SAL_USING_POSIX
    int socket;

    socket = lwip_socket(domain, type, protocol);
    if (socket >= 0)
    {
        struct lwip_sock *lwsock;

        lwsock = lwip_tryget_socket(socket);
        lwsock->conn->callback = event_callback;

        rt_wqueue_init(&lwsock->wait_head);
    }

    return socket;
#else
    return lwip_socket(domain, type, protocol);
#endif /* SAL_USING_POSIX */
}

static int inet_accept(int socket, struct sockaddr *addr, socklen_t *addrlen)
{
#ifdef SAL_USING_POSIX
    int new_socket;

    new_socket = lwip_accept(socket, addr, addrlen);
    if (new_socket >= 0)
    {
        struct lwip_sock *lwsock;

        lwsock = lwip_tryget_socket(new_socket);

        rt_wqueue_init(&lwsock->wait_head);
    }

    return new_socket;
#else
    return lwip_accept(socket, addr, addrlen);
#endif /* SAL_USING_POSIX */
}

static int inet_getsockname(int socket, struct sockaddr *name, socklen_t *namelen)
{
#if LWIP_VERSION_MAJOR < 2U
    rt_kprintf("ERROR: Your lwIP version is not supported. Please using lwIP 2.0.0+.\n");
    RT_ASSERT(LWIP_VERSION_MAJOR >= 2U);
#endif

    return lwip_getsockname(socket, name, namelen);
}

#ifdef SAL_USING_POSIX
static int inet_poll(struct dfs_fd *file, struct rt_pollreq *req)
{
    int mask = 0;
    struct lwip_sock *sock;
    struct sal_socket *sal_sock;

    sal_sock = sal_get_socket((int) file->data);
    if(!sal_sock)
    {
        return -1;
    }

    sock = lwip_tryget_socket((int)sal_sock->user_data);
    if (sock != NULL)
    {
        rt_base_t level;

        rt_poll_add(&sock->wait_head, req);

        level = rt_hw_interrupt_disable();
        if (sock->lastdata || sock->rcvevent)
        {
            mask |= POLLIN;
        }
        if (sock->sendevent)
        {
            mask |= POLLOUT;
        }
        if (sock->errevent)
        {
            mask |= POLLERR;
        }
        rt_hw_interrupt_enable(level);
    }

    return mask;
}
#endif

static const struct proto_ops lwip_inet_stream_ops = {
    inet_socket,
    lwip_close,
    lwip_bind,
    lwip_listen,
    lwip_connect,
    inet_accept,
    lwip_sendto,
    lwip_recvfrom,
    lwip_getsockopt,
    //TODO fix on 1.4.1
    lwip_setsockopt,
    lwip_shutdown,
    lwip_getpeername,
    inet_getsockname,
    lwip_ioctl,
#ifdef SAL_USING_POSIX
    inet_poll,
#endif
};

static int inet_create(struct sal_socket *socket, int type, int protocol)
{
    RT_ASSERT(socket);

    //TODO Check type & protocol

    socket->ops = &lwip_inet_stream_ops;

    return 0;
}

static const struct proto_family lwip_inet_family_ops = {
    "lwip",
    AF_INET,
    AF_INET,
    inet_create,
    lwip_gethostbyname,
    lwip_gethostbyname_r,
    lwip_freeaddrinfo,
    lwip_getaddrinfo,
};

int lwip_inet_init(void)
{
    sal_proto_family_register(&lwip_inet_family_ops);

    return 0;
}
INIT_COMPONENT_EXPORT(lwip_inet_init);
