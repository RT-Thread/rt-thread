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
 * FilePath: fpsci.c
 * Date: 2022-02-10 14:53:41
 * LastEditTime: 2022-02-17 17:33:51
 * Description:  This file is for cpu energy management
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe     2021/7/3     first release
 */

#include "fpsci.h"
#include "farm_smccc.h"
#include "ftypes.h"
#include "fcpu_info.h"
#include "ferror_code.h"
#include "fprintk.h"

FError PsciCpuOn(s32 cpu_id_mask, uintptr bootaddr)
{
    FError ret ;
    u64 cluster = 0;
    struct arm_smccc_res res;
    struct arm_smccc_quirk quirk;
    ret = GetCpuAffinityByMask(cpu_id_mask, &cluster);
    if (ret != ERR_SUCCESS)
    {
        f_printk("GetCpuAffinity is failed \r\n") ;
        return ret ;
    }
    __arm_smccc_smc(0xc4000003, cluster, bootaddr, 0, 0, 0, 0, 0,&res, &quirk);
    return ERR_SUCCESS ;
}
void PsciCpuReset(void)
{
    struct arm_smccc_res res;
    __arm_smccc_smc(0x84000009, 0, 0, 0, 0, 0, 0, 0, &res,NULL);
}