/*
 * File      : mips_types.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-09-07     Urey         the first version
 */

#ifndef _MIPS_TYPES_H_
#define _MIPS_TYPES_H_

#ifndef __ASSEMBLY__

typedef unsigned short umode_t;

/*
 * __xx is ok: it doesn't pollute the POSIX namespace. Use these in the
 * header files exported to user space
 */

typedef __signed__ char     __s8;
typedef unsigned char       __u8;

typedef __signed__ short    __s16;
typedef unsigned short      __u16;

typedef __signed__ int      __s32;
typedef unsigned int        __u32;

#if (_MIPS_SZLONG == 64)

typedef __signed__ long     __s64;
typedef unsigned long       __u64;

#else

#if defined(__GNUC__)
__extension__ typedef __signed__ long long __s64;
__extension__ typedef unsigned long long __u64;
#endif

#endif

/*
 * These aren't exported outside the kernel to avoid name space clashes
 */

#define BITS_PER_LONG _MIPS_SZLONG


typedef __signed char s8;
typedef unsigned char u8;

typedef __signed short s16;
typedef unsigned short u16;

typedef __signed int s32;
typedef unsigned int u32;

#if (_MIPS_SZLONG == 64)

typedef __signed__ long s64;
typedef unsigned long u64;

#else

#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
typedef __signed__ long long s64;
typedef unsigned long long u64;
#endif

#endif

typedef u32 dma_addr_t;

typedef u32 phys_addr_t;
typedef u32 phys_size_t;


/*
 * Don't use phys_t.  You've been warned.
 */

typedef unsigned long phys_t;

#endif /* __ASSEMBLY__ */


#endif /* _MIPS_TYPES_H_ */
