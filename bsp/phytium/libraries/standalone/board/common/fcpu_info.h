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
 * FilePath: fcpu_info.h
 * Date: 2022-03-08 19:37:19
 * LastEditTime: 2022-03-15 11:18:07
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef BOARD_COMMON_CPU_INFO_H
#define BOARD_COMMON_CPU_INFO_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ftypes.h"
#include "ferror_code.h"
u32 GetAffinity(void);
FError GetCpuId(u32 *cpu_id_p);
FError GetCpuAffinity(u32 cpu_id, u64 *cluster_value_p);
FError GetCpuAffinityByMask(u32 cpu_id, u64 *affinity_level_p);
FError UseAffinityGetCpuId(u64 affinity_level, u32 *cpu_id_p);
u32 GetCpuMaskToAffval(u32 *cpu_mask, u32 *cluster_id, u32 *target_list);
#ifdef __cplusplus
}
#endif

#endif // !