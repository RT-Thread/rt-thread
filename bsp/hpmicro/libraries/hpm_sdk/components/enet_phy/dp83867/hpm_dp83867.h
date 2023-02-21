/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_DP83867_H
#define HPM_DP83867_H

/*---------------------------------------------------------------------*
 * Includes
 *---------------------------------------------------------------------*/
#include "stdint.h"

/*---------------------------------------------------------------------*
 *  Macro Const Definitions
 *---------------------------------------------------------------------*/
#define PHY_ADDR (0U)
#define PHY_ID1  (0x2000U)
#define PHY_ID2  (0x28U)

/*---------------------------------------------------------------------*
 *  Typedef Struct Declarations
 *---------------------------------------------------------------------*/
typedef struct {
    bool loopback;
    uint8_t speed;
    bool auto_negotiation;
    uint8_t duplex_mode;
} dp83867_config_t;

typedef enum {
    DP83867_RX_DELAY_0P25_NS = 0,
    DP83867_RX_DELAY_0P50_NS,
    DP83867_RX_DELAY_0P75_NS,
    DP83867_RX_DELAY_1P00_NS,
    DP83867_RX_DELAY_1P25_NS,
    DP83867_RX_DELAY_1P50_NS,
    DP83867_RX_DELAY_1P75_NS,
    DP83867_RX_DELAY_2P00_NS,
    DP83867_RX_DELAY_2P25_NS,
    DP83867_RX_DELAY_2P50_NS,
    DP83867_RX_DELAY_2P75_NS,
    DP83867_RX_DELAY_3P00_NS,
    DP83867_RX_DELAY_3P25_NS,
    DP83867_RX_DELAY_3P50_NS,
    DP83867_RX_DELAY_3P75_NS,
    DP83867_RX_DELAY_4P00_NS
} dp83867_rgmii_rx_delay_t;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
/*---------------------------------------------------------------------*
 * Exported Functions
 *---------------------------------------------------------------------*/
uint16_t dp83867_check(ENET_Type *ptr, uint32_t addr);
void dp83867_reset(ENET_Type *ptr);
void dp83867_basic_mode_default_config(ENET_Type *ptr, dp83867_config_t *config);
bool dp83867_basic_mode_init(ENET_Type *ptr, dp83867_config_t *config);
void dp83867_read_status(ENET_Type *ptr);
void dp83867_control_config(ENET_Type *ptr);
void dp83867_ctl_config(ENET_Type *ptr);
void dp83867_bist_config(ENET_Type *ptr);
uint16_t dp83867_get_phy_link_status(ENET_Type *ptr);
void dp83867_set_rx_clk_delay(ENET_Type *ptr);
void dp83867_enable_crc_check(ENET_Type *ptr);
void dp83867_set_rgmii_rx_delay(ENET_Type *ptr, uint32_t phy_addr, uint8_t delay);
uint16_t dp83867_get_rgmii_rx_delay(ENET_Type *ptr, uint32_t phy_addr);
void dp83867_enable_rmii_inf(ENET_Type *ptr);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* HPM_DP83867_H */