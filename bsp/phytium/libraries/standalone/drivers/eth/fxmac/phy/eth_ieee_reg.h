/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: eth_ieee_reg.h
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file is for phys chip register definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/06/16    first release
 */

#ifndef ETH_IEEE_REG_H
#define ETH_IEEE_REG_H

/***************************** Include Files *********************************/
#include "ferror_code.h"

#ifdef __cplusplus
extern "C"
{
#endif

/***************** Macros (Inline Functions) Definitions *********************/

#define PHY_CONTROL_REG_OFFSET 0
#define PHY_STATUS_REG_OFFSET 1
#define PHY_IDENTIFIER_1_REG 2
#define PHY_IDENTIFIER_2_REG 3
#define PHY_AUTONEGO_ADVERTISE_REG 4
#define PHY_PARTNER_ABILITIES_1_REG_OFFSET 5
#define PHY_PARTNER_ABILITIES_2_REG_OFFSET 8
#define PHY_PARTNER_ABILITIES_3_REG_OFFSET 10
#define PHY_1000_ADVERTISE_REG_OFFSET 9
#define PHY_MMD_ACCESS_CONTROL_REG 13
#define PHY_MMD_ACCESS_ADDRESS_DATA_REG 14
#define PHY_SPECIFIC_STATUS_REG 17

#define PHY_CONTROL_FULL_DUPLEX_MASK 0x0100
#define PHY_CONTROL_LINKSPEED_MASK 0x0040
#define PHY_CONTROL_LINKSPEED_1000M 0x0040
#define PHY_CONTROL_LINKSPEED_100M 0x2000
#define PHY_CONTROL_LINKSPEED_10M 0x0000
#define PHY_CONTROL_RESET_MASK 0x8000

#define PHY_CONTROL_AUTONEGOTIATE_ENABLE 0x1000
#define PHY_CONTROL_AUTONEGOTIATE_RESTART 0x0200

#define PHY_STATUS_AUTONEGOTIATE_COMPLETE 0x0020
#define PHY_STAT_LINK_STATUS              0x0004

#define PHY_AUTOADVERTISE_ASYMMETRIC_PAUSE_MASK 0x0800
#define PHY_AUTOADVERTISE_PAUSE_MASK 0x0400
#define PHY_AUTOADVERTISE_AUTONEG_ERROR_MASK 0x8000

/* Advertisement control register. */
#define PHY_AUTOADVERTISE_10HALF 0x0020        /* Try for 10mbps half-duplex  */
#define PHY_AUTOADVERTISE_1000XFULL 0x0020     /* Try for 1000BASE-X full-duplex */
#define PHY_AUTOADVERTISE_10FULL 0x0040        /* Try for 10mbps full-duplex  */
#define PHY_AUTOADVERTISE_1000XHALF 0x0040     /* Try for 1000BASE-X half-duplex */
#define PHY_AUTOADVERTISE_100HALF 0x0080       /* Try for 100mbps half-duplex */
#define PHY_AUTOADVERTISE_1000XPAUSE 0x0080    /* Try for 1000BASE-X pause    */
#define PHY_AUTOADVERTISE_100FULL 0x0100       /* Try for 100mbps full-duplex */
#define PHY_AUTOADVERTISE_1000XPSE_ASYM 0x0100 /* Try for 1000BASE-X asym pause */
#define PHY_AUTOADVERTISE_100BASE4 0x0200      /* Try for 100mbps 4k packets  */

#define PHY_AUTOADVERTISE_100_AND_10 (PHY_AUTOADVERTISE_10FULL | PHY_AUTOADVERTISE_100FULL | \
                                      PHY_AUTOADVERTISE_10HALF | PHY_AUTOADVERTISE_100HALF)
#define PHY_AUTOADVERTISE_100 (PHY_AUTOADVERTISE_100FULL | PHY_AUTOADVERTISE_100HALF)
#define PHY_AUTOADVERTISE_10 (PHY_AUTOADVERTISE_10FULL | PHY_AUTOADVERTISE_10HALF)

#define PHY_AUTOADVERTISE_1000 0x0300

#define PHY_SPECIFIC_STATUS_SPEED_1000M (2L << 14)
#define PHY_SPECIFIC_STATUS_SPEED_100M (1L << 14)
#define PHY_SPECIFIC_STATUS_SPEED_0M (0L << 14)

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

typedef FError(*EthPhyWrite)(void *instance_p, u32 phy_address, u32 phy_reg_offset, u16 phy_data);
typedef FError(*EthPhyRead)(void *instance_p, u32 phy_address, u32 phy_reg_offset, u16 *phy_data_p);

/************************** Variable Definitions *****************************/

/************************** Function Prototypes ******************************/

#ifdef __cplusplus
}
#endif

#endif // !
