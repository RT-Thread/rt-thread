/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-06     chenYong     first version
 * 2022-06-02     xianxistu    add implement about "AT server"
 */

#ifndef __AT_SOCKET_H__
#define __AT_SOCKET_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>

#include <netdb.h>
#include <sys/socket.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef AT_SOCKET_RECV_BFSZ
#define AT_SOCKET_RECV_BFSZ            512
#endif

#define AT_DEFAULT_RECVMBOX_SIZE       10
#define AT_DEFAULT_ACCEPTMBOX_SIZE     10

/* sal socket magic word */
#define AT_SOCKET_MAGIC                0xA100

#ifdef AT_USING_SOCKET_SERVER
#define AT_SOCKET_INFO_LEN (sizeof("SOCKET:") + 4)
#endif

/* Current state of the AT socket. */
enum at_socket_state
{
    AT_SOCKET_NONE,
    AT_SOCKET_OPEN,
    AT_SOCKET_LISTEN,
    AT_SOCKET_CONNECT,
    AT_SOCKET_CLOSED
};

enum at_socket_type
{
    AT_SOCKET_INVALID   = 0,
    AT_SOCKET_TCP       = 0x10,      /* TCP IPv4 */
    AT_SOCKET_UDP       = 0x20,      /* UDP IPv4 */
};

typedef enum
{
    AT_SOCKET_EVT_RECV,
    AT_SOCKET_EVT_CLOSED,
#ifdef AT_USING_SOCKET_SERVER
    AT_SOCKET_EVT_CONNECTED,
#endif
} at_socket_evt_t;

struct at_socket;
struct at_device;

typedef void (*at_evt_cb_t)(struct at_socket *socket, at_socket_evt_t event, const char *buff, size_t bfsz);

/* A callback prototype to inform about events for AT socket */
typedef void (* at_socket_callback)(struct at_socket *conn, int event, uint16_t len);

/* AT socket operations function */
struct at_socket_ops
{
    int (*at_connect)(struct at_socket *socket, char *ip, int32_t port, enum at_socket_type type, rt_bool_t is_client);
    int (*at_closesocket)(struct at_socket *socket);
    int (*at_send)(struct at_socket *socket, const char *buff, size_t bfsz, enum at_socket_type type);
    int (*at_domain_resolve)(const char *name, char ip[16]);
    void (*at_set_event_cb)(at_socket_evt_t event, at_evt_cb_t cb);
    int (*at_socket)(struct at_device *device, enum at_socket_type type);
#ifdef AT_USING_SOCKET_SERVER
    int (*at_listen)(struct at_socket *socket, int backlog);
#endif
};

/* AT receive package list structure */
struct at_recv_pkt
{
    rt_slist_t list;
    size_t bfsz_totle;
    size_t bfsz_index;
    char *buff;
};
typedef struct at_recv_pkt *at_recv_pkt_t;

#ifdef AT_USING_SOCKET_SERVER
struct at_listen_state
{
    uint16_t is_listen;
    uint16_t port;
};
#endif

struct at_socket
{
    /* AT socket magic word */
    uint32_t magic;

    int socket;
#ifdef AT_USING_SOCKET_SERVER
    struct at_listen_state listen;
#endif

    /* device releated information for the socket */
    void *device;
    /* type of the AT socket (TCP, UDP or RAW) */
    enum at_socket_type type;
    /* current state of the AT socket */
    enum at_socket_state state;
    /* sockets operations */
    const struct at_socket_ops *ops;
    /* receive semaphore, received data release semaphore */
    rt_sem_t recv_notice;
    rt_mutex_t recv_lock;
    rt_slist_t recvpkt_list;

    /* timeout to wait for send or received data in milliseconds */
    int32_t recv_timeout;
    int32_t send_timeout;
    /* A callback function that is informed about events for this AT socket */
    at_socket_callback callback;

    /* number of times data was received, set by event_callback() */
    uint16_t rcvevent;
    /* number of times data was ACKed (free send buffer), set by event_callback() */
    uint16_t sendevent;
    /* error happened for this socket, set by event_callback() */
    uint16_t errevent;
    /* Last UDP connect address */
    struct sockaddr last_udp_adr;

#ifdef SAL_USING_POSIX
    rt_wqueue_t wait_head;
#endif
    rt_slist_t list;

    /* user-specific data */
    void *user_data;
};

int at_socket(int domain, int type, int protocol);
int at_closesocket(int socket);
int at_shutdown(int socket, int how);
int at_bind(int socket, const struct sockaddr *name, socklen_t namelen);
#ifdef AT_USING_SOCKET_SERVER
int at_listen(int socket, int backlog);
#endif
int at_connect(int socket, const struct sockaddr *name, socklen_t namelen);
#ifdef AT_USING_SOCKET_SERVER
int at_accept(int socket, struct sockaddr *name, socklen_t *namelen);
#endif
int at_sendto(int socket, const void *data, size_t size, int flags, const struct sockaddr *to, socklen_t tolen);
int at_send(int socket, const void *data, size_t size, int flags);
int at_recvfrom(int socket, void *mem, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen);
int at_recv(int socket, void *mem, size_t len, int flags);
int at_getsockopt(int socket, int level, int optname, void *optval, socklen_t *optlen);
int at_setsockopt(int socket, int level, int optname, const void *optval, socklen_t optlen);
struct hostent *at_gethostbyname(const char *name);
int at_gethostbyname_r(const char *name, struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop);
int at_getaddrinfo(const char *nodename, const char *servname, const struct addrinfo *hints, struct addrinfo **res);
void at_freeaddrinfo(struct addrinfo *ai);

struct at_socket *at_get_socket(int socket);
#ifdef AT_USING_SOCKET_SERVER
struct at_socket *at_get_base_socket(int base_socket);
#endif

#ifndef RT_USING_SAL

#define socket(domain, type, protocol)                      at_socket(domain, type, protocol)
#define closesocket(socket)                                 at_closesocket(socket)
#define shutdown(socket, how)                               at_shutdown(socket, how)
#define bind(socket, name, namelen)                         at_bind(socket, name, namelen)
#define connect(socket, name, namelen)                      at_connect(socket, name, namelen)
#define sendto(socket, data, size, flags, to, tolen)        at_sendto(socket, data, size, flags, to, tolen)
#define send(socket, data, size, flags)                     at_send(socket, data, size, flags)
#define recvfrom(socket, mem, len, flags, from, fromlen)    at_recvfrom(socket, mem, len, flags, from, fromlen)
#define getsockopt(socket, level, optname, optval, optlen)  at_getsockopt(socket, level, optname, optval, optlen)
#define setsockopt(socket, level, optname, optval, optlen)  at_setsockopt(socket, level, optname, optval, optlen)

#define gethostbyname(name)                                 at_gethostbyname(name)
#define getaddrinfo(nodename, servname, hints, res)         at_getaddrinfo(nodename, servname, hints, res)
#define freeaddrinfo(ai)                                    at_freeaddrinfo(ai)

#endif /* RT_USING_SAL */

#ifdef __cplusplus
}
#endif

#endif /* AT_SOCKET_H__ */
