/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021/01/21     greedyhao    The first version
 */

#include <rtthread.h>

#if defined (BSP_USING_SDCARD)

#include <dfs_elm.h>
#include <dfs_fs.h>
#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include "drv_gpio.h"

// #define DRV_DEBUG
#define DBG_TAG "app.card"
#include <rtdbg.h>

void sd_mount(void *parameter)
{
    while (1)
    {
        rt_thread_mdelay(500);
        if (rt_device_find("sd0") != RT_NULL)
        {
            if (dfs_mount("sd0", "/", "elm", 0, 0) == RT_EOK)
            {
                LOG_I("sd card mount to '/'");
                break;
            }
            else
            {
                LOG_W("sd card mount to '/' failed!");
            }
        }
    }
}

int ab32_sdcard_mount(void)
{
    rt_thread_t tid;

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
    return RT_EOK;
}
INIT_APP_EXPORT(ab32_sdcard_mount);
#elif defined (RT_USING_DFS_ROMFS)

#include <dfs_fs.h>
#include "dfs_romfs.h"

int ab32_romfs_mount(void)
{
    if (dfs_mount(RT_NULL, "/", "rom", 0, &(romfs_root)) == 0)
    {
        rt_kprintf("ROM file system initializated!\n");
    }
    else
    {
        rt_kprintf("ROM file system initializate failed!\n");
    }

    return 0;
}
INIT_ENV_EXPORT(ab32_romfs_mount);
#endif
