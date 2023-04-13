/*
 *  drivers/standby/type.h
 *
 * Copyright (c) 2018 Allwinner.
 * 2018-09-14 Written by fanqinghua (fanqinghua@allwinnertech.com).
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#ifndef __TYPE_H__
#define __TYPE_H__

#define readb(addr)     (*((volatile unsigned char *)(long)(addr)))
#define readw(addr)     (*((volatile unsigned short *)(long)(addr)))
#define readl(addr)     (*((volatile unsigned int *)(long)(addr)))
#define writeb(v, addr) (*((volatile unsigned char *)(long)(addr)) = (unsigned char)(v))
#define writew(v, addr) (*((volatile unsigned short *)(long)(addr)) = (unsigned short)(v))
#define writel(v, addr) (*((volatile unsigned int *)(long)(addr)) = (unsigned int)(v))

typedef char            bool;
typedef char            s8;
typedef short           s16;
typedef int         s32;
typedef long long int       s64;

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long int  u64;

#define true    1
#define false   0

#define BIT(nr)         (1UL << (nr))

/* Compute the number of elements in the given array */
#define ARRAY_SIZE(a)               \
    (sizeof(a) / sizeof((a)[0]))

#endif /*__TYPE_H__*/
