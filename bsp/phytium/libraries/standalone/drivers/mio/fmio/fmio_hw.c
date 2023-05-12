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
 * FilePath: fmio_hw.c
 * Date: 2022-06-20 21:05:23
 * LastEditTime: 2022-06-20 21:05:23
 * Description:  This file is for mio hardware operation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  liushengming 2022/06/20 first commit
 */

/***************************** Include Files *********************************/

#include "fmio_hw.h"
#include "ftypes.h"
#include "fassert.h"
#include "fmio.h"
/***************** Macros (Inline Functions) Definitions *********************/

#define FMIO_DEBUG_TAG "MIO-HW"
#define FMIO_ERROR(format, ...)   FT_DEBUG_PRINT_E(FMIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FMIO_INFO(format, ...)    FT_DEBUG_PRINT_I(FMIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FMIO_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FMIO_DEBUG_TAG, format, ##__VA_ARGS__)
/************************** Function Prototypes ******************************/

/**
 * @name: FMioSelectFunc
 * @msg: 设置Mio功能
 * @return {*}
 * @param {uintptr} addr
 * @param {u32} mio_type
 */
FError FMioSelectFunc(uintptr addr, u32 mio_type)
{
    FASSERT(mio_type < FMIO_NUM_OF_MIO_FUNC);
    FASSERT(addr);

    u32 reg_val;

    reg_val = FMioReadStatus(addr);

    if (mio_type == reg_val)
    {
        return FMIO_SUCCESS;
    }

    FMioWriteFunc(addr, mio_type);

    return FMIO_SUCCESS;
}

/**
 * @name: FMioGetMioFunc
 * @msg: 获取Mio状态
 * @return {*}
 * @param {uintptr} addr
 */
u32 FMioGetFunc(uintptr addr)
{
    FASSERT(addr);

    return FMioReadStatus(addr);
}

/**
 * @name: FMioGetVersion
 * @msg: 获取版本信息，默认32'h1
 * @return {*}
 * @param {uintptr} addr
 */
u32 FMioGetVersion(uintptr addr)
{
    FASSERT(addr);

    return FMioReadVersion(addr);
}
