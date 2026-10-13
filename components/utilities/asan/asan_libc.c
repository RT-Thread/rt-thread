/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "asan.h"
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#ifdef __NEWLIB__
#include <newlib.h>
#endif

/* GNU ld redirects unresolved libc references here. This file belongs to the
 * non-instrumented runtime group: all checks below are explicit. Never call a
 * wrapped entry from its own wrapper; __real_* bypasses the redirection.
 */
void *__real_memcpy(void *dst, const void *src, size_t size);
void *__real_memmove(void *dst, const void *src, size_t size);
void *__real_memset(void *dst, int value, size_t size);
char *__real_strcpy(char *dst, const char *src);
char *__real_strncpy(char *dst, const char *src, size_t size);
char *__real_strcat(char *dst, const char *src);
char *__real_strncat(char *dst, const char *src, size_t size);
int __real_vsprintf(char *dst, const char *fmt, va_list args);
int __real_vsnprintf(char *dst, size_t size, const char *fmt, va_list args);

static rt_bool_t check_string(const char *src, size_t limit, size_t *length)
{
    rt_size_t available = 0;
    rt_bool_t bounded = RT_FALSE;
    size_t i = 0;

    if (limit)
    {
        bounded = rt_asan_accessible_size(src, &available);
    }
    while (i < limit)
    {
        if (bounded && i >= available)
        {
            *length = i;
            rt_asan_check_read(src + i, 1);
            return RT_FALSE;
        }
        if (!src[i])
        {
            break;
        }
        i++;
    }
    *length = i;
    return RT_TRUE;
}

void *__wrap_memcpy(void *dst, const void *src, size_t size)
{
    rt_bool_t readable = rt_asan_check_read(src, size);
    rt_bool_t writable = rt_asan_check_write(dst, size);
    return readable && writable ? __real_memcpy(dst, src, size) : dst;
}

void *__wrap_memmove(void *dst, const void *src, size_t size)
{
    rt_bool_t readable = rt_asan_check_read(src, size);
    rt_bool_t writable = rt_asan_check_write(dst, size);
    return readable && writable ? __real_memmove(dst, src, size) : dst;
}

void *__wrap_memset(void *dst, int value, size_t size)
{
    return rt_asan_check_write(dst, size) ? __real_memset(dst, value, size) : dst;
}

size_t __wrap_strlen(const char *src)
{
    size_t length;
    check_string(src, (size_t)-1, &length);
    return length;
}

size_t __wrap_strnlen(const char *src, size_t size)
{
    size_t length;
    check_string(src, size, &length);
    return length;
}

char *__wrap_strcpy(char *dst, const char *src)
{
    size_t length;
    if (!check_string(src, (size_t)-1, &length) || !rt_asan_check_write(dst, length + 1))
    {
        return dst;
    }
    return __real_strcpy(dst, src);
}

char *__wrap_strncpy(char *dst, const char *src, size_t size)
{
    size_t length;
    rt_bool_t readable = check_string(src, size, &length);
    rt_bool_t writable = rt_asan_check_write(dst, size);
    return readable && writable ? __real_strncpy(dst, src, size) : dst;
}

char *__wrap_strcat(char *dst, const char *src)
{
    size_t prefix, length;
    if (!check_string(dst, (size_t)-1, &prefix) ||
        !check_string(src, (size_t)-1, &length) ||
        !rt_asan_check_write(dst + prefix, length + 1))
    {
        return dst;
    }
    return __real_strcat(dst, src);
}

char *__wrap_strncat(char *dst, const char *src, size_t size)
{
    size_t prefix, length;
    if (!check_string(dst, (size_t)-1, &prefix) ||
        !check_string(src, size, &length) ||
        !rt_asan_check_write(dst + prefix, length + 1))
    {
        return dst;
    }
    return __real_strncat(dst, src, size);
}

enum format_length
{
    LENGTH_DEFAULT,
    LENGTH_HH,
    LENGTH_H,
    LENGTH_L,
    LENGTH_LL,
    LENGTH_J,
    LENGTH_Z,
    LENGTH_T,
    LENGTH_CAPITAL_L
};

/* The format is checked before parsing, so its characters are readable.
 * Unsupported extensions stop argument inspection instead of guessing their
 * va_arg types. The original libc still formats them; destination protection
 * does not require knowing the conversion syntax.
 */
static rt_bool_t check_format_arguments(const char *fmt, va_list args)
{
    size_t ignored;
    const char *scan;
    if (!check_string(fmt, (size_t)-1, &ignored))
    {
        return RT_FALSE;
    }
    /* Find positional conversions before consuming any argument, including
     * *N$ widths/precisions. Literal dollar signs and %% do not opt out.
     */
    for (scan = fmt; *scan;)
    {
        if (*scan++ == '%')
        {
            if (*scan == '%')
            {
                scan++;
                continue;
            }
            while (*scan && strchr("-+ #0'.*0123456789hljztL", *scan))
            {
                scan++;
            }
            if (*scan == '$')
            {
                return RT_TRUE;
            }
        }
    }
    while (*fmt)
    {
        enum format_length length = LENGTH_DEFAULT;
        int precision = -1;
        if (*fmt++ != '%')
        {
            continue;
        }
        while (*fmt && strchr("-+ #0'", *fmt))
        {
            fmt++;
        }
        if (*fmt == '*')
        {
            fmt++;
            if (*fmt == '$' || (*fmt >= '0' && *fmt <= '9'))
            {
                return RT_TRUE;
            }
            (void)va_arg(args, int);
        }
        else
        {
            while (*fmt >= '0' && *fmt <= '9')
            {
                fmt++;
            }
        }
        if (*fmt == '$' || (*fmt >= '0' && *fmt <= '9'))
        {
            return RT_TRUE;
        }
        if (*fmt == '.')
        {
            fmt++;
            precision = 0;
            if (*fmt == '*')
            {
                fmt++;
                if (*fmt == '$' || (*fmt >= '0' && *fmt <= '9'))
                {
                    return RT_TRUE;
                }
                precision = va_arg(args, int);
            }
            else
            {
                while (*fmt >= '0' && *fmt <= '9')
                {
                    int digit = *fmt++ - '0';
                    precision = precision > (INT_MAX - digit) / 10 ? INT_MAX : precision * 10 + digit;
                }
            }
        }
        switch (*fmt)
        {
        case 'h':
            length = *++fmt == 'h' ? (fmt++, LENGTH_HH) : LENGTH_H;
            break;
        case 'l':
            length = *++fmt == 'l' ? (fmt++, LENGTH_LL) : LENGTH_L;
            break;
        case 'j':
            length = LENGTH_J;
            fmt++;
            break;
        case 'z':
            length = LENGTH_Z;
            fmt++;
            break;
        case 't':
            length = LENGTH_T;
            fmt++;
            break;
        case 'L':
            length = LENGTH_CAPITAL_L;
            fmt++;
            break;
        default:
            break;
        }
#if defined(__NEWLIB__) && !defined(_WANT_IO_C99_FORMATS)
        if (length == LENGTH_HH || length == LENGTH_J || length == LENGTH_Z || length == LENGTH_T ||
            *fmt == 'a' || *fmt == 'A')
        {
            return RT_TRUE;
        }
#endif
#if defined(__NEWLIB__) && !defined(_WANT_IO_LONG_LONG)
        if (length == LENGTH_LL)
        {
            return RT_TRUE;
        }
#endif
#if defined(__NEWLIB__) && !defined(_WANT_IO_LONG_DOUBLE)
        if (length == LENGTH_CAPITAL_L)
        {
            return RT_TRUE;
        }
#endif
        switch (*fmt)
        {
        case 'd':
        case 'i':
            switch (length)
            {
            case LENGTH_L:
                (void)va_arg(args, long);
                break;
            case LENGTH_LL:
                (void)va_arg(args, long long);
                break;
            case LENGTH_J:
                (void)va_arg(args, intmax_t);
                break;
            case LENGTH_Z:
            case LENGTH_T:
                (void)va_arg(args, ptrdiff_t);
                break;
            case LENGTH_DEFAULT:
            case LENGTH_H:
            case LENGTH_HH:
                (void)va_arg(args, int);
                break;
            default:
                return RT_TRUE;
            }
            break;
        case 'u':
        case 'o':
        case 'x':
        case 'X':
            switch (length)
            {
            case LENGTH_L:
                (void)va_arg(args, unsigned long);
                break;
            case LENGTH_LL:
                (void)va_arg(args, unsigned long long);
                break;
            case LENGTH_J:
                (void)va_arg(args, uintmax_t);
                break;
            case LENGTH_Z:
            case LENGTH_T:
                (void)va_arg(args, size_t);
                break;
            case LENGTH_DEFAULT:
            case LENGTH_H:
            case LENGTH_HH:
                (void)va_arg(args, unsigned int);
                break;
            default:
                return RT_TRUE;
            }
            break;
        case 'a':
        case 'A':
        case 'e':
        case 'E':
        case 'f':
        case 'F':
        case 'g':
        case 'G':
            if (length == LENGTH_CAPITAL_L)
            {
                (void)va_arg(args, long double);
            }
            else if (length == LENGTH_DEFAULT || length == LENGTH_L)
            {
                (void)va_arg(args, double);
            }
            else
            {
                return RT_TRUE;
            }
            break;
        case 'c':
            if (length != LENGTH_DEFAULT)
            {
                return RT_TRUE;
            }
            (void)va_arg(args, int);
            break;
        case 'p':
            if (length != LENGTH_DEFAULT)
            {
                return RT_TRUE;
            }
            (void)va_arg(args, void *);
            break;
        case 's':
        {
            const char *src;
            if (length != LENGTH_DEFAULT)
            {
                return RT_TRUE;
            }
            src = va_arg(args, const char *);
            /* Preserve libc's handling of a NULL %s argument. */
            if (src && !check_string(src, precision < 0 ? (size_t)-1 : (size_t)precision, &ignored))
            {
                return RT_FALSE;
            }
            break;
        }
        case 'n':
        {
            void *dst;
            size_t size;
            switch (length)
            {
            case LENGTH_HH:
                dst = va_arg(args, signed char *);
                size = sizeof(signed char);
                break;
            case LENGTH_H:
                dst = va_arg(args, short *);
                size = sizeof(short);
                break;
            case LENGTH_L:
                dst = va_arg(args, long *);
                size = sizeof(long);
                break;
            case LENGTH_LL:
                dst = va_arg(args, long long *);
                size = sizeof(long long);
                break;
            case LENGTH_J:
                dst = va_arg(args, intmax_t *);
                size = sizeof(intmax_t);
                break;
            case LENGTH_Z:
            case LENGTH_T:
                dst = va_arg(args, ptrdiff_t *);
                size = sizeof(ptrdiff_t);
                break;
            case LENGTH_DEFAULT:
                dst = va_arg(args, int *);
                size = sizeof(int);
                break;
            default:
                return RT_TRUE;
            }
            if (!rt_asan_check_write(dst, size))
            {
                return RT_FALSE;
            }
            break;
        }
        case '%':
            if (length != LENGTH_DEFAULT)
            {
                return RT_TRUE;
            }
            break;
        default:
            return RT_TRUE;
        }
        fmt++;
    }
    return RT_TRUE;
}

static int checked_format(char *dst, size_t size, const char *fmt, va_list args, rt_bool_t unbounded)
{
    va_list probe;
    rt_size_t available = 0;
    rt_bool_t bounded = RT_FALSE;
    rt_bool_t valid;
    size_t limit = size;
    int result;

#ifdef __NEWLIB__
    /* Newlib rejects this limit before reading arguments or writing output.
     * Clamping it first would turn EOVERFLOW into a successful call.
     */
    if (!unbounded && size > INT_MAX)
    {
        return __real_vsnprintf(dst, size, fmt, args);
    }
#endif
    va_copy(probe, args);
    valid = check_format_arguments(fmt, probe);
    va_end(probe);
    if (!valid)
    {
        return -1;
    }
    if (size)
    {
        bounded = rt_asan_accessible_size(dst, &available);
        if (bounded && !available)
        {
            rt_asan_check_write(dst, 1);
            return -1;
        }
        if (bounded && limit > available)
        {
            limit = available;
        }
    }
    /* No sizing pass: it would execute %n twice and could change subsequent
     * source data. Clamp output to known heap storage, then report the bytes
     * libc would have written under the original limit. Valid calls retain
     * libc's return value, truncation rules and format extensions.
     */
    result = unbounded && !bounded ? __real_vsprintf(dst, fmt, args) : __real_vsnprintf(dst, limit, fmt, args);
    if (result >= 0 && size)
    {
        size_t written = (size_t)result + 1;
        if (written > size)
        {
            written = size;
        }
        rt_asan_check_write(dst, written);
    }
    return result;
}

int __wrap_vsprintf(char *dst, const char *fmt, va_list args)
{
    return checked_format(dst, (size_t)-1, fmt, args, RT_TRUE);
}

int __wrap_vsnprintf(char *dst, size_t size, const char *fmt, va_list args)
{
    return checked_format(dst, size, fmt, args, RT_FALSE);
}

int __wrap_sprintf(char *dst, const char *fmt, ...)
{
    int result;
    va_list args;
    va_start(args, fmt);
    result = checked_format(dst, (size_t)-1, fmt, args, RT_TRUE);
    va_end(args);
    return result;
}

int __wrap_snprintf(char *dst, size_t size, const char *fmt, ...)
{
    int result;
    va_list args;
    va_start(args, fmt);
    result = checked_format(dst, size, fmt, args, RT_FALSE);
    va_end(args);
    return result;
}
