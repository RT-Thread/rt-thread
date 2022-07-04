/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-07     Meco Man     The first version.
 */

#include "posix/ctype.h"

#if !(defined(__ICCARM__) && (__VER__ > 9000000)) /* IAR9.0 has defined */
#ifndef isascii /* some toolchain use macro to define it */
int isascii(int c)
{
    return c >= 0x00 && c <= 0x7f;
}
#endif
#endif /* !(defined(__ICCARM__) && (__VER__ > 9000000)) */

#ifndef toascii
int toascii(int c)
{
    return (c)&0177;
}
#endif
