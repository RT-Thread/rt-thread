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
 * FilePath: ferror_code.h
 * Date: 2021-04-07 09:53:30
 * LastEditTime: 2022-02-17 18:05:27
 * Description:  This file is for error code functions
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */
#ifndef FERROR_CODE_H
#define FERROR_CODE_H

#include "ftypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef u32 FError;

#define FT_SUCCESS 0

/* 系统错误码模块定义 */
typedef enum
{
    ErrorModGeneral = 0,
    ErrModBsp,
    ErrModAssert,
    ErrModPort,
    StatusModBsp,
    ErrModMaxMask = 255,

} FtErrorCodeModuleMask;

/* COMMON组件的错误码子模块定义 */
typedef enum
{
    ErrCommGeneral = 0,
    ErrCommMemp,
    ErrInterrupt,
    ErrElf,
} FtErrCodeCommMask;

/* BSP模块的错误子模块定义 */
typedef enum
{
    ErrBspGeneral = 0,
    ErrBspClk,
    ErrBspScmi,
    ErrBspRtc,
    ErrBspTimer,
    ErrBspUart,
    ErrBspGpio,
    ErrBspSpi,
    ErrBspEth,
    ErrBspCan,
    ErrPcie,
    ErrBspQSpi,
    ErrBspMio,
    ErrBspI2c,
    ErrBspMmc,
    ErrBspWdt,
    ErrGic,
    ErrGdma,
    ErrNand,
    ErrIoMux,
    ErrBspSata,
    ErrUsb,
    ErrEthPhy,
    ErrDdma,
    ErrBspAdc,
    ErrBspPwm,
    ErrSema,
    ErrBspMEDIA,
    ErrBspMhu,
    ErrBspIOPad,
	
    ErrBspModMaxMask = 255
} FtErrCodeBspMask;

#define FT_ERRCODE_SYS_MODULE_OFFSET (u32)24
#define FT_ERRCODE_SUB_MODULE_OFFSET (u32)16

#define FT_ERRCODE_SYS_MODULE_MASK ((u32)0xff << FT_ERRCODE_SYS_MODULE_OFFSET) /* bit 24 .. 31 */
#define FT_ERRCODE_SUB_MODULE_MASK ((u32)0xff << FT_ERRCODE_SUB_MODULE_OFFSET) /* bit 16 .. 23 */
#define FT_ERRCODE_TAIL_VALUE_MASK ((u32)0xffff)                               /* bit  1 .. 15 */

/* Offset error code */
#define FT_ERRCODE_OFFSET(code, offset, mask) \
    (((code) << (offset)) & (mask))

/* Assembly error code */
#define FT_MAKE_ERRCODE(sys_mode, sub_mode, tail)                                                   \
    ((FT_ERRCODE_OFFSET((u32)sys_mode, FT_ERRCODE_SYS_MODULE_OFFSET, FT_ERRCODE_SYS_MODULE_MASK)) | \
     (FT_ERRCODE_OFFSET((u32)sub_mode, FT_ERRCODE_SUB_MODULE_OFFSET, FT_ERRCODE_SUB_MODULE_MASK)) | \
     ((u32)tail & FT_ERRCODE_TAIL_VALUE_MASK))
#define FT_CODE_ERR FT_MAKE_ERRCODE

#define ERR_SUCCESS FT_MAKE_ERRCODE(ErrorModGeneral, ErrBspGeneral, 0) /* 成功 */
#define ERR_GENERAL FT_MAKE_ERRCODE(ErrorModGeneral, ErrBspGeneral, 1) /* 一般错误 */

#ifdef __cplusplus
}
#endif

#endif
