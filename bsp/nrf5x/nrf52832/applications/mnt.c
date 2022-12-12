/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *  on chip filesystem support
 * Change Logs:
 * Date         Author        Notes
 * 2021-06-27   Chenyingchun  first version
 */
#include "board.h"
#include <rtthread.h>
#include <rtdevice.h>

#ifdef BSP_USING_ON_CHIP_FS

#ifndef RT_USING_FAL
#error "if you want to use on chip filesystem, you need to enable FAL package()"
#endif

#ifndef RT_USING_DFS
#error "if you want to use on chip filesystem, you need to enable DFS componment"
#endif

#ifndef BSP_USING_ON_CHIP_FLASH
#error "if you want to use on chip filesystem, you need to enable on-chip flash"
#endif

#ifndef RT_USING_MTD_NOR
#error "if you want to use on chip filesystem, you need to enable mtd nor"
#endif

#ifndef PKG_USING_LITTLEFS
#error "if you want to use on chip filesystem, you need to enable littlefs"
#endif

#include "fal.h"
#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/statfs.h>

#define LOG_TAG "drv.fs"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define FS_PARTITION_NAME ON_CHIP_PARTION_NAME

/**
  * @brief  on chip filesystem init
  * @param  void
  * @retval 0: filesystem init success, -1: filesystem init failed
  */

static int on_chip_fs_init(void)
{
    int result = 0;

    fal_init();

    struct rt_device *flash_dev = fal_mtd_nor_device_create(FS_PARTITION_NAME);

    if (flash_dev == NULL)
    {
        LOG_E("Can't create a block device on '%s' partition.", FS_PARTITION_NAME);
        result = -1;
        goto err;
    }
    else
    {
        LOG_D("Create a block device on the %s partition of flash successful.", FS_PARTITION_NAME);
    }

    if (rt_device_find(FS_PARTITION_NAME) != RT_NULL)
    {
        int mkfs_res = dfs_mkfs("lfs", FS_PARTITION_NAME);

        if (mkfs_res != 0)
        {
            LOG_E("dfs_mkfs error, errno = %d", rt_get_errno());
            result = -1;
            goto err;
        }

        if (dfs_mount(FS_PARTITION_NAME, "/", "lfs", 0, 0) == RT_EOK)
        {
            LOG_D("onchip elm filesystem mount to '/'");
        }
        else
        {
            LOG_E("onchip elm filesystem mount to '/' failed!");
            result = -1;
            goto err;
        }
    }
    else
    {
        LOG_E("find filesystem portion failed");
    }
err:
    return result;
}

INIT_ENV_EXPORT(on_chip_fs_init);

#endif /* BSP_USING_ON_CHIP_FS */
