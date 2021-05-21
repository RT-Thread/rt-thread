/*
 * @[H]: Copyright (C) 2014-2021 Phytium Technology.  All rights reserved.
 * 
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 * 
 *  Use of the Software is limited solely to applications:
 *  (a) running on a Phytium device, or
 *  (b) that interact with a Phytium device through a bus or interconnect.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  PHYTIUM  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 *  OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 * 
 *  Except as contained in this notice, the name of the Phytium shall not be used
 *  in advertising or otherwise to promote the sale, use or other dealings in
 *  this Software without prior written authorization from Phytium. 
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
