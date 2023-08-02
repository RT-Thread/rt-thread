/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-27     huanghe      first version
 * 2023-07-14   liqiaozhong    add SD file sys mount func
 *
 */
#include <rtthread.h>
#if defined(RT_USING_DFS)
#include <rtdbg.h>

#include <dfs_fs.h>
#include <dfs_file.h>

#define DBG_TAG "app.filesystem"
#define DBG_LVL DBG_INFO

#ifdef BSP_USING_SDCARD_FATFS
#define SD_DEIVCE_NAME "sd"
static int filesystem_mount(void)
{
    while (rt_device_find(SD_DEIVCE_NAME) == RT_NULL)
    {
        rt_thread_mdelay(1);
    }

    if (dfs_mount(SD_DEIVCE_NAME, "/", "elm", 0, 0) == 0)
    {
        LOG_I("file system initialization done!\n");
    }
    else
    {
        LOG_W("[sd] File System on SD initialization failed!");
        LOG_W("[sd] Try to format and re-mount...");
        if (dfs_mkfs("elm", SD_DEIVCE_NAME) == 0)
        {
            if (dfs_mount(SD_DEIVCE_NAME, "/", "elm", 0, 0) == 0)
            {
                LOG_I("[sd] File System on SD initialized!");
            }
        }
        LOG_E("[sd] File System on SD initialization failed!");
        return -1;
    }

    mkdir("/ram", 0x777);

#ifdef RT_USING_DFS_RAMFS
    extern struct dfs_ramfs *dfs_ramfs_create(rt_uint8_t *pool, rt_size_t size);

    rt_uint8_t *pool = RT_NULL;
    rt_size_t size = 8 * 1024 * 1024;

    pool = rt_malloc(size);
    if (pool == RT_NULL)
        LOG_E("Malloc fail!");

    if (dfs_mount(RT_NULL, "/ram", "ram", 0, (const void *)dfs_ramfs_create(pool, size)) == 0)
        LOG_I("RAM file system initializated!");
    else
        LOG_E("RAM file system initializate failed!");
#endif
    return RT_EOK;
}
INIT_ENV_EXPORT(filesystem_mount);

#else
static int filesystem_mount(void)
{
#ifdef RT_USING_DFS_RAMFS
    extern struct dfs_ramfs *dfs_ramfs_create(rt_uint8_t *pool, rt_size_t size);

    rt_uint8_t *pool = RT_NULL;
    rt_size_t size = 8 * 1024 * 1024;

    pool = rt_malloc(size);
    if (pool == RT_NULL)
        LOG_E("Malloc fail!");

    if (dfs_mount(RT_NULL, "/", "ram", 0, (const void *)dfs_ramfs_create(pool, size)) == 0)
        LOG_I("RAM file system initializated!");
    else
        LOG_E("RAM file system initializate failed!");
#endif

    return RT_EOK;
}
INIT_ENV_EXPORT(filesystem_mount);
#endif // #ifdef BSP_USING_SDCARD_FATFS
#endif // #if defined(RT_USING_DFS)