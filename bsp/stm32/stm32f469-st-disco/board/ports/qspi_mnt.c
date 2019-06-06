/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-11     ZYH          first version
 */
#include <rtthread.h>
#if defined(PKG_USING_FAL)
#include <fal.h>
#include <dfs_fs.h>

int mnt_init(void)
{
    fal_init();
#if defined(BSP_MOUNT_QSPI_WITH_LFS)
    fal_mtd_nor_device_create("qspiflash");
    if (dfs_mount("qspiflash", "/", "lfs", 0, 0) == 0)
    {
        rt_kprintf("Mount \"qspiflash\" on \"/\" success\n");
    }
    else
    {
        dfs_mkfs("lfs","qspiflash");
        if (dfs_mount("qspiflash", "/", "lfs", 0, 0) == 0)
        {
            rt_kprintf("Mount \"qspiflash\" on \"/\" success\n");
        }
        else
        {
            rt_kprintf("Mount \"qspiflash\" on \"/\" fail\n");
            return -1;
        }
    }
#endif
    return 0;
}
INIT_ENV_EXPORT(mnt_init);
#endif
