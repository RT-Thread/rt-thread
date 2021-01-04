/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-29     bigmagic    first version
 */
#include <rthw.h>
#include <rtthread.h>

#ifdef PKG_USING_LWEXT4

#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_file.h>
#include <ext4.h>
#include <ext4_debug.h>
#include <blk_device.h>
#include <stdint.h>
#include <pci.h>

#define EXT4_DEBUG_ALL  (0xFFFFFFFF)
#define EXT4_DEBUG_NO   (0)

int mount_ssd(void)
{
    struct blk_device *blkdev = (struct blk_device *)rt_device_find("dwc_ahsata_blk");

    if(blkdev == RT_NULL)
    {
        rt_kprintf("dwc_ahsata_blk not found!\n");
        return;
    }
    
    ext4_dmask_set(EXT4_DEBUG_NO);
    blk_device_init(blkdev);
    dfs_mount("dwc_ahsata_blk","/","ext",0,(void *)1);
    dfs_mount("dwc_ahsata_blk","/boot","ext",0,(void *)0);

    return 0;
}

INIT_ENV_EXPORT(mount_ssd);

#endif
