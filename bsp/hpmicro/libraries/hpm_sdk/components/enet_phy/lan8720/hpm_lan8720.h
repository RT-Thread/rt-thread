/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_LAN8720_H
#define HPM_LAN8720_H

/*---------------------------------------------------------------------
 * Includes
 *---------------------------------------------------------------------
 */
#include "hpm_enet_phy.h"
#include "hpm_common.h"
#include "hpm_enet_regs.h"
/*---------------------------------------------------------------------
 *  Macro Const Definitions
 *---------------------------------------------------------------------
 */
#ifndef LAN8720_ADDR
#define LAN8720_ADDR (0U)
#endif

#define LAN8720_ID1  (0x0007U)
#define LAN8720_ID2  (0x30U)

/*---------------------------------------------------------------------
 *  Typedef Struct Declarations
 *---------------------------------------------------------------------
 */
typedef struct {
    bool loopback;
    uint8_t speed;
    bool auto_negotiation;
    uint8_t duplex;
} lan8720_config_t;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
/*---------------------------------------------------------------------
 * Exported Functions
 *---------------------------------------------------------------------
 */
void lan8720_reset(ENET_Type *ptr);
void lan8720_basic_mode_default_config(ENET_Type *ptr, lan8720_config_t *config);
bool lan8720_basic_mode_init(ENET_Type *ptr, lan8720_config_t *config);
void lan8720_get_phy_status(ENET_Type *ptr, enet_phy_status_t *status);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* HPM_LAN8720_H */
