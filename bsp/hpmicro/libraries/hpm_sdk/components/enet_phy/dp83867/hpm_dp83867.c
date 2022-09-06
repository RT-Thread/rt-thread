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
#include "hpm_dp83867_regs.h"
#include "hpm_dp83867.h"
#include "board.h"

/*---------------------------------------------------------------------*
 * Interal API
 *---------------------------------------------------------------------*/
bool dp83867_id_check(ENET_Type *ptr)
{
    uint16_t id1, id2;

    id1 = enet_read_phy(ptr, PHY_ADDR, DP83867_REG_PHYID1);
    id2 = enet_read_phy(ptr, PHY_ADDR, DP83867_REG_PHYID2);

    if (DP83867_PHYID1_OUI_MSB_GET(id1) == PHY_ID1 && DP83867_PHYID2_OUI_MSB_GET(id2) == PHY_ID2) {
        return true;
    } else {
        return false;
    }
}

static void dp83867_phy_write_ext(ENET_Type *ptr, uint32_t phy_addr, uint32_t addr, uint32_t data)
{
    /* set the control register for register address */
    enet_write_phy(ptr, phy_addr, DP83867_EXT_REG_REGCR, DP83867_REGCR_FUNCTION_ADDR | DP83867_REGCR_DEVAD);

    /* write the specified register address */
    enet_write_phy(ptr, phy_addr, DP83867_EXT_REG_ADDAR, addr);

    /* set the control register for register data */
    enet_write_phy(ptr, phy_addr, DP83867_EXT_REG_REGCR, DP83867_REGCR_FUNCTION_DATA | DP83867_REGCR_DEVAD);

    /* write the specified register data */
    enet_write_phy(ptr, phy_addr, DP83867_EXT_REG_ADDAR, data);
}

static uint16_t dp83867_phy_read_ext(ENET_Type *ptr, uint32_t phy_addr, uint32_t addr)
{
    /* set the control register for register address */
    enet_write_phy(ptr, phy_addr, DP83867_EXT_REG_REGCR, DP83867_REGCR_FUNCTION_ADDR | DP83867_REGCR_DEVAD);

    /* write the specified register address */
    enet_write_phy(ptr, phy_addr, DP83867_EXT_REG_ADDAR, addr);

    /* set the control register for register data */
    enet_write_phy(ptr, phy_addr, DP83867_EXT_REG_REGCR, DP83867_REGCR_FUNCTION_DATA | DP83867_REGCR_DEVAD);

    /* read the specified register data */
    return enet_read_phy(ptr, phy_addr, DP83867_EXT_REG_ADDAR);
}
/*---------------------------------------------------------------------*
 * API
 *---------------------------------------------------------------------*/
uint16_t DP83867_REGister_check(ENET_Type *ptr, uint32_t addr)
{
   return enet_read_phy(ptr, PHY_ADDR, addr);
}

void dp83867_reset(ENET_Type *ptr)
{
    uint16_t data;

    /* PHY reset */
    enet_write_phy(ptr, PHY_ADDR, DP83867_REG_BMCR, DP83867_BMCR_RESET_SET(1));

    /* wait until the reset is completed */
    do {
        data = enet_read_phy(ptr, PHY_ADDR, DP83867_REG_BMCR);
    } while (DP83867_BMCR_RESET_GET(data));
}

void dp83867_basic_mode_default_config(ENET_Type *ptr, dp83867_config_t *config)
{
    config->loopback         = 0; /* Enable PCS loopback mode */
    config->speed            = 2; /* 3: reserved; 2: 1000mbps; 1: 100mbps; 0: 10mbps */
    config->auto_negotiation = 1; /* Enable Auto-Negotiation */
    config->duplex_mode      = 1; /* Full duplex mode */
}

bool dp83867_basic_mode_init(ENET_Type *ptr, dp83867_config_t *config)
{
    uint16_t para = 0;

    para |= DP83867_BMCR_RESET_SET(0)                        /* Normal operation */
         |  DP83867_BMCR_LOOPBACK_SET(config->loopback)      /* Configure PCS loopback mode */
         |  DP83867_BMCR_ANE_SET(config->auto_negotiation)   /* Configure Auto-Negotiation */
         |  DP83867_BMCR_PWD_SET(0)                          /* Normal operation */
         |  DP83867_BMCR_ISOLATE_SET(0)                      /* Normal operation */
         |  DP83867_BMCR_RESTART_AN_SET(0)                   /* Normal operation (ignored when Auto-Negotiation is disabled) */
         |  DP83867_BMCR_DUPLEX_SET(config->duplex_mode)     /* Config duplex mode */
         |  DP83867_BMCR_COLLISION_TEST_SET(0);              /* Normal operation */

    if (config->auto_negotiation == false) {
        para |= DP83867_BMCR_SPEED0_SET(config->speed) | DP83867_BMCR_SPEED1_SET(config->speed >> 1);
    }

    /* check the id of dp83867 */
    if (dp83867_id_check(ptr) == false) {
        return false;
    }

    while (dp83867_get_phy_link_status(ptr) == 0) {

    }

    return true;
}

void dp83867_init_auto_negotiation(void)
{

}

uint16_t dp83867_get_phy_link_status(ENET_Type *ptr)
{
    return DP83867_BMSR_LINK_STATUS_GET(enet_read_phy(ptr, PHY_ADDR, DP83867_REG_BMSR));
}

void dp83867_set_rgmii_rx_delay(ENET_Type *ptr, uint32_t phy_addr, uint8_t delay)
{
    dp83867_phy_write_ext(ptr, phy_addr, DP83867_EXT_REG_RGMIIDCTL, delay);
}

uint16_t dp83867_get_rgmii_rx_delay(ENET_Type *ptr, uint32_t phy_addr)
{
    uint16_t temp = 0;

    temp = dp83867_phy_read_ext(ptr, phy_addr, DP83867_EXT_REG_RGMIIDCTL);

    return temp;
}

void dp83867_set_rx_clk_delay(ENET_Type *ptr)
{
    uint16_t para = 0;

    para = dp83867_phy_read_ext(ptr, PHY_ADDR, DP83867_EXT_REG_RGMIICTL);
    dp83867_phy_write_ext(ptr, PHY_ADDR, DP83867_EXT_REG_RGMIICTL, para | 1);
}

void dp83867_enable_crc_check(ENET_Type *ptr)
{
    uint16_t para = 0;

    para = dp83867_phy_read_ext(ptr, PHY_ADDR, DP83867_EXT_REG_RXFCFG);
    dp83867_phy_write_ext(ptr, PHY_ADDR, DP83867_EXT_REG_RXFCFG, para | (1 << 7));
}

void dp83867_enable_rmii_inf(ENET_Type *ptr)
{
    uint16_t para = 0;

    para = dp83867_phy_read_ext(ptr, PHY_ADDR, DP83867_EXT_REG_RGMIICTL);
    dp83867_phy_write_ext(ptr, PHY_ADDR, DP83867_EXT_REG_RGMIICTL, para | (1 << 7));
}
