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
 * FilePath: fusb_sinit.c
 * Date: 2022-02-11 13:33:11
 * LastEditTime: 2022-02-18 09:21:45
 * Description:  This files is for static initialization of USB
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/8    init version
 */

/***************************** Include Files *********************************/
#include "fparameters.h"
#include "fusb_private.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Variable Definitions *****************************/
extern const FUsbConfig FUSBHC_CONFIG_TBL[FUSB3_NUM];

/************************** Function Prototypes ******************************/
/**
 * @name: FUsbLookupConfig
 * @msg: 获取USB的默认配置
 * @return {const FUsbConfig *} USB默认配置
 * @param {u32} instance_id USB实例号
 */
const FUsbConfig *FUsbLookupConfig(u32 instance_id)
{
    const FUsbConfig *ptr = NULL;
    u32 index;

    for (index = 0; index < (u32)FUSB3_NUM; index++)
    {
        if (FUSBHC_CONFIG_TBL[index].instance_id == instance_id)
        {
            ptr = &FUSBHC_CONFIG_TBL[index];
            break;
        }
    }

    return (const FUsbConfig *)ptr;
}