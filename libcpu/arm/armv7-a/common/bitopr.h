/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#ifndef __BITOPR_H__
#define __BITOPR_H__

#include <stdint.h>

/* bit i */
#ifndef _B
#define _B(i)               (((i) >= 32) ? (1ull << (i)) : (1u << ((i) & 0x1f)))
#endif

/* mask */
#ifndef _MB
#define _MB(i)              (((i) > 32) ? (_B(i) - 1) : (uint32_t)(_B(i) - 1))
#endif

/* Starting from i bit, the continuous n bits are 1 */
#ifndef _NB
#define _NB(i, n)           (_MB(n) << (i))
#endif

/* i to j bit is 1 */
#ifndef _B_B
#define _B_B(i, j)          (((i) <= (j)) ? (_MB((j) + 1) - _MB(i)) : (_MB((i) + 1) - _MB(j)))
#endif

/* shift left */
#ifndef _L
#define _L(i, n)            ((i) << (n))
#endif

/* shift right */
#ifndef _R
#define _R(i, n)            ((i) >> (n))
#endif

 /* extracting from bit i to bit j */
#ifndef _E_B_B
#define _E_B_B(x, i, j)     (((i) <= (j)) ? (((x) & _B_B(i, j)) >> i) : (((x) & _B_B(i, j))) >> j)
#endif

#endif
