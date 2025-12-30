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

#if (ETHER_PHY_CFG_TARGET_GPY111_ENABLE)

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
 #define RMAC_PHY_REG_MIICTRL                     (0x17U)
 #define RMAC_PHY_REG_MIICTRL_RXSKEW_MASK         (0x7000U)
 #define RMAC_PHY_REG_MIICTRL_RXSKEW_VALUE_1NS    (0x2000U)

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/* Vendor Specific PHY Registers */

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global function
 ***********************************************************************************************************************/
void rmac_phy_target_gpy111_initialize(rmac_phy_instance_ctrl_t * p_instance_ctrl);
bool rmac_phy_target_gpy111_is_support_link_partner_ability(rmac_phy_instance_ctrl_t * p_instance_ctrl,
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
void rmac_phy_target_gpy111_initialize (rmac_phy_instance_ctrl_t * p_instance_ctrl)
{
    uint32_t reg;

    /* Set RGMII receive timing skew to 1.0 ns. */
    R_RMAC_PHY_Read(p_instance_ctrl, RMAC_PHY_REG_MIICTRL, &reg);
    reg = (reg & ~RMAC_PHY_REG_MIICTRL_RXSKEW_MASK) | RMAC_PHY_REG_MIICTRL_RXSKEW_VALUE_1NS;
    R_RMAC_PHY_Write(p_instance_ctrl, RMAC_PHY_REG_MIICTRL, reg);
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
bool rmac_phy_target_gpy111_is_support_link_partner_ability (rmac_phy_instance_ctrl_t * p_instance_ctrl,
                                                             uint32_t                   line_speed_duplex)
{
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(line_speed_duplex);

    /* This PHY-LSI supports half and full duplex mode. */
    return true;
}                                      /* End of function rmac_phy_targets_is_support_link_partner_ability() */

#endif /* ETHER_PHY_CFG_TARGET_GPY111_ENABLE */
