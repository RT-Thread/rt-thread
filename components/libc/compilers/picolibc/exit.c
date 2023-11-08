/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <sys/types.h>

/* for exit() and abort() */
rt_noreturn void _exit (int status)
{
    extern void __rt_libc_exit(int status);
    __rt_libc_exit(status);
    while(1);
}
