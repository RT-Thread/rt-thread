/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: fi2s.c
 * Created Date: 2023-05-09 17:23:55
 * Last Modified: 2023-09-14 15:09:01
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------  -------- --------------------------------------
 *  1.0  Wangzq     2023/05/09  Modify the format and establish the version
 */

/***************************** Include Files *********************************/
#include <string.h>
#include <stdio.h>
#include "ftypes.h"
#include "fassert.h"
#include "fdrivers_port.h"
#include "ferror_code.h"
#include "fi2s_hw.h"
#include "fi2s.h"

#define FI2S_DEBUG_TAG "I2S"
#define FI2S_ERROR(format, ...) FT_DEBUG_PRINT_E(FI2S_DEBUG_TAG, format, ##__VA_ARGS__)
#define FI2S_INFO(format, ...) FT_DEBUG_PRINT_I(FI2S_DEBUG_TAG, format, ##__VA_ARGS__)
#define FI2S_DEBUG(format, ...) FT_DEBUG_PRINT_D(FI2S_DEBUG_TAG, format, ##__VA_ARGS__)

/**
 * @name: FI2sCfgInitialize
 * @msg:  init the config of i2s
 * @param (FI2s *} instance :the instance_p of  i2s
 * @param (const FI2sConfig *} config_p : the config  of  i2s
 * @return ret: 0:FI2S_SUCCESS,other:failed
 */
FError FI2sCfgInitialize(FI2s *instance, const FI2sConfig *config_p)
{
    FASSERT(instance && config_p);
    FError ret = FI2S_SUCCESS;
    u32 reg;
    if (FT_COMPONENT_IS_READY == instance->is_ready)
    {
        FI2S_ERROR("Device is already initialized!!!");
        return FI2S_ERR_NOT_INIT;
    }
    /*set the instance*/
    instance->config = *config_p;
    /*disble the all channel*/
    FI2sChannelDisable(instance);
    /*disable the transmmit core*/
    FI2sTxRxEnable(instance, FALSE);
    /*set the hw config*/
    FI2sSetHwconfig(instance);

    instance->is_ready = FT_COMPONENT_IS_READY;

    return ret;
}

/**
 * @name: FI2sChannelDisable
 * @msg:  diable the all channel
 * @param (FI2s *} instance_p :the instance_p of  i2s
 * @return null
 */
void FI2sChannelDisable(FI2s *instance)
{
    FASSERT(instance != NULL);
    u32 reg;

    for (int i = 0; i < 4; i++)
    {
        reg = FI2S_READ_REG32(instance->config.base_addr, FI2S_TER0(i));
        reg &= ~ FI2S_TER0_CTRL;
        FI2S_WRITE_REG32(instance->config.base_addr, FI2S_TER0(i), reg);

        reg = FI2S_READ_REG32(instance->config.base_addr, FI2S_RER0(i));
        reg &= ~ FI2S_RER0_CTRL;
        FI2S_WRITE_REG32(instance->config.base_addr, FI2S_RER0(i), reg);
    }
    return;
}

/**
 * @name: FI2sSetHwconfig
 * @msg:  set the hw config
 * @param (FI2s *} instance_p :the instance_p of  i2s
 * @return null
 */
void FI2sSetHwconfig(FI2s *instance)
{
    FASSERT(instance != NULL);
    switch (instance->data_config.word_length)
    {
        case FI2S_WORLD_LENGTH_16:
            instance->data_config.resolution = 0x02;
            break;
        case FI2S_WORLD_LENGTH_24:
            instance->data_config.resolution = 0x04;
            break;
        case FI2S_WORLD_LENGTH_32:
            instance->data_config.resolution = 0x05;
            break;
        default:
            instance->data_config.resolution = 0x02;
            break;
    }
    if (instance->data_config.work_mode == FI2S_CAPTURE)
    {
        FI2S_WRITE_REG32(instance->config.base_addr, FI2S_RCR0(0), instance->data_config.resolution);/*设置字长*/
    }
    else
    {
        FI2S_WRITE_REG32(instance->config.base_addr, FI2S_TCR0(0), instance->data_config.resolution);/*设置字长*/
    }
}

/**
 * @name: FI2sTxRxEnable
 * @msg:  enables/disables the i2s driver
 * @param (FI2s *} instance :the instance of i2s
 * @param (boolean} enable : TRUE/FALSE value to either enable or disable
 * @return null
 */
void FI2sTxRxEnable(FI2s *instance, boolean enable)
{
    FASSERT(instance != NULL);
    u32 reg;
    if (enable)
    {
        if (instance->data_config.work_mode == FI2S_CAPTURE)
        {
            FI2sRxHwEnable(instance);
        }
        else
        {
            FI2sTxHwEnable(instance);
        }
    }
    else
    {
        reg = FI2S_READ_REG32(instance->config.base_addr, FI2S_IER);
        reg &= ~FI2S_IER_CTRL;
        FI2S_WRITE_REG32(instance->config.base_addr, FI2S_IER, reg);

    }
    /*i2s instance enable */
    reg = FI2S_READ_REG32(instance->config.base_addr, FI2S_IER);
    reg |= FI2S_IER_CTRL;
    FI2S_WRITE_REG32(instance->config.base_addr, FI2S_IER, reg);
    return;
}

/**
 * @name: FI2sRxHwEnable
 * @msg:  enables i2s receiver and set the hw config
 * @param (FI2s *} instance :the instance of i2s
 * @return null
 */
void FI2sRxHwEnable(FI2s *instance)
{
    FASSERT(instance != NULL);
    u32 reg;
    /* enale the rx module of channel*/
    reg = FI2S_READ_REG32(instance->config.base_addr, FI2S_RER0(0));
    reg |= FI2S_RER0_CTRL;
    FI2S_WRITE_REG32(instance->config.base_addr, FI2S_RER0(0), reg);

    /*enable the rx channel of the i2s*/
    reg = FI2S_READ_REG32(instance->config.base_addr, FI2S_IRER);
    reg |= FI2S_IRER_CTRL;
    FI2S_WRITE_REG32(instance->config.base_addr, FI2S_IRER, reg);

    return;
}

/**
 * @name: FI2sTxHwEnable
 * @msg:  enables i2s playbacker and set the hw config
 * @param (FI2s *} instance :the instance of i2s
 * @return null
 */
void FI2sTxHwEnable(FI2s *instance)
{
    FASSERT(instance != NULL);
    u32 reg;
    /* enale the rx module of channel*/
    reg = FI2S_READ_REG32(instance->config.base_addr, FI2S_TER0(0));
    reg |= FI2S_TER0_CTRL;
    FI2S_WRITE_REG32(instance->config.base_addr, FI2S_TER0(0), reg);
    /*enable the rx channel of the i2s*/
    reg = FI2S_READ_REG32(instance->config.base_addr, FI2S_ITER);
    reg |= FI2S_ITER_CTRL;
    FI2S_WRITE_REG32(instance->config.base_addr, FI2S_ITER, reg);

    return;
}

/**
 * @name: FI2sDeInitialize
 * @msg:  deinit the config of i2s
 * @param (FI2s *} instance :the instance_p of  i2s
 * @return Null
 */
void FI2sDeInitialize(FI2s *instance)
{
    FASSERT(instance != NULL);
    instance->is_ready = 0;
    memset(instance, 0, sizeof(*instance));
}

/**
 * @name: FI2sClkOutDiv
 * @msg:  this function calculates the SCLK Output divider value of the i2s
 * @param (FI2s *} instance :the instance_p of  i2s
 * @return Null
 */
FError FI2sClkOutDiv(FI2s *instance)
{
    FASSERT(instance != NULL);
    FError ret = FI2S_SUCCESS;
    u64 fix, point;
    u32 reg, cfg;

    instance->data_config.sample_rate = FI2S_SAMPLE_RATE_CD;

    switch (instance->data_config.word_length)
    {
        case FI2S_WORLD_LENGTH_16:
            instance->data_config.data_length = 16;
            FI2S_WRITE_REG32(instance->config.base_addr, FI2S_CCR, 0x0);
            break;
        case FI2S_WORLD_LENGTH_24:
            instance->data_config.data_length = 24;
            FI2S_WRITE_REG32(instance->config.base_addr, FI2S_CCR, 0x08);
            break;
        case FI2S_WORLD_LENGTH_32:
            instance->data_config.data_length = 32;
            FI2S_WRITE_REG32(instance->config.base_addr, FI2S_CCR, 0x10);
            break;
        default:
            instance->data_config.data_length = 16;
            FI2S_WRITE_REG32(instance->config.base_addr, FI2S_CCR, 0x0);
            break;
    }
    fix = FI2s_Clk_Base / instance->data_config.sample_rate / instance->data_config.data_length / 32;
    point = (FI2s_Clk_Base / instance->data_config.sample_rate) << 10 / instance->data_config.data_length / 32;
    point = (point - (fix << 10)) * 10;
    cfg = ((u16) fix << 16) | (u16) point;

    /* set the sclk and mclk*/
    FI2S_WRITE_REG32(instance->config.base_addr, FI2S_FRAC_DIV, cfg);
    FI2S_WRITE_REG32(instance->config.base_addr, FI2S_EVEN_DIV, 0xf);

    /*enable the i2s clk*/
    reg = FI2S_READ_REG32(instance->config.base_addr, FI2S_CER);
    reg |= FI2S_CER_CTRL;
    FI2S_WRITE_REG32(instance->config.base_addr, FI2S_CER, reg);

    return FI2S_SUCCESS;
}

/**
 * @name: FI2sEnableIrq
 * @msg:  enable i2s irq
 * @param (uintptr} base_addr  :the base address of i2s instance
 * @param (u32} id  :the i2s number
 * @param (u32} event_type : the type  of  intr
 * @return null
 */
void FI2sEnableIrq(FI2s *instance, u32 event_type)
{
    uintptr base_addr = instance->config.base_addr;
    u32 reg_val = FI2S_READ_REG32(base_addr, FI2S_IMR0(0));
    switch (event_type)
    {
        case FI2S_INTR_TRANS_FO:
            reg_val &= ~ FI2S_INTR_TRANS_FO_MASK;
            break;
        case FI2S_INTR_TRANS_FE:
            reg_val &= ~  FI2S_INTR_TRANS_FE_MASK;
            break;
        case FI2S_INTR_RECEIVE_FO:
            reg_val &= ~ FI2S_INTR_RECRIVE_FO_MASK;
            break;
        case FI2S_INTR_RECEIVE_FE:
            reg_val &= ~ FI2S_INTR_RECRIVE_FE_MASK;
            break;
        default:
            break;
    }
    FI2S_WRITE_REG32(base_addr, FI2S_IMR0(0), reg_val);
    return ;
}

/**
 * @name: FI2sEnableIrq
 * @msg:  disable i2s irq
 * @param (uintptr} base_addr  :the base address of i2s instance
 * @param (u32} id  :the i2s number
 * @param (u32} event_type : the type  of  intr
 * @return null
 */
void FI2sDisableIrq(FI2s *instance,  u32 event_type)
{
    uintptr base_addr = instance->config.base_addr;
    u32 reg_val = FI2S_READ_REG32(base_addr, FI2S_IMR0(0));
    switch (event_type)
    {
        case FI2S_INTR_TRANS_FO:
            reg_val |= FI2S_INTR_TRANS_FO_MASK;
            break;
        case FI2S_INTR_TRANS_FE:
            reg_val |= FI2S_INTR_TRANS_FE_MASK;
            break;
        case FI2S_INTR_RECEIVE_FO:
            reg_val |= FI2S_INTR_RECRIVE_FO_MASK;
            break;
        case FI2S_INTR_RECEIVE_FE:
            reg_val |= FI2S_INTR_RECRIVE_FE_MASK;
            break;
        default:
            break;
    }
    FI2S_WRITE_REG32(base_addr, FI2S_IMR0(0), reg_val);
    return ;
}

/**
 * @name: FI2sStopWork
 * @msg:  stop the i2s
 * @param (FI2s *} instance_p :the instance_p of  i2s
 * @return Null
 */
void FI2sStopWork(FI2s *instance_p)
{
    FASSERT(instance_p != NULL);
    u32 reg;

    if (instance_p->data_config.work_mode == FI2S_PALYBACK)
    {
        reg = FI2S_READ_REG32(instance_p->config.base_addr, FI2S_ITER);
        reg &= ~ FI2S_ITER_CTRL;
        FI2S_WRITE_REG32(instance_p->config.base_addr, FI2S_ITER, reg);
    }
    else
    {
        reg = FI2S_READ_REG32(instance_p->config.base_addr, FI2S_IRER);
        reg &= ~ FI2S_IRER_CTRL;
        FI2S_WRITE_REG32(instance_p->config.base_addr, FI2S_IRER, reg);
    }

    reg = FI2S_READ_REG32(instance_p->config.base_addr, FI2S_CER);
    reg &= ~FI2S_CER_CTRL;
    FI2S_WRITE_REG32(instance_p->config.base_addr, FI2S_CER, reg);

    reg = FI2S_READ_REG32(instance_p->config.base_addr, FI2S_IER);
    reg &= ~FI2S_IER_CTRL;
    FI2S_WRITE_REG32(instance_p->config.base_addr, FI2S_IER, reg);

    return ;
}







