/*
 * Copyright (c) 2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Kernel-mode musl is linked with native RT-Thread threads, not musl's Linux
 * pthread runtime.  A few musl locale functions reach the Linux pthread
 * locale object through the architecture thread pointer.  Supply the fixed
 * UTF-8/C-locale subset used by kernel applications until a complete musl
 * pthread locale runtime is available.
 */

#include <rtthread.h>

#if defined(RT_USING_MUSLLIBC) && !defined(RT_USING_SMART)

#include <langinfo.h>
#include <stdio.h>
#include <wchar.h>

char *nl_langinfo(nl_item item)
{
    static char empty[] = "";

    if (item == CODESET)
    {
        return (char *)"UTF-8";
    }

    return empty;
}

wint_t btowc(int character)
{
    if (character == EOF)
    {
        return WEOF;
    }

    /* A single UTF-8 byte is a character only in the ASCII range. */
    if ((unsigned int)character > 0x7f)
    {
        return WEOF;
    }

    return (wint_t)character;
}

#endif /* RT_USING_MUSLLIBC && !RT_USING_SMART */
