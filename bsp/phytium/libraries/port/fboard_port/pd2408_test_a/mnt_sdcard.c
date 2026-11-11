/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-27     huanghe      first version
 * 2023-07-14   liqiaozhong    add SD file sys mount func
 * 2024-04-08    zhugengyu     define mount table by board
 */
#include <rtthread.h>
#include <dfs_fs.h>

#define DBG_TAG "mnt.filesystem"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#if defined(USE_SDIF0_TF)
#define FS_SD_MOUNT_POINT            "/"
#define FS_SD_DEVICE_NAME            "sd0"
#define FS_SD_DEVICE_INDEX           0
#elif defined(USE_SDIF0_EMMC)
#define FS_EMMC_MOUNT_POINT           "/"
#define FS_EMMC_DEVICE_NAME           "sd0"
#define FS_EMMC_DEVICE_INDEX          0
#endif

extern void sdif_change(rt_uint32_t id);

#if defined(USE_SDIF0_TF)
extern rt_int32_t sdif_card_inserted(rt_uint32_t id);
static rt_int32_t card_inserted = 0;

static void _sdcard_mount(void)
{
    rt_device_t device;

    device = rt_device_find(FS_SD_DEVICE_NAME);
    if (device == NULL)
    {
        mmcsd_wait_cd_changed(0);
        sdif_change(FS_SD_DEVICE_INDEX);
        mmcsd_wait_cd_changed(RT_WAITING_FOREVER);
        device = rt_device_find(FS_SD_DEVICE_NAME);
    }

    if (device != RT_NULL)
    {
        if (dfs_mount(FS_SD_DEVICE_NAME, FS_SD_MOUNT_POINT, "elm", 0, 0) == RT_EOK)
        {
            LOG_I("%s mount to '%s'", FS_SD_DEVICE_NAME, FS_SD_MOUNT_POINT);
            card_inserted = 1;
        }
        else
        {
            LOG_W("%s mount to '%s' failed!", FS_SD_DEVICE_NAME, FS_SD_MOUNT_POINT);
        }
    }
}

static void _sdcard_unmount(void)
{
    rt_thread_mdelay(200);
    dfs_unmount(FS_SD_MOUNT_POINT);
    LOG_I("Unmount %s", FS_SD_MOUNT_POINT);

    mmcsd_wait_cd_changed(0);
    sdif_change(FS_SD_DEVICE_INDEX);
    mmcsd_wait_cd_changed(RT_WAITING_FOREVER);

    card_inserted = 0;
}
#endif
static void sd_auto_mount(void *parameter)
{
    rt_thread_mdelay(20);

#if defined(USE_SDIF0_TF)
    if ((card_inserted == 0) && (sdif_card_inserted(FS_SD_DEVICE_INDEX) == 1))
    {
        _sdcard_mount();
    }

    while (RT_TRUE)
    {
        rt_thread_mdelay(200);

        if ((card_inserted == 0) && (sdif_card_inserted(FS_SD_DEVICE_INDEX) == 1))
        {
            _sdcard_mount();
        }

        if ((card_inserted == 1) && (sdif_card_inserted(FS_SD_DEVICE_INDEX) == 0))
        {
            _sdcard_unmount();
        }
    }
#elif defined(USE_SDIF0_EMMC)
    mmcsd_wait_cd_changed(0);
    sdif_change(FS_EMMC_DEVICE_INDEX);
    mmcsd_wait_cd_changed(RT_WAITING_FOREVER);

    if (dfs_mount(FS_EMMC_DEVICE_NAME, FS_EMMC_MOUNT_POINT, "elm", 0, 0) == RT_EOK)
    {
        LOG_I("%s mount to '%s'", FS_EMMC_DEVICE_NAME, FS_EMMC_MOUNT_POINT);
    }
    else
    {
        LOG_W("%s mount to '%s' failed!", FS_EMMC_DEVICE_NAME, FS_EMMC_MOUNT_POINT);
    }
#endif
}

static void sd_mount(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("sd_mount", sd_auto_mount, RT_NULL,
                           8192, RT_THREAD_PRIORITY_MAX - 2, 20);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    else
    {
        LOG_E("create sd_mount thread err!");
        return;
    }
}

int filesystem_mount(void)
{
    sd_mount();
    return RT_EOK;
}
INIT_APP_EXPORT(filesystem_mount);