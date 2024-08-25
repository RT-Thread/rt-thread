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
#include <dfs_fs.h>
#include <dfs_file.h>

#define DBG_TAG "app.filesystem"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static int littlefs_mount(void)
{
    if (rt_device_find("mflash") == RT_NULL)
    {
        LOG_E("mflash device not find!!");
        return -RT_EIO;
    }
    int ret = dfs_mount("mflash", "/", "lfs", 0, 0);
    if (ret != 0)
    {
        LOG_E("mflash mount to '/' failed!");
        ret = dfs_mkfs("lfs", "mflash");
        if (ret != 0)
            return ret;
        ret = dfs_mount("mflash", "/", "lfs", 0, 0);
        if (ret != 0)
            return ret;
    }

    LOG_D("mflash mount to '/' successed");

    return RT_EOK;
}
INIT_APP_EXPORT(littlefs_mount);
