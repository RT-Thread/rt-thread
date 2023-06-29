/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-16     Bernard      the first version
 * 2006-05-25     Bernard      rewrite vsprintf
 * 2006-08-10     Bernard      add rt_show_version
 * 2010-03-17     Bernard      remove rt_strlcpy function
 *                             fix gcc compiling issue.
 * 2010-04-15     Bernard      remove weak definition on ICCM16C compiler
 * 2012-07-18     Arda         add the alignment display for signed integer
 * 2012-11-23     Bernard      fix IAR compiler error.
 * 2012-12-22     Bernard      fix rt_kprintf issue, which found by Grissiom.
 * 2013-06-24     Bernard      remove rt_kprintf if RT_USING_CONSOLE is not defined.
 * 2013-09-24     aozima       make sure the device is in STREAM mode when used by rt_kprintf.
 * 2015-07-06     Bernard      Add rt_assert_handler routine.
 * 2021-02-28     Meco Man     add RT_KSERVICE_USING_STDLIB
 * 2021-12-20     Meco Man     implement rt_strcpy()
 * 2022-01-07     Gabriel      add __on_rt_assert_hook
 * 2022-06-04     Meco Man     remove strnlen
 * 2022-08-24     Yunjie       make rt_memset word-independent to adapt to ti c28x (16bit word)
 * 2022-08-30     Yunjie       make rt_vsnprintf adapt to ti c28x (16bit int)
 * 2023-02-02     Bernard      add Smart ID for logo version show
 */

#include <rtthread.h>
#include <rthw.h>

#define DBG_TAG           "kernel.device"
#ifdef RT_DEBUG_DEVICE
#define DBG_LVL           DBG_LOG
#else
#define DBG_LVL           DBG_WARNING
#endif /* defined (RT_DEBUG_DEVICE) */
#include <rtdbg.h>

#ifdef RT_USING_MODULE
#include <dlmodule.h>
#endif /* RT_USING_MODULE */

#ifdef RT_USING_SMART
#include <lwp.h>
#include <lwp_user_mm.h>
#include <console.h>
#endif

/* use precision */
#define RT_PRINTF_PRECISION
#define RT_PRINTF_SPECIAL

/**
 * @addtogroup KernelService
 * @{
 */

/* global errno in RT-Thread */
static volatile int __rt_errno;

#if defined(RT_USING_DEVICE) && defined(RT_USING_CONSOLE)
static rt_device_t _console_device = RT_NULL;
#endif

rt_weak void rt_hw_us_delay(rt_uint32_t us)
{
    (void) us;
    LOG_D("rt_hw_us_delay() doesn't support for this board."
        "Please consider implementing rt_hw_us_delay() in another file.");
}

rt_weak const char *rt_hw_cpu_arch(void)
{
    return "unknown";
}

static const char* rt_errno_strs[] =
{
    "OK",
    "ERROR",
    "ETIMOUT",
    "ERSFULL",
    "ERSEPTY",
    "ENOMEM",
    "ENOSYS",
    "EBUSY",
    "EIO",
    "EINTRPT",
    "EINVAL",
    "EUNKNOW"
};

/**
 * @brief This function return a pointer to a string that contains the
 * message of error.
 *
 * @param error the errorno code
 * @return a point to error message string
 */
const char *rt_strerror(rt_err_t error)
{
    if (error < 0)
        error = -error;

    return (error > RT_EINVAL + 1) ?
           rt_errno_strs[RT_EINVAL + 1] :
           rt_errno_strs[error];
}
RTM_EXPORT(rt_strerror);

/**
 * @brief This function gets the global errno for the current thread.
 *
 * @return errno
 */
rt_err_t rt_get_errno(void)
{
    rt_thread_t tid = RT_NULL;

    if (rt_interrupt_get_nest() != 0)
    {
        /* it's in interrupt context */
        return __rt_errno;
    }

    tid = rt_thread_self();
    if (tid == RT_NULL)
    {
        return __rt_errno;
    }

    return tid->error;
}
RTM_EXPORT(rt_get_errno);

/**
 * @brief This function sets the global errno for the current thread.
 *
 * @param error is the errno shall be set.
 */
void rt_set_errno(rt_err_t error)
{
    rt_thread_t tid = RT_NULL;

    if (rt_interrupt_get_nest() != 0)
    {
        /* it's in interrupt context */
        __rt_errno = error;

        return;
    }

    tid = rt_thread_self();
    if (tid == RT_NULL)
    {
        __rt_errno = error;

        return;
    }

    tid->error = error;
}
RTM_EXPORT(rt_set_errno);

/**
 * @brief This function returns the address of the current thread errno.
 *
 * @return The errno address.
 */
int *_rt_errno(void)
{
    rt_thread_t tid = RT_NULL;

    if (rt_interrupt_get_nest() != 0)
    {
        return (int *)&__rt_errno;
    }

    tid = rt_thread_self();
    if (tid != RT_NULL)
    {
        return (int *) & (tid->error);
    }

    return (int *)&__rt_errno;
}
RTM_EXPORT(_rt_errno);

#ifndef RT_KSERVICE_USING_STDLIB_MEMORY
/**
 * @brief  This function will set the content of memory to specified value.
 *
 * @param  s is the address of source memory, point to the memory block to be filled.
 *
 * @param  c is the value to be set. The value is passed in int form, but the function
 *         uses the unsigned character form of the value when filling the memory block.
 *
 * @param  count number of bytes to be set.
 *
 * @return The address of source memory.
 */
rt_weak void *rt_memset(void *s, int c, rt_ubase_t count)
{
#ifdef RT_KSERVICE_USING_TINY_SIZE
    char *xs = (char *)s;

    while (count--)
        *xs++ = c;

    return s;
#else
#define LBLOCKSIZE      (sizeof(rt_ubase_t))
#define UNALIGNED(X)    ((long)X & (LBLOCKSIZE - 1))
#define TOO_SMALL(LEN)  ((LEN) < LBLOCKSIZE)

    unsigned int i = 0;
    char *m = (char *)s;
    unsigned long buffer = 0;
    unsigned long *aligned_addr = RT_NULL;
    unsigned char d = (unsigned int)c & (unsigned char)(-1);  /* To avoid sign extension, copy C to an
                                unsigned variable. (unsigned)((char)(-1))=0xFF for 8bit and =0xFFFF for 16bit: word independent */

    RT_ASSERT(LBLOCKSIZE == 2 || LBLOCKSIZE == 4 || LBLOCKSIZE == 8);

    if (!TOO_SMALL(count) && !UNALIGNED(s))
    {
        /* If we get this far, we know that count is large and s is word-aligned. */
        aligned_addr = (unsigned long *)s;

        /* Store d into each char sized location in buffer so that
         * we can set large blocks quickly.
         */
        for (i = 0; i < LBLOCKSIZE; i++)
        {
            *(((unsigned char *)&buffer)+i) = d;
        }

        while (count >= LBLOCKSIZE * 4)
        {
            *aligned_addr++ = buffer;
            *aligned_addr++ = buffer;
            *aligned_addr++ = buffer;
            *aligned_addr++ = buffer;
            count -= 4 * LBLOCKSIZE;
        }

        while (count >= LBLOCKSIZE)
        {
            *aligned_addr++ = buffer;
            count -= LBLOCKSIZE;
        }

        /* Pick up the remainder with a bytewise loop. */
        m = (char *)aligned_addr;
    }

    while (count--)
    {
        *m++ = (char)d;
    }

    return s;

#undef LBLOCKSIZE
#undef UNALIGNED
#undef TOO_SMALL
#endif /* RT_KSERVICE_USING_TINY_SIZE */
}
RTM_EXPORT(rt_memset);

/**
 * @brief  This function will copy memory content from source address to destination address.
 *
 * @param  dst is the address of destination memory, points to the copied content.
 *
 * @param  src  is the address of source memory, pointing to the data source to be copied.
 *
 * @param  count is the copied length.
 *
 * @return The address of destination memory
 */
rt_weak void *rt_memcpy(void *dst, const void *src, rt_ubase_t count)
{
#ifdef RT_KSERVICE_USING_TINY_SIZE
    char *tmp = (char *)dst, *s = (char *)src;
    rt_ubase_t len = 0;

    if (tmp <= s || tmp > (s + count))
    {
        while (count--)
            *tmp ++ = *s ++;
    }
    else
    {
        for (len = count; len > 0; len --)
            tmp[len - 1] = s[len - 1];
    }

    return dst;
#else

#define UNALIGNED(X, Y) \
    (((long)X & (sizeof (long) - 1)) | ((long)Y & (sizeof (long) - 1)))
#define BIGBLOCKSIZE    (sizeof (long) << 2)
#define LITTLEBLOCKSIZE (sizeof (long))
#define TOO_SMALL(LEN)  ((LEN) < BIGBLOCKSIZE)

    char *dst_ptr = (char *)dst;
    char *src_ptr = (char *)src;
    long *aligned_dst = RT_NULL;
    long *aligned_src = RT_NULL;
    rt_ubase_t len = count;

    /* If the size is small, or either SRC or DST is unaligned,
    then punt into the byte copy loop.  This should be rare. */
    if (!TOO_SMALL(len) && !UNALIGNED(src_ptr, dst_ptr))
    {
        aligned_dst = (long *)dst_ptr;
        aligned_src = (long *)src_ptr;

        /* Copy 4X long words at a time if possible. */
        while (len >= BIGBLOCKSIZE)
        {
            *aligned_dst++ = *aligned_src++;
            *aligned_dst++ = *aligned_src++;
            *aligned_dst++ = *aligned_src++;
            *aligned_dst++ = *aligned_src++;
            len -= BIGBLOCKSIZE;
        }

        /* Copy one long word at a time if possible. */
        while (len >= LITTLEBLOCKSIZE)
        {
            *aligned_dst++ = *aligned_src++;
            len -= LITTLEBLOCKSIZE;
        }

        /* Pick up any residual with a byte copier. */
        dst_ptr = (char *)aligned_dst;
        src_ptr = (char *)aligned_src;
    }

    while (len--)
        *dst_ptr++ = *src_ptr++;

    return dst;
#undef UNALIGNED
#undef BIGBLOCKSIZE
#undef LITTLEBLOCKSIZE
#undef TOO_SMALL
#endif /* RT_KSERVICE_USING_TINY_SIZE */
}
RTM_EXPORT(rt_memcpy);

/**
 * @brief  This function will move memory content from source address to destination
 * address. If the destination memory does not overlap with the source memory,
 * the function is the same as memcpy().
 *
 * @param  dest is the address of destination memory, points to the copied content.
 *
 * @param  src is the address of source memory, point to the data source to be copied.
 *
 * @param  n is the copied length.
 *
 * @return The address of destination memory.
 */
void *rt_memmove(void *dest, const void *src, rt_size_t n)
{
    char *tmp = (char *)dest, *s = (char *)src;

    if (s < tmp && tmp < s + n)
    {
        tmp += n;
        s += n;

        while (n--)
            *(--tmp) = *(--s);
    }
    else
    {
        while (n--)
            *tmp++ = *s++;
    }

    return dest;
}
RTM_EXPORT(rt_memmove);

/**
 * @brief  This function will compare two areas of memory.
 *
 * @param  cs is a block of memory.
 *
 * @param  ct is another block of memory.
 *
 * @param  count is the size of the area.
 *
 * @return Compare the results:
 *         If the result < 0, cs is smaller than ct.
 *         If the result > 0, cs is greater than ct.
 *         If the result = 0, cs is equal to ct.
 */
rt_int32_t rt_memcmp(const void *cs, const void *ct, rt_size_t count)
{
    const unsigned char *su1 = RT_NULL, *su2 = RT_NULL;
    int res = 0;

    for (su1 = (const unsigned char *)cs, su2 = (const unsigned char *)ct; 0 < count; ++su1, ++su2, count--)
        if ((res = *su1 - *su2) != 0)
            break;

    return res;
}
RTM_EXPORT(rt_memcmp);
#endif /* RT_KSERVICE_USING_STDLIB_MEMORY*/

#ifndef RT_KSERVICE_USING_STDLIB
/**
 * @brief  This function will return the first occurrence of a string, without the
 * terminator '\0'.
 *
 * @param  s1 is the source string.
 *
 * @param  s2 is the find string.
 *
 * @return The first occurrence of a s2 in s1, or RT_NULL if no found.
 */
char *rt_strstr(const char *s1, const char *s2)
{
    int l1 = 0, l2 = 0;

    l2 = rt_strlen(s2);
    if (!l2)
    {
        return (char *)s1;
    }

    l1 = rt_strlen(s1);
    while (l1 >= l2)
    {
        l1 --;
        if (!rt_memcmp(s1, s2, l2))
        {
            return (char *)s1;
        }

        s1 ++;
    }

    return RT_NULL;
}
RTM_EXPORT(rt_strstr);

/**
 * @brief  This function will compare two strings while ignoring differences in case
 *
 * @param  a is the string to be compared.
 *
 * @param  b is the string to be compared.
 *
 * @return Compare the results:
 *         If the result < 0, a is smaller than a.
 *         If the result > 0, a is greater than a.
 *         If the result = 0, a is equal to a.
 */
rt_int32_t rt_strcasecmp(const char *a, const char *b)
{
    int ca = 0, cb = 0;

    do
    {
        ca = *a++ & 0xff;
        cb = *b++ & 0xff;
        if (ca >= 'A' && ca <= 'Z')
            ca += 'a' - 'A';
        if (cb >= 'A' && cb <= 'Z')
            cb += 'a' - 'A';
    }
    while (ca == cb && ca != '\0');

    return ca - cb;
}
RTM_EXPORT(rt_strcasecmp);

/**
 * @brief  This function will copy string no more than n bytes.
 *
 * @param  dst points to the address used to store the copied content.
 *
 * @param  src is the string to be copied.
 *
 * @param  n is the maximum copied length.
 *
 * @return The address where the copied content is stored.
 */
char *rt_strncpy(char *dst, const char *src, rt_size_t n)
{
    if (n != 0)
    {
        char *d = dst;
        const char *s = src;

        do
        {
            if ((*d++ = *s++) == 0)
            {
                /* NUL pad the remaining n-1 bytes */
                while (--n != 0)
                {
                    *d++ = 0;
                }

                break;
            }
        } while (--n != 0);
    }

    return (dst);
}
RTM_EXPORT(rt_strncpy);

/**
 * @brief  This function will copy string.
 *
 * @param  dst points to the address used to store the copied content.
 *
 * @param  src is the string to be copied.
 *
 * @return The address where the copied content is stored.
 */
char *rt_strcpy(char *dst, const char *src)
{
    char *dest = dst;

    while (*src != '\0')
    {
        *dst = *src;
        dst++;
        src++;
    }

    *dst = '\0';
    return dest;
}
RTM_EXPORT(rt_strcpy);

/**
 * @brief  This function will compare two strings with specified maximum length.
 *
 * @param  cs is the string to be compared.
 *
 * @param  ct is the string to be compared.
 *
 * @param  count is the maximum compare length.
 *
 * @return Compare the results:
 *         If the result < 0, cs is smaller than ct.
 *         If the result > 0, cs is greater than ct.
 *         If the result = 0, cs is equal to ct.
 */
rt_int32_t rt_strncmp(const char *cs, const char *ct, rt_size_t count)
{
    signed char __res = 0;

    while (count)
    {
        if ((__res = *cs - *ct++) != 0 || !*cs++)
        {
            break;
        }

        count --;
    }

    return __res;
}
RTM_EXPORT(rt_strncmp);

/**
 * @brief  This function will compare two strings without specified length.
 *
 * @param  cs is the string to be compared.
 *
 * @param  ct is the string to be compared.
 *
 * @return Compare the results:
 *         If the result < 0, cs is smaller than ct.
 *         If the result > 0, cs is greater than ct.
 *         If the result = 0, cs is equal to ct.
 */
rt_int32_t rt_strcmp(const char *cs, const char *ct)
{
    while (*cs && *cs == *ct)
    {
        cs++;
        ct++;
    }

    return (*cs - *ct);
}
RTM_EXPORT(rt_strcmp);

/**
 * @brief  This function will return the length of a string, which terminate will
 * null character.
 *
 * @param  s is the string
 *
 * @return The length of string.
 */
rt_size_t rt_strlen(const char *s)
{
    const char *sc = RT_NULL;

    for (sc = s; *sc != '\0'; ++sc) /* nothing */
        ;

    return sc - s;
}
RTM_EXPORT(rt_strlen);

#endif /* RT_KSERVICE_USING_STDLIB */

/**
 * @brief  The  strnlen()  function  returns the number of characters in the
 * string pointed to by s, excluding the terminating null byte ('\0'),
 * but at most maxlen.  In doing this, strnlen() looks only at the
 * first maxlen characters in the string pointed to by s and never
 * beyond s+maxlen.
 *
 * @param  s is the string.
 *
 * @param  maxlen is the max size.
 *
 * @return The length of string.
 */
rt_size_t rt_strnlen(const char *s, rt_ubase_t maxlen)
{
    const char *sc;

    for (sc = s; *sc != '\0' && (rt_ubase_t)(sc - s) < maxlen; ++sc) /* nothing */
        ;

    return sc - s;
}
RTM_EXPORT(rt_strnlen);

#ifdef RT_USING_HEAP
/**
 * @brief  This function will duplicate a string.
 *
 * @param  s is the string to be duplicated.
 *
 * @return The string address of the copy.
 */
char *rt_strdup(const char *s)
{
    rt_size_t len = rt_strlen(s) + 1;
    char *tmp = (char *)rt_malloc(len);

    if (!tmp)
    {
        return RT_NULL;
    }

    rt_memcpy(tmp, s, len);

    return tmp;
}
RTM_EXPORT(rt_strdup);
#endif /* RT_USING_HEAP */

/**
 * @brief This function will show the version of rt-thread rtos
 */
void rt_show_version(void)
{
    rt_kprintf("\n \\ | /\n");
#ifdef RT_USING_SMART
    rt_kprintf("- RT -     Thread Smart Operating System\n");
#else
    rt_kprintf("- RT -     Thread Operating System\n");
#endif
    rt_kprintf(" / | \\     %d.%d.%d build %s %s\n",
               (rt_int32_t)RT_VERSION_MAJOR, (rt_int32_t)RT_VERSION_MINOR, (rt_int32_t)RT_VERSION_PATCH, __DATE__, __TIME__);
    rt_kprintf(" 2006 - 2022 Copyright by RT-Thread team\n");
}
RTM_EXPORT(rt_show_version);

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
#ifdef RT_PRINTF_PRECISION
                          int   precision,
#endif /* RT_PRINTF_PRECISION */
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

#ifdef RT_PRINTF_SPECIAL
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
#endif /* RT_PRINTF_SPECIAL */

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

#ifdef RT_PRINTF_PRECISION
    if (i > precision)
    {
        precision = i;
    }
    size -= precision;
#else
    size -= i;
#endif /* RT_PRINTF_PRECISION */

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

#ifdef RT_PRINTF_SPECIAL
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
#endif /* RT_PRINTF_SPECIAL */

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

#ifdef RT_PRINTF_PRECISION
    while (i < precision--)
    {
        if (buf < end)
        {
            *buf = '0';
        }

        ++ buf;
    }
#endif /* RT_PRINTF_PRECISION */

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

#ifdef RT_PRINTF_PRECISION
    int precision = 0;      /* min. # of digits for integers and max for a string */
#endif /* RT_PRINTF_PRECISION */

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
            ++ fmt;
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
            ++ fmt;
            /* it's the next argument */
            field_width = va_arg(args, int);
            if (field_width < 0)
            {
                field_width = -field_width;
                flags |= LEFT;
            }
        }

#ifdef RT_PRINTF_PRECISION
        /* get the precision */
        precision = -1;
        if (*fmt == '.')
        {
            ++ fmt;
            if (_ISDIGIT(*fmt))
            {
                precision = skip_atoi(&fmt);
            }
            else if (*fmt == '*')
            {
                ++ fmt;
                /* it's the next argument */
                precision = va_arg(args, int);
            }
            if (precision < 0)
            {
                precision = 0;
            }
        }
#endif /* RT_PRINTF_PRECISION */
        /* get the conversion qualifier */
        qualifier = 0;
#ifdef RT_KPRINTF_USING_LONGLONG
        if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L')
#else
        if (*fmt == 'h' || *fmt == 'l')
#endif /* RT_KPRINTF_USING_LONGLONG */
        {
            qualifier = *fmt;
            ++ fmt;
#ifdef RT_KPRINTF_USING_LONGLONG
            if (qualifier == 'l' && *fmt == 'l')
            {
                qualifier = 'L';
                ++ fmt;
            }
#endif /* RT_KPRINTF_USING_LONGLONG */
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
#ifdef RT_PRINTF_PRECISION
            if (precision > 0 && len > precision)
            {
                len = precision;
            }
#endif /* RT_PRINTF_PRECISION */

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
#ifdef RT_PRINTF_SPECIAL
                field_width += 2; /* `0x` prefix */
                flags |= SPECIAL;
#endif
                flags |= ZEROPAD;
            }
#ifdef RT_PRINTF_PRECISION
            str = print_number(str, end,
                               (unsigned long)va_arg(args, void *),
                               16, qualifier, field_width, precision, flags);
#else
            str = print_number(str, end,
                               (unsigned long)va_arg(args, void *),
                               16, qualifier, field_width, flags);
#endif
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

#ifdef RT_KPRINTF_USING_LONGLONG
        if (qualifier == 'L')
        {
            num = va_arg(args, unsigned long long);
        }
        else if (qualifier == 'l')
#else
        if (qualifier == 'l')
#endif /* RT_KPRINTF_USING_LONGLONG */
        {
            num = va_arg(args, unsigned long);
        }
        else if (qualifier == 'h')
        {
            num = (rt_uint16_t)va_arg(args, rt_int32_t);
            if (flags & SIGN)
            {
                num = (rt_int16_t)num;
            }
        }
        else
        {
            num = (rt_uint32_t)va_arg(args, unsigned long);
        }
#ifdef RT_PRINTF_PRECISION
        str = print_number(str, end, num, base, qualifier, field_width, precision, flags);
#else
        str = print_number(str, end, num, base, qualifier, field_width, flags);
#endif
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

#ifdef RT_USING_CONSOLE

#ifdef RT_USING_DEVICE
/**
 * @brief  This function returns the device using in console.
 *
 * @return Returns the console device pointer or RT_NULL.
 */
rt_device_t rt_console_get_device(void)
{
    return _console_device;
}
RTM_EXPORT(rt_console_get_device);

/**
 * @brief  This function will set a device as console device.
 * After set a device to console, all output of rt_kprintf will be
 * redirected to this new device.
 *
 * @param  name is the name of new console device.
 *
 * @return the old console device handler on successful, or RT_NULL on failure.
 */
rt_device_t rt_console_set_device(const char *name)
{
#ifdef RT_USING_SMART
    rt_device_t new_iodev = RT_NULL, old_iodev = RT_NULL;

    /* find new console device */
    new_iodev = rt_device_find(name);
    if (new_iodev != RT_NULL)
    {
        if (_console_device != RT_NULL)
        {
            old_iodev = console_set_iodev(new_iodev);
        }
        else
        {
            console_register("console", new_iodev);
            _console_device = rt_device_find("console");
            rt_device_open(_console_device, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_STREAM);
        }
    }

    return old_iodev;
#else
    rt_device_t new_device, old_device;

    /* save old device */
    old_device = _console_device;

    /* find new console device */
    new_device = rt_device_find(name);

    /* check whether it's a same device */
    if (new_device == old_device) return RT_NULL;

    if (new_device != RT_NULL)
    {
        if (_console_device != RT_NULL)
        {
            /* close old console device */
            rt_device_close(_console_device);
        }

        /* set new console device */
        rt_device_open(new_device, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_STREAM);
        _console_device = new_device;
    }

    return old_device;
#endif
}
RTM_EXPORT(rt_console_set_device);
#endif /* RT_USING_DEVICE */

rt_weak void rt_hw_console_output(const char *str)
{
    /* empty console output */
}
RTM_EXPORT(rt_hw_console_output);

/**
 * @brief This function will put string to the console.
 *
 * @param str is the string output to the console.
 */
void rt_kputs(const char *str)
{
    if (!str)
    {
        return;
    }

#ifdef RT_USING_DEVICE
    if (_console_device == RT_NULL)
    {
        rt_hw_console_output(str);
    }
    else
    {
        rt_device_write(_console_device, 0, str, rt_strlen(str));
    }
#else
    rt_hw_console_output(str);
#endif /* RT_USING_DEVICE */
}

/**
 * @brief This function will print a formatted string on system console.
 *
 * @param fmt is the format parameters.
 *
 * @return The number of characters actually written to buffer.
 */
rt_weak int rt_kprintf(const char *fmt, ...)
{
    va_list args;
    rt_size_t length = 0;
    static char rt_log_buf[RT_CONSOLEBUF_SIZE];

    va_start(args, fmt);
    /* the return value of vsnprintf is the number of bytes that would be
     * written to buffer had if the size of the buffer been sufficiently
     * large excluding the terminating null byte. If the output string
     * would be larger than the rt_log_buf, we have to adjust the output
     * length. */
    length = rt_vsnprintf(rt_log_buf, sizeof(rt_log_buf) - 1, fmt, args);
    if (length > RT_CONSOLEBUF_SIZE - 1)
    {
        length = RT_CONSOLEBUF_SIZE - 1;
    }

#ifdef RT_USING_DEVICE
    if (_console_device == RT_NULL)
    {
        rt_hw_console_output(rt_log_buf);
    }
    else
    {
        rt_device_write(_console_device, 0, rt_log_buf, length);
    }
#else
    rt_hw_console_output(rt_log_buf);
#endif /* RT_USING_DEVICE */
    va_end(args);

    return length;
}
RTM_EXPORT(rt_kprintf);
#endif /* RT_USING_CONSOLE */

#if defined(RT_USING_HEAP) && !defined(RT_USING_USERHEAP)
#ifdef RT_USING_HOOK
static void (*rt_malloc_hook)(void *ptr, rt_size_t size);
static void (*rt_free_hook)(void *ptr);

/**
 * @addtogroup Hook
 * @{
 */

/**
 * @brief This function will set a hook function, which will be invoked when a memory
 *        block is allocated from heap memory.
 *
 * @param hook the hook function.
 */
void rt_malloc_sethook(void (*hook)(void *ptr, rt_size_t size))
{
    rt_malloc_hook = hook;
}

/**
 * @brief This function will set a hook function, which will be invoked when a memory
 *        block is released to heap memory.
 *
 * @param hook the hook function
 */
void rt_free_sethook(void (*hook)(void *ptr))
{
    rt_free_hook = hook;
}

/**@}*/

#endif /* RT_USING_HOOK */

#if defined(RT_USING_HEAP_ISR)
#elif defined(RT_USING_MUTEX)
static struct rt_mutex _lock;
#endif

rt_inline void _heap_lock_init(void)
{
#if defined(RT_USING_HEAP_ISR)
#elif defined(RT_USING_MUTEX)
    rt_mutex_init(&_lock, "heap", RT_IPC_FLAG_PRIO);
#endif
}

rt_inline rt_base_t _heap_lock(void)
{
#if defined(RT_USING_HEAP_ISR)
    return rt_hw_interrupt_disable();
#elif defined(RT_USING_MUTEX)
    if (rt_thread_self())
        return rt_mutex_take(&_lock, RT_WAITING_FOREVER);
    else
        return RT_EOK;
#else
    rt_enter_critical();
    return RT_EOK;
#endif
}

rt_inline void _heap_unlock(rt_base_t level)
{
#if defined(RT_USING_HEAP_ISR)
    rt_hw_interrupt_enable(level);
#elif defined(RT_USING_MUTEX)
    RT_ASSERT(level == RT_EOK);
    if (rt_thread_self())
        rt_mutex_release(&_lock);
#else
    rt_exit_critical();
#endif
}

#ifdef RT_USING_UTESTCASES
/* export to utest to observe the inner statements */
#ifdef _MSC_VER
#define rt_heap_lock() _heap_lock()
#define rt_heap_unlock() _heap_unlock()
#else
rt_base_t rt_heap_lock(void) __attribute__((alias("_heap_lock")));
void rt_heap_unlock(rt_base_t level) __attribute__((alias("_heap_unlock")));
#endif /* _MSC_VER */
#endif

#if defined(RT_USING_SMALL_MEM_AS_HEAP)
static rt_smem_t system_heap;
rt_inline void _smem_info(rt_size_t *total,
    rt_size_t *used, rt_size_t *max_used)
{
    if (total)
        *total = system_heap->total;
    if (used)
        *used = system_heap->used;
    if (max_used)
        *max_used = system_heap->max;
}
#define _MEM_INIT(_name, _start, _size) \
    system_heap = rt_smem_init(_name, _start, _size)
#define _MEM_MALLOC(_size)  \
    rt_smem_alloc(system_heap, _size)
#define _MEM_REALLOC(_ptr, _newsize)\
    rt_smem_realloc(system_heap, _ptr, _newsize)
#define _MEM_FREE(_ptr) \
    rt_smem_free(_ptr)
#define _MEM_INFO(_total, _used, _max)  \
    _smem_info(_total, _used, _max)
#elif defined(RT_USING_MEMHEAP_AS_HEAP)
static struct rt_memheap system_heap;
void *_memheap_alloc(struct rt_memheap *heap, rt_size_t size);
void _memheap_free(void *rmem);
void *_memheap_realloc(struct rt_memheap *heap, void *rmem, rt_size_t newsize);
#define _MEM_INIT(_name, _start, _size) \
    rt_memheap_init(&system_heap, _name, _start, _size)
#define _MEM_MALLOC(_size)  \
    _memheap_alloc(&system_heap, _size)
#define _MEM_REALLOC(_ptr, _newsize)    \
    _memheap_realloc(&system_heap, _ptr, _newsize)
#define _MEM_FREE(_ptr)   \
    _memheap_free(_ptr)
#define _MEM_INFO(_total, _used, _max)   \
    rt_memheap_info(&system_heap, _total, _used, _max)
#elif defined(RT_USING_SLAB_AS_HEAP)
static rt_slab_t system_heap;
rt_inline void _slab_info(rt_size_t *total,
    rt_size_t *used, rt_size_t *max_used)
{
    if (total)
        *total = system_heap->total;
    if (used)
        *used = system_heap->used;
    if (max_used)
        *max_used = system_heap->max;
}
#define _MEM_INIT(_name, _start, _size) \
    system_heap = rt_slab_init(_name, _start, _size)
#define _MEM_MALLOC(_size)  \
    rt_slab_alloc(system_heap, _size)
#define _MEM_REALLOC(_ptr, _newsize)    \
    rt_slab_realloc(system_heap, _ptr, _newsize)
#define _MEM_FREE(_ptr) \
    rt_slab_free(system_heap, _ptr)
#define _MEM_INFO       _slab_info
#else
#define _MEM_INIT(...)
#define _MEM_MALLOC(...)     RT_NULL
#define _MEM_REALLOC(...)    RT_NULL
#define _MEM_FREE(...)
#define _MEM_INFO(...)
#endif

/**
 * @brief This function will init system heap.
 *
 * @param begin_addr the beginning address of system page.
 *
 * @param end_addr the end address of system page.
 */
rt_weak void rt_system_heap_init(void *begin_addr, void *end_addr)
{
    rt_ubase_t begin_align = RT_ALIGN((rt_ubase_t)begin_addr, RT_ALIGN_SIZE);
    rt_ubase_t end_align   = RT_ALIGN_DOWN((rt_ubase_t)end_addr, RT_ALIGN_SIZE);

    RT_ASSERT(end_align > begin_align);

    /* Initialize system memory heap */
    _MEM_INIT("heap", begin_addr, end_align - begin_align);
    /* Initialize multi thread contention lock */
    _heap_lock_init();
}

/**
 * @brief Allocate a block of memory with a minimum of 'size' bytes.
 *
 * @param size is the minimum size of the requested block in bytes.
 *
 * @return the pointer to allocated memory or NULL if no free memory was found.
 */
rt_weak void *rt_malloc(rt_size_t size)
{
    rt_base_t level;
    void *ptr;

    /* Enter critical zone */
    level = _heap_lock();
    /* allocate memory block from system heap */
    ptr = _MEM_MALLOC(size);
    /* Exit critical zone */
    _heap_unlock(level);
    /* call 'rt_malloc' hook */
    RT_OBJECT_HOOK_CALL(rt_malloc_hook, (ptr, size));
    return ptr;
}
RTM_EXPORT(rt_malloc);

/**
 * @brief This function will change the size of previously allocated memory block.
 *
 * @param ptr is the pointer to memory allocated by rt_malloc.
 *
 * @param newsize is the required new size.
 *
 * @return the changed memory block address.
 */
rt_weak void *rt_realloc(void *ptr, rt_size_t newsize)
{
    rt_base_t level;
    void *nptr;

    /* Enter critical zone */
    level = _heap_lock();
    /* Change the size of previously allocated memory block */
    nptr = _MEM_REALLOC(ptr, newsize);
    /* Exit critical zone */
    _heap_unlock(level);
    return nptr;
}
RTM_EXPORT(rt_realloc);

/**
 * @brief  This function will contiguously allocate enough space for count objects
 *         that are size bytes of memory each and returns a pointer to the allocated
 *         memory.
 *
 * @note   The allocated memory is filled with bytes of value zero.
 *
 * @param  count is the number of objects to allocate.
 *
 * @param  size is the size of one object to allocate.
 *
 * @return pointer to allocated memory / NULL pointer if there is an error.
 */
rt_weak void *rt_calloc(rt_size_t count, rt_size_t size)
{
    void *p;

    /* allocate 'count' objects of size 'size' */
    p = rt_malloc(count * size);
    /* zero the memory */
    if (p)
    {
        rt_memset(p, 0, count * size);
    }
    return p;
}
RTM_EXPORT(rt_calloc);

/**
 * @brief This function will release the previously allocated memory block by
 *        rt_malloc. The released memory block is taken back to system heap.
 *
 * @param ptr the address of memory which will be released.
 */
rt_weak void rt_free(void *ptr)
{
    rt_base_t level;

    /* call 'rt_free' hook */
    RT_OBJECT_HOOK_CALL(rt_free_hook, (ptr));
    /* NULL check */
    if (ptr == RT_NULL) return;
    /* Enter critical zone */
    level = _heap_lock();
    _MEM_FREE(ptr);
    /* Exit critical zone */
    _heap_unlock(level);
}
RTM_EXPORT(rt_free);

/**
* @brief This function will caculate the total memory, the used memory, and
*        the max used memory.
*
* @param total is a pointer to get the total size of the memory.
*
* @param used is a pointer to get the size of memory used.
*
* @param max_used is a pointer to get the maximum memory used.
*/
rt_weak void rt_memory_info(rt_size_t *total,
                            rt_size_t *used,
                            rt_size_t *max_used)
{
    rt_base_t level;

    /* Enter critical zone */
    level = _heap_lock();
    _MEM_INFO(total, used, max_used);
    /* Exit critical zone */
    _heap_unlock(level);
}
RTM_EXPORT(rt_memory_info);

#if defined(RT_USING_SLAB) && defined(RT_USING_SLAB_AS_HEAP)
void *rt_page_alloc(rt_size_t npages)
{
    rt_base_t level;
    void *ptr;

    /* Enter critical zone */
    level = _heap_lock();
    /* alloc page */
    ptr = rt_slab_page_alloc(system_heap, npages);
    /* Exit critical zone */
    _heap_unlock(level);
    return ptr;
}

void rt_page_free(void *addr, rt_size_t npages)
{
    rt_base_t level;

    /* Enter critical zone */
    level = _heap_lock();
    /* free page */
    rt_slab_page_free(system_heap, addr, npages);
    /* Exit critical zone */
    _heap_unlock(level);
}
#endif

/**
 * @brief  This function allocates a memory block, which address is aligned to the
 * specified alignment size.
 *
 * @param  size is the allocated memory block size.
 *
 * @param  align is the alignment size.
 *
 * @return The memory block address was returned successfully, otherwise it was
 *         returned empty RT_NULL.
 */
rt_weak void *rt_malloc_align(rt_size_t size, rt_size_t align)
{
    void *ptr = RT_NULL;
    void *align_ptr = RT_NULL;
    int uintptr_size = 0;
    rt_size_t align_size = 0;

    /* sizeof pointer */
    uintptr_size = sizeof(void*);
    uintptr_size -= 1;

    /* align the alignment size to uintptr size byte */
    align = ((align + uintptr_size) & ~uintptr_size);

    /* get total aligned size */
    align_size = ((size + uintptr_size) & ~uintptr_size) + align;
    /* allocate memory block from heap */
    ptr = rt_malloc(align_size);
    if (ptr != RT_NULL)
    {
        /* the allocated memory block is aligned */
        if (((rt_ubase_t)ptr & (align - 1)) == 0)
        {
            align_ptr = (void *)((rt_ubase_t)ptr + align);
        }
        else
        {
            align_ptr = (void *)(((rt_ubase_t)ptr + (align - 1)) & ~(align - 1));
        }

        /* set the pointer before alignment pointer to the real pointer */
        *((rt_ubase_t *)((rt_ubase_t)align_ptr - sizeof(void *))) = (rt_ubase_t)ptr;

        ptr = align_ptr;
    }

    return ptr;
}
RTM_EXPORT(rt_malloc_align);

/**
 * @brief This function release the memory block, which is allocated by
 * rt_malloc_align function and address is aligned.
 *
 * @param ptr is the memory block pointer.
 */
rt_weak void rt_free_align(void *ptr)
{
    void *real_ptr = RT_NULL;

    /* NULL check */
    if (ptr == RT_NULL) return;
    real_ptr = (void *) * (rt_ubase_t *)((rt_ubase_t)ptr - sizeof(void *));
    rt_free(real_ptr);
}
RTM_EXPORT(rt_free_align);
#endif /* RT_USING_HEAP */

#ifndef RT_USING_CPU_FFS
#ifdef RT_USING_TINY_FFS
const rt_uint8_t __lowest_bit_bitmap[] =
{
    /*  0 - 7  */  0,  1,  2, 27,  3, 24, 28, 32,
    /*  8 - 15 */  4, 17, 25, 31, 29, 12, 32, 14,
    /* 16 - 23 */  5,  8, 18, 32, 26, 23, 32, 16,
    /* 24 - 31 */ 30, 11, 13,  7, 32, 22, 15, 10,
    /* 32 - 36 */  6, 21,  9, 20, 19
};

/**
 * @brief This function finds the first bit set (beginning with the least significant bit)
 * in value and return the index of that bit.
 *
 * Bits are numbered starting at 1 (the least significant bit).  A return value of
 * zero from any of these functions means that the argument was zero.
 *
 * @param value is the value to find the first bit set in.
 *
 * @return return the index of the first bit set. If value is 0, then this function
 * shall return 0.
 */
int __rt_ffs(int value)
{
    return __lowest_bit_bitmap[(rt_uint32_t)(value & (value - 1) ^ value) % 37];
}
#else
const rt_uint8_t __lowest_bit_bitmap[] =
{
    /* 00 */ 0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 10 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 20 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 30 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 40 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 50 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 60 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 70 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 80 */ 7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 90 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* A0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* B0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* C0 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* D0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* E0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* F0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};

/**
 * @brief This function finds the first bit set (beginning with the least significant bit)
 * in value and return the index of that bit.
 *
 * Bits are numbered starting at 1 (the least significant bit).  A return value of
 * zero from any of these functions means that the argument was zero.
 *
 * @param value is the value to find the first bit set in.
 *
 * @return Return the index of the first bit set. If value is 0, then this function
 *         shall return 0.
 */
int __rt_ffs(int value)
{
    if (value == 0)
    {
        return 0;
    }

    if (value & 0xff)
    {
        return __lowest_bit_bitmap[value & 0xff] + 1;
    }

    if (value & 0xff00)
    {
        return __lowest_bit_bitmap[(value & 0xff00) >> 8] + 9;
    }

    if (value & 0xff0000)
    {
        return __lowest_bit_bitmap[(value & 0xff0000) >> 16] + 17;
    }

    return __lowest_bit_bitmap[(value & 0xff000000) >> 24] + 25;
}
#endif /* RT_USING_TINY_FFS */
#endif /* RT_USING_CPU_FFS */

#ifndef __on_rt_assert_hook
    #define __on_rt_assert_hook(ex, func, line)         __ON_HOOK_ARGS(rt_assert_hook, (ex, func, line))
#endif

#ifdef RT_DEBUG
/* RT_ASSERT(EX)'s hook */

void (*rt_assert_hook)(const char *ex, const char *func, rt_size_t line);

/**
 * This function will set a hook function to RT_ASSERT(EX). It will run when the expression is false.
 *
 * @param hook is the hook function.
 */
void rt_assert_set_hook(void (*hook)(const char *ex, const char *func, rt_size_t line))
{
    rt_assert_hook = hook;
}

/**
 * The RT_ASSERT function.
 *
 * @param ex_string is the assertion condition string.
 *
 * @param func is the function name when assertion.
 *
 * @param line is the file line number when assertion.
 */
void rt_assert_handler(const char *ex_string, const char *func, rt_size_t line)
{
    volatile char dummy = 0;

    if (rt_assert_hook == RT_NULL)
    {
#ifdef RT_USING_MODULE
        if (dlmodule_self())
        {
            /* close assertion module */
            dlmodule_exit(-1);
        }
        else
#endif /*RT_USING_MODULE*/
        {
            rt_kprintf("(%s) assertion failed at function:%s, line number:%d \n", ex_string, func, line);
            while (dummy == 0);
        }
    }
    else
    {
        rt_assert_hook(ex_string, func, line);
    }
}
RTM_EXPORT(rt_assert_handler);
#endif /* RT_DEBUG */

/**@}*/
