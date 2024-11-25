/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-09-22     Meco Man     the first version
 */

#ifndef __RT_KSTDIO_H__
#define __RT_KSTDIO_H__

#include <rttypes.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

int rt_vsprintf(char *dest, const char *format, va_list arg_ptr);
int rt_vsnprintf(char *buf, rt_size_t size, const char *fmt, va_list args);
int rt_sprintf(char *buf, const char *format, ...);
int rt_snprintf(char *buf, rt_size_t size, const char *format, ...);
int rt_vsscanf(const char *buffer, const char *format, va_list ap);
int rt_sscanf(const char *str, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif
