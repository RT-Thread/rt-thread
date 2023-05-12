/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-04-08     wcx1024979076     first version
 */
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG    "mnt"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>

#ifdef RT_USING_FAL
#include "fal.h"

#ifdef BSP_USING_ON_CHIP_FLASH
int mnt_init(void)
{
    struct rt_device *rootfs = RT_NULL;

    /* 使用 filesystem 分区创建块设备，块设备名称为 filesystem */
    rootfs = fal_blk_device_create("filesystem");
    if(rootfs == RT_NULL)
    {
        LOG_E("Failed to create device.\n");
        return -RT_ERROR;
    }

    /* 将 elm fat 文件系统挂载 filesystem 分区 */
    if (dfs_mount("filesystem", "/", "elm", 0, 0) == 0)
    {
        LOG_D("file system initialization done!\n");
    }
    else
    {
        LOG_I("file system initialization failed!\n");
        if(dfs_mkfs("elm", "filesystem") == 0)
        {
            if (dfs_mount("filesystem", "/", "elm", 0, 0) == 0)
            {
                LOG_D("file system initialization done!\n");
            }
            else
            {
                LOG_D("file system initialization failed!\n");
            }
        }
    }

    return RT_EOK;
}
INIT_ENV_EXPORT(mnt_init);

#endif /* BSP_USING_ON_CHIP_FLASH */

#endif /* RT_USING_FAL */

#endif /* RT_USING_DFS */
