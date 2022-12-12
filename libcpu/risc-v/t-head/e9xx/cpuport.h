/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     zx.chen      The first version
 */

#ifndef CPUPORT_H__
#define CPUPORT_H__

#include <rtconfig.h>
#include <theadconfig.h>

/* bytes of register width  */
#ifdef ARCH_RISCV_64
#define DFSTORE                 fsd
#define DFLOAD                  fld
#define SFSTORE                 fsw
#define SFLOAD                  flw
#define STORE                   sd
#define LOAD                    ld
#define REGBYTES                8
#define SFREGBYTES              4
#define DFREGBYTES              8
#else
#define DFSTORE                 fsd
#define DFLOAD                  fld
#define SFSTORE                 fsw
#define SFLOAD                  flw
#define STORE                   sw
#define LOAD                    lw

#define REGBYTES                4
#define SFREGBYTES              4
#define DFREGBYTES              8
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
