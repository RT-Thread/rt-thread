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

#define DBG_TAG           "kernel.string"
#ifdef RT_DEBUG_DEVICE
#define DBG_LVL           DBG_LOG
#else
#define DBG_LVL           DBG_WARNING
#endif /* defined (RT_DEBUG_DEVICE) */
#include <rtdbg.h>

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
