/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_DP83848_H
#define HPM_DP83848_H

/*---------------------------------------------------------------------*
 * Includes
 *---------------------------------------------------------------------*/
#include "stdint.h"

/*---------------------------------------------------------------------*
 *  Macro Const Definitions
 *---------------------------------------------------------------------*/
#define PHY_ADDR (1U)
#define PHY_ID1  (0x2000U)
#define PHY_ID2  (0x17U)

/*---------------------------------------------------------------------*
 *  Typedef Struct Declarations
 *---------------------------------------------------------------------*/
typedef struct {
    bool loopback;
    uint8_t speed;
    bool auto_negotiation;
    uint8_t duplex_mode;
} dp83848_config_t;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
/*---------------------------------------------------------------------*
 * Exported Functions
 *---------------------------------------------------------------------*/
uint16_t dp83848_check(ENET_Type *ptr, uint32_t addr);
void dp83848_reset(ENET_Type *ptr);
void dp83848_basic_mode_default_config(ENET_Type *ptr, dp83848_config_t *config);
bool dp83848_basic_mode_init(ENET_Type *ptr, dp83848_config_t *config);
void dp83848_read_status(ENET_Type *ptr);
void dp83848_control_config(ENET_Type *ptr);
void dp83867_ctl_config(ENET_Type *ptr);
void dp83867_bist_config(ENET_Type *ptr);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* HPM_DP83848_H */