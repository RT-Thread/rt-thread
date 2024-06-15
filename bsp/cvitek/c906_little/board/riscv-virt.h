/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/01/11     flyingcys    The first version
 */

#ifndef RISCV_VIRT_H_
#define RISCV_VIRT_H_

#include "riscv-reg.h"

#ifdef __ASSEMBLER__
#define CONS(NUM, TYPE)NUM
#else
#define CONS(NUM, TYPE)NUM##TYPE
#endif /* __ASSEMBLER__ */

#define PRIM_HART           0
#ifdef RISCV_QEMU
#define CLINT_ADDR          CONS(0x02000000, UL)
#define CLINT_MSIP          CONS(0x0000, UL)
#define CLINT_MTIMECMP      CONS(0x4000, UL)
#define CLINT_MTIME         CONS(0xbff8, UL)
#else
#define CLINT_ADDR          CONS(0x74000000, UL)
#define CLINT_MSIP          CONS(0x0000, UL)
#define CLINT_MTIMECMP      CONS(0x4000, UL)
#undef CLINT_MTIME
//#define CLINT_MTIME           CONS(0x4004, UL)
#endif
//#define NS16550_ADDR      CONS(0x10000000, UL)

#ifndef __ASSEMBLER__

int xGetCoreID( void );

#endif /* __ASSEMBLER__ */

#endif /* RISCV_VIRT_H_ */
