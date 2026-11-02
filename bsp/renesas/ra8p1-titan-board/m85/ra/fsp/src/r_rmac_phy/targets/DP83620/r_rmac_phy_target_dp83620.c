/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/

/* Access to peripherals and board defines. */
#include "bsp_api.h"
#include "r_rmac_phy.h"

#if (ETHER_PHY_CFG_TARGET_DP83620_ENABLE)

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/* Vendor Specific PHY Registers */
 #define RMAC_PHY_REG_PAGE_SELECT    (0x13)
 #define RMAC_PHY_REG_14H            (0x14)

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global function
 ***********************************************************************************************************************/
void rmac_phy_target_dp83620_initialize(rmac_phy_instance_ctrl_t * p_instance_ctrl);
bool rmac_phy_target_dp83620_is_support_link_partner_ability(rmac_phy_instance_ctrl_t * p_instance_ctrl,
                                                             uint32_t                   line_speed_duplex);

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: rmac_phy_targets_initialize
 * Description  : PHY-LSI specific initialization processing
 * Arguments    : p_api_ctrl -
 *                    Ethernet channel number
 * Return Value : none
 ***********************************************************************************************************************/
void rmac_phy_target_dp83620_initialize (rmac_phy_instance_ctrl_t * p_instance_ctrl)
{
    uint32_t reg;

    if (ETHER_PHY_MII_TYPE_RMII == p_instance_ctrl->p_ether_phy_cfg->mii_type)
    {
        /*
         * The following is the recommended settings for TI to output 50 MHz from CLK_OUT when using Texas Instruments DP83620
         * in RMII master mode.
         */
        R_RMAC_PHY_Write(p_instance_ctrl, RMAC_PHY_REG_PAGE_SELECT, 0x0006);
        R_RMAC_PHY_Read(p_instance_ctrl, RMAC_PHY_REG_14H, &reg);
        if (0x800A == reg)
        {
            R_RMAC_PHY_Write(p_instance_ctrl, RMAC_PHY_REG_14H, 0x000A);
            R_RMAC_PHY_Write(p_instance_ctrl, RMAC_PHY_REG_PAGE_SELECT, 0x0000);
        }
    }
}                                      /* End of function rmac_phy_targets_initialize() */

/***********************************************************************************************************************
 * Function Name: rmac_phy_targets_is_support_link_partner_ability
 * Description  : Check if the PHY-LSI connected Ethernet controller supports link ability
 * Arguments    : p_instance_ctrl -
 *                    Ethernet control block
 *                line_speed_duplex -
 *                    Line speed duplex of link partner PHY-LSI
 * Return Value : bool
 ***********************************************************************************************************************/
bool rmac_phy_target_dp83620_is_support_link_partner_ability (rmac_phy_instance_ctrl_t * p_instance_ctrl,
                                                              uint32_t                   line_speed_duplex)
{
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(line_speed_duplex);

    /* This PHY-LSI supports half and full duplex mode. */
    return true;
}                                      /* End of function rmac_phy_targets_is_support_link_partner_ability() */

#endif /* ETHER_PHY_CFG_TARGET_DP83620_ENABLE */
