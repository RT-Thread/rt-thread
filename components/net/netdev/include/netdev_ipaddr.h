/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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
#include <rtconfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definitions of bits in internet address integers.
 * On subnets, the decomposition of addresses to host and net parts
 * is done according to subnet mask, not the masks here.
 */
#define IN_CLASSA(i)        (((long)(i) & 0x80000000) == 0)
#define IN_CLASSA_NET       0xff000000
#define IN_CLASSA_NSHIFT    24
#define IN_CLASSA_HOST      0x00ffffff
#define IN_CLASSA_MAX       128

#define IN_CLASSB(i)        (((long)(i) & 0xc0000000) == 0x80000000)
#define IN_CLASSB_NET       0xffff0000
#define IN_CLASSB_NSHIFT    16
#define IN_CLASSB_HOST      0x0000ffff
#define IN_CLASSB_MAX       65536

#define IN_CLASSC(i)        (((long)(i) & 0xe0000000) == 0xc0000000)
#define IN_CLASSC_NET       0xffffff00
#define IN_CLASSC_NSHIFT    8
#define IN_CLASSC_HOST      0x000000ff

#define IN_CLASSD(i)        (((long)(i) & 0xf0000000) == 0xe0000000)
#define IN_MULTICAST(i)     IN_CLASSD(i)

#define IN_EXPERIMENTAL(i)  (((long)(i) & 0xe0000000) == 0xe0000000)
#define IN_BADCLASS(i)      (((long)(i) & 0xf0000000) == 0xf0000000)

#define IN_LOOPBACKNET      127         /* official! */

/* IP address types for use in ip_addr_t.type member */
enum netdev_ip_addr_type {
  /** IPv4 */
  IPADDR_TYPE_V4 =   0U,
  /** IPv6 */
  IPADDR_TYPE_V6 =   6U,
  /** IPv4+IPv6 ("dual-stack") */
  IPADDR_TYPE_ANY = 46U
};

#if NETDEV_IPV4
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

/** Copy IP address - faster than ip4_addr_set: no NULL check */
#define ip4_addr_copy(dest, src)            ((dest).addr = (src).addr)
#define ip4_addr_cmp(addr1, addr2)          ((addr1)->addr == (addr2)->addr)
/** Safely copy one IP address to another (src may be NULL) */
#define ip4_addr_set(dest, src)             ((dest)->addr = ((src) == NULL ? 0 : (src)->addr))
/** Set complete address to zero */
#define ip4_addr_set_zero(ipaddr)           ((ipaddr)->addr = 0)
/** Set address to IPADDR_ANY (no need for htonl()) */
#define ip4_addr_set_any(ipaddr)            ((ipaddr)->addr = IPADDR_ANY)
#define ip4_addr_isany_val(ipaddr)          ((ipaddr).addr == IPADDR_ANY)
#define ip4_addr_isany(ipaddr)              ((ipaddr) == NULL || ip4_addr_isany_val(*(ipaddr)))

in_addr_t netdev_ipaddr_addr(const char *cp);
int netdev_ip4addr_aton(const char *cp, ip4_addr_t *addr);
char *netdev_ip4addr_ntoa(const ip4_addr_t *addr);
char *netdev_ip4addr_ntoa_r(const ip4_addr_t *addr, char *buf, int buflen);
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
#ifdef NETDEV_IPV6_SCOPES
    uint8_t zone;
#endif /* NETDEV_IPV6_SCOPES */
} ip6_addr_t;

/** This macro can be used to initialize a variable of type struct in6_addr
    to the IPv6 wildcard address. */
#define IN6ADDR_ANY_INIT {{{0,0,0,0}}}
/** This macro can be used to initialize a variable of type struct in6_addr
    to the IPv6 loopback address. */
#define IN6ADDR_LOOPBACK_INIT {{{0,0,0,PP_HTONL(1)}}}

/** This variable is initialized by the system to contain the wildcard IPv6 address.
 */
extern const struct in6_addr in6addr_any;

#define ip6_addr_cmp(addr1, addr2)  (((addr1)->addr[0] == (addr2)->addr[0]) && \
                                    ((addr1)->addr[1] == (addr2)->addr[1]) && \
                                    ((addr1)->addr[2] == (addr2)->addr[2]) && \
                                    ((addr1)->addr[3] == (addr2)->addr[3]))
/** Copy IPv6 address - faster than ip6_addr_set: no NULL check */
#define ip6_addr_copy(dest, src) do{(dest).addr[0] = (src).addr[0]; \
                                    (dest).addr[1] = (src).addr[1]; \
                                    (dest).addr[2] = (src).addr[2]; \
                                    (dest).addr[3] = (src).addr[3];}while(0)
/** Safely copy one IPv6 address to another (src may be NULL) */
#define ip6_addr_set(dest, src)  do{(dest)->addr[0] = (src) == NULL ? 0 : (src)->addr[0]; \
                                    (dest)->addr[1] = (src) == NULL ? 0 : (src)->addr[1]; \
                                    (dest)->addr[2] = (src) == NULL ? 0 : (src)->addr[2]; \
                                    (dest)->addr[3] = (src) == NULL ? 0 : (src)->addr[3];}while(0)
/** Set complete address to zero */
#define ip6_addr_set_zero(ip6addr)  do{(ip6addr)->addr[0] = 0; \
                                       (ip6addr)->addr[1] = 0; \
                                       (ip6addr)->addr[2] = 0; \
                                       (ip6addr)->addr[3] = 0;}while(0)
/** Set address to ipv6 'any' (no need for lwip_htonl()) */
#define ip6_addr_set_any(ip6addr)   ip6_addr_set_zero(ip6addr)
#define ip6_addr_isany_val(ip6addr) (((ip6addr).addr[0] == 0) && \
                                     ((ip6addr).addr[1] == 0) && \
                                     ((ip6addr).addr[2] == 0) && \
                                     ((ip6addr).addr[3] == 0))
#define ip6_addr_isany(ip6addr)     (((ip6addr) == NULL) || ip6_addr_isany_val(*(ip6addr)))

int netdev_ip6addr_aton(const char *cp, ip6_addr_t *addr);
char *netdev_ip6addr_ntoa(const ip6_addr_t *addr);
char *netdev_ip6addr_ntoa_r(const ip6_addr_t *addr, char *buf, int buflen);
#endif /* NETIF_IPV6 */

#if NETDEV_IPV4 && NETDEV_IPV6
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

#define IP_SET_TYPE_VAL(ipaddr, iptype) do { (ipaddr).type = (iptype); }while(0)
#define IP_SET_TYPE(ipaddr, iptype)     do { if((ipaddr) != NULL) { IP_SET_TYPE_VAL(*(ipaddr), iptype); }}while(0)
#define IP_GET_TYPE(ipaddr)             ((ipaddr)->type)

#define IP_IS_V4_VAL(ipaddr)           (IP_GET_TYPE(&ipaddr) == IPADDR_TYPE_V4)
#define IP_IS_V6_VAL(ipaddr)           (IP_GET_TYPE(&ipaddr) == IPADDR_TYPE_V6)
#define IP_IS_V4(ipaddr)               (((ipaddr) == NULL) || IP_IS_V4_VAL(*(ipaddr)))
#define IP_IS_V6(ipaddr)               (((ipaddr) != NULL) && IP_IS_V6_VAL(*(ipaddr)))

/** Convert generic ip address to specific protocol version */
#define ip_2_ip6(ipaddr)               (&((ipaddr)->u_addr.ip6))
/** Convert generic ip address to specific protocol version */
#define ip_2_ip4(ipaddr)               (&((ipaddr)->u_addr.ip4))

#define ip_addr_copy(dest, src)     do{ IP_SET_TYPE_VAL(dest, IP_GET_TYPE(&src)); if(IP_IS_V6_VAL(src)){ \
                                        ip6_addr_copy(*ip_2_ip6(&(dest)), *ip_2_ip6(&(src))); }else{ \
                                        ip4_addr_copy(*ip_2_ip4(&(dest)), *ip_2_ip4(&(src))); }}while(0)
#define ip_addr_cmp(addr1, addr2)   ((IP_GET_TYPE(addr1) != IP_GET_TYPE(addr2)) ? 0 : (IP_IS_V6_VAL(*(addr1)) ? \
                                     ip6_addr_cmp(ip_2_ip6(addr1), ip_2_ip6(addr2)) : \
                                     ip4_addr_cmp(ip_2_ip4(addr1), ip_2_ip4(addr2))))
#define ip_addr_set(dest, src)      do{ IP_SET_TYPE(dest, IP_GET_TYPE(src)); if(IP_IS_V6(src)){ \
                                        ip6_addr_set(ip_2_ip6(dest), ip_2_ip6(src)); }else{ \
                                        ip4_addr_set(ip_2_ip4(dest), ip_2_ip4(src)); }}while(0)
#define ip_addr_set_zero(ipaddr)    do{ ip6_addr_set_zero(ip_2_ip6(ipaddr)); IP_SET_TYPE(ipaddr, 0); }while(0)
#define ip_addr_set_any(is_ipv6, ipaddr) do{ if(is_ipv6){ \
                                             ip6_addr_set_any(ip_2_ip6(ipaddr)); IP_SET_TYPE(ipaddr, IPADDR_TYPE_V6); }else{ \
                                             ip4_addr_set_any(ip_2_ip4(ipaddr)); IP_SET_TYPE(ipaddr, IPADDR_TYPE_V4); }}while(0)

#define ip_addr_isany_val(ipaddr)   ((IP_IS_V6_VAL(ipaddr)) ? \
                                      ip6_addr_isany_val(*ip_2_ip6(&(ipaddr))) : \
                                      ip4_addr_isany_val(*ip_2_ip4(&(ipaddr))))
#define ip_addr_isany(ipaddr)       ((IP_IS_V6(ipaddr)) ? \
                                      ip6_addr_isany(ip_2_ip6(ipaddr)) : \
                                      ip4_addr_isany(ip_2_ip4(ipaddr)))

/* directly map this to the lwip internal functions */
#define inet_addr(cp)                       netdev_ipaddr_addr(cp)
#define inet_aton(cp, addr)                 ((IP_IS_V6_VAL(*addr)) ? \
                                              netdev_ip6addr_aton(cp, ip_2_ip6(addr)) : \
                                              netdev_ip4addr_aton(cp, ip_2_ip4(addr)))
#define inet_ntoa(addr)                     ((IP_IS_V6_VAL(addr)) ? \
                                              netdev_ip6addr_ntoa(ip_2_ip6(&addr)) : \
                                              netdev_ip4addr_ntoa(ip_2_ip4(&addr)))
#define inet_ntoa_r(addr, buf, buflen)      ((IP_IS_V6_VAL(addr)) ? \
                                              netdev_ip6addr_ntoa_r(ip_2_ip6(&addr), buf, buflen) : \
                                              netdev_ip4addr_ntoa_r(ip_2_ip4(&addr), buf, buflen))
#elif NETDEV_IPV4  /* NETDEV_IPV4 */

typedef ip4_addr_t ip_addr_t;

#define IP_SET_TYPE_VAL(ipaddr, iptype)
#define IP_SET_TYPE(ipaddr, iptype)
#define IP_GET_TYPE(ipaddr)                 IPADDR_TYPE_V4

#define ip_addr_copy(dest, src)             ip4_addr_copy(dest, src)
#define ip_addr_cmp(addr1, addr2)           ip4_addr_cmp(addr1, addr2)
#define ip_addr_set(dest, src)              ip4_addr_set(dest, src)
#define ip_addr_set_zero(ipaddr)            ip4_addr_set_zero(ipaddr)
#define ip_addr_set_any(is_ipv6, ipaddr)    ip4_addr_set_any(ipaddr)
#define ip_addr_isany_val(ipaddr)           ip4_addr_isany_val(ipaddr)
#define ip_addr_isany(ipaddr)               ip4_addr_isany(ipaddr)

/* directly map this to the lwip internal functions */
#define inet_addr(cp)                       netdev_ipaddr_addr(cp)
#define inet_aton(cp, addr)                 netdev_ip4addr_aton(cp,(ip4_addr_t*)addr)
#define inet_ntoa(addr)                     netdev_ip4addr_ntoa((const ip4_addr_t*)&(addr))
#define inet_ntoa_r(addr, buf, buflen)      netdev_ip4addr_ntoa_r((const ip4_addr_t*)&(addr), buf, buflen)
#else /* NETDEV_IPV6 */

typedef ip6_addr_t ip_addr_t;

#define IP_SET_TYPE_VAL(ipaddr, iptype)
#define IP_SET_TYPE(ipaddr, iptype)
#define IP_GET_TYPE(ipaddr)                 IPADDR_TYPE_V6

#define ip_addr_copy(dest, src)             ip6_addr_copy(dest, src)
#define ip_addr_cmp(addr1, addr2)           ip6_addr_cmp(addr1, addr2)
#define ip_addr_set(dest, src)              ip6_addr_set(dest, src)
#define ip_addr_set_zero(ipaddr)            ip6_addr_set_zero(ipaddr)
#define ip_addr_set_any(is_ipv6, ipaddr)    ip6_addr_set_any(ipaddr)
#define ip_addr_isany_val(ipaddr)           ip6_addr_isany_val(ipaddr)
#define ip_addr_isany(ipaddr)               ip6_addr_isany(ipaddr)

/* directly map this to the lwip internal functions */
#define inet_aton(cp, addr)                 netdev_ip6addr_aton(cp, (ip6_addr_t*)addr)
#define inet_ntoa(addr)                     netdev_ip6addr_ntoa((const ip6_addr_t*)&(addr))
#define inet_ntoa_r(addr, buf, buflen)      netdev_ip6addr_ntoa_r((const ip6_addr_t*)&(addr), buf, buflen)
#endif /* NTDEV_IPV4 && NTDEV_IPV6 */


const char *netdev_inet_ntop(int af, const void *src, char *dst, int32_t size);
int netdev_inet_pton(int af, const char *src, void *dst);

#define inet_ntop(af, src, dst, size)       netdev_inet_ntop(af, src, dst, size)
#define inet_pton(af, src, dst)             netdev_inet_pton(af, src, dst)

#ifdef __cplusplus
}
#endif

#endif /* __NETDEV_IPADDR_H__ */
