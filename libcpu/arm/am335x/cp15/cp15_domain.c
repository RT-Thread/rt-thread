/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include "cp15.h"
#include "cp15_def.h"

// DACR, Domain Access Control Register
// [ref]DDI0406C_d_armv7ar_arm.pdf: B4.1.43 DACR, Domain Access Control Register, VMSA
//      DDI0388I_cortex_a9_r4p1_trm.pdf: 4.2.4 c3 registers
//      DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.34 c3, Domain Access Control Register
//      Bit         Field           Description
//      (2n+1)-2n   Dn(n=15-0)      0b00 = No access. Any access generates a domain fault
//                                  0b01 = Client. Accesses are checked against the access permission bits in the TLB entry.
//                                  0b10 = Reserved. Any access generates a domain fault
//                                  0b11 = Manager. not generate an abort
//      MRC p15, 0, <Rt>, c3, c0, 0; Read DACR into Rt
//      MCR p15, 0, <Rt>, c3, c0, 0; Write Rt to DACR
#define _ARM_CP_DACR_R(dacr)    _ARM_CP_R(p15, 0, dacr, c3, c0, 0)
#define _ARM_CP_DACR_W(dacr)    _ARM_CP_W(p15, 0, dacr, c3, c0, 0)

void rt_cpu_domain_access_client_set(void)
{
    uint32_t dacr = 0x55555555;
    _ARM_CP_DACR_W(dacr);
}
