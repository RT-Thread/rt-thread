/*
 * Copyright (C) 2007 - 2019 Xilinx, Inc.
 * Copyright (C) 2021 WangHuachen.
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
 */

#ifndef __XADAPTER_H_
#define __XADAPTER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "lwipopts.h"

#if !NO_SYS
#ifdef OS_IS_XILKERNEL
#include "xmk.h"
#endif
#include "lwip/sys.h"
#endif

#include "lwip/netif.h"
#include "lwip/ip.h"

#include "netif/xtopology.h"
#include <netif/ethernetif.h>

struct xemac_s {
    enum xemac_types type;
    int  topology_index;
    void *state;
    struct eth_device *rt_eth_device;
#if defined(OS_IS_FREERTOS) && defined(__arm__) && !defined(ARMR5)
    TimerHandle_t xTimer;
#endif
};

enum ethernet_link_status {
    ETH_LINK_UNDEFINED = 0,
    ETH_LINK_UP,
    ETH_LINK_DOWN,
    ETH_LINK_NEGOTIATING
};

void eth_link_detect(struct netif *netif);
void         lwip_raw_init();
int         xemacif_input(struct netif *netif);
void         xemacif_input_thread(struct netif *netif);
struct netif *    xemac_add(struct netif *netif,
    ip_addr_t *ipaddr, ip_addr_t *netmask, ip_addr_t *gw,
    unsigned char *mac_ethernet_address,
    unsigned mac_baseaddr);
#if defined (__arm__) || defined (__aarch64__)
void xemacpsif_resetrx_on_no_rxdata(struct netif *netif);
#endif

/* global lwip debug variable used for debugging */
extern int lwip_runtime_debug;

#ifdef __cplusplus
}
#endif

#endif
