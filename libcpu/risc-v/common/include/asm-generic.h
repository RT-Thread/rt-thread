/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-12     WangXiaoyao  the first version
 * 2025-04-20     GuEe-GUI     Merge 64 and 32 mode
 */

#ifndef __ASM_GENERIC_H__
#define __ASM_GENERIC_H__

#include <rtconfig.h>

#ifdef __ASSEMBLY__
/* use to mark a start point where every task start from */
#define START_POINT(funcname)               \
    .global funcname;                       \
    .type funcname, %function;	            \
    funcname:                               \
    .cfi_sections .debug_frame, .eh_frame;  \
    .cfi_startproc;                         \
    .cfi_undefined ra

#define START_POINT_END(name)   \
    .cfi_endproc;               \
    .size name, .-name;

#define _AC(X,Y)        X
#define _AT(T,X)        X
#define __ASM_STR(x)    x
#else
#define _AC(X,Y)        (X##Y)
#define _AT(T,X)        ((T)(X))
#define __ASM_STR(x)    #x
#endif

#define _UL(x)          (_AC(x, UL))
#define _ULL(x)         (_AC(x, ULL))

#if __riscv_xlen == 64
#define BITS_PER_LONG   8
#define __REG_SEL(a, b) __ASM_STR(a)
#elif __riscv_xlen == 32
#define BITS_PER_LONG   4
#define __REG_SEL(a, b) __ASM_STR(b)
#else
#error "Unexpected __riscv_xlen"
#endif

#ifndef BIT
#define BIT(x)          (_UL(1) << (x))
#endif

#ifndef GENMASK
#define GENMASK(h, l)   (((_UL(~0)) << (l)) & (_UL(~0) >> (BITS_PER_LONG - 1 - (h))))
#endif

#define REG_WIDTH       __REG_SEL(d, w)
#define REG_L           __REG_SEL(ld, lw)
#define REG_S           __REG_SEL(sd, sw)
#define REG_SC          __REG_SEL(sc.d, sc.w)
#define REG_AMOSWAP_AQ  __REG_SEL(amoswap.d.aq, amoswap.w.aq)
#define REG_ASM         __REG_SEL(.dword, .word)
#define SZREG           __REG_SEL(8, 4)
#define LGREG           __REG_SEL(3, 2)
#define FREG_L          __REG_SEL(fld, flw)
#define FREG_S          __REG_SEL(fsd, fsw)

#if __riscv_xlen == 64
#ifdef __ASSEMBLY__
#define RISCV_PTR       .dword
#define RISCV_SZPTR     8
#define RISCV_LGPTR     3
#else
#define RISCV_PTR       ".dword"
#define RISCV_SZPTR     "8"
#define RISCV_LGPTR     "3"
#endif
#elif __riscv_xlen == 32
#ifdef __ASSEMBLY__
#define RISCV_PTR       .word
#define RISCV_SZPTR     4
#define RISCV_LGPTR     2
#else
#define RISCV_PTR       ".word"
#define RISCV_SZPTR     "4"
#define RISCV_LGPTR     "2"
#endif
#else
#error "Unexpected __riscv_xlen"
#endif

#endif /* __ASM_GENERIC_H__ */
