/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 */
#include <rtthread.h>

#define DBG_LEVEL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_DFS
#include <dfs.h>

int flopyy_system_init(void)
{
    extern int rt_floppy_init(void);
    return rt_floppy_init();
}
INIT_ENV_EXPORT(flopyy_system_init);

#if defined(RT_USING_DFS_ROMFS)
#include <dfs_fs.h>
#include <dfs_romfs.h>

int mnt_init(void)
{
    if (dfs_mount(RT_NULL, "/", "rom", 0, &(romfs_root)) == 0)
    {
        LOG_I("root filesystem mounted.");
    }

    return 0;
}
INIT_APP_EXPORT(mnt_init);
#endif /* end of RT_USING_DFS_ROMFS */
#endif /* end of RT_USING_DFS */
