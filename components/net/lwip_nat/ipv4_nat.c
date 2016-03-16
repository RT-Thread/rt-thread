/**
 * NAT - NAT implementation for lwIP supporting TCP/UDP and ICMP.
 * Copyright (c) 2009 Christian Walter, ?Embedded Solutions, Vienna 2009.
 *
 * Copyright (c) 2010 lwIP project ;-)
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
 */

/*
 * File      : ipv4_nat.c
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
 * 2015-01-26     Hichard      porting to RT-Thread
 * 2015-01-27     Bernard      code cleanup for lwIP in RT-Thread
 */

/*
 * TODOS:
 *  - we should decide if we want to use static tables for NAT or a linked
 *    list.
 *  - we should allocate icmp ping id if multiple clients are sending
 *    ping requests.
 *  - maybe we could hash the identifiers for TCP, ICMP and UDP and use
 *    a single table structure. This would reduce the code amount although
 *    it will cost performance.
 *  - NAT code must check for broadcast addresses and NOT forward
 *    them.
 *
 *  - netif_remove must notify NAT code when a NAT'ed interface is removed
 *  - allocate NAT entries from a new memp pool instead of the heap
 *  - let ttl be ticks, not seconds
 *
 * HOWTO USE:
 *
 * Shows how to create NAT between a PPP interface and an internal NIC.
 * In this case the network 213.129.231.168/29 is nat'ed when packets
 * are sent to the destination network 10.0.0.0/24 (untypical example -
 * most users will have the other way around).
 *
 * Step 1) Execute when network interfaces are ready.
 *
 * new_nat_entry.out_if = (struct netif *)&PPP_IF;
 * new_nat_entry.in_if = (struct netif *)&EMAC_if;
 * IP4_ADDR(&new_nat_entry.source_net, 213, 129, 231, 168);
 * IP4_ADDR(&new_nat_entry.source_netmask, 255, 255, 255, 248);
 * IP4_ADDR(&new_nat_entry.dest_net, 10, 0, 0, 0);
 * IP4_ADDR(&new_nat_entry.source_netmask, 255, 0, 0, 0);
 * ip_nat_add(&new_nat_entry);
 */

#include "ipv4_nat.h"
#include "lwip/opt.h"

#ifdef LWIP_USING_NAT

#include "lwip/ip.h"
#include "lwip/inet.h"
#include "lwip/netif.h"
#include "lwip/ip_addr.h"
#include "lwip/icmp.h"
#include "lwip/tcp_impl.h"
#include "lwip/udp.h"
#include "lwip/mem.h"
#include "lwip/sys.h"
#include "lwip/timers.h"
#include "netif/etharp.h"

#include <limits.h>
#include <string.h>

/** Define this to enable debug output of this module */
#ifndef LWIP_NAT_DEBUG
#define LWIP_NAT_DEBUG      LWIP_DBG_OFF
#endif

#define LWIP_NAT_TTL_INFINITE                    (INT_MAX)
#define LWIP_NAT_DEFAULT_TTL_SECONDS             (128)
#define LWIP_NAT_FORWARD_HEADER_SIZE_MIN         (sizeof(struct eth_hdr))

#define LWIP_NAT_DEFAULT_STATE_TABLES_ICMP       (4)
#define LWIP_NAT_DEFAULT_STATE_TABLES_TCP        (32)
#define LWIP_NAT_DEFAULT_STATE_TABLES_UDP        (32)

#define LWIP_NAT_DEFAULT_TCP_SOURCE_PORT         (40000)
#define LWIP_NAT_DEFAULT_UDP_SOURCE_PORT         (40000)

#define IPNAT_ENTRY_RESET(x) do { \
  (x)->ttl = 0; \
} while(0)

typedef struct ip_nat_conf
{
  struct ip_nat_conf *next;
  ip_nat_entry_t      entry;
} ip_nat_conf_t;

typedef struct ip_nat_entry_common
{
  s32_t           ttl; /* @todo: do we really need this to be signed?? */
  ip_addr_t       source;
  ip_addr_t       dest;
  ip_nat_conf_t   *cfg;
} ip_nat_entry_common_t;

typedef struct ip_nat_entries_icmp
{
  ip_nat_entry_common_t common;
  u16_t                 id;
  u16_t                 seqno;
} ip_nat_entries_icmp_t;

typedef struct ip_nat_entries_tcp
{
  ip_nat_entry_common_t common;
  u16_t                 nport;
  u16_t                 sport;
  u16_t                 dport;
} ip_nat_entries_tcp_t;

typedef struct ip_nat_entries_udp
{
  ip_nat_entry_common_t common;
  u16_t                 nport;
  u16_t                 sport;
  u16_t                 dport;
} ip_nat_entries_udp_t;

typedef union u_nat_entry
{
  ip_nat_entry_common_t *cmn;
  ip_nat_entries_tcp_t  *tcp;
  ip_nat_entries_icmp_t *icmp;
  ip_nat_entries_udp_t  *udp;
} nat_entry_t;

static ip_nat_conf_t *ip_nat_cfg = NULL;
static ip_nat_entries_icmp_t ip_nat_icmp_table[LWIP_NAT_DEFAULT_STATE_TABLES_ICMP];
static ip_nat_entries_tcp_t ip_nat_tcp_table[LWIP_NAT_DEFAULT_STATE_TABLES_TCP];
static ip_nat_entries_udp_t ip_nat_udp_table[LWIP_NAT_DEFAULT_STATE_TABLES_UDP];

/* ----------------------- Static functions (COMMON) --------------------*/
static void     ip_nat_chksum_adjust(u8_t *chksum, const u8_t *optr, s16_t olen, const u8_t *nptr, s16_t nlen);
static void     ip_nat_cmn_init(ip_nat_conf_t *nat_config, const struct ip_hdr *iphdr,
                                 ip_nat_entry_common_t *nat_entry);
static ip_nat_conf_t *ip_nat_shallnat(const struct ip_hdr *iphdr);
static void     ip_nat_reset_state(ip_nat_conf_t *cfg);

/* ----------------------- Static functions (DEBUG) ---------------------*/
#if defined(LWIP_DEBUG) && (LWIP_NAT_DEBUG & LWIP_DBG_ON)
static void     ip_nat_dbg_dump(const char *msg, const struct ip_hdr *iphdr);
static void     ip_nat_dbg_dump_ip(const ip_addr_t *addr);
static void     ip_nat_dbg_dump_icmp_nat_entry(const char *msg, const ip_nat_entries_icmp_t *nat_entry);
static void     ip_nat_dbg_dump_tcp_nat_entry(const char *msg, const ip_nat_entries_tcp_t *nat_entry);
static void     ip_nat_dbg_dump_udp_nat_entry(const char *msg, const ip_nat_entries_udp_t *nat_entry);
static void     ip_nat_dbg_dump_init(ip_nat_conf_t *ip_nat_cfg_new);
static void     ip_nat_dbg_dump_remove(ip_nat_conf_t *cur);
#else /* defined(LWIP_DEBUG) && (LWIP_NAT_DEBUG & LWIP_DBG_ON) */
#define ip_nat_dbg_dump(msg, iphdr)
#define ip_nat_dbg_dump_ip(addr)
#define ip_nat_dbg_dump_icmp_nat_entry(msg, nat_entry)
#define ip_nat_dbg_dump_tcp_nat_entry(msg, nat_entry)
#define ip_nat_dbg_dump_udp_nat_entry(msg, nat_entry)
#define ip_nat_dbg_dump_init(ip_nat_cfg_new)
#define ip_nat_dbg_dump_remove(cur)
#endif /* defined(LWIP_DEBUG) && (LWIP_NAT_DEBUG & LWIP_DBG_ON) */

/* ----------------------- Static functions (TCP) -----------------------*/
static ip_nat_entries_tcp_t *ip_nat_tcp_lookup_incoming(const struct ip_hdr *iphdr, const struct tcp_hdr *tcphdr);
static ip_nat_entries_tcp_t *ip_nat_tcp_lookup_outgoing(ip_nat_conf_t *nat_config,
                                                         const struct ip_hdr *iphdr, const struct tcp_hdr *tcphdr,
                                                         u8_t allocate);

/* ----------------------- Static functions (UDP) -----------------------*/
static ip_nat_entries_udp_t *ip_nat_udp_lookup_incoming(const struct ip_hdr *iphdr, const struct udp_hdr *udphdr);
static ip_nat_entries_udp_t *ip_nat_udp_lookup_outgoing(ip_nat_conf_t *nat_config,
                                                         const struct ip_hdr *iphdr, const struct udp_hdr *udphdr,
                                                         u8_t allocate);

/**
 * Timer callback function that calls ip_nat_tmr() and reschedules itself.
 *
 * @param arg unused argument
 */
static void
nat_timer(void *arg)
{
  LWIP_UNUSED_ARG(arg);
  LWIP_DEBUGF(TIMERS_DEBUG, ("tcpip: nat_timer()\n"));

  ip_nat_tmr();
  sys_timeout(LWIP_NAT_TMR_INTERVAL_SEC * 1000, nat_timer, NULL);
}

/** Initialize this module */
void
ip_nat_init(void)
{
  int i;
  extern void lwip_ip_input_set_hook(int (*hook)(struct pbuf *p, struct netif *inp));

  /* @todo: this can be omitted since we trust static variables
            to be initialized to zero */
  for (i = 0; i < LWIP_NAT_DEFAULT_STATE_TABLES_ICMP; i++) {
    IPNAT_ENTRY_RESET(&ip_nat_icmp_table[i].common);
  }
  for (i = 0; i < LWIP_NAT_DEFAULT_STATE_TABLES_TCP; i++) {
    IPNAT_ENTRY_RESET(&ip_nat_tcp_table[i].common);
  }
  for (i = 0; i < LWIP_NAT_DEFAULT_STATE_TABLES_UDP; i++) {
    IPNAT_ENTRY_RESET(&ip_nat_udp_table[i].common);
  }

  /* we must lock scheduler to protect following code */
  rt_enter_critical();

  /* add a lwip timer for NAT */
  sys_timeout(LWIP_NAT_TMR_INTERVAL_SEC * 1000, nat_timer, NULL);

  /* un-protect */
  rt_exit_critical();
}

/** Allocate a new ip_nat_conf_t item */
static ip_nat_conf_t*
ip_nat_alloc(void)
{
  ip_nat_conf_t *ret = (ip_nat_conf_t*)mem_malloc(sizeof(ip_nat_conf_t));
  return ret;
}

/** Free a removed ip_nat_conf_t item */
static void
ip_nat_free(ip_nat_conf_t *item)
{
  LWIP_ASSERT("item != NULL", item != NULL);
  mem_free(item);
}

/** Add a new NAT entry
 *
 * @param new_entry pointer to a structure used to initialize the entry
 * @return ERR_OK if succeeded
 */
err_t
ip_nat_add(const ip_nat_entry_t *new_entry)
{
  err_t err = ERR_VAL;
  ip_nat_conf_t *cur = ip_nat_cfg;
  ip_nat_conf_t *ip_nat_cfg_new = ip_nat_alloc();
  LWIP_ASSERT("new_entry != NULL", new_entry != NULL);

  if (ip_nat_cfg_new != NULL) {
    SMEMCPY(&ip_nat_cfg_new->entry, new_entry, sizeof(ip_nat_entry_t));
    ip_nat_cfg_new->next = NULL;

    ip_nat_dbg_dump_init(ip_nat_cfg_new);

    if (ip_nat_cfg == NULL) {
      ip_nat_cfg = ip_nat_cfg_new;
    } else {
      /* @todo: do we really need to enqueue the new entry at the end?? */
      while (cur->next != NULL) {
        cur = cur->next;
      }
      cur->next = ip_nat_cfg_new;
    }
    err = ERR_OK;
  } else {
    err = ERR_MEM;
  }
  return err;
}

/** Remove a NAT entry previously added by 'ip_nat_add()'.
 *
 * @param remove_entry describes the entry to remove
 */
void
ip_nat_remove(const ip_nat_entry_t *remove_entry)
{
  ip_nat_conf_t *cur = ip_nat_cfg;
  ip_nat_conf_t *next;
  ip_nat_conf_t *previous = NULL;

  while (cur != NULL) {
    /* Remove the NAT interfaces */
    if ((cur->entry.source_net.addr     == remove_entry->source_net.addr) &&
        (cur->entry.source_netmask.addr == remove_entry->source_netmask.addr) &&
        (cur->entry.dest_net.addr       == remove_entry->dest_net.addr) &&
        (cur->entry.dest_netmask.addr   == remove_entry->dest_netmask.addr) &&
        (cur->entry.out_if              == remove_entry->out_if) &&
        (cur->entry.in_if               == remove_entry->in_if))
    {
      ip_nat_dbg_dump_remove(cur);

      ip_nat_reset_state(cur);
      next = cur->next;
      if (cur == ip_nat_cfg) {
        ip_nat_cfg = next;
      } else {
        LWIP_ASSERT("NULL != previous", NULL != previous);
        previous->next = next;
      }
      /* free 'cur' or there will be a memory leak */
      ip_nat_free(cur);
      return;
    } else {
      previous = cur;
      cur = cur->next;
    }
  }
}

/** Reset a NAT configured entry to be reused.
 * Effectively calls IPNAT_ENTRY_RESET() on 'cfg'.
 *
 * @param cfg NAT entry to reset
 */
static void
ip_nat_reset_state(ip_nat_conf_t *cfg)
{
  int i;

  /* @todo: optimize this!!!
     why do we search for it anyway, if we have the pointer??? */
  for (i = 0; i < LWIP_NAT_DEFAULT_STATE_TABLES_ICMP; i++) {
    if(ip_nat_icmp_table[i].common.cfg == cfg) {
      IPNAT_ENTRY_RESET(&ip_nat_icmp_table[i].common);
    }
  }
  for (i = 0; i < LWIP_NAT_DEFAULT_STATE_TABLES_TCP; i++) {
    if(ip_nat_tcp_table[i].common.cfg == cfg) {
      IPNAT_ENTRY_RESET(&ip_nat_tcp_table[i].common);
    }
  }
  for (i = 0; i < LWIP_NAT_DEFAULT_STATE_TABLES_UDP; i++) {
    if(ip_nat_udp_table[i].common.cfg == cfg) {
      IPNAT_ENTRY_RESET(&ip_nat_udp_table[i].common);
    }
  }
}

/** Check if this packet should be routed or should be translated
 *
 * @param iphdr the IP header to check
 * @return - a NAT entry if the packet shall be translated,
 *         - NULL if the packet shall be routed normally
 */
static ip_nat_conf_t *
ip_nat_shallnat(const struct ip_hdr *iphdr)
{
  ip_nat_conf_t *nat_config = ip_nat_cfg;

  for (nat_config = ip_nat_cfg; nat_config != NULL; nat_config = nat_config->next) {
      if (ip_addr_netcmp(&(iphdr->dest), &(nat_config->entry.dest_net),
                       &(nat_config->entry.dest_netmask)) ||
      ip_addr_netcmp(&(iphdr->src), &(nat_config->entry.source_net),
                     &(nat_config->entry.source_netmask))) {
        break;
    }
  }

  return nat_config;
}

/** Check if the IP header can be hidden and if the remaining packet
 * is long enough. p->payload is reset to the IP header on return.
 *
 * @param p received packet, p->payload pointing to IP header
 * @param min_size minimum p->tot_len after hiding IP header
 * @return a pointer to the next header (after IP header),
 *         NULL if hiding IP header fails or the packet is too short
 */
static void*
ip_nat_check_header(struct pbuf *p, u16_t min_size)
{
  void *ret = NULL;
  struct ip_hdr  *iphdr = (struct ip_hdr*)p->payload;
  s16_t iphdr_len = IPH_HL(iphdr) * 4;

  if(!pbuf_header(p, -iphdr_len)) {
    if(p->tot_len >= min_size) {
      ret = p->payload;
    }
    /* Restore pbuf payload pointer from previous header check. */
    pbuf_header(p, iphdr_len);
  }
  return ret;
}

/** Input processing: check if a received packet belongs to a NAT entry
 * and if so, translated it and send it on.
 *
 * @param p received packet
 * @return 1 if the packet has been consumed (it was a NAT packet),
 *         0 if the packet has not been consumed (no NAT packet)
 */
u8_t
ip_nat_input(struct pbuf *p)
{
  struct ip_hdr        *iphdr = (struct ip_hdr*)p->payload;
  struct tcp_hdr       *tcphdr;
  struct udp_hdr       *udphdr;
  struct icmp_echo_hdr *icmphdr;
  nat_entry_t           nat_entry;
  err_t                 err;
  u8_t                  consumed = 0;
  int                   i;
  struct pbuf          *q = NULL;

  nat_entry.cmn = NULL;
  ip_nat_dbg_dump("ip_nat_in: checking nat for", iphdr);

  switch (IPH_PROTO(iphdr)) {
    case IP_PROTO_TCP:
      tcphdr = (struct tcp_hdr*)ip_nat_check_header(p, sizeof(struct tcp_hdr));
      if (tcphdr == NULL) {
        LWIP_DEBUGF(LWIP_NAT_DEBUG, ("ip_nat_input: short tcp packet (%" U16_F " bytes) discarded\n", p->tot_len));
      } else {
        nat_entry.tcp = ip_nat_tcp_lookup_incoming(iphdr, tcphdr);
        if (nat_entry.tcp != NULL) {
          /* Refresh TCP entry */
          nat_entry.tcp->common.ttl = LWIP_NAT_DEFAULT_TTL_SECONDS;
          tcphdr->dest = nat_entry.tcp->sport;
          /* Adjust TCP checksum for changed destination port */
          ip_nat_chksum_adjust((u8_t *)&(tcphdr->chksum),
            (u8_t *)&(nat_entry.tcp->nport), 2, (u8_t *)&(tcphdr->dest), 2);
          /* Adjust TCP checksum for changing dest IP address */
          ip_nat_chksum_adjust((u8_t *)&(tcphdr->chksum),
            (u8_t *)&(nat_entry.cmn->cfg->entry.out_if->ip_addr.addr), 4,
            (u8_t *)&(nat_entry.cmn->source.addr), 4);

          consumed = 1;
        }
      }
      break;

    case IP_PROTO_UDP:
      udphdr = (struct udp_hdr *)ip_nat_check_header(p, sizeof(struct udp_hdr));
      if (udphdr == NULL) {
        LWIP_DEBUGF(LWIP_NAT_DEBUG,
          ("ip_nat_input: short udp packet (%" U16_F " bytes) discarded\n",
          p->tot_len));
      } else {
        nat_entry.udp = ip_nat_udp_lookup_incoming(iphdr, udphdr);
        if (nat_entry.udp != NULL) {
          /* Refresh UDP entry */
          nat_entry.udp->common.ttl = LWIP_NAT_DEFAULT_TTL_SECONDS;
          udphdr->dest = nat_entry.udp->sport;
          /* Adjust UDP checksum for changed destination port */
          ip_nat_chksum_adjust((u8_t *)&(udphdr->chksum),
            (u8_t *)&(nat_entry.udp->nport), 2, (u8_t *)&(udphdr->dest), 2);
          /* Adjust UDP checksum for changing dest IP address */
          ip_nat_chksum_adjust((u8_t *)&(udphdr->chksum),
            (u8_t *)&(nat_entry.cmn->cfg->entry.out_if->ip_addr.addr), 4,
            (u8_t *)&(nat_entry.cmn->source.addr), 4);

          consumed = 1;
        }
      }
      break;

    case IP_PROTO_ICMP:
      icmphdr = (struct icmp_echo_hdr *)ip_nat_check_header(p, sizeof(struct icmp_echo_hdr));
      if (icmphdr == NULL) {
        LWIP_DEBUGF(LWIP_NAT_DEBUG,
          ("ip_nat_out: short icmp echo reply packet (%" U16_F " bytes) discarded\n",
          p->tot_len));
      } else {
        if (ICMP_ER == ICMPH_TYPE(icmphdr)) {
          for (i = 0; i < LWIP_NAT_DEFAULT_STATE_TABLES_ICMP; i++) {
            nat_entry.icmp = &ip_nat_icmp_table[i];
            if ((nat_entry.icmp->common.ttl) &&
                (iphdr->src.addr == nat_entry.icmp->common.dest.addr) &&
                (nat_entry.icmp->id == icmphdr->id) &&
                (nat_entry.icmp->seqno == icmphdr->seqno)) {
              ip_nat_dbg_dump_icmp_nat_entry("found existing nat entry: ", nat_entry.icmp);
              consumed = 1;
              IPNAT_ENTRY_RESET(nat_entry.cmn);
              break;
            }
          }
        }
      }
      break;

    default:
      break;
  }

  if(consumed) {
    /* packet consumed, send it out on in_if */
    struct netif *in_if;

    /* check if the pbuf has room for link headers */
    if (pbuf_header(p, PBUF_LINK_HLEN)) {
      /* pbuf has no room for link headers, allocate an extra pbuf */
      q = pbuf_alloc(PBUF_LINK, 0, PBUF_RAM);
      if (q == NULL) {
        LWIP_DEBUGF(LWIP_NAT_DEBUG, ("ip_nat_input: no pbuf for outgoing header\n"));
        // rt_kprintf("ip_nat_input: no pbuf for outgoing header\n");
        /* @todo: stats? */
        pbuf_free(p);
        p = NULL;
        return 1;
      } else {
        pbuf_cat(q, p);
      }
    } else {
      /* restore p->payload to IP header */
      if (pbuf_header(p, -PBUF_LINK_HLEN)) {
        LWIP_DEBUGF(LWIP_NAT_DEBUG, ("ip_nat_input: restoring header failed\n"));
        // rt_kprintf("ip_nat_input: restoring header failed\n");
        /* @todo: stats? */
        pbuf_free(p);
        p = NULL;
        return 1;
      }
      else q = p;
    }
    /* if we come here, q is the pbuf to send (either points to p or to a chain) */
    in_if = nat_entry.cmn->cfg->entry.in_if;
    iphdr->dest.addr = nat_entry.cmn->source.addr;
    ip_nat_chksum_adjust((u8_t *) & IPH_CHKSUM(iphdr),
      (u8_t *) & (nat_entry.cmn->cfg->entry.out_if->ip_addr.addr), 4,
      (u8_t *) & (iphdr->dest.addr), 4);

    ip_nat_dbg_dump("ip_nat_input: packet back to source after nat: ", iphdr);
    LWIP_DEBUGF(LWIP_NAT_DEBUG, ("ip_nat_input: sending packet on interface ("));
    ip_nat_dbg_dump_ip(&(in_if->ip_addr));
    LWIP_DEBUGF(LWIP_NAT_DEBUG, (")\n"));

    err = in_if->output(in_if, q, (ip_addr_t *)&(iphdr->dest));
    if(err != ERR_OK) {
      LWIP_DEBUGF(LWIP_NAT_DEBUG,
        ("ip_nat_input: failed to send rewritten packet. link layer returned %d\n",
        err));
      // rt_kprintf("ip_nat_input: failed to send rewritten packet. link layer returned %d\n", err);
    }
    /* now that q (and/or p) is sent (or not), give up the reference to it
       this frees the input pbuf (p) as we have consumed it. */
    pbuf_free(q);
  }
  return consumed;
}

/** Check if one NAT entry timed out */
static void
ip_nat_check_timeout(ip_nat_entry_common_t *nat_entry)
{
  if(nat_entry->ttl > 0) {
    if(nat_entry->ttl != LWIP_NAT_TTL_INFINITE) {
      /* this is not a 'no-timeout' entry */
      if(nat_entry->ttl > LWIP_NAT_TMR_INTERVAL_SEC) {
        nat_entry->ttl -= LWIP_NAT_TMR_INTERVAL_SEC;
      } else {
        nat_entry->ttl = 0;
      }
    }
  }
}

/** The NAT timer function, to be called at an interval of
 * LWIP_NAT_TMR_INTERVAL_SEC seconds.
 */
void
ip_nat_tmr(void)
{
  int i;

  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("ip_nat_tmr: removing old entries\n"));

  for(i = 0; i < LWIP_NAT_DEFAULT_STATE_TABLES_ICMP; i++) {
    ip_nat_check_timeout((ip_nat_entry_common_t *) & ip_nat_icmp_table[i]);
  }
  for(i = 0; i < LWIP_NAT_DEFAULT_STATE_TABLES_TCP; i++) {
    ip_nat_check_timeout((ip_nat_entry_common_t *) & ip_nat_tcp_table[i]);
  }
  for(i = 0; i < LWIP_NAT_DEFAULT_STATE_TABLES_UDP; i++) {
    ip_nat_check_timeout((ip_nat_entry_common_t *) & ip_nat_udp_table[i]);
  }
}

/** Check if we want to perform NAT with this packet. If so, send it out on
 * the correct interface.
 *
 * @param p the packet to test/send
 * @return 1: the packet has been sent using NAT,
 *         0: the packet did not belong to a NAT entry
 */
u8_t
ip_nat_out(struct pbuf *p)
{
  u8_t                  sent = 0;
  err_t                 err;
  struct ip_hdr        *iphdr = p->payload;
  struct icmp_echo_hdr *icmphdr;
  struct tcp_hdr       *tcphdr;
  struct udp_hdr       *udphdr;
  ip_nat_conf_t        *nat_config;
  nat_entry_t           nat_entry;
  int             i;

  nat_entry.cmn = NULL;

  ip_nat_dbg_dump("ip_nat_out: checking nat for", iphdr);

  /* Check if this packet should be routed or should be translated */
  nat_config = ip_nat_shallnat(iphdr);
  if (nat_config != NULL ) {
    if (nat_config->entry.out_if == NULL) {
      LWIP_DEBUGF(LWIP_NAT_DEBUG, ("ip_nat_out: no external interface for nat table entry\n"));
    } else {
      switch (IPH_PROTO(iphdr))
      {
      case IP_PROTO_TCP:
        tcphdr = (struct tcp_hdr *)ip_nat_check_header(p, sizeof(struct tcp_hdr));
        if (tcphdr == NULL) {
          LWIP_DEBUGF(LWIP_NAT_DEBUG,
            ("ip_nat_out: short tcp packet (%" U16_F " bytes) discarded\n", p->tot_len));
        } else {
          nat_entry.tcp = ip_nat_tcp_lookup_outgoing(nat_config, iphdr, tcphdr, 1);
          if (nat_entry.tcp != NULL) {
            /* Adjust TCP checksum for changing source port */
            tcphdr->src = nat_entry.tcp->nport;
            ip_nat_chksum_adjust((u8_t *)&(tcphdr->chksum),
              (u8_t *)&(nat_entry.tcp->sport), 2, (u8_t *)&(tcphdr->src), 2);
            /* Adjust TCP checksum for changing source IP address */
            ip_nat_chksum_adjust((u8_t *)&(tcphdr->chksum),
              (u8_t *)&(nat_entry.cmn->source.addr), 4,
              (u8_t *)&(nat_entry.cmn->cfg->entry.out_if->ip_addr.addr), 4);
          }
        }
        break;

      case IP_PROTO_UDP:
        udphdr = (struct udp_hdr *)ip_nat_check_header(p, sizeof(struct udp_hdr));
        if (udphdr == NULL) {
          LWIP_DEBUGF(LWIP_NAT_DEBUG,
            ("ip_nat_out: short udp packet (%" U16_F " bytes) discarded\n", p->tot_len));
        } else {
          nat_entry.udp = ip_nat_udp_lookup_outgoing(nat_config, iphdr, udphdr, 1);
          if (nat_entry.udp != NULL) {
            /* Adjust UDP checksum for changing source port */
            udphdr->src = nat_entry.udp->nport;
            ip_nat_chksum_adjust((u8_t *)&(udphdr->chksum),
              (u8_t *)&(nat_entry.udp->sport), 2, (u8_t *) & (udphdr->src), 2);
            /* Adjust UDP checksum for changing source IP address */
            ip_nat_chksum_adjust((u8_t *)&(udphdr->chksum),
              (u8_t *)&(nat_entry.cmn->source.addr), 4,
              (u8_t *)&(nat_entry.cmn->cfg->entry.out_if->ip_addr.addr), 4);
          }
        }
        break;

      case IP_PROTO_ICMP:
        icmphdr = (struct icmp_echo_hdr *)ip_nat_check_header(p, sizeof(struct icmp_echo_hdr));
        if(icmphdr == NULL) {
          LWIP_DEBUGF(LWIP_NAT_DEBUG,
            ("ip_nat_out: short icmp echo packet (%" U16_F " bytes) discarded\n", p->tot_len));
        } else {
          if (ICMPH_TYPE(icmphdr) == ICMP_ECHO) {
            for (i = 0; i < LWIP_NAT_DEFAULT_STATE_TABLES_ICMP; i++) {
              if (!ip_nat_icmp_table[i].common.ttl) {
                nat_entry.icmp = &ip_nat_icmp_table[i];
                ip_nat_cmn_init(nat_config, iphdr, nat_entry.cmn);
                nat_entry.icmp->id = icmphdr->id;
                nat_entry.icmp->seqno = icmphdr->seqno;
                ip_nat_dbg_dump_icmp_nat_entry(" ip_nat_out: created new NAT entry ", nat_entry.icmp);
                break;
              }
            }
            if (NULL == nat_entry.icmp)
            {
              LWIP_DEBUGF(LWIP_NAT_DEBUG, ("ip_nat_out: no more NAT entries for ICMP available\n"));
            }
          }
        }
        break;
      default:
        break;
      }

      if (nat_entry.cmn != NULL) {
        struct netif *out_if = nat_entry.cmn->cfg->entry.out_if;
        /* Exchange the IP source address with the address of the interface
        * where the packet will be sent.
        */
        /* @todo: check nat_config->entry.out_if agains nat_entry.cmn->cfg->entry.out_if */
        iphdr->src.addr = nat_config->entry.out_if->ip_addr.addr;
        ip_nat_chksum_adjust((u8_t *) & IPH_CHKSUM(iphdr),
          (u8_t *) & (nat_entry.cmn->source.addr), 4, (u8_t *) & iphdr->src.addr, 4);

        ip_nat_dbg_dump("ip_nat_out: rewritten packet", iphdr);
        LWIP_DEBUGF(LWIP_NAT_DEBUG, ("ip_nat_out: sending packet on interface ("));
        ip_nat_dbg_dump_ip(&(out_if->ip_addr));
        LWIP_DEBUGF(LWIP_NAT_DEBUG, (")\n"));

        err = out_if->output(out_if, p, (ip_addr_t *)&(iphdr->dest));
        if (err != ERR_OK) {
          LWIP_DEBUGF(LWIP_NAT_DEBUG,
            ("ip_nat_out: failed to send rewritten packet. link layer returned %d\n", err));
          // rt_kprintf("ip_nat_out: failed to send rewritten packet. link layer returned %d\n", err);
        } else {
          sent = 1;
        }
      }
    }
  }

  return sent;
}

/** Initialize common parts of a NAT entry
 *
 * @param nat_config NAT config entry
 * @param iphdr IP header from which to initialize the entry
 * @param nat_entry entry to initialize
 */
static void
ip_nat_cmn_init(ip_nat_conf_t *nat_config, const struct ip_hdr *iphdr, ip_nat_entry_common_t *nat_entry)
{
  LWIP_ASSERT("NULL != nat_entry", NULL != nat_entry);
  LWIP_ASSERT("NULL != nat_config", NULL != nat_config);
  LWIP_ASSERT("NULL != iphdr", NULL != iphdr);
  nat_entry->cfg = nat_config;
  nat_entry->dest = *((ip_addr_t *)&iphdr->dest);
  nat_entry->source = *((ip_addr_t *)&iphdr->src);
  nat_entry->ttl = LWIP_NAT_DEFAULT_TTL_SECONDS;
}

/**
 * This function checks for incoming packets if we already have a NAT entry.
 * If yes a pointer to the NAT entry is returned. Otherwise NULL.
 *
 * @param nat_config NAT configuration.
 * @param iphdr The IP header.
 * @param udphdr The UDP header.
 * @return A pointer to an existing NAT entry or
 *         NULL if none is found.
 */
static ip_nat_entries_udp_t *
ip_nat_udp_lookup_incoming(const struct ip_hdr *iphdr, const struct udp_hdr *udphdr)
{
  int i;
  ip_nat_entries_udp_t *nat_entry = NULL;

  for (i = 0; i < LWIP_NAT_DEFAULT_STATE_TABLES_UDP; i++) {
    if (ip_nat_udp_table[i].common.ttl) {
      if ((iphdr->src.addr == ip_nat_udp_table[i].common.dest.addr) &&
          (udphdr->src == ip_nat_udp_table[i].dport) &&
          (udphdr->dest == ip_nat_udp_table[i].nport)) {
        nat_entry = &ip_nat_udp_table[i];
        ip_nat_dbg_dump_udp_nat_entry("ip_nat_udp_lookup_incoming: found existing nat entry: ",
                                      nat_entry);
        break;
      }
    }
  }
  return nat_entry;
}

/**
 * This function checks if we already have a NAT entry for this UDP connection.
 * If yes the a pointer to this NAT entry is returned.
 *
 * @param iphdr The IP header.
 * @param udphdr The UDP header.
 * @param allocate If no existing NAT entry is found and this flag is true
 *        a NAT entry is allocated.
 */
static ip_nat_entries_udp_t *
ip_nat_udp_lookup_outgoing(ip_nat_conf_t *nat_config, const struct ip_hdr *iphdr,
                           const struct udp_hdr *udphdr, u8_t allocate)
{
  int i;
  nat_entry_t nat_entry;
  int last_free = -1;

  nat_entry.cmn = NULL;
  for (i = 0; i < LWIP_NAT_DEFAULT_STATE_TABLES_UDP; i++) {
    if (ip_nat_udp_table[i].common.ttl) {
      if ((iphdr->src.addr == ip_nat_udp_table[i].common.source.addr) &&
          (iphdr->dest.addr == ip_nat_udp_table[i].common.dest.addr) &&
          (udphdr->src == ip_nat_udp_table[i].sport) &&
          (udphdr->dest == ip_nat_udp_table[i].dport)) {
        nat_entry.udp = &ip_nat_udp_table[i];

        ip_nat_dbg_dump_udp_nat_entry("ip_nat_udp_lookup_outgoing: found existing nat entry: ",
                                      nat_entry.udp);
        break;
      }
    } else {
        last_free = i;
    }
  }
  if (nat_entry.cmn == NULL) {
    if (allocate) {
      if (last_free != -1) {
        nat_entry.udp = &ip_nat_udp_table[last_free];
        nat_entry.udp->nport = htons((u16_t) (LWIP_NAT_DEFAULT_UDP_SOURCE_PORT + i));
        nat_entry.udp->sport = udphdr->src;
        nat_entry.udp->dport = udphdr->dest;
        ip_nat_cmn_init(nat_config, iphdr, nat_entry.cmn);

        ip_nat_dbg_dump_udp_nat_entry("ip_nat_udp_lookup_outgoing: created new nat entry: ",
                                      nat_entry.udp);
      } else {
        LWIP_DEBUGF(LWIP_NAT_DEBUG, ("ip_nat_udp_lookup_outgoing: no more NAT entries available\n"));
        // rt_kprintf("ip_nat_udp_lookup_outgoing: no more NAT entries available\n");
      }
    }
  }
  return nat_entry.udp;
}

/**
 * This function checks for incoming packets if we already have a NAT entry.
 * If yes a pointer to the NAT entry is returned. Otherwise NULL.
 *
 * @param nat_config NAT configuration.
 * @param iphdr The IP header.
 * @param tcphdr The TCP header.
 * @return A pointer to an existing NAT entry or NULL if none is found.
 */
static ip_nat_entries_tcp_t *
ip_nat_tcp_lookup_incoming(const struct ip_hdr *iphdr, const struct tcp_hdr *tcphdr)
{
  int i;
  ip_nat_entries_tcp_t *nat_entry = NULL;

  for (i = 0; i < LWIP_NAT_DEFAULT_STATE_TABLES_TCP; i++) {
    if (ip_nat_tcp_table[i].common.ttl) {
      if ((iphdr->src.addr == ip_nat_tcp_table[i].common.dest.addr) &&
          (tcphdr->src == ip_nat_tcp_table[i].dport) &&
          (tcphdr->dest == ip_nat_tcp_table[i].nport)) {
        nat_entry = &ip_nat_tcp_table[i];

        ip_nat_dbg_dump_tcp_nat_entry("ip_nat_tcp_lookup_incoming: found existing nat entry: ",
                                      nat_entry);
        break;
      }
    }
  }
  return nat_entry;
}

/**
 * This function checks if we already have a NAT entry for this TCP connection.
 * If yes the a pointer to this NAT entry is returned.
 *
 * @param iphdr The IP header.
 * @param tcphdr The TCP header.
 * @param allocate If no existing NAT entry is found and this flag is true
 *   a NAT entry is allocated.
 */
static ip_nat_entries_tcp_t *
ip_nat_tcp_lookup_outgoing(ip_nat_conf_t *nat_config, const struct ip_hdr *iphdr,
                           const struct tcp_hdr *tcphdr, u8_t allocate)
{
  int i;
  nat_entry_t nat_entry;
  int last_free = -1;

  nat_entry.cmn = NULL;
  for (i = 0; i < LWIP_NAT_DEFAULT_STATE_TABLES_TCP; i++) {
    if (ip_nat_tcp_table[i].common.ttl) {
      if ((iphdr->src.addr == ip_nat_tcp_table[i].common.source.addr) &&
          (iphdr->dest.addr == ip_nat_tcp_table[i].common.dest.addr) &&
          (tcphdr->src == ip_nat_tcp_table[i].sport) &&
          (tcphdr->dest == ip_nat_tcp_table[i].dport)) {
        nat_entry.tcp = &ip_nat_tcp_table[i];

        ip_nat_dbg_dump_tcp_nat_entry("ip_nat_tcp_lookup_outgoing: found existing nat entry: ",
                                      nat_entry.tcp);
        break;
      }
    } else {
        last_free = i;
    }
  }
  if (nat_entry.cmn == NULL) {
    if (allocate) {
      if (last_free != -1) {
        nat_entry.tcp = &ip_nat_tcp_table[last_free];
        nat_entry.tcp->nport = htons((u16_t) (LWIP_NAT_DEFAULT_TCP_SOURCE_PORT + i));
        nat_entry.tcp->sport = tcphdr->src;
        nat_entry.tcp->dport = tcphdr->dest;
        ip_nat_cmn_init(nat_config, iphdr, nat_entry.cmn);

        ip_nat_dbg_dump_tcp_nat_entry("ip_nat_tcp_lookup_outgoing: created new nat entry: ",
                                      nat_entry.tcp);
      } else {
        LWIP_DEBUGF(LWIP_NAT_DEBUG, ("ip_nat_udp_lookup_outgoing: no more NAT entries available\n"));
        // rt_kprintf("ip_nat_udp_lookup_outgoing: no more NAT entries available\n");
      }
    }
  }
  return nat_entry.tcp;
}

/** Adjusts the checksum of a NAT'ed packet without having to completely recalculate it
 * @todo: verify this works for little- and big-endian
 *
 * @param chksum points to the chksum in the packet
 * @param optr points to the old data in the packet
 * @param olen length of old data
 * @param nptr points to the new data in the packet
 * @param nlen length of new data
 */
static void
ip_nat_chksum_adjust(u8_t *chksum, const u8_t *optr, s16_t olen, const u8_t *nptr, s16_t nlen)
{
  s32_t x, oldval, newval;

  LWIP_ASSERT("NULL != chksum", NULL != chksum);
  LWIP_ASSERT("NULL != optr", NULL != optr);
  LWIP_ASSERT("NULL != nptr", NULL != nptr);
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("ip_nat_chksum_adjust: chksum=%p, optr=%p, olen=%" U16_F ", nptr=%p, nlen=%" U16_F "\n",
    chksum, optr, olen, nptr, nlen));
  x = chksum[0] * 256 + chksum[1];
  x = ~x & 0xFFFF;
  while (olen) {
    oldval = optr[0] * 256 + optr[1];
    optr += 2;
    x -= oldval & 0xffff;
    if (x <= 0) {
      x--;
      x &= 0xffff;
    }
    olen -= 2;
  }
  while (nlen) {
    newval = nptr[0] * 256 + nptr[1];
    nptr += 2;
    x += newval & 0xffff;
    if (x & 0x10000) {
      x++;
      x &= 0xffff;
    }
    nlen -= 2;
  }
  x = ~x & 0xFFFF;
  chksum[0] = x / 256;
  chksum[1] = x & 0xff;
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("ip_nat_chksum_adjust: chksum = 0x%x\n", *((u16_t *) chksum)));
}

#if defined(LWIP_DEBUG) && (LWIP_NAT_DEBUG & LWIP_DBG_ON)
/**
 * This function dumps an IP address
 *
 * @param addr IP address
 */
static void
ip_nat_dbg_dump_ip(const ip_addr_t *addr)
{
  LWIP_ASSERT("NULL != addr", NULL != addr);
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("%" U16_F ".%" U16_F ".%" U16_F ".%" U16_F,
    ip4_addr1(addr), ip4_addr2(addr), ip4_addr3(addr), ip4_addr4(addr)));
}

/**
 * This function dumps an IP header
 *
 * @param msg a message to print
 * @param iphdr IP header
 */
static void
ip_nat_dbg_dump(const char *msg, const struct ip_hdr *iphdr)
{
  LWIP_ASSERT("NULL != msg", NULL != msg);
  LWIP_ASSERT("NULL != iphdr", NULL != iphdr);
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("%s: IP: (", msg));
  ip_nat_dbg_dump_ip((ip_addr_t *)&(iphdr->src));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (" --> "));
  ip_nat_dbg_dump_ip((ip_addr_t *)&(iphdr->dest));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (" id=%" U16_F ", chksum=%" U16_F ")\n",
    ntohs(IPH_ID(iphdr)), ntohs(IPH_CHKSUM(iphdr))));
}

/**
 * This function dumps an ICMP echo reply/recho request nat entry.
 *
 * @param msg a message to print
 * @param nat_entry the ICMP NAT entry to print
 */
static void
ip_nat_dbg_dump_icmp_nat_entry(const char *msg, const ip_nat_entries_icmp_t *nat_entry)
{
  LWIP_ASSERT("NULL != msg", NULL != msg);
  LWIP_ASSERT("NULL != nat_entry", NULL != nat_entry);
  LWIP_ASSERT("NULL != nat_entry->common.cfg", NULL != nat_entry->common.cfg);
  LWIP_ASSERT("NULL != nat_entry->common.cfg->entry.out_if",
    NULL != nat_entry->common.cfg->entry.out_if);
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("%s", msg));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("ICMP : ("));
  ip_nat_dbg_dump_ip(&(nat_entry->common.source));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (" --> "));
  ip_nat_dbg_dump_ip(&(nat_entry->common.dest));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (" id=%" U16_F, ntohs(nat_entry->id)));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (", seq=%" U16_F, ntohs(nat_entry->seqno)));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (") mapped at ("));
  ip_nat_dbg_dump_ip(&(nat_entry->common.cfg->entry.out_if->ip_addr));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (" --> "));
  ip_nat_dbg_dump_ip(&(nat_entry->common.dest));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (" id=%" U16_F, ntohs(nat_entry->id)));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (", seq=%" U16_F, ntohs(nat_entry->seqno)));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (")\n"));
}

/**
 * This function dumps an TCP nat entry.
 *
 * @param msg a message to print
 * @param nat_entry the TCP NAT entry to print
 */
static void
ip_nat_dbg_dump_tcp_nat_entry(const char *msg, const ip_nat_entries_tcp_t *nat_entry)
{
  LWIP_ASSERT("NULL != msg", NULL != msg);
  LWIP_ASSERT("NULL != nat_entry", NULL != nat_entry);
  LWIP_ASSERT("NULL != nat_entry->common.cfg", NULL != nat_entry->common.cfg);
  LWIP_ASSERT("NULL != nat_entry->common.cfg->entry.out_if",
    NULL != nat_entry->common.cfg->entry.out_if);
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("%s", msg));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("TCP : ("));
  ip_nat_dbg_dump_ip(&(nat_entry->common.source));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (":%" U16_F, ntohs(nat_entry->sport)));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (" --> "));
  ip_nat_dbg_dump_ip(&(nat_entry->common.dest));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (":%" U16_F, ntohs(nat_entry->dport)));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (") mapped at ("));
  ip_nat_dbg_dump_ip(&(nat_entry->common.cfg->entry.out_if->ip_addr));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (":%" U16_F, ntohs(nat_entry->nport)));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (" --> "));
  ip_nat_dbg_dump_ip(&(nat_entry->common.dest));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (":%" U16_F, ntohs(nat_entry->dport)));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (")\n"));
}

/**
 * This function dumps a UDP NAT entry.
 *
 * @param msg a message to print
 * @param nat_entry the UDP NAT entry to print
 */
static void
ip_nat_dbg_dump_udp_nat_entry(const char *msg, const ip_nat_entries_udp_t *nat_entry)
{
  LWIP_ASSERT("NULL != msg", NULL != msg);
  LWIP_ASSERT("NULL != nat_entry", NULL != nat_entry);
  LWIP_ASSERT("NULL != nat_entry->common.cfg", NULL != nat_entry->common.cfg);
  LWIP_ASSERT("NULL != nat_entry->common.cfg->entry.out_if",
    NULL != nat_entry->common.cfg->entry.out_if);
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("%s", msg));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("UDP : ("));
  ip_nat_dbg_dump_ip(&(nat_entry->common.source));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (":%" U16_F, ntohs(nat_entry->sport)));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (" --> "));
  ip_nat_dbg_dump_ip(&(nat_entry->common.dest));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (":%" U16_F, ntohs(nat_entry->dport)));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (") mapped at ("));
  ip_nat_dbg_dump_ip(&(nat_entry->common.cfg->entry.out_if->ip_addr));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (":%" U16_F, ntohs(nat_entry->nport)));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (" --> "));
  ip_nat_dbg_dump_ip(&(nat_entry->common.dest));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (":%" U16_F, ntohs(nat_entry->dport)));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (")\n"));
}

/** Prints some info when creating a new NAT entry */
static void
ip_nat_dbg_dump_init(ip_nat_conf_t *ip_nat_cfg_new)
{
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("ip_nat_init: added new NAT interface\n"));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("ip_nat_init:   "));
  ip_nat_dbg_dump_ip(&(ip_nat_cfg_new->entry.source_net));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("/"));
  ip_nat_dbg_dump_ip(&(ip_nat_cfg_new->entry.source_netmask));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("@"));
  ip_nat_dbg_dump_ip(&(ip_nat_cfg_new->entry.in_if->ip_addr));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (" --> "));
  ip_nat_dbg_dump_ip(&(ip_nat_cfg_new->entry.dest_net));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("/"));
  ip_nat_dbg_dump_ip(&(ip_nat_cfg_new->entry.dest_netmask));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("@"));
  ip_nat_dbg_dump_ip(&(ip_nat_cfg_new->entry.out_if->ip_addr));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("\n"));
}

/** Prints some info when removing a NAT entry */
static void
ip_nat_dbg_dump_remove(ip_nat_conf_t *cur)
{
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("ip_nat_remove: removing existing NAT interface\n"));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("ip_nat_remove:   "));
  ip_nat_dbg_dump_ip(&(cur->entry.source_net));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("/"));
  ip_nat_dbg_dump_ip(&(cur->entry.source_netmask));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("@"));
  ip_nat_dbg_dump_ip(&(cur->entry.in_if->ip_addr));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, (" --> "));
  ip_nat_dbg_dump_ip(&(cur->entry.dest_net));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("/"));
  ip_nat_dbg_dump_ip(&(cur->entry.dest_netmask));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("@"));
  ip_nat_dbg_dump_ip(&(cur->entry.out_if->ip_addr));
  LWIP_DEBUGF(LWIP_NAT_DEBUG, ("\n"));
}
#endif /* defined(LWIP_DEBUG) && (LWIP_NAT_DEBUG & LWIP_DBG_ON) */

#endif /* IP_NAT */
