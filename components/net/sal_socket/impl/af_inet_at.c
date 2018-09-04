/*
 * File      : af_inet_at.c
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
 * 2018-06-06     ChenYong     First version
 */

#include <rtthread.h>

#include <netdb.h>
#include <sal.h>

#include <at_socket.h>
#include <af_inet.h>

#ifdef SAL_USING_POSIX
#include <dfs_poll.h>
#endif

#ifdef SAL_USING_POSIX
static int at_poll(struct dfs_fd *file, struct rt_pollreq *req)
{
    int mask = 0;
    struct at_socket *sock;
    struct sal_socket *sal_sock;

    sal_sock = sal_get_socket((int) file->data);
    if(!sal_sock)
    {
        return -1;
    }

    sock = at_get_socket((int)sal_sock->user_data);
    if (sock != NULL)
    {
        rt_base_t level;

        rt_poll_add(&sock->wait_head, req);

        level = rt_hw_interrupt_disable();
        if (sock->rcvevent)
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

static const struct proto_ops at_inet_stream_ops =
{
    at_socket,
    at_closesocket,
    at_bind,
    NULL,
    at_connect,
    NULL,
    at_sendto,
    at_recvfrom,
    at_getsockopt,
    at_setsockopt,
    at_shutdown,
    NULL,
    NULL,
    NULL,

#ifdef SAL_USING_POSIX
    at_poll,
#endif /* SAL_USING_POSIX */
};

static int at_create(struct sal_socket *socket, int type, int protocol)
{
    RT_ASSERT(socket);

    //TODO Check type & protocol

    socket->ops = &at_inet_stream_ops;

    return 0;
}

static const struct proto_family at_inet_family_ops = {
    "at",
    AF_AT,
    AF_INET,
    at_create,
    at_gethostbyname,
    NULL,
    at_freeaddrinfo,
    at_getaddrinfo,
};

int at_inet_init(void)
{
    sal_proto_family_register(&at_inet_family_ops);

    return 0;
}
INIT_COMPONENT_EXPORT(at_inet_init);
