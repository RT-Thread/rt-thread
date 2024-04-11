/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-5-30     bernard       the first version
 */

#include <rtthread.h>

#ifdef BSP_USING_SDIO
#include <dfs_fs.h>

int mnt_init(void)
{
    rt_thread_delay(RT_TICK_PER_SECOND/100);
    if (dfs_mount("sd1", "/", "ext", 0, 0) == 0)
    {
        rt_kprintf("file system initialization done!\n");
    }
    else if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("file system initialization done!\n");
    }

#ifdef RT_USING_DFS_ROMFS
    mkdir("/rom", 0777);
    extern const struct romfs_dirent romfs_root;
    if (dfs_mount(RT_NULL, "/rom", "rom", 0, &romfs_root) == 0)
    {
        rt_kprintf("ROM File System initialized!\n");
    }
#endif

    return 0;
}
INIT_ENV_EXPORT(mnt_init);
#endif
