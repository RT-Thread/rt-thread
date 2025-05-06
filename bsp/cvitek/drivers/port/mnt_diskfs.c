/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>

#define DBG_TAG "app.filesystem"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

static int _wait_device_ready(const char* devname)
{
    int k;

    for(k = 0; k < 10; k++)
    {
        if (rt_device_find(devname) != RT_NULL)
        {
            return 1;
        }
        rt_thread_mdelay(50);
    }

    return 0;
}

static void sd_mount(const char *devname)
{
    if (!_wait_device_ready(devname)) {
        LOG_W("Failed to find device: %s", devname);
        return;
    }

    if (dfs_mount(devname, "/", "ext", 0, 0) == RT_EOK)
    {
        LOG_I("device '%s' is mounted to '/' as EXT", devname);
    }
    else if (dfs_mount(devname, "/", "elm", 0, 0) == RT_EOK)
    {
        LOG_I("device '%s' is mounted to '/' as FAT", devname);
    }
    else
    {
        LOG_W("Failed to mount device '%s' to '/': %d\n", devname, rt_get_errno());
    }
}

int mount_init(void)
{
#ifdef BSP_USING_SDH
    sd_mount("sd1");
#endif

    return RT_EOK;
}
INIT_ENV_EXPORT(mount_init);

#endif /* RT_USING_DFS */
