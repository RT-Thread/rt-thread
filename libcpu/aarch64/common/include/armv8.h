/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-15     Bernard      first version
 */

#ifndef __ARMV8_H__
#define __ARMV8_H__

#include <rtconfig.h>

#ifdef ARCH_USING_HW_THREAD_SELF
#define ARM64_THREAD_REG tpidr_el1
#endif /* ARCH_USING_HW_THREAD_SELF */

#ifdef __ASSEMBLY__

/*********************
 *   CONTEXT_OFFSET  *
 *********************/

#define CONTEXT_OFFSET_ELR_EL1    0x0
#define CONTEXT_OFFSET_SPSR_EL1   0x8
#define CONTEXT_OFFSET_SP_EL0     0x10
#define CONTEXT_OFFSET_X30        0x18
#define CONTEXT_OFFSET_FPCR       0x20
#define CONTEXT_OFFSET_FPSR       0x28
#define CONTEXT_OFFSET_X28        0x30
#define CONTEXT_OFFSET_X29        0x38
#define CONTEXT_OFFSET_X26        0x40
#define CONTEXT_OFFSET_X27        0x48
#define CONTEXT_OFFSET_X24        0x50
#define CONTEXT_OFFSET_X25        0x58
#define CONTEXT_OFFSET_X22        0x60
#define CONTEXT_OFFSET_X23        0x68
#define CONTEXT_OFFSET_X20        0x70
#define CONTEXT_OFFSET_X21        0x78
#define CONTEXT_OFFSET_X18        0x80
#define CONTEXT_OFFSET_X19        0x88
#define CONTEXT_OFFSET_X16        0x90
#define CONTEXT_OFFSET_X17        0x98
#define CONTEXT_OFFSET_X14        0xa0
#define CONTEXT_OFFSET_X15        0xa8
#define CONTEXT_OFFSET_X12        0xb0
#define CONTEXT_OFFSET_X13        0xb8
#define CONTEXT_OFFSET_X10        0xc0
#define CONTEXT_OFFSET_X11        0xc8
#define CONTEXT_OFFSET_X8         0xd0
#define CONTEXT_OFFSET_X9         0xd8
#define CONTEXT_OFFSET_X6         0xe0
#define CONTEXT_OFFSET_X7         0xe8
#define CONTEXT_OFFSET_X4         0xf0
#define CONTEXT_OFFSET_X5         0xf8
#define CONTEXT_OFFSET_X2         0x100
#define CONTEXT_OFFSET_X3         0x108
#define CONTEXT_OFFSET_X0         0x110
#define CONTEXT_OFFSET_X1         0x118

#define CONTEXT_OFFSET_Q31        0x120
#define CONTEXT_OFFSET_Q30        0x130
#define CONTEXT_OFFSET_Q29        0x140
#define CONTEXT_OFFSET_Q28        0x150
#define CONTEXT_OFFSET_Q27        0x160
#define CONTEXT_OFFSET_Q26        0x170
#define CONTEXT_OFFSET_Q25        0x180
#define CONTEXT_OFFSET_Q24        0x190
#define CONTEXT_OFFSET_Q23        0x1a0
#define CONTEXT_OFFSET_Q22        0x1b0
#define CONTEXT_OFFSET_Q21        0x1c0
#define CONTEXT_OFFSET_Q20        0x1d0
#define CONTEXT_OFFSET_Q19        0x1e0
#define CONTEXT_OFFSET_Q18        0x1f0
#define CONTEXT_OFFSET_Q17        0x200
#define CONTEXT_OFFSET_Q16        0x210
#define CONTEXT_OFFSET_Q15        0x220
#define CONTEXT_OFFSET_Q14        0x230
#define CONTEXT_OFFSET_Q13        0x240
#define CONTEXT_OFFSET_Q12        0x250
#define CONTEXT_OFFSET_Q11        0x260
#define CONTEXT_OFFSET_Q10        0x270
#define CONTEXT_OFFSET_Q9         0x280
#define CONTEXT_OFFSET_Q8         0x290
#define CONTEXT_OFFSET_Q7         0x2a0
#define CONTEXT_OFFSET_Q6         0x2b0
#define CONTEXT_OFFSET_Q5         0x2c0
#define CONTEXT_OFFSET_Q4         0x2d0
#define CONTEXT_OFFSET_Q3         0x2e0
#define CONTEXT_OFFSET_Q2         0x2f0
#define CONTEXT_OFFSET_Q1         0x300
#define CONTEXT_OFFSET_Q0         0x310

#define CONTEXT_FPU_SIZE          (32 * 16)
#define CONTEXT_SIZE              (0x120 + CONTEXT_FPU_SIZE)

#else /* !__ASSEMBLY__ */

#include <rttypes.h>

typedef struct { rt_uint64_t value[2]; } rt_uint128_t;

/* the exception stack without VFP registers */
struct rt_hw_exp_stack
{
    rt_uint64_t pc;
    rt_uint64_t cpsr;
    rt_uint64_t sp_el0;
    rt_uint64_t x30;
    rt_uint64_t fpcr;
    rt_uint64_t fpsr;
    rt_uint64_t x28;
    rt_uint64_t x29;
    rt_uint64_t x26;
    rt_uint64_t x27;
    rt_uint64_t x24;
    rt_uint64_t x25;
    rt_uint64_t x22;
    rt_uint64_t x23;
    rt_uint64_t x20;
    rt_uint64_t x21;
    rt_uint64_t x18;
    rt_uint64_t x19;
    rt_uint64_t x16;
    rt_uint64_t x17;
    rt_uint64_t x14;
    rt_uint64_t x15;
    rt_uint64_t x12;
    rt_uint64_t x13;
    rt_uint64_t x10;
    rt_uint64_t x11;
    rt_uint64_t x8;
    rt_uint64_t x9;
    rt_uint64_t x6;
    rt_uint64_t x7;
    rt_uint64_t x4;
    rt_uint64_t x5;
    rt_uint64_t x2;
    rt_uint64_t x3;
    rt_uint64_t x0;
    rt_uint64_t x1;

    rt_uint128_t fpu[32];
};

void rt_hw_show_register(struct rt_hw_exp_stack *regs);

#define SP_ELx     ((unsigned long)0x01)
#define SP_EL0     ((unsigned long)0x00)
#define PSTATE_EL1 ((unsigned long)0x04)
#define PSTATE_EL2 ((unsigned long)0x08)
#define PSTATE_EL3 ((unsigned long)0x0c)

rt_ubase_t rt_hw_get_current_el(void);
void rt_hw_set_elx_env(void);
void rt_hw_set_current_vbar(rt_ubase_t addr);

/* ESR:generic */
#define ARM64_ABORT_WNR(esr)        ((esr) & 0x40)
#define ARM64_ESR_EXTRACT_EC(esr)   ((((esr) >> 26) & 0x3fU))
#define ARM64_ESR_EXTRACT_FSC(esr)  ((esr) & 0x3f)

/* ESR:EC */
#define ARM64_EC_INST_ABORT_FROM_LO_EXCEPTION   (0b100000)
#define ARM64_EC_INST_ABORT_WITHOUT_A_CHANGE    (0b100001)
#define ARM64_EC_DATA_ABORT_FROM_LO_EXCEPTION   (0b100100)
#define ARM64_EC_DATA_ABORT_WITHOUT_A_CHANGE    (0b100101)

/* ESR:FSC */
#define ARM64_FSC_TRANSLATION_FAULT_LEVEL_0     (0b000100)
#define ARM64_FSC_TRANSLATION_FAULT_LEVEL_1     (0b000101)
#define ARM64_FSC_TRANSLATION_FAULT_LEVEL_2     (0b000110)
#define ARM64_FSC_TRANSLATION_FAULT_LEVEL_3     (0b000111)
#define ARM64_FSC_PERMISSION_FAULT_LEVEL_0      (0b001100)
#define ARM64_FSC_PERMISSION_FAULT_LEVEL_1      (0b001101)
#define ARM64_FSC_PERMISSION_FAULT_LEVEL_2      (0b001110)
#define ARM64_FSC_PERMISSION_FAULT_LEVEL_3      (0b001111)
#define ARM64_FSC_ACCESS_FLAG_FAULT_LEVEL_0     (0b001000)
#define ARM64_FSC_ACCESS_FLAG_FAULT_LEVEL_1     (0b001001)
#define ARM64_FSC_ACCESS_FLAG_FAULT_LEVEL_2     (0b001010)
#define ARM64_FSC_ACCESS_FLAG_FAULT_LEVEL_3     (0b001011)

#endif /* __ASSEMBLY__ */

#endif
