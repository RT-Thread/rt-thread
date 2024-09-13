/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-13     RT-Thread    Export as header
 */
#ifndef __LWP_SYS_SOCKET_H__
#define __LWP_SYS_SOCKET_H__

/* socket levels */
#define INTF_SOL_SOCKET     1
#define IMPL_SOL_SOCKET     0xFFF

#define INTF_IPPROTO_IP     0
#define IMPL_IPPROTO_IP     0

#define INTF_IPPROTO_TCP    6
#define IMPL_IPPROTO_TCP    6

#define INTF_IPPROTO_IPV6   41
#define IMPL_IPPROTO_IPV6   41

/* SOL_SOCKET option names */
#define INTF_SO_BROADCAST   6
#define INTF_SO_KEEPALIVE   9
#define INTF_SO_REUSEADDR   2
#define INTF_SO_TYPE        3
#define INTF_SO_ERROR       4
#define INTF_SO_SNDTIMEO    21
#define INTF_SO_RCVTIMEO    20
#define INTF_SO_RCVBUF      8
#define INTF_SO_LINGER      13
#define INTF_SO_NO_CHECK    11
#define INTF_SO_ACCEPTCONN  30
#define INTF_SO_DONTROUTE   5
#define INTF_SO_OOBINLINE   10
#define INTF_SO_REUSEPORT   15
#define INTF_SO_SNDBUF      7
#define INTF_SO_SNDLOWAT    19
#define INTF_SO_RCVLOWAT    18
#define INTF_SO_BINDTODEVICE        25
#define INTF_SO_TIMESTAMPNS         35
#define INTF_SO_TIMESTAMPING        37
#define INTF_SO_SELECT_ERR_QUEUE    45

#define IMPL_SO_BROADCAST   0x0020
#define IMPL_SO_KEEPALIVE   0x0008
#define IMPL_SO_REUSEADDR   0x0004
#define IMPL_SO_TYPE        0x1008
#define IMPL_SO_ERROR       0x1007
#define IMPL_SO_SNDTIMEO    0x1005
#define IMPL_SO_RCVTIMEO    0x1006
#define IMPL_SO_RCVBUF      0x1002
#define IMPL_SO_LINGER      0x0080
#define IMPL_SO_NO_CHECK    0x100a
#define IMPL_SO_ACCEPTCONN  0x0002
#define IMPL_SO_DONTROUTE   0x0010
#define IMPL_SO_OOBINLINE   0x0100
#define IMPL_SO_REUSEPORT   0x0200
#define IMPL_SO_SNDBUF      0x1001
#define IMPL_SO_SNDLOWAT    0x1003
#define IMPL_SO_RCVLOWAT    0x1004
#define IMPL_SO_BINDTODEVICE        0x100b
#define IMPL_SO_TIMESTAMPNS         INTF_SO_TIMESTAMPNS
#define IMPL_SO_TIMESTAMPING        INTF_SO_TIMESTAMPING
#define IMPL_SO_SELECT_ERR_QUEUE    INTF_SO_SELECT_ERR_QUEUE

/* IPPROTO_IP option names */
#define INTF_IP_TTL 2
#define INTF_IP_TOS 1
#define INTF_IP_MULTICAST_TTL   33
#define INTF_IP_MULTICAST_IF    32
#define INTF_IP_MULTICAST_LOOP  34
#define INTF_IP_ADD_MEMBERSHIP  35
#define INTF_IP_DROP_MEMBERSHIP 36

#define IMPL_IP_TTL  2
#define IMPL_IP_TOS  1
#define IMPL_IP_MULTICAST_TTL   5
#define IMPL_IP_MULTICAST_IF    6
#define IMPL_IP_MULTICAST_LOOP  7
#define IMPL_IP_ADD_MEMBERSHIP  3
#define IMPL_IP_DROP_MEMBERSHIP 4

/* IPPROTO_TCP option names */
#define INTF_TCP_NODELAY    1
#define INTF_TCP_KEEPALIVE  9
#define INTF_TCP_KEEPIDLE   4
#define INTF_TCP_KEEPINTVL  5
#define INTF_TCP_KEEPCNT    6

#define IMPL_TCP_NODELAY    0x01
#define IMPL_TCP_KEEPALIVE  0x02
#define IMPL_TCP_KEEPIDLE   0x03
#define IMPL_TCP_KEEPINTVL  0x04
#define IMPL_TCP_KEEPCNT    0x05

/* IPPROTO_IPV6 option names */
#define INTF_IPV6_V6ONLY    26
#define IMPL_IPV6_V6ONLY    27

struct musl_sockaddr
{
    uint16_t sa_family;
    char     sa_data[14];
};

struct musl_ifmap {
    unsigned long int mem_start;
    unsigned long int mem_end;
    unsigned short int base_addr;
    unsigned char irq;
    unsigned char dma;
    unsigned char port;
};

struct musl_ifreq
{
    union
    {
#define IFNAMSIZ    16
        char ifrn_name[IFNAMSIZ];
    } ifr_ifrn;
    union
    {
        struct musl_sockaddr ifru_addr;
        struct musl_sockaddr ifru_dstaddr;
        struct musl_sockaddr ifru_broadaddr;
        struct musl_sockaddr ifru_netmask;
        struct musl_sockaddr ifru_hwaddr;
        short int ifru_flags;
        int ifru_ivalue;
        int ifru_mtu;
        struct musl_ifmap ifru_map;
        char ifru_slave[IFNAMSIZ];
        char ifru_newname[IFNAMSIZ];
        char *ifru_data;
    } ifr_ifru;
};

struct musl_rtentry
{
    unsigned long int rt_pad1;
    struct musl_sockaddr rt_dst;
    struct musl_sockaddr rt_gateway;
    struct musl_sockaddr rt_genmask;
    unsigned short int rt_flags;
    short int rt_pad2;
    unsigned long int rt_pad3;
    unsigned char rt_tos;
    unsigned char rt_class;
    short int rt_pad4[sizeof(long)/2-1];
    short int rt_metric;
    char *rt_dev;
    unsigned long int rt_mtu;
    unsigned long int rt_window;
    unsigned short int rt_irtt;
};

#endif /* __LWP_SYS_SOCKET_H__ */
