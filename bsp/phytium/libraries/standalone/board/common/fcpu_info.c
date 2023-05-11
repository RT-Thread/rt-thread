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
 * FilePath: cpu_info.c
 * Date: 2022-03-08 19:37:19
 * LastEditTime: 2022-03-15 11:18:14
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "fcpu_info.h"
#include "ferror_code.h"
#include "fparameters.h"
#include "fprintk.h"

FError GetCpuId(u32 *cpu_id_p)
{
    u32 affinity = GetAffinity();
    FError ret = ERR_SUCCESS ;

    switch (affinity & 0xfff)
    {
#ifdef CORE0_AFF
        case CORE0_AFF:
            *cpu_id_p = 0 ;
            break;
#endif
#ifdef CORE1_AFF
        case CORE1_AFF:
            *cpu_id_p = 1 ;
            break;
#endif
#ifdef CORE2_AFF
        case CORE2_AFF:
            *cpu_id_p = 2;
            break;
#endif
#ifdef CORE3_AFF
        case CORE3_AFF:
            *cpu_id_p = 3 ;
            break;
#endif
#ifdef CORE4_AFF
        case CORE4_AFF:
            *cpu_id_p = 4 ;
            break;
#endif
#ifdef CORE5_AFF
        case CORE5_AFF:
            *cpu_id_p = 5 ;
            break;
#endif
#ifdef CORE6_AFF
        case CORE6_AFF:
            *cpu_id_p = 6 ;
            break;
#endif
#ifdef CORE7_AFF
        case CORE7_AFF:
            *cpu_id_p = 7 ;
            break;
#endif
        default:
            ret = ERR_GENERAL ;
            break;
    }
    return ret;
}

/**
 * @name: GetCpuAffinityByMask
 * @msg:  Determine the cluster information using the CPU ID
 * @param {u32} cpu_id cpu id mask .for example : 1 is core0 ,2 is core1 .....
 * @param {u64} *affinity_level_p cluster information , format is:
 * |--------[bit31-24]-------[bit23-16]-------------[bit15-8]--------[bit7-0]
 * |--------Affinity level3-----Affinity level2-----Affinity level1---Affinity level0
 * @return {*} ERR_SUCCESS is ok
 */
FError GetCpuAffinityByMask(u32 cpu_id_mask, u64 *affinity_level_p)
{
    FError ret = ERR_SUCCESS ;
    switch (cpu_id_mask)
    {
#ifdef CORE0_AFF
        case (1<<0):
            *affinity_level_p = CORE0_AFF;
            break ;
#endif
#ifdef CORE1_AFF
        case (1<<1):
            *affinity_level_p = CORE1_AFF;
            break ;
#endif
#ifdef CORE2_AFF
        case (1<<2):
            *affinity_level_p = CORE2_AFF;
            break ;
#endif
#ifdef CORE3_AFF
        case (1<<3):
            *affinity_level_p = CORE3_AFF;
            break ;
#endif
#ifdef CORE4_AFF
        case (1<<4):
            *affinity_level_p = CORE4_AFF;
            break ;
#endif
#ifdef CORE5_AFF
        case (1<<5):
            *affinity_level_p = CORE5_AFF;
            break ;
#endif
#ifdef CORE6_AFF
        case (1<<6):
            *affinity_level_p = CORE6_AFF;
            break ;
#endif
#ifdef CORE7_AFF
        case (1<<7):
            *affinity_level_p = CORE7_AFF;
            break ;
#endif
        default:
            ret = ERR_GENERAL;
            break;
    }
    return ret;
}


/**
 * @name: GetCpuAffinity
 * @msg:  Determine the cluster information using the CPU ID
 * @param {u32} cpu_id cpu id .for example : 0 is core0 ,1 is core1 .....
 * @param {u64} *affinity_level_p cluster information , format is:
 * |--------[bit31-24]-------[bit23-16]-------------[bit15-8]--------[bit7-0]
 * |--------Affinity level3-----Affinity level2-----Affinity level1---Affinity level0
 * @return {*} ERR_SUCCESS is ok
 */
FError GetCpuAffinity(u32 cpu_id, u64 *affinity_level_p)
{
    FError ret = ERR_SUCCESS ;
    switch (cpu_id)
    {
#ifdef CORE0_AFF
        case (0):
            *affinity_level_p = CORE0_AFF;
            break ;
#endif
#ifdef CORE1_AFF
        case (1):
            *affinity_level_p = CORE1_AFF;
            break ;
#endif
#ifdef CORE2_AFF
        case (2):
            *affinity_level_p = CORE2_AFF;
            break ;
#endif
#ifdef CORE3_AFF
        case (3):
            *affinity_level_p = CORE3_AFF;
            break ;
#endif
#ifdef CORE4_AFF
        case (4):
            *affinity_level_p = CORE4_AFF;
            break ;
#endif
#ifdef CORE5_AFF
        case (5):
            *affinity_level_p = CORE5_AFF;
            break ;
#endif
#ifdef CORE6_AFF
        case (6):
            *affinity_level_p = CORE6_AFF;
            break ;
#endif
#ifdef CORE7_AFF
        case (7):
            *affinity_level_p = CORE7_AFF;
            break ;
#endif
        default:
            ret = ERR_GENERAL;
            break;
    }
    return ret;
}


/**
 * @name: UseAffinityGetCpuId
 * @msg:  Get the core value from affinity level
 * @param {u64} affinity_level is cpu affinity level value
 * @param {u32*} cpu_id_p is pointer to get cpu id value
 * @return {*} ERR_SUCCESS is ok , ERR_GENERAL is fail
 */
FError UseAffinityGetCpuId(u64 affinity_level, u32 *cpu_id_p)
{
    FError ret = ERR_SUCCESS ;
    switch (affinity_level)
    {
#ifdef CORE0_AFF
        case CORE0_AFF:
            *cpu_id_p = 0;
            break ;
#endif
#ifdef CORE1_AFF
        case CORE1_AFF:
            *cpu_id_p = 1;
            break ;
#endif
#ifdef CORE2_AFF
        case CORE2_AFF:
            *cpu_id_p = 2;
            break ;
#endif
#ifdef CORE3_AFF
        case CORE3_AFF:
            *cpu_id_p = 3;
            break ;
#endif
#ifdef CORE4_AFF
        case CORE4_AFF:
            *cpu_id_p = 4;
            break ;
#endif
#ifdef CORE5_AFF
        case CORE5_AFF:
            *cpu_id_p = 5;
            break ;
#endif
#ifdef CORE6_AFF
        case CORE6_AFF:
            *cpu_id_p = 6;
            break ;
#endif
#ifdef CORE7_AFF
        case CORE7_AFF:
            *cpu_id_p = 7;
            break ;
#endif
        default:
            ret = ERR_GENERAL;
            break;
    }
    return ret;
}
