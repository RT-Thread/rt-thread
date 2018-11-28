/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-18     ChenYong     First version
 */
#ifndef SAL_IPADDR_H__
#define SAL_IPADDR_H__

#include "sal_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/** IPv4 only: set the IP address given as an u32_t */
#define ip4_addr_set_u32(dest_ipaddr, src_u32) ((dest_ipaddr)->addr = (src_u32))
/** IPv4 only: get the IP address as an u32_t */
#define ip4_addr_get_u32(src_ipaddr) ((src_ipaddr)->addr)

#define IP4ADDR_STRLEN_MAX  16

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

#define htons(x) (u16_t)PP_HTONS(x)
#define ntohs(x) (u16_t)PP_NTOHS(x)
#define htonl(x) (u32_t)PP_HTONL(x)
#define ntohl(x) (u32_t)PP_NTOHL(x)

/* If your port already typedef's in_addr_t, define IN_ADDR_T_DEFINED
   to prevent this code from redefining it. */
#if !defined(in_addr_t) && !defined(IN_ADDR_T_DEFINED)
typedef u32_t in_addr_t;
#endif

struct in_addr
{
    in_addr_t s_addr;
};

struct in6_addr
{
    union
    {
        u32_t u32_addr[4];
        u8_t u8_addr[16];
    } un;
#define s6_addr  un.u8_addr
};

enum sal_ip_addr_type
{
    /** IPv4 */
    IPADDR_TYPE_V4 = 0U,
    /** IPv6 */
    IPADDR_TYPE_V6 = 6U,
    /** IPv4+IPv6 ("dual-stack") */
    IPADDR_TYPE_ANY = 46U
};

typedef struct ip4_addr
{
    u32_t addr;
} ip4_addr_t;

typedef struct ip6_addr
{
    u32_t addr[4];
} ip6_addr_t;

typedef struct _ip_addr
{
    union
    {
        ip6_addr_t ip6;
        ip4_addr_t ip4;
    } u_addr;
    /** @ref sal_ip_addr_type */
    u8_t type;
} ip_addr_t;

/** 255.255.255.255 */
#define IPADDR_NONE         ((u32_t)0xffffffffUL)
/** 127.0.0.1 */
#define IPADDR_LOOPBACK     ((u32_t)0x7f000001UL)
/** 0.0.0.0 */
#define IPADDR_ANY          ((u32_t)0x00000000UL)
/** 255.255.255.255 */
#define IPADDR_BROADCAST    ((u32_t)0xffffffffUL)

/** 255.255.255.255 */
#define INADDR_NONE         IPADDR_NONE
/** 127.0.0.1 */
#define INADDR_LOOPBACK     IPADDR_LOOPBACK
/** 0.0.0.0 */
#define INADDR_ANY          IPADDR_ANY
/** 255.255.255.255 */
#define INADDR_BROADCAST    IPADDR_BROADCAST

#define IPADDR_BROADCAST_STRING "255.255.255.255"

in_addr_t sal_ipaddr_addr(const char *cp);
int sal_ip4addr_aton(const char *cp, ip4_addr_t *addr);
char *sal_ip4addr_ntoa(const ip4_addr_t *addr);
char *sal_ip4addr_ntoa_r(const ip4_addr_t *addr, char *buf, int buflen);

#define inet_addr(cp) sal_ipaddr_addr(cp)
#define inet_aton(cp,addr) sal_ip4addr_aton(cp,(ip4_addr_t*)addr)
#define inet_ntoa(addr) sal_ip4addr_ntoa((const ip4_addr_t*)&(addr))
#define inet_ntoa_r(addr, buf, buflen)  sal_ip4addr_ntoa_r((const ip4_addr_t*)&(addr), buf, buflen)

#ifdef __cplusplus
}
#endif

#endif /* SAL_IPADDR_H__ */
