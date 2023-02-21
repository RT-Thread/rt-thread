/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-03     Bernard      The first version
 * 2020/11/20     BalanceTWK   Add FPU support
 */

#ifndef CPUPORT_H__
#define CPUPORT_H__

#include <rtconfig.h>

/* bytes of register width  */
#define STORE                   sw
#define LOAD                    lw
#define REGBYTES                4

#ifdef __riscv_flen
#define ARCH_RISCV_FPU

#if __riscv_flen == 32
#define ARCH_RISCV_FPU_S
#endif

#if __riscv_flen == 64
#define ARCH_RISCV_FPU_D
#endif
#endif

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
