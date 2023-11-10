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
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:01:10
 * Description:  This files is for getting default configuration of specific IOPad instance_id
 *
 * Modify History:
 *  Ver   Who           Date        Changes
 * -----  ------        --------    --------------------------------------
 * 1.0   zhangyan   2023/7/3    first release
 */

#include "fparameters.h"
#include "fassert.h"
#include "fiopad.h"

extern FIOPadConfig FIOPadConfigTbl[FIOPAD_NUM];

/**
 * @name: FIOPadLookupConfig
 * @msg: get iopad configs by id
 * @return {*}
 * @param {u32} instanceId, id of iopad ctrl
 */
const FIOPadConfig *FIOPadLookupConfig(u32 instance_id)
{
    FASSERT(instance_id < FIOPAD_NUM);
    const FIOPadConfig *pconfig = NULL;
    u32 index;

    for (index = 0; index < (u32)FIOPAD_NUM; index++)
    {
        if (FIOPadConfigTbl[index].instance_id == instance_id)
        {
            pconfig = &FIOPadConfigTbl[index];
            break;
        }
    }

    return (const FIOPadConfig *)pconfig;
}