/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-04-03     Urey         the first version
 */
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>

int mnt_init(void)
{
#ifdef RT_USING_DFS_WINSHAREDIR
    extern int dfs_win32_init(void);
    extern rt_err_t rt_win_sharedir_init(const char *name);

    dfs_win32_init();
    rt_win_sharedir_init("wshare");

    if (dfs_mount("wshare", "/", "wdir", 0, 0) == 0)
    {
        rt_kprintf("File System on root initialized!\n");
    }
    else
    {
        rt_kprintf("File System on root initialization failed!\n");
    }

    if (dfs_mount("sd0", "/sd", "elm", 0, 0) == 0)
    {
        rt_kprintf("File System on sd initialized!\n");
    }
    else
    {
        rt_kprintf("File System on sd initialization failed!\n");
    }
#else
    if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("File System on sd initialized!\n");
    }
    else
    {
        rt_kprintf("File System on sd initialization failed!\n");
    }
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(mnt_init);
#endif
