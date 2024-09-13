/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2018-12-13     balanceTWK    add sdcard port file
 * 2019-08-23     WillianChan   add spi sdcard port code
 */

#include <rtthread.h>

#if defined BSP_USING_SDIO_SDCARD || defined BSP_USING_SPI_SDCARD
#include <dfs_elm.h>
#include <dfs_fs.h>
#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include "drv_gpio.h"

#define DBG_TAG "app.card"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

void sd_mount(void *parameter)
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

int stm32_sdcard_mount(void)
{
    rt_thread_t tid;

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
#endif /* BSP_USING_SDIO_SDCARD || BSP_USING_SPI_SDCARD */

#ifdef BSP_USING_SPI_SDCARD
#include "drv_spi.h"
#include "dev_spi_msd.h"
static int rt_hw_spi2_tfcard(void)
{
    __HAL_RCC_GPIOC_CLK_ENABLE();
    rt_hw_spi_device_attach("spi2", "spi20", GET_PIN(D, 2));
    return msd_init("sd0", "spi20");
}
INIT_DEVICE_EXPORT(rt_hw_spi2_tfcard);
#endif /* BSP_USING_SPI_SDCARD */
