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
 * FilePath: fsdmmc.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:55:57
 * Description:  This file is for functions in this file are the minimum required functions
 * for this driver. 
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/2    init
 */

#ifndef  FSDMMC_H
#define  FSDMMC_H
/***************************** Include Files *********************************/

#include "ftypes.h"
#include "ferror_code.h"
#include "fkernel.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/
#define FSDMMC_SUCCESS           FT_SUCCESS
#define FSDMMC_ERR_NOT_READY     FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 1)
#define FSDMMC_ERR_TIMEOUT       FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 2)
#define FSDMMC_ERR_CMD_FAILED    FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 3)
#define FSDMMC_ERR_DATA_FAILED   FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 4)
#define FSDMMC_ERR_CARD_NO_FOUND FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 5)
#define FSDMMC_ERR_INVALID_BUF   FT_MAKE_ERRCODE(ErrModBsp, ErrBspMmc, 6)

/**************************** Type Definitions *******************************/
enum
{
    FSDMMC_DMA_BD_INTR = 0,
    FSDMMC_CMD_INTR,
    FSDMMC_ERROR_INTR,

    FSDMMC_INTR_NUM
}; /* 中断类型 */

enum
{
    FSDMMC_EVT_CARD_REMOVED = 0,
    FSDMMC_EVT_CMD_DONE,
    FSDMMC_EVT_CMD_ERROR,
    FSDMMC_EVT_CMD_RESP_ERROR,
    FSDMMC_EVT_DATA_ERROR,
    FSDMMC_EVT_DATA_READ_DONE,
    FSDMMC_EVT_DATA_WRITE_DONE,

    FSDMMC_EVT_NUM
}; /* 事件类型 */

/**
 * This typedef contains data information for the device.
 */
typedef struct
{
    u8 *buf;
    u32 blksz;
    u32 blkcnt;
    u32 datalen;
} FSdmmcData;

/**
 * This typedef contains command information for the device.
 */
typedef struct
{
    u32 cmdidx;
    u32 cmdarg;
    u32 resptype;
    u32 response[4];
    u32 flag;
#define FSDMMC_CMD_FLAG_NEED_STOP         BIT(0)
#define FSDMMC_CMD_FLAG_NEED_INIT         BIT(1)
#define FSDMMC_CMD_FLAG_EXP_RESP          BIT(2)
#define FSDMMC_CMD_FLAG_EXP_LONG_RESP     BIT(3)
#define FSDMMC_CMD_FLAG_NEED_RESP_CRC     BIT(4)
#define FSDMMC_CMD_FLAG_EXP_DATA          BIT(5)
#define FSDMMC_CMD_FLAG_WRITE_DATA        BIT(6)
#define FSDMMC_CMD_FLAG_READ_DATA         BIT(7)
#define FSDMMC_CMD_FLAG_NEED_AUTO_STOP    BIT(8)
#define FSDMMC_CMD_FLAG_ADTC              BIT(9)
    FSdmmcData *data_p;
} FSdmmcCmd;

/**
 * This typedef contains configuration information for the device.
 */
typedef struct
{
    u32     instance_id; /* Device instance id */
    uintptr base_addr;   /* Device base address */
    u32     irq_num[FSDMMC_INTR_NUM];
} FSdmmcConfig;

typedef void (*FSdmmcEventHandler)(void *args);

/**
 * This typedef contains driver instance data. The user is required to allocate a
 * variable of this type for every device in the system. A pointer
 * to a variable of this type is then passed to the driver API functions.
 */
typedef struct
{
    FSdmmcConfig config;      /* Current active configs */
    u32          is_ready;    /* Device is initialized and ready */
    FSdmmcEventHandler evt_handler[FSDMMC_EVT_NUM];
    void         *evt_args[FSDMMC_EVT_NUM];
} FSdmmc; /* Device instance */

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/* 获取FSDMMC控制器默认配置 */
const FSdmmcConfig *FSdmmcLookupConfig(u32 instance_id);

/* 初始化FSDMMC控制器, 使之可以使用 */
FError FSdmmcCfgInitialize(FSdmmc *instance_p, const FSdmmcConfig *cofig_p);

/* 去使能FSDMMC控制器, 清零实例数据 */
void FSdmmcDeInitialize(FSdmmc *instance_p);

/* 通过FSDMMC轮询方式发送/接收数据和命令 */
FError FSdmmcPollTransfer(FSdmmc *instance_p, FSdmmcCmd *cmd_data_p);

/* 通过FSDMMC中断方式发送/接收数据和命令 */
FError FSdmmcInterruptTransfer(FSdmmc *instance_p, FSdmmcCmd *cmd_data_p);

/* 获取FSDMMC的中断掩码 */
u32 FSdmmcGetInterruptMask(uintptr base_addr, u32 intr_type);

/* 设置FSDMMC的中断掩码 */
void FSdmmcSetInterruptMask(uintptr base_addr, u32 intr_type, u32 mask, boolean enable);

/* 命令中断响应函数 */
void FSdmmcCmdInterrupHandler(s32 vector, void *param);

/* 错误中断响应函数 */
void FSdmmcErrInterrupHandler(s32 vector, void *param);

/* DMA中断响应函数 */
void FSdmmcDmaInterrupHandler(s32 vector, void *param);

/* 注册中断事件响应函数 */
void FSdmmcRegisterInterruptHandler(FSdmmc *instance_p, u32 event, FSdmmcEventHandler handler, void *args);

#ifdef __cplusplus
}
#endif


#endif
