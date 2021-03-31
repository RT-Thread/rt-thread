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

int speed()
{
    int i;
    time_t t;

    printf("%d\n", time(0));
    for (i = 0; i < 10000000; ++i)
        t = time(0);

    printf("%d\n", time(0));
    return 0;
}
FINSH_FUNCTION_EXPORT(speed, speed test);
