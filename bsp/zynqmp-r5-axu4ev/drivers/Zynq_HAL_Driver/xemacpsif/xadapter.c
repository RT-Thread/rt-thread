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

#include "lwipopts.h"
#include "xlwipconfig.h"
#include "xemac_ieee_reg.h"

#if !NO_SYS
#ifdef OS_IS_XILKERNEL
#include "xmk.h"
#include "sys/process.h"
#endif
#endif

#include "lwip/mem.h"
#include "lwip/stats.h"
#include "lwip/sys.h"
#include "lwip/ip.h"
#include "lwip/tcp.h"
#include "lwip/udp.h"
#include "lwip/priv/tcp_priv.h"

#include "netif/etharp.h"
#include "netif/xadapter.h"

#ifdef XLWIP_CONFIG_INCLUDE_EMACLITE
#include "netif/xemacliteif.h"
#endif

#ifdef XLWIP_CONFIG_INCLUDE_AXI_ETHERNET
#include "netif/xaxiemacif.h"
#endif

#ifdef XLWIP_CONFIG_INCLUDE_GEM
#include "netif/xemacpsif.h"
#endif

#if !NO_SYS
#include "lwip/tcpip.h"
#endif

#ifdef OS_IS_FREERTOS
#define THREAD_STACKSIZE 256
#define LINK_DETECT_THREAD_INTERVAL 1000 /* one second */

void link_detect_thread(void *p);
#endif

/* global lwip debug variable used for debugging */
int lwip_runtime_debug = 0;

enum ethernet_link_status eth_link_status = ETH_LINK_UNDEFINED;
u32_t phyaddrforemac;

void
lwip_raw_init()
{
    ip_init();    /* Doesn't do much, it should be called to handle future changes. */
#if LWIP_UDP
    udp_init();    /* Clears the UDP PCB list. */
#endif
#if LWIP_TCP
    tcp_init();    /* Clears the TCP PCB list and clears some internal TCP timers. */
            /* Note: you must call tcp_fasttmr() and tcp_slowtmr() at the */
            /* predefined regular intervals after this initialization. */
#endif
}

static enum xemac_types
find_mac_type(unsigned base)
{
    int i;

    for (i = 0; i < xtopology_n_emacs; i++) {
        if (xtopology[i].emac_baseaddr == base)
            return xtopology[i].emac_type;
    }

    return xemac_type_unknown;
}

int
xtopology_find_index(unsigned base)
{
    int i;

    for (i = 0; i < xtopology_n_emacs; i++) {
        if (xtopology[i].emac_baseaddr == base)
            return i;
    }

    return -1;
}

/*
 * xemac_add: this is a wrapper around lwIP's netif_add function.
 * The objective is to provide portability between the different Xilinx MAC's
 * This function can be used to add both xps_ethernetlite and xps_ll_temac
 * based interfaces
 */
struct netif *
xemac_add(struct netif *netif,
    ip_addr_t *ipaddr, ip_addr_t *netmask, ip_addr_t *gw,
    unsigned char *mac_ethernet_address,
    unsigned mac_baseaddr)
{
    int i;

#ifdef OS_IS_FREERTOS
    /* Start thread to detect link periodically for Hot Plug autodetect */
    sys_thread_new("link_detect_thread", link_detect_thread, netif,
            THREAD_STACKSIZE, tskIDLE_PRIORITY);
#endif

    /* set mac address */
    netif->hwaddr_len = 6;
    for (i = 0; i < 6; i++)
        netif->hwaddr[i] = mac_ethernet_address[i];

    /* initialize based on MAC type */
        switch (find_mac_type(mac_baseaddr)) {
            case xemac_type_xps_emaclite:
#ifdef XLWIP_CONFIG_INCLUDE_EMACLITE
                return netif_add(netif, ipaddr, netmask, gw,
                    (void*)(UINTPTR)mac_baseaddr,
                    xemacliteif_init,
#if NO_SYS
                    ethernet_input
#else
                    tcpip_input
#endif
                    );
#else
                return NULL;
#endif
            case xemac_type_axi_ethernet:
#ifdef XLWIP_CONFIG_INCLUDE_AXI_ETHERNET
                return netif_add(netif, ipaddr, netmask, gw,
                    (void*)(UINTPTR)mac_baseaddr,
                    xaxiemacif_init,
#if NO_SYS
                    ethernet_input
#else
                    tcpip_input
#endif
                    );
#else
                return NULL;
#endif
#if defined (__arm__) || defined (__aarch64__)
            case xemac_type_emacps:
#ifdef XLWIP_CONFIG_INCLUDE_GEM
                return netif_add(netif, ipaddr, netmask, gw,
                        (void*)(UINTPTR)mac_baseaddr,
                        xemacpsif_init,
#if NO_SYS
                        ethernet_input
#else
                        tcpip_input
#endif

                        );
#endif
#endif
            default:
                xil_printf("unable to determine type of EMAC with baseaddress 0x%08x\r\n",
                        mac_baseaddr);
                return NULL;
    }
}

int
xemacif_input(struct netif *netif)
{
    struct xemac_s *emac = (struct xemac_s *)netif->state;

    int n_packets = 0;

    switch (emac->type) {
        case xemac_type_xps_emaclite:
#ifdef XLWIP_CONFIG_INCLUDE_EMACLITE
            n_packets = xemacliteif_input(netif);
            break;
#else
            // print("incorrect configuration: xps_ethernetlite drivers not present?");
            while(1);
            return 0;
#endif
        case xemac_type_axi_ethernet:
#ifdef XLWIP_CONFIG_INCLUDE_AXI_ETHERNET
            n_packets = xaxiemacif_input(netif);
            break;
#else
            // print("incorrect configuration: axi_ethernet drivers not present?");
            while(1);
            return 0;
#endif
#if defined (__arm__) || defined (__aarch64__)
        case xemac_type_emacps:
#ifdef XLWIP_CONFIG_INCLUDE_GEM
            n_packets = xemacpsif_input(netif);
            break;
#else
            xil_printf("incorrect configuration: ps7_ethernet drivers not present?\r\n");
            while(1);
            return 0;
#endif
#endif
        default:
            // print("incorrect configuration: unknown temac type");
            while(1);
            return 0;
    }

    return n_packets;
}

#if defined(XLWIP_CONFIG_INCLUDE_GEM)
u32_t phy_link_detect(XEmacPs *xemacp, u32_t phy_addr)
{
    u16_t status;

    /* Read Phy Status register twice to get the confirmation of the current
     * link status.
     */
    XEmacPs_PhyRead(xemacp, phy_addr, IEEE_STATUS_REG_OFFSET, &status);
    XEmacPs_PhyRead(xemacp, phy_addr, IEEE_STATUS_REG_OFFSET, &status);

    if (status & IEEE_STAT_LINK_STATUS)
        return 1;
    return 0;
}
#elif defined(XLWIP_CONFIG_INCLUDE_AXI_ETHERNET)
static u32_t phy_link_detect(XAxiEthernet *xemacp, u32_t phy_addr)
{
    u16_t status;

    /* Read Phy Status register twice to get the confirmation of the current
     * link status.
     */
    XAxiEthernet_PhyRead(xemacp, phy_addr, IEEE_STATUS_REG_OFFSET, &status);
    XAxiEthernet_PhyRead(xemacp, phy_addr, IEEE_STATUS_REG_OFFSET, &status);

    if (status & IEEE_STAT_LINK_STATUS)
        return 1;
    return 0;
}
#elif defined(XLWIP_CONFIG_INCLUDE_EMACLITE)
static u32_t phy_link_detect(XEmacLite *xemacp, u32_t phy_addr)
{
    u16_t status;

    /* Read Phy Status register twice to get the confirmation of the current
     * link status.
     */
    XEmacLite_PhyRead(xemacp, phy_addr, IEEE_STATUS_REG_OFFSET, &status);
    XEmacLite_PhyRead(xemacp, phy_addr, IEEE_STATUS_REG_OFFSET, &status);

    if (status & IEEE_STAT_LINK_STATUS)
        return 1;
    return 0;
}
#endif

#if defined(XLWIP_CONFIG_INCLUDE_GEM)
u32_t phy_autoneg_status(XEmacPs *xemacp, u32_t phy_addr)
{
    u16_t status;

    /* Read Phy Status register twice to get the confirmation of the current
     * link status.
     */
    XEmacPs_PhyRead(xemacp, phy_addr, IEEE_STATUS_REG_OFFSET, &status);
    XEmacPs_PhyRead(xemacp, phy_addr, IEEE_STATUS_REG_OFFSET, &status);

    if (status & IEEE_STAT_AUTONEGOTIATE_COMPLETE)
        return 1;
    return 0;
}
#elif defined(XLWIP_CONFIG_INCLUDE_AXI_ETHERNET)
static u32_t phy_autoneg_status(XAxiEthernet *xemacp, u32_t phy_addr)
{
    u16_t status;

    /* Read Phy Status register twice to get the confirmation of the current
     * link status.
     */
    XAxiEthernet_PhyRead(xemacp, phy_addr, IEEE_STATUS_REG_OFFSET, &status);
    XAxiEthernet_PhyRead(xemacp, phy_addr, IEEE_STATUS_REG_OFFSET, &status);

    if (status & IEEE_STAT_AUTONEGOTIATE_COMPLETE)
        return 1;
    return 0;
}
#elif defined(XLWIP_CONFIG_INCLUDE_EMACLITE)
static u32_t phy_autoneg_status(XEmacLite *xemacp, u32_t phy_addr)
{
    u16_t status;

    /* Read Phy Status register twice to get the confirmation of the current
     * link status.
     */
    XEmacLite_PhyRead(xemacp, phy_addr, IEEE_STATUS_REG_OFFSET, &status);
    XEmacLite_PhyRead(xemacp, phy_addr, IEEE_STATUS_REG_OFFSET, &status);

    if (status & IEEE_STAT_AUTONEGOTIATE_COMPLETE)
        return 1;
    return 0;
}
#endif

void eth_link_detect(struct netif *netif)
{
    u32_t link_speed, phy_link_status;
    struct xemac_s *xemac = (struct xemac_s *)(netif->state);

#if defined(XLWIP_CONFIG_INCLUDE_GEM)
    xemacpsif_s *xemacs = (xemacpsif_s *)(xemac->state);
    XEmacPs *xemacp = &xemacs->emacps;
#elif defined(XLWIP_CONFIG_INCLUDE_AXI_ETHERNET)
    xaxiemacif_s *xemacs = (xaxiemacif_s *)(xemac->state);
    XAxiEthernet *xemacp = &xemacs->axi_ethernet;
#elif defined(XLWIP_CONFIG_INCLUDE_EMACLITE)
    xemacliteif_s *xemacs = (xemacliteif_s *)(xemac->state);
    XEmacLite *xemacp = xemacs->instance;
#endif

    if ((xemacp->IsReady != (u32)XIL_COMPONENT_IS_READY) ||
            (eth_link_status == ETH_LINK_UNDEFINED))
        return;

    phy_link_status = phy_link_detect(xemacp, phyaddrforemac);

    if ((eth_link_status == ETH_LINK_UP) && (!phy_link_status))
        eth_link_status = ETH_LINK_DOWN;

    switch (eth_link_status) {
        case ETH_LINK_UNDEFINED:
        case ETH_LINK_UP:
            return;
        case ETH_LINK_DOWN:
            netif_set_link_down(netif);
            eth_link_status = ETH_LINK_NEGOTIATING;
            xil_printf("Ethernet Link down\r\n");
            break;
        case ETH_LINK_NEGOTIATING:
            if (phy_link_status &&
                phy_autoneg_status(xemacp, phyaddrforemac)) {

                /* Initiate Phy setup to get link speed */
#if defined(XLWIP_CONFIG_INCLUDE_GEM)
                link_speed = phy_setup_emacps(xemacp,
                                phyaddrforemac);
                XEmacPs_SetOperatingSpeed(xemacp, link_speed);
#elif defined(XLWIP_CONFIG_INCLUDE_AXI_ETHERNET)
                link_speed = phy_setup_axiemac(xemacp);
                XAxiEthernet_SetOperatingSpeed(xemacp,
                                   link_speed);
#endif
                netif_set_link_up(netif);
                eth_link_status = ETH_LINK_UP;
                xil_printf("Ethernet Link up\r\n");
            }
            break;
    }
}

#ifdef OS_IS_FREERTOS
void link_detect_thread(void *p)
{
    struct netif *netif = (struct netif *) p;

    while (1) {
        /* Call eth_link_detect() every second to detect Ethernet link
         * change.
         */
        eth_link_detect(netif);
        vTaskDelay(LINK_DETECT_THREAD_INTERVAL / portTICK_RATE_MS);
    }
}
#endif
