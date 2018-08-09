/**
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved. 
 *
 * Copyright (c) 2014 Nordic Semiconductor. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 */
 
#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#include "mem_manager.h"

#define NO_SYS                      1
#define NO_SYS_NO_TIMERS            0
#define MEM_LIBC_MALLOC             1
#define MEMP_MEM_MALLOC             1
#define MEM_ALIGNMENT               4
#define MEM_SIZE                    0
#define PBUF_POOL_SIZE              32
#define LWIP_ARP                    0
#define IP_REASS_MAX_PBUFS          0
#define IP_FRAG_USES_STATIC_BUF     0
#define MEMP_NUM_RAW_PCB            0
#define MEMP_NUM_UDP_PCB            2
#define MEMP_NUM_TCP_PCB            1
#define MEMP_NUM_TCP_PCB_LISTEN     1
#define MEMP_NUM_TCP_SEG            0
#define MEMP_NUM_FRAG_PBUF          0
#define MEMP_NUM_TCPIP_MSG_API      0
#define MEMP_NUM_TCPIP_MSG_INPKT    0
#define MEMP_NUM_SNMP_NODE          0
#define MEMP_NUM_SNMP_ROOTNODE      0
#define MEMP_NUM_SNMP_VARBIND       0
#define MEMP_NUM_SNMP_VALUE         0
#define IP_DEFAULT_TTL              255
#define IP_SOF_BROADCAST            0
#define IP_SOF_BROADCAST_RECV       0
#define LWIP_ICMP                   1
#define LWIP_BROADCAST_PING         0
#define LWIP_MULTICAST_PING         0
#define LWIP_RAW                    0
#define TCP_LISTEN_BACKLOG          1
#define LWIP_NETIF_STATUS_CALLBACK  1
#define LWIP_NETIF_LINK_CALLBACK    1
#define LWIP_NETIF_HWADDRHINT       1
#define LWIP_NETCONN                0
#define LWIP_SOCKET                 0
#define LWIP_STATS_DISPLAY          0
#define MEM_STATS                   0
#define SYS_STATS                   0
#define MEMP_STATS                  0
#define LINK_STATS                  0
#define ETHARP_TRUST_IP_MAC         0
#define ETH_PAD_SIZE                2
#define LWIP_CHKSUM_ALGORITHM       2
#define LWIP_CHECKSUM_ON_COPY               1
#define LWIP_ND6_MAX_MULTICAST_SOLICIT      1
#define LWIP_ND6_MAX_NEIGHBOR_ADVERTISEMENT 1
#define LWIP_ND6_RETRANS_TIMER              20000
#define LWIP_ND6_QUEUEING                   0
#define LWIP_ND6_NUM_ROUTERS                1
#define LWIP_ND6_DELAY_FIRST_PROBE_TIME     10000

#define LWIP_TCP_KEEPALIVE          1

#define LWIP_ARP                    0
#define ARP_TABLE_SIZE              0
#define IP_REASSEMBLY               0
#define IP_FRAG                     0
#define LWIP_TCP                    1
#define LWIP_IPV6                   1
#define LWIP_IPV4                   0
#define LWIP_ICMP6                  1
#define LWIP_IPV6_REASS             0
#define LWIP_ND6_TCP_REACHABILITY_HINTS 0
#define LWIP_IPV6_MLD               0
#define LWIP_STATS                  0
#define PPP_IPV6_SUPPORT            0
#define LWIP_PPP_API                0
#define PPP_SUPPORT                 0
#define LWIP_DNS                    1
#define LWIP_SUPPORT_CUSTOM_PBUF    1
#define LWIP_BTLE_6LOWPAN           1

#define TCP_TMR_INTERVAL            50
// Keepalive values, compliant with RFC 1122. Don't change this unless you know what you're doing
#define TCP_KEEPIDLE_DEFAULT        10000UL // Default KEEPALIVE timer in milliseconds
#define TCP_KEEPINTVL_DEFAULT       2000UL  // Default Time between KEEPALIVE probes in milliseconds
#define TCP_KEEPCNT_DEFAULT         9U      // Default Counter for KEEPALIVE probes
#define TCP_MSS                     896
#define TCP_WND                     (4 * TCP_MSS)
#define TCP_SND_BUF                 (4 * TCP_MSS)


#define SO_REUSE                    1

//#define mem_init(...)
//#define mem_free(p)                 nrf_free((p))
//#define mem_malloc(sz)              nrf_malloc((sz))
//#define mem_trim(p,sz)              nrf_realloc((p),(sz))

#define LWIP_DEBUG                  0

#define ETHARP_DEBUG                LWIP_DBG_OFF
#define NETIF_DEBUG                 LWIP_DBG_OFF
#define PBUF_DEBUG                  LWIP_DBG_OFF
#define API_LIB_DEBUG               LWIP_DBG_OFF
#define API_MSG_DEBUG               LWIP_DBG_OFF
#define SOCKETS_DEBUG               LWIP_DBG_OFF
#define ICMP_DEBUG                  LWIP_DBG_OFF
#define INET_DEBUG                  LWIP_DBG_OFF
#define IP_DEBUG                    LWIP_DBG_OFF
#define IP_REASS_DEBUG              LWIP_DBG_OFF
#define RAW_DEBUG                   LWIP_DBG_OFF
#define MEM_DEBUG                   LWIP_DBG_OFF
#define MEMP_DEBUG                  LWIP_DBG_OFF
#define SYS_DEBUG                   LWIP_DBG_OFF
#define TCP_DEBUG                   LWIP_DBG_OFF
#define TCP_INPUT_DEBUG             LWIP_DBG_OFF
#define TCP_OUTPUT_DEBUG            LWIP_DBG_OFF
#define TCP_RTO_DEBUG               LWIP_DBG_OFF
#define TCP_CWND_DEBUG              LWIP_DBG_OFF
#define TCP_WND_DEBUG               LWIP_DBG_OFF
#define TCP_FR_DEBUG                LWIP_DBG_OFF
#define TCP_QLEN_DEBUG              LWIP_DBG_OFF
#define TCP_RST_DEBUG               LWIP_DBG_OFF
#define UDP_DEBUG                   LWIP_DBG_OFF
#define TCPIP_DEBUG                 LWIP_DBG_OFF
#define PPP_DEBUG                   LWIP_DBG_OFF
#define SLIP_DEBUG                  LWIP_DBG_OFF
#define DHCP_DEBUG                  LWIP_DBG_OFF
#define SYS_LIGHTWEIGHT_PROT        0

#endif /* __LWIPOPTS_H__ */
