/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-13     balanceTWK   add sdcard port file
 * 2021-05-10     Meco Man     fix a bug that cannot use fatfs in the main thread at starting up
 * 2021-07-28     Meco Man     implement romfs as the root filesystem
 */

#include <rtthread.h>

#ifdef BSP_USING_FS
#include <dfs_romfs.h>
#include <dfs_fs.h>
#include <dfs_posix.h>
#include <fal.h>

#define BSP_USING_NOR_MTD_FS

#if DFS_FILESYSTEMS_MAX < 4
#error "Please define DFS_FILESYSTEMS_MAX more than 4"
#endif
#if DFS_FILESYSTEM_TYPES_MAX < 4
#error "Please define DFS_FILESYSTEM_TYPES_MAX more than 4"
#endif

#define DBG_TAG "app.filesystem"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef BSP_USING_SDCARD
static void sd_mount(void *parameter)
{
    while (1)
    {
        rt_thread_mdelay(500);
        if(rt_device_find("sd0") != RT_NULL)
        {
            if (dfs_mount("sd0", "/sdcard", "elm", 0, 0) == RT_EOK)
            {
                LOG_I("sd card mount to '/sdcard'");
                break;
            }
            else
            {
                LOG_W("sd card mount to '/sdcard' failed!");
            }
        }
    }
}

static int onboard_sdcard_mount(void)
{
    rt_thread_t tid;

    if (dfs_mount("sd0", "/sdcard", "elm", 0, 0) == RT_EOK)
    {
        LOG_I("sd card mount to '/sdcard'");
    }
    else
    {
        tid = rt_thread_create("sd_mount", sd_mount, RT_NULL,
                               1024, RT_THREAD_PRIORITY_MAX - 2, 20);
        if (tid != RT_NULL)
        {
            rt_thread_startup(tid);
        }
        else
        {
            LOG_E("create sd_mount thread err!");
        }
    }

    return RT_EOK;
}
#endif

#ifdef BSP_USING_NOR_MTD_FS

#define FS_PARTITION_NAME              "filesystem"

static void mtd_mount(void *parameter)
{
    struct rt_device *mtd_dev = RT_NULL;
    fal_init();
    mtd_dev = fal_mtd_nor_device_create(FS_PARTITION_NAME);
    if (!mtd_dev)
    {
        LOG_E("Can't create a mtd device on '%s' partition.", FS_PARTITION_NAME);
    }
    while (1)
    {
        rt_thread_mdelay(500);
        if(rt_device_find(FS_PARTITION_NAME) != RT_NULL)
        {
            if (dfs_mount(FS_PARTITION_NAME, "/flash", "lfs", 0, 0) == RT_EOK)
            {
                LOG_I("mtd nor flash mount to '/flash'");
                break;
            }
            else
            {
                LOG_W("mtd nor flash mount to '/flash' failed!");
            }
        }
    }
}

static int onboard_mtd_mount(void)
{
    rt_thread_t tid;

    if (dfs_mount(FS_PARTITION_NAME, "/flash", "lfs", 0, 0) == RT_EOK)
    {
        LOG_I("mtd nor flash mount to '/flash'");
    }
    else
    {
        tid = rt_thread_create("mtd_mount", mtd_mount, RT_NULL,
                               1024, RT_THREAD_PRIORITY_MAX - 3, 20);
        if (tid != RT_NULL)
        {
            rt_thread_startup(tid);
        }
        else
        {
            LOG_E("create mtd_mount thread err!");
        }
    }

    return RT_EOK;
}
#endif


static const struct romfs_dirent _romfs_root[] =
{
#ifdef BSP_USING_SDCARD
    {ROMFS_DIRENT_DIR, "sdcard", RT_NULL, 0},
#endif
#ifdef BSP_USING_NOR_MTD_FS
    {ROMFS_DIRENT_DIR, "flash", RT_NULL, 0},
#endif
    
//  {ROMFS_DIRENT_DIR, "flash", RT_NULL, 0},
};

const struct romfs_dirent romfs_root =
{
    ROMFS_DIRENT_DIR, "/", (rt_uint8_t *)_romfs_root, sizeof(_romfs_root) / sizeof(_romfs_root[0])
};

static int filesystem_mount(void)
{
    if (dfs_mount(RT_NULL, "/", "rom", 0, &(romfs_root)) != 0)
    {
        LOG_E("rom mount to '/' failed!");
    }
#ifdef BSP_USING_SDCARD
    onboard_sdcard_mount();
#endif
    
#ifdef BSP_USING_NOR_MTD_FS
    onboard_mtd_mount();
#endif
    
    return RT_EOK;
}
INIT_APP_EXPORT(filesystem_mount);

#endif /* BSP_USING_FS */
