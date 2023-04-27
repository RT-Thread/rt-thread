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
 * FilePath: fsdmmc_intr.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:54:53
 * Description:  This file contains the functions that are related to interrupt processing
 * for the fsdmmc device.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/2    init
 */

/***************************** Include Files *********************************/
#include "fassert.h"
#include "fio.h"
#include "fdebug.h"

#include "fsdmmc_hw.h"
#include "fsdmmc.h"

/************************** Constant Definitions *****************************/
#define FSDMMC_DEBUG_TAG "FSDMMC-INTR"
#define FSDMMC_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSDMMC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDMMC_WARN(format, ...)    FT_DEBUG_PRINT_W(FSDMMC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDMMC_INFO(format, ...)    FT_DEBUG_PRINT_I(FSDMMC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDMMC_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSDMMC_DEBUG_TAG, format, ##__VA_ARGS__)

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
static void FSdmmcCallEvtHandler(FSdmmcEventHandler handler, void *arg)
{
    if (NULL != handler)
    {
        handler(arg);
    }
}

/************************** Function Prototypes ******************************/
extern u32 FSdmmcMakeRawCmd(FSdmmcCmd *cmd_p);
extern void FSdmmcSendCmd(uintptr base_addr, FSdmmcCmd *cmd_p);
extern FError FSdmmcSendData(uintptr base_addr, boolean read, FSdmmcCmd *cmd_p);

/************************** Variable Definitions *****************************/

/*****************************************************************************/
/**
 * @name: FSdmmcGetInterruptMask
 * @msg: 获取FSDMMC的中断掩码
 * @return {u32} 中断掩码
 * @param {uintptr} base_addr FSDMMC控制器基地址
 * @param {u32} intr_type FSDMMC中断类型, 参考FSDMMC_INTR_NUM
 * @note FSDMMC控制器初始化后才能调用此函数
 */
u32 FSdmmcGetInterruptMask(uintptr base_addr, u32 intr_type)
{
    u32 mask;

    switch (intr_type)
    {
        case FSDMMC_CMD_INTR:
            mask = FSDMMC_READ_REG(base_addr, FSDMMC_NORMAL_INT_EN_REG_OFFSET);
            break;
        case FSDMMC_ERROR_INTR:
            mask = FSDMMC_READ_REG(base_addr, FSDMMC_ERROR_INT_EN_REG_OFFSET);
            break;
        case FSDMMC_DMA_BD_INTR:
            mask = FSDMMC_READ_REG(base_addr, FSDMMC_BD_ISR_EN_REG_OFFSET);
            break;
        default:
            FASSERT(0);
            break;
    }

    return mask;
}

/**
 * @name: FSdmmcSetInterruptMask
 * @msg: 设置FSDMMC的中断掩码
 * @param {uintptr} base_addr FSDMMC控制器基地址
 * @param {u32} intr_type FSDMMC中断类型, 参考FSDMMC_INTR_NUM
 * @param {u32} mask 中断掩码
 * @param {boolean} enable TRUE:打开中断, FALSE:关闭中断
 * @note FSDMMC控制器初始化后才能调用此函数
 */
void FSdmmcSetInterruptMask(uintptr base_addr, u32 intr_type, u32 mask, boolean enable)
{
    u32 old_mask = FSdmmcGetInterruptMask(base_addr, intr_type);
    u32 new_mask = 0;

    if (TRUE == enable)
    {
        new_mask = old_mask | mask;
    }
    else
    {
        new_mask = old_mask & (~mask);
    }

    switch (intr_type)
    {
        case FSDMMC_CMD_INTR:
            FSDMMC_WRITE_REG(base_addr, FSDMMC_NORMAL_INT_EN_REG_OFFSET, new_mask);
            break;
        case FSDMMC_ERROR_INTR:
            FSDMMC_WRITE_REG(base_addr, FSDMMC_ERROR_INT_EN_REG_OFFSET, new_mask);
            break;
        case FSDMMC_DMA_BD_INTR:
            FSDMMC_WRITE_REG(base_addr, FSDMMC_BD_ISR_EN_REG_OFFSET, new_mask);
            break;
        default:
            FASSERT(0);
            break;
    }

    return;
}

/**
 * @name: FSdmmcCmdInterrupHandler
 * @msg: 命令中断响应函数
 * @return {*} 无
 * @param {s32} vector 中断向量号
 * @param {void} *param 中断响应输入参数
 * @note 此函数用于设置FSDMMC中断时注册，用户可以自定义一个中断响应函数替换此函数
 */
void FSdmmcCmdInterrupHandler(s32 vector, void *param)
{
    FASSERT(param);
    u32 status;
    FSdmmc *instance_p = (FSdmmc *)param;
    uintptr base_addr = instance_p->config.base_addr;

    /* clear interrupts */
    status = FSDMMC_READ_REG(base_addr, FSDMMC_NORMAL_INT_STATUS_REG_OFFSET);

    if (status & FSDMMC_NORMAL_INT_STATUS_CR) /* 卡移除中断 */
    {
        FSdmmcCallEvtHandler(instance_p->evt_handler[FSDMMC_EVT_CARD_REMOVED],
                             instance_p->evt_args[FSDMMC_EVT_CARD_REMOVED]);
    }

    if (status & FSDMMC_NORMAL_INT_STATUS_CC) /* 命令完成中断 */
    {
        FSdmmcCallEvtHandler(instance_p->evt_handler[FSDMMC_EVT_CMD_DONE],
                             instance_p->evt_args[FSDMMC_EVT_CMD_DONE]);
    }

    if (status & FSDMMC_NORMAL_INT_STATUS_EI) /* 命令错误中断 */
    {
        FSdmmcCallEvtHandler(instance_p->evt_handler[FSDMMC_EVT_CMD_ERROR],
                             instance_p->evt_args[FSDMMC_EVT_CMD_ERROR]);
    }

    FSdmmcClearNormalInterruptStatus(base_addr);
}

/**
 * @name: FSdmmcDmaInterrupHandler
 * @msg: DMA中断响应函数
 * @return {*}
 * @param {s32} vector 中断向量号
 * @param {void} *param 中断响应输入参数
 * @note 此函数用于设置FSDMMC中断时注册，用户可以自定义一个中断响应函数替换此函数
 */
void FSdmmcDmaInterrupHandler(s32 vector, void *param)
{
    FASSERT(param);
    u32 status;
    FSdmmc *instance_p = (FSdmmc *)param;
    uintptr base_addr = instance_p->config.base_addr;

    /* clear interrupts */
    status = FSDMMC_READ_REG(base_addr, FSDMMC_BD_ISR_REG_OFFSET);

    if (status & FSDMMC_BD_ISR_REG_DAIS) /* DMA 错误中断 */
    {
        FSdmmcCallEvtHandler(instance_p->evt_handler[FSDMMC_EVT_DATA_ERROR],
                             instance_p->evt_args[FSDMMC_EVT_DATA_ERROR]);
    }

    if (status & FSDMMC_BD_ISR_REG_RESPE) /* 读 SD 卡操作，AXI BR 通道完成中断 */
    {
        FSdmmcCallEvtHandler(instance_p->evt_handler[FSDMMC_EVT_DATA_READ_DONE],
                             instance_p->evt_args[FSDMMC_EVT_DATA_READ_DONE]);
    }

    if (status & FSDMMC_BD_ISR_REG_DATFRAX) /* AXI 总线强制释放中断*/
    {
        FSDMMC_ERROR("FSDMMC_BD_ISR_REG_DATFRAX");
    }

    if (status & FSDMMC_BD_ISR_REG_NRCRC) /* 无 CRC 响应中断*/
    {
        FSDMMC_ERROR("FSDMMC_BD_ISR_REG_NRCRC");
    }

    if (status & FSDMMC_BD_ISR_REG_TRE) /* CRC 响应错误中断*/
    {
        FSDMMC_ERROR("FSDMMC_BD_ISR_REG_TRE");
    }

    if (status & FSDMMC_BD_ISR_REG_CMDE) /* 命令响应错误中断*/
    {
        FSDMMC_ERROR("FSDMMC_BD_ISR_REG_CMDE");
    }

    if (status & FSDMMC_BD_ISR_REG_DTE) /* 超时中断*/
    {
        FSDMMC_ERROR("FSDMMC_BD_ISR_REG_DTE");
    }

    if (status & FSDMMC_BD_ISR_REG_TRS) /* DMA 传输完成中断*/
    {
        FSdmmcCallEvtHandler(instance_p->evt_handler[FSDMMC_EVT_DATA_WRITE_DONE],
                             instance_p->evt_args[FSDMMC_EVT_DATA_WRITE_DONE]);
    }

    FSdmmcClearBDInterruptStatus(base_addr);
}

/**
 * @name: FSdmmcErrInterrupHandler
 * @msg: 错误中断响应函数
 * @return {*}
 * @param {s32} vector 中断向量号
 * @param {void} *param 中断响应输入参数
 * @note 此函数用于设置FSDMMC中断时注册，用户可以自定义一个中断响应函数替换此函数
 */
void FSdmmcErrInterrupHandler(s32 vector, void *param)
{
    FASSERT(param);
    u32 status;
    FSdmmc *instance_p = (FSdmmc *)param;
    uintptr base_addr = instance_p->config.base_addr;

    status = FSDMMC_READ_REG(base_addr, FSDMMC_ERROR_INT_STATUS_REG_OFFSET);

    if (status & FSDMMC_ERROR_INT_STATUS_CNR) /* 命令响应错误中断 */
    {
        FSdmmcCallEvtHandler(instance_p->evt_handler[FSDMMC_EVT_CMD_RESP_ERROR],
                             instance_p->evt_args[FSDMMC_EVT_CMD_RESP_ERROR]);
    }

    if (status & FSDMMC_ERROR_INT_STATUS_CIR) /* 命令索引错误中断 */
    {
        FSDMMC_ERROR("FSDMMC_ERROR_INT_STATUS_CIR");
    }

    if (status & FSDMMC_ERROR_INT_STATUS_CCRCE) /* 命令 CRC 错误中断 */
    {
        FSDMMC_ERROR("FSDMMC_ERROR_INT_STATUS_CCRCE");
    }

    if (status & FSDMMC_ERROR_INT_STATUS_CTE) /* 命令超时错误中断 */
    {
        FSDMMC_ERROR("FSDMMC_ERROR_INT_STATUS_CTE");
    }

    /* clear command error status */
    FSdmmcClearErrorInterruptStatus(base_addr);
}

/**
 * @name: FSdmmcRegisterInterruptHandler
 * @msg: 注册中断事件响应函数
 * @return {*}
 * @param {FSdmmc} *instance_p FSDMMC驱动控制数据
 * @param {u32} event FSDMMC中断事件类型，参考FSDMMC_EVT_NUM
 * @param {FSdmmcEventHandler} handler, FSDMMC中断事件响应函数
 * @note 此函数用于设置FSDMMC中断时注册，被注册的函数被FSdmmcCmdInterrupHandler、FSdmmcErrInterrupHandler
 * 和FSdmmcDmaInterrupHandler调用
 */
void FSdmmcRegisterInterruptHandler(FSdmmc *instance_p, u32 event, FSdmmcEventHandler handler, void *args)
{
    FASSERT(instance_p);
    instance_p->evt_handler[event] = handler;
    instance_p->evt_args[event] = args;
}

/**
 * @name: FSdmmcInterruptTransfer
 * @msg: 通过FSDMMC中断方式发送/接收数据和命令
 * @return {FError} 驱动初始化的错误码信息，FSDMMC_SUCCESS 表示发送/接收成功，其它返回值表示发送/接收失败
 * @param {FSdmmc} *instance_p FSDMMC驱动控制数据
 * @param {FSdmmcCmd} *cmd_data_p FSDMMC数据和命令
 * @note FSDMMC控制器初始化后才能调用此函数，使用前需要确保FSDMMC中断设置完成
 */
FError FSdmmcInterruptTransfer(FSdmmc *instance_p, FSdmmcCmd *cmd_data_p)
{
    FASSERT(instance_p && cmd_data_p);
    uintptr base_addr = instance_p->config.base_addr;
    FError ret = FSDMMC_SUCCESS;

    if (FALSE == FSdmmcCheckIfCardExists(base_addr))
    {
        FSDMMC_ERROR("Card not found !!! fsdio ctrl base 0x%x", base_addr);
        return FSDMMC_ERR_CARD_NO_FOUND;
    }

    if (cmd_data_p->flag & FSDMMC_CMD_FLAG_EXP_DATA)
    {
        /* transfer data */
        FSDMMC_INFO("====DATA [%d] START: buf: %p=====", cmd_data_p->cmdidx, cmd_data_p->data_p);
        ret = FSdmmcSendData(base_addr,
                             (FSDMMC_CMD_FLAG_READ_DATA == (cmd_data_p->flag & FSDMMC_CMD_FLAG_READ_DATA)),
                             cmd_data_p);
    }
    else
    {
        /* transfer command */
        FSDMMC_INFO("=====CMD [%d] START=====", cmd_data_p->cmdidx);
        FSdmmcSendCmd(base_addr, cmd_data_p);
    }

    return ret;
}