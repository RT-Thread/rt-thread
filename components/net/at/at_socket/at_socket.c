/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-06     chenyong     first version
 */

#include <at.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

#include <at_socket.h>
#include <at_device.h>

#ifdef SAL_USING_POSIX
#include <dfs_poll.h>
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


/* the global of sockets list */
static rt_slist_t _socket_list = RT_SLIST_OBJECT_INIT(_socket_list);

struct at_socket *at_get_socket(int socket)
{
    rt_base_t level;
    size_t list_num = 0;
    rt_slist_t *node = RT_NULL;
    struct at_socket *at_sock = RT_NULL;

    level = rt_hw_interrupt_disable();

    rt_slist_for_each(node, &_socket_list)
    {
        if (socket == (list_num++))
        {
            at_sock = rt_slist_entry(node, struct at_socket, list);
            if (at_sock && at_sock->magic == AT_SOCKET_MAGIC)
            {
                rt_hw_interrupt_enable(level);
                return at_sock;
            }
        }
    } 
    
    rt_hw_interrupt_enable(level);

    return RT_NULL;
}

/* get a block to the AT socket receive list*/
static size_t at_recvpkt_put(rt_slist_t *rlist, const char *ptr, size_t length)
{
    at_recv_pkt_t pkt = RT_NULL;

    pkt = (at_recv_pkt_t) rt_calloc(1, sizeof(struct at_recv_pkt));
    if (pkt == RT_NULL)
    {
        LOG_E("No memory for receive packet table!");
        return 0;
    }

    pkt->bfsz_totle = length;
    pkt->bfsz_index = 0;
    pkt->buff = (char *) ptr;

    rt_slist_append(rlist, &pkt->list);

    return length;
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

    for(node = rt_slist_first(rlist); node; node = rt_slist_next(node))
    {
        pkt = rt_slist_entry(node, struct at_recv_pkt, list);
        if (pkt->buff)
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
    if (pkt->buff)
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
    at_recv_pkt_t pkt = RT_NULL;
    size_t content_pos = 0, page_pos = 0;

    if (rt_slist_isempty(rlist))
    {
        return 0;
    }

    for (node = rt_slist_first(rlist); node; node = rt_slist_next(node))
    {
        pkt = rt_slist_entry(node, struct at_recv_pkt, list);

        page_pos = pkt->bfsz_totle - pkt->bfsz_index;

        if (page_pos >= len - content_pos)
        {
            memcpy((char *) mem + content_pos, pkt->buff + pkt->bfsz_index, len - content_pos);
            pkt->bfsz_index += len - content_pos;
            if (pkt->bfsz_index == pkt->bfsz_totle)
            {
                at_recvpkt_node_delete(rlist, node);
            }
            content_pos = len;
            break;
        }
        else
        {
            memcpy((char *) mem + content_pos, pkt->buff + pkt->bfsz_index, page_pos);
            content_pos += page_pos;
            pkt->bfsz_index += page_pos;
            at_recvpkt_node_delete(rlist, node);
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

static struct at_socket *alloc_socket_by_device(struct at_device *device)
{
    static rt_mutex_t at_slock = RT_NULL;
    struct at_socket *sock = RT_NULL;
    char name[RT_NAME_MAX] = {0};
    int idx = 0;

    if (at_slock == RT_NULL)
    {
        /* create AT socket lock */
        at_slock = rt_mutex_create("at_slock", RT_IPC_FLAG_FIFO);
        if (at_slock == RT_NULL)
        {
            LOG_E("No memory for socket allocation lock!");
            return RT_NULL;
        }
    }

    rt_mutex_take(at_slock, RT_WAITING_FOREVER);

    /* find an empty at socket entry */
    for (idx = 0; idx < device->class->socket_num && device->sockets[idx].magic; idx++);

    /* can't find an empty protocol family entry */
    if (idx == device->class->socket_num)
    {
        goto __err;
    }

    /* add device socket to global socket list */
    {
        rt_base_t level;

        level = rt_hw_interrupt_disable();

        rt_slist_init(&(device->sockets[idx].list));
        rt_slist_append(&_socket_list, &(device->sockets[idx].list));

        rt_hw_interrupt_enable(level);
    }

    sock = &(device->sockets[idx]);
    /* the socket descriptor is the number of sockte lists */
    sock->socket = rt_slist_len(&_socket_list) - 1;
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
    rt_slist_init(&sock->recvpkt_list);
#ifdef SAL_USING_POSIX
    rt_wqueue_init(&sock->wait_head);
#endif

    rt_snprintf(name, RT_NAME_MAX, "%s%d", "at_skt", idx);
    /* create AT socket receive mailbox */
    if ((sock->recv_notice = rt_sem_create(name, 0, RT_IPC_FLAG_FIFO)) == RT_NULL)
    {
        LOG_E("No memory socket receive notic semaphore create.");
        goto __err;
    }

    rt_snprintf(name, RT_NAME_MAX, "%s%d", "at_skt", idx);
    /* create AT socket receive ring buffer lock */
    if((sock->recv_lock = rt_mutex_create(name, RT_IPC_FLAG_FIFO)) == RT_NULL)
    {
        LOG_E("No memory for socket receive mutex create.");
        rt_sem_delete(sock->recv_notice);
        goto __err;
    }

    rt_mutex_release(at_slock);
    return sock;

__err:
    rt_mutex_release(at_slock);
    return RT_NULL;
}

static struct at_socket *alloc_socket(void)
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

    return alloc_socket_by_device(device);
}

int at_socket(int domain, int type, int protocol)
{
    struct at_socket *sock = RT_NULL;
    enum at_socket_type socket_type;

    /* check socket family protocol */
    RT_ASSERT(domain == AF_AT || domain == AF_INET);

    //TODO check protocol

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
        return -1;
    }

    /* allocate and initialize a new AT socket */
    sock = alloc_socket();
    if (sock == RT_NULL)
    {
        return -1;
    }
    sock->type = socket_type;
    sock->state = AT_SOCKET_OPEN;

    return sock->socket;
}

static int free_socket(struct at_socket *sock)
{
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
        int list_num = 0;
        rt_slist_t *node = RT_NULL;
        struct at_socket *at_sock = RT_NULL;

        level = rt_hw_interrupt_disable();

        rt_slist_for_each(node, &_socket_list)
        {
            if (sock->socket == (list_num++))
            {
                at_sock = rt_slist_entry(node, struct at_socket, list);
                if (at_sock)
                {
                    rt_slist_remove(&_socket_list, &at_sock->list);
                    break;
                }
            }
        }

        rt_hw_interrupt_enable(level);
    }

    rt_memset(sock, 0x00, sizeof(struct at_socket));

    return 0;
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

int at_bind(int socket, const struct sockaddr *name, socklen_t namelen)
{
    struct at_socket *sock = RT_NULL;
    struct at_device *device = RT_NULL;
    ip_addr_t input_ipaddr, local_ipaddr;
    uint16_t port = 0;

    sock = at_get_socket(socket);
    if (sock == RT_NULL)
    {
        return -1;
    }

    /* get current device ip address */
    device = (struct at_device *) sock->device;
    ip_addr_copy(local_ipaddr, device->netdev->ip_addr);

    /* prase ip address and port from sockaddr structure */
    socketaddr_to_ipaddr_port(name, &input_ipaddr, &port);

    /* input ip address is different from device ip address */
    if (ip_addr_cmp(&input_ipaddr, &local_ipaddr) == 0)
    {   
        struct at_socket *new_sock = RT_NULL;
        struct at_device *new_device = RT_NULL;
        enum at_socket_type type = sock->type;

        /* close old socket */
        if (at_closesocket(socket) < 0)
        {
            return -1;
        }
        
        extern struct at_device *at_device_get_by_ipaddr(ip_addr_t *ip_addr);
        new_device = at_device_get_by_ipaddr(&input_ipaddr);
        if (new_device == RT_NULL)
        {
            return -1;
        }

        /* allocate new socket */
        new_sock = alloc_socket_by_device(new_device);
        if (new_sock == RT_NULL)
        {
            return -1;
        }
        new_sock->type = type;
        new_sock->state = AT_SOCKET_OPEN;
    }

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

static void at_recv_notice_cb(struct at_socket *sock, at_socket_evt_t event, const char *buff, size_t bfsz)
{
    RT_ASSERT(buff);
    RT_ASSERT(event == AT_SOCKET_EVT_RECV);
    
    /* check the socket object status */
    if (sock->magic != AT_SOCKET_MAGIC)
    {
        return;
    }

    /* put receive buffer to receiver packet list */
    rt_mutex_take(sock->recv_lock, RT_WAITING_FOREVER);
    at_recvpkt_put(&(sock->recvpkt_list), buff, bfsz);
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

int at_connect(int socket, const struct sockaddr *name, socklen_t namelen)
{
    struct at_socket *sock = RT_NULL;
    ip_addr_t remote_addr;
    uint16_t remote_port = 0;
    char ipstr[16] = { 0 };
    int result = 0;

    sock = at_get_socket(socket);
    if (sock == RT_NULL)
    {
        result = -1;
        goto __exit;
    }

    if (sock->state != AT_SOCKET_OPEN)
    {
        LOG_E("Socket(%d) connect state is %d.", sock->socket, sock->state);
        result = -1;
        goto __exit;
    }

    /* get IP address and port by socketaddr structure */
    socketaddr_to_ipaddr_port(name, &remote_addr, &remote_port);
    ipaddr_to_ipstr(name, ipstr);

    if (sock->ops->at_connect(sock, ipstr, remote_port, sock->type, RT_TRUE) < 0)
    {
        result = -1;
        goto __exit;
    }

    sock->state = AT_SOCKET_CONNECT;

    /* set AT socket receive data callback function */
    sock->ops->at_set_event_cb(AT_SOCKET_EVT_RECV, at_recv_notice_cb);
    sock->ops->at_set_event_cb(AT_SOCKET_EVT_CLOSED, at_closed_notice_cb);

__exit:

    if (result < 0)
    {
        if (sock != RT_NULL)
        {
            at_do_event_changes(sock, AT_EVENT_ERROR, RT_TRUE);
        }
    }

    if (sock)
    {
        at_do_event_changes(sock, AT_EVENT_SEND, RT_TRUE);
    }
    
    return result;
}

int at_recvfrom(int socket, void *mem, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen)
{
    struct at_socket *sock = RT_NULL;
    int timeout, result = 0;
    size_t recv_len = 0;

    if (mem == RT_NULL || len == 0)
    {
        LOG_E("AT recvfrom input data or length error!");
        return -1;
    }

    sock = at_get_socket(socket);
    if (sock == RT_NULL)
    {
        result = -1;
        goto __exit;
    }

    /* if the socket type is UDP, nead to connect socket first */
    if (from && sock->type == AT_SOCKET_UDP && sock->state == AT_SOCKET_OPEN)
    {
        ip_addr_t remote_addr;
        uint16_t remote_port = 0;
        char ipstr[16] = { 0 };

        socketaddr_to_ipaddr_port(from, &remote_addr, &remote_port);
        ipaddr_to_ipstr(from, ipstr);

        if (sock->ops->at_connect(sock, ipstr, remote_port, sock->type, RT_TRUE) < 0)
        {
            result = -1;
            goto __exit;
        }
        sock->state = AT_SOCKET_CONNECT;
        /* set AT socket receive data callback function */
        sock->ops->at_set_event_cb(AT_SOCKET_EVT_RECV, at_recv_notice_cb);
        sock->ops->at_set_event_cb(AT_SOCKET_EVT_CLOSED, at_closed_notice_cb);
    }

    /* receive packet list last transmission of remaining data */
    rt_mutex_take(sock->recv_lock, RT_WAITING_FOREVER);
    if((recv_len = at_recvpkt_get(&(sock->recvpkt_list), (char *)mem, len)) > 0)
    {
        rt_mutex_release(sock->recv_lock);
        goto __exit;
    }
    rt_mutex_release(sock->recv_lock);
        
    /* socket passively closed, receive function return 0 */
    if (sock->state == AT_SOCKET_CLOSED)
    {
        result = 0;
        goto __exit;
    }
    else if (sock->state != AT_SOCKET_CONNECT && sock->state != AT_SOCKET_OPEN)
    {
        LOG_E("received data error, current socket (%d) state (%d) is error.", socket, sock->state);
        result = -1;
        goto __exit;
    }

    /* non-blocking sockets receive data */
    if (flags & MSG_DONTWAIT)
    {
        goto __exit;
    }

    /* set AT socket receive timeout */
    if ((timeout = sock->recv_timeout) == 0)
    {
        timeout = RT_WAITING_FOREVER;
    }
    else
    {
        timeout = rt_tick_from_millisecond(timeout);
    }

    while (1)
    {
        /* wait the receive semaphore */
        if (rt_sem_take(sock->recv_notice, timeout) < 0)
        {
            LOG_E("AT socket (%d) receive timeout (%d)!", socket, timeout);
            errno = EAGAIN;
            result = -1;
            goto __exit;
        }
        else
        {
            if (sock->state == AT_SOCKET_CONNECT)
            {
                /* get receive buffer to receiver ring buffer */
                rt_mutex_take(sock->recv_lock, RT_WAITING_FOREVER);
                recv_len = at_recvpkt_get(&(sock->recvpkt_list), (char *) mem, len);
                rt_mutex_release(sock->recv_lock);
                if (recv_len > 0)
                {
                    break;
                }
            }
            else
            {
                LOG_D("received data exit, current socket (%d) is closed by remote.", socket);
                result = 0;
                goto __exit;
            }
        }
    }

__exit:

    if (sock != RT_NULL)
    {
        if (recv_len > 0)
        {
            result = recv_len;
            at_do_event_changes(sock, AT_EVENT_RECV, RT_FALSE);
            errno = 0;
            if (!rt_slist_isempty(&sock->recvpkt_list))
            {
                at_do_event_changes(sock, AT_EVENT_RECV, RT_TRUE);
            }
            else
            {
                at_do_event_clean(sock, AT_EVENT_RECV);
            }
        }
        else
        {
            at_do_event_changes(sock, AT_EVENT_ERROR, RT_TRUE);
        }
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
    int len, result = 0;

    if (data == RT_NULL || size == 0)
    {
        LOG_E("AT sendto input data or size error!");
        result = -1;
        goto __exit;
    }

    sock = at_get_socket(socket);
    if (sock == RT_NULL)
    {
        result = -1;
        goto __exit;
    }

    switch (sock->type)
    {
    case AT_SOCKET_TCP:
        if (sock->state == AT_SOCKET_CLOSED)
        {
            result = 0;
            goto __exit;
        }
        else if (sock->state != AT_SOCKET_CONNECT && sock->state != AT_SOCKET_OPEN)
        {
            LOG_E("send data error, current socket (%d) state (%d) is error.", socket, sock->state);
            result = -1;
            goto __exit;
        }

        if ((len = sock->ops->at_send(sock, (const char *) data, size, sock->type)) < 0)
        {
            result = -1;
            goto __exit;
        }
        break;

    case AT_SOCKET_UDP:
        if (to && sock->state == AT_SOCKET_OPEN)
        {
            ip_addr_t remote_addr;
            uint16_t remote_port = 0;
            char ipstr[16] = { 0 };

            socketaddr_to_ipaddr_port(to, &remote_addr, &remote_port);
            ipaddr_to_ipstr(to, ipstr);

            if (sock->ops->at_connect(sock, ipstr, remote_port, sock->type, RT_TRUE) < 0)
            {
                result = -1;
                goto __exit;
            }
            sock->state = AT_SOCKET_CONNECT;
            /* set AT socket receive data callback function */
            sock->ops->at_set_event_cb(AT_SOCKET_EVT_RECV, at_recv_notice_cb);
            sock->ops->at_set_event_cb(AT_SOCKET_EVT_CLOSED, at_closed_notice_cb);
        }

        if ((len = sock->ops->at_send(sock, (char *) data, size, sock->type)) < 0)
        {
            result = -1;
            goto __exit;
        }
        break;

    default:
        LOG_E("Socket (%d) type %d is not support.", socket, sock->type);
        result = -1;
        goto __exit;
    }

__exit:

    if (result < 0)
    {
        if (sock != RT_NULL)
        {
            at_do_event_changes(sock, AT_EVENT_ERROR, RT_TRUE);   
        }
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
        return -1;
    }

    sock = at_get_socket(socket);
    if (sock == RT_NULL)
    {
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
            return -1;
        }
        break;

    default:
        LOG_E("AT socket (%d) not support option level : %d.", socket, level);
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
        return -1;
    }

    sock = at_get_socket(socket);
    if (sock == RT_NULL)
    {
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

struct hostent *at_gethostbyname(const char *name)
{
    struct at_device *device = RT_NULL;
    ip_addr_t addr;
    char ipstr[16] = { 0 };
    /* buffer variables for at_gethostbyname() */
    static struct hostent s_hostent;
    static char *s_aliases;
    static ip_addr_t s_hostent_addr;
    static ip_addr_t *s_phostent_addr[2];
    static char s_hostname[DNS_MAX_NAME_LENGTH + 1];
    size_t idx = 0;

    if (name == RT_NULL)
    {
        LOG_E("AT gethostbyname input name error!");
        return RT_NULL;
    }

    device = at_device_get_first_initialized();
    if (device == RT_NULL)
    {
        return RT_NULL;
    }

    for (idx = 0; idx < strlen(name) && !isalpha(name[idx]); idx++);

    if (idx < strlen(name))
    {
        if (device->class->socket_ops->at_domain_resolve(name, ipstr) < 0)
        {
            return RT_NULL;
        }
    }
    else
    {
        strncpy(ipstr, name, strlen(name));
    }

#if NETDEV_IPV4 && NETDEV_IPV6
    addr.u_addr.ip4.addr = ipstr_to_u32(ipstr);
	addr.type = IPADDR_TYPE_V4;
#elif NETDEV_IPV4
    addr.addr = ipstr_to_u32(ipstr);
#elif NETDEV_IPV6
#error "not support IPV6."
#endif /* NETDEV_IPV4 && NETDEV_IPV6 */
 
    /* fill hostent structure */
    s_hostent_addr = addr;
    s_phostent_addr[0] = &s_hostent_addr;
    s_phostent_addr[1] = RT_NULL;
    strncpy(s_hostname, name, DNS_MAX_NAME_LENGTH);
    s_hostname[DNS_MAX_NAME_LENGTH] = 0;
    s_hostent.h_name = s_hostname;
    s_aliases = RT_NULL;
    s_hostent.h_aliases = &s_aliases;
    s_hostent.h_addrtype = AF_AT;
    s_hostent.h_length = sizeof(ip_addr_t);
    s_hostent.h_addr_list = (char**) &s_phostent_addr;

    return &s_hostent;
}

int at_getaddrinfo(const char *nodename, const char *servname,
                    const struct addrinfo *hints, struct addrinfo **res)
{
    int port_nr = 0;
    ip_addr_t addr;
    struct addrinfo *ai;
    struct sockaddr_storage *sa;
    size_t total_size = 0;
    size_t namelen = 0;
    int ai_family = 0;
    struct at_device *device = RT_NULL;

    if (res == RT_NULL)
    {
        return EAI_FAIL;
    }
    *res = RT_NULL;

    device = at_device_get_first_initialized();
    if (device == RT_NULL)
    {
        return EAI_FAIL;
    }

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
            /* no DNS lookup, just parse for an address string */
            if (!inet_aton(nodename, &addr))
            {
                return EAI_NONAME;
            }

            if (ai_family == AF_AT || ai_family == AF_INET)
            {
                return EAI_NONAME;
            }
        }
        else
        {
            char ip_str[16] = { 0 };
            size_t idx = 0;

            for (idx = 0; idx < strlen(nodename) && !isalpha(nodename[idx]); idx++);

            if(idx < strlen(nodename))
            {
                if (device->class->socket_ops->at_domain_resolve((char *) nodename, ip_str) != 0)
                {
                    return EAI_FAIL;
                }
            }
            else
            {
                strncpy(ip_str, nodename, strlen(nodename));
            }
            
        #if NETDEV_IPV4 && NETDEV_IPV6 
            addr.type = IPADDR_TYPE_V4;
            if ((addr.u_addr.ip4.addr = ipstr_to_u32(ip_str)) == 0)
            {
                return EAI_FAIL;
            }
        #elif NETDEV_IPV4
            addr.addr = ipstr_to_u32(ip_str);
        #elif NETDEV_IPV6
        #error "not support IPV6."
        #endif /* NETDEV_IPV4 && NETDEV_IPV6 */  
        }
    }
    else
    {
        /* to do service location specified, use loopback address */
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
    ai = (struct addrinfo *) rt_malloc(total_size);
    if (ai == RT_NULL)
    {
        return EAI_MEMORY;
    }
    memset(ai, 0, total_size);
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
        memcpy(ai->ai_canonname, nodename, namelen);
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
