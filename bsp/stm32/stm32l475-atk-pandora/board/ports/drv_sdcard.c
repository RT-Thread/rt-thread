/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-14     balanceTWK   add sdcard port file
 * 2021-02-26     Meco Man     fix a bug that cannot use fatfs in the main thread at starting up
 */

#include <rtthread.h>

#ifdef BSP_USING_SDCARD

#include <dfs_elm.h>
#include <dfs_fs.h>
#include <dfs_posix.h>
#include "drv_spi.h"
#include "spi_msd.h"

#define DBG_TAG "app.card"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static void sd_mount(void *parameter)
{
    while (1)
    {
        rt_thread_mdelay(500);
        if(rt_device_find("sd0") != RT_NULL)
        {
            if (dfs_mount("sd0", "/", "elm", 0, 0) == RT_EOK)
            {
                LOG_I("sd card mount to '/'");
                break;
            }
            else
            {
                LOG_W("sd card mount to '/' failed!");
            }
        }
    }
}

static int onboard_sdcard_mount(void)
{
    rt_thread_t tid;

    if (dfs_mount("sd0", "/", "elm", 0, 0) == RT_EOK)
    {
        LOG_I("sd card mount to '/'");
    }
    else
    {
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
    }

    return RT_EOK;
}
INIT_APP_EXPORT(onboard_sdcard_mount);

static int rt_hw_spi1_tfcard(void)
{
    __HAL_RCC_GPIOC_CLK_ENABLE();
    rt_hw_spi_device_attach("spi1", "spi10", GPIOC, GPIO_PIN_3);
    return msd_init("sd0", "spi10");
}
INIT_DEVICE_EXPORT(rt_hw_spi1_tfcard);

#endif /* BSP_USING_SDCARD */

