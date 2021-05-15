/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-01-21     Bernard      the first version
 */

#ifndef RTLIBC_H__
#define RTLIBC_H__

/* definitions for libc if toolchain has no these definitions */
#include "libc/libc_stat.h"
#include "libc/libc_errno.h"

#include "libc/libc_fcntl.h"
#include "libc/libc_ioctl.h"
#include "libc/libc_signal.h"
#include "libc/libc_fdset.h"
#include "libc/libc_limits.h"
#include "libc/libc_stdio.h"

#ifndef RT_USING_LIBC
#if defined(__CC_ARM) || defined(__CLANG_ARM) || defined(__IAR_SYSTEMS_ICC__)
typedef signed long off_t;
typedef int mode_t;
#endif

/* dirent.h */
#define DT_UNKNOWN           0x00
#define DT_REG               0x01
#define DT_DIR               0x02

#endif

#if defined(__MINGW32__) || defined(_WIN32)
typedef signed long off_t;
typedef int mode_t;
#endif

#endif

