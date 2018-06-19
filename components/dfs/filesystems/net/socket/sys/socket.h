/*
 * File      : socket.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
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
 * 2015-02-17     Bernard      First version
 */

#ifndef SOCKET_H__
#define SOCKET_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <lwip/sockets.h>
#include <lwip/api.h>
#include <lwip/init.h>

#include <rtdevice.h>

#if LWIP_VERSION < 0x2000000
typedef uint16_t sa_family_t;
typedef uint16_t in_port_t;

struct sockaddr_storage
{
    sa_family_t ss_family;       /* Address family */
    char        ss_data[14];     /* 14-bytes of address data */
};
#endif

#if LWIP_VERSION < 0x2000000
#define SELWAIT_T int
#else
#ifndef SELWAIT_T
#define SELWAIT_T u8_t
#endif
#endif

/*
 * Re-define lwip socket
 *
 * NOTE: please make sure the definitions same in lwip::net_socket.c
 */
struct lwip_sock {
  /** sockets currently are built on netconns, each socket has one netconn */
  struct netconn *conn;
  /** data that was left from the previous read */
  void *lastdata;
  /** offset in the data that was left from the previous read */
  u16_t lastoffset;
  /** number of times data was received, set by event_callback(),
      tested by the receive and select functions */
  s16_t rcvevent;
  /** number of times data was ACKed (free send buffer), set by event_callback(),
      tested by select */
  u16_t sendevent;
  /** error happened for this socket, set by event_callback(), tested by select */
  u16_t errevent;
  /** last error that occurred on this socket */
#if LWIP_VERSION < 0x2000000
  int err;
#else
  u8_t err;
#endif
  /** counter of how many threads are waiting for this socket using select */
  SELWAIT_T select_waiting;

  rt_wqueue_t wait_head;
};
struct lwip_sock *lwip_tryget_socket(int s);

int accept(int s, struct sockaddr *addr, socklen_t *addrlen);
int bind(int s, const struct sockaddr *name, socklen_t namelen);
int shutdown(int s, int how);
int getpeername (int s, struct sockaddr *name, socklen_t *namelen);
int getsockname (int s, struct sockaddr *name, socklen_t *namelen);
int getsockopt (int s, int level, int optname, void *optval, socklen_t *optlen);
int setsockopt (int s, int level, int optname, const void *optval, socklen_t optlen);
int connect(int s, const struct sockaddr *name, socklen_t namelen);
int listen(int s, int backlog);
int recv(int s, void *mem, size_t len, int flags);
int recvfrom(int s, void *mem, size_t len, int flags,
      struct sockaddr *from, socklen_t *fromlen);
int send(int s, const void *dataptr, size_t size, int flags);
int sendto(int s, const void *dataptr, size_t size, int flags,
    const struct sockaddr *to, socklen_t tolen);
int socket(int domain, int type, int protocol);
int closesocket(int s);
int ioctlsocket(int s, long cmd, void *arg);

#ifdef __cplusplus
}
#endif

#endif
