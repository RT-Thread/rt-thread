/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-18     ChenYong     First version
 */

#ifndef __NETDEV_IPADDR_H__
#define __NETDEV_IPADDR_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Only supports the IPV4 protocol */
#ifndef NETDEV_IPV4
#define NETDEV_IPV4           1
#endif

#ifndef NETDEV_IPV6
#define NETDEV_IPV6           0
#endif

#ifdef NETDEV_IPV4
/** IPv4 only: set the IP address given as an u32_t */
#define ip4_addr_set_u32(dest_ipaddr, src_u32) ((dest_ipaddr)->addr = (src_u32))
/** IPv4 only: get the IP address as an u32_t */
#define ip4_addr_get_u32(src_ipaddr) ((src_ipaddr)->addr)

#define IP4ADDR_STRLEN_MAX  16
#endif /* NETIF_IPV4 */

/* These macros should be calculated by the preprocessor and are used
   with compile-time constants only (so that there is no little-endian
   overhead at runtime). */
#define PP_HTONS(x) ((((x) & 0x00ffUL) << 8) | (((x) & 0xff00UL) >> 8))
#define PP_NTOHS(x) PP_HTONS(x)
#define PP_HTONL(x) ((((x) & 0x000000ffUL) << 24) | \
                     (((x) & 0x0000ff00UL) <<  8) | \
                     (((x) & 0x00ff0000UL) >>  8) | \
                     (((x) & 0xff000000UL) >> 24))
#define PP_NTOHL(x) PP_HTONL(x)

#define htons(x) (uint16_t)PP_HTONS(x)
#define ntohs(x) (uint16_t)PP_NTOHS(x)
#define htonl(x) (uint32_t)PP_HTONL(x)
#define ntohl(x) (uint32_t)PP_NTOHL(x)

/* If your port already typedef's in_addr_t, define IN_ADDR_T_DEFINED
   to prevent this code from redefining it. */
#if !defined(in_addr_t) && !defined(IN_ADDR_T_DEFINED)
typedef uint32_t in_addr_t;
#endif

#if NETDEV_IPV4
struct in_addr
{
    in_addr_t s_addr;
};

typedef struct ip4_addr
{
    uint32_t addr;
} ip4_addr_t;

typedef ip4_addr_t ip_addr_t;
#endif /* NETIF_IPV4 */

#if NETDEV_IPV6
struct in6_addr
{
    union
    {
        uint32_t u32_addr[4];
        uint8_t u8_addr[16];
    } un;
#define s6_addr  un.u8_addr
};

typedef struct ip6_addr
{
    uint32_t addr[4];
} ip6_addr_t;

typedef ip6_addr ip_addr_t
#endif /* NETIF_IPV6 */

#if NETDEV_IPV4 && NETDEV_IPV6
/* IP address types for use in ip_addr_t.type member */
enum netdev_ip_addr_type
{
    /** IPv4 */
    IPADDR_TYPE_V4 = 0U,
    /** IPv6 */
    IPADDR_TYPE_V6 = 6U,
    /** IPv4+IPv6 ("dual-stack") */
    IPADDR_TYPE_ANY = 46U
};

/* A union struct for both IP version's addresses */
typedef struct _ip_addr
{
    union
    {
        ip6_addr_t ip6;
        ip4_addr_t ip4;
    } u_addr;
    /** @ref netdev_ip_addr_type */
    uint8_t type;
} ip_addr_t;
#endif /* NETIF_IPV4 && NETIF_IPV6 */

/** 255.255.255.255 */
#define IPADDR_NONE         ((uint32_t)0xffffffffUL)
/** 127.0.0.1 */
#define IPADDR_LOOPBACK     ((uint32_t)0x7f000001UL)
/** 0.0.0.0 */
#define IPADDR_ANY          ((uint32_t)0x00000000UL)
/** 255.255.255.255 */
#define IPADDR_BROADCAST    ((uint32_t)0xffffffffUL)

/** 255.255.255.255 */
#define INADDR_NONE         IPADDR_NONE
/** 127.0.0.1 */
#define INADDR_LOOPBACK     IPADDR_LOOPBACK
/** 0.0.0.0 */
#define INADDR_ANY          IPADDR_ANY
/** 255.255.255.255 */
#define INADDR_BROADCAST    IPADDR_BROADCAST

#define IPADDR_BROADCAST_STRING "255.255.255.255"

#ifdef NETDEV_IPV4

/** Copy IP address - faster than ip4_addr_set: no NULL check */
#define ip4_addr_copy(dest, src)            ((dest).addr = (src).addr)
#define ip4_addr_cmp(addr1, addr2)          ((addr1)->addr == (addr2)->addr)
/** Set complete address to zero */
#define ip4_addr_set_zero(ipaddr)           ((ipaddr)->addr = 0)
#define ip4_addr_isany_val(ipaddr)          ((ipaddr).addr == IPADDR_ANY)
#define ip4_addr_isany(ipaddr)              ((ipaddr) == NULL || ip4_addr_isany_val(*(ipaddr)))

#define ip_addr_copy(dest, src)             ip4_addr_copy(dest, src)
#define ip_addr_cmp(addr1, addr2)           ip4_addr_cmp(addr1, addr2)
#define ip_addr_set_zero(ipaddr)            ip4_addr_set_zero(ipaddr)
#define ip_addr_isany(ipaddr)               ip4_addr_isany(ipaddr)

in_addr_t netdev_ipaddr_addr(const char *cp);
int netdev_ip4addr_aton(const char *cp, ip4_addr_t *addr);
char *netdev_ip4addr_ntoa(const ip4_addr_t *addr);
char *netdev_ip4addr_ntoa_r(const ip4_addr_t *addr, char *buf, int buflen);

#define inet_addr(cp)                       netdev_ipaddr_addr(cp)
#define inet_aton(cp, addr)                 netdev_ip4addr_aton(cp,(ip4_addr_t*)addr)
#define inet_ntoa(addr)                     netdev_ip4addr_ntoa((const ip4_addr_t*)&(addr))
#define inet_ntoa_r(addr, buf, buflen)      netdev_ip4addr_ntoa_r((const ip4_addr_t*)&(addr), buf, buflen)

#endif /* NETDEV_IPV4 */

#ifdef __cplusplus
}
#endif

#endif /* __NETDEV_IPADDR_H__ */
