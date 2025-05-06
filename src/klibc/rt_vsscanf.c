/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author              Notes
 * 2024-11-24     Meco Man            port to klibc
 * 2025-01-04     Meco Man            using Phoenix version
 */

/*
 * Copyright 2017, 2022-2023 Phoenix Systems
 * Author: Adrian Kepka, Gerard Swiderski
 */

#include <rtthread.h>
#include <stdlib.h> /* for strtod */
#include <ctype.h> /* for isspace */
#include <stdarg.h> /* for va_list */

#define FORMAT_NIL_STR     "(nil)"
#define FORMAT_NIL_STR_LEN (sizeof(FORMAT_NIL_STR) - 1)

#define LONG       0x01   /* l: long or double */
#define LONGDOUBLE 0x02   /* L: long double */
#define SHORT      0x04   /* h: short */
#define SUPPRESS   0x08   /* *: suppress assignment */
#define POINTER    0x10   /* p: void * (as hex) */
#define NOSKIP     0x20   /* [ or c: do not skip blanks */
#define LONGLONG   0x400  /* ll: long long (+ deprecated q: quad) */
#define PTRDIFF    0x800  /* t: ptrdiff_t */
#define SHORTSHORT 0x4000 /* hh: char */
#define UNSIGNED   0x8000 /* %[oupxX] conversions */

#define SIGNOK     0x40  /* +/- is (still) legal */
#define NDIGITS    0x80  /* no digits detected */
#define PFXOK      0x100 /* 0x prefix is (still) legal */
#define NZDIGITS   0x200 /* no zero digits detected */

#define CT_CHAR    0 /* %c conversion */
#define CT_CCL     1 /* %[...] conversion */
#define CT_STRING  2 /* %s conversion */
#define CT_INT     3 /* %[dioupxX] conversion */
#define CT_FLOAT   4 /* %[aefgAEFG] conversion */
#define CT_NONE    5 /* No conversion (ex. %n) */

static const unsigned char *__sccl(char *tab, const unsigned char *fmt)
{
    int c, n, v;

    c = *fmt++;
    if (c == '^') {
        v = 1;
        c = *fmt++;
    }
    else {
        v = 0;
    }

    rt_memset(tab, (uint8_t)v, 256);

    if (c == 0) {
        return (fmt - 1);
    }

    v = 1 - v;
    tab[c] = v;
    for (;;) {
        n = *fmt++;
        switch (n) {

            case 0:
                return (fmt - 1);

            case '-':
                n = *fmt;
                if ((n == ']') || (n < c)) {
                    c = '-';
                    tab[c] = v;
                    break;
                }
                fmt++;

                do {
                    tab[++c] = v;
                } while (c < n);
                c = n;
                break;

            case ']':
                return (fmt);

            default:
                c = n;
                tab[c] = v;
                break;
        }
    }
}

static int scanf_parse(char *ccltab, const char *inp, int *inr, char const *fmt0, va_list ap)
{
    const unsigned char *fmt = (const unsigned char *)fmt0;
    int c, n, flags, nassigned, nconversions, nread, base;
    rt_size_t width;
    char *p, *p0;
    char buf[32];

    static const short basefix[17] = { 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

    *inr = rt_strlen(inp);

    nassigned = 0;
    nconversions = 0;
    nread = 0;
    base = 0;
    for (;;) {
        int convType = CT_NONE;
        c = *fmt++;
        if (c == '\0') {
            return (nassigned);
        }

        if (isspace(c) != 0) {
            while ((*inr > 0) && (isspace((int)*inp) != 0)) {
                nread++;
                (*inr)--;
                inp++;
            }
            continue;
        }

        if (c != '%') {
            if (*inr <= 0) {
                return (nconversions != 0 ? nassigned : -1);
            }

            if (*inp != c) {
                return nassigned;
            }

            nread++;
            (*inr)--;
            inp++;
            continue;
        }

        width = 0;
        flags = 0;
        for (;;) {
            c = *fmt++;
            if (c == '\0') {
                return nassigned;
            }

            if (c == '%') {
                if (*inr <= 0) {
                    return (nconversions != 0 ? nassigned : -1);
                }

                if (*inp != c) {
                    return nassigned;
                }

                nread++;
                (*inr)--;
                inp++;
                break;
            }

            switch (c) {
                case '*':
                    flags |= SUPPRESS;
                    continue;

                case 'l':
                    if ((flags & LONG) != 0) {
                        flags &= ~LONG;
                        flags |= LONGLONG;
                    }
                    else {
                        flags |= LONG;
                    }
                    continue;

                case 'L':
                    flags |= LONGDOUBLE;
                    continue;

                case 'q':
                case 'j':
                    flags |= LONGLONG;
                    continue;

                case 't':
                    flags |= PTRDIFF;
                    continue;

                case 'z':
                    if (sizeof(rt_size_t) == sizeof(uint64_t)) {
                        flags |= LONGLONG;
                    }
                    continue;

                case 'h':
                    if ((flags & SHORT) != 0) {
                        flags &= ~SHORT;
                        flags |= SHORTSHORT;
                    }
                    else {
                        flags |= SHORT;
                    }
                    continue;

                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    width = width * 10 + c - '0';
                    continue;
                default:
                    break;
            }

            /* conversions */
            switch (c) {
                case 'd':
                    convType = CT_INT;
                    base = 10;
                    break;

                case 'i':
                    convType = CT_INT;
                    base = 0;
                    break;

                case 'o':
                    convType = CT_INT;
                    flags |= UNSIGNED;
                    base = 8;
                    break;

                case 'u':
                    convType = CT_INT;
                    flags |= UNSIGNED;
                    base = 10;
                    break;

                case 'X':
                case 'x':
                    flags |= PFXOK; /* enable 0x prefixing */
                    convType = CT_INT;
                    flags |= UNSIGNED;
                    base = 16;
                    break;

                case 'A':
                case 'E':
                case 'F':
                case 'G':
                case 'a':
                case 'e':
                case 'f':
                case 'g':
                    convType = CT_FLOAT;
                    break;


                case 's':
                    convType = CT_STRING;
                    break;

                case '[':
                    fmt = __sccl(ccltab, fmt);
                    flags |= NOSKIP;
                    convType = CT_CCL;
                    break;

                case 'c':
                    flags |= NOSKIP;
                    convType = CT_CHAR;
                    break;

                case 'p':
                    flags |= POINTER | PFXOK | UNSIGNED;
                    convType = CT_INT;
                    base = 16;
                    break;

                case 'n':
                    nconversions++;
                    if ((flags & SUPPRESS) != 0) {
                        break;
                    }
                    if ((flags & SHORTSHORT) != 0) {
                        *va_arg(ap, char *) = nread;
                    }
                    else if ((flags & SHORT) != 0) {
                        *va_arg(ap, short *) = nread;
                    }
                    else if ((flags & LONG) != 0) {
                        *va_arg(ap, long *) = nread;
                    }
                    else if ((flags & LONGLONG) != 0) {
                        *va_arg(ap, long long *) = nread;
                    }
                    else if ((flags & PTRDIFF) != 0) {
                        *va_arg(ap, ptrdiff_t *) = nread;
                    }
                    else {
                        *va_arg(ap, int *) = nread;
                    }
                    break;

                default:
                    /* Character not a conversion specifier; end parsing */
                    return nassigned;
            }

            break;
        }

        if (convType == CT_NONE) {
            continue;
        }

        if (*inr <= 0) {
            return (nconversions != 0 ? nassigned : -1);
        }

        if ((flags & NOSKIP) == 0) {
            while (isspace((int)*inp) != 0) {
                nread++;
                if (--(*inr) > 0) {
                    inp++;
                }
                else {
                    return (nconversions != 0 ? nassigned : -1);
                }
            }
        }

        /* do the conversion */
        switch (convType) {
            case CT_CHAR:
                if (width == 0) {
                    width = 1;
                }

                if (*inr <= 0) {
                    return (nconversions != 0 ? nassigned : -1);
                }

                if (width > *inr) {
                    width = *inr;
                }

                if ((flags & SUPPRESS) == 0) {
                    rt_memcpy(va_arg(ap, char *), inp, width);
                    nassigned++;
                }

                *inr -= width;
                inp += width;
                nread += width;
                nconversions++;
                break;

            case CT_CCL:
                if (width == 0) {
                    width = (rt_size_t)~0;
                }
                if ((flags & SUPPRESS) != 0) {
                    n = 0;
                    while (ccltab[(unsigned char)*inp] != 0) {
                        n++;
                        (*inr)--;
                        inp++;
                        if (--width == 0) {
                            break;
                        }
                        if (*inr <= 0) {
                            if (n == 0) {
                                return (nconversions != 0 ? nassigned : -1);
                            }
                            break;
                        }
                    }
                    if (n == 0) {
                        return nassigned;
                    }
                }
                else {
                    p0 = p = va_arg(ap, char *);
                    while (ccltab[(unsigned char)*inp] != 0) {
                        (*inr)--;
                        *p++ = *inp++;
                        if (--width == 0) {
                            break;
                        }
                        if (*inr <= 0) {
                            if (p == p0) {
                                return (nconversions != 0 ? nassigned : -1);
                            }
                            break;
                        }
                    }
                    n = p - p0;
                    if (n == 0) {
                        return nassigned;
                    }
                    *p = 0;
                    nassigned++;
                }
                nread += n;
                nconversions++;
                break;

            case CT_STRING:
                if (width == 0) {
                    width = (rt_size_t)~0;
                }
                if ((flags & SUPPRESS) != 0) {
                    while (isspace((int)*inp) == 0) {
                        nread++;
                        (*inr)--;
                        inp++;
                        if (--width == 0) {
                            break;
                        }
                        if (*inr <= 0) {
                            break;
                        }
                    }
                }
                else {
                    p0 = p = va_arg(ap, char *);
                    while (isspace((int)*inp) == 0) {
                        (*inr)--;
                        *p++ = *inp++;
                        if (--width == 0) {
                            break;
                        }
                        if (*inr <= 0) {
                            break;
                        }
                    }
                    *p = 0;
                    nread += p - p0;
                    nassigned++;
                }
                nconversions++;
                continue;

            case CT_INT:
                if (((flags & POINTER) != 0) && ((*inr) >= FORMAT_NIL_STR_LEN) && (rt_strncmp(FORMAT_NIL_STR, inp, FORMAT_NIL_STR_LEN) == 0)) {
                    *va_arg(ap, void **) = RT_NULL;
                    nassigned++;
                    nconversions++;
                    nread += FORMAT_NIL_STR_LEN;
                    inp += FORMAT_NIL_STR_LEN;
                    (*inr) -= FORMAT_NIL_STR_LEN;
                    break;
                }

                if (--width > (sizeof(buf) - 2)) {
                    width = sizeof(buf) - 2;
                }
                width++;

                if ((flags & SUPPRESS) != 0) {
                    width = ~0;
                }

                flags |= SIGNOK | NDIGITS | NZDIGITS;
                for (p = buf; width; width--) {
                    int ok = 0;
                    c = *inp;
                    switch (c) {
                        case '0':
                            if (base == 0) {
                                base = 8;
                                flags |= PFXOK;
                            }
                            if ((flags & NZDIGITS) != 0) {
                                flags &= ~(SIGNOK | NZDIGITS | NDIGITS);
                            }
                            else {
                                flags &= ~(SIGNOK | PFXOK | NDIGITS);
                            }
                            ok = 1;
                            break;

                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                            base = basefix[base];
                            flags &= ~(SIGNOK | PFXOK | NDIGITS);
                            ok = 1;
                            break;

                        case '8':
                        case '9':
                            base = basefix[base];
                            if (base <= 8) {
                                break; /* not legal here */
                            }
                            flags &= ~(SIGNOK | PFXOK | NDIGITS);
                            ok = 1;
                            break;

                        case 'A':
                        case 'B':
                        case 'C':
                        case 'D':
                        case 'E':
                        case 'F':
                        case 'a':
                        case 'b':
                        case 'c':
                        case 'd':
                        case 'e':
                        case 'f':
                            if (base <= 10) {
                                break;
                            }
                            flags &= ~(SIGNOK | PFXOK | NDIGITS);
                            ok = 1;
                            break;

                        case '+':
                        case '-':
                            if ((flags & SIGNOK) != 0) {
                                flags &= ~SIGNOK;
                                ok = 1;
                            }
                            break;

                        case 'x':
                        case 'X':
                            if (((flags & PFXOK) != 0) && (p == buf + 1)) {
                                base = 16; /* if %i */
                                flags &= ~PFXOK;
                                ok = 1;
                            }
                            break;
                    }
                    if (!ok)
                        break;

                    if ((flags & SUPPRESS) == 0) {
                        *p++ = c;
                    }
                    if (--(*inr) > 0) {
                        inp++;
                    }
                    else {
                        break;
                    }
                }
                if ((flags & NDIGITS) != 0) {
                    return (nconversions != 0 ? nassigned : -1);
                }

                c = ((unsigned char *)p)[-1];
                if ((c == 'x') || (c == 'X')) {
                    --p;
                    inp--;
                    (*inr)++;
                }

                if ((flags & SUPPRESS) == 0) {
                    uint64_t res;

                    *p = 0;
                    if ((flags & UNSIGNED) == 0) {
                        res = strtoll(buf, (char **)RT_NULL, base);
                    }
                    else {
                        res = strtoull(buf, (char **)RT_NULL, base);
                    }
                    if ((flags & POINTER) != 0) {
                        *va_arg(ap, void **) = (void *)(unsigned long)res;
                    }
                    else if ((flags & SHORTSHORT) != 0) {
                        *va_arg(ap, char *) = res;
                    }
                    else if ((flags & SHORT) != 0) {
                        *va_arg(ap, short *) = res;
                    }
                    else if ((flags & LONG) != 0) {
                        *va_arg(ap, long *) = res;
                    }
                    else if ((flags & LONGLONG) != 0) {
                        *va_arg(ap, long long *) = res;
                    }
                    else if ((flags & PTRDIFF) != 0) {
                        *va_arg(ap, ptrdiff_t *) = res;
                    }
                    else {
                        *va_arg(ap, int *) = res;
                    }
                    nassigned++;
                }

                nread += p - buf;
                nconversions++;
                break;

            case CT_FLOAT: {
                union {
                    float f;
                    double d;
                    long double ld;
                } res;

                const char *srcbuf = inp;
                if ((width != 0) && (width < *inr)) {
                    /* TODO: handle larger widths */
                    if (width > (sizeof(buf) - 1)) {
                        return (nconversions != 0 ? nassigned : -1);
                    }

                    rt_memcpy(buf, inp, width);
                    buf[width] = '\0';
                    srcbuf = buf;
                }

                int is_zero;
                if ((flags & LONGDOUBLE) != 0) {
                    res.ld = strtold(srcbuf, &p);
                    is_zero = res.ld == 0;
                }
                else if ((flags & LONG) != 0) {
                    res.d = strtod(srcbuf, &p);
                    is_zero = res.d == 0;
                }
                else {
                    res.f = strtof(srcbuf, &p);
                    is_zero = res.f == 0;
                }

                if (is_zero && (srcbuf == p)) {
                    return (nconversions != 0 ? nassigned : -1);
                }

                int consumed = p - srcbuf;
                *inr -= consumed;
                inp += consumed;
                nread += consumed;
                nconversions++;
                if ((flags & SUPPRESS) == 0) {
                    if ((flags & LONGDOUBLE) != 0) {
                        *va_arg(ap, long double *) = res.ld;
                    }
                    else if ((flags & LONG) != 0) {
                        *va_arg(ap, double *) = res.d;
                    }
                    else {
                        *va_arg(ap, float *) = res.f;
                    }

                    nassigned++;
                }

                break;
            }

            default:
                break;
        }
    }
    /* never reached */
}

int rt_vsscanf(const char *str, const char *format, va_list ap)
{
    int ret, nremain;
    char *ccltab = rt_malloc(256);

    if (ccltab == RT_NULL) {
        return -1;
    }

    ret = scanf_parse(ccltab, str, &nremain, format, ap);
    rt_free(ccltab);

    return ret;
}
