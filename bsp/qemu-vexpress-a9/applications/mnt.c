/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/12/31     Bernard      Add license info
 */

#include <rtthread.h>

#define DBG_TAG     "FileSystem"
#define DBG_LVL     DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>

int mnt_init(void)
{
    rt_thread_delay(RT_TICK_PER_SECOND);

    if (dfs_mount("sd", "/", "elm", 0, 0) == 0)
    {
        LOG_I("file system initialization done!\n");
        return 0;
    }
    else
    {
        LOG_W("[sd] File System on SD ('sd') initialization failed!");
        LOG_W("[sd] Try to format and re-mount...");
        if (dfs_mkfs("elm", "sd") == 0)
        {
            if (dfs_mount("sd", "/", "elm", 0, 0) == 0)
            {
                LOG_I("[sd] File System on SD ('sd') initialized!");
                return 0;
            }
        }

        LOG_E("[sd] File System on SD ('sd') initialization failed!");
        return -1;
    }

}
INIT_ENV_EXPORT(mnt_init);
#endif
