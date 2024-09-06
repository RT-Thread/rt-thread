/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-06     ChenYong     First version
 */

#include <rtthread.h>

#include <netdb.h>
#include <sal_low_lvl.h>

#include <at_socket.h>
#include <af_inet.h>

#include <netdev.h>

#ifdef SAL_USING_POSIX
#include <poll.h>
#endif

#ifdef SAL_USING_AT

#ifdef SAL_USING_POSIX
static int at_poll(struct dfs_file *file, struct rt_pollreq *req)
{
    int mask = 0;
    struct at_socket *sock;
    struct sal_socket *sal_sock;

    sal_sock = sal_get_socket((int)file->vnode->data);
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

static const struct sal_socket_ops at_socket_ops =
{
    at_socket,
    at_closesocket,
    at_bind,
#ifdef AT_USING_SOCKET_SERVER
    at_listen,
#else
    NULL,
#endif
    at_connect,
#ifdef AT_USING_SOCKET_SERVER
    at_accept,
#else
    NULL,
#endif
    at_sendto,
    NULL,
    NULL,
    at_recvfrom,
    at_getsockopt,
    at_setsockopt,
    at_shutdown,
    NULL,
    NULL,
    NULL,
    NULL,
#ifdef SAL_USING_POSIX
    at_poll,
#endif /* SAL_USING_POSIX */
};

static const struct sal_netdb_ops at_netdb_ops =
{
    at_gethostbyname,
    at_gethostbyname_r,
    at_getaddrinfo,
    at_freeaddrinfo,
};

static const struct sal_proto_family at_inet_family =
{
    AF_AT,
    AF_INET,
    &at_socket_ops,
    &at_netdb_ops,
};


/* Set AT network interface device protocol family information */
int sal_at_netdev_set_pf_info(struct netdev *netdev)
{
    RT_ASSERT(netdev);

    netdev->sal_user_data = (void *) &at_inet_family;
    return 0;
}

#endif /* SAL_USING_AT */
