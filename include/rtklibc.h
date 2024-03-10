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

/* kstring */

#ifndef RT_KSERVICE_USING_STDLIB_MEMORY
void *rt_memset(void *src, int c, rt_ubase_t n);
void *rt_memcpy(void *dest, const void *src, rt_ubase_t n);
void *rt_memmove(void *dest, const void *src, rt_size_t n);
rt_int32_t rt_memcmp(const void *cs, const void *ct, rt_size_t count);
#endif /* RT_KSERVICE_USING_STDLIB_MEMORY */
char *rt_strdup(const char *s);
rt_size_t rt_strnlen(const char *s, rt_ubase_t maxlen);
#ifndef RT_KSERVICE_USING_STDLIB
char *rt_strstr(const char *str1, const char *str2);
rt_int32_t rt_strcasecmp(const char *a, const char *b);
char *rt_strcpy(char *dst, const char *src);
char *rt_strncpy(char *dest, const char *src, rt_size_t n);
rt_int32_t rt_strncmp(const char *cs, const char *ct, rt_size_t count);
rt_int32_t rt_strcmp(const char *cs, const char *ct);
rt_size_t rt_strlen(const char *src);
#else
#include <string.h>
#ifdef RT_KSERVICE_USING_STDLIB_MEMORY
#define rt_memset(s, c, count)      memset(s, c, count)
#define rt_memcpy(dst, src, count)  memcpy(dst, src, count)
#define rt_memmove(dest, src, n)    memmove(dest, src, n)
#define rt_memcmp(cs, ct, count)    memcmp(cs, ct, count)
#endif /* RT_KSERVICE_USING_STDLIB_MEMORY */
#define rt_strstr(str1, str2)       strstr(str1, str2)
#define rt_strcasecmp(a, b)         strcasecmp(a, b)
#define rt_strcpy(dest, src)        strcpy(dest, src)
#define rt_strncpy(dest, src, n)    strncpy(dest, src, n)
#define rt_strncmp(cs, ct, count)   strncmp(cs, ct, count)
#define rt_strcmp(cs, ct)           strcmp(cs, ct)
#define rt_strlen(src)              strlen(src)
#endif /*RT_KSERVICE_USING_STDLIB*/

#ifdef __cplusplus
}
#endif

#endif /* __RT_KLIBC_H__ */
