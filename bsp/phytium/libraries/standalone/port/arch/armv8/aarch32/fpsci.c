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
 * LastEditTime: 2022-02-17 17:30:35
 * Description:  This file is for cpu energy management
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe     2021/7/3     first release
 */


#include "fpsci.h"
#include "fsmc.h"
#include "fcpu_info.h"
#include "ferror_code.h"
#include "fparameters.h"
#include "ftypes.h"

#define PSCI_CPUON_NUM 0x84000003
#define PSCI_RESET_NUM 0x84000009

/**
 * @name: FPsci_CpuOn
 * @msg:  Power up a core
 * @in param cpu_id_mask: cpu id mask
 * @in param bootaddr:  a 32-bit entry point physical address (or IPA).
 * @return FError
 */
FError PsciCpuOn(s32 cpu_id_mask, uintptr bootaddr)
{
    FError ret ;
    u64 cluster = 0;
    FSmc_Data_t input = {0};
    FSmc_Data_t output = {0};
    input.function_identifier = PSCI_CPUON_NUM;
    ret = GetCpuAffinityByMask(cpu_id_mask, &cluster);
    if (ret != ERR_SUCCESS)
    {
        return ret;
    }

    input.a1 = cluster;

    input.a2 = (u32)(bootaddr & 0xFFFFFFFF);
    FSmcCall(&input, &output);
    __asm__ volatile("NOP");
    return ERR_SUCCESS;
}

void PsciCpuReset(void)
{

    FSmc_Data_t input = {0};
    FSmc_Data_t output = {0};

    input.function_identifier = PSCI_RESET_NUM;
    FSmcCall(&input, &output);

    __asm__ volatile("NOP");
    while (1)
        ;
}
