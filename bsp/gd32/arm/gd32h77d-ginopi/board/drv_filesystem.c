/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <dfs_fs.h>
#include <dfs_romfs.h>

#ifdef BSP_USING_FLASH_FATFS
#include <fal.h>
#include "fal_cfg.h"
#endif

#define DBG_TAG "app.filesystem"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#if defined(BSP_USING_SDCARD_FATFS) || defined(BSP_USING_FLASH_FATFS) || defined(RT_USBH_MSTORAGE)
static const struct romfs_dirent _romfs_root[] =
{
#ifdef BSP_USING_SDCARD_FATFS
    {ROMFS_DIRENT_DIR, "sd", RT_NULL, 0},
#endif
#ifdef BSP_USING_FLASH_FATFS
    {ROMFS_DIRENT_DIR, "flash", RT_NULL, 0},
#endif
#ifdef RT_USBH_MSTORAGE
    {ROMFS_DIRENT_DIR, "udisk", RT_NULL, 0},
#endif
};
#endif

const struct romfs_dirent romfs_root =
{
#if defined(BSP_USING_SDCARD_FATFS) || defined(BSP_USING_FLASH_FATFS) || defined(RT_USBH_MSTORAGE)
    ROMFS_DIRENT_DIR, "/", (rt_uint8_t *)_romfs_root,
    sizeof(_romfs_root) / sizeof(_romfs_root[0])
#else
    ROMFS_DIRENT_DIR, "/", RT_NULL, 0
#endif
};

#ifdef BSP_USING_FLASH_FATFS
static void qspi_flash_mount(void)
{
    const struct fal_partition *partition;
    rt_device_t device;
    rt_uint8_t probe_data;
    int result;

    if (fal_init() <= 0)
    {
        LOG_E("FAL initialization failed");
        return;
    }

    partition = fal_partition_find(GD25Q64E_FILESYSTEM_PART_NAME);
    if (partition == RT_NULL ||
        fal_partition_read(partition, 0, &probe_data, sizeof(probe_data)) !=
        (int)sizeof(probe_data))
    {
        LOG_E("QSPI flash is not accessible");
        return;
    }

    device = rt_device_find(GD25Q64E_FILESYSTEM_PART_NAME);
    if (device == RT_NULL)
    {
        device = fal_blk_device_create(GD25Q64E_FILESYSTEM_PART_NAME);
    }
    if (device == RT_NULL)
    {
        LOG_E("create FAL block device failed");
        return;
    }

#ifdef BSP_USING_FLASH_FS_AUTO_MOUNT
    result = dfs_mount(GD25Q64E_FILESYSTEM_PART_NAME,
                       "/flash", "elm", 0, RT_NULL);
    if (result == RT_EOK)
    {
        LOG_I("QSPI flash mounted at /flash");
    }
    else
    {
        LOG_W("QSPI flash mount failed: %d; format with: mkfs -t elm %s",
              rt_get_errno(), GD25Q64E_FILESYSTEM_PART_NAME);
        LOG_W("then mount with: mount %s /flash elm",
              GD25Q64E_FILESYSTEM_PART_NAME);
    }
#endif
}
#endif /* BSP_USING_FLASH_FATFS */

#ifdef BSP_USING_FS_AUTO_MOUNT
static void sdcard_mount(void)
{
    rt_device_t device = rt_device_find("sd0");
    int result;

    if (device == RT_NULL)
    {
        LOG_W("SD card device not found");
        return;
    }

    if (rt_device_init(device) != RT_EOK)
    {
        LOG_W("SD card not detected, skip mounting");
        return;
    }

    result = dfs_mount("sd0", "/sd", "elm", 0, RT_NULL);
    if (result == RT_EOK)
    {
        LOG_I("SD card mounted at /sd");
    }
    else
    {
        LOG_E("SD card mount failed: %d", rt_get_errno());
    }
}
#endif

static int filesystem_mount(void)
{
    if (dfs_mount(RT_NULL, "/", "rom", 0, &romfs_root) != RT_EOK)
    {
        LOG_E("ROM filesystem mount failed");
        return -RT_ERROR;
    }

#ifdef BSP_USING_FLASH_FATFS
    qspi_flash_mount();
#endif

#ifdef BSP_USING_FS_AUTO_MOUNT
    rt_thread_mdelay(500);
    sdcard_mount();
#endif

    return RT_EOK;
}
INIT_ENV_EXPORT(filesystem_mount);
