/*
 * File      : mnt_init.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2017, RT-Thread Development Team
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
 * 2017-11-8      Tangyuxin    first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>

int mnt_init(void)
{
    rt_kprintf("init filesystem...\n");
#ifdef RT_USING_MTD_NOR
    //mount rootfs
    if (dfs_mount("rootfs", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("File System on root initialized!\n");
    }
    else
    {
        rt_kprintf("File System on root initialization failed!\n");
    }

    //mount appfs
    if (dfs_mount("appfs", "/appfs", "elm", 0, 0) == 0)
    {
        rt_kprintf("File System on appfs initialized!\n");
    }
    else
    {
        rt_kprintf("File System on appfs initialization failed!\n");
    }
#endif

#if (defined(RT_USING_SDIO) && defined(RT_USING_MSC0))
    rt_thread_delay(RT_TICK_PER_SECOND/5);
    if (dfs_mount("sd0", "/sd", "elm", 0, 0) == 0)
    {
        rt_kprintf("File System on TF initialized!\n");
    }
    else
    {
        rt_kprintf("File System on TF fail!\n");
    }
#endif

    return 0;
}
INIT_ENV_EXPORT(mnt_init);

#endif
