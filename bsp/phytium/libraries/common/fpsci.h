/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: fpsci.h
 * Created Date: 2023-06-21 16:13:14
 * Last Modified: 2023-06-27 15:33:23
 * Description:  This file is for
 *
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 *  1.0     huanghe   2023-06-21        first release
 */

#ifndef FPSCI_H
#define FPSCI_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "ftypes.h"

/* 版本掩码 */

#define FPSCI_VERSION_MASK 0x0000FFFF
#define FPSCI_MAJOR_VERSION(x) ((x) >> 16)
#define FPSCI_MINOR_VERSION(x) ((x) & 0xFFFF)

/* Power State 参数 */

#define FPSCI_POWER_STATE_ID_MASK            0xFFFF
#define FPSCI_POWER_STATE_ID_SHIFT           0
#define FPSCI_POWER_STATE_TYPE_SHIFT         16
#define FPSCI_POWER_STATE_AFFL_SHIFT         24

/* stateid encoding */
#define FPSCI_STATEID_CORE_RETENTION    0x2
#define FPSCI_STATEID_CORE_POWERDOWN    0x8


/* 版本掩码 */

#define FPSCI_VERSION_MASK 0x0000FFFF


/* 定义复位模式 */

#define FPSCI_SYSTEM_RESET_TYPE_COLD  0
#define FPSCI_SYSTEM_RESET_TYPE_WARM  1

/* 定义PSCI 错误码 */

#define FPSCI_SUCCESS           0
#define FPSCI_NOT_SUPPORTED         -1
#define FPSCI_INVALID_PARAMS            -2
#define FPSCI_DENIED                -3
#define FPSCI_ALREADY_ON            -4
#define FPSCI_ON_PENDING            -5
#define FPSCI_INTERNAL_FAILURE      -6
#define FPSCI_NOT_PRESENT           -7
#define FPSCI_DISABLED          -8
#define FPSCI_INVALID_ADDRESS       -9

int FPsciInit(void) ;
int FPsciVersion(void) ;
int FPsciCpuSuspend(u32 power_state, unsigned long entry_point_address, unsigned long context_id) ;
int FPsciCpuOn(unsigned long target_cpu, unsigned long entry_point_address, unsigned long context_id) ;
int FPsciAffinityInfo(unsigned long target_affinity, u32 lowest_affinity_level) ;
void FPsciSystemReset(u32 reset_type) ;
int FPsciFeatures(u32 psci_fid) ;
int FPsciCpuOff(void) ;
int FPsciCpuMaskOn(s32 cpu_id_mask, uintptr bootaddr) ;
#ifdef __cplusplus
}
#endif

#endif /* __ASM_ARM_MACRO_H__ */

