/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022/12/25     flyingcys    first version
 */
#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>
#include "dfs_romfs.h"

#define DBG_TAG "app.filesystem"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

static const struct romfs_dirent _romfs_root[] =
{
#ifdef BSP_USING_ON_CHIP_FLASH
    {ROMFS_DIRENT_DIR, "flash", RT_NULL, 0},
#endif
    {ROMFS_DIRENT_DIR, "sdcard", RT_NULL, 0}
};

const struct romfs_dirent romfs_root =
{
    ROMFS_DIRENT_DIR, "/", (rt_uint8_t *)_romfs_root, sizeof(_romfs_root)  / sizeof(_romfs_root[0])
};

static void sd_mount(void *parameter)
{
    while (1)
    {
        rt_thread_mdelay(500);

        if (rt_device_find("sd0") != RT_NULL)
        {
            if (dfs_mount("sd0", "/sdcard", "elm", 0, 0) == RT_EOK)
            {
                LOG_I("sd card mount to '/sdcard'");
                break;
            }
            else
            {
                LOG_W("sd card mount to '/sdcard' failed! %d\n", rt_get_errno());
            }
        }
    }
}

int mount_init(void)
{
    if(dfs_mount(RT_NULL, "/", "rom", 0, &romfs_root) != 0)
    {
        LOG_E("rom mount to '/' failed!");
    }

#ifdef BSP_USING_ON_CHIP_FLASH_FS
    struct rt_device *flash_dev = RT_NULL;

    /* 使用 filesystem 分区创建块设备，块设备名称为 filesystem */
    flash_dev = fal_blk_device_create("filesystem");
    if(flash_dev == RT_NULL)
    {
        LOG_E("Failed to create device.\n");
        return -RT_ERROR;
    }

    if (dfs_mount("filesystem", "/flash", "lfs", 0, 0) != 0)
    {
        LOG_I("file system initialization failed!\n");
        if(dfs_mkfs("lfs", "filesystem") == 0)
        {
            if (dfs_mount("filesystem", "/flash", "lfs", 0, 0) == 0)
            {
                LOG_I("mount to '/flash' success!");
            }
        }
    }
    else
    {
        LOG_I("mount to '/flash' success!");
    }
#endif

#ifdef BSP_USING_SDH
    rt_thread_t tid;

    tid = rt_thread_create("sd_mount", sd_mount, RT_NULL,
                            2048, RT_THREAD_PRIORITY_MAX - 2, 20);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    else
    {
        LOG_E("create sd_mount thread err!");
    }
#endif

    return RT_EOK;
}
INIT_APP_EXPORT(mount_init);

#endif /* RT_USING_DFS */
