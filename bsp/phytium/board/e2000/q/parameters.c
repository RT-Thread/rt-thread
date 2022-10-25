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


/**
 * @name: GetCpuMaskToAffval
 * @msg:  参考 GetCpuMaskToAffval 进行参数的重新定义 ，两个小核心定义的id 为0，1 ，两个大核的id 为 2，3
 * @return {*}
 * @note: 
 * @param {u32} *cpu_mask
 * @param {u32} *cluster_id
 * @param {u32} *target_list
 */
u32 GetCpuMaskToAffval(u32 *cpu_mask, u32 *cluster_id, u32 *target_list)
{
    if (*cpu_mask == 0)
    {
        return 0;
    }

    *target_list = 0;
    *cluster_id = 0;

    if (*cpu_mask & 0x4)
    {
        *target_list = 1;
        *cpu_mask &= ~0x4;
    }
    else if (*cpu_mask & 0x8)
    {
        *cluster_id = 0x100;
        *target_list = 1;
        *cpu_mask &= ~0x8;
    }
    else if (*cpu_mask & 0x3)
    {
        *cluster_id = 0x200;
        if ((*cpu_mask & 0x3) == 0x3)
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
        *cpu_mask &= ~0x3;
    }
    else
    {
        *cpu_mask = 0;
        return 0;
    }

    return 1;
}