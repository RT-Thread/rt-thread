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
 * FilePath: fcpu_affinity_mask.c
 * Date: 2023-11-6 10:33:28
 * LastEditTime: 2023-11-6 10:33:28
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhangyan    2023/11/6       init commit
 */
#include "fparameters.h"

u32 GetCpuMaskToAffval(u32 *cpu_mask, u32 *cluster_id, u32 *target_list)
{
    if (*cpu_mask == 0)
    {
        return 0;
    }

    *target_list = 0;
    *cluster_id = 0;

    if (*cpu_mask & 0x3)
    {
        if ((*cpu_mask & 0x3) == 0x3)
        {
            *target_list = 3;
        }
        else if ((*cpu_mask & 0x1))
        {
            *target_list = 1;
        }
        else
        {
            *target_list = 2;
        }
        *cpu_mask &= ~0x3;
    }
    else if (*cpu_mask & 0xc)
    {
        *cluster_id = 0x100;
        if ((*cpu_mask & 0xc) == 0xc)
        {
            *target_list = 3;
        }
        else if ((*cpu_mask & 0x4))
        {
            *target_list = 1;
        }
        else
        {
            *target_list = 2;
        }
        *cpu_mask &= ~0xc;
    }
    else
    {
        *cpu_mask = 0;
        return 0;
    }

    return 1;
}
