/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#ifndef __ASMOPR_H__
#define __ASMOPR_H__

#define _ARM_NOP()          asm volatile ("NOP\n\t")
#define _ARM_DSB()          asm volatile ("DSB\n\t")
#define _ARM_ISB()          asm volatile ("ISB\n\t")
#define _ARM_DMB()          asm volatile ("DMB\n\t")
#define _ARM_CLZ(y, x)      asm volatile ("CLZ %[result], %[value]\n\t" : [result] "=r" (y) : [value] "r" (x))

#define _ARM_CP_R(coproc, opcode1, Rt, CRn, CRm, opcode2) \
    asm volatile ("MRC " #coproc ", " #opcode1 ", %[oup], " #CRn ", " #CRm ", " #opcode2 "\n\t" : [oup] "=r" (Rt))
#define _ARM_CP_W(coproc, opcode1, Rt, CRn, CRm, opcode2) \
    asm volatile ("MCR " #coproc ", " #opcode1 ", %[inp], " #CRn ", " #CRm ", " #opcode2 "\n\t" :: [inp] "r" (Rt))

#define _ARM_FPEXC_R(fpexc) asm volatile("vmrs %0, fpexc" : "=r"(fpexc));
#define _ARM_FPEXC_W(fpexc) asm volatile("vmsr fpexc, %0" :: "r"(fpexc));

#define _ARM_FPSCR_R(fpscr) asm volatile("vmrs %0, fpscr" : "=r"(fpscr));
#define _ARM_FPSCR_W(fpscr) asm volatile("vmsr fpscr, %0" :: "r"(fpscr));


#endif // __ASMOPR_H__
