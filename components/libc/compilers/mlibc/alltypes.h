/*
 * Copyright (c) mlibc & plct lab
 *
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/06/16     bernard      the first verison
 */

#ifndef MLIBC_ALLTYPES_H__
#define MLIBC_ALLTYPES_H__

#include <stdint.h>

typedef uint64_t fsblkcnt_t;
typedef uint64_t fsfilcnt_t;

#define INT_FAST16_MIN  INT32_MIN
#define INT_FAST32_MIN  INT32_MIN

#define INT_FAST16_MAX  INT32_MAX
#define INT_FAST32_MAX  INT32_MAX

#define UINT_FAST16_MAX UINT32_MAX
#define UINT_FAST32_MAX UINT32_MAX

#if (defined(__GNUC__) && (__SIZEOF_POINTER__ == 8))
#define __LONG_MAX INT64_MAX
#else
#define __LONG_MAX INT32_MAX
#endif /* __GNUC__ */

#endif
