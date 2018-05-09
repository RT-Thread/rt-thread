/*
 * File      : rtlibc.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
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
 * 2017-01-21     Bernard      the first version
 */

#ifndef RTLIBC_H__
#define RTLIBC_H__

/* definitions for libc if toolchain has no these definitions */
#include "libc/libc_stat.h"
#include "libc/libc_errno.h"

#include "libc/libc_fcntl.h"
#include "libc/libc_ioctl.h"
#include "libc/libc_dirent.h"
#include "libc/libc_signal.h"
#include "libc/libc_fdset.h"

#if defined(__CC_ARM) || defined(__IAR_SYSTEMS_ICC__)
typedef signed long off_t;
typedef int mode_t;
#endif

#if defined(__MINGW32__) || defined(_WIN32)
typedef signed long off_t;
typedef int mode_t;
#endif

#endif

