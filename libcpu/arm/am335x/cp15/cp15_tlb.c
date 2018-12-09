/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include "cp15.h"
#include "cp15_def.h"

// TTBCR, Translation Table Base Control Register
// [ref]DDI0406C_d_armv7ar_arm.pdf: B4.1.153 TTBCR, Translation Table Base Control Register, VMSA
//      Bit     Field           Description
//      31-6    Reverse
//      5       PD1             Specifies occurrence of a translation table walk on a TLB miss when using Translation Table Base Register 1.
//      4       PD0             Specifies occurrence of a translation table walk on a TLB miss when using Translation Table Base Register 0.
//      3       Reverse
//      2-0     N               Specifies the boundary size of Translation Table Base Register 0:
//                              b000 = 16KB, reset value
//                              b001 = 8KB
//                              b010 = 4KB
//                              b011 = 2KB
//                              b100 = 1KB
//                              b101 = 512B
//                              b110 = 256B
//                              b111 = 128B
//      MRC p15, 0, <Rd>, c2, c0, 2 ; Read Translation Table Base Control Register
//      MCR p15, 0, <Rd>, c2, c0, 2 ; Write Translation Table Base Control Register
#define _ARM_CP_TTBCR_R(ttbcr)  _ARM_CP_R(p15, 0, ttbcr, c2, c0, 2)
#define _ARM_CP_TTBCR_W(ttbcr)  _ARM_CP_W(p15, 0, ttbcr, c2, c0, 2)
// TTBR0, Translation Table Base Register 0
// [ref]DDI0406C_d_armv7ar_arm.pdf: B4.1.154 TTBR0, Translation Table Base Register 0, VMSA
//      Bit         Field                       Description
//      31-(14-N)   Translation table base 0    Holds the translation table base address, the physical address of the first level translation table.
//      (13-N)-5    Reverse
//      4-3         RGN                         Indicates the outer cacheable attributes for translation table walking:
//                                              b00 = outer noncacheable
//                                              b01 = write-back, write allocate
//                                              b10 = write-through, no allocate on write
//                                              b11 = write-back, no allocate on write.
//      2           reverse
//      1           S                           0/1 = Non-shareable/Shareable
//      0           C                           0/1 = Inner Non-cacheable/Inner Cacheable
//      MRC p15, 0, <Rd>, c2, c0, 0 ; Read Translation Table Base Register
//      MCR p15, 0, <Rd>, c2, c0, 0 ; Write Translation Table Base Register
#define _ARM_CP_TTBR0_R(ttbr0)  _ARM_CP_R(p15, 0, ttbr0, c2, c0, 0)
#define _ARM_CP_TTBR0_W(ttbr0)  _ARM_CP_W(p15, 0, ttbr0, c2, c0, 0)

void rt_cpu_tlb_set(uint32_t ttb)
{
    uint32_t ttbcr = 0;
    _ARM_CP_TTBCR_W(ttbcr);
    _ARM_DSB();
    _ARM_CP_TTBR0_W(ttb);
    _ARM_DMB();
}

// c8, TLB operations
// [ref]DDI0406C_d_armv7ar_arm.pdf: B3.17.1 CP15 register summary by coprocessor register number
//                                  VMSA CP15 c8 register summary, TLB maintenance operations
//      DDI0388I_cortex_a9_r4p1_trm.pdf: 4.2.9 c8 registers
//      DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.41 c8, TLB operations
//      CRn     opc1    CRm     opc2    Operation                                                               cortex-a9   cortex-a8
//      c8      0       c3      0       TLBIALLIS, Invalidate entire TLB IS                                     surpported
//                              1       TLBIMVAIS, Invalidate unified TLB entry by MVA and ASID IS              surpported
//                              2       TLBIASIDIS, Invalidate unified TLB by ASID match IS                     surpported
//                              3       TLBIMVAAIS, Invalidate unified TLB entry by MVA all ASID IS             surpported
//                      c5      0       ITLBIALL, invalidate instruction TLB                                    surpported  surpported
//                              1       ITLBIMVA, invalidate instruction TLB entry by MVA and ASID              surpported  surpported
//                              2       ITLBIASID, invalidate instruction TLB by ASID match                     surpported  surpported
//                      c6      0       DTLBIALL, invalidate data TLB                                           surpported  surpported
//                              1       DTLBIMVA, invalidate data TLB entry by MVA and ASID                     surpported  surpported
//                              2       DTLBIASID, invalidate data TLB by ASID match                            surpported  surpported
//                      c7      0       TLBIALL, invalidate unified TLB                                         surpported  surpported
//                              1       TLBIMVA, invalidate unified TLB entry by MVA and ASID                   surpported  surpported
//                              2       TLBIASID, invalidate unified TLB by ASID match                          surpported  surpported
//                              3       TLBIMVAA, invalidate unified TLB entries by MVA all ASID                surpported
//              4       c3      0       TLBIALLHIS, Invalidate entire Hyp unified TLB IS
//                              1       TLBIMVAHIS, Invalidate Hyp unified TLB entry by MVA IS
//                              4       TLBIALLNSNHIS, Invalidate entire Non-secure non-Hyp unified TLB IS
//                      c7      0       TLBIALLH, Invalidate entire Hyp unified TLB
//                              1       TLBIMVAH, Invalidate Hyp unified TLB entry by MVA
//                              4       TLBIALLNSNH, Invalidate entire Non-secure non-Hyp unified TLB
#define _ARM_CP_TLBIALL_W(sbz)          _ARM_CP_W(p15, 0, sbz, c8, c7, 0)   // invalidate unified TLB
void rt_cpu_tlb_invalidate(void)
{
    uint32_t sbz = 0;
    _ARM_CP_TLBIALL_W(sbz);
    _ARM_DSB();
}
