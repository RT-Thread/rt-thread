/*
 * Copyright (c) 2019-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-02     CoreBoxer    add LittleFS on QSPI NOR Flash (IMXRT1180-EVK)
 */

#include <rtthread.h>

/* ====================================================================
 * QSPI NOR Flash LittleFS (controlled by BSP_USING_QSPI_FLASH_FS)
 *
 * Dependencies:
 *   - drv_flash.c (Flash read/write/erase driver via ROM API)
 *   - FAL framework (partition management)
 *   - LittleFS component (RT-Thread package)
 *
 * FAL partition configuration (fal_cfg.h):
 *   "filesystem" partition → filesystem area of norflash0
 *
 * Mount procedure:
 *   1. Find FAL partition to confirm correct configuration
 *   2. Create MTD NOR block device
 *   3. Try direct mount (for already formatted filesystem)
 *   4. If failed, perform mkfs then remount (first use or format scenario)
 * ==================================================================== */
#ifdef BSP_USING_QSPI_FLASH_FS
#include <dfs_fs.h>
#include <fal.h>

#define FS_PARTITION_NAME  "filesystem"
#define FS_TYPE_NAME       "lfs"
#define FS_MOUNT_POINT     "/"

static int _qspi_flash_fs_mount(void)
{
    struct fal_mtd_nor_device *mtd_dev;
    int ret;

    /* Find FAL partition to confirm configuration is correct */
    if (fal_partition_find(FS_PARTITION_NAME) == RT_NULL)
    {
        rt_kprintf("[qspi_fs] partition '%s' not found, check fal_cfg.h\n",
                   FS_PARTITION_NAME);
        return -RT_ERROR;
    }

    /* Create MTD NOR block device for filesystem partition */
    mtd_dev = (struct fal_mtd_nor_device *)fal_mtd_nor_device_create(FS_PARTITION_NAME);
    if (mtd_dev == RT_NULL)
    {
        rt_kprintf("[qspi_fs] failed to create MTD NOR device for '%s'\n",
                   FS_PARTITION_NAME);
        return -RT_ERROR;
    }

    /* Try direct mount (for already formatted flash) */
    ret = dfs_mount(FS_PARTITION_NAME, FS_MOUNT_POINT, FS_TYPE_NAME, 0, 0);
    if (ret == 0)
    {
        rt_kprintf("[qspi_fs] '%s' mounted at '%s'\n",
                   FS_PARTITION_NAME, FS_MOUNT_POINT);
        return RT_EOK;
    }

    /* Mount failed, indicating flash is not formatted (first use scenario), perform mkfs */
    rt_kprintf("[qspi_fs] mount failed (ret=%d), formatting '%s'...\n",
               ret, FS_PARTITION_NAME);

    ret = dfs_mkfs(FS_TYPE_NAME, FS_PARTITION_NAME);
    if (ret != 0)
    {
        rt_kprintf("[qspi_fs] mkfs failed (ret=%d)\n", ret);
        return -RT_ERROR;
    }

    /* Remount after successful mkfs */
    ret = dfs_mount(FS_PARTITION_NAME, FS_MOUNT_POINT, FS_TYPE_NAME, 0, 0);
    if (ret != 0)
    {
        rt_kprintf("[qspi_fs] mount failed after mkfs (ret=%d)\n", ret);
        return -RT_ERROR;
    }

    rt_kprintf("[qspi_fs] '%s' formatted and mounted at '%s'\n",
               FS_PARTITION_NAME, FS_MOUNT_POINT);
    return RT_EOK;
}
INIT_APP_EXPORT(_qspi_flash_fs_mount);
/*
 * FAL initialization registered as INIT_COMPONENT_EXPORT:
 *   after Flash driver (INIT_DEVICE_EXPORT)
 *   before filesystem mount (INIT_APP_EXPORT)
 */
INIT_COMPONENT_EXPORT(fal_init);

#endif /* BSP_USING_QSPI_FLASH_FS */