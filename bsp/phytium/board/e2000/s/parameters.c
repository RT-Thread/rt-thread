/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
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
 * FilePath: main.c
 * Date: 2022-10-08 23:16:43
 * LastEditTime: 2022-10-08 23:16:44
 * Description:  This file is for 
 * 
 * Modify History: 
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
 */
#include "rtconfig.h"
#include <rtthread.h>

#include "fcpu_info.h"
#include "fparameters.h"

u32 GetCpuMaskToAffval(u32 *cpu_mask, u32 *cluster_id, u32 *target_list)
{
    if (*cpu_mask == 0)
    {
        return 0;
    }

    *target_list = 0;
    *cluster_id = 0;

    if (*cpu_mask & 0x1)
    {
        *target_list = 1;
        *cluster_id = 0x200;
        *cpu_mask &= ~0x1;
    }
    else
    {
        *cpu_mask = 0;
        return 0;
    }

    return 1;
}
