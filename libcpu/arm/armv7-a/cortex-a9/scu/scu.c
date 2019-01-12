/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include "scu.h"
#include <rtthread.h>
#include <cp15.h>
#include <bitopr.h>
#include <stdbool.h>

SCU* scu_get(void)
{
    static SCU* s_scu_base = 0;
    if (s_scu_base == 0) {
        if (armv7_get_cortex_type() == CORTEX_TYPE_A9) {
            // [ref]cortex_a9_mpcore_trm_100486_0401_10_en.pdf: 1.5 Private Memory Region
            //      0x0000 - 0x00FC SCU registers
            s_scu_base = (SCU*)(rt_cpu_cbar_get() + 0x0000);
        }
        else {
            RT_ASSERT(false);
        }
    }
    return s_scu_base;
}

// enable scu
void scu_enable(void)
{
    SCU* pScu = scu_get();

    // [ref]cortex_a9_mpcore_trm_100486_0401_10_en.pdf: 2.2.2 SCU Control Register
    //      Bit     Field               Description
    //      0       SCU enable          0 = SCU disable. This is the default setting.
    //                                  1 = SCU enable.
    pScu->control |= _B(0);
}

// Get the number of cpu
// @return the number of cpu
uint32_t scu_get_cpu_nums(void)
{
    SCU* pScu = scu_get();

    // [ref]cortex_a9_mpcore_trm_100486_0401_10_en.pdf: 2.2.3 SCU Configuration Register
    //      Bit     Field               Description
    //      1-0     Number of CPUs      Number of CPUs present in the Cortex-A9 MPCore processor
    //                                  0b00 One Cortex - A9 processor, CPU0.
    //                                  0b01 Two Cortex - A9 processors, CPU0 and CPU1.
    //                                  0b10 Three Cortex - A9 processors, CPU0, CPU1, and CPU2.
    //                                  0b11 Four Cortex - A9 processors, CPU0, CPU1, CPU2, and CPU3.
    return pScu->config & _B_B(1, 0);
}

// Get the size encoding of tag ram
// @return the size encoding of tag ram
uint32_t scu_get_tag_ram_size_encoding(uint32_t cpuIdx)
{
    SCU* pScu = scu_get();

    // [ref]cortex_a9_mpcore_trm_100486_0401_10_en.pdf: 2.2.3 SCU Configuration Register
    //      Bit     Field               Description
    //      15-14   CPU3 Tag RAM sizes  CPU3~CPU0 Tag RAM sizes:0b00 16KB cache, 64 indexes per tag RAM
    //      13-12   CPU2 Tag RAM sizes                          0b01 32KB cache, 128 indexes per tag RAM.
    //      11-10   CPU1 Tag RAM sizes                          0b10 64KB cache, 256 indexes per tag RAM.
    //      9-8     CPU0 Tag RAM sizes                          0b11 Reserved
    cpuIdx &= 0x3;
    uint32_t tagRamSizeEncoding = _E_B_B(pScu->config, 15, 8);
    return tagRamSizeEncoding >> (cpuIdx << 2);
}

// get cpus that in smp
// @return cpus that in smp
uint32_t scu_get_cpus_in_smp(void)
{
    SCU* pScu = scu_get();

    // [ref]cortex_a9_mpcore_trm_100486_0401_10_en.pdf: 2.2.3 SCU Configuration Register
    //      Bit     Field               Description
    //      7-4     CPUs SMP            Shows the Cortex-A9 processors that are in Symmetric Multi-processing (SMP) or Asymmetric Multiprocessing (AMP)mode.
    //                                  0 = This Cortex - A9 processor is in AMP mode, not taking part in coherency, or not present.
    //                                  1 = This Cortex - A9 processor is in SMP mode, taking part in coherency.
    //                                  Bit 7 is for CPU3
    //                                  Bit 6 is for CPU2
    //                                  Bit 5 is for CPU1
    //                                  Bit 4 is for CPU0.
    return _E_B_B(pScu->config, 7, 4);
}

// Invalidates the SCU copy of the tag rams for the specified core
// @param cpuIdx 0x0~0x3 = CPU0~CPU3
// @param wayMask The ways to invalidate. Pass 0xF to invalidate all ways
void scu_secure_invalidate(uint32_t cpuIdx, uint32_t wayMask)
{
    SCU* pScu = scu_get();

    // [ref]cortex_a9_mpcore_trm_100486_0401_10_en.pdf: 2.2.5 SCU Invalidate All Registers in Secure State Register
    //      Bit     Field               Description
    //      15-12   CPU3 ways           Specifies the ways that must be invalidated for CPU3
    //      11-8    CPU2 ways           Specifies the ways that must be invalidated for CPU2
    //      7-4     CPU1 ways           Specifies the ways that must be invalidated for CPU1
    //      3-0     CPU0 ways           Specifies the ways that must be invalidated for CPU0
    cpuIdx &= 0x3;
    wayMask &= 0xF;
    pScu->invalidAllRegsInSecureState = wayMask << (cpuIdx << 2);
}