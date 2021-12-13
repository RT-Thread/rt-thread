/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-11     xiangxistu   The first version
 */

#ifndef __SYS_UTSNAME_H__
#define __SYS_UTSNAME_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtthread.h>

struct utsname
{
    char sysname[RT_NAME_MAX];      /* Operating system name (e.g., "Linux", "RT-Thread") */
    char nodename[RT_NAME_MAX];     /* Name within "some implementation-defined network" */
    char release[RT_NAME_MAX];      /* Operating system release (e.g., "2.6.28") */
    char version[RT_NAME_MAX];      /* Operating system version */
    char machine[RT_NAME_MAX];      /* Hardware identifier */
#ifdef _GNU_SOURCE
    char domainname[RT_NAME_MAX]; /* NIS or YP domain name */
#endif
};



int uname(struct utsname *buf);


#ifdef __cplusplus
}
#endif

#endif
