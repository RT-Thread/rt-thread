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
 * FilePath: fgmac_ar803x.c
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file is for  ar803x PHYs chip
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2021/07/13    first release
 */


/***************************** Include Files *********************************/

#include "fio.h"
#include "ferror_code.h"
#include "ftypes.h"
#include "fdebug.h"

#include "fgmac_hw.h"
#include "fgmac.h"
#include "fgmac_ar803x.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FGMAC_DEBUG_TAG "FGMAC-AR803X"
#define FGMAC_ERROR(format, ...)   FT_DEBUG_PRINT_E(FGMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGMAC_WARN(format, ...)    FT_DEBUG_PRINT_W(FGMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGMAC_INFO(format, ...)    FT_DEBUG_PRINT_I(FGMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGMAC_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FGMAC_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/
/* write phy register */
extern FError FGmacWritePhyReg(FGmac *instance_p, u32 phy_address, u16 phy_reg, u16 phy_reg_val);
/* read phy register */
extern FError FGmacReadPhyReg(FGmac *instance_p, u32 phy_address, u16 phy_reg, u16 *phy_reg_val_p);


/************************** Variable Definitions *****************************/

/*****************************************************************************/

/* 此文件主要为了完成用户对外接口，用户可以使用这些接口直接开始工作 */

/* - 包括用户API的定义和实现
   - 同时包含必要的OPTION方法，方便用户进行配置
   - 如果驱动可以直接进行I/O操作，在此源文件下可以将API 进行实现 */


/**
 * @name: FGmacAr803xDebugRegRead
 * @msg: read phy debug register value
 * @param {FGmac} *instance_p, instance of FGmac controller
 * @param {u32} phy_address, phy address connect to fgmac
 * @param {u16} debug_reg, phy debug register offset to read
 * @param {u16} *reg_data_p, phy register value pointer
 * @return err code information, FGMAC_SUCCESS indicates success，others indicates failed
 */
static FError FGmacAr803xDebugRegRead(FGmac *instance_p, u32 phy_address, u16 debug_reg, u16 *reg_data_p)
{
    FASSERT(instance_p && reg_data_p);
    FError ret = FGMAC_SUCCESS;

    ret = FGmacWritePhyReg(instance_p, phy_address, FGMAC_AR803X_DEBUG_ADDR, debug_reg & FGMAC_AR803X_DEBUG_DATA_MASK);
    if (FGMAC_SUCCESS != ret)
    {
        return ret;
    }

    ret = FGmacReadPhyReg(instance_p, phy_address, FGMAC_AR803X_DEBUG_DATA, reg_data_p);
    return ret;
}

static FError FGmacAr803xMaskReg(FGmac *instance_p, u32 phy_address, u16 reg, u32 clear, u32 set)
{
    FASSERT(instance_p);
    FError ret = FGMAC_SUCCESS;
    u16 val = 0;

    ret = FGmacReadPhyReg(instance_p, phy_address, reg, &val);
    if (FGMAC_SUCCESS != ret)
    {
        return ret;
    }

    val &= ~clear;
    val |= set;

    ret = FGmacWritePhyReg(instance_p, phy_address, FGMAC_AR803X_DEBUG_DATA, val);
    return ret;
}

/**
 * @name: FGmacAr803xDisableHibernate
 * @msg: disable phy Power hibernate control
 * @param {FGmac} *instance_p, instance of FGmac controller
 * @return err code information, FGMAC_SUCCESS indicates success，others indicates failed
 */
FError FGmacAr803xDisableHibernate(FGmac *instance_p)
{
    FASSERT(instance_p);
    u32 ret = FGMAC_SUCCESS;
    u16 reg_val = 0;

    ret = FGmacAr803xDebugRegRead(instance_p, instance_p->phy_addr, FGMAC_AR803X_DEBUG_HIB_CTRL_REG, &reg_val);
    if (FGMAC_SUCCESS != ret)
    {
        return ret;
    }

    reg_val &= ~FGMAC_AR803X_PS_HIB_EN;
    ret = FGmacWritePhyReg(instance_p, instance_p->phy_addr, FGMAC_AR803X_DEBUG_DATA, reg_val);

    reg_val = 0;
    FGmacAr803xDebugRegRead(instance_p, instance_p->phy_addr, FGMAC_AR803X_DEBUG_HIB_CTRL_REG, &reg_val);
    FGMAC_INFO("Debug reg: 0x%lx, ret: 0x%lx", reg_val, ret);

    return ret;
}

/**
 * @name: FFmacAr803xRxClockDelayControl
 * @msg: control phy debug register0 for rx clock delay
 * @param {FGmac} *instance_p, instance of FGmac controller
 * @param {u32} enable_setting, 1-enable, else disable
 * @return err code information, FGMAC_SUCCESS indicates success，others indicates failed
 */
FError FFmacAr803xRxClockDelayControl(FGmac *instance_p, u32 enable_setting)
{
    FASSERT(instance_p);
    u32 ret = FGMAC_SUCCESS;
    u16 reg_val = 0;

    ret = FGmacAr803xDebugRegRead(instance_p, instance_p->phy_addr, FGMAC_AR803X_RX_CLOCK_CTRL_REG, &reg_val);
    if (FGMAC_SUCCESS != ret)
    {
        return ret;
    }

    if (enable_setting == FGMAC_RX_CLOCK_ENABLE)
    {
        reg_val |= FGMAC_AR803X_RX_CLOCK_DELAY;
    }
    else
    {
        reg_val &= ~FGMAC_AR803X_RX_CLOCK_DELAY;
    }

    ret = FGmacWritePhyReg(instance_p, instance_p->phy_addr, FGMAC_AR803X_DEBUG_DATA, reg_val);

    reg_val = 0;
    FGmacAr803xDebugRegRead(instance_p, instance_p->phy_addr, FGMAC_AR803X_RX_CLOCK_CTRL_REG, &reg_val);
    FGMAC_INFO("Debug reg: 0x%lx, ret: 0x%lx", reg_val, ret);

    return ret;
}

/**
 * @name: FFmacAr803xTxClockDelayControl
 * @msg: control phy debug register5 for tx clock delay
 * @param {FGmac} *instance_p, instance of FGmac controller
 * @param {u32} enable_setting, 1-enable, else disable
 * @return err code information, FGMAC_SUCCESS indicates success，others indicates failed
 */
FError FFmacAr803xTxClockDelayControl(FGmac *instance_p, u32 enable_setting)
{
    FASSERT(instance_p);
    u32 ret = FGMAC_SUCCESS;
    u16 reg_val = 0;

    ret = FGmacAr803xDebugRegRead(instance_p, instance_p->phy_addr, FGMAC_AR803X_TX_CLOCK_CTRL_REG, &reg_val);
    if (FGMAC_SUCCESS != ret)
    {
        return ret;
    }

    if (enable_setting == FGMAC_TX_CLOCK_ENABLE)
    {
        reg_val |= FGMAC_AR803X_TX_CLOCK_DELAY;
    }
    else
    {
        reg_val &= ~FGMAC_AR803X_TX_CLOCK_DELAY;
    }

    ret = FGmacWritePhyReg(instance_p, instance_p->phy_addr, FGMAC_AR803X_DEBUG_DATA, reg_val);

    reg_val = 0;
    FGmacAr803xDebugRegRead(instance_p, instance_p->phy_addr, FGMAC_AR803X_TX_CLOCK_CTRL_REG, &reg_val);
    FGMAC_INFO("Debug reg: 0x%lx, ret: 0x%lx", reg_val, ret);

    return ret;
}
