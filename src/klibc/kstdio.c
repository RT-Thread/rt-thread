/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-10     Meco Man     the first version
 */

#include <rtdef.h>
#include <rtcompiler.h>
#include <rtklibc.h>
#include <rtm.h>

#define DBG_TAG           "kernel.stdio"
#ifdef RT_DEBUG_DEVICE
#define DBG_LVL           DBG_LOG
#else
#define DBG_LVL           DBG_WARNING
#endif /* defined (RT_DEBUG_DEVICE) */
#include <rtdbg.h>

/* private function */
#define _ISDIGIT(c)  ((unsigned)((c) - '0') < 10)

/**
 * @brief  This function will duplicate a string.
 *
 * @param  n is the string to be duplicated.
 *
 * @param  base is support divide instructions value.
 *
 * @return the duplicated string pointer.
 */
#ifdef RT_KPRINTF_USING_LONGLONG
rt_inline int divide(unsigned long long *n, int base)
#else
rt_inline int divide(unsigned long *n, int base)
#endif /* RT_KPRINTF_USING_LONGLONG */
{
    int res;

    /* optimized for processor which does not support divide instructions. */
#ifdef RT_KPRINTF_USING_LONGLONG
    res = (int)((*n) % base);
    *n = (long long)((*n) / base);
#else
    res = (int)((*n) % base);
    *n = (long)((*n) / base);
#endif

    return res;
}

rt_inline int skip_atoi(const char **s)
{
    int i = 0;
    while (_ISDIGIT(**s))
        i = i * 10 + *((*s)++) - '0';

    return i;
}

#define ZEROPAD     (1 << 0)    /* pad with zero */
#define SIGN        (1 << 1)    /* unsigned/signed long */
#define PLUS        (1 << 2)    /* show plus */
#define SPACE       (1 << 3)    /* space if plus */
#define LEFT        (1 << 4)    /* left justified */
#define SPECIAL     (1 << 5)    /* 0x */
#define LARGE       (1 << 6)    /* use 'ABCDEF' instead of 'abcdef' */

static char *print_number(char *buf,
                          char *end,
#ifdef RT_KPRINTF_USING_LONGLONG
                          unsigned long long  num,
#else
                          unsigned long  num,
#endif /* RT_KPRINTF_USING_LONGLONG */
                          int   base,
                          int   qualifier,
                          int   s,
                          int   precision,
                          int   type)
{
    char c = 0, sign = 0;
#ifdef RT_KPRINTF_USING_LONGLONG
    char tmp[64] = {0};
#else
    char tmp[32] = {0};
#endif /* RT_KPRINTF_USING_LONGLONG */
    int precision_bak = precision;
    const char *digits = RT_NULL;
    static const char small_digits[] = "0123456789abcdef";
    static const char large_digits[] = "0123456789ABCDEF";
    int i = 0;
    int size = 0;

    size = s;

    digits = (type & LARGE) ? large_digits : small_digits;
    if (type & LEFT)
    {
        type &= ~ZEROPAD;
    }

    c = (type & ZEROPAD) ? '0' : ' ';

    /* get sign */
    sign = 0;
    if (type & SIGN)
    {
        switch (qualifier)
        {
        case 'h':
            if ((rt_int16_t)num < 0)
            {
                sign = '-';
                num = (rt_uint16_t)-num;
            }
            break;
        case 'L':
        case 'l':
            if ((long)num < 0)
            {
                sign = '-';
                num = (unsigned long)-num;
            }
            break;
        case 0:
        default:
            if ((rt_int32_t)num < 0)
            {
                sign = '-';
                num = (rt_uint32_t)-num;
            }
            break;
        }

        if (sign != '-')
        {
            if (type & PLUS)
            {
                sign = '+';
            }
            else if (type & SPACE)
            {
                sign = ' ';
            }
        }
    }

    if (type & SPECIAL)
    {
        if (base == 2 || base == 16)
        {
            size -= 2;
        }
        else if (base == 8)
        {
            size--;
        }
    }

    i = 0;
    if (num == 0)
    {
        tmp[i++] = '0';
    }
    else
    {
        while (num != 0)
            tmp[i++] = digits[divide(&num, base)];
    }

    if (i > precision)
    {
        precision = i;
    }
    size -= precision;

    if (!(type & (ZEROPAD | LEFT)))
    {
        if ((sign) && (size > 0))
        {
            size--;
        }

        while (size-- > 0)
        {
            if (buf < end)
            {
                *buf = ' ';
            }

            ++ buf;
        }
    }

    if (sign)
    {
        if (buf < end)
        {
            *buf = sign;
        }
        -- size;
        ++ buf;
    }

    if (type & SPECIAL)
    {
        if (base == 2)
        {
            if (buf < end)
                *buf = '0';
            ++ buf;
            if (buf < end)
                *buf = 'b';
            ++ buf;
        }
        else if (base == 8)
        {
            if (buf < end)
                *buf = '0';
            ++ buf;
        }
        else if (base == 16)
        {
            if (buf < end)
            {
                *buf = '0';
            }

            ++ buf;
            if (buf < end)
            {
                *buf = type & LARGE ? 'X' : 'x';
            }
            ++ buf;
        }
    }

    /* no align to the left */
    if (!(type & LEFT))
    {
        while (size-- > 0)
        {
            if (buf < end)
            {
                *buf = c;
            }

            ++ buf;
        }
    }

    while (i < precision--)
    {
        if (buf < end)
        {
            *buf = '0';
        }

        ++ buf;
    }

    /* put number in the temporary buffer */
    while (i-- > 0 && (precision_bak != 0))
    {
        if (buf < end)
        {
            *buf = tmp[i];
        }

        ++ buf;
    }

    while (size-- > 0)
    {
        if (buf < end)
        {
            *buf = ' ';
        }

        ++ buf;
    }

    return buf;
}

#if defined(__GNUC__) && !defined(__ARMCC_VERSION) /* GCC */
#pragma GCC diagnostic push
/* ignore warning: this statement may fall through */
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#endif /* defined(__GNUC__) && !defined(__ARMCC_VERSION) */
/**
 * @brief  This function will fill a formatted string to buffer.
 *
 * @param  buf is the buffer to save formatted string.
 *
 * @param  size is the size of buffer.
 *
 * @param  fmt is the format parameters.
 *
 * @param  args is a list of variable parameters.
 *
 * @return The number of characters actually written to buffer.
 */
rt_weak int rt_vsnprintf(char *buf, rt_size_t size, const char *fmt, va_list args)
{
#ifdef RT_KPRINTF_USING_LONGLONG
    unsigned long long num = 0;
#else
    unsigned long num = 0;
#endif /* RT_KPRINTF_USING_LONGLONG */
    int i = 0, len = 0;
    char *str = RT_NULL, *end = RT_NULL, c = 0;
    const char *s = RT_NULL;

    rt_uint8_t base = 0;            /* the base of number */
    rt_uint8_t flags = 0;           /* flags to print number */
    rt_uint8_t qualifier = 0;       /* 'h', 'l', or 'L' for integer fields */
    rt_int32_t field_width = 0;     /* width of output field */
    int precision = 0;      /* min. # of digits for integers and max for a string */

    str = buf;
    end = buf + size;

    /* Make sure end is always >= buf */
    if (end < buf)
    {
        end  = ((char *) - 1);
        size = end - buf;
    }

    for (; *fmt ; ++fmt)
    {
        if (*fmt != '%')
        {
            if (str < end)
            {
                *str = *fmt;
            }

            ++ str;
            continue;
        }

        /* process flags */
        flags = 0;

        while (1)
        {
            /* skips the first '%' also */
            ++fmt;
            if (*fmt == '-') flags |= LEFT;
            else if (*fmt == '+') flags |= PLUS;
            else if (*fmt == ' ') flags |= SPACE;
            else if (*fmt == '#') flags |= SPECIAL;
            else if (*fmt == '0') flags |= ZEROPAD;
            else break;
        }

        /* get field width */
        field_width = -1;
        if (_ISDIGIT(*fmt))
        {
            field_width = skip_atoi(&fmt);
        }
        else if (*fmt == '*')
        {
            ++fmt;
            /* it's the next argument */
            field_width = va_arg(args, int);
            if (field_width < 0)
            {
                field_width = -field_width;
                flags |= LEFT;
            }
        }

        /* get the precision */
        precision = -1;
        if (*fmt == '.')
        {
            ++fmt;
            if (_ISDIGIT(*fmt))
            {
                precision = skip_atoi(&fmt);
            }
            else if (*fmt == '*')
            {
                ++fmt;
                /* it's the next argument */
                precision = va_arg(args, int);
            }
            if (precision < 0)
            {
                precision = 0;
            }
        }

        qualifier = 0; /* get the conversion qualifier */

        if (*fmt == 'h' || *fmt == 'l' ||
#ifdef RT_KPRINTF_USING_LONGLONG
            *fmt == 'L' ||
#endif /* RT_KPRINTF_USING_LONGLONG */
            *fmt == 'z')
        {
            qualifier = *fmt;
            ++fmt;
#ifdef RT_KPRINTF_USING_LONGLONG
            if (qualifier == 'l' && *fmt == 'l')
            {
                qualifier = 'L';
                ++fmt;
            }
#endif /* RT_KPRINTF_USING_LONGLONG */
            if (qualifier == 'h' && *fmt == 'h')
            {
                qualifier = 'H';
                ++fmt;
            }
        }

        /* the default base */
        base = 10;

        switch (*fmt)
        {
        case 'c':
            if (!(flags & LEFT))
            {
                while (--field_width > 0)
                {
                    if (str < end) *str = ' ';
                    ++ str;
                }
            }

            /* get character */
            c = (rt_uint8_t)va_arg(args, int);
            if (str < end)
            {
                *str = c;
            }
            ++ str;

            /* put width */
            while (--field_width > 0)
            {
                if (str < end) *str = ' ';
                ++ str;
            }
            continue;

        case 's':
            s = va_arg(args, char *);
            if (!s)
            {
                s = "(NULL)";
            }

            for (len = 0; (len != field_width) && (s[len] != '\0'); len++);

            if (precision > 0 && len > precision)
            {
                len = precision;
            }

            if (!(flags & LEFT))
            {
                while (len < field_width--)
                {
                    if (str < end) *str = ' ';
                    ++ str;
                }
            }

            for (i = 0; i < len; ++i)
            {
                if (str < end) *str = *s;
                ++ str;
                ++ s;
            }

            while (len < field_width--)
            {
                if (str < end) *str = ' ';
                ++ str;
            }
            continue;

        case 'p':
            if (field_width == -1)
            {
                field_width = sizeof(void *) << 1;
                field_width += 2; /* `0x` prefix */
                flags |= SPECIAL;
                flags |= ZEROPAD;
            }
            str = print_number(str, end, (unsigned long)va_arg(args, void *),
                               16, qualifier, field_width, precision, flags);
            continue;

        case '%':
            if (str < end)
            {
                *str = '%';
            }
            ++ str;
            continue;

        /* integer number formats - set up the flags and "break" */
        case 'b':
            base = 2;
            break;
        case 'o':
            base = 8;
            break;

        case 'X':
            flags |= LARGE;
        case 'x':
            base = 16;
            break;

        case 'd':
        case 'i':
            flags |= SIGN;
        case 'u':
            break;

        case 'e':
        case 'E':
        case 'G':
        case 'g':
        case 'f':
        case 'F':
            va_arg(args, double);
        default:
            if (str < end)
            {
                *str = '%';
            }
            ++ str;

            if (*fmt)
            {
                if (str < end)
                {
                    *str = *fmt;
                }
                ++ str;
            }
            else
            {
                -- fmt;
            }
            continue;
        }

        if (qualifier == 'L')
        {
            num = va_arg(args, unsigned long long);
        }
        else if (qualifier == 'l')
        {
            num = va_arg(args, unsigned long);
        }
        else if (qualifier == 'H')
        {
            num = (rt_int8_t)va_arg(args, rt_int32_t);
            if (flags & SIGN)
            {
                num = (rt_int8_t)num;
            }
        }
        else if (qualifier == 'h')
        {
            num = (rt_uint16_t)va_arg(args, rt_int32_t);
            if (flags & SIGN)
            {
                num = (rt_int16_t)num;
            }
        }
        else if (qualifier == 'z')
        {
            num = va_arg(args, rt_size_t);
            if (flags & SIGN)
            {
                num = (rt_ssize_t)num;
            }
        }
        else
        {
            num = (rt_uint32_t)va_arg(args, unsigned long);
        }
        str = print_number(str, end, num, base, qualifier, field_width, precision, flags);
    }

    if (size > 0)
    {
        if (str < end)
        {
            *str = '\0';
        }
        else
        {
            end[-1] = '\0';
        }
    }

    /* the trailing null byte doesn't count towards the total
    * ++str;
    */
    return str - buf;
}
RTM_EXPORT(rt_vsnprintf);
#if defined(__GNUC__) && !defined(__ARMCC_VERSION) /* GCC */
#pragma GCC diagnostic pop /* ignored "-Wimplicit-fallthrough" */
#endif /* defined(__GNUC__) && !defined(__ARMCC_VERSION) */

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
