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
 * FilePath: fsdmmc.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:55:23
 * Description:  This file is for functions in this file are the minimum required functions
 * for this driver. 
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/2    init
 */

/***************************** Include Files *********************************/
#include <string.h>

#include "fassert.h"
#include "fio.h"
#include "ferror_code.h"
#include "ftypes.h"
#include "fdebug.h"


#include "fsleep.h"

#include "fsdmmc_hw.h"
#include "fsdmmc.h"
#include "fsdmmc_dma.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FSDMMC_DEBUG_TAG "FSDMMC"
#define FSDMMC_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSDMMC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDMMC_WARN(format, ...)    FT_DEBUG_PRINT_W(FSDMMC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDMMC_INFO(format, ...)    FT_DEBUG_PRINT_I(FSDMMC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDMMC_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSDMMC_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/

/* 此文件主要为了完成用户对外接口，用户可以使用这些接口直接开始工作 */

/* - 包括用户API的定义和实现
   - 同时包含必要的OPTION方法，方便用户进行配置
   - 如果驱动可以直接进行I/O操作，在此源文件下可以将API 进行实现 */

/**
 * @name: FSdmmcCfgInitialize
 * @msg: 初始化FSDMMC控制器, 使之可以使用
 * @return {FError} 驱动初始化的错误码信息，FSDMMC_SUCCESS 表示初始化成功，其它返回值表示初始化失败
 * @param {FSdmmc} *instance_p FSDMMC驱动控制数据
 * @param {FSdmmcConfig} *input_config_p FSDMMC用户输入配置
 * @note 输入配置通过FSdmmcLookupConfig获取，用户按照需要修改后传入此函数
 */
FError FSdmmcCfgInitialize(FSdmmc *instance_p, const FSdmmcConfig *input_config_p)
{
    FASSERT(instance_p && input_config_p);
    uintptr base_addr;
    FError ret = FSDMMC_SUCCESS;

    /*
    * If the device is started, disallow the initialize and return a Status
    * indicating it is started.  This allows the user to de-initialize the device
    * and reinitialize, but prevents a user from inadvertently
    * initializing.
    */
    if (FT_COMPONENT_IS_READY == instance_p->is_ready)
    {
        FSDMMC_WARN("Device is already initialized!!!");
    }

    /*
    * Set default values and configuration data, including setting the
    * callback handlers to stubs  so the system will not crash should the
    * application not assign its own callbacks.
     */
    FSdmmcDeInitialize(instance_p);

    instance_p->config = *input_config_p;
    base_addr = instance_p->config.base_addr;

    /*
    * Check if card exists
    */
    if (!FSdmmcCheckIfCardExists(base_addr))
    {
        FSDMMC_ERROR("Storage device not found !!! 0x%x", base_addr);
        return FSDMMC_ERR_CARD_NO_FOUND;
    }

    /*
    * Reset the device.
    */
    ret = FSdmmcReset(base_addr);
    if (FSDMMC_SUCCESS == ret)
    {
        instance_p->is_ready = FT_COMPONENT_IS_READY;
    }

    return ret;
}

/**
 * @name: FSdmmcDeInitialize
 * @msg: 去使能FSDMMC控制器, 清零实例数据
 * @return {*}
 * @param {FSdmmc} *instance_p FSDMMC驱动控制数据
 */
void FSdmmcDeInitialize(FSdmmc *instance_p)
{
    FASSERT(instance_p);

    instance_p->is_ready = 0;
    memset(instance_p, 0, sizeof(*instance_p));

    return;
}

/**
 * @name: FSdmmcMakeRawCmd
 * @msg: 组装生成待发送的命令
 * @return {*}
 * @param {FSdmmcCmd} *cmd_p 命令控制数据
 */
u32 FSdmmcMakeRawCmd(FSdmmcCmd *cmd_p)
{
    FASSERT(cmd_p);
    u32 raw_cmd = 0;

    /*
     * rawcmd :
     *   trty << 14 | opcode << 8 | cmdw << 6 | cice << 4 | crce << 3 | resp
     */
    raw_cmd |= FSDMMC_CMD_SETTING_CMDI(cmd_p->cmdidx);

    if (cmd_p->flag & FSDMMC_CMD_FLAG_ADTC)
    {
        raw_cmd |= FSDMMC_CMD_SETTING_TRTY(0b10);    /* adtc指令 */
    }

    if (0 == (cmd_p->flag & FSDMMC_CMD_FLAG_EXP_RESP))
    {
        raw_cmd |= FSDMMC_CMD_NO_RESP;
    }
    else if (cmd_p->flag & FSDMMC_CMD_FLAG_EXP_LONG_RESP)
    {
        raw_cmd |= FSDMMC_CMD_RESP_136_BIT;
    }
    else
    {
        raw_cmd |= FSDMMC_CMD_RESP_48_BIT;
    }

    return raw_cmd;
}

/**
 * @name: FSdmmcWaitCmdEnd
 * @msg: 阻塞等待命令发送完成，获取命令返回的响应
 * @return {FError} FSDMMC_SUCCESS表示命令发送成功，其它表示命令发送失败
 * @param {uintptr} base_addr FSDMMC控制器基地址
 * @param {FSdmmcCmd} *cmd_p 命令控制数据
 */
static FError FSdmmcWaitCmdEnd(uintptr base_addr, FSdmmcCmd *cmd_p)
{
    FASSERT(cmd_p);
    FError ret = FSDMMC_SUCCESS;

    ret = FSdmmcWaitStatus(base_addr, FSDMMC_TIMEOUT);
    if (FSDMMC_SUCCESS != ret)
    {
        return ret;
    }

    if (cmd_p->flag & FSDMMC_CMD_FLAG_EXP_RESP)
    {
        if (cmd_p->flag & FSDMMC_CMD_FLAG_EXP_LONG_RESP)
        {
            cmd_p->response[0] = FSDMMC_READ_REG(base_addr, FSDMMC_CMD_RESP_1_REG_OFFSET);
            cmd_p->response[1] = FSDMMC_READ_REG(base_addr, FSDMMC_CMD_RESP_2_REG_OFFSET);
            cmd_p->response[2] = FSDMMC_READ_REG(base_addr, FSDMMC_CMD_RESP_3_REG_OFFSET);
            cmd_p->response[3] = FSDMMC_READ_REG(base_addr, FSDMMC_CMD_RESP_4_REG_OFFSET);
        }
        else
        {
            cmd_p->response[0] = FSDMMC_READ_REG(base_addr, FSDMMC_CMD_RESP_1_REG_OFFSET);
            cmd_p->response[1] = 0;
            cmd_p->response[2] = 0;
            cmd_p->response[3] = 0;
        }
    }

    FSDMMC_INFO("get cmd resp: 0x%x:0x%x:0x%x:0x%x",
                cmd_p->response[0],
                cmd_p->response[1],
                cmd_p->response[2],
                cmd_p->response[3]);

    return FSDMMC_SUCCESS;
}

/**
 * @name: FSdmmcSendCmd
 * @msg: 发送命令
 * @return {FError} FSDMMC_SUCCESS表示命令发送成功，其它表示命令发送失败
 * @param {uintptr} base_addr FSDMMC控制器基地址
 * @param {FSdmmcCmd} *cmd_p 命令控制数据
 */
void FSdmmcSendCmd(uintptr base_addr, FSdmmcCmd *cmd_p)
{
    FASSERT(cmd_p);
    u32 raw_cmd = FSdmmcMakeRawCmd(cmd_p);

    FSdmmcSendPrivateCmd(base_addr, raw_cmd, cmd_p->cmdarg);
}

/**
 * @name: FSdmmcTransferCmdPoll
 * @msg: 通过FSDMMC轮询方式发送命令，阻塞等待命令返回
 * @return {*}
 * @param {uintptr} base_addr FSDMMC控制器基地址
 * @param {FSdmmcCmd} *cmd_p 命令控制数据
 */
static FError FSdmmcTransferCmdPoll(uintptr base_addr, FSdmmcCmd *cmd_p)
{
    FASSERT(cmd_p);
    FSdmmcSendCmd(base_addr, cmd_p);
    return FSdmmcWaitCmdEnd(base_addr, cmd_p);
}

/**
 * @name: FSdmmcSendAdtcCmd
 * @msg: 发送ADTC命令
 * @return {*}
 * @param {uintptr} base_addr FSDMMC控制器基地址
 * @param {FSdmmcCmd} *cmd_p 命令控制数据
 */
static void FSdmmcSendAdtcCmd(uintptr base_addr, FSdmmcCmd *cmd_p)
{
    FASSERT(cmd_p);
    u32 raw_cmd = FSdmmcMakeRawCmd(cmd_p);

    FSdmmcClearNormalInterruptStatus(base_addr);
    raw_cmd |= FSDMMC_CMD_SETTING_TRTY(0b10); /* adtc指令 */
    FSDMMC_WRITE_REG(base_addr, FSDMMC_CMD_SETTING_REG_OFFSET, raw_cmd);
    return;
}

/**
 * @name: FSdmmcSendData
 * @msg: 发送数据
 * @return {*}
 * @param {uintptr} base_addr FSDMMC控制器基地址
 * @param {boolean} read TREU: 读数据 FALSE: 写数据
 * @param {FSdmmcCmd} *cmd_p 命令控制数据
 */
FError FSdmmcSendData(uintptr base_addr, boolean read, FSdmmcCmd *cmd_p)
{
    FASSERT(cmd_p);
    FSdmmcData *dat_p = cmd_p->data_p;
    u32 card_addr;
    u32 blk_cnt;
    FError ret = FSDMMC_SUCCESS;

    if ((dat_p->datalen >= FSDMMC_DMA_ADDR_ALIGN) && (dat_p->datalen % FSDMMC_DMA_ADDR_ALIGN != 0))
    {
        FSDMMC_ERROR("Invalid size: total = %d.", dat_p->datalen);
        return FSDMMC_ERR_INVALID_BUF;
    }

    if (((uintptr)(dat_p->buf) % FSDMMC_DMA_ADDR_ALIGN) != 0)
    {
        FSDMMC_ERROR("Buffer %p can not be used for DMA.", dat_p->buf);
        return FSDMMC_ERR_INVALID_BUF;
    }

    card_addr = cmd_p->cmdarg;
    blk_cnt = dat_p->datalen / dat_p->blksz;
    if (dat_p->datalen % dat_p->blksz)
    {
        blk_cnt++;
    }

    FSDMMC_INFO("Data len: %d, card addr: 0x%x, blk cnt: %d, is %s",
                dat_p->datalen, card_addr, blk_cnt, read ? "read" : "write");

    if (read)
    {
        if ((cmd_p->flag & FSDMMC_CMD_FLAG_ADTC) && (dat_p->blksz > dat_p->datalen))
        {
            FSdmmcSendAdtcCmd(base_addr, cmd_p);
        }
        /* read data */
        FSdmmcSetReadDMA(base_addr, (uintptr)card_addr, blk_cnt, dat_p->buf);
    }
    else
    {
        /* invalidate write buf */
        FSDMMC_DATA_BARRIER();

        /* write data */
        FSdmmcSetWriteDMA(base_addr, (uintptr)card_addr, blk_cnt, dat_p->buf);
    }

    return ret;
}

/**
 * @name: FSdmmcTransferDataPoll
 * @msg: 通过FSDMMC轮询方式发送数据，阻塞等待数据返回
 * @return {*}
 * @param {uintptr} base_addr FSDMMC控制器基地址
 * @param {FSdmmcCmd} *cmd_p 待发送数据
 */
static FError FSdmmcTransferDataPoll(uintptr base_addr, FSdmmcCmd *cmd_p)
{
    FASSERT(cmd_p);
    FError ret = FSDMMC_SUCCESS;
    FSdmmcData *dat_p = cmd_p->data_p;
    const boolean read = (FSDMMC_CMD_FLAG_READ_DATA == (cmd_p->flag & FSDMMC_CMD_FLAG_READ_DATA));

    ret = FSdmmcSendData(base_addr, read, cmd_p);
    if (FSDMMC_SUCCESS != ret)
    {
        return ret;
    }

    ret = FSdmmcWaitCmdEnd(base_addr, cmd_p);
    if (FSDMMC_SUCCESS != ret)
    {
        return ret;
    }

    ret = FSdmmcWaitDMAStatus(base_addr, read, FSDMMC_TIMEOUT);
    if (FSDMMC_SUCCESS != ret)
    {
        return ret;
    }

    FSDMMC_DATA_BARRIER();
    return ret;
}

/**
 * @name: FSdmmcPollTransfer
 * @msg: 通过FSDMMC轮询方式发送/接收数据和命令
 * @return {FError} 驱动初始化的错误码信息，FSDMMC_SUCCESS 表示发送/接收成功，其它返回值表示发送/接收失败
 * @param {FSdmmc} *instance_p FSDMMC驱动控制数据
 * @param {FSdmmcCmd} *cmd_data_p FSDMMC数据和命令
 * @note FSDMMC控制器初始化后才能调用此函数
 */
FError FSdmmcPollTransfer(FSdmmc *instance_p, FSdmmcCmd *cmd_data_p)
{
    FASSERT(instance_p && cmd_data_p);
    uintptr base_addr = instance_p->config.base_addr;
    FError ret = FSDMMC_SUCCESS;

    if (FALSE == FSdmmcCheckIfCardExists(base_addr))
    {
        FSDMMC_ERROR("Card not found !!! fsdio ctrl base 0x%x.", base_addr);
        return FSDMMC_ERR_CARD_NO_FOUND;
    }

    if (cmd_data_p->flag & FSDMMC_CMD_FLAG_EXP_DATA)
    {
        /* transfer data */
        FSDMMC_INFO("====DATA [%d] START: buf: %p=====", cmd_data_p->cmdidx, cmd_data_p->data_p->buf);
        ret = FSdmmcTransferDataPoll(base_addr, cmd_data_p);
        if (FSDMMC_SUCCESS != ret)
        {
            FSDMMC_ERROR("Transfer data failed 0x%x.", ret);
            return ret;
        }

        FSDMMC_INFO("====DATA [%d] END 0x%x=====", cmd_data_p->cmdidx, ret);
    }
    else
    {
        /* transfer command */
        FSDMMC_INFO("=====CMD [%d] START=====", cmd_data_p->cmdidx);
        ret = FSdmmcTransferCmdPoll(base_addr, cmd_data_p);
        if (FSDMMC_SUCCESS != ret)
        {
            FSDMMC_ERROR("Send cmd failed 0x%x.", ret);
            return ret;
        }

        FSDMMC_INFO("=====CMD [%d] END: 0x%x=====", cmd_data_p->cmdidx, ret);
    }

    return ret;
}