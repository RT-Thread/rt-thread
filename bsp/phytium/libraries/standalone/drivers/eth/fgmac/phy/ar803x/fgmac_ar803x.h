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
 * FilePath: fgmac_ar803x.h
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file is for This file is for  ar803x PHYs chip
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2021/07/13    first release
 */


#ifndef  FGMAC_AR803X_H
#define  FGMAC_AR803X_H

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fassert.h"
#include "fgmac_phy.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/

/* phy id */
#define FGMAC_AR803X_PHY_ID1             0x4D  /*803xPhy芯片 id1值为4d   8035芯片 id1 为0x004d  id2 为0xd072 */
#define FGMAC_AR803X_PHY_ID2             0x4D

/* address and data port */
#define FGMAC_AR803X_DEBUG_ADDR         0x1DU
#define FGMAC_AR803X_DEBUG_DATA         0x1EU

/* debug register offset */
#define FGMAC_AR803X_DEBUG_HIB_CTRL_REG  0xBU
#define FGMAC_AR803X_RX_CLOCK_CTRL_REG   0x0U
#define FGMAC_AR803X_TX_CLOCK_CTRL_REG   0x5U

#define FGMAC_AR803X_DEBUG_DATA_MASK    GENMASK(5, 0)

/* rx clock delay setting */
#define FGMAC_RX_CLOCK_ENABLE   1
#define FGMAC_RX_CLOCK_DISABLE   0

/* tx clock delay setting */
#define FGMAC_TX_CLOCK_ENABLE   1
#define FGMAC_TX_CLOCK_DISABLE   0

/* hib ctrl and auto-negotiation register */
#define FGMAC_AR803X_PS_HIB_EN           BIT(15)

#define FGMAC_AR803X_RX_CLOCK_DELAY      BIT(15)
#define FGMAC_AR803X_TX_CLOCK_DELAY      BIT(8)

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/* disable phy Power hibernate control */
FError FGmacAr803xDisableHibernate(FGmac *instance_p);

/* control phy debug register0 for rx clock delay */
FError FFmacAr803xRxClockDelayControl(FGmac *instance_p, u32 enable_setting);

/* control phy debug register5 for tx clock delay */
FError FFmacAr803xTxClockDelayControl(FGmac *instance_p, u32 enable_setting);

#ifdef __cplusplus
}
#endif


#endif
