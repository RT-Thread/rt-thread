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
 * FilePath: fiopad_sinit.c
 * Date: 2021-04-29 10:21:53
 * LastEditTime: 2022-02-18 08:29:20
 * Description:  This files is for the ioctrl static init functions
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2023/7/30    first release
 */


#include "fparameters.h"
#include "fassert.h"
#include "fioctrl.h"

extern FIOCtrlConfig FIOCtrlConfigTbl[FIOCTRL_NUM];

/**
 * @name: FIOCtrlLookupConfig
 * @msg: get ioctrl configs by id
 * @return {*}
 * @param {u32} instanceId, id of iopad ctrl
 */
const FIOCtrlConfig *FIOCtrlLookupConfig(u32 instance_id)
{
    FASSERT(instance_id < FIOCTRL_NUM);
    const FIOCtrlConfig *pconfig = NULL;
    u32 index;

    for (index = 0; index < (u32)FIOCTRL_NUM; index++)
    {
        if (FIOCtrlConfigTbl[index].instance_id == instance_id)
        {
            pconfig = &FIOCtrlConfigTbl[index];
            break;
        }
    }

    return (const FIOCtrlConfig *)pconfig;
}