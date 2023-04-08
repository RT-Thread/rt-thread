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
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <rtthread.h>
#include <stdint.h>

#define DBG_TAG    "sal.winsock"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#include "rtt_winsock.h"

static struct sal_type_hostent sal_hostent;
static sal_type_ip_addr_t hostent_addr = { 0 };
static sal_type_ip_addr_t* hostent_addr_p = RT_NULL;

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
            LOG_E("WSAStartup failed: %d\n", iResult);          \
            return -RT_ERROR;                                   \
        }                                                       \
    }while(0)

static void data_sync_sockaddr(struct sal_type_sockaddr* sal, struct sockaddr** window)
{
    /*
     *       ws2def.h
     * typedef struct sockaddr {
     *
     * #if (_WIN32_WINNT < 0x0600)
     *     u_short sa_family;
     * #else
     *     ADDRESS_FAMILY sa_family;           // Address family.
     * #endif //(_WIN32_WINNT < 0x0600)
     *
     *     CHAR sa_data[14];                   // Up to 14 bytes of direct address.
     * } SOCKADDR, *PSOCKADDR, FAR *LPSOCKADDR;
     *
     ***********************************
     *      sal_socket.h
     * struct sockaddr
     * {
     *     uint8_t        sa_len;
     *     sa_family_t    sa_family;
     *     char           sa_data[14];
     * };
     */
    ADDRESS_FAMILY family = 0;
    family = sal->sa_family;

    *window = sal;
    (* window)->sa_family = family;
}

int win_socket(int domain, int type, int protocol)
{
    WINDOWS_PERVIOS_COMAMND;

     return (int)socket(domain, type, protocol);
}

int win_closesocket(int s)
{
    return (int)closesocket(s);
}

int win_bind(int s, const struct sal_type_sockaddr *name, sal_type_socklen_t namelen)
{
    return (int)bind(s, name, namelen);
}

int win_listen(int s, int backlog)
{
    return (int)listen(s, backlog);
}

int win_connect(int s, const struct sal_type_sockaddr *name, sal_type_socklen_t namelen)
{
    struct sockaddr *windows_addr = RT_NULL;
    data_sync_sockaddr(name, &windows_addr);

    return (int)connect(s, windows_addr, namelen);
}

int win_accept(int s, struct sal_type_sockaddr *addr, sal_type_socklen_t *addrlen)
{
    WINDOWS_PERVIOS_COMAMND;

    return (int)accept(s, addr, addrlen);
}

int win_sendto(int s, const void *data, size_t size, int flags, const struct sal_type_sockaddr *to, sal_type_socklen_t tolen)
{
    return (int)sendto(s, data, size, flags, to, tolen);
}

int win_recvfrom(int s, void *mem, size_t len, int flags, struct sal_type_sockaddr *from, sal_type_socklen_t *fromlen)
{
    return (int)recvfrom(s, mem, len, flags, from, fromlen);
}

int win_getsockopt(int s, int level, int optname, void *optval, sal_type_socklen_t *optlen)
{
    return (int)getsockopt(s, level, optname, optval, optlen);
}

int win_setsockopt(int s, int level, int optname, const void *optval, sal_type_socklen_t optlen)
{
    return (int)setsockopt(s, level, optname, optval, optlen);
}

int win_shutdown(int s, int how)
{
    return (int)shutdown(s, how);
}

int win_getpeername(int s, struct sal_type_sockaddr *name, sal_type_socklen_t *namelen)
{
    return (int)getpeername(s, name, namelen);
}

int win_getsockname(int s, struct sal_type_sockaddr *name, sal_type_socklen_t *namelen)
{
    return (int)getsockname(s, name, namelen);
}

int win_ioctlsocket(int s, long cmd, void *arg)
{
    return (int)ioctlsocket(s, cmd, arg);
}

#ifdef SAL_USING_POSIX
/* use windows poll, but not wait */
int inet_poll(struct dfs_file* file, struct rt_pollreq* req)
{
    /*
    WSAPOLLFD winpoll;
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

    return winpoll.revents;
    */

   return 0;
}
#endif /* SAL_USING_POSIX */

struct sal_type_hostent* win_gethostbyname(const char* name)
{
    struct hostent *windows_hostent;
    char** h_addr_list;

    WINDOWS_PERVIOS_COMAMND;

    windows_hostent = gethostbyname(name);

    sal_hostent.h_name = windows_hostent->h_name;
    sal_hostent.h_aliases = windows_hostent->h_aliases;
    sal_hostent.h_addrtype = windows_hostent->h_addrtype;
    sal_hostent.h_length = windows_hostent->h_length;
    sal_hostent.h_addr_list = windows_hostent->h_addr_list;
    hostent_addr.addr = ((struct in_addr*)windows_hostent->h_addr)->s_addr;
    hostent_addr_p = &hostent_addr;
    sal_hostent.h_addr_list = &hostent_addr_p;

    return &sal_hostent;
}

int win_getaddrinfo(const char* nodename, const char* servname, const struct sal_type_addrinfo* hints, struct sal_type_addrinfo** res)
{
    int port_nr = 0;
    sal_type_ip_addr_t addr = { 0 };
    struct sal_type_addrinfo* ai;
    struct sal_type_sockaddr_storage* sa;
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
        WINDOWS_PERVIOS_COMAMND;
        struct hostent* hostent = gethostbyname(nodename);
        if (hostent == RT_NULL)
            return EAI_FAIL;
        addr.addr = ((struct in_addr*)hostent->h_addr)->s_addr;
    }

    total_size = sizeof(struct sal_type_addrinfo) + sizeof(struct sal_type_sockaddr_storage);
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

    RT_ASSERT(total_size <= sizeof(struct sal_type_addrinfo) + sizeof(struct sal_type_sockaddr_storage) + DNS_MAX_NAME_LENGTH + 1);
    ai = (struct sal_type_addrinfo*)rt_malloc(total_size);
    if (ai == RT_NULL)
    {
        return EAI_MEMORY;
    }
    rt_memset(ai, 0, total_size);

    /* cast through void* to get rid of alignment warnings */
    sa = (struct sal_type_sockaddr_storage*)(void*)((uint8_t*)ai + sizeof(struct sal_type_addrinfo));
    struct sal_type_sockaddr_in* sa4 = (struct sal_type_sockaddr_in*)sa;

    sa4->sin_family = AF_INET;
    sa4->sin_addr.sal_type_s_addr = addr.addr;
    sa4->sin_port = htons((uint16_t)port_nr);

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
        ai->ai_canonname = ((char*)ai + sizeof(struct sal_type_addrinfo) + sizeof(struct sal_type_sockaddr_storage));
        rt_memcpy(ai->ai_canonname, nodename, namelen);
        ai->ai_canonname[namelen] = 0;
    }

    ai->ai_addrlen = sizeof(struct sal_type_sockaddr_storage);
    ai->ai_addr = (struct sal_type_sockaddr*)sa;
    ai->ai_family = sa4->sin_family;

    *res = ai;

    return 0;
}

void win_freeaddrinfo(struct sal_type_addrinfo* ai)
{
    struct sal_type_addrinfo* next;

    while (ai != NULL)
    {
        next = ai->ai_next;
        rt_free(ai);
        ai = next;
    }
}
