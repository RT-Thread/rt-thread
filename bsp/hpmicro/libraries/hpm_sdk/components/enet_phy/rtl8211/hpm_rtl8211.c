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
#include "hpm_rtl8211_regs.h"
#include "hpm_rtl8211.h"

/*---------------------------------------------------------------------
 * Internal API
 *---------------------------------------------------------------------
 */
static bool rtl8211_check_id(ENET_Type *ptr)
{
    uint16_t id1, id2;

    id1 = enet_read_phy(ptr, RTL8211_ADDR, RTL8211_PHYID1);
    id2 = enet_read_phy(ptr, RTL8211_ADDR, RTL8211_PHYID2);

    if (RTL8211_PHYID1_OUI_MSB_GET(id1) == RTL8211_ID1 && RTL8211_PHYID2_OUI_LSB_GET(id2) == RTL8211_ID2) {
        return true;
    } else {
        return false;
    }
}

/*---------------------------------------------------------------------
 * API
 *---------------------------------------------------------------------
 */
void rtl8211_reset(ENET_Type *ptr)
{
    uint16_t data;

    /* PHY reset */
    enet_write_phy(ptr, RTL8211_ADDR, RTL8211_BMCR, RTL8211_BMCR_RESET_SET(1));

    /* wait until the reset is completed */
    do {
        data = enet_read_phy(ptr, RTL8211_ADDR, RTL8211_BMCR);
    } while (RTL8211_BMCR_RESET_GET(data));
}

void rtl8211_basic_mode_default_config(ENET_Type *ptr, rtl8211_config_t *config)
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

bool rtl8211_basic_mode_init(ENET_Type *ptr, rtl8211_config_t *config)
{
    uint16_t data = 0;

    data |= RTL8211_BMCR_RESET_SET(0)                        /* Normal operation */
         |  RTL8211_BMCR_LOOPBACK_SET(config->loopback)      /* configure PCS loopback mode */
         |  RTL8211_BMCR_ANE_SET(config->auto_negotiation)   /* configure Auto-Negotiation */
         |  RTL8211_BMCR_PWD_SET(0)                          /* Normal operation */
         |  RTL8211_BMCR_ISOLATE_SET(0)                      /* Normal operation */
         |  RTL8211_BMCR_RESTART_AN_SET(0)                   /* Normal operation (ignored when Auto-Negotiation is disabled) */
         |  RTL8211_BMCR_COLLISION_TEST_SET(0);              /* Normal operation */

    if (config->auto_negotiation == 0) {
        data |= RTL8211_BMCR_SPEED0_SET(config->speed) | RTL8211_BMCR_SPEED1_SET(config->speed >> 1);   /* Set port speed */
        data |= RTL8211_BMCR_DUPLEX_SET(config->duplex);                                                /* Set duplex mode */
    }

    enet_write_phy(ptr, RTL8211_ADDR, RTL8211_BMCR, data);

    /* check the id of rtl8211 */
    if (rtl8211_check_id(ptr) == false) {
        return false;
    }

    return true;
}


void rtl8211_get_phy_status(ENET_Type *ptr, enet_phy_status_t *status)
{
    uint16_t data;

    data = enet_read_phy(ptr, RTL8211_ADDR, RTL8211_PHYSR);
    status->enet_phy_link = RTL8211_PHYSR_LINK_REAL_TIME_GET(data);
    status->enet_phy_speed = RTL8211_PHYSR_SPEED_GET(data) == 0 ? enet_phy_port_speed_10mbps : RTL8211_PHYSR_SPEED_GET(data) == 1 ? enet_phy_port_speed_100mbps : enet_phy_port_speed_1000mbps;
    status->enet_phy_duplex = RTL8211_PHYSR_DUPLEX_GET(data);
}
