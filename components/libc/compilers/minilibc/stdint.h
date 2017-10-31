#ifndef __STDINT_H__
#define __STDINT_H__

typedef signed char  int8_t;
typedef signed short int16_t;
typedef signed int   int32_t;

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

typedef long long		int64_t;
typedef unsigned long long uint64_t;
typedef signed long     intptr_t;
typedef unsigned long   uintptr_t;

/*
 * 7.18.2 Limits of specified-width integer types.
 *
 * The following object-like macros specify the minimum and maximum limits
 * of integer types corresponding to the typedef names defined above.
 */

/* 7.18.2.1 Limits of exact-width integer types */
#define	INT8_MIN		(-0x7f - 1)
#define	INT16_MIN		(-0x7fff - 1)
#define	INT32_MIN		(-0x7fffffff - 1)

#define	INT8_MAX		0x7f
#define	INT16_MAX		0x7fff
#define	INT32_MAX		0x7fffffff

#define	UINT8_MAX		0xff
#define	UINT16_MAX		0xffff
#define	UINT32_MAX		0xffffffffU

#ifndef __INT_MAX__
#define __INT_MAX__     2147483647
#endif
#define INT_MIN         (-1 - INT_MAX)
#define INT_MAX         (__INT_MAX__)
#define UINT_MAX        (INT_MAX * 2U + 1U)

#define LONG_MAX	((long)(~0UL>>1))
#define LONG_MIN	(-LONG_MAX - 1)
#define ULONG_MAX	(~0UL)

#define SIZE_MAX	ULONG_MAX

#endif
