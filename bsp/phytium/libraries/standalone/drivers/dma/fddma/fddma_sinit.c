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
 * FilePath: fddma_sinit.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:24:47
 * Description:  This file is for static initialization
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/5/13    init commit
 */

/***************************** Include Files *********************************/
#include "fparameters.h"
#include "fassert.h"

#include "fddma_hw.h"
#include "fddma.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/
extern const FDdmaConfig fddma_cfg_tbl[FDDMA_INSTANCE_NUM];

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
/**
 * @name: FDdmaLookupConfig
 * @msg: 获取DDMA实例默认配置
 * @return {const FDdmaConfig *} DDMA控制器默认配置
 * @param {u32} instance_id, DDMA实例号
 */
const FDdmaConfig *FDdmaLookupConfig(u32 instance_id)
{
    const FDdmaConfig *ptr = NULL;
    u32 index;

    for (index = 0; index < (u32)FDDMA_INSTANCE_NUM; index++)
    {
        if (fddma_cfg_tbl[index].id == instance_id)
        {
            ptr = &fddma_cfg_tbl[index];
            break;
        }
    }

    return (const FDdmaConfig *)ptr;
}