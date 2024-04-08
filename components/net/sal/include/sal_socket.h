/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-24     ChenYong     First version
 */

#ifndef SAL_SOCKET_H__
#define SAL_SOCKET_H__

#include <stddef.h>
#include <arpa/inet.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(socklen_t) && !defined(SOCKLEN_T_DEFINED)
typedef uint32_t socklen_t;
#endif

#if !defined(sa_family_t) && !defined(SA_FAMILY_T_DEFINED)
typedef uint8_t sa_family_t;
#endif

/* If your port already typedef's in_port_t, define IN_PORT_T_DEFINED
   to prevent this code from redefining it. */
#if !defined(in_port_t) && !defined(IN_PORT_T_DEFINED)
typedef uint16_t in_port_t;
#endif

/* Socket protocol types (TCP/UDP/RAW) */
#define SOCK_STREAM     1
#define SOCK_DGRAM      2
#define SOCK_RAW        3
#define SOCK_PACKET     10

#define SOCK_NONBLOCK   04000
#define SOCK_CLOEXEC    02000000

#define SOCK_MAX        (SOCK_CLOEXEC + 1)

/* Option flags per-socket. These must match the SOF_ flags in ip.h (checked in init.c) */
#define SO_REUSEADDR    0x0004 /* Allow local address reuse */
#define SO_KEEPALIVE    0x0008 /* keep connections alive */
#define SO_BROADCAST    0x0020 /* permit to send and to receive broadcast messages (see IP_SOF_BROADCAST option) */

#define SO_PASSCRED         16
#define SO_PEERCRED         17

#define SO_BINDTODEVICE     25
#define SO_ATTACH_FILTER    26
#define SO_DETACH_FILTER    27

#define SO_SNDBUFFORCE      32
#define SO_RCVBUFFORCE      33
#define SO_PROTOCOL         38
#define SO_DOMAIN           39

/* Additional options, not kept in so_options */
#define SO_DEBUG        0x0001 /* Unimplemented: turn on debugging info recording */
#define SO_ACCEPTCONN   0x0002 /* socket has had listen() */
#define SO_DONTROUTE    0x0010 /* Unimplemented: just use interface addresses */
#define SO_USELOOPBACK  0x0040 /* Unimplemented: bypass hardware when possible */
#define SO_LINGER       0x0080 /* linger on close if data present */
#define SO_DONTLINGER   ((int)(~SO_LINGER))
#define SO_OOBINLINE    0x0100 /* Unimplemented: leave received OOB data in line */
#define SO_REUSEPORT    0x0200 /* Unimplemented: allow local address & port reuse */
#define SO_SNDBUF       0x1001 /* Unimplemented: send buffer size */
#define SO_RCVBUF       0x1002 /* receive buffer size */
#define SO_SNDLOWAT     0x1003 /* Unimplemented: send low-water mark */
#define SO_RCVLOWAT     0x1004 /* Unimplemented: receive low-water mark */
#define SO_SNDTIMEO     0x1005 /* send timeout */
#define SO_RCVTIMEO     0x1006 /* receive timeout */
#define SO_ERROR        0x1007 /* get error status and clear */
#define SO_TYPE         0x1008 /* get socket type */
#define SO_CONTIMEO     0x1009 /* Unimplemented: connect timeout */
#define SO_NO_CHECK     0x100a /* don't create UDP checksum */

/* Level number for (get/set)sockopt() to apply to socket itself */
#define SOL_SOCKET      0xfff    /* options for socket level */
#define SOL_NETLINK     270

#define AF_UNSPEC       0
#define AF_UNIX         1
#define AF_INET         2
#define AF_INET6        10
#define AF_NETLINK      16
#define AF_CAN          29  /* Controller Area Network      */
#define AF_AT           45  /* AT socket */
#define AF_WIZ          46  /* WIZnet socket */
#define PF_UNIX         AF_UNIX
#define PF_INET         AF_INET
#define PF_INET6        AF_INET6
#define PF_NETLINK      AF_NETLINK
#define PF_UNSPEC       AF_UNSPEC
#define PF_CAN          AF_CAN
#define PF_AT           AF_AT
#define PF_WIZ          AF_WIZ

#define AF_MAX          (AF_WIZ + 1)  /* For now.. */

#define IPPROTO_IP      0
#define IPPROTO_ICMP    1
#define IPPROTO_TCP     6
#define IPPROTO_UDP     17
#define IPPROTO_IPV6    41
#define IPPROTO_ICMPV6  58
#define IPPROTO_UDPLITE 136
#define IPPROTO_RAW     255

/* Flags we can use with send and recv */
#define MSG_PEEK        0x01    /* Peeks at an incoming message */
#define MSG_WAITALL     0x02    /* Unimplemented: Requests that the function block until the full amount of data requested can be returned */
#define MSG_OOB         0x04    /* Unimplemented: Requests out-of-band data. The significance and semantics of out-of-band data are protocol-specific */
#define MSG_DONTWAIT    0x08    /* Nonblocking i/o for this operation only */
#define MSG_MORE        0x10    /* Sender will send more */

#define MSG_ERRQUEUE    0x2000  /* Fetch message from error queue */
#define MSG_CONFIRM     0x0800  /* Confirm path validity */

/* Options for level IPPROTO_IP */
#define IP_TOS             1
#define IP_TTL             2

/* Options for level IPPROTO_TCP */
#define TCP_NODELAY     0x01    /* don't delay send to coalesce packets */
#define TCP_KEEPALIVE   0x02    /* send KEEPALIVE probes when idle for pcb->keep_idle milliseconds */
#define TCP_KEEPIDLE    0x03    /* set pcb->keep_idle  - Same as TCP_KEEPALIVE, but use seconds for get/setsockopt */
#define TCP_KEEPINTVL   0x04    /* set pcb->keep_intvl - Use seconds for get/setsockopt */
#define TCP_KEEPCNT     0x05    /* set pcb->keep_cnt   - Use number of probes sent for get/setsockopt */

/* Options and types related to multicast membership */
#define IP_ADD_MEMBERSHIP  3
#define IP_DROP_MEMBERSHIP 4
/* Options and types for UDP multicast traffic handling */
#define IP_MULTICAST_TTL   5
#define IP_MULTICAST_IF    6
#define IP_MULTICAST_LOOP  7

typedef struct ip_mreq
{
    struct in_addr imr_multiaddr; /* IP multicast address of group */
    struct in_addr imr_interface; /* local IP address of interface */
} ip_mreq;

/* The Type of Service provides an indication of the abstract parameters of the quality of service desired */
#define IPTOS_TOS_MASK                 0x1E
#define IPTOS_TOS(tos)                 ((tos) & IPTOS_TOS_MASK)
#define IPTOS_LOWDELAY                 0x10
#define IPTOS_THROUGHPUT               0x08
#define IPTOS_RELIABILITY              0x04
#define IPTOS_LOWCOST                  0x02
#define IPTOS_MINCOST                  IPTOS_LOWCOST

/* The Network Control precedence designation is intended to be used within a network only */
#define IPTOS_PREC_MASK                0xe0
#define IPTOS_PREC(tos)                ((tos) & IPTOS_PREC_MASK)
#define IPTOS_PREC_NETCONTROL          0xe0
#define IPTOS_PREC_INTERNETCONTROL     0xc0
#define IPTOS_PREC_CRITIC_ECP          0xa0
#define IPTOS_PREC_FLASHOVERRIDE       0x80
#define IPTOS_PREC_FLASH               0x60
#define IPTOS_PREC_IMMEDIATE           0x40
#define IPTOS_PREC_PRIORITY            0x20
#define IPTOS_PREC_ROUTINE             0x00

#define SCM_RIGHTS      0x01        /* rw: access rights (array of int) */
#define SCM_CREDENTIALS 0x02        /* rw: struct ucred     */
#define SCM_SECURITY    0x03        /* rw: security label       */

/* Options for shatdown type */
#ifndef SHUT_RD
  #define SHUT_RD       0
  #define SHUT_WR       1
  #define SHUT_RDWR     2
#endif

struct sockaddr
{
    uint8_t        sa_len;
    sa_family_t    sa_family;
    char           sa_data[14];
};

/* Structure describing the address of an AF_LOCAL (aka AF_UNIX) socket.  */
struct sockaddr_un
{
    unsigned short sa_family;
    char sun_path[108];         /* Path name.  */
};

#if NETDEV_IPV4
/* members are in network byte order */
struct sockaddr_in
{
    uint8_t        sin_len;
    sa_family_t    sin_family;
    in_port_t      sin_port;
    struct in_addr sin_addr;
#define SIN_ZERO_LEN 8
    char            sin_zero[SIN_ZERO_LEN];
};
#endif /* NETDEV_IPV4 */

#if NETDEV_IPV6
struct sockaddr_in6
{
  uint8_t         sin6_len;      /* length of this structure    */
  sa_family_t     sin6_family;   /* AF_INET6                    */
  in_port_t       sin6_port;     /* Transport layer port #      */
  uint32_t        sin6_flowinfo; /* IPv6 flow information       */
  struct in6_addr sin6_addr;     /* IPv6 address                */
  uint32_t        sin6_scope_id; /* Set of interfaces for scope */
};
#endif /* NETDEV_IPV6 */

struct sockaddr_storage
{
    uint8_t        s2_len;
    sa_family_t    ss_family;
    char           s2_data1[2];
    uint32_t       s2_data2[3];
#if NETDEV_IPV6
    uint32_t       s2_data3[3];
#endif /* NETDEV_IPV6 */
};

#ifdef RT_USING_MUSLLIBC
#ifndef __DEFINED_struct_iovec
struct iovec
{
    void *iov_base;
    size_t iov_len;
};
#endif
#endif

struct msghdr
{
    void            *msg_name;
    socklen_t        msg_namelen;
    struct iovec    *msg_iov;
    int              msg_iovlen;
    void            *msg_control;
    socklen_t        msg_controllen;
    int              msg_flags;
};

/* RFC 3542, Section 20: Ancillary Data */
struct cmsghdr
{
    size_t  cmsg_len;   /* number of bytes, including header */
    int     cmsg_level; /* originating protocol */
    int     cmsg_type;  /* protocol-specific type */
};

#define CMSG_NXTHDR(mhdr, cmsg) cmsg_nxthdr((mhdr), (cmsg))

#define CMSG_ALIGN(len) (((len) + sizeof(long) - 1) & ~(sizeof(long)-1))

#define CMSG_DATA(cmsg) ((void *)(cmsg) + sizeof(struct cmsghdr))
#define CMSG_SPACE(len) (sizeof(struct cmsghdr) + CMSG_ALIGN(len))
#define CMSG_LEN(len)   (sizeof(struct cmsghdr) + (len))

#define __CMSG_FIRSTHDR(ctl, len) \
    ((len) >= sizeof(struct cmsghdr) ? (struct cmsghdr *)(ctl) : (struct cmsghdr *)NULL)

#define CMSG_FIRSTHDR(msg)  __CMSG_FIRSTHDR((msg)->msg_control, (msg)->msg_controllen)
#define CMSG_OK(mhdr, cmsg) \
    ((cmsg)->cmsg_len >= sizeof(struct cmsghdr) && \
    (cmsg)->cmsg_len <= (unsigned long)((mhdr)->msg_controllen - ((char *)(cmsg) - (char *)(mhdr)->msg_control)))

#define for_each_cmsghdr(cmsg, msg) \
    for (cmsg = CMSG_FIRSTHDR(msg); cmsg; cmsg = CMSG_NXTHDR(msg, cmsg))

static inline struct cmsghdr *__cmsg_nxthdr(void *_ctl, size_t _size, struct cmsghdr *_cmsg)
{
    struct cmsghdr *_ptr;

    _ptr = (struct cmsghdr *)(((unsigned char *)_cmsg) + CMSG_ALIGN(_cmsg->cmsg_len));

    if ((unsigned long)((char *)(_ptr + 1) - (char *)_ctl) > _size)
    {
        return (struct cmsghdr *)NULL;
    }

    return _ptr;
}

static inline struct cmsghdr *cmsg_nxthdr(struct msghdr *_msg, struct cmsghdr *_cmsg)
{
    return __cmsg_nxthdr(_msg->msg_control, _msg->msg_controllen, _cmsg);
}

#define IFNAMSIZ    16
struct sal_ifmap
{
    unsigned long int mem_start;
    unsigned long int mem_end;
    unsigned short int base_addr;
    unsigned char irq;
    unsigned char dma;
    unsigned char port;
};

struct sal_ifreq
{
    union
    {
        char ifrn_name[IFNAMSIZ];
    } ifr_ifrn;
    union
    {
        struct sockaddr ifru_addr;
        struct sockaddr ifru_dstaddr;
        struct sockaddr ifru_broadaddr;
        struct sockaddr ifru_netmask;
        struct sockaddr ifru_hwaddr;
        short int ifru_flags;
        int ifru_ivalue;
        int ifru_mtu;
        struct sal_ifmap ifru_map;
        char ifru_slave[IFNAMSIZ];
        char ifru_newname[IFNAMSIZ];
        char *ifru_data;
    } ifr_ifru;
};

int sal_accept(int socket, struct sockaddr *addr, socklen_t *addrlen);
int sal_bind(int socket, const struct sockaddr *name, socklen_t namelen);
int sal_shutdown(int socket, int how);
int sal_getpeername (int socket, struct sockaddr *name, socklen_t *namelen);
int sal_getsockname (int socket, struct sockaddr *name, socklen_t *namelen);
int sal_getsockopt (int socket, int level, int optname, void *optval, socklen_t *optlen);
int sal_setsockopt (int socket, int level, int optname, const void *optval, socklen_t optlen);
int sal_connect(int socket, const struct sockaddr *name, socklen_t namelen);
int sal_listen(int socket, int backlog);
int sal_sendmsg(int socket, const struct msghdr *message, int flags);
int sal_recvmsg(int socket, struct msghdr *message, int flags);
int sal_recvfrom(int socket, void *mem, size_t len, int flags,
      struct sockaddr *from, socklen_t *fromlen);
int sal_sendto(int socket, const void *dataptr, size_t size, int flags,
    const struct sockaddr *to, socklen_t tolen);
int sal_socket(int domain, int type, int protocol);
int sal_socketpair(int domain, int type, int protocol, int *fds);
int sal_closesocket(int socket);
int sal_ioctlsocket(int socket, long cmd, void *arg);

#ifdef __cplusplus
}
#endif

#endif /* SAL_SOCKET_H__ */
