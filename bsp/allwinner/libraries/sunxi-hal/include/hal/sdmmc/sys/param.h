/*-
 * Copyright (c) 1982, 1986, 1989, 1993
 *  The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *  @(#)param.h 8.3 (Berkeley) 4/4/95
 * $FreeBSD: releng/10.1/sys/sys/param.h 272463 2014-10-03 00:58:34Z gjb $
 */

#ifndef _SYS_PARAM_H_
#define _SYS_PARAM_H_

#define NBBY    8       /* number of bits in a byte */
#define NBPW    sizeof(int) /* number of bytes per word (integer) */

/* Bit map related macros. */
#define setbit(a,i) (((unsigned char *)(a))[(i)/NBBY] |= 1<<((i)%NBBY))
#define clrbit(a,i) (((unsigned char *)(a))[(i)/NBBY] &= ~(1<<((i)%NBBY)))
#define isset(a,i)                          \
    (((const unsigned char *)(a))[(i)/NBBY] & (1<<((i)%NBBY)))
#define isclr(a,i)                          \
    ((((const unsigned char *)(a))[(i)/NBBY] & (1<<((i)%NBBY))) == 0)

/* Macros for counting and rounding. */
#ifndef howmany
#define howmany(x, y)   (((x)+((y)-1))/(y))
#endif
#define nitems(x)   (sizeof((x)) / sizeof((x)[0]))
#define rounddown(x, y) (((x)/(y))*(y))
#define rounddown2(x, y) ((x)&(~((y)-1)))          /* if y is power of two */
#define roundup(x, y)   ((((x)+((y)-1))/(y))*(y))  /* to any y */
#define roundup2(x, y)  (((x)+((y)-1))&(~((y)-1))) /* if y is powers of two */
#define powerof2(x) ((((x)-1)&(x))==0)

/* Macros for min/max. */
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

#define ct_assert(e) extern char (*ct_assert(void)) [sizeof(char[1 - 2*!(e)])]


#define do_div(n,base) ({                   \
        unsigned int __base = (base);                \
        unsigned int __rem;                      \
        __rem = ((u64)(n)) % __base;            \
        (n) = ((u64)(n)) / __base;              \
        __rem;                          \
    })


#endif  /* _SYS_PARAM_H_ */
