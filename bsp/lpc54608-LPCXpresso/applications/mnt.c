/*
 * File      : mnt.c
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
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
 * 2017-08-08     Yang        the first version
 */

#include <rtthread.h>
#include <dfs.h>
#include <dfs_fs.h>

#ifdef RT_USING_DFS_ROMFS
#include <dfs_romfs.h>
#endif

#include "drv_sd.h"

#ifdef RT_USING_DFS_ROMFS
#define SD_ROOT     "/sdcard"
#else
#define SD_ROOT     "/"
#endif

int mnt_init(void)
{
#ifdef RT_USING_DFS_ROMFS
    /* initialize the device filesystem */
    dfs_init();

    dfs_romfs_init();

    /* mount rom file system */
	if (dfs_mount(RT_NULL, "/", "rom", 0, &(romfs_root)) == 0)
    {
        rt_kprintf("ROM file system initializated!\n");
    }
#endif

#ifdef BSP_DRV_SDCARD
    /* initilize sd card */
     mci_hw_init("sd0");
#endif

#ifdef RT_DFS_ELM_REENTRANT    
    /* mount sd card fat partition 1 as root directory */
    if (dfs_mount("sd0", SD_ROOT, "elm", 0, 0) == 0)
        rt_kprintf("File System initialized!\n");
    else
        rt_kprintf("File System init failed!\n");
#endif
    
    return 0;
}
INIT_ENV_EXPORT(mnt_init);
