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

#ifdef RT_USING_DFS
#include <dfs_fs.h>

int mnt_init(void)
{
    fal_init();
#define FS_PARTITION_NAME "flash"
    struct rt_device *mtd_dev;
    mtd_dev = fal_blk_device_create(FS_PARTITION_NAME);
    if (dfs_mount(FS_PARTITION_NAME, "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("Filesystem initialized!");
    }
    else
    {
        dfs_mkfs("elm", FS_PARTITION_NAME);
        if (dfs_mount(FS_PARTITION_NAME, "/", "elm", 0, 0) != 0)
        {
            rt_kprintf("Failed to initialize filesystem!");
        }
    }

    return 0;
}
INIT_ENV_EXPORT(mnt_init);
#endif

