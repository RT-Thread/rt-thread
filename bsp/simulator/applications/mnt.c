/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-04-03     Urey         the first version
 * 2022-06-01     Meco Man     improve the init process
 */
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG     "FileSystem"
#define DBG_LVL     DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>

static int mnt_init(void)
{
#ifdef RT_USING_DFS_WINSHAREDIR
    extern int dfs_win32_init(void);
    extern rt_err_t rt_win_sharedir_init(const char *name);

    dfs_win32_init();
    rt_win_sharedir_init("wshare");

    if (dfs_mount("wshare", "/", "wdir", 0, 0) == 0)
    {
        LOG_I("[wshare] File System on root ('wshare') initialized!");
    }
    else
    {
        LOG_E("[wshare] File System on root ('wshare') initialization failed!");
    }

    if (dfs_mount("sd0", "/sd", "elm", 0, 0) == 0)
#else
    if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
#endif /* RT_USING_DFS_WINSHAREDIR */
    {
        LOG_I("[sd0] File System on SD ('sd0') initialized!");
    }
    else
    {
        LOG_W("[sd0] File System on SD ('sd0') initialization failed!");
        LOG_W("[sd0] Try to format and re-mount...");
        if (dfs_mkfs("elm", "sd0") == 0)
        {
        #ifdef RT_USING_DFS_WINSHAREDIR
            if (dfs_mount("sd0", "/sd", "elm", 0, 0) == 0)
        #else
            if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
        #endif /* RT_USING_DFS_WINSHAREDIR */
            {
                LOG_I("[sd0] File System on SD ('sd0') initialized!");
                return 0;
            }
        }

        LOG_E("[sd0] File System on SD ('sd0') initialization failed!");
    }
    return 0;
}
INIT_ENV_EXPORT(mnt_init);
#endif /* RT_USING_DFS */
