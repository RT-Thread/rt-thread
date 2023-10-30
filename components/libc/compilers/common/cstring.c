/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-01-12     Meco Man     The first version.
 */

#include "posix/string.h"
#include <ctype.h>
#include <rtthread.h>
#include <stdlib.h>

/**
 * @brief Erases the data in the n bytes of the memory starting at the
 *        location pointed to by s, by writing zeros (bytes containing '\0') to that area.
 *
 * @note  The bzero() function is deprecated (marked as LEGACY in POSIX. 1-2001).
 *
 * @param    s is a pointer to the memory area to be cleared.
 * @param    n is the number of bytes to clear.
 */
#ifndef RT_USING_PICOLIBC
void bzero(void *s, size_t n)
{
    rt_memset(s, 0, n);
}
#endif

/**
 * @brief Copies data from a source memory area to a destination memory area.
 *
 * @param    src is a pointer to the source memory area.
 * @param    dest is a pointer to the destination memory area.
 * @param    n is the number of bytes to copy.
 */
void bcopy(const void *src, void *dest, size_t n)
{
    rt_memcpy(dest, src, n);
}

/**
 * @brief Compares two memory areas.
 *
 * @param    s1 is a pointer to the first memory area.
 * @param    s2 is a pointer to the second memory area.
 * @param    n is the number of bytes to compare.
 *
 * @return   0 if both memory areas are equal, non-zero otherwise.
 */
int bcmp(const void *s1, const void *s2, size_t n)
{
    return rt_memcmp(s1, s2, n);
}

/**
 * @brief Clears the data in the memory area by overwriting it with zeros.
 *
 * @param    s is a pointer to the memory area to be cleared.
 * @param    n is the number of bytes to clear.
 */
void explicit_bzero(void *s, size_t n)
{
    volatile char *vs = (volatile char *)s;
    while (n)
    {
        *vs++ = 0;
        n--;
    }
}

/**
 * @brief Locates the first occurrence of a character in a string.
 *
 * @param    s is a pointer to the string.
 * @param    c is the character to be found.
 *
 * @return   A pointer to the first occurrence of the character in the string, or NULL if not found.
 */
char *index(const char *s, int c)
{
    return strchr(s, c);
}

/**
 * @brief Locates the last occurrence of a character in a string.
 *
 * @param    s is a pointer to the string.
 * @param    c is the character to be found.
 *
 * @return   A pointer to the last occurrence of the character in the string, or NULL if not found.
 */
char *rindex(const char *s, int c)
{
    return strrchr(s, c);
}

/**
 * @brief Finds the position of the first set bit in an integer.
 *
 * @param    i is the integer to search for the first set bit.
 *
 * @return   The position (1-based) of the first set bit, or 0 if no bits are set.
 */
int ffs(int i)
{
    int bit;

    if (0 == i)
        return 0;

    for (bit = 1; !(i & 1); ++bit)
        i >>= 1;
    return bit;
}

/**
 * @brief Finds the position of the first set bit in a long integer.
 *
 * @param    i is the long integer to search for the first set bit.
 *
 * @return   The position (1-based) of the first set bit, or 0 if no bits are set.
 */
int ffsl(long i)
{
    int bit;

    if (0 == i)
        return 0;

    for (bit = 1; !(i & 1); ++bit)
        i >>= 1;
    return bit;
}

/**
 * @brief Finds the position of the first set bit in a long long integer.
 *
 * @param    i is the long long integer to search for the first set bit.
 *
 * @return   The position (1-based) of the first set bit, or 0 if no bits are set.
 */
int ffsll(long long i)
{
    int bit;

    if (0 == i)
        return 0;

    for (bit = 1; !(i & 1); ++bit)
        i >>= 1;
    return bit;
}

/**
 * @brief Searches for the last occurrence of a character in a memory area.
 *
 * @param    ptr is a pointer to the memory area.
 * @param    ch is the character to search for.
 * @param    pos is the maximum position to search within the memory area.
 *
 * @return   A pointer to the last occurrence of the character in the memory area, or NULL if not found.
 */
void *memrchr(const void *ptr, int ch, size_t pos)
{
    char *end = (char *)ptr + pos - 1;
    while (end != ptr)
    {
        if (*end == ch)
            return end;
        end--;
    }
    return (*end == ch) ? (end) : (NULL);
}

/**
 * @brief Calculates the length of a string up to a maximum length.
 *
 * @param    s is a pointer to the string.
 * @param    maxlen is the maximum number of characters to consider.
 *
 * @return   The length of the string, up to a maximum of maxlen.
 */
size_t strnlen(const char *s, size_t maxlen)
{
    const char *sc;
    for (sc = s; maxlen != 0 && *sc != '\0'; maxlen--, ++sc)
        ;
    return sc - s;
}

/**
 * @brief Locates the first occurrence of a character in a string, or returns a pointer
 *        to the null-terminating character if the character is not found.
 *
 * @param    s is a pointer to the string.
 * @param    c is the character to be found.
 *
 * @return   A pointer to the first occurrence of the character in the string, or a pointer
 *           to the null-terminating character if the character is not found.
 */
char *strchrnul(const char *s, int c)
{
    while (*s != '\0' && *s != c)
        s++;
    return (char *)s;
}

/**
 * @brief Compares two strings, ignoring case.
 *
 * @param    s1 is a pointer to the first string.
 * @param    s2 is a pointer to the second string.
 *
 * @return   An integer less than, equal to, or greater than 0 if s1 is found to be less than,
 *           equal to, or greater than s2, respectively, ignoring case.
 */
int strcasecmp(const char *s1, const char *s2)
{
    const unsigned char *u1 = (const unsigned char *)s1;
    const unsigned char *u2 = (const unsigned char *)s2;
    int result;

    while ((result = tolower(*u1) - tolower(*u2)) == 0 && *u1 != 0)
    {
        u1++;
        u2++;
    }

    return result;
}

/**
 * @brief Compares two strings, ignoring case, up to a specified maximum number of characters.
 *
 * @param    s1 is a pointer to the first string.
 * @param    s2 is a pointer to the second string.
 * @param    n is the maximum number of characters to compare.
 *
 * @return   An integer less than, equal to, or greater than 0 if the first n characters of s1
 *           is found to be less than, equal to, or greater than the first n characters of s2,
 *           respectively, ignoring case.
 */
int strncasecmp(const char *s1, const char *s2, size_t n)
{
    const unsigned char *u1 = (const unsigned char *)s1;
    const unsigned char *u2 = (const unsigned char *)s2;
    int result;

    for (; n != 0; n--)
    {
        result = tolower(*u1) - tolower(*u2);
        if (result)
            return result;
        if (*u1 == 0)
            return 0;
        u1++;
        u2++;
    }
    return 0;
}

/**
 * @brief Duplicates a string in a new memory area.
 *
 * @param    s is a pointer to the string to be duplicated.
 *
 * @return   A pointer to the duplicated string in a new memory area.
 */
char *strdup(const char *s)
{
    char *news = (char *)malloc(strlen(s) + 1);

    if (news)
    {
        strcpy(news, s);
    }

    return news;
}

/**
 * @brief Duplicates a string up to a specified maximum length in a new memory area.
 *
 * @param    s is a pointer to the string to be duplicated.
 * @param    size is the maximum number of characters to duplicate.
 *
 * @return   A pointer to the duplicated string in a new memory area.
 */
char *strndup(const char *s, size_t size)
{
    size_t nsize = strnlen(s, size);
    char *news = (char *)malloc(nsize + 1);
    if (news)
    {
        rt_memcpy(news, s, nsize);
        news[nsize] = '\0';
    }

    return news;
}

/**
 * @brief A reentrant version of the strtok function for splitting strings.
 *
 * @param    str is a pointer to the string to be split.
 * @param    delim is a pointer to the delimiters to use for splitting.
 * @param    saveptr is a pointer to the save position for reentrancy.
 *
 * @return   A pointer to the next token in the string, or NULL if no more tokens are found.
 */
rt_weak char *strtok_r(char *str, const char *delim, char **saveptr)
{
    char *pbegin;
    char *pend = NULL;

    if (str)
    {
        pbegin = str;
    }
    else if (saveptr && *saveptr)
    {
        pbegin = *saveptr;
    }
    else
    {
        return NULL;
    }

    for (; *pbegin && strchr(delim, *pbegin) != NULL; pbegin++)
        ;

    if (!*pbegin)
    {
        return NULL;
    }

    for (pend = pbegin + 1; *pend && strchr(delim, *pend) == NULL; pend++)
        ;

    if (*pend)
    {
        *pend++ = '\0';
    }

    if (saveptr)
    {
        *saveptr = pend;
    }

    return pbegin;
}
