/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: fi2s_sinit.c
 * Created Date: 2023-06-01 16:46:27
 * Last Modified: 2023-06-13 17:27:07
 * Description:  This file is for
 * 
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------  -------- --------------------------------------
 *  1.0  Wangzq     2023/05/09  Modify the format and establish the version
 */

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fparameters.h"
#include "fi2s.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Variable Definitions *****************************/

extern const FI2sConfig FI2S_CONFIG_TBL[FI2S_NUM];
/************************** Function Prototypes ******************************/
/**
 * @name: FI2sLookupConfig
 * @msg: 获取I2C驱动的默认配置参数
 * @return {const FI2sConfig*} 驱动默认参数
 * @param {u32} instance_id, 当前控制的I2S控制器实例号
 */
const FI2sConfig *FI2sLookupConfig(u32 instance_id)
{
    const FI2sConfig *ptr = NULL;
    u32 index;

    for (index = 0; index < (u32)FI2S_NUM; index++)
    {
        if (FI2S_CONFIG_TBL[index].instance_id == instance_id)
        {
            ptr = &FI2S_CONFIG_TBL[index];
            break;
        }
    }

    return (const FI2sConfig *)ptr;
}
