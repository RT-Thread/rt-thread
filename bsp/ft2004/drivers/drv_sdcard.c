/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-03-18     Carl      the first version
 */

#include <rtthread.h>

#ifdef BSP_USING_SDC

#include <dfs_elm.h>
#include <dfs_fs.h>
#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include "drv_sdctrl.h"

#define DBG_TAG "app.card"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_err_t _sdcard_mount(void)
{
    rt_device_t device;

    device = rt_device_find("sd0");
    rt_kprintf("rt_device_find %x \r\n", device);
    if (device == NULL)
    {
        mmcsd_wait_cd_changed(0);
        ft2004_mmcsd_change();
        if (mmcsd_wait_cd_changed(rt_tick_from_millisecond(5000)) == -RT_ETIMEOUT)
        {
            rt_kprintf("timeout \r\n");
            return -RT_ERROR;
        }
        device = rt_device_find("sd0");
    }

    rt_thread_mdelay(1000);
    LOG_I("dfs_mount  \r\n");
    if (device != RT_NULL)
    {
        if (dfs_mount("sd0", "/", "elm", 0, 0) == RT_EOK)
        {
            LOG_I("sd card mount to '/'");
        }
        else
        {
            LOG_W("sd card mount to '/' failed!");
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}

static void _sdcard_unmount(void)
{
    rt_thread_mdelay(200);
    dfs_unmount("/");
    LOG_I("Unmount \"/\"");

    mmcsd_wait_cd_changed(0);
    ft2004_mmcsd_change();
    mmcsd_wait_cd_changed(rt_tick_from_millisecond(5000));
    LOG_I("Unmount is over \r\n");
}

static void sd_mount(void *parameter)
{
    rt_uint8_t state = 0; /* 1. is valid card ,0 is removal */
#ifdef BSP_SDC_IRQ_CARD_REMOVE
    rt_uint32_t status;
#endif
    while (1)
    {
        switch (state)
        {
        case 0:
            if (ft2004_card_status() == 1)
            {
#ifdef BSP_SDC_IRQ_CARD_REMOVE
                ft2004_card_remove_check(0, RT_NULL); /* Clear removal flag bit */
#endif
                if (_sdcard_mount() == RT_EOK)
                {
                    state = 1;
                }
                else
                {
                    /* For the critical case of frequent plug */
                    rt_kprintf("dfs_unmount \r\n");
                    _sdcard_unmount();
                    ft2004_sdctrl_reset();
                }
            }
            else
            {
                rt_thread_mdelay(100);
            }
            break;
        case 1:

#ifdef BSP_SDC_IRQ_CARD_REMOVE
            if (ft2004_card_remove_check(RT_WAITING_FOREVER, &status) == RT_EOK)
            {
                if (status & SDCTR_CARD_REMOVE_FLG)
                {
                    state = 0;
                    _sdcard_unmount();
                }
            }
#else
            if (ft2004_card_status() == 0)
            {
                state = 0;
                _sdcard_unmount();
            }
#endif
            else
            {
                rt_thread_mdelay(100);
            }
            break;
        default:
            state = 0;
            break;
        }
    }
}

int ft2004_sdcard_mount(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("sd_mount", sd_mount, RT_NULL,
                           8192, 2, 20);

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
INIT_APP_EXPORT(ft2004_sdcard_mount);

#endif /* BSP_USING_SDCARD */
