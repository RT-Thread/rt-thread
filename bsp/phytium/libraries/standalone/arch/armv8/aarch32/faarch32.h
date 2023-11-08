/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: faarch32.h
 * Date: 2022-02-10 14:53:41
 * LastEditTime: 2022-02-17 17:28:37
 * Description:  This file is for system register related macro definition functions
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   Huanghe     2021/7/3     first release
 * 1.1   Wangxiaodong  2021/9/24    modify sys_icc_bpr_set and sys_icc_bpr_get
 * 1.2   Wangxiaodong  2023/6/12    restruct AArch32 System Register access mode
 */

#ifndef FAARCH32_H
#define FAARCH32_H

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdio.h>
#include "ftypes.h"


/* System register defines The format is: coproc, opc1, CRn, CRm, opc2 */
#define SCR		    15, 0, 1, 1, 0  /* Secure Configuration Register*/
#define SCTLR		15, 0, 1, 0, 0  /* System Control Register */
#define ACTLR		15, 0, 1, 0, 1
#define SDCR		15, 0, 1, 3, 1
#define MPIDR		15, 0, 0, 0, 5
#define MIDR		15, 0, 0, 0, 0
#define HVBAR		15, 4, 12, 0, 0
#define VBAR		15, 0, 12, 0, 0
#define MVBAR		15, 0, 12, 0, 1
#define NSACR		15, 0, 1, 1, 2
#define CPACR		15, 0, 1, 0, 2
#define DCCIMVAC	15, 0, 7, 14, 1
#define DCCMVAC		15, 0, 7, 10, 1 /*Data Cache line Clean by VA to PoC*/
#define DCIMVAC		15, 0, 7, 6, 1  /*Data Cache line Invalidate by VA to PoC*/
#define DCISW		15, 0, 7, 6, 2  /*Data Cache line Invalidate by Set/Way*/
#define DCCISW		15, 0, 7, 14, 2 /*Data Cache line Clean and Invalidate by Set/Way*/
#define DCCSW		15, 0, 7, 10, 2
#define CTR		    15, 0, 0, 0, 1  /*Cache Type Register*/
#define DACR		15, 0, 3, 0, 0  /*Domain Access Control Register*/
#define ID_MMFR4	15, 0, 0, 2, 6
#define ID_DFR0		15, 0, 0, 1, 2
#define ID_DFR1		15, 0, 0, 3, 5
#define ID_PFR0		15, 0, 0, 1, 0
#define ID_PFR1		15, 0, 0, 1, 1
#define MAIR0		15, 0, 10, 2, 0
#define MAIR1		15, 0, 10, 2, 1
#define TTBCR		15, 0, 2, 0, 2
#define TTBR0		15, 0, 2, 0, 0  /*Translation Table Base Register 0*/
#define TTBR1		15, 0, 2, 0, 1
#define TLBIALL		15, 0, 8, 7, 0  /*TLB Invalidate All*/
#define TLBIALLH	15, 4, 8, 7, 0
#define TLBIALLIS	15, 0, 8, 3, 0
#define TLBIMVA		15, 0, 8, 7, 1
#define TLBIMVAA	15, 0, 8, 7, 3
#define TLBIMVAAIS	15, 0, 8, 3, 3
#define TLBIMVAHIS	15, 4, 8, 3, 1
#define BPIALLIS	15, 0, 7, 1, 6
#define BPIALL		15, 0, 7, 5, 6  /*Branch Predictor Invalidate All*/
#define ICIALLU		15, 0, 7, 5, 0  /*Instruction Cache Invalidate All to PoU*/
#define ICIMVAU		15, 0, 7, 5, 1  /*Instruction Cache line Invalidate by VA to PoU*/
#define HSCTLR		15, 4, 1, 0, 0
#define HCR		    15, 4, 1, 1, 0
#define HCPTR		15, 4, 1, 1, 2
#define HSTR		15, 4, 1, 1, 3
#define CNTHCTL		15, 4, 14, 1, 0
#define CNTKCTL		15, 0, 14, 1, 0
#define VPIDR		15, 4, 0, 0, 0
#define VMPIDR		15, 4, 0, 0, 5
#define ISR		    15, 0, 12, 1, 0
#define CLIDR		15, 1, 0, 0, 1  /*Cache Level ID Register*/
#define CSSELR		15, 2, 0, 0, 0  /*Cache Size Selection Register*/
#define CCSIDR		15, 1, 0, 0, 0  /* Current Cache Size ID Register*/
#define CCSIDR2		15, 1, 0, 0, 2
#define HTCR		15, 4, 2, 0, 2
#define HMAIR0		15, 4, 10, 2, 0
#define ATS1CPR		15, 0, 7, 8, 0
#define ATS1HR		15, 4, 7, 8, 0

/* Fault registers. The format is: coproc, opt1, CRn, CRm, opt2 */
#define DFSR		15, 0, 5, 0, 0  /* Data Fault Status Register */
#define IFSR		15, 0, 5, 0, 1  /* Instruction Fault Status Register*/
#define DFAR		15, 0, 6, 0, 0  /* Data Fault Address Register*/
#define IFAR		15, 0, 6, 0, 2  /* Instruction Fault Address Register*/

/* Debug registers. The format is: coproc, opt1, CRn, CRm, opt2 */
#define DBGDSCR		14, 0, 0, 1, 0  /* Debug Status and Control Register, Internal View */ 
#define DBGOSDLR	14, 0, 1, 3, 4

static _ALWAYS_INLINE u32 AARCH32_READ_SYSREG_32(const int coproc, const int opc1, const int CRn, const int CRm, const int opc2)
{
    u32 val = 0;
    __asm__ __volatile__("MRC p%a[coproc], %a[opc1], %0, c%a[CRn], c%a[CRm], %a[opc2]"
                       : "=r"(val)
                       : [coproc] "n" (coproc), [opc1] "n" (opc1),
                        [CRn] "n" (CRn), [CRm] "n" (CRm), [opc2] "n" (opc2)
                       :"memory");
    return val;
}

static _ALWAYS_INLINE void AARCH32_WRITE_SYSREG_32(const int coproc, const int opc1, const int CRn, const int CRm, const int opc2, const u32 val)
{
    __asm__ __volatile__("MCR p%a[coproc], %a[opc1], %0, c%a[CRn], c%a[CRm], %a[opc2]"
                       : 
                       : "r"(val), 
                        [coproc] "n" (coproc), [opc1] "n" (opc1), 
                        [CRn] "n" (CRn), [CRm] "n" (CRm), [opc2] "n" (opc2)
                       :"memory");
}

static _ALWAYS_INLINE u64 AARCH32_READ_SYSREG_64(const int coproc, const int opc1, const int CRm)
{
    u64 val = 0;
    __asm__ __volatile__("MRRC p%a[coproc], %a[opc1], %Q0, %R0, c%a[CRm]"
                         : "=r"(val)
                         : [coproc] "n" (coproc), [opc1] "n" (opc1), [CRm] "n" (CRm)
                         : "memory");
    return val;
}

static _ALWAYS_INLINE void AARCH32_WRITE_SYSREG_64(const int coproc, const int opc1, const int CRm, const u64 val)                                                               
{
    __asm__ __volatile__("MCRR p%a[coproc], %a[opc1], %Q0, %R0, c%a[CRm]"
                        :
                        : "r"(val), 
                        [coproc] "n" (coproc), [opc1] "n" (opc1), [CRm] "n" (CRm)
                        :"memory");
}


#define MFCPSR() (            \
{                         \
    u32 rval = 0U;        \
    __asm__ __volatile__( \
                          "mrs	%0, cpsr\n"  \
                          : "=r"(rval));    \
    rval;                 \
})

#define MTCPSR(v) __asm__ __volatile__( \
                                        "msr	cpsr,%0\n"                     \
                                        :                                   \
                                        : "r"(v)                            \
                                        : "cc")

/* Instruction Synchronization Barrier */
#define ISB() __asm__ __volatile__("isb" \
                                   :     \
                                   :     \
                                   : "memory")

/* Data Synchronization Barrier */
#define DSB() __asm__ __volatile__("dsb" \
                                   :     \
                                   :     \
                                   : "memory")

/* Data Memory Barrier */
#define DMB() __asm__ __volatile__("dmb" \
                                   :     \
                                   :     \
                                   : "memory")

#define WMB         DSB


#define INTERRUPT_DISABLE()         \
    __asm volatile("CPSID i" ::     \
                   : "memory"); \
    DSB();          \
    ISB();

#define INTERRUPT_ENABLE()          \
    __asm volatile("CPSIE i" ::     \
                   : "memory"); \
    DSB();          \
    ISB();


#ifdef __cplusplus
}
#endif

#endif // !