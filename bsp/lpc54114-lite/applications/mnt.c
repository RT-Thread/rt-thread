/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>

#if defined(RT_USING_DFS)
#include <dfs_file.h>
#include <dfs_posix.h>
#endif

#define BSP_FLASH_MOUNT_PATH  "/mnt/flash"
#define BSP_SDCARD_MOUNT_PATH "/mnt/sd"

int mnt_init(void)
{
#if defined(BSP_USING_SPIFLASH)
    if(dfs_mount("flash0", BSP_FLASH_MOUNT_PATH, "elm", 0, 0) != 0)
    {
        rt_kprintf("spi flash mount '%s' failed.\n", BSP_FLASH_MOUNT_PATH);
    }
#endif

#if defined(BSP_USING_SDCARD)
    if(dfs_mount("sd0", BSP_SDCARD_MOUNT_PATH, "elm", 0, 0) != 0)
    {
        rt_kprintf("sdcard mount '%s' failed.\n", BSP_SDCARD_MOUNT_PATH);
    }
#endif

    return 0;
}
INIT_APP_EXPORT(mnt_init);
