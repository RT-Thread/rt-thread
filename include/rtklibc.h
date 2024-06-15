/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-10     Meco Man     the first version
 */

#ifndef __RT_KLIBC_H__
#define __RT_KLIBC_H__

#include <rtconfig.h>
#include <rtdef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* kstdio */
int rt_vsprintf(char *dest, const char *format, va_list arg_ptr);
int rt_vsnprintf(char *buf, rt_size_t size, const char *fmt, va_list args);
int rt_sprintf(char *buf, const char *format, ...);
int rt_snprintf(char *buf, rt_size_t size, const char *format, ...);

rt_err_t rt_get_errno(void);
void rt_set_errno(rt_err_t no);
int *_rt_errno(void);
const char *rt_strerror(rt_err_t error);
#if !defined(RT_USING_NEWLIBC) && !defined(_WIN32)
#ifndef errno
#define errno    *_rt_errno()
#endif
#endif /* !defined(RT_USING_NEWLIBC) && !defined(_WIN32) */

/* kstring */

void *rt_memset(void *src, int c, rt_ubase_t n);
void *rt_memcpy(void *dest, const void *src, rt_ubase_t n);
void *rt_memmove(void *dest, const void *src, rt_size_t n);
rt_int32_t rt_memcmp(const void *cs, const void *ct, rt_size_t count);
char *rt_strdup(const char *s);
rt_size_t rt_strnlen(const char *s, rt_ubase_t maxlen);
char *rt_strstr(const char *str1, const char *str2);
rt_int32_t rt_strcasecmp(const char *a, const char *b);
char *rt_strcpy(char *dst, const char *src);
char *rt_strncpy(char *dest, const char *src, rt_size_t n);
rt_int32_t rt_strncmp(const char *cs, const char *ct, rt_size_t count);
rt_int32_t rt_strcmp(const char *cs, const char *ct);
rt_size_t rt_strlen(const char *src);

#ifdef __cplusplus
}
#endif

#endif /* __RT_KLIBC_H__ */
