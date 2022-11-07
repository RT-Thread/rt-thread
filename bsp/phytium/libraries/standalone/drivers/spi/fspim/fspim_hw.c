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
 * FilePath: fspim_hw.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:08:00
 * Description:  This files is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021-12-3   init commit
 * 1.1   zhugengyu  2022-4-15   support test mode
 */


#include "fassert.h"
#include "fdebug.h"
#include "fspim_hw.h"
#include "fspim.h"

/***************************** Include Files *********************************/

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FSPIM_DEBUG_TAG "SPIM-HW"
#define FSPIM_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSPIM_WARN(format, ...)   FT_DEBUG_PRINT_W(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSPIM_INFO(format, ...)    FT_DEBUG_PRINT_I(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSPIM_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/

/**
 * @name: FSpimGetTxFifoDepth
 * @msg: 获取TX Fifo可以设置的最大深度
 * @return {u32} TX Fifo的深度
 * @param {uintptr} base_addr, SPI控制器基地址
 */
u32 FSpimGetTxFifoDepth(uintptr base_addr)
{
    u32 fifo_depth;
    for (fifo_depth = 1; fifo_depth < FSPIM_MAX_FIFO_DEPTH; fifo_depth++)
    {
        FSpimSetTxFifoThreshold(base_addr, fifo_depth);
        if (fifo_depth != FSpimGetTxFifoThreshold(base_addr))
        {
            FSPIM_INFO("Tx fifo threshold is %d", fifo_depth);
            break;
        }
    }

    FSpimSetTxFifoThreshold(base_addr, 0);
    return fifo_depth;
}

/**
 * @name: FSpimGetRxFifoDepth
 * @msg: 获取RX Fifo可以设置的最大深度
 * @return {u32} Rx Fifo的深度
 * @param {uintptr} base_addr, SPI控制器基地址
 */
u32 FSpimGetRxFifoDepth(uintptr base_addr)
{
    u32 fifo_depth = FSPIM_MIN_FIFO_DEPTH;
    while (FSPIM_MAX_FIFO_DEPTH >= fifo_depth)
    {
        FSpimSetRxFifoThreshold(base_addr, fifo_depth);
        if (fifo_depth != FSpimGetRxFifoThreshold(base_addr))
        {
            FSPIM_INFO("Rx fifo threshold is %d", fifo_depth);
            break;
        }

        fifo_depth++;
    }

    return fifo_depth;
}

/**
 * @name: FSpimSelSlaveDev
 * @msg: 选择SPI从设备
 * @return {无}
 * @param {uintptr} base_addr, SPI控制器基地址
 * @param {u32} slave_dev_id, 从设备ID
 */
void FSpimSelSlaveDev(uintptr base_addr, u32 slave_dev_id)
{
    FASSERT(slave_dev_id < FSPIM_NUM_OF_SLAVE_DEV);
    u32 reg_val;

    reg_val = (FSPIM_SER_SELECT << slave_dev_id);
    FSPIM_WRITE_REG32(base_addr, FSPIM_SER_OFFSET, reg_val);
    return;
}

/**
 * @name: FSpimSetSpeed
 * @msg: 设置SPI传输速度
 * @return {FError}
 * @param {uintptr} base_addr, SPI控制器基地址
 * @param {u32} speed, SPI传输速度设置
 */
FError FSpimSetSpeed(uintptr base_addr, u32 speed)
{
    u32 clk_div;
    boolean enabled = FSpimGetEnable(base_addr);

    if (enabled)
        FSpimSetEnable(base_addr, FALSE);

    clk_div = FSPI_FREQ / speed;
    FSPIM_INFO("set clk div as %d", clk_div);
    FSPIM_WRITE_REG32(base_addr, FSPIM_BAUD_R_OFFSET, clk_div);

    if (enabled)
        FSpimSetEnable(base_addr, TRUE);

    return FSPIM_SUCCESS;
}

/**
 * @name: FSpimSetTransMode
 * @msg: 设置SPI传输模式
 * @return {无}
 * @param {uintptr} base_addr, SPI控制器基地址
 * @param {u32} trans_mode, SPI传输模式设置
 */
void FSpimSetTransMode(uintptr base_addr, u32 trans_mode)
{
    FASSERT(trans_mode < FSPIM_TRANS_MODE_MAX);
    u32 reg_val;
    boolean enabled = FSpimGetEnable(base_addr);

    if (enabled)
        FSpimSetEnable(base_addr, FALSE);

    reg_val = FSpimGetCtrlR0(base_addr);
    reg_val &= ~FSPIM_CTRL_R0_TMOD_MASK; /* clear trans mode bits */
    switch (trans_mode)
    {
    case FSPIM_TRANS_MODE_RX_TX:
        reg_val |= FSPIM_CTRL_R0_TMOD(FSPIM_TMOD_RX_TX);
        break;
    case FSPIM_TRANS_MODE_TX_ONLY:
        reg_val |= FSPIM_CTRL_R0_TMOD(FSPIM_TMOD_TX_ONLY);
        break;
    case FSPIM_TRANS_MODE_RX_ONLY:
        reg_val |= FSPIM_CTRL_R0_TMOD(FSPIM_TMOD_RX_ONLY);
        break;
    case FSPIM_TRANS_MODE_READ_EEPROM:
        reg_val |= FSPIM_CTRL_R0_TMOD(FSPIM_TMOD_RD_EEPROM);
        break;
    default:
        FASSERT(0);
        break;
    }

    FSpimSetCtrlR0(base_addr, reg_val);

    if (enabled)
        FSpimSetEnable(base_addr, TRUE);

    return;
}

/**
 * @name: FSpimSetCpha
 * @msg: 设置串行时钟相位
 * @return {无}
 * @param {uintptr} base_addr, SPI控制器基地址
 * @param {u32} cpha_mode, SPI控制器的相位设置
 */
void FSpimSetCpha(uintptr base_addr, u32 cpha_mode)
{
    u32 reg_val = FSpimGetCtrlR0(base_addr);

    reg_val &= ~FSPIM_CTRL_R0_SCPHA_MASK; /* clear bits */
    if (FSPIM_CPHA_1_EDGE == cpha_mode)
        reg_val |= FSPIM_CTRL_R0_SCPHA(FSPIM_SCPHA_SWITCH_DATA_MID);
    else if (FSPIM_CPHA_2_EDGE == cpha_mode)
        reg_val |= FSPIM_CTRL_R0_SCPHA(FSPIM_SCPHA_SWITCH_DATA_BEG);
    else
        FASSERT(0);

    FSpimSetCtrlR0(base_addr, reg_val);
}

/**
 * @name: FSpimSetCpol
 * @msg: 设置串行时钟极性
 * @return {无}
 * @param {uintptr} base_addr, SPI控制器基地址
 * @param {u32} cpol_mode, SPI控制器的极性设置
 */
void FSpimSetCpol(uintptr base_addr, u32 cpol_mode)
{
    u32 reg_val = FSpimGetCtrlR0(base_addr);

    reg_val &= ~FSPIM_CTRL_R0_SCPOL_MASK; /* clear bits */
    if (FSPIM_CPOL_LOW == cpol_mode)
        reg_val |= FSPIM_CTRL_R0_SCPOL(FSPIM_SCPOL_INACTIVE_LOW);
    else if (FSPIM_CPOL_HIGH == cpol_mode)
        reg_val |= FSPIM_CTRL_R0_SCPOL(FSPIM_SCPOL_INACTIVE_HIGH);
    else
        FASSERT(0);

    FSpimSetCtrlR0(base_addr, reg_val);
}

/**
 * @name: FSpimSetSlaveEnable
 * @msg: 使能/去使能和从设备的连接
 * @return {无}
 * @param {uintptr} base_addr, SPI控制器基地址
 * @param {boolean} enable, TRUE: 使能从设备, FALSE: 去使能从设备
 */
void FSpimSetSlaveEnable(uintptr base_addr, boolean enable)
{
    u32 reg_val;
    boolean enabled = FSpimGetEnable(base_addr);

    if (enabled)
        FSpimSetEnable(base_addr, FALSE);

    reg_val = FSpimGetCtrlR0(base_addr);

    reg_val &= ~FSPIM_CTRL_R0_SLV_OE_MASK;
    if (enable)
        reg_val |= FSPIM_CTRL_R0_SLV_OE(FSPIM_SLAVE_TX_ENABLE);
    else
        reg_val |= FSPIM_CTRL_R0_SLV_OE(FSPIM_SLAVE_TX_DISALE);

    FSpimSetCtrlR0(base_addr, reg_val);

    if (enabled)
        FSpimSetEnable(base_addr, TRUE);

    return;
}