/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*---------------------------------------------------------------------
 * Includes
 *---------------------------------------------------------------------
 */
#include "hpm_enet_drv.h"
#include "hpm_dp83848_regs.h"
#include "hpm_dp83848.h"
/*---------------------------------------------------------------------
 * Internal API
 *---------------------------------------------------------------------
 */
static bool dp83848_check_id(ENET_Type *ptr)
{
    uint16_t id1, id2;

    id1 = enet_read_phy(ptr, DP83848_ADDR, DP83848_PHYIDR1);
    id2 = enet_read_phy(ptr, DP83848_ADDR, DP83848_PHYIDR2);

    if (DP83848_PHYIDR1_OUI_MSB_GET(id1) == DP83848_ID1 && DP83848_PHYIDR2_OUI_LSB_GET(id2) == DP83848_ID2) {
        return true;
    } else {
        return false;
    }
}

/*---------------------------------------------------------------------
 * API
 *---------------------------------------------------------------------
 */
void dp83848_reset(ENET_Type *ptr)
{
    uint16_t data;

    /* PHY reset */
    enet_write_phy(ptr, DP83848_ADDR, DP83848_BMCR, DP83848_BMCR_RESET_SET(1));

    /* wait until the reset is completed */
    do {
        data = enet_read_phy(ptr, DP83848_ADDR, DP83848_BMCR);
    } while (DP83848_BMCR_RESET_GET(data));
}

void dp83848_basic_mode_default_config(ENET_Type *ptr, dp83848_config_t *config)
{
    config->loopback         = false;                        /* Disable PCS loopback mode */
    #if __DISABLE_AUTO_NEGO
    config->auto_negotiation = false;                        /* Disable Auto-Negotiation */
    config->speed            = enet_phy_port_speed_100mbps;
    config->duplex           = enet_phy_duplex_full;
    #else
    config->auto_negotiation = true;                         /* Enable Auto-Negotiation */
    #endif
}

bool dp83848_basic_mode_init(ENET_Type *ptr, dp83848_config_t *config)
{
    uint16_t data = 0;

    data |= DP83848_BMCR_RESET_SET(0)                        /* Normal operation */
         |  DP83848_BMCR_LOOPBACK_SET(config->loopback)      /* configure PCS loopback mode */
         |  DP83848_BMCR_ANE_SET(config->auto_negotiation)   /* configure Auto-Negotiation */
         |  DP83848_BMCR_PWD_SET(0)                          /* Normal operation */
         |  DP83848_BMCR_ISOLATE_SET(0)                      /* Normal operation */
         |  DP83848_BMCR_RESTART_AN_SET(0)                   /* Normal operation (ignored when Auto-Negotiation is disabled) */
         |  DP83848_BMCR_COLLISION_TEST_SET(0);              /* Normal operation */

    if (config->auto_negotiation == false) {
        data |= DP83848_BMCR_SPEED0_SET(config->speed);      /* Set port speed */
        data |= DP83848_BMCR_DUPLEX_SET(config->duplex);     /* Set duplex mode */
    }

    /* check the id of dp83848 */
    if (dp83848_check_id(ptr) == false) {
        return false;
    }

    enet_write_phy(ptr, DP83848_ADDR, DP83848_BMCR, data);

    return true;
}

void dp83848_get_phy_status(ENET_Type *ptr, enet_phy_status_t *status)
{
    uint16_t data;

    data = enet_read_phy(ptr, DP83848_ADDR, DP83848_PHYSTS);
    status->enet_phy_link = DP83848_PHYSTS_LINK_STATUS_GET(data);
    status->enet_phy_speed = DP83848_PHYSTS_SPEED_STATUS_GET(data) ? enet_phy_port_speed_10mbps : enet_phy_port_speed_100mbps;
    status->enet_phy_duplex = DP83848_PHYSTS_DUPLEX_STATUS_GET(data);
}
