/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2022-10-26  huanghe      first commit
 *
 */

#include "rtconfig.h"
#include <rtthread.h>

#include "fcpu_info.h"

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
    else if (*cpu_mask & 0x30)
    {
        *cluster_id = 0x200;
        if ((*cpu_mask & 0x30) == 0x30)
        {
            *target_list = 3;
        }
        else if ((*cpu_mask & 0x10))
        {
            *target_list = 1;
        }
        else
        {
            *target_list = 2;
        }
        *cpu_mask &= ~0x30;
    }
    else if (*cpu_mask & 0xc0)
    {
        *cluster_id = 0x300;
        if ((*cpu_mask & 0xc0) == 0xc0)
        {
            *target_list = 3;
        }
        else if ((*cpu_mask & 0x40))
        {
            *target_list = 1;
        }
        else
        {
            *target_list = 2;
        }
        *cpu_mask &= ~0xc0;
    }
    else
    {
        *cpu_mask = 0;
        return 0;
    }

    return 1;
}
