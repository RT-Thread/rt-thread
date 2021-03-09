/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-11-17     Bernard      first version
 */

#include <stdio.h>
#include <stdlib.h>
#include <finsh.h>

int libc_env()
{
    printf("PATH=%s\n", getenv("PATH"));
    putenv("foo=bar");
    printf("foo=%s\n", getenv("foo"));
    return 0;
}
FINSH_FUNCTION_EXPORT(libc_env, get/set_env test);
