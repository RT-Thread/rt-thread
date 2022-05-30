/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-26     xiangxistu   first version
 */

/* Do NOT include sys/time.h in this file */
/* Do NOT include WinSock2.h or winsock.h in this file */
#include <rtthread.h>
#include <sal_low_lvl.h>
#include <sal_socket.h>
#include <sal_netdb.h>

#define DBG_TAG    "sal.winsock"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

/* Important, must reserve */
#pragma comment( lib, "ws2_32.lib" )

/*
 * reserve for select / poll
 *
 * #define WINDOWS_STACK_SIZE 2048
 * #define WINDOWS_PRIORITY   2048
 * #define WINDOWS_TICK       10
 *
 * struct poll_thread_list
 * {
 *     int socket;
 *     rt_slist_t slist;
 * };
 * static rt_slist_t poll_pending_list = RT_SLIST_OBJECT_INIT(poll_pending_list);
 *
 **/

#define WINDOWS_PERVIOS_COMAMND                                 \
    do                                                          \
    {                                                           \
        int iResult;                                            \
        WSADATA wsa_data;                                       \
                                                                \
        iResult = WSAStartup(MAKEWORD(2, 2), &wsa_data);        \
        if (iResult != 0)                                       \
        {                                                       \
            LOG_E("WSAStartup failed: %d\n", iResult);     \
            return -RT_ERROR;                                   \
        }                                                       \
    }while(0)

int win_socket(int domain, int type, int protocol)
{
    WINDOWS_PERVIOS_COMAMND;

     return (int)socket(domain, type, protocol);
}

int win_closesocket(int s)
{
    return (int)closesocket(s);
}

int win_bind(int s, const struct sockaddr *name, socklen_t namelen)
{
    return (int)bind(s, name, namelen);
}

int win_listen(int s, int backlog)
{
    return (int)listen(s, backlog);
}

int win_connect(int s, const struct sockaddr *name, socklen_t namelen)
{
    /*
     * int result;
     * WINDOWS_PERVIOS_COMAMND;
     *
     * result = connect(s, name, namelen);
     * if (result == -1)
     * {
     *     LOG_E("error :%d\n", WSAGetLastError());
     *     return WSAGetLastError();
     * }
     * else
     * {
     *     return result;
     * }
     **/
    return (int)connect(s, name, namelen);
}

int win_accept(int s, struct sockaddr *addr, socklen_t *addrlen)
{
    WINDOWS_PERVIOS_COMAMND;
    return (int)accept(s, addr, addrlen);
}

int win_sendto(int s, const void *data, size_t size, int flags, const struct sockaddr *to, socklen_t tolen)
{
    return (int)sendto(s, data, size, flags, to, tolen);
}

int win_recvfrom(int s, void *mem, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen)
{
    return (int)recvfrom(s, mem, len, flags, from, fromlen);
}

int win_getsockopt(int s, int level, int optname, void *optval, socklen_t *optlen)
{
    return (int)getsockopt(s, level, optname, optval, optlen);
}

int win_setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen)
{
    return (int)setsockopt(s, level, optname, optval, optlen);
}

int win_shutdown(int s, int how)
{
    return (int)shutdown(s, how);
}

int win_getpeername(int s, struct sockaddr *name, socklen_t *namelen)
{
    return (int)getpeername(s, name, namelen);
}

int win_getsockname(int s, struct sockaddr *name, socklen_t *namelen)
{
    return (int)getsockname(s, name, namelen);
}

int win_ioctlsocket(int s, long cmd, void *arg)
{
    return (int)ioctlsocket(s, cmd, arg);
}

#ifdef SAL_USING_POSIX
/* use windows poll, but not wait */
static int inet_poll(struct dfs_fd* file, struct rt_pollreq* req)
{
    /*WSAPOLLFD winpoll;
    struct sal_socket* sal_sock;
    int mask = 0;
    int poll_event = 0;

    sal_sock = sal_get_socket((int)file->data);
    if (!sal_sock)
    {
        return -1;
    }

    winpoll.fd = sal_sock->socket;
    poll_event &= POLLERR | POLLHUP;
    winpoll.events = req->_key & (~poll_event);
    poll_event = 0;

    mask = WSAPoll(&winpoll, 1, 0);
    if (mask == 0)
        return 0;

    return winpoll.revents;*/
}
#endif

static struct hostent* win_gethostbyname(const char* name)
{
    WINDOWS_PERVIOS_COMAMND;
    return gethostbyname(name);
}

static int win_getaddrinfo(const char* nodename, const char* servname, const struct addrinfo* hints, struct addrinfo** res)
{
    int port_nr = 0;
    ip_addr_t addr = { 0 };
    struct addrinfo* ai;
    struct sockaddr_storage* sa;
    size_t total_size = 0;
    size_t namelen = 0;
    char* change_point;

    if (res == RT_NULL)
        return EAI_FAIL;
    *res = RT_NULL;

    if ((nodename == RT_NULL) && (servname == RT_NULL))
        return EAI_NONAME;

    if ((hints != RT_NULL)
        && (hints->ai_family != AF_INET && hints->ai_family != AF_UNSPEC))
        return EAI_FAMILY;

    if (servname != RT_NULL)
    {
        /* service name specified: convert to port number */
        port_nr = atoi(servname);
        if ((port_nr <= 0) || (port_nr > 0xffff))
        {
            return EAI_SERVICE;
        }
    }

    if (nodename != RT_NULL)
    {
        struct hostent* hostent = win_gethostbyname(nodename);
        if (hostent == RT_NULL)
            return EAI_FAIL;

#if NETDEV_IPV4 && NETDEV_IPV6
        addr.type = IPADDR_TYPE_V4;
        if ((addr.u_addr.ip4.addr = ((struct in_addr*)hostent->h_addr)->s_addr) == 0)
        {
            return EAI_FAIL;
        }
#elif NETDEV_IPV4
        addr.addr = ((struct in_addr*)hostent->h_addr)->s_addr;
#elif NETDEV_IPV6
#error "not support IPV6."
#endif /* NETDEV_IPV4 && NETDEV_IPV6 */
    }

    total_size = sizeof(struct addrinfo) + sizeof(struct sockaddr_storage);
    if (nodename != RT_NULL)
    {
        namelen = strlen(nodename);
        if (namelen > DNS_MAX_NAME_LENGTH)
        {
            /* invalid name length */
            return EAI_FAIL;
        }
        RT_ASSERT(total_size + namelen + 1 > total_size);
        total_size += namelen + 1;
    }
    /* If this fails, please report to lwip-devel! :-) */
    RT_ASSERT(total_size <= sizeof(struct addrinfo) + sizeof(struct sockaddr_storage) + DNS_MAX_NAME_LENGTH + 1);
    ai = (struct addrinfo*)rt_malloc(total_size);
    if (ai == RT_NULL)
    {
        return EAI_MEMORY;
    }
    rt_memset(ai, 0, total_size);
    /* cast through void* to get rid of alignment warnings */
    sa = (struct sockaddr_storage*)(void*)((uint8_t*)ai + sizeof(struct addrinfo));
    struct sockaddr_in* sa4 = (struct sockaddr_in*)sa;

    sa4->sin_family = AF_INET;
    sa4->sin_addr.S_un.S_addr = addr.addr;
    sa4->sin_port = htons((uint16_t)port_nr);


    ai->ai_family = AF_INET;
    /* set up addrinfo */
    if (hints != RT_NULL)
    {
        /* copy socktype & protocol from hints if specified */
        ai->ai_socktype = hints->ai_socktype;
        ai->ai_protocol = hints->ai_protocol;
    }
    if (nodename != RT_NULL)
    {
        /* copy nodename to canonname if specified */
        ai->ai_canonname = ((char*)ai + sizeof(struct addrinfo) + sizeof(struct sockaddr_storage));
        rt_memcpy(ai->ai_canonname, nodename, namelen);
        ai->ai_canonname[namelen] = 0;
    }
    ai->ai_addrlen = sizeof(struct sockaddr_storage);
    ai->ai_addr = (struct sockaddr*)sa;

    /* change  ai_canonname <-> ai_addr
     *
     * Win2scok.h
     * typedef struct addrinfo
     * {
     *     int                 ai_flags;       // AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST
     *     int                 ai_family;      // PF_xxx
     *     int                 ai_socktype;    // SOCK_xxx
     *     int                 ai_protocol;    // 0 or IPPROTO_xxx for IPv4 and IPv6
     *     size_t              ai_addrlen;     // Length of ai_addr
     *     char* ai_canonname;   // Canonical name for nodename                              <------
     *     _Field_size_bytes_(ai_addrlen) struct sockaddr* ai_addr;        // Binary address <------
     *     struct addrinfo* ai_next;        // Next structure in linked list
     * }
     * ADDRINFOA, * PADDRINFOA;
     *
     * *********************
     *
     * sal.h
     *
     * struct addrinfo {
     * int               ai_flags;
     * int               ai_family;
     * int               ai_socktype;
     * int               ai_protocol;
     * socklen_t         ai_addrlen;
     * struct sockaddr* ai_addr;      <------
     * char* ai_canonname;            <------
     * struct addrinfo* ai_next;
     * };
     **/
    change_point = ai->ai_addr;
    ai->ai_addr = ai->ai_canonname;
    ai->ai_canonname = change_point;

    *res = ai;

    return 0;
}

static void win_freeaddrinfo(struct addrinfo* ai)
{
    struct addrinfo* next;

    while (ai != NULL)
    {
        next = ai->ai_next;
        rt_free(ai);
        ai = next;
    }
}

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

#include <netdev.h>
#include <netdev_ipaddr.h>
/* Set lwIP network interface device protocol family information */
int sal_win_netdev_set_pf_info(struct netdev* netdev)
{
    RT_ASSERT(netdev);

    netdev->sal_user_data = (void*)&windows_inet_family;
    return 0;
}
