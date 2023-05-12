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
 * FilePath: fgdma_sinit.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:15
 * Description:  This file is for gdma static init
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2021/11/5    init commit
 * 1.1   zhugengyu  2022/5/16    modify according to tech manual.
 */

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fparameters.h"

#include "fgdma.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Variable Definitions *****************************/
extern const FGdmaConfig fgdma_cfg_tbl[FGDMA_INSTANCE_NUM];

/************************** Function Prototypes ******************************/
/**
 * @name: FGdmaLookupConfig
 * @msg: 获取GDMA控制器默认配置
 * @return {const FGdmaConfig *} 控制器默认配置
 * @param {u32} instance_id, GDMA控制器ID
 */
const FGdmaConfig *FGdmaLookupConfig(u32 instance_id)
{
    const FGdmaConfig *ptr = NULL;
    u32 index;

    for (index = 0; index < (u32)FGDMA_INSTANCE_NUM; index++)
    {
        if (fgdma_cfg_tbl[index].instance_id == instance_id)
        {
            ptr = &fgdma_cfg_tbl[index];
            break;
        }
    }

    return (const FGdmaConfig *)ptr;
}