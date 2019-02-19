/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include "cp15.h"

 // MIDR, Main ID Register, VMSA
 // [ref]DDI0406C_d_armv7ar_arm.pdf: B4.1.105 MIDR, Main ID Register, VMSA
 //      DDI0388I_cortex_a9_r4p1_trm.pdf: 4.3.1 Main ID Register
 //      DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.2 c0, Main ID Register
 //      Bit     Field               Description                                     cortex-a9               cortex-a8
 //      31-24   Implementor         Indicates the implementor.                      0x41,ARM                0x41,ARM
 //      23-20   Variant             An IMPLEMENTATION DEFINED variant number        major revision number   the variant number, or major revision
 //      19-16   Architecture        0x1 = ARMv4                                     0xF                     0xF
 //                                  0x2 = ARMv4T
 //                                  0x3 = ARMv5(obsolete)
 //                                  0x4 = ARMv5T
 //                                  0x5 = ARMv5TE
 //                                  0x6 = ARMv5TEJ
 //                                  0x7 = ARMv6
 //                                  0xF = Defined by CPUID scheme
 //      15-4    Primary part number IMPLEMENTATION DEFINED                          0xC09 = Cortex-A9       0xC08 = Cortex-A8
 //      3-0     Revision            IMPLEMENTATION DEFINED                          Minor revision number   revision number, or minor revision
 //      MRC p15, 0, <Rt>, c0, c0, 0 ; Read MIDR into Rt
#define _ARM_CP_MIDR_R(midr)    _ARM_CP_R(p15, 0, midr, c0, c0, 0)
CORTEX_TYPE armv7_get_cortex_type(void)
{
    uint32_t midr;
    _ARM_CP_MIDR_R(midr);
    uint32_t priPartNum = _E_B_B(midr, 15, 4);
    switch (priPartNum) {
    case 0xC05:
        return CORTEX_TYPE_A5;
    case 0xC07:
        return CORTEX_TYPE_A7;
    case 0xC08:
        return CORTEX_TYPE_A8;
    case 0xC09:
        return CORTEX_TYPE_A9;
    case 0xC0F:
        return CORTEX_TYPE_A15;
    case 0xC11:
        return CORTEX_TYPE_A17;
    default:
        return CORTEX_TYPE_UNKNOWN;
    }
}
