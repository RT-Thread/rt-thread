/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-27     xqyjlj       add uname
 */

#ifndef __SYS_UTSNAME_H__
#define __SYS_UTSNAME_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RT_USING_MUSLLIBC
/* this is required for musl <sys/utsname.h> */
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#include_next <sys/utsname.h>
/* limiting influence of _POSIX_SOURCE */
#undef _POSIX_SOURCE

#else /* def _POSIX_SOURCE */
#include_next <sys/utsname.h>
#endif
#else

struct utsname
{
    char sysname[65];
    char nodename[65];
    char release[65];
    char version[65];
    char machine[65];
    char domainname[65];
};

int uname(struct utsname *);

#endif

#ifdef __cplusplus
}
#endif

#endif
