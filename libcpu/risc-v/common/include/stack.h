/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 * 2021-11-18     JasonHu      add fpu member
 * 2022-10-22     Shell        Support kernel mode RVV
 */

#ifndef __STACK_H__
#define __STACK_H__

#include <rtconfig.h>

#include <context_ext.h>

#ifndef __ASSEMBLY__
#include <rtdef.h>
#endif

#ifdef ARCH_RISCV_FPU
    #define K_XSTATUS_EXT               SR_FS
#else
    #define K_XSTATUS_EXT               0
#endif

#ifdef ARCH_RISCV_M_MODE
    #define K_XSTATUS_DEFAULT_BASE      (SR_PP | SR_PIE | K_XSTATUS_EXT)
#else
    #define K_XSTATUS_DEFAULT_BASE      (SR_PP | SR_PIE | SR_SUM | K_XSTATUS_EXT)
#endif

#ifdef ARCH_RISCV_VECTOR
    #define K_XSTATUS_DEFAULT           (K_XSTATUS_DEFAULT_BASE | SR_VS)
#else
    #define K_XSTATUS_DEFAULT           K_XSTATUS_DEFAULT_BASE
#endif

#ifdef ARCH_RISCV_32E
    #define CTX_GENERAL_REG_NR          18
    #define FRAME_OFF_SP                (17 * SZREG)
#else
    #define CTX_GENERAL_REG_NR          34
    #define FRAME_OFF_SP                (33 * SZREG)
#endif
#define CTX_ALL_REG_NR                  (CTX_GENERAL_REG_NR + CTX_FPU_REG_NR + CTX_VECTOR_REG_NR)

#define FRAME_OFF_XSTATUS               (2 * SZREG)
#define FRAME_OFF_XCAUSE                (3 * SZREG)
#define FRAME_OFF_GP                    (4 * SZREG)
#define FRAME_OFF_TP                    (5 * SZREG)
#define FRAME_OFF_A7                    (18 * SZREG)

/* Switch frame */
#define RT_HW_SWITCH_CONTEXT_XSTATUS    0
#define RT_HW_SWITCH_CONTEXT_S1         1
#define RT_HW_SWITCH_CONTEXT_S0         2
#define RT_HW_SWITCH_CONTEXT_RA         3
#define RT_HW_SWITCH_CONTEXT_TP         4
#ifdef ARCH_RISCV_32E
#define RT_HW_SWITCH_CONTEXT_SIZE       8   /* Padding for alignment */
#else
#define RT_HW_SWITCH_CONTEXT_S2         5
#define RT_HW_SWITCH_CONTEXT_S3         6
#define RT_HW_SWITCH_CONTEXT_S4         7
#define RT_HW_SWITCH_CONTEXT_S5         8
#define RT_HW_SWITCH_CONTEXT_S6         9
#define RT_HW_SWITCH_CONTEXT_S7         10
#define RT_HW_SWITCH_CONTEXT_S8         11
#define RT_HW_SWITCH_CONTEXT_S9         12
#define RT_HW_SWITCH_CONTEXT_S10        13
#define RT_HW_SWITCH_CONTEXT_S11        14
#define RT_HW_SWITCH_CONTEXT_SIZE       16  /* Padding for alignment */
#endif

#ifndef __ASSEMBLY__
typedef struct rt_hw_switch_frame
{
    rt_ubase_t regs[RT_HW_SWITCH_CONTEXT_SIZE];
} *rt_hw_switch_frame_t;

RT_STATIC_ASSERT(riscv_switch_frame_size,
        sizeof(struct rt_hw_switch_frame) == RT_HW_SWITCH_CONTEXT_SIZE * sizeof(rt_ubase_t));

#ifdef ARCH_RISCV_USING_IRQ_STACK
void riscv_irq_stack_init(void);
void *riscv_irq_stack_top(void);
#endif

struct rt_hw_stack_frame
{
    rt_ubase_t epc;                 /* epc - epc   - program counter */
    rt_ubase_t ra;                  /* x1  - ra    - return address for jumps */
    rt_ubase_t xstatus;             /*             - supervisor/machine status register */
    rt_ubase_t xcause;              /*             - supervisor/machine cause register */
    rt_ubase_t gp;                  /* x3  - gp    - global pointer */
    rt_ubase_t tp;                  /* x4  - tp    - thread pointer */
    rt_ubase_t t0;                  /* x5  - t0    - temporary register 0 */
    rt_ubase_t t1;                  /* x6  - t1    - temporary register 1 */
    rt_ubase_t t2;                  /* x7  - t2    - temporary register 2 */
    rt_ubase_t s0_fp;               /* x8  - s0/fp - saved register 0 or frame pointer */
    rt_ubase_t s1;                  /* x9  - s1    - saved register 1 */
    rt_ubase_t a0;                  /* x10 - a0    - return value or function argument 0 */
    rt_ubase_t a1;                  /* x11 - a1    - return value or function argument 1 */
    rt_ubase_t a2;                  /* x12 - a2    - function argument 2 */
    rt_ubase_t a3;                  /* x13 - a3    - function argument 3 */
    rt_ubase_t a4;                  /* x14 - a4    - function argument 4 */
    rt_ubase_t a5;                  /* x15 - a5    - function argument 5 */
#ifndef ARCH_RISCV_32E
    rt_ubase_t a6;                  /* x16 - a6    - function argument 6 */
    rt_ubase_t a7;                  /* x17 - s7    - function argument 7 */
    rt_ubase_t s2;                  /* x18 - s2    - saved register 2 */
    rt_ubase_t s3;                  /* x19 - s3    - saved register 3 */
    rt_ubase_t s4;                  /* x20 - s4    - saved register 4 */
    rt_ubase_t s5;                  /* x21 - s5    - saved register 5 */
    rt_ubase_t s6;                  /* x22 - s6    - saved register 6 */
    rt_ubase_t s7;                  /* x23 - s7    - saved register 7 */
    rt_ubase_t s8;                  /* x24 - s8    - saved register 8 */
    rt_ubase_t s9;                  /* x25 - s9    - saved register 9 */
    rt_ubase_t s10;                 /* x26 - s10   - saved register 10 */
    rt_ubase_t s11;                 /* x27 - s11   - saved register 11 */
    rt_ubase_t t3;                  /* x28 - t3    - temporary register 3 */
    rt_ubase_t t4;                  /* x29 - t4    - temporary register 4 */
    rt_ubase_t t5;                  /* x30 - t5    - temporary register 5 */
    rt_ubase_t t6;                  /* x31 - t6    - temporary register 6 */
#endif /* !ARCH_RISCV_32E */

    rt_ubase_t user_sp_exc_stack;   /* sscratch - user mode sp/exception stack  */

#ifdef ARCH_RISCV_FPU
    rt_ubase_t f[CTX_FPU_REG_NR];   /* f0~f31 */
#endif
#ifdef ARCH_RISCV_VECTOR
    rt_ubase_t v[CTX_VECTOR_REG_NR];
#endif
};

RT_STATIC_ASSERT(riscv_trap_frame_size,
        sizeof(struct rt_hw_stack_frame) == CTX_ALL_REG_NR * sizeof(rt_ubase_t));
#endif /* __ASSEMBLY__ */

#endif /* __STACK_H__ */
