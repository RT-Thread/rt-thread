/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include "cp15.h"

// A9 ACTLR
// [ref]DDI0388I_cortex_a9_r4p1_trm.pdf: 4.3.10 Auxiliary Control Register
// A8 ACTLR
// [ref]DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.26 c1, Auxiliary Control Register
//      MRC p15, 0, <Rd>, c1, c0, 1; Read ACTLR
//      MCR p15, 0, <Rd>, c1, c0, 1; Write ACTLR
#define _ARM_CP_ACTLR_R(actlr) _ARM_CP_R(p15, 0, actlr, c1, c0, 1)
#define _ARM_CP_ACTLR_W(actlr) _ARM_CP_W(p15, 0, actlr, c1, c0, 1)

void rt_cpu_auxctl_feature_enable(uint32_t enFlag)
{
    uint32_t actlr;
    _ARM_CP_ACTLR_R(actlr);
    actlr |= enFlag;
    _ARM_CP_ACTLR_W(actlr);
}
void rt_cpu_auxctl_feature_disable(uint32_t disFlag)
{
    uint32_t actlr;
    _ARM_CP_ACTLR_R(actlr);
    actlr &= ~disFlag;
    _ARM_CP_ACTLR_W(actlr);
}

// SCTLR, System Control Register
// [ref]DDI0406C_d_armv7ar_arm.pdf: B4.1.130 SCTLR, System Control Register, VMSA
//      DDI0388I_cortex_a9_r4p1_trm.pdf: 4.3.9 System Control Register
//      DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.25 c1, Control Register
//      Bit     Field           Description                                                     cortex-a9   cortex-a8
//      31      reverse
//      30      TE              0/1 = Enables ARM/Thumb exception generation                    supported   supported
//      29      AFE             0 = AP[0] behavior defined; 1 = access flag behavior defined    supported   supported
//      28      TRE             0/1 = TEX remap disabled/enable                                 supported   supported
//      27      NMFI            0/1 = FIQ exceptions can/cannot be masked by software           supported   supported
//      26      reverse
//      25      EE              0/1 = CPSR E bit is set to 0/1 on an exception                  supported   supported
//      24      VE              0/1 = FIQ and IRQ vectors from/not from the vector table
//      23      reverse
//      22      U               In ARMv7 this bit is RAO/SBOP,
//      21      FI              Fast interrupts configuration enable
//      20      UWXN            if implementation includes the Virtualization Extensions
//      19      WXN             if implementation includes the Virtualization Extensions
//      18      reverse
//      17      HA              0/1 = Hardware Access flag disable/enable                       supported   supported
//      16-15   reverse
//      14      RR              0/1 = Normal replacement strategy/Predictable strategy          supported
//      13      V               0/1 = Normal/High exception vectors selected                    supported   supported
//      12      I               0/1 = instruction caching disabled/enable                       supported   supported
//      11      Z               0/1 = program flow prediction disabled/enable                   supported   supported
//      10      SW              0/1 = SWP and SWPB are UNDEFINED/DEFINED                        supported
//      9-8     reverse         
//      7       B               In ARMv7 this bit is RAZ/SBZP
//      6       reverse         
//      5       CP15BEN         0/1 = CP15 barrier operations disabled/enable
//      4-3     reverse         
//      2       C               0/1 = data caching disabled/enable                              supported   supported
//      1       A               0/1 = strict alignment fault checking disabled/enabled          supported   supported
//      0       M               0/1 = MMU disabled/enable                                       supported   supported
//      MRC p15, 0, <Rd>, c1, c0, 0; Read SCTLR
//      MCR p15, 0, <Rd>, c1, c0, 0; Write SCTLR
#define _ARM_CP_SCTLR_R(sctlr) _ARM_CP_R(p15, 0, sctlr, c1, c0, 0)
#define _ARM_CP_SCTLR_W(sctlr) _ARM_CP_W(p15, 0, sctlr, c1, c0, 0)

void rt_cpu_ctl_feature_disable(uint32_t features)
{
    uint32_t sctlr;
    _ARM_CP_SCTLR_R(sctlr);
    uint32_t bakC = sctlr & CP15_SCTLR_C;
    sctlr &= ~features;
    if ((features & CP15_SCTLR_C) && (bakC & CP15_SCTLR_C)) {
        rt_cpu_dcache_clean();
    }
    _ARM_CP_SCTLR_W(sctlr);
    _ARM_DSB();

    if (features & CP15_SCTLR_Z)
        rt_cpu_branch_predictor_invalidate();

    if (features & CP15_SCTLR_I)
        rt_cpu_icache_invalidate();

    if (features & CP15_SCTLR_C) {
        if (bakC & CP15_SCTLR_C)
            rt_cpu_dcache_clean_invalidate();
        else
            rt_cpu_dcache_invalidate();
        CORTEX_TYPE cortexType = armv7_get_cortex_type();
        if (cortexType == CORTEX_TYPE_A8) {
            rt_cpu_auxctl_feature_enable(CP15_ACTLR_A8_L2EN);
        }
    }
}
void rt_cpu_ctl_feature_enable(uint32_t features)
{
    if (features & CP15_SCTLR_C) {
        CORTEX_TYPE cortexType = armv7_get_cortex_type();
        if (cortexType == CORTEX_TYPE_A8) {
            rt_cpu_auxctl_feature_disable(CP15_ACTLR_A8_L2EN);
        }   
    }
    uint32_t sctlr;
    _ARM_CP_SCTLR_R(sctlr);
    sctlr |= features;
    _ARM_CP_SCTLR_W(sctlr);
    _ARM_DSB();
}
uint32_t rt_cpu_ctl_feature_get(void)
{
    uint32_t sctlr;
    _ARM_CP_SCTLR_R(sctlr);
    return sctlr;
}

void rt_cpu_cache_disable(void)
{
    rt_cpu_ctl_feature_disable(CP15_SCTLR_Z | CP15_SCTLR_I | CP15_SCTLR_C);
}
void rt_cpu_cache_enable(void)
{
    rt_cpu_ctl_feature_enable(CP15_SCTLR_Z | CP15_SCTLR_I | CP15_SCTLR_C);
}

void rt_cpu_mmu_disable(void)
{
    rt_cpu_ctl_feature_disable(CP15_SCTLR_M);
}
void rt_cpu_mmu_enable(void)
{
    rt_cpu_ctl_feature_enable(CP15_SCTLR_M);
}

// MPIDR
// [ref]DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.6 c0, Multiprocessor ID Register
//      a read-only register that is Read-As-Zero
//      DDI0388I_cortex_a9_r4p1_trm.pdf: 4.3.3 Multiprocessor Affinity Register
//      Bit     Field           Description
//      1-0     CPU ID          Indicates the CPU number in the Cortex-A9 MPCore configuration:
//                              0x0 = Processor is CPU0
//                              0x1 = Processor is CPU1
//                              0x2 = Processor is CPU2
//                              0x3 = Processor is CPU3
//                              In the uniprocessor version this value is fixed at 0x0.
//      MRC p15,0,<Rd>,c0,c0,5; read Multiprocessor ID register
#define _ARM_CP_MPIDR_R(mpidr) _ARM_CP_R(p15, 0, mpidr, c0, c0, 5)
uint32_t rt_cpu_get_current_id(void)
{
    uint32_t mpidr;
    _ARM_CP_MPIDR_R(mpidr);
    return mpidr & _B_B(1, 0);
}