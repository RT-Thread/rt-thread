/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef DRV_ENET_H
#define DRV_ENET_H

#include <netif/ethernetif.h>
#include "../../applications/inc/netconf.h"
#include "hpm_enet_drv.h"

typedef struct {
    ENET_Type * instance;
    enet_desc_t desc;
    enet_mac_config_t mac_config;
    uint8_t media_interface;
    uint32_t mask;
    uint32_t dis_mask;
    uint32_t irq_number;
    bool int_refclk;
    uint8_t tx_delay;
    uint8_t rx_delay;
    bool ptp_enable;
    uint32_t ptp_clk_src;
    enet_ptp_config_t ptp_config;
    enet_ptp_time_t ptp_timestamp;
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
    bool ptp_enable;
    uint32_t ptp_clk_src;
    enet_ptp_config_t *ptp_config;
    enet_ptp_time_t *ptp_timestamp;
} hpm_enet_t;

#ifndef ENET0_TX_BUFF_COUNT
#define ENET0_TX_BUFF_COUNT  (10U)
#endif

#ifndef ENET0_RX_BUFF_COUNT
#define ENET0_RX_BUFF_COUNT  (20U)
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
#define ENET1_RX_BUFF_COUNT  (20U)
#endif

#ifndef ENET1_RX_BUFF_SIZE
#define ENET1_RX_BUFF_SIZE   ENET_MAX_FRAME_SIZE
#endif

#ifndef ENET1_TX_BUFF_SIZE
#define ENET1_TX_BUFF_SIZE   ENET_MAX_FRAME_SIZE
#endif

int rt_hw_eth_init(void);

#endif /* DRV_ENET_H */

/* DRV_GPIO_H */
