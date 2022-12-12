/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-08     supperthomas first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "fal.h"
#include <dfs_fs.h>

#define DBG_TAG    "mnt"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>

int mnt_init(void)
{
#ifdef BSP_USING_ON_CHIP_FLASH
    fal_init();
#define FS_PARTITION_NAME "flash"
    struct rt_device *mtd_dev;
    mtd_dev = fal_blk_device_create(FS_PARTITION_NAME);
    if (!mtd_dev)
    {
        LOG_E("Failed to create device.\n");
    }
#ifdef BSP_USING_ON_CHIP_FLASH_FATFS
    if (dfs_mount(FS_PARTITION_NAME, "/", "elm", 0, 0) == 0)
    {
        LOG_I("Filesystem initialized!");
    }
    else
    {
        dfs_mkfs("elm", FS_PARTITION_NAME);
        if (dfs_mount(FS_PARTITION_NAME, "/", "elm", 0, 0) != 0)
        {
            LOG_I("Failed to initialize filesystem!");
        }
    }
#endif /* BSP_USING_ON_CHIP_FLASH_FATFS */
#endif /* BSP_USING_ON_CHIP_FLASH */
    return 0;
}
INIT_ENV_EXPORT(mnt_init);
#endif /* RT_USING_DFS */
