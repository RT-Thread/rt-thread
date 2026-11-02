/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-03     Bernard      The first version
 * 2020/11/20     BalanceTWK   Add FPU support
 * 2023/01/04     WangShun     Adapt to CH32
 * 2023/08/11     HPMicro      Define ARCH_RISCV_FPU if FPU is enabled
 */

#ifndef CPUPORT_H__
#define CPUPORT_H__

#include <rtconfig.h>

#ifndef __ASSEMBLY__
#ifdef RT_USING_SMP
typedef union {
    unsigned long slock;
    struct __arch_tickets {
        unsigned short owner;
        unsigned short next;
    } tickets;
} rt_hw_spinlock_t;
#endif
#endif

/* Preprocessor Definition */
#if __riscv_flen == 32
#define ARCH_RISCV_FPU
#define ARCH_RISCV_FPU_S
#endif

#if __riscv_flen == 64
#define ARCH_RISCV_FPU
#define ARCH_RISCV_FPU_D
#endif

/* bytes of register width  */
#ifdef ARCH_CPU_64BIT
#define STORE                   sd
#define LOAD                    ld
#define REGBYTES                8
#else
#define STORE                   sw
#define LOAD                    lw
#define REGBYTES                4
#endif

/* Preprocessor Definition */
#ifdef ARCH_RISCV_FPU
#ifdef ARCH_RISCV_FPU_D
#define FSTORE                  fsd
#define FLOAD                   fld
#define FREGBYTES               8
#define rv_floatreg_t           rt_int64_t
#endif
#ifdef ARCH_RISCV_FPU_S
#define FSTORE                  fsw
#define FLOAD                   flw
#define FREGBYTES               4
#define rv_floatreg_t           rt_int32_t
#endif
#endif

#endif
