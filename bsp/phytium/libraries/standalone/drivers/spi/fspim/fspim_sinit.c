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
 * FilePath: fspim_sinit.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:08:24
 * Description:  This file is for providing spim init basic func.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/3   init commit
 * 1.1   zhugengyu  2022/4/15   support test mode
 */

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fparameters.h"
#include "fspim.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Variable Definitions *****************************/

extern const FSpimConfig FSPIM_CONFIG_TBL[FSPI_NUM];

/************************** Function Prototypes ******************************/
/**
 * @name: FSpimLookupConfig
 * @msg: 获取FSPIM实例的默认配置
 * @return {const FSpimConfig *} FSPIM实例的默认配置
 * @param {u32} instance_id, SPI控制器ID
 */
const FSpimConfig *FSpimLookupConfig(u32 instance_id)
{
    const FSpimConfig *ptr = NULL;
    u32 index;

    for (index = 0; index < (u32)FSPI_NUM; index++)
    {
        if (FSPIM_CONFIG_TBL[index].instance_id == instance_id)
        {
            ptr = &FSPIM_CONFIG_TBL[index];
            break;
        }
    }

    return (const FSpimConfig *)ptr;
}
