/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2015, RT-Thread Development Team
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
 * 2009-01-05     Bernard      the first version
 */

#include <rtthread.h>
#include <stdio.h>
#include <board.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>
#endif

#include "init.h"

void rt_init_thread_entry(void *parameter)
{
    components_init();

    /* File system Initialization */
#ifdef RT_USING_DFS
    {
#ifdef RT_USING_DFS_WINSHAREDIR
        {
            extern rt_err_t rt_win_sharedir_init(const char *name);
            extern int dfs_win32_init(void);

            rt_win_sharedir_init("wdd");
            dfs_win32_init();

            if (dfs_mount("wdd", "/", "wdir", 0, 0) == 0)
                rt_kprintf("win32 share directory initialized!\n");
            else
                rt_kprintf("win32 share directory initialized failed!\n");
        }
#endif

#ifdef RT_USING_DFS_ELMFAT
        /* mount sd card fatfs as root directory */
#ifdef _WIN32
        if (dfs_mount("sd0", "/disk/sd", "elm", 0, 0) == 0)
#else
        if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
#endif
            rt_kprintf("fatfs initialized!\n");
        else
            rt_kprintf("fatfs initialization failed!\n");
#endif

#ifdef RT_USING_DFS_UFFS
        /* mount uffs as the nand flash file system */
        if (dfs_mount("nand0", "/disk/nand", "uffs", 0, 0) == 0)
            rt_kprintf("uffs initialized!\n");
        else
            rt_kprintf("uffs initialization failed!\n");
#endif

#ifdef RT_USING_DFS_JFFS2
        /* mount jffs2 as the nor flash file system */
        if (dfs_mount("nor", "/disk/nor", "jffs2", 0, 0) == 0)
            rt_kprintf("jffs2 initialized!\n");
        else
            rt_kprintf("jffs2 initialization failed!\n");
#endif

    }
#endif
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
                           rt_init_thread_entry, RT_NULL,
                           2048, RT_THREAD_PRIORITY_MAX / 3, 20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
