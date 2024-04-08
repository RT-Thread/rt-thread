/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-02-17     Bernard      First version
 * 2018-05-17     ChenYong     Add socket abstraction layer
 */

#ifndef SYS_SOCKET_H_
#define SYS_SOCKET_H_

#include <rtthread.h>
#include <sal_socket.h>
#ifdef SAL_USING_TLS
#include <sal_tls.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SAL_USING_POSIX
int accept(int s, struct sockaddr *addr, socklen_t *addrlen);
int bind(int s, const struct sockaddr *name, socklen_t namelen);
int shutdown(int s, int how);
int getpeername(int s, struct sockaddr *name, socklen_t *namelen);
int getsockname(int s, struct sockaddr *name, socklen_t *namelen);
int getsockopt(int s, int level, int optname, void *optval, socklen_t *optlen);
int setsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
int connect(int s, const struct sockaddr *name, socklen_t namelen);
int listen(int s, int backlog);
int recv(int s, void *mem, size_t len, int flags);
int recvfrom(int s, void *mem, size_t len, int flags,
      struct sockaddr *from, socklen_t *fromlen);
int recvmsg(int s, struct msghdr *message, int flags);
int sendmsg(int s, const struct msghdr *message, int flags);
int send(int s, const void *dataptr, size_t size, int flags);
int sendto(int s, const void *dataptr, size_t size, int flags,
    const struct sockaddr *to, socklen_t tolen);
int socket(int domain, int type, int protocol);
int closesocket(int s);
int ioctlsocket(int s, long cmd, void *arg);
int socketpair(int domain, int type, int protocol, int *fds);
#else
#define accept(s, addr, addrlen)                           sal_accept(s, addr, addrlen)
#define bind(s, name, namelen)                             sal_bind(s, name, namelen)
#define shutdown(s, how)                                   sal_shutdown(s, how)
#define getpeername(s, name, namelen)                      sal_getpeername(s, name, namelen)
#define getsockname(s, name, namelen)                      sal_getsockname(s, name, namelen)
#define getsockopt(s, level, optname, optval, optlen)      sal_getsockopt(s, level, optname, optval, optlen)
#define setsockopt(s, level, optname, optval, optlen)      sal_setsockopt(s, level, optname, optval, optlen)
#define connect(s, name, namelen)                          sal_connect(s, name, namelen)
#define listen(s, backlog)                                 sal_listen(s, backlog)
#define recv(s, mem, len, flags)                           sal_recvfrom(s, mem, len, flags, NULL, NULL)
#define recvfrom(s, mem, len, flags, from, fromlen)        sal_recvfrom(s, mem, len, flags, from, fromlen)
#define recvmsg(s, message, flags)                         sal_recvmsg(s, message, flags)
#define send(s, dataptr, size, flags)                      sal_sendto(s, dataptr, size, flags, NULL, NULL)
#define sendto(s, dataptr, size, flags, to, tolen)         sal_sendto(s, dataptr, size, flags, to, tolen)
#define sendmsg(s, message, flags)                         sal_sendmsg(s, message, flags)
#define socket(domain, type, protocol)                     sal_socket(domain, type, protocol)
#define socketpair(domain, type, protocol, fds)            sal_socketpair(domain, type, protocol, fds)
#define closesocket(s)                                     sal_closesocket(s)
#define ioctlsocket(s, cmd, arg)                           sal_ioctlsocket(s, cmd, arg)
#endif /* SAL_USING_POSIX */

#ifdef __cplusplus
}
#endif

#endif /* _SYS_SOCKET_H_ */
