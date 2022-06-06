/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-26     xiangxistu   first version
 */

#include <rtthread.h>
#include <sal_low_lvl.h>
#include <sal_socket.h>
#include <sal_netdb.h>
#include <netdev_ipaddr.h>
#include <netdev.h>
#include "rtt_winsock.h"

static win_netdev_ping(struct netdev* netif, const char* host, size_t data_len,
    uint32_t timeout, struct netdev_ping_resp* ping_resp)
{
    return 0;
}

const struct netdev_ops win_netdev_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
#ifdef RT_USING_FINSH
    win_netdev_ping,
    RT_NULL,
#endif /* RT_USING_FINSH */
    RT_NULL,
};

 static const struct sal_socket_ops windows_socket_ops =
 {
     win_socket,
     win_closesocket,
     win_bind,
     win_listen,
     win_connect,
     win_accept,
     win_sendto,
     win_recvfrom,
     win_getsockopt,
     win_setsockopt,
     win_shutdown,
     win_getpeername,
     win_getsockname,
     win_ioctlsocket,
 #ifdef SAL_USING_POSIX
     inet_poll,
 #else
     RT_NULL,
 #endif
 };

 static const struct sal_netdb_ops windows_netdb_ops =
 {
     win_gethostbyname,
     RT_NULL,
     win_getaddrinfo,
     win_freeaddrinfo,
 };

 static const struct sal_proto_family windows_inet_family =
 {
     AF_INET,
     AF_INET6,
     &windows_socket_ops,
     &windows_netdb_ops,
 };

 /* Set lwIP network interface device protocol family information */
 int sal_win_netdev_set_pf_info(struct netdev* netdev)
 {
     RT_ASSERT(netdev);

     netdev->sal_user_data = (void*)&windows_inet_family;
     return 0;
 }

static int win_netdev_add(void)
{
#define ETHERNET_MTU        1500
#define HWADDR_LEN          6

    rt_err_t result = RT_EOK;
    struct netdev* netdev = RT_NULL;

    char name[RT_NAME_MAX] = {0};

    netdev = (struct netdev *)rt_calloc(1, sizeof(struct netdev));
    if (netdev == RT_NULL)
    {
        return -RT_EEMPTY;
    }

    sal_win_netdev_set_pf_info(netdev);

    rt_strncpy(name, "win_e0", RT_NAME_MAX);
    result = netdev_register(netdev, name, RT_NULL);

    netdev->flags = NETDEV_FLAG_UP | NETDEV_FLAG_LINK_UP | NETDEV_FLAG_INTERNET_UP;
    netdev->mtu = ETHERNET_MTU;
    netdev->ops = &win_netdev_ops;
    netdev->hwaddr_len = HWADDR_LEN;

    return result;
}
INIT_ENV_EXPORT(win_netdev_add);
