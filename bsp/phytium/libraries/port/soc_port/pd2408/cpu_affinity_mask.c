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
 * Date: 2024-06-24 10:33:28
 * LastEditTime: 2024-06-24 10:33:28
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangzq    2024/06/24      init commit
 */
#include "rtconfig.h"
#include <rtthread.h>

#include "fcpu_info.h"
#include "fparameters.h"

const int cluster_ids[FCORE_NUM] = {
    CORE0_AFF,
    CORE1_AFF,
    CORE2_AFF,
    CORE3_AFF,
    CORE4_AFF,
    CORE5_AFF,
    CORE6_AFF,
    CORE7_AFF
};

/**
 * @name: GetCpuMaskToAffval
 * @msg:  Convert information in cpu_mask to cluster_ID and target_list
 * @param {u32} *cpu_mask is each bit of cpu_mask represents a selected CPU, for example, 0x3 represents core0 and CORE1 .
 * @param {u32} *cluster_id is information about the cluster in which core resides ,format is
 * |--------[bit31-24]-------[bit23-16]-------------[bit15-8]-----------[bit7-0]
 * |--------Affinity level3-----Affinity level2-----Affinity level1-----Affinity level0
 * @param {u32} *target_list  is core mask in cluster
 * @return {u32} 0 indicates that the conversion was not successful , 1 indicates that the conversion was successful
 */
u32 GetCpuMaskToAffval(u32 *cpu_mask, u32 *cluster_id, u32 *target_list)
{
    if (*cpu_mask == 0)
    {
        return 0;
    }

    *target_list = 0;
    *cluster_id = 0;

    for (int i = 0; i < sizeof(cluster_ids) / sizeof(cluster_ids[0]); i++)
    {
        if (*cpu_mask & (1 << i))
        {
            *cpu_mask &= ~(1 << i) ;
            *cluster_id = cluster_ids[i];
            *target_list = 1;
            break;
        }
    }

    return 1;
}

