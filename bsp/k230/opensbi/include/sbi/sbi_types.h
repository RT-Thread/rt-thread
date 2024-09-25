/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_TYPES_H__
#define __SBI_TYPES_H__

#ifndef OPENSBI_EXTERNAL_SBI_TYPES

/* clang-format off */

typedef char			s8;
typedef unsigned char		u8;
typedef unsigned char		uint8_t;

typedef short			s16;
typedef unsigned short		u16;
typedef short			int16_t;
typedef unsigned short		uint16_t;

typedef int			s32;
typedef unsigned int		u32;
typedef int			int32_t;
typedef unsigned int		uint32_t;

#if __riscv_xlen == 64
typedef long			s64;
typedef unsigned long		u64;
typedef long			int64_t;
typedef unsigned long		uint64_t;
#define PRILX			"016lx"
#elif __riscv_xlen == 32
typedef long long		s64;
typedef unsigned long long	u64;
typedef long long		int64_t;
typedef unsigned long long	uint64_t;
#define PRILX			"08lx"
#else
#error "Unexpected __riscv_xlen"
#endif

typedef int			bool;
typedef unsigned long		ulong;
typedef unsigned long		uintptr_t;
typedef unsigned long		size_t;
typedef long			ssize_t;
typedef unsigned long		virtual_addr_t;
typedef unsigned long		virtual_size_t;
typedef unsigned long		physical_addr_t;
typedef unsigned long		physical_size_t;

#define TRUE			1
#define FALSE			0
#define true			TRUE
#define false			FALSE

#define NULL			((void *)0)

#define __packed		__attribute__((packed))
#define __noreturn		__attribute__((noreturn))
#define __aligned(x)		__attribute__((aligned(x)))

#define likely(x) __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE, MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#define container_of(ptr, type, member) ({			\
	const typeof(((type *)0)->member) * __mptr = (ptr);	\
	(type *)((char *)__mptr - offsetof(type, member)); })

#define array_size(x) 	(sizeof(x) / sizeof((x)[0]))

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CLAMP(a, lo, hi) MIN(MAX(a, lo), hi)

#define STR(x) XSTR(x)
#define XSTR(x) #x

#define ROUNDUP(a, b) ((((a)-1) / (b) + 1) * (b))
#define ROUNDDOWN(a, b) ((a) / (b) * (b))

/* clang-format on */

#else
/*
 * OPENSBI_EXTERNAL_SBI_TYPES could be defined in CFLAGS for using the
 * external definitions of data types and common macros.
 * OPENSBI_EXTERNAL_SBI_TYPES is the file name to external header file,
 * the external build system should address the additional include
 * directory ccordingly.
 */

#define XSTR(x) #x
#define STR(x) XSTR(x)
#include STR(OPENSBI_EXTERNAL_SBI_TYPES)
#endif

#endif
