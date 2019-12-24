/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#if defined(RT_USING_SPI_MSD) && defined(RT_USING_DFS_ELMFAT)
#include <spi_msd.h>
#include <dfs_fs.h>
int mnt_init(void)
{
    msd_init("sd0", "spi10");
    if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("Mount \"/dev/sd0\" on \"/\"\n");
    }
    return 0;
}
INIT_ENV_EXPORT(mnt_init);
#endif

