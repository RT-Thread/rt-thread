/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-10     Meco Man     the first version
 */

#include <rtthread.h>
#if defined(RT_KLIBC_USING_LIBC_VSSCANF) || \
    defined(RT_KLIBC_USING_LIBC_VSNPRINTF)
#include <stdio.h>
#endif

/**
 * @brief  This function will fill a formatted string to buffer.
 *
 * @param  buf is the buffer to save formatted string.
 *
 * @param  size is the size of buffer.
 *
 * @param  fmt is the format parameters.
 *
 * @return The number of characters actually written to buffer.
 */
int rt_snprintf(char *buf, rt_size_t size, const char *fmt, ...)
{
    rt_int32_t n = 0;
    va_list args;

    va_start(args, fmt);
    n = rt_vsnprintf(buf, size, fmt, args);
    va_end(args);

    return n;
}
RTM_EXPORT(rt_snprintf);

/**
 * @brief  This function will fill a formatted string to buffer.
 *
 * @param  buf is the buffer to save formatted string.
 *
 * @param  format is the format parameters.
 *
 * @param  arg_ptr is a list of variable parameters.
 *
 * @return The number of characters actually written to buffer.
 */
int rt_vsprintf(char *buf, const char *format, va_list arg_ptr)
{
    return rt_vsnprintf(buf, (rt_size_t) - 1, format, arg_ptr);
}
RTM_EXPORT(rt_vsprintf);

/**
 * @brief  This function will fill a formatted string to buffer
 *
 * @param  buf the buffer to save formatted string.
 *
 * @param  format is the format parameters.
 *
 * @return The number of characters actually written to buffer.
 */
int rt_sprintf(char *buf, const char *format, ...)
{
    rt_int32_t n = 0;
    va_list arg_ptr;

    va_start(arg_ptr, format);
    n = rt_vsprintf(buf, format, arg_ptr);
    va_end(arg_ptr);

    return n;
}
RTM_EXPORT(rt_sprintf);

#ifdef RT_KLIBC_USING_LIBC_VSNPRINTF
int rt_vsnprintf(char *buf, rt_size_t size, const char *fmt, va_list args)
{
    return vsnprintf(buf, size, fmt, args);
}
#endif /* RT_KLIBC_USING_LIBC_VSNPRINTF */
RTM_EXPORT(rt_vsnprintf);

#ifdef RT_KLIBC_USING_LIBC_VSSCANF
int rt_vsscanf(const char *buffer, const char *format, va_list ap)
{
    return vsscanf(buffer, format, ap);
}
#endif /* RT_KLIBC_USING_LIBC_VSSCANF */
RTM_EXPORT(rt_vsscanf);

/**
 * @brief  This function parses a formatted string from the input string.
 *
 * @param  str the input string to be parsed.
 *
 * @param  format the format string that specifies how to interpret the input.
 *
 * @return The number of input items successfully matched and assigned.
 */
int rt_sscanf(const char *str, const char *format, ...)
{
    va_list ap;
    int rv;

    va_start(ap, format);
    rv = rt_vsscanf(str, format, ap);
    va_end(ap);

    return rv;
}
RTM_EXPORT(rt_sscanf);
