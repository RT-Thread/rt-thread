/****************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 *
 * Copyright (C) 2007 Michael Giacomelli
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/

/*  fixed precision code.  We use a combination of Sign 15.16 and Sign.31
     precision here.

    The WMA decoder does not always follow this convention, and occasionally
    renormalizes values to other formats in order to maximize precision.
    However, only the two precisions above are provided in this file.

*/

#include "types.h"

#define PRECISION       16
#define PRECISION64     16


#define fixtof64(x)       (float)((float)(x) / (float)(1 << PRECISION64))        //does not work on int64_t!
#define ftofix32(x)       ((fixed32)((x) * (float)(1 << PRECISION) + ((x) < 0 ? -0.5 : 0.5)))
#define itofix64(x)       (IntTo64(x))
#define itofix32(x)       ((x) << PRECISION)
#define fixtoi32(x)       ((x) >> PRECISION)
#define fixtoi64(x)       (IntFrom64(x))


/*fixed functions*/

fixed64 IntTo64(int x);
int IntFrom64(fixed64 x);
fixed32 Fixed32From64(fixed64 x);
fixed64 Fixed32To64(fixed32 x);
fixed64 fixmul64byfixed(fixed64 x, fixed32 y);
fixed32 fixdiv32(fixed32 x, fixed32 y);
fixed64 fixdiv64(fixed64 x, fixed64 y);
fixed32 fixsqrt32(fixed32 x);
long fsincos(unsigned long phase, fixed32 *cos);

#ifdef CPU_ARM

/*Sign-15.16 format */

#define fixmul32(x, y)  \
    ({ int32_t __hi;  \
       uint32_t __lo;  \
       int32_t __result;  \
       asm ("smull   %0, %1, %3, %4\n\t"  \
            "movs    %0, %0, lsr %5\n\t"  \
            "adc    %2, %0, %1, lsl %6"  \
            : "=&r" (__lo), "=&r" (__hi), "=r" (__result)  \
            : "%r" (x), "r" (y),  \
              "M" (PRECISION), "M" (32 - PRECISION)  \
            : "cc");  \
       __result;  \
    })

#define fixmul32b(x, y)  \
    ({ int32_t __hi;  \
       uint32_t __lo;  \
       int32_t __result;  \
       asm ("smull   %0, %1, %3, %4\n\t"  \
            "movs    %2, %1, lsl #1"  \
            : "=&r" (__lo), "=&r" (__hi), "=r" (__result)  \
            : "%r" (x), "r" (y)  \
            : "cc");  \
       __result;  \
    })

#elif defined(CPU_COLDFIRE)

static inline int32_t fixmul32(int32_t x, int32_t y)
{
#if PRECISION != 16
#warning Coldfire fixmul32() only works for PRECISION == 16
#endif
    int32_t t1;
    asm (
        "mac.l   %[x], %[y], %%acc0  \n" /* multiply */
        "mulu.l  %[y], %[x]      \n"     /* get lower half, avoid emac stall */
        "movclr.l %%acc0, %[t1]  \n"     /* get higher half */
        "lsr.l   #1, %[t1]       \n"
        "move.w  %[t1], %[x]     \n"
        "swap    %[x]            \n"
        : [t1] "=&d" (t1), [x] "+d" (x)
        : [y] "d"  (y)
    );
    return x;
}

static inline int32_t fixmul32b(int32_t x, int32_t y)
{
    asm (
        "mac.l   %[x], %[y], %%acc0  \n" /* multiply */
        "movclr.l %%acc0, %[x]  \n"     /* get higher half */
        : [x] "+d" (x)
        : [y] "d"  (y)
    );
    return x;
}

#else

static inline fixed32 fixmul32(fixed32 x, fixed32 y)
{
    fixed64 temp;
    temp = x;
    temp *= y;

    temp >>= PRECISION;

    return (fixed32)temp;
}

static inline fixed32 fixmul32b(fixed32 x, fixed32 y)
{
    fixed64 temp;

    temp = x;
    temp *= y;

    temp >>= 31;        //16+31-16 = 31 bits

    return (fixed32)temp;
}

#endif

