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
 * FilePath: fsdmmc_hw.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:54:02
 * Description:  This file contains macros that can be used to access the device.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/2    init
 */

/***************************** Include Files *********************************/
#include "fassert.h"
#include "fdebug.h"
#include "fsdmmc_hw.h"
#include "fsdmmc.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FSDMMC_DEBUG_TAG "FSDMMC-HW"
#define FSDMMC_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSDMMC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDMMC_WARN(format, ...)    FT_DEBUG_PRINT_W(FSDMMC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDMMC_INFO(format, ...)    FT_DEBUG_PRINT_I(FSDMMC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDMMC_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSDMMC_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/
/**
 * @name: FSdmmcSoftwareReset
 * @msg: 完成软复位
 * @return {*}
 * @param {uintptr} base_addr FSDMMC控制器基地址
 * @param {int} retries 重试次数
 */
FError FSdmmcSoftwareReset(uintptr base_addr, int retries)
{
    FASSERT(retries > 1);
    u32 reg_val;

    FSDMMC_SET_BIT(base_addr, FSDMMC_SOFTWARE_RESET_REG_OFFSET, FSDMMC_SOFTWARE_RESET_SRST);
    FSDMMC_CLR_BIT(base_addr, FSDMMC_SOFTWARE_RESET_REG_OFFSET, FSDMMC_SOFTWARE_RESET_SRST);

    do
    {
        reg_val = FSDMMC_READ_REG(base_addr, FSDMMC_STATUS_REG_OFFSET);
    }
    while (!(reg_val & FSDMMC_STATUS_IDIE) &&
           (retries-- > 0));

    if (!(reg_val & FSDMMC_STATUS_IDIE) && (retries <= 0))
    {
        FSDMMC_ERROR("Software reset timeout!!! status: 0x%x", reg_val);
        return FSDMMC_ERR_TIMEOUT;
    }

    return FSDMMC_SUCCESS;
}

/**
 * @name: FSdmmcSetCardClk
 * @msg: 设置FSDMMC的时钟
 * @return {*}
 * @param {uintptr} base_addr FSDMMC控制器基地址
 * @param {u32} clk_freq_hz 时钟频率，HZ
 */
FError FSdmmcSetCardClk(uintptr base_addr, u32 clk_freq_hz)
{
    FSDMMC_WRITE_REG(base_addr, FSDMMC_CLOCK_DIV_REG_OFFSET, FSDMMC_CLK_DIVIDER(clk_freq_hz));
    FSDMMC_WRITE_REG(base_addr, FSDMMC_SD_DRV_REG_OFFSET, FSDMMC_DEFAULT_DRV);
    FSDMMC_WRITE_REG(base_addr, FSDMMC_SD_SAMP_REG_OFFSET, FSDMMC_DEFAULT_SAMP);

    return FSdmmcSoftwareReset(base_addr, FSDMMC_TIMEOUT);
}

static const char *FSdmmcGetRespTypeStr(u32 hw_cmd)
{
    const char *str;

    switch (FSDMMC_CMD_RESP_MASK & hw_cmd)
    {
        case FSDMMC_CMD_NO_RESP:
            str = "NONE";
            break;
        case FSDMMC_CMD_RESP_136_BIT:
            str = "LONG";
            break;
        case FSDMMC_CMD_RESP_48_BIT:
            str = "SHORT";
            break;
        case FSDMMC_CMD_RESP_48_BIT_BUSY_CHECK:
            str = "SHORT CHECK BUSY";
            break;
        default:
            FASSERT(0);
    }

    return str;
}

/**
 * @name: FSdmmcSendPrivateCmd
 * @msg: 发送命令
 * @return {*}
 * @param {uintptr} base_addr FSDMMC控制器基地址
 * @param {u32} cmd 待发送的命令
 * @param {u32} arg 待发送命令的参数
 */
void FSdmmcSendPrivateCmd(uintptr base_addr, u32 cmd, u32 arg)
{
    /* 清空状态寄存器 */
    FSdmmcClearNormalInterruptStatus(base_addr);
    FSdmmcClearErrorInterruptStatus(base_addr);
    FSdmmcClearBDInterruptStatus(base_addr);

    /* 设置命令 */
    FSDMMC_WRITE_REG(base_addr, FSDMMC_CMD_SETTING_REG_OFFSET, cmd);

    FSDMMC_DATA_BARRIER();

    /* 设置参数，同时触发发送命令 */
    FSDMMC_WRITE_REG(base_addr, FSDMMC_ARGUMENT_REG_OFFSET, FSDMMC_ARGUMENT_MASK & arg);

    FSDMMC_INFO("CMD: 0x%08x ", FSDMMC_READ_REG(base_addr, FSDMMC_CMD_SETTING_REG_OFFSET));
    FSDMMC_INFO("ARG: 0x%08x",  FSDMMC_READ_REG(base_addr, FSDMMC_ARGUMENT_REG_OFFSET));
    FSDMMC_INFO("RESP: %s", FSdmmcGetRespTypeStr(cmd));
}

/**
 * @name: FSdmmcReset
 * @msg: 重置FSDMMC控制器
 * @return {*}
 * @param {uintptr} base_addr FSDMMC控制器基地址
 */
FError FSdmmcReset(uintptr base_addr)
{
    u32 reg_val;
    FError ret = FSDMMC_SUCCESS;

    ret = FSdmmcSoftwareReset(base_addr, FSDMMC_TIMEOUT);
    if (FSDMMC_SUCCESS != ret)
    {
        return ret;
    }

    /* set card detection */
    FSDMMC_WRITE_REG(base_addr, FSDMMC_SD_SEN_REG_OFFSET, 0x0);
    reg_val = FSDMMC_SEN_CREFR_VAL | FSDMMC_SEN_DEBNCE_VAL;
    FSDMMC_WRITE_REG(base_addr, FSDMMC_SD_SEN_REG_OFFSET, reg_val);

    /* configure cmd data timeout */
    FSDMMC_WRITE_REG(base_addr, FSDMMC_TIMEOUT_CMD_REG_OFFSET, FSDMMC_CMD_TIMEOUT);
    FSDMMC_WRITE_REG(base_addr, FSDMMC_TIMEOUT_DATA_REG_OFFSET, FSDMMC_DATA_TIMEOUT);

    /* handle DMA cache */
    FSDMMC_WRITE_REG(base_addr, FSDMMC_HDS_AXI_REG_CONF1_REG_OFFSET, FSDMMC_AXI_CONF1);
    FSDMMC_WRITE_REG(base_addr, FSDMMC_HDS_AXI_REG_CONF2_REG_OFFSET, FSDMMC_AXI_CONF2);

    /* set ending */
    reg_val = FSDMMC_PERMDW_STD_END | FSDMMC_PERMDR_STD_END;
    FSDMMC_WRITE_REG(base_addr, FSDMMC_CONTROLL_SETTING_REG_OFFSET, reg_val);

    /* disable interrupt */
    FSDMMC_WRITE_REG(base_addr, FSDMMC_NORMAL_INT_EN_REG_OFFSET, 0x0);
    FSDMMC_WRITE_REG(base_addr, FSDMMC_ERROR_INT_EN_REG_OFFSET, 0x0);
    FSDMMC_WRITE_REG(base_addr, FSDMMC_BD_ISR_EN_REG_OFFSET, 0x0);

    /* clear interrupr status */
    FSdmmcClearNormalInterruptStatus(base_addr);
    FSdmmcClearErrorInterruptStatus(base_addr);
    FSdmmcClearBDInterruptStatus(base_addr);

    return ret;
}

/**
 * @name: FSdmmcWaitStatus
 * @msg: 等待命令完成或者命令错误状态
 * @return {*}
 * @param {uintptr} base_addr FSDMMC控制器基地址
 * @param {int} retries 重试次数
 */
FError FSdmmcWaitStatus(uintptr base_addr, int retries)
{
    FASSERT(retries > 1);
    const u32 status_mask = FSDMMC_NORMAL_INT_STATUS_CC | FSDMMC_NORMAL_INT_STATUS_EI; /* 等待命令完成或者发生错误 */
    u32 status;

    do
    {
        status = status_mask & FSDMMC_READ_REG(base_addr, FSDMMC_NORMAL_INT_STATUS_REG_OFFSET);
    }
    while ((!status) && (retries-- > 0));

    if (FSDMMC_NORMAL_INT_STATUS_EI & status)
    {
        FSDMMC_ERROR("Error status: 0x%x,  remain retries: %d", status, retries);
        FSdmmcReset(base_addr);
        return FSDMMC_ERR_CMD_FAILED;
    }
    else if (0 >= retries)
    {
        FSDMMC_ERROR("Wait timeout!!! status 0x%x", status);
        return FSDMMC_ERR_TIMEOUT;
    }

    return FSDMMC_SUCCESS;
}

/**
 * @name: FSdmmcWaitDMAStatus
 * @msg: 等待数据传输完成或者传输错误状态
 * @return {*}
 * @param {uintptr} base_addr FSDMMC控制器基地址
 * @param {boolean} read TRUE: 当前是读数据 FALSE: 当前是写数据
 * @param {int} retries 重试次数
 */
FError FSdmmcWaitDMAStatus(uintptr base_addr, boolean read, int retries)
{
    const u32 status_mask = read ?
                            (FSDMMC_BD_ISR_REG_RESPE | FSDMMC_BD_ISR_REG_DAIS) : /* 等待DMA传输完成或者发生错误 */
                            (FSDMMC_BD_ISR_REG_TRS | FSDMMC_BD_ISR_REG_DAIS); /* 等待DMA传输完成或者发生错误 */
    u32 status;

    /* 等待DMA传输完成或者发生错误 */
    do
    {
        status = status_mask & FSDMMC_READ_REG(base_addr, FSDMMC_BD_ISR_REG_OFFSET);
    }
    while ((!status) && (retries-- > 0));

    if (status & FSDMMC_BD_ISR_REG_DAIS)
    {
        FSDMMC_ERROR("BD Data error when %s blk!", read ? "read" : "write");
        FSdmmcReset(base_addr);
        return FSDMMC_ERR_DATA_FAILED;
    }
    else if (0 >= retries)
    {
        FSDMMC_ERROR("BD Data timeout !!!");
        return FSDMMC_ERR_TIMEOUT;
    }

    return FSDMMC_SUCCESS;
}