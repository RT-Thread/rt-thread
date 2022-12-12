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
#include "hpm_rtl8201_regs.h"
#include "hpm_rtl8201.h"
#include "board.h"

/*---------------------------------------------------------------------*
 * Internal API
 *---------------------------------------------------------------------*/
static bool rtl8201_id_check(ENET_Type *ptr)
{
    uint16_t id1, id2;

    id1 = enet_read_phy(ptr, PHY_ADDR, RTL8201_REG_PHYID1);
    id2 = enet_read_phy(ptr, PHY_ADDR, RTL8201_REG_PHYID2);

    if (RTL8201_PHYID1_OUI_MSB_GET(id1) == PHY_ID1 && RTL8201_PHYID2_OUI_MSB_GET(id2) == PHY_ID2) {
        return true;
    } else {
        return false;
    }
}

/*---------------------------------------------------------------------*
 * API
 *---------------------------------------------------------------------*/
uint16_t rtl8201_register_check(ENET_Type *ptr, uint32_t addr)
{
   return enet_read_phy(ptr, PHY_ADDR, addr);
}

void rtl8201_reset(ENET_Type *ptr)
{
    uint16_t data;

    /* PHY reset */
    enet_write_phy(ptr, PHY_ADDR, RTL8201_REG_BMCR, RTL8201_BMCR_RESET_SET(1));

    /* wait until the reset is completed */
    do {
        data = enet_read_phy(ptr, PHY_ADDR, RTL8201_REG_BMCR);
    } while (RTL8201_BMCR_RESET_GET(data));
}

void rtl8201_basic_mode_default_config(ENET_Type *ptr, rtl8201_config_t *config)
{
    config->loopback         = 1; /* Enable PCS loopback mode */
    config->speed            = 2; /* reserved:3/2; 100mbps: 1; 10mbps: 0 */
    config->auto_negotiation = 1; /* Enable Auto-Negotiation */
    config->duplex_mode      = 1; /* Full duplex mode */
}

bool rtl8201_basic_mode_init(ENET_Type *ptr, rtl8201_config_t *config)
{
    uint16_t para = 0;

    para |= RTL8201_BMCR_RESET_SET(0)                        /* Normal operation */
         |  RTL8201_BMCR_LOOPBACK_SET(config->loopback)      /* configure PCS loopback mode */
         |  RTL8201_BMCR_ANE_SET(config->auto_negotiation)   /* configure Auto-Negotiation */
         |  RTL8201_BMCR_PWD_SET(0)                          /* Normal operation */
         |  RTL8201_BMCR_ISOLATE_SET(0)                      /* Normal operation */
         |  RTL8201_BMCR_RESTART_AN_SET(0)                   /* Normal operation (ignored when Auto-Negotiation is disabled) */
         |  RTL8201_BMCR_COLLISION_TEST_SET(0);              /* Normal operation */

    if (config->auto_negotiation == 0) {
        para |= RTL8201_BMCR_SPEED0_SET(config->speed) | RTL8201_BMCR_SPEED1_SET(config->speed >> 1);
    }

    /* check the id of rtl8201 */
    if (rtl8201_id_check(ptr) == false) {
        return false;
    }

    para = enet_read_phy(ptr, PHY_ADDR, RTL8201_REG_BMCR) & ~RTL8201_BMCR_SPEED0_MASK;
    enet_write_phy(ptr, PHY_ADDR, RTL8201_REG_BMCR, para);

    /* select page 7 */
    enet_write_phy(ptr, PHY_ADDR, 31, 7);
    para = enet_read_phy(ptr, PHY_ADDR, 16);
    para |= 1 << 12; /* set txc as input mode */
    enet_write_phy(ptr, PHY_ADDR, 16, para);

    return true;
}


void rtl8201_init_auto_negotiation(void)
{
}
