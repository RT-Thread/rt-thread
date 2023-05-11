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
 * FilePath: fsdmmc_sinit.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:55:09
 * Description:  This file contains the implementation of the fsdmmc driver's static
 * initialization functionality.
 * 
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/2    init
 */


/* - This file contains the implementation of driver's static initialization functionality.
- 驱动静态初始化  */

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fparameters.h"

#include "fsdmmc.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Variable Definitions *****************************/

extern const FSdmmcConfig FSDMMC_CONFIG_TBL[FSDMMC_NUM];

/************************** Function Prototypes ******************************/
/**
 * @name: FSdmmcLookupConfig
 * @msg: 获取FSDMMC控制器默认配置
 * @return {const FSdmmcConfig *}  FSDMMC默认配置，返回NULL如果找不到默认配置
 * @param {u32} instance_id 驱动控制器ID
 * @note instance_id从0开始，取决于FSDMMC控制器的个数
 */
const FSdmmcConfig *FSdmmcLookupConfig(u32 instance_id)
{
    const FSdmmcConfig *ptr = NULL;
    u32 index;

    for (index = 0; index < (u32)FSDMMC_NUM; index++)
    {
        if (FSDMMC_CONFIG_TBL[index].instance_id == instance_id)
        {
            ptr = &FSDMMC_CONFIG_TBL[index];
            break;
        }
    }

    return (const FSdmmcConfig *)ptr;
}