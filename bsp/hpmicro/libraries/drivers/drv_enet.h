/*
 * Copyright (c) 2021-2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef DRV_ENET_H
#define DRV_ENET_H

#include <netif/ethernetif.h>
#include "hpm_enet_drv.h"
#include "board.h"

typedef struct {
    ENET_Type * instance;
    enet_desc_t desc;
    enet_mac_config_t mac_config;
    uint8_t media_interface;
    uint32_t irq_number;
    bool int_refclk;
    uint8_t tx_delay;
    uint8_t rx_delay;
    enet_int_config_t int_config;
#if __USE_ENET_PTP
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
#if __USE_ENET_PTP
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

#if ENET_SOC_RGMII_EN
#ifndef ENET0_TX_BUFF_COUNT
#define ENET0_TX_BUFF_COUNT  (50U)
#endif

#ifndef ENET0_RX_BUFF_COUNT
#define ENET0_RX_BUFF_COUNT  (60U)
#endif
#else
#ifndef ENET0_TX_BUFF_COUNT
#define ENET0_TX_BUFF_COUNT  (10U)
#endif

#ifndef ENET0_RX_BUFF_COUNT
#define ENET0_RX_BUFF_COUNT  (20U)
#endif
#endif

#ifndef ENET0_RX_BUFF_SIZE
#define ENET0_RX_BUFF_SIZE   ENET_MAX_FRAME_SIZE
#endif

#ifndef ENET0_TX_BUFF_SIZE
#define ENET0_TX_BUFF_SIZE   ENET_MAX_FRAME_SIZE
#endif

#ifndef ENET1_TX_BUFF_COUNT
#define ENET1_TX_BUFF_COUNT  (10U)
#endif

#ifndef ENET1_RX_BUFF_COUNT
#define ENET1_RX_BUFF_COUNT  (30U)
#endif

#ifndef ENET1_RX_BUFF_SIZE
#define ENET1_RX_BUFF_SIZE   ENET_MAX_FRAME_SIZE
#endif

#ifndef ENET1_TX_BUFF_SIZE
#define ENET1_TX_BUFF_SIZE   ENET_MAX_FRAME_SIZE
#endif

#ifndef MAC_ADDR0
#define MAC_ADDR0       (0x98U)
#endif

#ifndef MAC_ADDR1
#define MAC_ADDR1       (0x2CU)
#endif

#ifndef MAC_ADDR2
#define MAC_ADDR2       (0xBCU)
#endif

#ifndef MAC_ADDR3
#define MAC_ADDR3       (0xB1U)
#endif

#ifndef MAC_ADDR4
#define MAC_ADDR4       (0x9FU)
#endif

#ifndef MAC_ADDR5
#define MAC_ADDR5       (0x17U)
#endif

int rt_hw_eth_init(void);

#endif /* DRV_ENET_H */

/* DRV_GPIO_H */
