/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_RTL8211_H
#define HPM_RTL8211_H

/*---------------------------------------------------------------------
 * Includes
 *---------------------------------------------------------------------
 */
#include "hpm_enet_phy.h"
#include "hpm_common.h"
#include "hpm_enet_regs.h"
/*---------------------------------------------------------------------
 *
 *  Macro Const Definitions
 *---------------------------------------------------------------------
 */
#ifndef RTL8211_ADDR
#define RTL8211_ADDR (2U)
#endif

#define RTL8211_ID1  (0x001CU)
#define RTL8211_ID2  (0x32U)

/*---------------------------------------------------------------------
 *  Typedef Struct Declarations
 *---------------------------------------------------------------------
 */
typedef struct {
    bool loopback;
    uint8_t speed;
    bool auto_negotiation;
    uint8_t duplex;
} rtl8211_config_t;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
/*---------------------------------------------------------------------
 * Exported Functions
 *---------------------------------------------------------------------
 */
void rtl8211_reset(ENET_Type *ptr);
void rtl8211_basic_mode_default_config(ENET_Type *ptr, rtl8211_config_t *config);
bool rtl8211_basic_mode_init(ENET_Type *ptr, rtl8211_config_t *config);
void rtl8211_get_phy_status(ENET_Type *ptr, enet_phy_status_t *status);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* HPM_RTL8211_H */
