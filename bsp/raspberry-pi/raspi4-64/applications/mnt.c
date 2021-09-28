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

#ifdef BSP_USING_SDIO0
#include <dfs_fs.h>

int mnt_init(void)
{
    rt_thread_delay(RT_TICK_PER_SECOND);
    if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("file system initialization done!\n");
    }

    return 0;
}
INIT_ENV_EXPORT(mnt_init);
#endif
