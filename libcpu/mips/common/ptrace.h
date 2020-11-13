/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 */

#ifndef _MIPS_PTRACE_H
#define _MIPS_PTRACE_H

#include "asm.h"
#include "mips_regs.h"

#define HI_LO_SIZE  4

#define FP_REG_SIZE 8
#define NUM_FPU_REGS 16

#ifndef __ASSEMBLY__
#include <rtthread.h>

struct mips_fpu_struct {
    rt_uint64_t	fpr[NUM_FPU_REGS];
    rt_uint32_t	fcr31;
    rt_uint32_t	pad;
};

struct pt_regs {
#ifndef ARCH_MIPS64
    /* Only O32 Need This! */
    /* Pad bytes for argument save space on the stack. */
    rt_uint32_t pad0[8];

    /* Saved main processor registers. */
    rt_uint32_t regs[32];

    /* Saved special registers. */
    rt_uint32_t cp0_status;
    rt_uint32_t hi;
    rt_uint32_t lo;
    rt_uint32_t cp0_badvaddr;
    rt_uint32_t cp0_cause;
    rt_uint32_t cp0_epc;
#else
    /* Saved main processor registers. */
    unsigned long regs[32];

    /* Saved special registers. */
    rt_uint32_t cp0_status;
    rt_uint32_t hi;
    rt_uint32_t lo;
    unsigned long cp0_badvaddr;
    rt_uint32_t cp0_cause;
    unsigned long cp0_epc;
#endif

#ifdef RT_USING_FPU
    /* FPU Registers */
    /* Unlike Linux Kernel, we save these registers unconditionally,
     * so it should be a part of pt_regs */
    struct mips_fpu_struct fpu;
#endif
} __aligned(8);
#endif

/* Note: For call stack o32 ABI has 0x8 shadowsoace Here  */
#ifdef ARCH_MIPS64
#define PT_R0		(0x0 * LONGSIZE)	/* 0 */
#else
#define PT_R0		(0x8 * LONGSIZE)	/* 0 */
#endif
#define PT_R1		((PT_R0) + LONGSIZE)	/* 1 */
#define PT_R2		((PT_R1) + LONGSIZE)	/* 2 */
#define PT_R3		((PT_R2) + LONGSIZE)	/* 3 */
#define PT_R4		((PT_R3) + LONGSIZE)	/* 4 */
#define PT_R5		((PT_R4) + LONGSIZE)	/* 5 */
#define PT_R6		((PT_R5) + LONGSIZE)	/* 6 */
#define PT_R7		((PT_R6) + LONGSIZE)	/* 7 */
#define PT_R8		((PT_R7) + LONGSIZE)	/* 8 */
#define PT_R9		((PT_R8) + LONGSIZE)	/* 9 */
#define PT_R10		((PT_R9) + LONGSIZE)	/* 10 */
#define PT_R11		((PT_R10) + LONGSIZE)	/* 11 */
#define PT_R12		((PT_R11) + LONGSIZE)	/* 12 */
#define PT_R13		((PT_R12) + LONGSIZE)	/* 13 */
#define PT_R14		((PT_R13) + LONGSIZE)	/* 14 */
#define PT_R15		((PT_R14) + LONGSIZE)	/* 15 */
#define PT_R16		((PT_R15) + LONGSIZE)	/* 16 */
#define PT_R17		((PT_R16) + LONGSIZE)	/* 17 */
#define PT_R18		((PT_R17) + LONGSIZE)	/* 18 */
#define PT_R19		((PT_R18) + LONGSIZE)	/* 19 */
#define PT_R20		((PT_R19) + LONGSIZE)	/* 20 */
#define PT_R21		((PT_R20) + LONGSIZE)	/* 21 */
#define PT_R22		((PT_R21) + LONGSIZE)	/* 22 */
#define PT_R23		((PT_R22) + LONGSIZE)	/* 23 */
#define PT_R24		((PT_R23) + LONGSIZE)	/* 24 */
#define PT_R25		((PT_R24) + LONGSIZE)	/* 25 */
#define PT_R26		((PT_R25) + LONGSIZE)	/* 26 */
#define PT_R27		((PT_R26) + LONGSIZE)	/* 27 */
#define PT_R28		((PT_R27) + LONGSIZE)	/* 28 */
#define PT_R29		((PT_R28) + LONGSIZE)	/* 29 */
#define PT_R30		((PT_R29) + LONGSIZE)	/* 30 */
#define PT_R31		((PT_R30) + LONGSIZE)	/* 31 */

/*
 * Saved special registers
 */
#define PT_STATUS	((PT_R31) + LONGSIZE)	/* 32 */
#define PT_HI		((PT_STATUS) + HI_LO_SIZE)	/* 33 */
#define PT_LO		((PT_HI) + HI_LO_SIZE)	/* 34 */
#define PT_BADVADDR	((PT_LO) + LONGSIZE)	/* 35 */
#define PT_CAUSE	((PT_BADVADDR) + LONGSIZE)	/* 36 */
#define PT_EPC		((PT_CAUSE) + LONGSIZE)	/* 37 */

#define PT_REG_END		((PT_EPC) + LONGSIZE) /* Align already ensured manually */

#ifdef RT_USING_FPU
#define PT_FPU_R0               (PT_REG_END)
#define PT_FPU_R2               ((PT_FPU_R0) + FP_REG_SIZE)
#define PT_FPU_R4               ((PT_FPU_R2) + FP_REG_SIZE)
#define PT_FPU_R6               ((PT_FPU_R4) + FP_REG_SIZE)
#define PT_FPU_R8               ((PT_FPU_R6) + FP_REG_SIZE)
#define PT_FPU_R10              ((PT_FPU_R8) + FP_REG_SIZE)
#define PT_FPU_R12              ((PT_FPU_R10) + FP_REG_SIZE)
#define PT_FPU_R14              ((PT_FPU_R12) + FP_REG_SIZE)
#define PT_FPU_R16              ((PT_FPU_R14) + FP_REG_SIZE)
#define PT_FPU_R18              ((PT_FPU_R16) + FP_REG_SIZE)
#define PT_FPU_R20              ((PT_FPU_R18) + FP_REG_SIZE)
#define PT_FPU_R22              ((PT_FPU_R20) + FP_REG_SIZE)
#define PT_FPU_R24              ((PT_FPU_R22) + FP_REG_SIZE)
#define PT_FPU_R26              ((PT_FPU_R24) + FP_REG_SIZE)
#define PT_FPU_R28              ((PT_FPU_R26) + FP_REG_SIZE)
#define PT_FPU_R30              ((PT_FPU_R28) + FP_REG_SIZE)
#define PT_FPU_FCSR31           ((PT_FPU_R30) + FP_REG_SIZE)
#define PT_FPU_PAD0             ((PT_FPU_FCSR31) + 4)

#define PT_FPU_END     	        ((PT_FPU_PAD0) + 4)
#define PT_SIZE			PT_FPU_END
#else
#define PT_SIZE			PT_REG_END
#endif

#endif