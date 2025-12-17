/*
 * Copyright (c) 2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef DRV_TSW_H
#define DRV_TSW_H

#include <netif/ethernetif.h>
#include "hpm_tsw_drv.h"
#include "board.h"

#define TSW_MAC_COUNT            (6U)
#define TSW_FRAME_BUFF_COUNT     (16U)

typedef enum {
    TSW_MAC_ADDR_PARA_ERROR    = -1,
    TSW_MAC_ADDR_FROM_OTP_MAC,
    TSW_MAC_ADDR_FROM_OTP_UUID,
    TSW_MAC_ADDR_FROM_MACRO
} tsw_mac_addr_t;

typedef struct {
    uint32_t buffer;
    uint16_t count;
    uint16_t size;
} tsw_buff_config_t;

typedef struct {
    uint8_t mac_addr0;
    uint8_t mac_addr1;
    uint8_t mac_addr2;
    uint8_t mac_addr3;
    uint8_t mac_addr4;
    uint8_t mac_addr5;
} mac_init_t;

typedef struct {
    TSW_Type *instance;
    uint8_t port;
    tsw_buff_config_t *rx_buff_cfg;
    tsw_buff_config_t *tx_buff_cfg;
    uint8_t mac[TSW_MAC_COUNT];
    uint8_t media_interface;
    uint32_t irq_number;
    bool int_refclk;
    uint8_t tx_delay;
    uint8_t rx_delay;
} tsw_device;

typedef struct {
    const char *name;
    TSW_Type *base;
    clock_name_t clock_name;
    int32_t irq_num;
    uint8_t inf;
    struct eth_device *eth_dev;
    tsw_device *tsw_dev;
    uint8_t port;
    tsw_buff_config_t *rx_buff_cfg;
    tsw_buff_config_t *tx_buff_cfg;
    uint8_t tx_delay;
    uint8_t rx_delay;
    bool int_refclk;
} hpm_tsw_t;

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

int rt_hw_tsw_init(void);

#endif /* DRV_TSW_H */

