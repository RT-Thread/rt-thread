/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 * 2021-11-18     JasonHu      add fpu member
 */

#ifndef __STACK_H__
#define __STACK_H__

#include <rtthread.h>
#include "cpuport.h"

struct rt_hw_stack_frame
{
    rt_ubase_t ra;         /* x1  - ra     - return address for jumps            1*/
    rt_ubase_t x2;         /* x2  - sp     - stack pointer                       2*/
    rt_ubase_t gp;         /* x3  - gp     - global pointer                      3*/
    rt_ubase_t tp;         /* x4  - tp     - thread pointer                      4*/
    rt_ubase_t t0;         /* x5  - t0     - temporary register 0                5*/
    rt_ubase_t t1;         /* x6  - t1     - temporary register 1                6*/
    rt_ubase_t t2;         /* x7  - t2     - temporary register 2                7*/
    rt_ubase_t s0_fp;      /* x8  - s0/fp  - saved register 0 or frame pointer   8*/
    rt_ubase_t s1;         /* x9  - s1     - saved register 1                    9*/
    rt_ubase_t a0;         /* x10 - a0     - return value or function argument 0 10*/
    rt_ubase_t a1;         /* x11 - a1     - return value or function argument 1 11*/
    rt_ubase_t a2;         /* x12 - a2     - function argument 2                12*/
    rt_ubase_t a3;         /* x13 - a3     - function argument 3                13*/
    rt_ubase_t a4;         /* x14 - a4     - function argument 4                14*/
    rt_ubase_t a5;         /* x15 - a5     - function argument 5                15*/
#ifndef __riscv_32e
    rt_ubase_t a6;         /* x16 - a6     - function argument 6                16*/
    rt_ubase_t a7;         /* x17 - s7     - function argument 7                17*/
    rt_ubase_t s2;         /* x18 - s2     - saved register 2                   18*/
    rt_ubase_t s3;         /* x19 - s3     - saved register 3                   19*/
    rt_ubase_t s4;         /* x20 - s4     - saved register 4                   20*/
    rt_ubase_t s5;         /* x21 - s5     - saved register 5                   21*/
    rt_ubase_t s6;         /* x22 - s6     - saved register 6                   22*/
    rt_ubase_t s7;         /* x23 - s7     - saved register 7                   23*/
    rt_ubase_t s8;         /* x24 - s8     - saved register 8                   24*/
    rt_ubase_t s9;         /* x25 - s9     - saved register 9                   25*/
    rt_ubase_t s10;        /* x26 - s10    - saved register 10                  26*/
    rt_ubase_t s11;        /* x27 - s11    - saved register 11                  27*/
    rt_ubase_t t3;         /* x28 - t3     - temporary register 3               28*/
    rt_ubase_t t4;         /* x29 - t4     - temporary register 4               29*/
    rt_ubase_t t5;         /* x30 - t5     - temporary register 5               30*/
    rt_ubase_t t6;         /* x31 - t6     - temporary register 6               31*/
#endif
    rt_ubase_t epc;        /* epc - epc    - program counter                    32*/
    rt_ubase_t mstatus;    /*              - supervisor status register         33*/
};

#if defined(__riscv_flen) && defined(ARCH_RISCV_FPU)
typedef struct {
    rt_ubase_t fcsr;
#if __riscv_flen == 64
    uint64_t f[CTX_FPU_REG_NR];      /* f0~f31 */
#elif __riscv_flen == 32
    uint32_t f[CTX_FPU_REG_NR];      /* f0~f31 */
#endif
} __attribute__((__packed__)) rt_hw_stack_f_frame_t;
#endif /* __riscv_flen */

#if defined(__riscv_vector) && defined(ARCH_RISCV_VECTOR)
typedef struct {
    rt_ubase_t vl;
    rt_ubase_t vtype;
    rt_ubase_t vstart;
    rt_ubase_t vxsat;
    rt_ubase_t vxrm;
    rt_ubase_t v[];                    /* v0~v31 */
} rt_hw_stack_v_frame_t;
#endif

#if (defined(__riscv_matrix) || defined(__riscv_xtheadmatrix)) && defined(ARCH_RISCV_MATRIX)
typedef struct {
    rt_ubase_t xmrstart;
    rt_ubase_t xmcsr;
    rt_ubase_t xmsize;
    rt_ubase_t x[];                    /* M0 ~ M7 */
} rt_hw_stack_x_frame_t;
#endif

#endif
