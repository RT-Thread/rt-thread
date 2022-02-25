/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-23     Meco Man     integrate v1.4.1 v2.0.3 and v2.1.2 porting layer
 * 2022-02-25     xiangxistu   modify the default config through v1.4.1
 */

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#include <rtconfig.h>

/* ---------- LIBC and standard header files ---------- */
#include <limits.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/errno.h>
#define LWIP_ERRNO_INCLUDE "sys/errno.h"

#define LWIP_TIMEVAL_PRIVATE    0
#define LWIP_NO_UNISTD_H        0
#define LWIP_NO_STDDEF_H        0
#define LWIP_NO_STDINT_H        0
#define LWIP_NO_INTTYPES_H      0
#define LWIP_NO_LIMITS_H        0
#define LWIP_NO_CTYPE_H         0
#define LWIP_SOCKET_SELECT      1
#define LWIP_SOCKET_POLL        1

#define LWIP_RAND rand

#ifndef SSIZE_MAX
#define SSIZE_MAX INT_MAX
#endif

/* some errno not defined in newlib */
#ifndef ENSRNOTFOUND
#define ENSRNOTFOUND 163  /* Domain name not found */
#endif

/* ---------- Basic Configuration ---------- */
#define LWIP_IPV4                   1

#ifdef RT_USING_LWIP_IPV6
#define LWIP_IPV6                   1
#else
#define LWIP_IPV6                   0
#endif /* RT_USING_LWIP_IPV6 */

#define NO_SYS                      0
#define SYS_LIGHTWEIGHT_PROT        1
#define LWIP_SOCKET                 1
#define LWIP_NETCONN                1

#ifdef RT_LWIP_IGMP
#define LWIP_IGMP                   1
#else
#define LWIP_IGMP                   0
#endif

#ifdef RT_LWIP_ICMP
#define LWIP_ICMP                   1
#else
#define LWIP_ICMP                   0
#endif

#ifdef RT_LWIP_SNMP
#define LWIP_SNMP                   1
#else
#define LWIP_SNMP                   0
#endif

#ifdef RT_LWIP_DNS
#define LWIP_DNS                    1
#else
#define LWIP_DNS                    0
#endif

#define LWIP_HAVE_LOOPIF            0

#define LWIP_PLATFORM_BYTESWAP      0

/* #define RT_LWIP_DEBUG */

#ifdef RT_LWIP_DEBUG
#define LWIP_DEBUG
#endif

/* ---------- Debug options ---------- */
#ifdef LWIP_DEBUG
#ifdef RT_LWIP_SYS_DEBUG
#define SYS_DEBUG                   LWIP_DBG_ON
#else
#define SYS_DEBUG                   LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_ETHARP_DEBUG
#define ETHARP_DEBUG                LWIP_DBG_ON
#else
#define ETHARP_DEBUG                LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_PPP_DEBUG
#define PPP_DEBUG                   LWIP_DBG_ON
#else
#define PPP_DEBUG                   LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_MEM_DEBUG
#define MEM_DEBUG                   LWIP_DBG_ON
#else
#define MEM_DEBUG                   LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_MEMP_DEBUG
#define MEMP_DEBUG                  LWIP_DBG_ON
#else
#define MEMP_DEBUG                  LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_PBUF_DEBUG
#define PBUF_DEBUG                  LWIP_DBG_ON
#else
#define PBUF_DEBUG                  LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_API_LIB_DEBUG
#define API_LIB_DEBUG               LWIP_DBG_ON
#else
#define API_LIB_DEBUG               LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_API_MSG_DEBUG
#define API_MSG_DEBUG               LWIP_DBG_ON
#else
#define API_MSG_DEBUG               LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_TCPIP_DEBUG
#define TCPIP_DEBUG                 LWIP_DBG_ON
#else
#define TCPIP_DEBUG                 LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_NETIF_DEBUG
#define NETIF_DEBUG                 LWIP_DBG_ON
#else
#define NETIF_DEBUG                 LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_SOCKETS_DEBUG
#define SOCKETS_DEBUG               LWIP_DBG_ON
#else
#define SOCKETS_DEBUG               LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_DNS_DEBUG
#define DNS_DEBUG                   LWIP_DBG_ON
#else
#define DNS_DEBUG                   LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_AUTOIP_DEBUG
#define AUTOIP_DEBUG                LWIP_DBG_ON
#else
#define AUTOIP_DEBUG                LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_DHCP_DEBUG
#define DHCP_DEBUG                  LWIP_DBG_ON
#else
#define DHCP_DEBUG                  LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_IP_DEBUG
#define IP_DEBUG                    LWIP_DBG_ON
#else
#define IP_DEBUG                    LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_IP_REASS_DEBUG
#define IP_REASS_DEBUG              LWIP_DBG_ON
#else
#define IP_REASS_DEBUG              LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_ICMP_DEBUG
#define ICMP_DEBUG                  LWIP_DBG_ON
#else
#define ICMP_DEBUG                  LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_IGMP_DEBUG
#define IGMP_DEBUG                  LWIP_DBG_ON
#else
#define IGMP_DEBUG                  LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_UDP_DEBUG
#define UDP_DEBUG                   LWIP_DBG_ON
#else
#define UDP_DEBUG                   LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_TCP_DEBUG
#define TCP_DEBUG                   LWIP_DBG_ON
#else
#define TCP_DEBUG                   LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_TCP_INPUT_DEBUG
#define TCP_INPUT_DEBUG             LWIP_DBG_ON
#else
#define TCP_INPUT_DEBUG             LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_TCP_OUTPUT_DEBUG
#define TCP_OUTPUT_DEBUG            LWIP_DBG_ON
#else
#define TCP_OUTPUT_DEBUG            LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_TCP_RTO_DEBUG
#define TCP_RTO_DEBUG               LWIP_DBG_ON
#else
#define TCP_RTO_DEBUG               LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_TCP_CWND_DEBUG
#define TCP_CWND_DEBUG              LWIP_DBG_ON
#else
#define TCP_CWND_DEBUG              LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_TCP_WND_DEBUG
#define TCP_WND_DEBUG               LWIP_DBG_ON
#else
#define TCP_WND_DEBUG               LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_TCP_FR_DEBUG
#define TCP_FR_DEBUG                LWIP_DBG_ON
#else
#define TCP_FR_DEBUG                LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_TCP_QLEN_DEBUG
#define TCP_QLEN_DEBUG              LWIP_DBG_ON
#else
#define TCP_QLEN_DEBUG              LWIP_DBG_OFF
#endif

#ifdef RT_LWIP_TCP_RST_DEBUG
#define TCP_RST_DEBUG               LWIP_DBG_ON
#else
#define TCP_RST_DEBUG               LWIP_DBG_OFF
#endif

#endif /* LWIP_DEBUG */

#define LWIP_DBG_TYPES_ON           (LWIP_DBG_ON|LWIP_DBG_TRACE|LWIP_DBG_STATE|LWIP_DBG_FRESH|LWIP_DBG_HALT)

/* ---------- Memory options ---------- */
#define MEMCPY(dst,src,len)             rt_memcpy(dst,src,len)
#define SMEMCPY(dst,src,len)            MEMCPY(dst,src,len)

#ifdef RT_LWIP_MEM_ALIGNMENT
#define MEM_ALIGNMENT RT_LWIP_MEM_ALIGNMENT
#else
#define MEM_ALIGNMENT               4
#endif

#define MEMP_OVERFLOW_CHECK         1
#define LWIP_ALLOW_MEM_FREE_FROM_OTHER_CONTEXT 1

//#define MEM_LIBC_MALLOC             1
//#define MEM_USE_POOLS               1
//#define MEMP_USE_CUSTOM_POOLS       1
//#define MEM_SIZE                    (1024*64)

#define MEMP_MEM_MALLOC             0

/* MEMP_NUM_PBUF: the number of memp struct pbufs. If the application
   sends a lot of data out of ROM (or other static memory), this
   should be set high. */
#define MEMP_NUM_PBUF               32 //16

/* the number of struct netconns */
#ifdef RT_MEMP_NUM_NETCONN
#define MEMP_NUM_NETCONN            RT_MEMP_NUM_NETCONN
#endif

/* the number of UDP protocol control blocks. One per active RAW "connection". */
#ifdef RT_LWIP_RAW_PCB_NUM
#define MEMP_NUM_RAW_PCB            RT_LWIP_RAW_PCB_NUM
#endif

/* the number of UDP protocol control blocks. One per active UDP "connection". */
#ifdef RT_LWIP_UDP_PCB_NUM
#define MEMP_NUM_UDP_PCB            RT_LWIP_UDP_PCB_NUM
#endif

/* the number of simulatenously active TCP connections. */
#ifdef RT_LWIP_TCP_PCB_NUM
#define MEMP_NUM_TCP_PCB            RT_LWIP_TCP_PCB_NUM
#endif

/* the number of simultaneously queued TCP */
#ifdef RT_LWIP_TCP_SEG_NUM
#define MEMP_NUM_TCP_SEG            RT_LWIP_TCP_SEG_NUM
#else
#define MEMP_NUM_TCP_SEG            TCP_SND_QUEUELEN
#endif

/*
 * You can re-define following setting in rtcofnig.h to overwrite the default
 * setting in the lwip opts.h
 */
/* MEMP_NUM_NETBUF: the number of struct netbufs. */
// #define MEMP_NUM_NETBUF             2
/* MEMP_NUM_NETCONN: the number of struct netconns. */
// #define MEMP_NUM_NETCONN            4

/* MEMP_NUM_TCPIP_MSG_*: the number of struct tcpip_msg, which is used
   for sequential API communication and incoming packets. Used in
   src/api/tcpip.c. */
// #define MEMP_NUM_TCPIP_MSG_API      16
// #define MEMP_NUM_TCPIP_MSG_INPKT    16

/* ---------- Pbuf options ---------- */
/* PBUF_POOL_SIZE: the number of buffers in the pbuf pool. */
#ifdef RT_LWIP_PBUF_NUM
#define PBUF_POOL_SIZE               RT_LWIP_PBUF_NUM
#endif

/* PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. */
#ifdef RT_LWIP_PBUF_POOL_BUFSIZE
#define PBUF_POOL_BUFSIZE            RT_LWIP_PBUF_POOL_BUFSIZE
#endif

/* PBUF_LINK_HLEN: the number of bytes that should be allocated for a
   link level header. */
#define PBUF_LINK_HLEN              16

#ifdef RT_LWIP_ETH_PAD_SIZE
#define ETH_PAD_SIZE                RT_LWIP_ETH_PAD_SIZE
#endif

#ifdef LWIP_USING_NAT
#define IP_NAT                      1
#else
#define IP_NAT                      0
#endif

/* ---------- TCP options ---------- */
#ifdef RT_LWIP_TCP
#define LWIP_TCP                    1
#else
#define LWIP_TCP                    0
#endif

#define TCP_TTL                     255

/* Controls if TCP should queue segments that arrive out of
   order. Define to 0 if your device is low on memory. */
#define TCP_QUEUE_OOSEQ             1

/* TCP Maximum segment size. */
#define TCP_MSS                     1460

/* TCP sender buffer space (bytes). */
#ifdef RT_LWIP_TCP_SND_BUF
#define TCP_SND_BUF                 RT_LWIP_TCP_SND_BUF
#else
#define TCP_SND_BUF                 (TCP_MSS * 2)
#endif

/* TCP sender buffer space (pbufs). This must be at least = 2 *
   TCP_SND_BUF/TCP_MSS for things to work. */
#define TCP_SND_QUEUELEN            (4 * TCP_SND_BUF/TCP_MSS)

/* TCP writable space (bytes). This must be less than or equal
   to TCP_SND_BUF. It is the amount of space which must be
   available in the tcp snd_buf for select to return writable */
#define TCP_SNDLOWAT                (TCP_SND_BUF/2)
#define TCP_SNDQUEUELOWAT           TCP_SND_QUEUELEN/2

/* TCP receive window. */
#ifdef RT_LWIP_TCP_WND
#define TCP_WND                     RT_LWIP_TCP_WND
#else
#define TCP_WND                     (TCP_MSS * 2)
#endif

/* Maximum number of retransmissions of data segments. */
#define TCP_MAXRTX                  12

/* Maximum number of retransmissions of SYN segments. */
#define TCP_SYNMAXRTX               4

/* tcpip thread options */
#ifdef RT_LWIP_TCPTHREAD_PRIORITY
#define TCPIP_MBOX_SIZE             RT_LWIP_TCPTHREAD_MBOX_SIZE
#define TCPIP_THREAD_PRIO           RT_LWIP_TCPTHREAD_PRIORITY
#define TCPIP_THREAD_STACKSIZE      RT_LWIP_TCPTHREAD_STACKSIZE
#else
#define TCPIP_MBOX_SIZE             8
#define TCPIP_THREAD_PRIO           128
#define TCPIP_THREAD_STACKSIZE      4096
#endif
#define TCPIP_THREAD_NAME           "tcpip"
#define DEFAULT_TCP_RECVMBOX_SIZE   10

/* ---------- ARP options ---------- */
#define LWIP_ARP                    1
#define ARP_TABLE_SIZE              10
#define ARP_QUEUEING                1

/* ---------- Checksum options ---------- */
#ifdef RT_LWIP_USING_HW_CHECKSUM
#define CHECKSUM_GEN_IP                 0
#define CHECKSUM_GEN_UDP                0
#define CHECKSUM_GEN_TCP                0
#define CHECKSUM_GEN_ICMP               0
#define CHECKSUM_CHECK_IP               0
#define CHECKSUM_CHECK_UDP              0
#define CHECKSUM_CHECK_TCP              0
#define CHECKSUM_CHECK_ICMP             0
#endif

/* ---------- IP options ---------- */
/* Define IP_FORWARD to 1 if you wish to have the ability to forward
   IP packets across network interfaces. If you are going to run lwIP
   on a device with only one network interface, define this to 0. */
#define IP_FORWARD                  0

/* IP reassembly and segmentation.These are orthogonal even
 * if they both deal with IP fragments */
#ifdef RT_LWIP_REASSEMBLY_FRAG
#define IP_REASSEMBLY               1
#define IP_FRAG                     1
#define IP_REASS_MAX_PBUFS          10
#define MEMP_NUM_REASSDATA          10
#else
#define IP_REASSEMBLY               0
#define IP_FRAG                     0
#endif

/* ---------- ICMP options ---------- */
#define ICMP_TTL                    255

/* ---------- DHCP options ---------- */
/* Define LWIP_DHCP to 1 if you want DHCP configuration of
   interfaces. */
#ifdef RT_LWIP_DHCP
#define LWIP_DHCP                   1
#else
#define LWIP_DHCP                   0
#endif

/* 1 if you want to do an ARP check on the offered address
   (recommended). */
#define DHCP_DOES_ARP_CHECK         (LWIP_DHCP)

/* ---------- AUTOIP options ------- */
#define LWIP_AUTOIP                 0
#define LWIP_DHCP_AUTOIP_COOP       (LWIP_DHCP && LWIP_AUTOIP)

/* ---------- UDP options ---------- */
#ifdef RT_LWIP_UDP
#define LWIP_UDP                    1
#else
#define LWIP_UDP                    0
#endif

#define LWIP_UDPLITE                0
#define UDP_TTL                     255
#define DEFAULT_UDP_RECVMBOX_SIZE   1

/* ---------- RAW options ---------- */
#ifdef RT_LWIP_RAW
#define LWIP_RAW                    1
#else
#define LWIP_RAW                    0
#endif

#define DEFAULT_RAW_RECVMBOX_SIZE   1
#define DEFAULT_ACCEPTMBOX_SIZE     10

/* ---------- Statistics options ---------- */
#ifdef RT_LWIP_STATS
#define LWIP_STATS                  1
#define LWIP_STATS_DISPLAY          1
#else
#define LWIP_STATS                  0
#endif

#if LWIP_STATS
#define LINK_STATS                  1
#define IP_STATS                    1
#define ICMP_STATS                  1
#define IGMP_STATS                  1
#define IPFRAG_STATS                1
#define UDP_STATS                   1
#define TCP_STATS                   1
#define MEM_STATS                   1
#define MEMP_STATS                  1
#define PBUF_STATS                  1
#define SYS_STATS                   1
#define MIB2_STATS                  1
#endif /* LWIP_STATS */

/* ---------- PPP options ---------- */
#ifdef RT_LWIP_PPP
#define PPP_SUPPORT                 1      /* Set > 0 for PPP */
#else
#define PPP_SUPPORT                 0      /* Set > 0 for PPP */
#endif

#if PPP_SUPPORT
#define NUM_PPP                     1      /* Max PPP sessions. */

/* Select modules to enable.  Ideally these would be set in the makefile but
 * we're limited by the command line length so you need to modify the settings
 * in this file.
 */
#ifdef RT_LWIP_PPPOE
#define PPPOE_SUPPORT               1
#else
#define PPPOE_SUPPORT               0
#endif

#ifdef RT_LWIP_PPPOS
#define PPPOS_SUPPORT               1
#else
#define PPPOS_SUPPORT               0
#endif

#define PAP_SUPPORT                 1      /* Set > 0 for PAP. */
#define CHAP_SUPPORT                1      /* Set > 0 for CHAP. */
#define MSCHAP_SUPPORT              0      /* Set > 0 for MSCHAP (NOT FUNCTIONAL!) */
#define CBCP_SUPPORT                0      /* Set > 0 for CBCP (NOT FUNCTIONAL!) */
#define CCP_SUPPORT                 0      /* Set > 0 for CCP (NOT FUNCTIONAL!) */
#define VJ_SUPPORT                  1      /* Set > 0 for VJ header compression. */
#define MD5_SUPPORT                 1      /* Set > 0 for MD5 (see also CHAP) */

#endif /* PPP_SUPPORT */

/**
 * LWIP_POSIX_SOCKETS_IO_NAMES==1: Enable POSIX-style sockets functions names.
 * Disable this option if you use a POSIX operating system that uses the same
 * names (read, write & close). (only used if you use sockets.c)
 */
#ifndef LWIP_POSIX_SOCKETS_IO_NAMES
#define LWIP_POSIX_SOCKETS_IO_NAMES     0
#endif

/**
 * LWIP_TCP_KEEPALIVE==1: Enable TCP_KEEPIDLE, TCP_KEEPINTVL and TCP_KEEPCNT
 * options processing. Note that TCP_KEEPIDLE and TCP_KEEPINTVL have to be set
 * in seconds. (does not require sockets.c, and will affect tcp.c)
 */
#ifndef LWIP_TCP_KEEPALIVE
#define LWIP_TCP_KEEPALIVE              1
#endif

/**
 * LWIP_NETIF_HOSTNAME==1: Support netif hostname
 */
#ifndef LWIP_NETIF_HOSTNAME
#define LWIP_NETIF_HOSTNAME             1
#endif

/**
 * LWIP_NETIF_API==1: Support netif api (in netifapi.c)
 */
#ifndef LWIP_NETIF_API
#define LWIP_NETIF_API                  1
#endif

/* MEMP_NUM_SYS_TIMEOUT: the number of simulateously active timeouts. */
#define MEMP_NUM_SYS_TIMEOUT       (LWIP_TCP + IP_REASSEMBLY + LWIP_ARP + (2*LWIP_DHCP) + LWIP_AUTOIP + LWIP_IGMP + LWIP_DNS + PPP_SUPPORT)

/*
 * LWIP_COMPAT_SOCKETS==1: Enable BSD-style sockets functions names.
 * (only used if you use sockets.c)
 */
#ifdef SAL_USING_POSIX
#define LWIP_COMPAT_SOCKETS             0
#else
#ifndef LWIP_COMPAT_SOCKETS
#define LWIP_COMPAT_SOCKETS             1
#endif
#endif

/**
 * LWIP_SO_SNDTIMEO==1: Enable send timeout for sockets/netconns and
 * SO_SNDTIMEO processing.
 */
#ifndef LWIP_SO_SNDTIMEO
#define LWIP_SO_SNDTIMEO                1
#endif

/**
 * LWIP_SO_RCVTIMEO==1: Enable receive timeout for sockets/netconns and
 * SO_RCVTIMEO processing.
 */
#ifndef LWIP_SO_RCVTIMEO
#define LWIP_SO_RCVTIMEO                1
#endif

/**
 * LWIP_SO_RCVBUF==1: Enable SO_RCVBUF processing.
 */
#ifndef LWIP_SO_RCVBUF
#define LWIP_SO_RCVBUF                  1
#endif

/**
 * If LWIP_SO_RCVBUF is used, this is the default value for recv_bufsize.
 */
#ifndef RECV_BUFSIZE_DEFAULT
#define RECV_BUFSIZE_DEFAULT            8192
#endif

/**
 * SO_REUSE==1: Enable SO_REUSEADDR option.
 */
#ifndef SO_REUSE
#define SO_REUSE                        0
#endif

#if RT_USING_LWIP_VER_NUM >= 0x20000 /* >= v2.0.0 */
#define LWIP_HOOK_IP4_ROUTE_SRC(dest, src)  lwip_ip4_route_src(dest, src)
#include "lwip/ip_addr.h"
struct netif *lwip_ip4_route_src(const ip4_addr_t *dest, const ip4_addr_t *src);
#endif /* RT_USING_LWIP_VER_NUM >= 0x20000 */

#endif /* __LWIPOPTS_H__ */
