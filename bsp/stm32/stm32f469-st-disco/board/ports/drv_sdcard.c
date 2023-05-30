/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2018-12-13     balanceTWK    add sdcard port file
 * 2019-06-11     WillianChan   Add SD card hot plug detection
 */

#include <rtthread.h>

#ifdef BSP_USING_SDCARD

#include <dfs_elm.h>
#include <dfs_fs.h>
#include <dfs_posix.h>
#include "drv_gpio.h"
#include "drv_sdio.h"

#define DBG_TAG "app.card"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* SD Card hot plug detection pin */
#define SD_CHECK_PIN GET_PIN(G, 2)

static void _sdcard_mount(void)
{
    rt_device_t device;

    device = rt_device_find("sd0");
    if (device == NULL)
    {
        mmcsd_wait_cd_changed(0);
        stm32_mmcsd_change();
        mmcsd_wait_cd_changed(RT_WAITING_FOREVER);
        device = rt_device_find("sd0");
    }
    if (device != RT_NULL)
    {
        if (dfs_mount("sd0", "/", "elm", 0, 0) == RT_EOK)
        {
            LOG_I("sd card mount to '/'");
        }
        else
        {
            LOG_W("sd card mount to '/' failed!");
        }
    }
}

static void _sdcard_unmount(void)
{
    rt_thread_mdelay(200);
    dfs_unmount("/");
    LOG_I("Unmount \"/\"");

    mmcsd_wait_cd_changed(0);
    stm32_mmcsd_change();
    mmcsd_wait_cd_changed(RT_WAITING_FOREVER);
}

static void sd_mount(void *parameter)
{
    rt_uint8_t re_sd_check_pin = 1;

    while (1)
    {
        rt_thread_mdelay(200);
        if(re_sd_check_pin && (re_sd_check_pin = rt_pin_read(SD_CHECK_PIN)) == 0)
        {
            _sdcard_mount();
        }

        if (!re_sd_check_pin && (re_sd_check_pin = rt_pin_read(SD_CHECK_PIN)) != 0)
        {
            _sdcard_unmount();
        }
    }
}

int stm32_sdcard_mount(void)
{
    rt_thread_t tid;

    rt_pin_mode(SD_CHECK_PIN, PIN_MODE_INPUT_PULLUP);

    tid = rt_thread_create("sd_mount", sd_mount, RT_NULL,
                           1024, RT_THREAD_PRIORITY_MAX - 2, 20);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    else
    {
        LOG_E("create sd_mount thread err!");
    }
    return RT_EOK;
}
INIT_APP_EXPORT(stm32_sdcard_mount);

#endif /* BSP_USING_SDCARD */
