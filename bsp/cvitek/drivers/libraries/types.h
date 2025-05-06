/* SPDX-License-Identifier: Apache-2.0 */

#ifndef __TYPES_H
#define __TYPES_H

#ifndef __ASSEMBLY__
#ifdef CONFIG_64BIT
typedef unsigned long       uintptr_t;
typedef unsigned long       size_t;
/* bsd */
typedef unsigned char       u_char;
typedef unsigned short      u_short;
typedef unsigned int        u_int;
typedef unsigned long       u_long;

/* sysv */
typedef unsigned char       unchar;
typedef unsigned short      ushort;
typedef unsigned int        uint;
typedef unsigned long       ulong;

typedef signed char         s8;
typedef signed short        s16;
typedef signed int          s32;
typedef signed long         s64;

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long       u64;

typedef signed char         __s8;
typedef signed short        __s16;
typedef signed int          __s32;
typedef signed long         __s64;

typedef unsigned char       __u8;
typedef unsigned short      __u16;
typedef unsigned int        __u32;
typedef unsigned long       __u64;

#endif /*  CONFIG_64BIT */
#endif /*  __ASSEMBLY__ */
#endif /* __TYPES_H */
