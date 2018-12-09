/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include <stdint.h>
#include <stdbool.h>

#ifndef _B
#define _B(i)               (((i) >= 32) ? (1ull << (i)) : (1u << (i)))
#endif
#ifndef _MB
#define _MB(i)              (((i) > 32) ? (_B(i) - 1) : (uint32_t)(_B(i) - 1))
#endif
#ifndef _NB
#define _NB(i, n)           (_MB(n) << (i))
#endif
#ifndef _B_B
#define _B_B(i, j)          ((i <= j) ? (_MB(j + 1) - _MB(i)) : (_MB(i + 1) - _MB(j)))
#endif
#ifndef _L
#define _L(i, n)            ((i) << (n))
#endif
#ifndef _R
#define _R(i, n)            ((i) >> (n))
#endif
 // extracting from bit i to bit j
#ifndef _E_B_B
#define _E_B_B(x, i, j)     ((i <= j) ? ((x & _B_B(i, j)) >> i) : ((x & _B_B(i, j))) >> j)
#endif

#define _ARM_DSB()          asm volatile ("dsb\n\t")
#define _ARM_ISB()          asm volatile ("isb\n\t")
#define _ARM_DMB()          asm volatile ("dmb\n\t")
#define _ARM_CLZ(y, x)      asm volatile ("clz %[result], %[value]\n\t" : [result] "=r" (y) : [value] "r" (x))
#define _ARM_CP_R(coproc, opcode1, Rt, CRn, CRm, opcode2) \
    asm volatile ("mrc " #coproc ", " #opcode1 ", %[oup], " #CRn ", " #CRm ", " #opcode2 "\n\t" : [oup] "=r" (Rt))
#define _ARM_CP_W(coproc, opcode1, Rt, CRn, CRm, opcode2) \
    asm volatile ("mcr " #coproc ", " #opcode1 ", %[inp], " #CRn ", " #CRm ", " #opcode2 "\n\t" :: [inp] "r" (Rt))
