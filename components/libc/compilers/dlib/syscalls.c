/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-13     Meco Man     implement exit() and abort()
 * 2021-02-20     Meco Man     add system()
 */
#include <rtthread.h>

/* for exit() and abort() */
void __exit (int status)
{
    extern void __rt_libc_exit(int status);
    __rt_libc_exit(status);
    while(1);
}

int system(const char * string)
{
    extern int __rt_libc_system(const char *string);
    return __rt_libc_system(string);
}
