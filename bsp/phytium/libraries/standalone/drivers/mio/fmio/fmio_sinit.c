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
 * FilePath: fmio_sinit.c
 * Date: 2022-06-20 20:33:25
 * LastEditTime: 2022-06-20 20:33:25
 * Description:  This file is for mio static initialization functionality
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  liushengming  2022/06/20  first commit
 */
#include "ftypes.h"
#include "fparameters.h"
#include "fassert.h"
#include "fmio.h"
#include "fmio_hw.h"


extern FMioConfig FMioConfigTbl[FMIO_NUM];

/***************** Macros (Inline Functions) Definitions *********************/
#define FMIO_DEBUG_TAG "MIO"
#define FMIO_ERROR(format, ...)   FT_DEBUG_PRINT_E(FMIO_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/

/**
 * @name: FMioLookupConfig
 * @msg: get mio configs by id
 * @param {u32} instance_id, id of mio ctrl
 * @return {FMioConfig *}, mio config address
 */
const FMioConfig *FMioLookupConfig(u32 instance_id)
{
    FASSERT(instance_id < FMIO_NUM);
    const FMioConfig *pconfig = NULL;
    u32 index;

    for (index = 0; index < (u32)FMIO_NUM; index++)
    {
        if (FMioConfigTbl[index].instance_id == instance_id)
        {
            pconfig = &FMioConfigTbl[index];
            break;
        }
    }
    return (const FMioConfig *)pconfig;
}
