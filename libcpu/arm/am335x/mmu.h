/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-01-10     bernard      porting to AM1808
 */

#ifndef __MMU_H__
#define __MMU_H__

#include <rtthread.h>

#ifndef _B
#define _B(i)           (((i) >= 32) ? (1ull << (i)) : (1u << (i)))
#endif
#ifndef _L
#define _L(i, n)        ((i) << (n))
#endif

// [ref]
//   1) DDI0406C_d_armv7ar_arm.pdf: B3.5.1 Short-descriptor translation table format descriptors
//      Section
//      Bit     Field                   Default     Description
//      31-20   PA[31:20]                           Section base address
//      19      NS                                  Non-secure bit
//      18      0
//      17      nG                                  The not global bit
//      16      S                                   The Shareable bit
//      15      AP[2]                               Access Permissions bits
//      14-12   TEX[2:0]                            TRE == 0, Remap disabled; TRE == 1 Remap enabled. set TRE = 0. See description below
//      11-10   AP[1:0]                             Access Permissions bits
//      9       IMPLEMENTATION DEFINED              Not implemented(no find in DDI0344K_cortex_a8_r3p2_trm.pdf)
//      8-5     Domain                              Domain field
//      4       XN                                  The Execute-never bit
//      3       C                                   See description below
//      2       B                                   See description below
//      1       1
//      0       PXN                                 The Privileged execute-never bit
//   2) DDI0406C_d_armv7ar_arm.pdf: B3.8.2 Short-descriptor format memory region attributes, without TEX remap
//      TEX[2:0]    C   B   Description                                         Memory type             Page Shareable
//      000         0   0   Strongly-ordered                                    Strongly-ordered        Shareable
//                      1   Shareable Device                                    Device                  Shareable
//                  1   0   Outer and Inner Write-Through, no Write-Allocate    Normal                  S bit
//                      1   Outer and Inner Write-Back, no Write-Allocate       Normal                  S bit
//      001         0   0   Outer and Inner Non-cacheable                       Normal                  S bit
//                      1   Reserved                                            -                      -
//                  1   0   IMPLEMENTATION DEFINED                              IMPLEMENTATION DEFINED  IMPLEMENTATION DEFINED
//                      1   Outer and Inner Write-Back, Write-Allocate          Normal                  S bit
//      010         0   0   Non-shareable Device                                Device                  Non-shareable
//                      1   Reserved                                            -                      -
//                  1   x   Reserved                                            -                      -
//      011         x   x   Reserved                                            -                      -
//      1BB         A   A   Cacheable memory : AA = Inner attribute             Normal                  S bit
//                                             BB = Outer attribute
//
//      Table B3-11 Inner and Outer cache attribute encoding
//      When TEX[2] == 1, the translation table entry describes Cacheable memory, and the rest of the encoding defines
//      the Inner and Outer cache attributes :
//          TEX[1:0]    Define the Outer cache attribute.
//          C, B        Define the Inner cache attribute.
//      Encoding    Cache attribute
//      00          Non-cacheable
//      01          Write-Back, Write-Allocate
//      10          Write-Through, no Write-Allocate
//      11          Write-Back, no Write-Allocate
//   4) DDI0406C_d_armv7ar_arm.pdf: B3.7.1 Access permissions
//      AP[2:0] access permissions control, Short-descriptor format only
//      AP[2]   AP[1:0]     PL1 access  Unprivileged access     Description
//      0       00          NA          NA                      All accesses generate Permission faults
//              01          R/W         NA                      Access only at PL1
//              10          R/W         RO                      Writes at PL0 generate Permission faults
//              11          R/W         R/W                     Full access
//      1       00          -           -                       Reserved
//              01          RO          NA                      Read-only, only at PL1
//              10          RO          RO                      Read-only at any privilege level, deprecateda
//              11          RO          RO                      Read-only at any privilege level
//   5) DDI0406C_d_armv7ar_arm.pdf: B4.1.43 DACR, Domain Access Control Register, VMSA
//      DACR
//      Bit         Field       Default     Description
//      (2n+1):2n   Dn(n=0~15)              Domain n access permission, Permitted values are:
//                                          0b00 = No access. Any access to the domain generates a Domain fault.
//                                          0b01 = Client.Accesses are checked against the permission bits in the translation tables.
//                                          0b10 = Reserved, effect is UNPREDICTABLE.
//                                          0b11 = Manager.Accesses are not checked against the permission bits in the translation tables.

#define DESC_SEC		_B(1)   // section
#define CB				(_B(14)/*TEX[2]*/ | _L(0b01, 12)/*TEX[1:0]*/ | _L(0b01, 2)/*C,B*/)  // Inner/Outer: Write-Back, Write-Allocate
#define NCNB			(0/*TEX[2]*/ | _L(0b00, 12)/*TEX[1:0]*/ | _L(0b01, 2)/*C,B*/)       // Inner: Strongly-ordered. Outer: Shareable Device
#define AP_RW			(0/*AP[2]*/ | _L(0b11, 10)/*AP[1:0]*/)      // PL1/PL0: RW
#define AP_RO			(_B(15)/*AP[2]*/ | _L(0b10, 10)/*AP[1:0]*/) // PL1: RW, PL0: RO
#define AP_RWRO			(0/*AP[2]*/ | _L(0b11, 10)/*AP[1:0]*/)      // PL1/PL0: RW
#define AP_NA			(0/*AP[2]*/ | _L(0b00, 10)/*AP[1:0]*/)      // PL1/PL0: NA(no access)

#define DOMAIN			(_L(0, 5)/*Domain*/)                        // only use domain0

#define RW_CB		    (DESC_SEC | DOMAIN | AP_RW | CB)            // RW, cache, buffer
#define RW_NCNB		    (DESC_SEC | DOMAIN | AP_RW | NCNB)	        // RW, no cache, no buffer

#define RWRO_CB         (DESC_SEC | DOMAIN | AP_RWRO | CB)          // PL1: RW, PL0: RO. cache, buffer
#define RWRO_NCNB       (DESC_SEC | DOMAIN | AP_RWRO | NCNB)        // PL1: RW, PL0: RO. no cache, no buffer

#define RO_C            (DESC_SEC | DOMAIN | AP_RO | CB)            // RO, cache, no buffer
#define RO_NC           (DESC_SEC | DOMAIN | AP_RO | NCNB)          // RO, cache, no buffer

#define NA_FAULT        (DESC_SEC | DOMAIN | AP_NA | NCNB)          // no access


#ifdef __cplusplus
extern "C" {
#endif

    void rt_hw_mmu_init(void);

#ifdef __cplusplus
}
#endif

#endif
