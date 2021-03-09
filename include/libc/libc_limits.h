/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-05     Meco Man     the first version
 */

#ifndef LIBC_LIMITS_H__
#define LIBC_LIMITS_H__

#include <limits.h>
#include <rtconfig.h>

#ifdef RT_USING_POSIX

#ifndef SSIZE_MAX
# define SSIZE_MAX      LONG_MAX
#endif

#endif

#endif
