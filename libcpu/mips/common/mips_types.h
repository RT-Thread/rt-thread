/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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
