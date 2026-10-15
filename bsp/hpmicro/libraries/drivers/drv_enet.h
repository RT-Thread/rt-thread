/*
 * Copyright (c) 2021-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef DRV_ENET_H
#define DRV_ENET_H

#include <netif/ethernetif.h>
#include "hpm_enet_drv.h"
#include "board.h"
#include "rtt_board.h"
#include "lwip/sys.h"

#if defined(LWIP_SUPPORT_CUSTOM_PBUF) && LWIP_SUPPORT_CUSTOM_PBUF
typedef struct my_custom_pbuf {
   struct pbuf_custom p;
   void *dma_descriptor;
} my_custom_pbuf_t;
#endif

typedef enum {
    ENET_MAC_ADDR_PARA_ERROR    = -1,
    ENET_MAC_ADDR_FROM_OTP_MAC,
    ENET_MAC_ADDR_FROM_OTP_UUID,
    ENET_MAC_ADDR_FROM_MACRO
} enet_mac_addr_t;

typedef struct {
    uint8_t mac_addr0;
    uint8_t mac_addr1;
    uint8_t mac_addr2;
    uint8_t mac_addr3;
    uint8_t mac_addr4;
    uint8_t mac_addr5;
} mac_init_t;

typedef struct {
    ENET_Type * instance;
    clock_name_t clock_name;
    enet_desc_t desc;
    enet_mac_config_t mac_config;
    uint8_t media_interface;
    uint32_t irq_number;
    bool int_refclk;
    uint8_t tx_delay;
    uint8_t rx_delay;
    enet_int_config_t int_config;
    enet_frame_t *frame;
    int cnt;
#if defined(__USE_ENET_PTP) && __USE_ENET_PTP
    bool ptp_enable;
    uint32_t ptp_clk_src;
    enet_ptp_config_t ptp_config;
    enet_ptp_ts_update_t ptp_timestamp;
#endif
} enet_device;

typedef struct _hpm_enet
{
    const char *name;
    ENET_Type *base;
    clock_name_t clock_name;
    int32_t irq_num;
    uint8_t inf;
    struct eth_device *eth_dev;
    enet_device *enet_dev;
    enet_buff_config_t *rx_buff_cfg;
    enet_buff_config_t *tx_buff_cfg;
    volatile enet_rx_desc_t *dma_rx_desc_tab;
    volatile enet_tx_desc_t *dma_tx_desc_tab;
    uint8_t tx_delay;
    uint8_t rx_delay;
    bool int_refclk;
    enet_frame_t *frame;
    int cnt;
#if defined(__USE_ENET_PTP) && __USE_ENET_PTP
    bool ptp_enable;
    uint32_t ptp_clk_src;
    enet_ptp_config_t *ptp_config;
    enet_ptp_ts_update_t *ptp_timestamp;
#endif
} hpm_enet_t;

#define IS_UUID_INVALID(UUID)  (UUID[0] == 0 && \
                                UUID[1] == 0 && \
                                UUID[2] == 0 && \
                                UUID[3] == 0)

#define IS_MAC_INVALID(MAC) (MAC[0] == 0 && \
                             MAC[1] == 0 && \
                             MAC[2] == 0 && \
                             MAC[3] == 0 && \
                             MAC[4] == 0 && \
                             MAC[5] == 0)


#ifndef ENET0_TX_BUFF_COUNT
#define ENET0_TX_BUFF_COUNT  (10U)
#endif

#ifndef ENET0_RX_BUFF_COUNT
#define ENET0_RX_BUFF_COUNT  (20U)
#endif

#ifndef ENET0_RX_BUFF_SIZE
#define ENET0_RX_BUFF_SIZE   (1536U)
#endif

#ifndef ENET0_TX_BUFF_SIZE
#define ENET0_TX_BUFF_SIZE   (1536U)
#endif

#ifndef ENET1_TX_BUFF_COUNT
#define ENET1_TX_BUFF_COUNT  (10U)
#endif

#ifndef ENET1_RX_BUFF_COUNT
#define ENET1_RX_BUFF_COUNT  (20U)
#endif

#ifndef ENET1_RX_BUFF_SIZE
#define ENET1_RX_BUFF_SIZE   (1536U)
#endif

#ifndef ENET1_TX_BUFF_SIZE
#define ENET1_TX_BUFF_SIZE   (1536U)
#endif

#ifndef MAC0_ADDR0
#define MAC0_ADDR0       (0x98U)
#endif

#ifndef MAC0_ADDR1
#define MAC0_ADDR1       (0x2CU)
#endif

#ifndef MAC0_ADDR2
#define MAC0_ADDR2       (0xBCU)
#endif

#ifndef MAC0_ADDR3
#define MAC0_ADDR3       (0xB1U)
#endif

#ifndef MAC0_ADDR4
#define MAC0_ADDR4       (0x9FU)
#endif

#ifndef MAC0_ADDR5
#define MAC0_ADDR5       (0x17U)
#endif


#ifndef MAC1_ADDR0
#define MAC1_ADDR0       (0x98U)
#endif

#ifndef MAC1_ADDR1
#define MAC1_ADDR1       (0x2CU)
#endif

#ifndef MAC1_ADDR2
#define MAC1_ADDR2       (0xBCU)
#endif

#ifndef MAC1_ADDR3
#define MAC1_ADDR3       (0xB1U)
#endif

#ifndef MAC1_ADDR4
#define MAC1_ADDR4       (0x9FU)
#endif

#ifndef MAC1_ADDR5
#define MAC1_ADDR5       (0x27U)
#endif
int rt_hw_eth_init(void);

#endif /* DRV_ENET_H */

/* DRV_GPIO_H */
