/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*---------------------------------------------------------------------*
 * Includes
 *---------------------------------------------------------------------*/
#include "hpm_enet_drv.h"
#include "hpm_dp83848_regs.h"
#include "hpm_dp83848.h"
#include "board.h"

/*---------------------------------------------------------------------*
 * Internal API
 *---------------------------------------------------------------------*/
static bool dp83848_id_check(ENET_Type *ptr)
{
    uint16_t id1, id2;

    id1 = enet_read_phy(ptr, PHY_ADDR, DP83848_REG_PHYID1);
    id2 = enet_read_phy(ptr, PHY_ADDR, DP83848_REG_PHYID2);

    if (DP83848_PHYID1_OUI_MSB_GET(id1) == PHY_ID1 && DP83848_PHYID2_OUI_MSB_GET(id2) == PHY_ID2) {
        return true;
    } else {
        return false;
    }
}

/*---------------------------------------------------------------------*
 * API
 *---------------------------------------------------------------------*/
uint16_t dp83848_register_check(ENET_Type *ptr, uint32_t addr)
{
   return enet_read_phy(ptr, PHY_ADDR, addr);
}

void dp83848_reset(ENET_Type *ptr)
{
    uint16_t data;

    /* PHY reset */
    enet_write_phy(ptr, PHY_ADDR, DP83848_REG_BMCR, DP83848_BMCR_RESET_SET(1));

    /* wait until the reset is completed */
    do {
        data = enet_read_phy(ptr, PHY_ADDR, DP83848_REG_BMCR);
    } while (DP83848_BMCR_RESET_GET(data));
}

void dp83848_basic_mode_default_config(ENET_Type *ptr, dp83848_config_t *config)
{
    config->loopback         = 1; /* Enable PCS loopback mode */
    config->speed            = 2; /* reserved:3/2; 100mbps: 1; 10mbps: 0 */
    config->auto_negotiation = 1; /* Enable Auto-Negotiation */
    config->duplex_mode      = 1; /* Full duplex mode */
}

bool dp83848_basic_mode_init(ENET_Type *ptr, dp83848_config_t *config)
{
    uint16_t para = 0;

    para |= DP83848_BMCR_RESET_SET(0)                        /* Normal operation */
         |  DP83848_BMCR_LOOPBACK_SET(config->loopback)      /* configure PCS loopback mode */
         |  DP83848_BMCR_ANE_SET(config->auto_negotiation)   /* configure Auto-Negotiation */
         |  DP83848_BMCR_PWD_SET(0)                          /* Normal operation */
         |  DP83848_BMCR_ISOLATE_SET(0)                      /* Normal operation */
         |  DP83848_BMCR_RESTART_AN_SET(0)                   /* Normal operation (ignored when Auto-Negotiation is disabled) */
         |  DP83848_BMCR_COLLISION_TEST_SET(0);              /* Normal operation */

    if (config->auto_negotiation == 0) {
        para |= DP83848_BMCR_SPEED0_SET(config->speed) | DP83848_BMCR_SPEED1_SET(config->speed >> 1);
    }

    /* check the id of dp83848 */
    if (dp83848_id_check(ptr) == false) {
        return false;
    }

    para = enet_read_phy(ptr, PHY_ADDR, DP83848_REG_BMCR) & ~ DP83848_BMCR_SPEED0_MASK;
    enet_write_phy(ptr, PHY_ADDR, DP83848_REG_BMCR, para);

    return true;
}


void dp83848_init_auto_negotiation(void)
{
}
