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
 * FilePath: fgic_sinit.c
 * Date: 2022-03-30 15:00:29
 * LastEditTime: 2022-03-30 15:00:29
 * Description: This file is for gic static variables implementation.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/4/16   init commit
 */


#include "fgic.h"

extern FGicConfig fgic_config[FGIC_NUM];


/**
 * @name: FGicLookupConfig
 * @msg:  Gets the default configuration parameters in the current GIC
 * @param {u32} instance_id
 * @return {*}
 */
FGicConfig *FGicLookupConfig(u32 instance_id)
{
    FGicConfig *ptr = NULL;
    u32 index;

    for (index = 0; index < (u32)FGIC_NUM; index++)
    {
        if (fgic_config[index].instance_id == instance_id)
        {
            ptr = &fgic_config[index];
            break;
        }
    }

    return (FGicConfig *)ptr;
}
