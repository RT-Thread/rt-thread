/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include "cp15.h"

// CPACR, Coprocessor Access Control Registe
// [ref]DDI0406C_d_armv7ar_arm.pdf: B6.1.23 CPACR, Coprocessor Access Control Register, PMSA
//      DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.27 c1, Coprocessor Access Control Register
//      DDI0388I_cortex_a9_r4p1_trm.pdf: 4.3.11 Coprocessor Access Control Register
//      Bit     Field               Description                                     cortex-a9   cortex-a8
//      31      ASEDIS              Disable Advanced SIMD functionality             supported
//      30      D32DIS              Disable use of D16-D31 of the VFP register file supported
//      29      reverse
//      28      TRCDIS              Disable CP14 access to trace registers
//      27-26   cp13                cp13-cp0:                                                   supported
//      25-24   cp12                    b00=Access denied                                       supported
//      23-22   cp11                    b01=Privileged mode access only             supported   supported
//      21-20   cp10                    b10=Reserved                                supported   supported
//      19-18   cp9                     b11=Privileged and User mode access                     supported
//      17-16   cp8                                                                             supported
//      15-14   cp7                                                                             supported
//      13-12   cp6                                                                             supported
//      11-10   cp5                                                                             supported
//      9-8     cp4                                                                             supported
//      7-6     cp3                                                                             supported
//      5-4     cp2                                                                             supported
//      3-2     cp1                                                                             supported
//      1-0     cp0                                                                             supported
//      MRC p15, 0, <Rt>, c1, c0, 2 ; Read CPACR into Rt
//      MCR p15, 0, <Rt>, c1, c0, 2 ; Write Rt to CPACR
#define _ARM_CP_CPACR_R(cpacr)  _ARM_CP_R(p15, 0, cpacr, c1, c0, 2)
#define _ARM_CP_CPACR_W(cpacr)  _ARM_CP_W(p15, 0, cpacr, c1, c0, 2)
// NSACR, Non-Secure Access Control Register
// [ref]DDI0406C_d_armv7ar_arm.pdf: B4.1.111 NSACR, Non-Secure Access Control Register, Security Extensions
//      DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.30 c1, Nonsecure Access Control Register
//      DDI0388I_cortex_a9_r4p1_trm.pdf: 4.3.13 Non-secure Access Control Register
//      Bit     Field               Description                                     cortex-a9   cortex-a8
//      13-0    cp13-cp0            cp13-cp0:                                       cp11-cp10   cp13-cp0
//                                  0 = secure access only, reset value
//                                  1 = secure or nonsecure access.
//      MRC p15, 0, <Rd>, c1, c1, 2; Read Nonsecure Access Control Register data
//      MCR p15, 0, <Rd>, c1, c1, 2; Write Nonsecure Access Control Register data
#define _ARM_CP_NSACR_R(nsacr)  _ARM_CP_R(p15, 0, nsacr, c1, c1, 2)
#define _ARM_CP_NSACR_W(nsacr)  _ARM_CP_W(p15, 0, nsacr, c1, c1, 2)
void rt_cpu_vfp_neon_access_enable(void)
{
    uint32_t nsacr;
    _ARM_CP_NSACR_R(nsacr);
    if ((nsacr & _B_B(11, 10)) != _B_B(11, 10)) {
        nsacr |= _B_B(11, 10);
        _ARM_CP_NSACR_W(nsacr);
    }

    uint32_t cpacr;
    _ARM_CP_CPACR_R(cpacr);
    cpacr |= _L(0x3, 22) | _L(0x3, 20);
    _ARM_CP_CPACR_W(cpacr);
    _ARM_ISB();
}

// FPSCR, Floating-point Status and Control Register
// [ref]DDI0406C_d_armv7ar_arm.pdf: B4.1.58 FPSCR, Floating-point Status and Control Register, VMSA
//      Bit     Field               Description
//      25      DN                  Default NaN mode control bit:
//                                  0 = NaN operands propagate through to the output of a floating - point operation.
//                                  1 = Any operation involving one or more NaNs returns the Default NaN.
//      24      FZ                  Flush-to-zero mode control bit:
//                                  0 = Flush - to - zero mode disabled.Behavior of the floating - point system is fully compliant with the IEEE 754 standard.
//                                  1 = Flush - to - zero mode enabled.
//      23-22   RMode               Rounding Mode control field. The encoding of this field is:
//                                  0b00 = Round to Nearest(RN) mode.
//                                  0b01 = Round towards Plus Infinity(RP) mode.
//                                  0b10 = Round towards Minus Infinity(RM) mode.
//                                  0b11 = Round towards Zero(RZ) mode.
//      15      IDE                 Input Denormal exception trap enable
//      14-13   reverse
//      12      IXE                 Inexact exception trap enable
//      11      UFE                 Underflow exception trap enable
//      10      OFE                 Overflow exception trap enable
//      9       DZE                 Division by Zero exception trap enable
//      8       IOE                 Invalid Operation exception trap enable
//      7       IDC                 Input Denormal cumulative exception bit
//      6-5     reverse
//      4       IXC                 Inexact cumulative exception bit
//      3       UFC                 Underflow cumulative exception bit
//      2       OFC                 Overflow cumulative exception bit
//      1       DZC                 Division by Zero cumulative exception bit
//      0       IOC                 Invalid Operation cumulative exception bit
uint32_t rt_cpu_fpscr_get_default(void)
{
    return _B(25)/*DN*/ | _B(24)/*FZ*/;
}

void rt_cpu_fpscr_init(void)
{
    uint32_t fpscr;
    _ARM_FPSCR_R(fpscr);
    fpscr &= ~(_B_B(23, 22) | _B_B(15, 0));
    fpscr |= rt_cpu_fpscr_get_default();
    _ARM_FPSCR_W(fpscr);
}