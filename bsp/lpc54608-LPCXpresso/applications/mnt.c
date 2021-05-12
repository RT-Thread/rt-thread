/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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
