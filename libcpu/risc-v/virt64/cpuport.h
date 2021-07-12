/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-03     Bernard      The first version
 */

#ifndef CPUPORT_H__
#define CPUPORT_H__

#include <rtconfig.h>

/* bytes of register width  */
#ifdef ARCH_CPU_64BIT
#define STORE                   sd
#define LOAD                    ld
#define REGBYTES                8
#else
// error here, not portable
#endif

#ifdef RISCV_U_MODE
#define RISCV_USER_ENTRY 0xFFFFFFE000000000ULL
#endif

#ifdef RISCV_S_MODE
//csr in s-mode
// M/U/S Interrupt Registers
#define SRC_XIE         sie
#define SRC_XIP         sip
#define SRC_XTVEC       stvec
#define SRC_XSTATUS     sstatus
#define SRC_XSCRATCH    sscratch
#define SRC_XEPC        sepc
#define SRC_XCAUSE      scause
#define SRC_XTVAL       stval
#define XRET            sret
#else
//csr in m-mode
// M/U/S Interrupt Registers
#define SRC_XIE         mie
#define SRC_XIP         mip
#define SRC_XTVEC       mtvec
#define SRC_XSTATUS     mstatus
#define SRC_XSCRATCH    mscratch
#define SRC_XEPC        mepc
#define SRC_XCAUSE      mcause
#define SRC_XTVAL       mtval
#define XRET            mret
#endif

#endif
