/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-11     xiangxistu   first version
 */

#include <sys/utsname.h>

static struct utsname default_utsname;

int uname(struct utsname *buf)
{
    rt_memcpy(&default_utsname, buf, sizeof(struct utsname));

    return 0;
}

