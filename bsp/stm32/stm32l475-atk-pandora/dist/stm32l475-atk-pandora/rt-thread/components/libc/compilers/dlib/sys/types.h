/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>
#include <rtthread.h>

typedef rt_int32_t clockid_t;
typedef rt_int32_t key_t;       /* Used for interprocess communication. */
typedef rt_int32_t pid_t;       /* Used for process IDs and process group IDs. */
#ifndef ARCH_CPU_64BIT
typedef signed int   ssize_t;  /* Used for a count of bytes or an error indication. */
#else
typedef long signed int   ssize_t;  /* Used for a count of bytes or an error indication. */
#endif

#endif
