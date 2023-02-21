/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __ETHERNETIF_H__
#define __ETHERNETIF_H__
#include "hal_emac.h"
#if CTX_TYPE
#include <utils_list.h>
#endif
#include "lwip/err.h"
#include "lwip/netif.h"
#include "ethernet_phy.h"

#define DHCP_OFF              (uint8_t)0
#define DHCP_START            (uint8_t)1
#define DHCP_WAIT_ADDRESS     (uint8_t)2
#define DHCP_ADDRESS_ASSIGNED (uint8_t)3
#define DHCP_TIMEOUT          (uint8_t)4
#define DHCP_LINK_DOWN        (uint8_t)5

#if CTX_TYPE
#define ETH_MAX_BUFFER_SIZE        (ETH_MAX_PACKET_SIZE)
#define EMAC_TX_COMMON_FLAGS   (EMAC_BD_FIELD_MSK(TX_RD)  | \
                                EMAC_BD_FIELD_MSK(TX_IRQ) | \
                                EMAC_BD_FIELD_MSK(TX_PAD) | \
                                EMAC_BD_FIELD_MSK(TX_CRC) | \
                                EMAC_BD_FIELD_MSK(TX_EOF) )

struct unsent_item{
    struct utils_list_hdr hdr;
    struct pbuf *p;
};

typedef struct {
    struct utils_list unsent;
    uint8_t Tx_free_bd_num;
    uint8_t Rx_free_bd_num;
    volatile uint16_t unsent_num;
    uint32_t tx_pkt_cnt;
    uint32_t rx_pkt_cnt;
    uint32_t out_tmr;
    uint32_t done_tmr;
}eth_context;
#endif
/* Exported types ------------------------------------------------------------*/
err_t ethernetif_init(struct netif *netif);
void ethernet_link_check_state(struct netif *netif);
void ethernet_link_status_updated(struct netif *netif);

#endif
