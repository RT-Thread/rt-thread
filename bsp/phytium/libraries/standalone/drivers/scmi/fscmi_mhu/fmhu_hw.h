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
 * FilePath: fmhu_hw.h
 * Date: 2022-12-29 16:40:54
 * LastEditTime: 2022-12-29 16:40:55
 * Description:  This file is for mhu hardware define
 * 
 * Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0 liushengming 2023/12/30 init
 */
#ifndef FMHU_HW_H
#define FMHU_HW_H

#include "fio.h"
#include "fkernel.h"
#include "ftypes.h"
#include "ferror_code.h"
#include "fassert.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define AP_OS_STAT_OFFSET 	0x100
#define AP_OS_SET_OFFSET	    0x108
#define AP_OS_CLR_OFFSET	    0x110

#define AP_OS_INT_OFFSET         0x508

#define FMHU_DATA_MASK GENMASK(31, 0)

#define FMHU_READ_REG32(addr, reg_offset) FtIn32((addr) + (u32)(reg_offset))
#define FMHU_WRITE_REG32(addr, reg_offset, reg_value) FtOut32((addr) + (u32)(reg_offset), (u32)(reg_value))

/***************** Macros (Inline Functions) Definitions *********************/

#define FMHU_READ_STAT(addr) (u32)(FMHU_DATA_MASK & FMHU_READ_REG32(addr, AP_OS_STAT_OFFSET))

#define FMHU_READ_SECU(addr) (u32)((u32)(1U << 31) & FMHU_READ_REG32(addr, AP_OS_STAT_OFFSET))

#define FMHU_WRITE_SET(addr, dat) FMHU_WRITE_REG32((addr), AP_OS_SET_OFFSET, (dat))

#define FMHU_WRITE_CLR(addr, dat) FMHU_WRITE_REG32((addr), AP_OS_CLR_OFFSET, (dat))

#define FMHU_WRITE_INT(addr, dat) FMHU_WRITE_REG32((addr), AP_OS_INT_OFFSET, (dat))

/************************** Function Prototypes ******************************/

/**
 * @name: FMhuGetChanStatus
 * @msg: Mhu get channel status
 * @return {*}
 * @param {uintptr} addr
 */
static inline u32 FMhuGetChanStatus(uintptr addr)
{
    FASSERT(addr);

    return FMHU_READ_STAT(addr);
}

/**
 * @name: FMhuSendData
 * @msg: Mhu write the AP_OS_SET register to send share memory Data
 * @return {*}
 * @param {uintptr} addr
 * @param {u32} chan
 */
static inline void FMhuSendData(uintptr addr, u32 chan)
{
    FASSERT(addr);

    FMHU_WRITE_SET(addr, chan);

    return;
}

/**
 * @name: FMhuStartup
 * @msg: 
 * @return {*}
 * @param {uintptr} addr
 */
static inline void FMhuStartup(uintptr addr)
{
    FASSERT(addr);

    u32 val;

    val = FMHU_READ_STAT(addr);
    FMHU_WRITE_CLR(addr, val);

    /* irq set */

    return;
}

/**
 * @name: FMhuShutdown
 * @msg: 
 * @return {*}
 * @param {uintptr} addr
 */
static inline void FMhuShutdown(uintptr addr)
{
    FASSERT(addr);

    FMHU_WRITE_INT(addr,1);

    return;
}

/**
 * @name: FMhuLastTxDone
 * @msg: 
 * @return {*}
 * @param {uintptr} addr
 */
static inline u32 FMhuLastTxDone(uintptr addr)
{
    FASSERT(addr);

    return (FMHU_READ_SECU(addr) == (u32)(1U << 31));
}

#ifdef __cplusplus
}
#endif

#endif