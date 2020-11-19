/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2018-12-13     balanceTWK    add sdcard port file
 * 2019-06-11     WillianChan   Add SD card hot plug detection
 */

#include <rtthread.h>

#ifdef BSP_USING_FS

#if RT_DFS_ELM_MAX_SECTOR_SIZE < 4096
#error "Please define RT_DFS_ELM_MAX_SECTOR_SIZE more than 4096"
#endif
#if DFS_FILESYSTEMS_MAX < 4
#error "Please define DFS_FILESYSTEMS_MAX more than 4"
#endif
#if DFS_FILESYSTEM_TYPES_MAX < 4
#error "Please define DFS_FILESYSTEM_TYPES_MAX more than 4"
#endif

#include <dfs_fs.h>
#include "dfs_romfs.h"
#include "drv_sdio.h"
#include "fal.h"
#define DBG_TAG "app.filesystem"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static const struct romfs_dirent _romfs_root[] = {
    {ROMFS_DIRENT_DIR, "flash", RT_NULL, 0},
    {ROMFS_DIRENT_DIR, "sdcard", RT_NULL, 0}};

const struct romfs_dirent romfs_root = {
    ROMFS_DIRENT_DIR, "/", (rt_uint8_t *)_romfs_root, sizeof(_romfs_root) / sizeof(_romfs_root[0])};

#ifdef BSP_USING_SDCARD_FS

/* SD Card hot plug detection pin */
#define SD_CHECK_PIN GET_PIN(D, 5)

static void _sdcard_mount(void)
{
    rt_device_t device;

    device = rt_device_find("sd0");
    if (device == NULL)
    {
        mmcsd_wait_cd_changed(0);
        sdcard_change();
        mmcsd_wait_cd_changed(RT_WAITING_FOREVER);
        device = rt_device_find("sd0");
    }
    if (device != RT_NULL)
    {
        if (dfs_mount("sd0", "/sdcard", "elm", 0, 0) == RT_EOK)
        {
            LOG_I("sd card mount to '/sdcard'");
        }
        else
        {
            LOG_W("sd card mount to '/sdcard' failed!");
        }
    }
}

static void _sdcard_unmount(void)
{
    rt_thread_mdelay(200);
    dfs_unmount("/sdcard");
    LOG_I("Unmount \"/sdcard\"");

    mmcsd_wait_cd_changed(0);
    sdcard_change();
    mmcsd_wait_cd_changed(RT_WAITING_FOREVER);
}

static void sd_mount(void *parameter)
{
    rt_uint8_t re_sd_check_pin = 1;
    rt_thread_mdelay(200);
    if (rt_pin_read(SD_CHECK_PIN))
    {
        _sdcard_mount();
    }
    while (1)
    {
        rt_thread_mdelay(200);
        if (!re_sd_check_pin && (re_sd_check_pin = rt_pin_read(SD_CHECK_PIN)) != 0)
        {
            _sdcard_mount();
        }

        if (re_sd_check_pin && (re_sd_check_pin = rt_pin_read(SD_CHECK_PIN)) == 0)
        {
            _sdcard_unmount();
        }
    }
}

#endif /* BSP_USING_SDCARD_FS */

int mount_init(void)
{
    if (dfs_mount(RT_NULL, "/", "rom", 0, &(romfs_root)) != 0)
    {
        LOG_E("rom mount to '/' failed!");
    }
#ifdef BSP_USING_SPI_FLASH_FS
    struct rt_device *flash_dev = RT_NULL;

#ifndef RT_USING_WIFI
    fal_init();
#endif

    flash_dev = fal_mtd_nor_device_create("filesystem");

    if (flash_dev)
    {
        //mount filesystem
        if (dfs_mount(flash_dev->parent.name, "/flash", "lfs", 0, 0) != 0)
        {
            LOG_W("mount to '/flash' failed! try to mkfs %s", flash_dev->parent.name);
            dfs_mkfs("lfs", flash_dev->parent.name);
            if (dfs_mount(flash_dev->parent.name, "/flash", "lfs", 0, 0) == 0)
            {
                LOG_I("mount to '/flash' success!");
            }
        }
        else
        {
            LOG_I("mount to '/flash' success!");
        }
    }
    else
    {
        LOG_E("Can't create  block device  filesystem or bt_image partition.");
    }

#endif

#ifdef BSP_USING_SDCARD_FS
    rt_thread_t tid;

    rt_pin_mode(SD_CHECK_PIN, PIN_MODE_INPUT_PULLUP);

    tid = rt_thread_create("sd_mount", sd_mount, RT_NULL,
                           2048, RT_THREAD_PRIORITY_MAX - 2, 20);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    else
    {
        LOG_E("create sd_mount thread err!");
    }
    return RT_EOK;
#endif
}
INIT_APP_EXPORT(mount_init);

#endif /* BSP_USING_FS */
