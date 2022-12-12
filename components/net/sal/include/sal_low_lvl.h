/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     ChenYong     First version
 * 2022-05-15     Meco Man     rename sal.h as sal_low_lvl.h to avoid conflicts
 *                             with Microsoft Visual Studio header file
 */

#ifndef SAL_LOW_LEVEL_H__
#define SAL_LOW_LEVEL_H__

#include <rtdevice.h>

#ifdef SAL_USING_POSIX
#include <dfs_file.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(socklen_t) && !defined(SOCKLEN_T_DEFINED)
typedef uint32_t socklen_t;
#endif

/* SAL socket magic word */
#define SAL_SOCKET_MAGIC               0x5A10

/* The maximum number of sockets structure */
#ifndef SAL_SOCKETS_NUM
#define SAL_SOCKETS_NUM                DFS_FD_MAX
#endif

/* The maximum number of protocol families */
#ifndef SAL_PROTO_FAMILIES_NUM
#define SAL_PROTO_FAMILIES_NUM         4
#endif

/* SAL socket offset */
#ifndef SAL_SOCKET_OFFSET
#define SAL_SOCKET_OFFSET              0
#endif

struct sal_socket
{
    uint32_t magic;                    /* SAL socket magic word */

    int socket;                        /* SAL socket descriptor */
    int domain;
    int type;
    int protocol;

    struct netdev *netdev;             /* SAL network interface device */

    void *user_data;                   /* user-specific data */
#ifdef SAL_USING_TLS
    void *user_data_tls;               /* user-specific TLS data */
#endif
};

/* network interface socket opreations */
struct sal_socket_ops
{
    int (*socket)     (int domain, int type, int protocol);
    int (*closesocket)(int s);
    int (*bind)       (int s, const struct sockaddr *name, socklen_t namelen);
    int (*listen)     (int s, int backlog);
    int (*connect)    (int s, const struct sockaddr *name, socklen_t namelen);
    int (*accept)     (int s, struct sockaddr *addr, socklen_t *addrlen);
    int (*sendto)     (int s, const void *data, size_t size, int flags, const struct sockaddr *to, socklen_t tolen);
    int (*recvfrom)   (int s, void *mem, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen);
    int (*getsockopt) (int s, int level, int optname, void *optval, socklen_t *optlen);
    int (*setsockopt) (int s, int level, int optname, const void *optval, socklen_t optlen);
    int (*shutdown)   (int s, int how);
    int (*getpeername)(int s, struct sockaddr *name, socklen_t *namelen);
    int (*getsockname)(int s, struct sockaddr *name, socklen_t *namelen);
    int (*ioctlsocket)(int s, long cmd, void *arg);
#ifdef SAL_USING_POSIX
    int (*poll)       (struct dfs_fd *file, struct rt_pollreq *req);
#endif
};

/* sal network database name resolving */
struct sal_netdb_ops
{
    struct hostent* (*gethostbyname)  (const char *name);
    int             (*gethostbyname_r)(const char *name, struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop);
    int             (*getaddrinfo)    (const char *nodename, const char *servname, const struct addrinfo *hints, struct addrinfo **res);
    void            (*freeaddrinfo)   (struct addrinfo *ai);
};

struct sal_proto_family
{
    int family;                                  /* primary protocol families type */
    int sec_family;                              /* secondary protocol families type */
    const struct sal_socket_ops *skt_ops;        /* socket opreations */
    const struct sal_netdb_ops *netdb_ops;       /* network database opreations */
};

/* SAL(Socket Abstraction Layer) initialize */
int sal_init(void);
/* Get SAL socket object by socket descriptor */
struct sal_socket *sal_get_socket(int sock);

/* check SAL socket netweork interface device internet status */
int sal_check_netdev_internet_up(struct netdev *netdev);

#ifdef __cplusplus
}
#endif

#endif /* SAL_H__ */
