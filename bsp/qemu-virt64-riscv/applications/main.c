/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <rthw.h>
#include <string.h>

// int main(void)
// {
//     rt_kprintf("Hello RISC-V\n");

//     return 0;
// }

int main(void)
{
    int count;

    for (count = 0; count < 10; count++)
    {
        rt_kprintf("RISC-V test: %d\n", count);
        rt_thread_mdelay(1000);
    }

    return 0;
}
