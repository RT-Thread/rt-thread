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
 * FilePath: fi2c.c
 * Date: 2021-11-01 14:53:42
 * LastEditTime: 2022-02-18 08:36:58
 * Description:  This file is for complete user external interface
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  zhugengyu 2021/11/1  first commit
 * 1.1  liushengming 2022/2/18  modified to support i2c
 */


/***************************** Include Files *********************************/
#include <string.h>
#include "fio.h"
#include "ferror_code.h"
#include "ftypes.h"
#include "fdebug.h"
#include "fi2c_hw.h"
#include "fi2c.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FI2C_DEBUG_TAG "I2C"
#define FI2C_ERROR(format, ...)   FT_DEBUG_PRINT_E(FI2C_DEBUG_TAG, format, ##__VA_ARGS__)
#define FI2C_INFO(format, ...)    FT_DEBUG_PRINT_I(FI2C_DEBUG_TAG, format, ##__VA_ARGS__)
#define FI2C_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FI2C_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/

static FError FI2cReset(FI2c *instance_p);

/************************** Variable Definitions *****************************/
static const char *FI2C_ERROR_CODE_MSG[FI2C_NUM_OF_ERR_CODE] =
{
    "FI2C_SUCCESS : fi2c success",
    "FI2C_ERR_INVAL_PARM : fi2c invalid input parameters",
    "FI2C_ERR_NOT_READY : fi2c driver is not ready",
    "FI2C_ERR_TIMEOUT : fi2c wait timeout",
    "FI2C_ERR_NOT_SUPPORT : fi2c not support operation",
    "FI2C_ERR_INVAL_STATE : fi2c invalid state"
};

/**
 * @name: FI2cCfgInitialize
 * @msg: 完成I2C驱动实例的初始化，使之可以使用
 * @param {FI2c} *instance_p I2C驱动实例数据
 * @param {FI2cConfig} *cofig_p I2C驱动配置数据
 * @return SUCCESS if initialization was successful
 *         ERROR
 */
FError FI2cCfgInitialize(FI2c *instance_p, const FI2cConfig *input_config_p)
{
    FASSERT(instance_p && input_config_p);

    FError ret = FI2C_SUCCESS;

    /*
        * If the device is started, disallow the initialize and return a Status
        * indicating it is started.  This allows the user to de-initialize the device
        * and reinitialize, but prevents a user from inadvertently
        * initializing.
    */
    if (FT_COMPONENT_IS_READY == instance_p->is_ready)
    {
        FI2C_ERROR("Device is already initialized!!!");
        return FI2C_ERR_INVAL_STATE;
    }

    /*
        * Set default values and configuration data, including setting the
        * callback handlers to stubs  so the system will not crash should the
        * application not assign its own callbacks.
     */
    FI2cDeInitialize(instance_p);
    instance_p->config = *input_config_p;

    /*
    * Reset the device.
    */
    ret = FI2cReset(instance_p);
    if (FI2C_SUCCESS == ret)
    {
        instance_p->is_ready = FT_COMPONENT_IS_READY;
    }

    return ret;
}

/**
 * @name: FI2cDeInitialize
 * @msg: 完成I2C驱动实例去使能，清零实例数据
 * @return {*}
 * @param {FI2c} *instance_p
 */
void FI2cDeInitialize(FI2c *instance_p)
{
    FASSERT(instance_p);
    instance_p->is_ready = 0;

    memset(instance_p, 0, sizeof(*instance_p));
}

/**
 * @name: FI2cReset
 * @msg: 重置I2C控制器
 * @return {*}
 * @param {FI2c} *instance_p, I2C驱动实例数据
 */
static FError FI2cReset(FI2c *instance_p)
{
    FASSERT(instance_p);

    FError ret = FI2C_SUCCESS;
    FI2cConfig *config_p = &instance_p->config;
    uintptr base_addr = config_p->base_addr;
    u32 reg_val = 0;

    ret = FI2cSetEnable(base_addr, FALSE); /* disable i2c ctrl */

    if (FI2C_MASTER == config_p->work_mode)
    {
        reg_val |= (config_p->use_7bit_addr) ? FI2C_CON_MASTER_ADR_7BIT : FI2C_CON_MASTER_ADR_10BIT ;
        reg_val |= FI2C_CON_SLAVE_DISABLE;
        reg_val |= FI2C_CON_MASTER_MODE;
        reg_val |= FI2C_CON_RESTART_EN;
    }
    else
    {
        reg_val |= (config_p->use_7bit_addr) ? FI2C_CON_SLAVE_ADR_7BIT : FI2C_CON_SLAVE_ADR_10BIT;
        reg_val &= (~FI2C_CON_MASTER_MODE);
        reg_val |= FI2C_CON_SLAVE_MODE;
    }
    reg_val |= FI2C_CON_STD_SPEED;

    FI2C_WRITE_REG32(base_addr, FI2C_CON_OFFSET, reg_val);
    FI2C_WRITE_REG32(base_addr, FI2C_RX_TL_OFFSET, 0);
    FI2C_WRITE_REG32(base_addr, FI2C_TX_TL_OFFSET, 0);
    FI2C_SET_INTRRUPT_MASK(base_addr, 0); /* disable all intr */

    ret = FI2cSetSpeed(base_addr, config_p->speed_rate);

    if (FI2C_SUCCESS == ret)
    {
        ret = FI2cSetEnable(base_addr, TRUE);    /* enable i2c ctrl */
    }

    /* if init successed, and i2c is in slave mode, set slave address */
    if ((FI2C_SUCCESS == ret) && (FI2C_SLAVE == config_p->work_mode))
    {
        ret = FI2cSetSar(base_addr, config_p->slave_addr);
    }

    return ret;
}

/**
 * @name: FI2cErrorToMessage
 * @msg: 获取I2C模块错误码对应的错误信息
 * @return {const char *}, 错误码信息，NULL表示失败
 * @param {FError} error, I2C输入错误码
 */
const char *FI2cErrorToMessage(FError error)
{
    const char *msg = NULL;
    if (FI2C_SUCCESS != error && (FI2C_ERR_CODE_PREFIX != error & (FT_ERRCODE_SYS_MODULE_MASK | FT_ERRCODE_SUB_MODULE_MASK)))
    {
        /* if input error do not belong to this module */
        return msg;
    }
    u32 index = error & FT_ERRCODE_TAIL_VALUE_MASK;

    if (index < FI2C_NUM_OF_ERR_CODE)
    {
        msg = FI2C_ERROR_CODE_MSG[index];
    }

    return msg;
}