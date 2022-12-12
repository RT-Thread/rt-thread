/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-21 10:43:52
 * @LastEditTime: 2021-04-21 10:43:53
 * @Description:  Description of file
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */

#include "ft_psci.h"
#include "ft_smc.h"
#include "ft_cpu.h"
#include "ft_printf.h"

#define PSCI_CPUON_NUM 0x84000003
#define PSCI_RESET_NUM 0x84000009

/**
 * @name: FPsci_CpuOn
 * @msg:  Power up a core
 * @in param CpuList:  Bits[24:31]: Must be zero.
 *                     Bits[16:23] Aff2: Match Aff2 of target core MPIDR
 *                     Bits[8:15] Aff1: Match Aff1 of target core MPIDR
 *                     Bits[0:7] Aff0: Match Aff0 of target core MPIDR
 * @in param BootAddr:  a 32-bit entry point physical address (or IPA).
 * @return {None}
 */
void FPsci_CpuOn(s32 CpuIdMask, u32 BootAddr)
{

    FSmc_Data_t Input = {0};
    FSmc_Data_t Output = {0};
    Input.FunctionIdentifier = PSCI_CPUON_NUM;

    if ((1 << 0) == CpuIdMask)
    {
        Input.a1 = SoftAffiTable[0];
    }
    else if ((1 << 1) == CpuIdMask)
    {
        Input.a1 = SoftAffiTable[1];
    }
    else if ((1 << 2) == CpuIdMask)
    {
        Input.a1 = SoftAffiTable[2];
    }
    else if ((1 << 3) == CpuIdMask)
    {
        Input.a1 = SoftAffiTable[3];
    }
    else
    {
        return;
    }

    /*input.a2 = (u32)(BootAddr >> 32);*/
    Input.a2 = (u32)(BootAddr & 0xFFFFFFFF);
    FSmc_Call(&Input, &Output);
    __asm__ volatile("NOP");
}

void FPsci_Reset(void)
{

    FSmc_Data_t Input = {0};
    FSmc_Data_t Output = {0};

    Input.FunctionIdentifier = PSCI_RESET_NUM;
    FSmc_Call(&Input, &Output);

    __asm__ volatile("NOP");
    while (1)
        ;
}
