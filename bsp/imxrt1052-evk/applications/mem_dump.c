/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-05     Tanek        first version
 */

#include <rtthread.h>

static void mem_dump(uint32_t buffer, uint32_t length)
{
    uint32_t *buf = (uint32_t *)buffer;
    int i;

    for (i = 0; i < length / 4; i++)
    {
        rt_kprintf("0x%08X,", buf[i]);

        if (i % 8 == 7)
        {
            rt_kprintf("\n");
        }
        else
        {
            rt_kprintf(" ");
        }
    }
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(mem_dump, dump memory);
#endif
