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

int libc_rand(void)
{
    int i1, i2;
    int j1, j2;

    /* The C standard says that "If rand is called before any calls to
     srand have been made, the same sequence shall be generated as
     when srand is first called with a seed value of 1." */
    i1 = rand();
    i2 = rand();
    srand(1);
    j1 = rand();
    j2 = rand();
    if (i1 < 0 || i2 < 0 || j1 < 0 || j2 < 0)
    {
        puts("Test FAILED!");
    }
    if (j1 == i1 && j2 == i2)
    {
        puts("Test succeeded.");
        return 0;
    }
    else
    {
        if (j1 != i1)
            printf("%d != %d\n", j1, i1);
        if (j2 != i2)
            printf("%d != %d\n", j2, i2);
        puts("Test FAILED!");
        return 1;
    }
}
FINSH_FUNCTION_EXPORT(libc_rand, rand test for libc);
