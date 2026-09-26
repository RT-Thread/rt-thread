/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-25     seteiro      replace newlib strtoul and ctype locale
 *
 * newlib strtoul, locale and strtod do not fit in 16KB flash / 2KB RAM.
 * kservice's backtrace parser calls strtoul. rt_vsscanf calls the
 * integer and float converters below.
 */

#define _U 01
#define _L 02
#define _N 04
#define _S 010
#define _P 020
#define _C 040
#define _X 0100
#define _B 0200

/* Index 0 is EOF. Character c is stored at index c + 1. */
static const char ctype_table[257] = {
    0,
    _C, _C, _C, _C, _C, _C, _C, _C,
    _C, _C | _S, _C | _S, _C | _S, _C | _S, _C | _S, _C, _C,
    _C, _C, _C, _C, _C, _C, _C, _C,
    _C, _C, _C, _C, _C, _C, _C, _C,
    _S | _B, _P, _P, _P, _P, _P, _P, _P,
    _P, _P, _P, _P, _P, _P, _P, _P,
    _N, _N, _N, _N, _N, _N, _N, _N,
    _N, _N, _P, _P, _P, _P, _P, _P,
    _P, _U | _X, _U | _X, _U | _X, _U | _X, _U | _X, _U | _X, _U,
    _U, _U, _U, _U, _U, _U, _U, _U,
    _U, _U, _U, _U, _U, _U, _U, _U,
    _U, _U, _U, _P, _P, _P, _P, _P,
    _P, _L | _X, _L | _X, _L | _X, _L | _X, _L | _X, _L | _X, _L,
    _L, _L, _L, _L, _L, _L, _L, _L,
    _L, _L, _L, _L, _L, _L, _L, _L,
    _L, _L, _L, _P, _P, _P, _P, _C
};

const char *__locale_ctype_ptr(void)
{
    return ctype_table;
}

void *rt_malloc(unsigned long size);
void rt_free(void *ptr);

void *malloc(unsigned long size)
{
    return rt_malloc(size);
}

void free(void *ptr)
{
    rt_free(ptr);
}

static int digit(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return ch - '0';
    }
    if (ch >= 'a' && ch <= 'z')
    {
        return ch - 'a' + 10;
    }
    if (ch >= 'A' && ch <= 'Z')
    {
        return ch - 'A' + 10;
    }
    return -1;
}

unsigned long strtoul(const char *nptr, char **endptr, int base)
{
    const char *s = nptr;
    unsigned long value = 0;
    int any = 0;
    int d;

    if (s == 0)
    {
        if (endptr)
        {
            *endptr = (char *)nptr;
        }
        return 0;
    }

    while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r')
    {
        s++;
    }

    if ((base == 0 || base == 16) && s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
    {
        base = 16;
        s += 2;
    }
    else if (base == 0)
    {
        base = (*s == '0') ? 8 : 10;
        if (*s == '0')
        {
            s++;
        }
    }

    while ((d = digit(*s)) >= 0 && d < base)
    {
        value = value * (unsigned long)base + (unsigned long)d;
        any = 1;
        s++;
    }

    if (endptr)
    {
        *endptr = (char *)(any ? s : nptr);
    }
    return value;
}

long long strtoll(const char *nptr, char **endptr, int base)
{
    const char *s = nptr;
    int neg = 0;

    if (s == 0)
    {
        if (endptr)
        {
            *endptr = (char *)nptr;
        }
        return 0;
    }
    while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r')
    {
        s++;
    }
    if (*s == '-')
    {
        neg = 1;
        s++;
    }
    else if (*s == '+')
    {
        s++;
    }
    if (neg)
    {
        return -(long long)strtoul(s, endptr, base);
    }
    return (long long)strtoul(s, endptr, base);
}

unsigned long long strtoull(const char *nptr, char **endptr, int base)
{
    return (unsigned long long)strtoul(nptr, endptr, base);
}

double strtod(const char *nptr, char **endptr)
{
    if (endptr)
    {
        *endptr = (char *)nptr;
    }
    return 0;
}

float strtof(const char *nptr, char **endptr)
{
    if (endptr)
    {
        *endptr = (char *)nptr;
    }
    return 0;
}

long double strtold(const char *nptr, char **endptr)
{
    if (endptr)
    {
        *endptr = (char *)nptr;
    }
    return 0;
}
