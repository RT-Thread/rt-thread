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
#include <rtdbg.h>
#ifndef RT_USING_SMART
#include <dfs_fs.h>
#include <dfs_file.h>

static int ram_disk_mount(const char *mount_point)
{
    extern struct dfs_ramfs *dfs_ramfs_create(rt_uint8_t *pool, rt_size_t size);

    rt_uint8_t *pool = RT_NULL;
    rt_size_t size = 8 * 1024 * 1024;

    pool = rt_malloc(size);
    if (pool == RT_NULL)
    {
        LOG_E("Malloc fail!");
    }

    if (dfs_mount(RT_NULL, mount_point, "ram", 0, (const void *)dfs_ramfs_create(pool, size)) == 0)
    {
        LOG_I("RAM file system initializated!");
    }
    else
    {
        LOG_E("RAM file system initializate failed!");
    }

    return RT_EOK;
}

static int filesystem_mount(void)
{
    return ram_disk_mount("/"); /* mount ramdisk as / */
}
INIT_APP_EXPORT(filesystem_mount);
#endif