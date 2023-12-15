/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021/08/19     bernard      the first version
 */

#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>

int mnt_init(void)
{
    if (rt_device_find("virtio-blk0"))
    {
        if (dfs_mount("virtio-blk0", "/", "ext", 0, RT_NULL))
        {
            rt_kprintf("ext4 initialization fail!\n");
        }

        mkdir("/dev/shm", 0x777);
        if (dfs_mount(RT_NULL, "/dev/shm", "tmp", 0, 0) != 0)
        {
            rt_kprintf("dir /dev/shm mount failed!\n");
        }
        if (dfs_mount(RT_NULL, "/tmp", "tmp", 0, 0) != 0)
        {
            rt_kprintf("dir /tmp mount failed!\n");
        }
        if (dfs_mount(RT_NULL, "/run", "tmp", 0, 0) != 0)
        {
            rt_kprintf("dir /run mount failed!\n");
        }

        if (rt_device_find("virtio-blk1"))
        {
            if (dfs_mount("virtio-blk1", "/root", "elm", 0, RT_NULL))
            {
                if (dfs_mount("virtio-blk1", "/root", "ext", 0, RT_NULL))
                {
                    rt_kprintf("dir /root mount failed!\\n");
                }
            }
        }
    }

    return 0;
}
INIT_ENV_EXPORT(mnt_init);
#endif
