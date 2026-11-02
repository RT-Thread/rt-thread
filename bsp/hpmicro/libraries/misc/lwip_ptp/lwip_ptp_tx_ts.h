/*
 * Copyright (c) 2026 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LWIP_PTP_TX_TS_H
#define LWIP_PTP_TX_TS_H

#include <stdbool.h>
#include "lwip/def.h"
#include "lwip/pbuf.h"
#include "lwip/prot/ethernet.h"
#include "lwip/prot/ip.h"
#include "lwip/prot/ip4.h"
#include "lwip/prot/udp.h"

/**
 * @brief True if this Ethernet frame should use ENET TX descriptor TTSE and HW timestamp
 * PTPd sends messages that need precise egress time on UDP event port 319 only.
 * General port 320 (Announce, Follow_Up, Delay_Resp, etc.) does not use TX HW stamp.
 */
static inline bool lwip_ptp_frame_needs_tx_hw_timestamp(const struct pbuf *p)
{
    u8_t hdr[SIZEOF_ETH_HDR + SIZEOF_VLAN_HDR + IP_HLEN + sizeof(struct udp_hdr)];
    u16_t ethertype;
    u16_t ip_off;
    const struct ip_hdr *iph;
    u16_t ip_len;
    const struct udp_hdr *udph;

    if (p == NULL || p->tot_len < (s16_t)(SIZEOF_ETH_HDR + IP_HLEN + UDP_HLEN)) {
        return false;
    }
    if (pbuf_copy_partial(p, hdr, (u16_t)sizeof(hdr), 0) != (u16_t)sizeof(hdr)) {
        return false;
    }
    ethertype = lwip_ntohs(*(u16_t *)(hdr + 12U));
    ip_off = SIZEOF_ETH_HDR;
    if (ethertype == ETHTYPE_VLAN) {
        if (p->tot_len < (s16_t)(SIZEOF_ETH_HDR + SIZEOF_VLAN_HDR + IP_HLEN + UDP_HLEN)) {
            return false;
        }
        ethertype = lwip_ntohs(*(u16_t *)(hdr + (SIZEOF_ETH_HDR + 2U)));
        ip_off = SIZEOF_ETH_HDR + SIZEOF_VLAN_HDR;
    }
    if (ethertype != ETHTYPE_IP) {
        return false;
    }
    iph = (const struct ip_hdr *)(hdr + ip_off);
    if (IPH_HL(iph) != 5) {
        return false;
    }
    if (IPH_PROTO(iph) != IP_PROTO_UDP) {
        return false;
    }
    ip_len = IP_HLEN;
    if ((u32_t)ip_off + (u32_t)ip_len + UDP_HLEN > sizeof(hdr)) {
        return false;
    }
    udph = (const struct udp_hdr *)(hdr + ip_off + ip_len);
    return udph->dest == PP_HTONS(319);
}

#endif /* LWIP_PTP_TX_TS_H */
