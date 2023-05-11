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
 * FilePath: phy_yt.h
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file is for yt PHYs chip.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/06/16    first release
 */

#ifndef PHY_YT_H
#define PHY_YT_H

#include "ferror_code.h"
#include "eth_ieee_reg.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define FETH_PHY_ERR_READ FT_MAKE_ERRCODE(ErrModBsp, ErrEthPhy, 0x1u)

FError PhyYtSetLoopBack(void *instance_p, u32 phy_addr, EthPhyWrite write_p, EthPhyRead read_p);
FError PhyYtCheckConnectStatus(void *instance_p, u32 phy_addr, EthPhyWrite write_p, EthPhyRead read_p);
FError PhyChangeModeToSds(void *instance_p, u32 phy_addr, EthPhyWrite write_p, EthPhyRead read_p);
FError PhyChangeModeToSgmii(void *instance_p, u32 phy_addr, EthPhyWrite write_p, EthPhyRead read_p);

#ifdef __cplusplus
}
#endif

#endif // !