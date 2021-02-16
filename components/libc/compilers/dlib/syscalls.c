/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-13     Meco Man     implement exit() and abort()
 */
#include <rtthread.h>

void exit (int status)
{
    extern void __exit__(int status);
    __exit__(status);
    while(1);
}

void abort(void)
{
    extern void __abort__(void);
    __abort__();
    while(1);
}
