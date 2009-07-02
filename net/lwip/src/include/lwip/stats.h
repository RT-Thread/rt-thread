/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved. 
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
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#ifndef __LWIP_STATS_H__
#define __LWIP_STATS_H__

#include "lwip/opt.h"

#include "lwip/mem.h"
#include "lwip/memp.h"

#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_STATS

#ifndef LWIP_STATS_LARGE
#define LWIP_STATS_LARGE 0
#endif

#if LWIP_STATS_LARGE
#define STAT_COUNTER     u32_t
#define STAT_COUNTER_F   U32_F
#else
#define STAT_COUNTER     u16_t
#define STAT_COUNTER_F   U16_F
#endif 

struct stats_proto {
  STAT_COUNTER xmit;             /* Transmitted packets. */
  STAT_COUNTER rexmit;           /* Retransmitted packets. */
  STAT_COUNTER recv;             /* Received packets. */
  STAT_COUNTER fw;               /* Forwarded packets. */
  STAT_COUNTER drop;             /* Dropped packets. */
  STAT_COUNTER chkerr;           /* Checksum error. */
  STAT_COUNTER lenerr;           /* Invalid length error. */
  STAT_COUNTER memerr;           /* Out of memory error. */
  STAT_COUNTER rterr;            /* Routing error. */
  STAT_COUNTER proterr;          /* Protocol error. */
  STAT_COUNTER opterr;           /* Error in options. */
  STAT_COUNTER err;              /* Misc error. */
  STAT_COUNTER cachehit;
};

struct stats_igmp {
  STAT_COUNTER lenerr;           /* Invalid length error. */
  STAT_COUNTER chkerr;           /* Checksum error. */
  STAT_COUNTER v1_rxed;          /* */
  STAT_COUNTER join_sent;        /* */
  STAT_COUNTER leave_sent;       /* */
  STAT_COUNTER unicast_query;    /* */
  STAT_COUNTER report_sent;      /* */
  STAT_COUNTER report_rxed;      /* */
  STAT_COUNTER group_query_rxed; /* */
};

struct stats_mem {
  mem_size_t avail;
  mem_size_t used;
  mem_size_t max;
  mem_size_t err;
};

struct stats_syselem {
  STAT_COUNTER used;
  STAT_COUNTER max;
  STAT_COUNTER err;
};

struct stats_sys {
  struct stats_syselem sem;
  struct stats_syselem mbox;
};

struct stats_ {
#if LINK_STATS
  struct stats_proto link;
#endif
#if ETHARP_STATS
  struct stats_proto etharp;
#endif
#if IPFRAG_STATS
  struct stats_proto ip_frag;
#endif
#if IP_STATS
  struct stats_proto ip;
#endif
#if ICMP_STATS
  struct stats_proto icmp;
#endif
#if IGMP_STATS
  struct stats_igmp igmp;
#endif
#if UDP_STATS
  struct stats_proto udp;
#endif
#if TCP_STATS
  struct stats_proto tcp;
#endif
#if MEM_STATS
  struct stats_mem mem;
#endif
#if MEMP_STATS
  struct stats_mem memp[MEMP_MAX];
#endif
#if SYS_STATS
  struct stats_sys sys;
#endif
};

extern struct stats_ lwip_stats;

#define stats_init() /* Compatibility define, not init needed. */

#define STATS_INC(x) ++lwip_stats.x
#else
#define stats_init()
#define STATS_INC(x)
#endif /* LWIP_STATS */

#if TCP_STATS
#define TCP_STATS_INC(x) STATS_INC(x)
#else
#define TCP_STATS_INC(x)
#endif

#if UDP_STATS
#define UDP_STATS_INC(x) STATS_INC(x)
#else
#define UDP_STATS_INC(x)
#endif

#if ICMP_STATS
#define ICMP_STATS_INC(x) STATS_INC(x)
#else
#define ICMP_STATS_INC(x)
#endif

#if IGMP_STATS
#define IGMP_STATS_INC(x) STATS_INC(x)
#else
#define IGMP_STATS_INC(x)
#endif

#if IP_STATS
#define IP_STATS_INC(x) STATS_INC(x)
#else
#define IP_STATS_INC(x)
#endif

#if IPFRAG_STATS
#define IPFRAG_STATS_INC(x) STATS_INC(x)
#else
#define IPFRAG_STATS_INC(x)
#endif

#if ETHARP_STATS
#define ETHARP_STATS_INC(x) STATS_INC(x)
#else
#define ETHARP_STATS_INC(x)
#endif

#if LINK_STATS
#define LINK_STATS_INC(x) STATS_INC(x)
#else
#define LINK_STATS_INC(x)
#endif

/* Display of statistics */
#if LWIP_STATS_DISPLAY
void stats_display(void);
#else
#define stats_display()
#endif /* LWIP_STATS_DISPLAY */

#ifdef __cplusplus
}
#endif

#endif /* __LWIP_STATS_H__ */
