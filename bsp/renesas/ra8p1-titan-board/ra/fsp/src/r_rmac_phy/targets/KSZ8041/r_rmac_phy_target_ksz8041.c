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

#if (ETHER_PHY_CFG_TARGET_KSZ8041_ENABLE)

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/* Vendor Specific PHY Registers */
 #define RMAC_PHY_REG_PHY_CONTROL_1                    (0x1E)

 #define ETHER_PHY_LED_MODE_LED0_LINK_LED1_ACTIVITY    (0x4000U)
 #define ETHER_PHY_LED_MODE_MASK                       (0xC000U)

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global function
 ***********************************************************************************************************************/
void rmac_phy_target_ksz8041_initialize(rmac_phy_instance_ctrl_t * p_instance_ctrl);
bool rmac_phy_target_ksz8041_is_support_link_partner_ability(rmac_phy_instance_ctrl_t * p_instance_ctrl,
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
void rmac_phy_target_ksz8041_initialize (rmac_phy_instance_ctrl_t * p_instance_ctrl)
{
    uint32_t reg;

    /*
     * When KSZ8041NL of the Micrel, Inc. is used,
     * the pin that outputs the state of LINK is used combinedly with ACTIVITY in default.
     * The setting of the pin is changed so that only the state of LINK is output.
     */
    R_RMAC_PHY_Read(p_instance_ctrl, RMAC_PHY_REG_PHY_CONTROL_1, &reg);
    reg &= ~ETHER_PHY_LED_MODE_MASK;
    reg |= ETHER_PHY_LED_MODE_LED0_LINK_LED1_ACTIVITY;
    R_RMAC_PHY_Write(p_instance_ctrl, RMAC_PHY_REG_PHY_CONTROL_1, reg);
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
bool rmac_phy_target_ksz8041_is_support_link_partner_ability (rmac_phy_instance_ctrl_t * p_instance_ctrl,
                                                              uint32_t                   line_speed_duplex)
{
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(line_speed_duplex);

    /* This PHY-LSI supports half and full duplex mode. */
    return true;
}                                      /* End of function rmac_phy_targets_is_support_link_partner_ability() */

#endif /* ETHER_PHY_CFG_TARGET_KSZ8041_ENABLE */
