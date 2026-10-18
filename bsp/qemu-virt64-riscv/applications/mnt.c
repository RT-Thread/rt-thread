/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>

#define DBG_TAG "FileSystem"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>

#ifndef RT_USING_DM
#define ROOTFS_MOUNT_RETRIES     100
#define ROOTFS_MOUNT_RETRY_DELAY 10

static int mnt_rootfs(void)
{
    int retry;

    for (retry = 0; retry < ROOTFS_MOUNT_RETRIES; retry++)
    {
        if (rt_device_find("virtio-blk0") != RT_NULL)
        {
            /* mount virtio-blk as root directory */
            if ((retry == 0 && dfs_mount("virtio-blk0", "/", "elm", 0, RT_NULL) == RT_EOK) ||
                dfs_mount("virtio-blk0", "/", "ext", 0, RT_NULL) == RT_EOK)
            {
                LOG_I("file system initialization done!");
                return RT_EOK;
            }
        }

        rt_thread_mdelay(ROOTFS_MOUNT_RETRY_DELAY);
    }

    LOG_E("file system initialization fail!");
    return -RT_ERROR;
}
#endif

#ifdef RT_USING_DFS_PTYFS
static int mnt_ptyfs(void)
{
    mkdir("/dev/pts", 0755);

    if (dfs_mount(RT_NULL, "/dev/pts", "ptyfs", 0, RT_NULL) != RT_EOK)
    {
        LOG_E("ptyfs mounted on /dev/pts failed!");
        return -RT_ERROR;
    }

    LOG_I("ptyfs mounted on /dev/pts success!");
    return RT_EOK;
}
#endif

#if defined(RT_USING_DFS_PROCFS) && !defined(RT_USING_DM)
static int mnt_procfs(void)
{
    mkdir("/proc", 0755);

    if (dfs_mount(RT_NULL, "/proc", "procfs", 0, RT_NULL) != RT_EOK)
    {
        LOG_E("procfs mounted on /proc failed!");
        return -RT_ERROR;
    }

    LOG_I("procfs mounted on /proc success!");
    return RT_EOK;
}
#endif

int mnt_init(void)
{
#ifndef RT_USING_DM
    (void)mnt_rootfs();
#endif

#ifdef RT_USING_DFS_PTYFS
    (void)mnt_ptyfs();
#endif
#if defined(RT_USING_DFS_PROCFS) && !defined(RT_USING_DM)
    (void)mnt_procfs();
#endif

    return 0;
}
#ifdef RT_USING_DM
/* The driver model mounts rootfs at the environment initialization level. */
INIT_FS_EXPORT(mnt_init);
#else
INIT_ENV_EXPORT(mnt_init);
#endif
#endif
