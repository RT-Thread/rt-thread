/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-06     chenyong     first version
 * 2022-06-02     xianxistu    add implement about "AT server"
 */

#include <at.h>
#ifdef AT_USING_SOCKET_SERVER
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/errno.h>

#include <at_socket.h>
#include <at_device.h>

#ifdef SAL_USING_POSIX
#include <poll.h>
#endif

#include <arpa/inet.h>
#include <netdev.h>

#define LOG_TAG              "at.skt"
#include <at_log.h>

#ifdef AT_USING_SOCKET

#define HTONS_PORT(x) ((((x) & 0x00ffUL) << 8) | (((x) & 0xff00UL) >> 8))
#define NIPQUAD(addr) \
        ((unsigned char *)&addr)[0], \
        ((unsigned char *)&addr)[1], \
        ((unsigned char *)&addr)[2], \
        ((unsigned char *)&addr)[3]

/* The maximum number of sockets structure */
#ifndef AT_SOCKETS_NUM
#define AT_SOCKETS_NUM       AT_DEVICE_SOCKETS_NUM
#endif

typedef enum {
    AT_EVENT_SEND,
    AT_EVENT_RECV,
    AT_EVENT_ERROR,
} at_event_t;

#ifdef AT_USING_SOCKET_SERVER
static void at_connect_notice_cb(struct at_socket *sock, at_socket_evt_t event, const char *buff, size_t bfsz);
#endif

static rt_mutex_t at_slock = RT_NULL;

/* the global of sockets list */
static rt_slist_t _socket_list = RT_SLIST_OBJECT_INIT(_socket_list);

struct at_socket *at_get_socket(int socket)
{
    rt_base_t level;
    rt_slist_t *node = RT_NULL;
    struct at_socket *at_sock = RT_NULL;

    level = rt_hw_interrupt_disable();

    rt_slist_for_each(node, &_socket_list)
    {
        at_sock = rt_slist_entry(node, struct at_socket, list);
        if (at_sock && socket == at_sock->socket)
        {
            if (at_sock->magic == AT_SOCKET_MAGIC)
            {
                rt_hw_interrupt_enable(level);
                return at_sock;
            }
        }
    }

    rt_hw_interrupt_enable(level);

    return RT_NULL;
}

#ifdef AT_USING_SOCKET_SERVER
struct at_socket *at_get_base_socket(int base_socket)
{
    rt_base_t level;
    rt_slist_t *node = RT_NULL;
    struct at_socket *at_sock = RT_NULL;

    level = rt_hw_interrupt_disable();

    rt_slist_for_each(node, &_socket_list)
    {
        at_sock = rt_slist_entry(node, struct at_socket, list);
        if (at_sock && base_socket == (int)at_sock->user_data && at_sock->state != AT_SOCKET_LISTEN)
        {
            if (at_sock->magic == AT_SOCKET_MAGIC)
            {
                rt_hw_interrupt_enable(level);
                return at_sock;
            }
        }
    }

    rt_hw_interrupt_enable(level);

    return RT_NULL;
}
#endif

/* get a block to the AT socket receive list*/
static rt_err_t at_recvpkt_put(rt_slist_t *rlist, const char *ptr, size_t length)
{
    at_recv_pkt_t pkt = RT_NULL;

    pkt = (at_recv_pkt_t) rt_calloc(1, sizeof(struct at_recv_pkt));
    if (pkt == RT_NULL)
    {
        LOG_E("No memory for receive packet table!");
        return -RT_ENOMEM;
    }

    pkt->bfsz_totle = length;
    pkt->bfsz_index = 0;
    pkt->buff = (char *) ptr;

    rt_slist_append(rlist, &pkt->list);

    return RT_EOK;
}

/* delete and free all receive buffer list */
static int at_recvpkt_all_delete(rt_slist_t *rlist)
{
    at_recv_pkt_t pkt = RT_NULL;
    rt_slist_t *node = RT_NULL;

    if (rt_slist_isempty(rlist))
    {
        return 0;
    }

    for(node = rt_slist_first(rlist); node;)
    {
        pkt = rt_slist_entry(node, struct at_recv_pkt, list);
        node = rt_slist_next(node);
        if (pkt && pkt->buff)
        {
            rt_free(pkt->buff);
        }
        if (pkt)
        {
            rt_free(pkt);
            pkt = RT_NULL;
        }
    }

    return 0;
}

/* delete and free specified list block */
static int at_recvpkt_node_delete(rt_slist_t *rlist, rt_slist_t *node)
{
    at_recv_pkt_t pkt = RT_NULL;

    if (rt_slist_isempty(rlist))
    {
        return 0;
    }

    rt_slist_remove(rlist, node);

    pkt = rt_slist_entry(node, struct at_recv_pkt, list);
    if (pkt && pkt->buff)
    {
        rt_free(pkt->buff);
    }
    if (pkt)
    {
        rt_free(pkt);
        pkt = RT_NULL;
    }

    return 0;
}

/* get a block from AT socket receive buffer list */
static size_t at_recvpkt_get(rt_slist_t *rlist, char *mem, size_t len)
{
    rt_slist_t *node = RT_NULL;
    rt_slist_t *free_node = RT_NULL;
    at_recv_pkt_t pkt = RT_NULL;
    size_t content_pos = 0, page_pos = 0;

    if (rt_slist_isempty(rlist))
    {
        return 0;
    }

    for (node = rt_slist_first(rlist); node;)
    {
        pkt = rt_slist_entry(node, struct at_recv_pkt, list);

        free_node = node;
        node = rt_slist_next(node);

        if (!pkt) continue;

        page_pos = pkt->bfsz_totle - pkt->bfsz_index;

        if (page_pos >= len - content_pos)
        {
            rt_memcpy((char *) mem + content_pos, pkt->buff + pkt->bfsz_index, len - content_pos);
            pkt->bfsz_index += len - content_pos;
            if (pkt->bfsz_index == pkt->bfsz_totle)
            {
                at_recvpkt_node_delete(rlist, free_node);
            }
            content_pos = len;
            break;
        }
        else
        {
            rt_memcpy((char *) mem + content_pos, pkt->buff + pkt->bfsz_index, page_pos);
            content_pos += page_pos;
            pkt->bfsz_index += page_pos;
            at_recvpkt_node_delete(rlist, free_node);
        }
    }

    return content_pos;
}

static void at_do_event_changes(struct at_socket *sock, at_event_t event, rt_bool_t is_plus)
{
    switch (event)
    {
    case AT_EVENT_SEND:
    {
        if (is_plus)
        {
            sock->sendevent = 1;

#ifdef SAL_USING_POSIX
            rt_wqueue_wakeup(&sock->wait_head, (void*) POLLOUT);
#endif
        }
        else if (sock->sendevent)
        {
            sock->sendevent = 0;
        }
        break;
    }
    case AT_EVENT_RECV:
    {
        if (is_plus)
        {
            sock->rcvevent++;

#ifdef SAL_USING_POSIX
            rt_wqueue_wakeup(&sock->wait_head, (void*) POLLIN);
#endif
        }
        else if (sock->rcvevent)
        {
            sock->rcvevent --;
        }
        break;
    }
    case AT_EVENT_ERROR:
    {
        if (is_plus)
        {
            sock->errevent++;

#ifdef SAL_USING_POSIX
            rt_wqueue_wakeup(&sock->wait_head, (void*) POLLERR);
#endif
        }
        else if (sock->errevent)
        {
            sock->errevent --;
        }
        break;
    }
    default:
        LOG_E("Not supported event (%d)", event);
    }
}

static void at_do_event_clean(struct at_socket *sock, at_event_t event)
{
    switch (event)
    {
    case AT_EVENT_SEND:
    {
        sock->sendevent = 0;
        break;
    }
    case AT_EVENT_RECV:
    {
        sock->rcvevent = 0;
        break;
    }
    case AT_EVENT_ERROR:
    {
        sock->errevent = 0;
        break;
    }
    default:
        LOG_E("Not supported event (%d)", event);
    }
}

static int free_socket(struct at_socket *sock)
{
    if (at_slock == RT_NULL)
    {
        /* create AT socket lock */
        at_slock = rt_mutex_create("at_slock", RT_IPC_FLAG_PRIO);
        if (at_slock == RT_NULL)
        {
            LOG_E("No memory for socket allocation lock!");
            return RT_NULL;
        }
    }

    rt_mutex_take(at_slock, RT_WAITING_FOREVER);
    if (sock->recv_notice)
    {
        rt_sem_delete(sock->recv_notice);
    }

    if (sock->recv_lock)
    {
        rt_mutex_delete(sock->recv_lock);
    }

    if (!rt_slist_isempty(&sock->recvpkt_list))
    {
        at_recvpkt_all_delete(&sock->recvpkt_list);
    }

    /* delect socket from socket list */
    {
        rt_base_t level;
        rt_slist_t *node = RT_NULL;
        struct at_socket *at_sock = RT_NULL;

        level = rt_hw_interrupt_disable();

        rt_slist_for_each(node, &_socket_list)
        {
            at_sock = rt_slist_entry(node, struct at_socket, list);
            if (at_sock && sock->socket == at_sock->socket)
            {
                if (at_sock->magic == AT_SOCKET_MAGIC)
                {
                    rt_slist_remove(&_socket_list, &at_sock->list);
                    break;
                }
            }
        }

        rt_hw_interrupt_enable(level);
    }

    rt_memset(sock, RT_NULL, sizeof(struct at_socket));
    rt_mutex_release(at_slock);
    return 0;
}

static struct at_socket *alloc_socket_by_device(struct at_device *device, enum at_socket_type type)
{
    rt_base_t level;
    struct at_socket *sock = RT_NULL;
    char name[RT_NAME_MAX] = {0};
    int idx = 0;

    if (at_slock == RT_NULL)
    {
        /* create AT socket lock */
        at_slock = rt_mutex_create("at_slock", RT_IPC_FLAG_PRIO);
        if (at_slock == RT_NULL)
        {
            LOG_E("No memory for socket allocation lock!");
            return RT_NULL;
        }
    }

    rt_mutex_take(at_slock, RT_WAITING_FOREVER);

    /* find an empty at socket entry */
    if (device->class->socket_ops->at_socket != RT_NULL)
    {
        idx = device->class->socket_ops->at_socket(device, type);
    }
    else
    {
        for (idx = 0; idx < device->class->socket_num && device->sockets[idx].magic == AT_SOCKET_MAGIC; idx++);
    }

    /* can't find an empty protocol family entry */
    if (idx < 0 || idx >= device->class->socket_num)
    {
        LOG_E("can't find an empty protocol family entry.");
        goto __err;
    }

    sock = &(device->sockets[idx]);
    /* the socket descriptor is the number of sockte lists */
    sock->socket = idx;
    /* the socket operations is the specify operations of the device */
    sock->ops = device->class->socket_ops;
    /* the user-data is the at device socket descriptor */
    sock->user_data = (void *) idx;
    sock->device = (void *) device;
    sock->magic = AT_SOCKET_MAGIC;
    sock->state = AT_SOCKET_NONE;
    sock->rcvevent = RT_NULL;
    sock->sendevent = RT_NULL;
    sock->errevent = RT_NULL;

    rt_slist_init(&(sock->list));
    level = rt_hw_interrupt_disable();
    rt_slist_insert(&_socket_list, &(sock->list));
    rt_hw_interrupt_enable(level);

    rt_slist_init(&sock->recvpkt_list);
#ifdef SAL_USING_POSIX
    rt_wqueue_init(&sock->wait_head);
#endif

    rt_snprintf(name, RT_NAME_MAX, "%s%d", "at_skt", idx);
    /* create AT socket receive semaphore */
    if ((sock->recv_notice = rt_sem_create(name, 0, RT_IPC_FLAG_FIFO)) == RT_NULL)
    {
        LOG_E("No memory socket receive notic semaphore create.");
        goto __err;
    }
    /* set AT socket receive semaphore 'max_value' to 1 */
    rt_sem_control(sock->recv_notice, RT_IPC_CMD_SET_VLIMIT, (void *)1);

    rt_snprintf(name, RT_NAME_MAX, "%s%d", "at_skt", idx);
    /* create AT socket receive ring buffer lock */
    if((sock->recv_lock = rt_mutex_create(name, RT_IPC_FLAG_PRIO)) == RT_NULL)
    {
        LOG_E("No memory for socket receive mutex create.");
        goto __err;
    }

    rt_mutex_release(at_slock);
    return sock;

__err:
    rt_mutex_release(at_slock);
    if(sock != RT_NULL)
    {
        free_socket(sock);
    }
    return RT_NULL;
}

static struct at_socket *alloc_socket(enum at_socket_type type)
{
    extern struct netdev *netdev_default;
    struct netdev *netdev = RT_NULL;
    struct at_device *device = RT_NULL;

    if (netdev_default && netdev_is_up(netdev_default) &&
            netdev_family_get(netdev_default) == AF_AT)
    {
        netdev = netdev_default;
    }
    else
    {
        /* get network interface device by protocol family AF_AT */
        netdev = netdev_get_by_family(AF_AT);
        if (netdev == RT_NULL)
        {
            return RT_NULL;
        }
    }

    device = at_device_get_by_name(AT_DEVICE_NAMETYPE_NETDEV, netdev->name);
    if (device == RT_NULL)
    {
        return RT_NULL;
    }

    return alloc_socket_by_device(device, type);
}

static void at_recv_notice_cb(struct at_socket *sock, at_socket_evt_t event, const char *buff, size_t bfsz);
static void at_closed_notice_cb(struct at_socket *sock, at_socket_evt_t event, const char *buff, size_t bfsz);

int at_socket(int domain, int type, int protocol)
{
    struct at_socket *sock = RT_NULL;
    enum at_socket_type socket_type;

    /* check socket family protocol */
    if(domain != AF_INET && domain != AF_AT)
    {
        rt_set_errno(EAFNOSUPPORT);
        return -1;
    }

    /*TODO check protocol*/

    switch(type)
    {
    case SOCK_STREAM:
        socket_type = AT_SOCKET_TCP;
        break;

    case SOCK_DGRAM:
        socket_type = AT_SOCKET_UDP;
        break;

    default :
        LOG_E("Don't support socket type (%d)!", type);
        rt_set_errno(EPROTOTYPE);
        return -1;
    }

    /* allocate and initialize a new AT socket */
    sock = alloc_socket(socket_type);
    if (sock == RT_NULL)
    {
        LOG_E("Failed to allocate socket");
        rt_set_errno(EIO);
        return -1;
    }
    sock->type = socket_type;
    sock->state = AT_SOCKET_OPEN;

    /* set AT socket receive data callback function */
    sock->ops->at_set_event_cb(AT_SOCKET_EVT_RECV, at_recv_notice_cb);
    sock->ops->at_set_event_cb(AT_SOCKET_EVT_CLOSED, at_closed_notice_cb);
#ifdef AT_USING_SOCKET_SERVER
    sock->ops->at_set_event_cb(AT_SOCKET_EVT_CONNECTED, at_connect_notice_cb);
#endif

    return sock->socket;
}

int at_closesocket(int socket)
{
    struct at_socket *sock = RT_NULL;
    enum at_socket_state last_state;

    /* deal with TCP server actively disconnect */
    rt_thread_delay(rt_tick_from_millisecond(100));

    sock = at_get_socket(socket);
    if (sock == RT_NULL)
    {
        rt_set_errno(ENXIO);
        return -1;
    }

    last_state = sock->state;

    /* the rt_at_socket_close is need some time, so change state in advance */
    sock->state = AT_SOCKET_CLOSED;

    if (last_state != AT_SOCKET_CLOSED)
    {
        if (sock->ops->at_closesocket(sock) != 0)
        {
            free_socket(sock);
            rt_set_errno(EIO);
            return -1;
        }
    }

    free_socket(sock);
    return 0;
}

int at_shutdown(int socket, int how)
{
    struct at_socket *sock = RT_NULL;
    enum at_socket_state last_state;

    sock = at_get_socket(socket);
    if (sock == RT_NULL)
    {
        rt_set_errno(ENXIO);
        return -1;
    }

    last_state = sock->state;

    /* the rt_at_socket_close is need some time, so change state in advance */
    sock->state = AT_SOCKET_CLOSED;

    if (last_state != AT_SOCKET_CLOSED)
    {
        if (sock->ops->at_closesocket(sock) != 0)
        {
            free_socket(sock);
            rt_set_errno(EIO);
            return -1;
        }
    }

    free_socket(sock);
    return 0;
}

/* get IP address and port by socketaddr structure information */
static int socketaddr_to_ipaddr_port(const struct sockaddr *sockaddr, ip_addr_t *addr, uint16_t *port)
{
    const struct sockaddr_in* sin = (const struct sockaddr_in*) (const void *) sockaddr;

#if NETDEV_IPV4 && NETDEV_IPV6
    addr->u_addr.ip4.addr = sin->sin_addr.s_addr;
    addr->type = IPADDR_TYPE_V4;
#elif NETDEV_IPV4
    addr->addr = sin->sin_addr.s_addr;
#elif NETDEV_IPV6
#error "not support IPV6."
#endif /* NETDEV_IPV4 && NETDEV_IPV6 */

    *port = (uint16_t) HTONS_PORT(sin->sin_port);

    return 0;
}

#ifdef AT_USING_SOCKET_SERVER
/* set socketaddr structure information by IP address and port */
static int ipaddr_port_to_socketaddr(struct sockaddr *sockaddr, ip_addr_t *addr, uint16_t *port)
{
    struct sockaddr_in* sin = (struct sockaddr_in*) (void *) sockaddr;

#if NETDEV_IPV4 && NETDEV_IPV6
    sin->sin_addr.s_addr = addr->u_addr.ip4.addr;
#elif NETDEV_IPV4
    sin->sin_addr.s_addr = addr->addr;
#elif NETDEV_IPV6
#error "not support IPV6."
#endif /* NETDEV_IPV4 && NETDEV_IPV6 */

    sin->sin_port = (uint16_t) HTONS_PORT(*port);

    return 0;
}
#endif

int at_bind(int socket, const struct sockaddr *name, socklen_t namelen)
{
    struct at_socket *sock = RT_NULL;
    struct at_device *device = RT_NULL;
    ip_addr_t input_ipaddr, local_ipaddr;
    uint16_t port = 0;

    if (name == NULL || namelen == 0)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    sock = at_get_socket(socket);
    if (sock == RT_NULL)
    {
        rt_set_errno(ENXIO);
        return -1;
    }

    /* get current device ip address */
    device = (struct at_device *) sock->device;
    ip_addr_copy(local_ipaddr, device->netdev->ip_addr);

    /* prase ip address and port from sockaddr structure */
    socketaddr_to_ipaddr_port(name, &input_ipaddr, &port);

    /* input ip address is different from device ip address */
    if (ip_addr_cmp(&input_ipaddr, &local_ipaddr) != 0)
    {
        struct at_socket *new_sock = RT_NULL;
        struct at_device *new_device = RT_NULL;
        enum at_socket_type type = sock->type;

        /* close old socket */
        if (at_closesocket(socket) < 0)
        {
            free_socket(sock);
            rt_set_errno(EIO);
            return -1;
        }

        extern struct at_device *at_device_get_by_ipaddr(ip_addr_t *ip_addr);
        new_device = at_device_get_by_ipaddr(&input_ipaddr);
        if (new_device == RT_NULL)
        {
            rt_set_errno(EHOSTUNREACH);
            return -1;
        }

        /* allocate new socket */
        new_sock = alloc_socket_by_device(new_device, type);
        if (new_sock == RT_NULL)
        {
            rt_set_errno(EIO);
            return -1;
        }
        new_sock->type = type;
        new_sock->state = AT_SOCKET_OPEN;
    }

#ifdef AT_USING_SOCKET_SERVER
    /* store 'port' into at_socket */
    sock->listen.port = port;
#endif

    return 0;
}

/* ipaddr structure change to IP address */
static int ipaddr_to_ipstr(const struct sockaddr *sockaddr, char *ipstr)
{
    struct sockaddr_in *sin = (struct sockaddr_in *) sockaddr;

    /* change network ip_addr to ip string  */
    rt_snprintf(ipstr, 16, "%u.%u.%u.%u", NIPQUAD(sin->sin_addr.s_addr));

    return 0;
}

#ifdef AT_USING_SOCKET_SERVER
static void at_connect_notice_cb(struct at_socket *sock, at_socket_evt_t event, const char *buff, size_t bfsz)
{
    RT_ASSERT(buff);
    RT_ASSERT(sock == RT_NULL);
    RT_ASSERT(event == AT_SOCKET_EVT_CONNECTED);

    int new_socket;
    struct at_socket *new_sock = RT_NULL;
    rt_base_t level;
    rt_slist_t *node = RT_NULL;
    struct at_socket *at_sock = RT_NULL;
    char *socket_info = RT_NULL;
    int base_socket = 0;

    /* avoid use bottom driver to alloc "socket" */
    new_socket = at_socket(AF_AT, SOCK_STREAM, 0);
    if (new_socket == -1)
    {
        return;
    }
    new_sock = at_get_socket(new_socket);
    new_sock->state = AT_SOCKET_CONNECT;
    rt_sscanf(buff, "SOCKET:%d", &base_socket);
    LOG_D("ACCEPT BASE SOCKET: %d", base_socket);
    new_sock->user_data = (void *)base_socket;

    /* find out the listen socket */
    level = rt_hw_interrupt_disable();
    rt_slist_for_each(node, &_socket_list)
    {
        at_sock = rt_slist_entry(node, struct at_socket, list);
        if (at_sock && at_sock->magic == AT_SOCKET_MAGIC && at_sock->listen.is_listen == RT_TRUE)
        {
            break;
        }
        at_sock = RT_NULL;
    }
    rt_hw_interrupt_enable(level);

    if (at_sock == RT_NULL)
    {
        at_closesocket(new_socket);
        return;
    }

    /* put incoming "socket" to the listen socket receiver packet list */
    socket_info = rt_malloc(AT_SOCKET_INFO_LEN);
    rt_memset(socket_info, 0, AT_SOCKET_INFO_LEN);
    rt_sprintf(socket_info, "SOCKET:%d", new_sock->socket);

    /* wakeup the "accept" function */
    rt_mutex_take(at_sock->recv_lock, RT_WAITING_FOREVER);
    if (at_recvpkt_put(&(at_sock->recvpkt_list), socket_info, AT_SOCKET_INFO_LEN) != RT_EOK)
    {
        at_closesocket(new_socket);
        rt_free(socket_info);
        rt_mutex_release(at_sock->recv_lock);
        return;
    }
    rt_mutex_release(at_sock->recv_lock);
    rt_sem_release(at_sock->recv_notice);

    at_do_event_changes(at_sock, AT_EVENT_RECV, RT_TRUE);
}
#endif

static void at_recv_notice_cb(struct at_socket *sock, at_socket_evt_t event, const char *buff, size_t bfsz)
{
    RT_ASSERT(buff);
    RT_ASSERT(event == AT_SOCKET_EVT_RECV);

    /* check the socket object status */
    if (sock->magic != AT_SOCKET_MAGIC || sock->state == AT_SOCKET_CLOSED)
    {
        rt_free((void *)buff);
        return;
    }

    /* put receive buffer to receiver packet list */
    rt_mutex_take(sock->recv_lock, RT_WAITING_FOREVER);
    if (at_recvpkt_put(&(sock->recvpkt_list), buff, bfsz) != RT_EOK)
    {
        rt_free((void *)buff);
        rt_mutex_release(sock->recv_lock);
        return;
    }
    rt_mutex_release(sock->recv_lock);

    rt_sem_release(sock->recv_notice);

    at_do_event_changes(sock, AT_EVENT_RECV, RT_TRUE);
}

static void at_closed_notice_cb(struct at_socket *sock, at_socket_evt_t event, const char *buff, size_t bfsz)
{
    RT_ASSERT(event == AT_SOCKET_EVT_CLOSED);

    /* check the socket object status */
    if (sock->magic != AT_SOCKET_MAGIC)
    {
        return;
    }

    at_do_event_changes(sock, AT_EVENT_RECV, RT_TRUE);
    at_do_event_changes(sock, AT_EVENT_ERROR, RT_TRUE);

    sock->state = AT_SOCKET_CLOSED;
    rt_sem_release(sock->recv_notice);
}

#ifdef AT_USING_SOCKET_SERVER
int at_listen(int socket, int backlog)
{
    struct at_socket *sock = RT_NULL;
    int result = 0;

    sock = at_get_socket(socket);
    if (sock == RT_NULL)
    {
        rt_set_errno(ENXIO);
        return -1;
    }

    if (sock->state != AT_SOCKET_OPEN)
    {
        LOG_E("Socket(%d) connect state is %d.", sock->socket, sock->state);
        rt_set_errno(ENETUNREACH);
        result = -1;
        goto __exit;
    }

    if (sock->ops->at_listen(sock, backlog) < 0)
    {
        rt_set_errno(EIO);
        result = -1;
        goto __exit;
    }

    sock->listen.is_listen = RT_TRUE;
    sock->state = AT_SOCKET_LISTEN;

__exit:
    if (result < 0)
    {
        at_do_event_changes(sock, AT_EVENT_ERROR, RT_TRUE);
    }

    return result;
}
#endif

int at_connect(int socket, const struct sockaddr *name, socklen_t namelen)
{
    struct at_socket *sock = RT_NULL;
    ip_addr_t remote_addr;
    uint16_t remote_port = 0;
    char ipstr[16] = { 0 };
    int result = 0;

    if (name == RT_NULL || namelen == 0)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    sock = at_get_socket(socket);
    if (sock == RT_NULL)
    {
        rt_set_errno(ENXIO);
        return -1;
    }

    if (sock->state != AT_SOCKET_OPEN)
    {
        LOG_E("Socket(%d) connect state is %d.", sock->socket, sock->state);
        rt_set_errno(EPERM);
        result = -1;
        goto __exit;
    }

    /* get IP address and port by socketaddr structure */
    socketaddr_to_ipaddr_port(name, &remote_addr, &remote_port);
    ipaddr_to_ipstr(name, ipstr);

    if (sock->ops->at_connect(sock, ipstr, remote_port, sock->type, RT_TRUE) < 0)
    {
        rt_set_errno(EIO);
        result = -1;
        goto __exit;
    }

    sock->state = AT_SOCKET_CONNECT;

__exit:
    if (result < 0)
    {
        at_do_event_changes(sock, AT_EVENT_ERROR, RT_TRUE);
    }
    else
    {
        at_do_event_changes(sock, AT_EVENT_SEND, RT_TRUE);
    }

    return result;
}

#ifdef AT_USING_SOCKET_SERVER
int at_accept(int socket, struct sockaddr *name, socklen_t *namelen)
{
    struct at_socket *sock = RT_NULL;
    struct at_socket *new_sock = RT_NULL;
    char receive_buff[AT_SOCKET_INFO_LEN];
    ip_addr_t remote_addr;
    uint16_t remote_port = 0;
    int new_socket = -1;
    int result = 0;

    sock = at_get_socket(socket);
    if (sock == RT_NULL)
    {
        rt_set_errno(ENXIO);
        return -1;
    }

    if (sock->state != AT_SOCKET_LISTEN)
    {
        LOG_E("Socket(%d) connect state is %d.", sock->socket, sock->state);
        rt_set_errno(EIO);
        result = -1;
        goto __exit;
    }

    /* wait the receive semaphore, waiting for info */
    if (rt_sem_take(sock->recv_notice, RT_WAITING_FOREVER) != RT_EOK)
    {
        rt_set_errno(EAGAIN);
        result = -1;
        goto __exit;
    }
    else
    {
        /* get receive buffer to receiver ring buffer */
        rt_mutex_take(sock->recv_lock, RT_WAITING_FOREVER);
        at_recvpkt_get(&(sock->recvpkt_list), (char *) &receive_buff, AT_SOCKET_INFO_LEN);
        rt_mutex_release(sock->recv_lock);
        at_do_event_changes(sock, AT_EVENT_RECV, RT_FALSE);
    }

    rt_sscanf(&receive_buff[0], "SOCKET:%d", &new_socket);
    new_sock = at_get_socket(new_socket);
    ip4_addr_set_any(&remote_addr);
    ipaddr_port_to_socketaddr(name, &remote_addr, &remote_port);
    LOG_D("Accept: [socket :%d, base_socket:%d]", new_socket, (int)new_sock->user_data);

__exit:
    if (result < 0)
    {
        at_do_event_changes(sock, AT_EVENT_ERROR, RT_TRUE);
    }

    return new_sock->socket;
}
#endif

int at_recvfrom(int socket, void *mem, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen)
{
    struct at_socket *sock = RT_NULL;
    int timeout, result = 0;
    size_t recv_len = 0;

    if (mem == RT_NULL || len == 0)
    {
        /* if the requested number of bytes to receive from a stream socket was 0. */
        rt_set_errno(EFAULT);
        return -1;
    }

    sock = at_get_socket(socket);
    if (sock == RT_NULL)
    {
        rt_set_errno(ENXIO);
        return -1;
    }

    /* if the socket type is UDP, need to connect socket first */
    if (sock->type == AT_SOCKET_UDP)
    {
        if (from == RT_NULL || fromlen == 0)
        {
            rt_set_errno(EFAULT);
            return -1;
        }

        if(sock->state == AT_SOCKET_CONNECT && rt_memcmp(&sock->last_udp_adr, from, sizeof(struct sockaddr)) != 0)
        {
            if (sock->ops->at_closesocket(sock) != 0)
            {
                free_socket(sock);
                rt_set_errno(EIO);
                goto __exit;
            }
            sock->state = AT_SOCKET_OPEN;
        }

        if (sock->state == AT_SOCKET_OPEN)
        {
            ip_addr_t remote_addr;
            uint16_t remote_port = 0;
            char ipstr[16] = { 0 };

            socketaddr_to_ipaddr_port(from, &remote_addr, &remote_port);
            ipaddr_to_ipstr(from, ipstr);

            if (sock->ops->at_connect(sock, ipstr, remote_port, sock->type, RT_TRUE) < 0)
            {
                at_do_event_changes(sock, AT_EVENT_ERROR, RT_TRUE);
                rt_set_errno(EIO);
                /* socket shutdown */
                goto __exit;
            }

            rt_memcpy(&sock->last_udp_adr, from, sizeof(struct sockaddr));
            sock->state = AT_SOCKET_CONNECT;
        }
    }

    while (1)
    {
        /* receive packet list last transmission of remaining data */
        rt_mutex_take(sock->recv_lock, RT_WAITING_FOREVER);
        recv_len = at_recvpkt_get(&(sock->recvpkt_list), (char *)mem, len);
        rt_mutex_release(sock->recv_lock);
        if (recv_len > 0)
        {
            if (rt_slist_isempty(&sock->recvpkt_list))
            {
                at_do_event_clean(sock, AT_EVENT_RECV);
            }
            result = recv_len;
            goto __exit;
        }

        if (sock->state == AT_SOCKET_CLOSED)
        {
            /* socket passively closed, receive function return 0 */
            result = 0;
            goto __exit;
        }

        if (flags & MSG_DONTWAIT)
        {
            rt_set_errno(EAGAIN);
            result = -1;
            goto __exit;
        }

        /* set AT socket receive timeout */
        if (sock->recv_timeout == 0)
        {
            timeout = RT_WAITING_FOREVER;
        }
        else
        {
            timeout = rt_tick_from_millisecond(sock->recv_timeout);
        }
        if (rt_sem_take(sock->recv_notice, timeout) != RT_EOK)
        {
            LOG_D("AT socket (%d) receive timeout (%d)!", socket, timeout);
            rt_set_errno(EAGAIN);
            result = -1;
            goto __exit;
        }
    }

__exit:
    if (result <= 0)
    {
        at_do_event_changes(sock, AT_EVENT_ERROR, RT_TRUE);
    }

    return result;
}

int at_recv(int s, void *mem, size_t len, int flags)
{
    return at_recvfrom(s, mem, len, flags, RT_NULL, RT_NULL);
}

int at_sendto(int socket, const void *data, size_t size, int flags, const struct sockaddr *to, socklen_t tolen)
{
    struct at_socket *sock = RT_NULL;
    int len = 0, result = 0;

    if (data == RT_NULL || size == 0)
    {
        LOG_E("AT sendto input data or size error!");
        rt_set_errno(EFAULT);
        return -1;
    }

    sock = at_get_socket(socket);
    if (sock == RT_NULL)
    {
        rt_set_errno(ENXIO);
        return -1;
    }

    switch (sock->type)
    {
    case AT_SOCKET_TCP:
        if (sock->state == AT_SOCKET_CLOSED)
        {
            /* socket passively closed, transmit function return 0 */
            result = 0;
            goto __exit;
        }
        else if (sock->state != AT_SOCKET_CONNECT)
        {
            LOG_E("send data error, current socket (%d) state (%d) is error.", socket, sock->state);
            rt_set_errno(ENETUNREACH);
            result = -1;
            goto __exit;
        }

        if ((len = sock->ops->at_send(sock, (const char *) data, size, sock->type)) < 0)
        {
            rt_set_errno(EIO);
            result = -1;
            goto __exit;
        }
        break;

    case AT_SOCKET_UDP:
        if (to == RT_NULL || tolen == 0)
        {
            rt_set_errno(EFAULT);
            result = -1;
            goto __exit;
        }

        /* Inconsistent with the last UDP sending address, reconnect to a new address */
        if(sock->state == AT_SOCKET_CONNECT && rt_memcmp(&sock->last_udp_adr, to, sizeof(struct sockaddr)) != 0)
        {
            if (sock->ops->at_closesocket(sock) != 0)
            {
                free_socket(sock);
                rt_set_errno(EIO);
                goto __exit;
            }
            sock->state = AT_SOCKET_OPEN;
        }

        if (sock->state == AT_SOCKET_OPEN)
        {
            ip_addr_t remote_addr;
            uint16_t remote_port = 0;
            char ipstr[16] = { 0 };

            socketaddr_to_ipaddr_port(to, &remote_addr, &remote_port);
            ipaddr_to_ipstr(to, ipstr);

            if (sock->ops->at_connect(sock, ipstr, remote_port, sock->type, RT_TRUE) < 0)
            {
                rt_set_errno(EIO);
                result = -1;
                goto __exit;
            }

            rt_memcpy(&sock->last_udp_adr, to, sizeof(struct sockaddr));
            sock->state = AT_SOCKET_CONNECT;
        }

        if ((len = sock->ops->at_send(sock, (char *) data, size, sock->type)) < 0)
        {
            rt_set_errno(EIO);
            result = -1;
            goto __exit;
        }
        break;

    default:
        LOG_E("Socket (%d) type %d is not support.", socket, sock->type);
        rt_set_errno(EPERM);
        result = -1;
        goto __exit;
    }

__exit:
    if (result < 0)
    {
        at_do_event_changes(sock, AT_EVENT_ERROR, RT_TRUE);
    }
    else
    {
        result = len;
    }

    return result;
}

int at_send(int socket, const void *data, size_t size, int flags)
{
    return at_sendto(socket, data, size, flags, RT_NULL, 0);
}

int at_getsockopt(int socket, int level, int optname, void *optval, socklen_t *optlen)
{
    struct at_socket *sock;
    int32_t timeout;

    if (optval == RT_NULL || optlen == RT_NULL)
    {
        LOG_E("AT getsocketopt input option value or option length error!");
        rt_set_errno(EFAULT);
        return -1;
    }

    sock = at_get_socket(socket);
    if (sock == RT_NULL)
    {
        rt_set_errno(ENXIO);
        return -1;
    }

    switch (level)
    {
    case SOL_SOCKET:
        switch (optname)
        {
        case SO_RCVTIMEO:
            timeout = sock->recv_timeout;
            ((struct timeval *)(optval))->tv_sec = (timeout) / 1000U;
            ((struct timeval *)(optval))->tv_usec = (timeout % 1000U) * 1000U;
            break;

        case SO_SNDTIMEO:
            timeout = sock->send_timeout;
            ((struct timeval *) optval)->tv_sec = timeout / 1000U;
            ((struct timeval *) optval)->tv_usec = (timeout % 1000U) * 1000U;
            break;

        default:
            LOG_E("AT socket (%d) not support option name : %d.", socket, optname);
            rt_set_errno(EPERM);
            return -1;
        }
        break;

    default:
        LOG_E("AT socket (%d) not support option level : %d.", socket, level);
        rt_set_errno(EPERM);
        return -1;
    }

    return 0;
}

int at_setsockopt(int socket, int level, int optname, const void *optval, socklen_t optlen)
{
    struct at_socket *sock;

    if (optval == RT_NULL)
    {
        LOG_E("AT setsockopt input option value error!");
        rt_set_errno(EFAULT);
        return -1;
    }

    sock = at_get_socket(socket);
    if (sock == RT_NULL)
    {
        rt_set_errno(ENXIO);
        return -1;
    }

    switch (level)
    {
    case SOL_SOCKET:
        switch (optname)
        {
        case SO_RCVTIMEO:
            sock->recv_timeout = ((const struct timeval *) optval)->tv_sec * 1000
                    + ((const struct timeval *) optval)->tv_usec / 1000;
            break;

        case SO_SNDTIMEO:
            sock->send_timeout = ((const struct timeval *) optval)->tv_sec * 1000
                    + ((const struct timeval *) optval)->tv_usec / 1000;
            break;

        default:
            LOG_E("AT socket (%d) not support option name : %d.", socket, optname);
            rt_set_errno(EPERM);
            return -1;
        }
        break;
    case IPPROTO_TCP:
        switch (optname)
        {
        case TCP_NODELAY:
            break;
        }
        break;
    default:
        LOG_E("AT socket (%d) not support option level : %d.", socket, level);
        rt_set_errno(EPERM);
        return -1;
    }

    return 0;
}

static uint32_t ipstr_atol(const char* nptr)
{
    uint32_t total = 0;
    char sign = '+';
    /* jump space */
    while (isspace(*nptr))
    {
        ++nptr;
    }
    if (*nptr == '-' || *nptr == '+')
    {
        sign = *nptr++;
    }
    while (isdigit(*nptr))
    {
        total = 10 * total + ((*nptr++) - '0');
    }
    return (sign == '-') ? -total : total;
}

/* IP address to unsigned int type */
static uint32_t ipstr_to_u32(char *ipstr)
{
    char ipBytes[4] = { 0 };
    uint32_t i;

    for (i = 0; i < 4; i++, ipstr++)
    {
        ipBytes[i] = (char) ipstr_atol(ipstr);
        if ((ipstr = strchr(ipstr, '.')) == RT_NULL)
        {
            break;
        }
    }
    return *(uint32_t *) ipBytes;
}

/**
 * @brief resolves a domain name via AT device and returns its IP address.
 * @note function uses static global mutex internally, which will cause multiple AT devices to block and wait while performing DNS resolution.
 * @param name Pointer to a string containing the domain name.
 * @param addr Pointer to a structure where the IP address information is stored.
 * @return int Returns 0 on success or -1/-2 on failure
 *          -1: domain failed
 *          -2: HOST_NOT_FOUND
 */
static int _gethostbyname_by_device(const char *name, ip_addr_t *addr)
{
    static rt_mutex_t at_dlock = RT_NULL;

    struct at_device *device = RT_NULL;
    char ipstr[16] = { 0 };
    size_t idx = 0;

    device = at_device_get_first_initialized();
    if (device == RT_NULL)
    {
        return -1;
    }

    if (!netdev_is_link_up(device->netdev))
    {
        return -1;
    }

    for (idx = 0; idx < strlen(name) && !isalpha(name[idx]); idx++);

    if (idx < strlen(name))
    {
        if (at_dlock == RT_NULL)
        {
            at_dlock = rt_mutex_create("at_dlock", RT_IPC_FLAG_PRIO);
            if (at_dlock == RT_NULL)
            {
                return -1;
            }
        }

        rt_mutex_take(at_dlock, RT_WAITING_FOREVER);
        if (device->class->socket_ops->at_domain_resolve(name, ipstr) < 0)
        {
            rt_mutex_release(at_dlock);
            return -2;
        }
        rt_mutex_release(at_dlock);
    }
    else
    {
        strncpy(ipstr, name, strlen(name));
    }

#if NETDEV_IPV4 && NETDEV_IPV6
    addr.type = IPADDR_TYPE_V4;
    if (inet_aton(ipstr, addr) == 0)
    {
        return -1;
    }
#elif NETDEV_IPV4
    if (inet_aton(ipstr, addr) == 0)
    {
        return -1;
    }
#elif NETDEV_IPV6
#error "not support IPV6."
#endif /* NETDEV_IPV4 && NETDEV_IPV6 */

    return 0;
}

struct hostent *at_gethostbyname(const char *name)
{
    ip_addr_t addr = {0};
    /* buffer variables for at_gethostbyname() */
    static struct hostent s_hostent;
    static char *s_aliases;
    static ip_addr_t s_hostent_addr;
    static ip_addr_t *s_phostent_addr[2];
    static char s_hostname[DNS_MAX_NAME_LENGTH + 1];

    if (name == RT_NULL)
    {
        LOG_E("AT gethostbyname input name error!");
        return RT_NULL;
    }

    if (strlen(name) > DNS_MAX_NAME_LENGTH)
    {
        return RT_NULL;
    }

    if (_gethostbyname_by_device(name, &addr) != 0)
    {
        return RT_NULL;
    }

    /* fill hostent structure */
    s_hostent_addr = addr;
    s_phostent_addr[0] = &s_hostent_addr;
    s_phostent_addr[1] = RT_NULL;
    strncpy(s_hostname, name, strlen(name));
    s_hostname[strlen(name)] = 0;
    s_aliases = RT_NULL;

    s_hostent.h_name = s_hostname;
    s_hostent.h_aliases = &s_aliases;
    s_hostent.h_addrtype = AF_AT;
    s_hostent.h_length = sizeof(ip_addr_t);
    s_hostent.h_addr_list = (char**) &s_phostent_addr;

    return &s_hostent;
}

int at_gethostbyname_r(const char *name, struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop)
{
    struct gethostbyname_r_helper
    {
        ip_addr_t *addr_list[2];
        ip_addr_t addr;
        char *aliases;
    };

    char *hostname = RT_NULL;
    int lh_errno = 0;
    int domain_err = 0;
    size_t namelen = 0;
    struct gethostbyname_r_helper *h = RT_NULL;

    if (h_errnop == RT_NULL)
    {
        h_errnop = &lh_errno;
    }

    if ((name == RT_NULL) || (ret == RT_NULL) || (buf == RT_NULL))
    {
        *h_errnop = EINVAL;
        return -1;
    }

    if (result == RT_NULL)
    {
        *h_errnop = EINVAL;
        return -1;
    }

    *result = RT_NULL;

    namelen = strlen(name);
    if (buflen < (sizeof(struct gethostbyname_r_helper) + (namelen + 1)))
    {
        *h_errnop = ERANGE;
        return -1;
    }

    h = (struct gethostbyname_r_helper *)buf;
    hostname = ((char *)h) + sizeof(struct gethostbyname_r_helper);

    domain_err = _gethostbyname_by_device(name, &h->addr);
    if (domain_err != 0)
    {
        if (domain_err == -2)
        {
            *h_errnop = HOST_NOT_FOUND;
        }

        *h_errnop = NO_DATA;
        return -1;
    }

    rt_memcpy(hostname, name, namelen);
    hostname[namelen] = 0;

    h->addr_list[0] = &h->addr;
    h->addr_list[1] = NULL;
    h->aliases = NULL;

    ret->h_name = hostname;
    ret->h_aliases = &h->aliases;
    ret->h_addrtype = AF_INET;
    ret->h_length = sizeof(ip_addr_t);
    ret->h_addr_list = (char **)&h->addr_list;

    *result = ret;
    return 0;
}

int at_getaddrinfo(const char *nodename, const char *servname,
                    const struct addrinfo *hints, struct addrinfo **res)
{
    int port_nr = 0;
    ip_addr_t addr = {0};
    struct addrinfo *ai;
    struct sockaddr_storage *sa;
    size_t total_size = 0;
    size_t namelen = 0;
    int ai_family = 0;

    if (res == RT_NULL)
    {
        return EAI_FAIL;
    }
    *res = RT_NULL;

    if ((nodename == RT_NULL) && (servname == RT_NULL))
    {
        return EAI_NONAME;
    }

    if (hints != RT_NULL)
    {
        ai_family = hints->ai_family;
        if (hints->ai_family != AF_AT && hints->ai_family != AF_INET && hints->ai_family != AF_UNSPEC)
        {
            return EAI_FAMILY;
        }
    }
    else
    {
        ai_family = AF_UNSPEC;
    }

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
        /* service location specified, try to resolve */
        if ((hints != RT_NULL) && (hints->ai_flags & AI_NUMERICHOST))
        {
            if (ai_family == AF_AT || ai_family == AF_INET)
            {
                return EAI_NONAME;
            }

            /* no DNS lookup, just parse for an address string */
            if (!inet_aton(nodename, &addr))
            {
                return EAI_NONAME;
            }

        }
        else
        {
            int domain_err = 0;
            domain_err = _gethostbyname_by_device(nodename, &addr);
            if (domain_err != 0)
            {
                if (domain_err == -2)
                {
                    return HOST_NOT_FOUND;
                }

                return NO_DATA;
            }
        }
    }
    else
    {
        /* service location specified, use loopback address */
        inet_aton("127.0.0.1", &addr);
    }

    total_size = sizeof(struct addrinfo) + sizeof(struct sockaddr_storage);
    if (nodename != RT_NULL)
    {
        namelen = strlen(nodename);
        if (namelen == 0 || namelen > DNS_MAX_NAME_LENGTH)
        {
            /* invalid name length */
            return EAI_FAIL;
        }

        total_size += namelen + 1;
    }
    /* If this fails, please report to lwip-devel! :-) */
    if (total_size > sizeof(struct addrinfo) + sizeof(struct sockaddr_storage) + DNS_MAX_NAME_LENGTH + 1)
    {
        return EAI_FAIL;
    }

    ai = (struct addrinfo *) rt_malloc(total_size);
    if (ai == RT_NULL)
    {
        return EAI_MEMORY;
    }
    rt_memset(ai, RT_NULL, total_size);
    /* cast through void* to get rid of alignment warnings */
    sa = (struct sockaddr_storage *) (void *) ((uint8_t *) ai + sizeof(struct addrinfo));
    struct sockaddr_in *sa4 = (struct sockaddr_in *) sa;
    /* set up sockaddr */
#if NETDEV_IPV4 && NETDEV_IPV6
    sa4->sin_addr.s_addr = addr.u_addr.ip4.addr;
    sa4->type = IPADDR_TYPE_V4;
#elif NETDEV_IPV4
    sa4->sin_addr.s_addr = addr.addr;
#elif NETDEV_IPV6
#error "not support IPV6."
#endif /* NETDEV_IPV4 && NETDEV_IPV6 */
    sa4->sin_family = AF_INET;
    sa4->sin_len = sizeof(struct sockaddr_in);
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
        ai->ai_canonname = ((char *) ai + sizeof(struct addrinfo) + sizeof(struct sockaddr_storage));
        rt_memcpy(ai->ai_canonname, nodename, namelen);
        ai->ai_canonname[namelen] = 0;
    }
    ai->ai_addrlen = sizeof(struct sockaddr_storage);
    ai->ai_addr = (struct sockaddr *) sa;

    *res = ai;

    return 0;
}

void at_freeaddrinfo(struct addrinfo *ai)
{
    struct addrinfo *next;

    while (ai != NULL)
    {
        next = ai->ai_next;
        rt_free(ai);
        ai = next;
    }
}

#endif /* AT_USING_SOCKET */
