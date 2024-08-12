/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*---------------------------------------------------------------------
 * Includes
 *---------------------------------------------------------------------
 */
#include "hpm_enet_drv.h"
#include "hpm_jl1111_regs.h"
#include "hpm_jl1111.h"

/*---------------------------------------------------------------------
 * Internal API
 *---------------------------------------------------------------------
 */
static bool jl1111_check_id(ENET_Type *ptr)
{
    uint16_t id1, id2;

    id1 = enet_read_phy(ptr, JL1111_ADDR, JL1111_PHYID1);
    id2 = enet_read_phy(ptr, JL1111_ADDR, JL1111_PHYID2);

    if (JL1111_PHYID1_OUI_MSB_GET(id1) == JL1111_ID1 && JL1111_PHYID2_OUI_LSB_GET(id2) == JL1111_ID2) {
        return true;
    } else {
        return false;
    }
}

/*---------------------------------------------------------------------
 * API
 *---------------------------------------------------------------------
 */
void jl1111_reset(ENET_Type *ptr)
{
    uint16_t data;

    /* PHY reset */
    enet_write_phy(ptr, JL1111_ADDR, JL1111_BMCR, JL1111_BMCR_RESET_SET(1));

    /* wait until the reset is completed */
    do {
        data = enet_read_phy(ptr, JL1111_ADDR, JL1111_BMCR);
    } while (JL1111_BMCR_RESET_GET(data));
}

void jl1111_basic_mode_default_config(ENET_Type *ptr, jl1111_config_t *config)
{
    (void)ptr;

    config->loopback         = false;                        /* Disable PCS loopback mode */
    #if defined(__DISABLE_AUTO_NEGO) && (__DISABLE_AUTO_NEGO)
    config->auto_negotiation = false;                        /* Disable Auto-Negotiation */
    config->speed            = enet_phy_port_speed_100mbps;
    config->duplex           = enet_phy_duplex_full;
    #else
    config->auto_negotiation = true;                         /* Enable Auto-Negotiation */
    #endif
}

bool jl1111_basic_mode_init(ENET_Type *ptr, jl1111_config_t *config)
{
    uint16_t data = 0;

    data |= JL1111_BMCR_RESET_SET(0)                        /* Normal operation */
         |  JL1111_BMCR_LOOPBACK_SET(config->loopback)      /* configure PCS loopback mode */
         |  JL1111_BMCR_ANE_SET(config->auto_negotiation)   /* configure Auto-Negotiation */
         |  JL1111_BMCR_PWD_SET(0)                          /* Normal operation */
         |  JL1111_BMCR_ISOLATE_SET(0)                      /* Normal operation */
         |  JL1111_BMCR_RESTART_AN_SET(0)                   /* Normal operation (ignored when Auto-Negotiation is disabled) */
         |  JL1111_BMCR_COLLISION_TEST_SET(0);              /* Normal operation */

    if (config->auto_negotiation == 0) {
        data |= JL1111_BMCR_SPEED0_SET(config->speed);      /* Set port speed */
        data |= JL1111_BMCR_DUPLEX_SET(config->duplex);     /* Set duplex mode */
    }

    /* check the id of jl1111 */
    if (jl1111_check_id(ptr) == false) {
        return false;
    }

    enet_write_phy(ptr, JL1111_ADDR, JL1111_BMCR, data);

    return true;
}

void jl1111_get_phy_status(ENET_Type *ptr, enet_phy_status_t *status)
{
    uint16_t data, anar, anlpar;

    data = enet_read_phy(ptr, JL1111_ADDR, JL1111_BMSR);
    status->enet_phy_link = JL1111_BMSR_LINK_STATUS_GET(data);

    anar = enet_read_phy(ptr, JL1111_ADDR, JL1111_ANAR);
    anlpar = enet_read_phy(ptr, JL1111_ADDR, JL1111_ANLPAR);
    data = anar & anlpar;

    if (JL1111_ANAR_100BASE_TX_GET(data)) {
        if (JL1111_ANAR_100BASE_TX_FD_GET(data)) {
            status->enet_phy_speed = enet_phy_port_speed_100mbps;
            status->enet_phy_duplex = enet_phy_duplex_full;
        } else {
            status->enet_phy_speed = enet_phy_port_speed_100mbps;
            status->enet_phy_duplex = enet_phy_duplex_half;
        }
    } else if (JL1111_ANAR_10BASE_T_GET(data)) {
        if (JL1111_ANAR_10BASE_T_FD_GET(data)) {
            status->enet_phy_speed = enet_phy_port_speed_10mbps;
            status->enet_phy_duplex = enet_phy_duplex_full;
        } else {
            status->enet_phy_speed = enet_phy_port_speed_10mbps;
            status->enet_phy_duplex = enet_phy_duplex_half;
        }
    } else {

    }
}
