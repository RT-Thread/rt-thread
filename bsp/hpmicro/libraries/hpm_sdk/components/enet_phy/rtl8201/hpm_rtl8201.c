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
#include "hpm_rtl8201_regs.h"
#include "hpm_rtl8201.h"

/*---------------------------------------------------------------------
 * Internal API
 *---------------------------------------------------------------------
 */
static bool rtl8201_check_id(ENET_Type *ptr)
{
    uint16_t id1, id2;

    id1 = enet_read_phy(ptr, RTL8201_ADDR, RTL8201_PHYID1);
    id2 = enet_read_phy(ptr, RTL8201_ADDR, RTL8201_PHYID2);

    if (RTL8201_PHYID1_OUI_MSB_GET(id1) == RTL8201_ID1 && RTL8201_PHYID2_OUI_LSB_GET(id2) == RTL8201_ID2) {
        return true;
    } else {
        return false;
    }
}

/*---------------------------------------------------------------------
 * API
 *---------------------------------------------------------------------
 */
void rtl8201_reset(ENET_Type *ptr)
{
    uint16_t data;

    /* PHY reset */
    enet_write_phy(ptr, RTL8201_ADDR, RTL8201_BMCR, RTL8201_BMCR_RESET_SET(1));

    /* wait until the reset is completed */
    do {
        data = enet_read_phy(ptr, RTL8201_ADDR, RTL8201_BMCR);
    } while (RTL8201_BMCR_RESET_GET(data));
}

void rtl8201_basic_mode_default_config(ENET_Type *ptr, rtl8201_config_t *config)
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
    config->txc_input        = true;                         /* Set TXC as input mode */
}

bool rtl8201_basic_mode_init(ENET_Type *ptr, rtl8201_config_t *config)
{
    uint16_t data = 0;

    data |= RTL8201_BMCR_RESET_SET(0)                        /* Normal operation */
         |  RTL8201_BMCR_LOOPBACK_SET(config->loopback)      /* configure PCS loopback mode */
         |  RTL8201_BMCR_ANE_SET(config->auto_negotiation)   /* configure Auto-Negotiation */
         |  RTL8201_BMCR_PWD_SET(0)                          /* Normal operation */
         |  RTL8201_BMCR_ISOLATE_SET(0)                      /* Normal operation */
         |  RTL8201_BMCR_RESTART_AN_SET(0)                   /* Normal operation (ignored when Auto-Negotiation is disabled) */
         |  RTL8201_BMCR_COLLISION_TEST_SET(0);              /* Normal operation */

    if (config->auto_negotiation == 0) {
        data |= RTL8201_BMCR_SPEED0_SET(config->speed);      /* Set port speed */
        data |= RTL8201_BMCR_DUPLEX_SET(config->duplex);     /* Set duplex mode */
    }

    /* check the id of rtl8201 */
    if (rtl8201_check_id(ptr) == false) {
        return false;
    }

    enet_write_phy(ptr, RTL8201_ADDR, RTL8201_BMCR, data);

    /* select page 7 */
    enet_write_phy(ptr, RTL8201_ADDR, RTL8201_PAGESEL, 7);

    /* set txc direction */
    data = enet_read_phy(ptr, RTL8201_ADDR, RTL8201_RMSR_P7);
    data &= ~RTL8201_RMSR_P7_RG_RMII_CLKDIR_MASK;
    data |= RTL8201_RMSR_P7_RG_RMII_CLKDIR_SET(config->txc_input);
    enet_write_phy(ptr, RTL8201_ADDR, RTL8201_RMSR_P7, data);

    return true;
}

void rtl8201_get_phy_status(ENET_Type *ptr, enet_phy_status_t *status)
{
    uint16_t data;

    data = enet_read_phy(ptr, RTL8201_ADDR, RTL8201_BMSR);
    status->enet_phy_link = RTL8201_BMSR_LINK_STATUS_GET(data);

    data = enet_read_phy(ptr, RTL8201_ADDR, RTL8201_BMCR);
    status->enet_phy_speed = RTL8201_BMCR_SPEED0_GET(data) == 0 ? enet_phy_port_speed_10mbps : enet_phy_port_speed_100mbps;
    status->enet_phy_duplex = RTL8201_BMCR_DUPLEX_GET(data);
}
