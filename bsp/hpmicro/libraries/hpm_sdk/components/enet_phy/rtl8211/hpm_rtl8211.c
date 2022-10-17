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
#include "hpm_rtl8211_regs.h"
#include "hpm_rtl8211.h"
#include "board.h"

/*---------------------------------------------------------------------*
 * Interal API
 *---------------------------------------------------------------------*/
static bool rtl8211_id_check(ENET_Type *ptr)
{
    uint16_t id1, id2;

    id1 = enet_read_phy(ptr, PHY_ADDR, RTL8211_REG_PHYID1);
    id2 = enet_read_phy(ptr, PHY_ADDR, RTL8211_REG_PHYID2);

    if (RTL8211_PHYID1_OUI_MSB_GET(id1) == PHY_ID1 && RTL8211_PHYID2_OUI_MSB_GET(id2) == PHY_ID2) {
        return true;
    } else {
        return false;
    }
}

/*---------------------------------------------------------------------*
 * API
 *---------------------------------------------------------------------*/
uint16_t rtl8211_register_check(ENET_Type *ptr, uint32_t addr)
{
   return enet_read_phy(ptr, PHY_ADDR, addr);
}

void rtl8211_reset(ENET_Type *ptr)
{
    uint16_t data;

    /* PHY reset */
    enet_write_phy(ptr, PHY_ADDR, RTL8211_REG_BMCR, RTL8211_BMCR_RESET_SET(1));

    /* wait until the reset is completed */
    do {
        data = enet_read_phy(ptr, PHY_ADDR, RTL8211_REG_BMCR);
    } while (RTL8211_BMCR_RESET_GET(data));
}

void rtl8211_basic_mode_default_config(ENET_Type *ptr, rtl8211_config_t *config)
{
    config->loopback         = 0; /* Enable PCS loopback mode */
    config->speed            = 1; /* reserved:3/2; 100mbps: 1; 10mbps: 0 */
    config->auto_negotiation = 1; /* Enable Auto-Negotiation */
    config->duplex_mode      = 1; /* Full duplex mode */
}

bool rtl8211_basic_mode_init(ENET_Type *ptr, rtl8211_config_t *config)
{
    uint16_t para = 0;

    para |= RTL8211_BMCR_RESET_SET(0)                        /* Normal operation */
         |  RTL8211_BMCR_LOOPBACK_SET(config->loopback)      /* configure PCS loopback mode */
         |  RTL8211_BMCR_ANE_SET(config->auto_negotiation)   /* configure Auto-Negotiation */
         |  RTL8211_BMCR_PWD_SET(0)                          /* Normal operation */
         |  RTL8211_BMCR_ISOLATE_SET(0)                      /* Normal operation */
         |  RTL8211_BMCR_RESTART_AN_SET(0)                   /* Normal operation (ignored when Auto-Negotiation is disabled) */
         |  RTL8211_BMCR_COLLISION_TEST_SET(0);              /* Normal operation */

    if (config->auto_negotiation == 0) {
        para |= RTL8211_BMCR_SPEED0_SET(config->speed) | RTL8211_BMCR_SPEED1_SET(config->speed >> 1);
    }

    enet_write_phy(ptr, PHY_ADDR, RTL8211_REG_BMCR, para);

    /* check the id of rtl8211 */
    if (rtl8211_id_check(ptr) == false) {
        return false;
    }

    return true;
}

void rtl8211_auto_negotiation_init(void)
{
    /* TODO */
}


void rtl8211_read_status(ENET_Type *ptr)
{
    uint16_t status;

    status = enet_read_phy(ptr, PHY_ADDR,  RTL8211_REG_BMSR);
    printf("BMSR: %08x\n", status);
    status = enet_read_phy(ptr, PHY_ADDR,  RTL8211_REG_GBSR);
    printf("GBSR: %08x\n", status);
    status = enet_read_phy(ptr, PHY_ADDR,  RTL8211_REG_GBESR);
    printf("GBESR: %08x\n", status);
    status = enet_read_phy(ptr, PHY_ADDR,  RTL8211_REG_PHYSR);
    printf("PHYSR: %08x\n", status);
    status = enet_read_phy(ptr, PHY_ADDR,  RTL8211_REG_RXERC);
    printf("RXERC: %08x\n", status);

    status = enet_read_phy(ptr, PHY_ADDR, RTL8211_REG_PHYCR);
    printf("PHYCR, %x\n", status);
}

void rtl8211_control_config(ENET_Type *ptr)
{
    uint16_t para = 0;

    para = enet_read_phy(ptr, PHY_ADDR, RTL8211_REG_PHYCR) | (1 << 10);

    enet_write_phy(ptr, PHY_ADDR, RTL8211_REG_PHYCR, para);

}