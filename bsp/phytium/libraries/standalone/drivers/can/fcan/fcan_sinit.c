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
 * FilePath: fcan_sinit.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:29:15
 * Description:  This files is for getting default configuration of specific can instance_id
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/5/26  first releases
 */


#include "fcan.h"
#include "fparameters.h"
#include "fassert.h"

extern const FCanConfig FCanConfigTbl[FCAN_NUM];

/**
 * @name: FCanLookupConfig
 * @msg:  get default configuration of specific can instance_id.
 * @param {u32} instance_id, instance id of Can controller
 * @return {FCanConfig*} Default configuration parameters of Can
 */
const FCanConfig *FCanLookupConfig(u32 instance_id)
{
    FASSERT(instance_id < FCAN_NUM);
    const FCanConfig *pconfig = NULL;
    u32 index;

    for (index = 0; index < (u32)FCAN_NUM; index++)
    {
        if (FCanConfigTbl[index].instance_id == instance_id)
        {
            pconfig = &FCanConfigTbl[index];
            break;
        }
    }
    return (const FCanConfig *)pconfig;
}
