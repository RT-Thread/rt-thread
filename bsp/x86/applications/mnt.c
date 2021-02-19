/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 */
#include <rtthread.h>

extern int rt_floppy_init(void);

int mnt_init(void)
{
    rt_floppy_init();

    return 0;
}
