/*
 * File      : clock.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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
