/*
 * COPYRIGHT (C) 2012-2022, Shanghai Real-Thread Technology Co., Ltd
 * All rights reserved.
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <unistd.h>
#include "drv_pin.h"

#ifdef BSP_USING_SDMMC
#include "drv_sdmmc.h"
#endif

#ifdef RT_USING_FAL
#include "fal.h"
#endif

#ifdef RT_USING_DFS
#include <dfs_fs.h>

#define SD_CHECK_PIN GET_PIN(GPIO_PORT_G, GPIO_PIN_3)

void sd_check_thread_entry(void *p)
{
    rt_uint8_t old_sd_check = 0;

    /* 挂载sd0分区 */
    if (RT_NULL != rt_device_find("sd0p0"))
    {
        if (dfs_mount("sd0p0", "/", "elm", 0, 0) == 0)
        {
            rt_kprintf("Mount \"sd0p0\" on \"/\" success\n");
        }
        else
        {
            rt_kprintf("Mount \"sd0p0\" on \"/\" fail\n");
            return ;
        }

        /* 挂载sd1分区 */
        if (RT_NULL != rt_device_find("sd0p1"))
        {
            if (dfs_mount("sd0p1", "/", "elm", 0, 0) == 0)
            {
                rt_kprintf("Mount \"sd0p1\" on \"/\" success\n");
            }
            else
            {
                rt_kprintf("Mount \"sd0p1\" on \"/data\" fail\n");
            }
        }

        while (1)
        {
#ifdef SD_CARD_CHECK
            if (!rt_pin_read(SD_CHECK_PIN) && !old_sd_check) // mount
#else
            if (!old_sd_check) // mount
#endif
            {
                sd_mmc1_init();
                /* 挂载sd2分区 */
                if (RT_NULL != rt_device_find("sd1p0"))
                {

                    if (access("/mnt", 0) != 0)
                    {
                        mkdir("/mnt", 0777);
                    }

                    if (dfs_mount("sd1p0", "/mnt", "elm", 0, 0) == 0)
                    {
                        rt_kprintf("Mount \"sd1p0\" on \"/mnt\" success\n");
                    }
                    else
                    {
                        rt_kprintf("Mount \"sd1p0\" on \"/mnt\" fail\n");
                    }
                }
                old_sd_check = 1;
            }
#ifdef SD_CARD_CHECK
            else if (rt_pin_read(SD_CHECK_PIN) && old_sd_check) // unmount
            {
                if (RT_NULL != rt_device_find("sd1p0"))
                {

                    if (dfs_unmount("/mnt") == 0)
                    {
                        rt_kprintf("unMount \"sd1p0\" on \"/mnt\" success\n");
                    }
                    else
                    {
                        rt_kprintf("unMount \"sd1p0\" on \"/mnt\" fail\n");
                    }
                }
                sd_mmc1_deinit();
                old_sd_check = 0;
            }
#endif
            rt_thread_delay(RT_TICK_PER_SECOND);
        }
    }
    return ;
}

int mnt_init(void)
{
#ifdef RT_USING_FAL
    {
        rt_thread_t thread = NULL;

        rt_pin_mode(SD_CHECK_PIN, PIN_MODE_INPUT_PULLUP);

        thread = rt_thread_create("sd", sd_check_thread_entry, NULL, RT_SYSTEM_WORKQUEUE_STACKSIZE, 21, 10);
        if (thread == NULL)
        {
            return -1;
        }
        rt_thread_startup(thread);
    }
#endif
    return 0;
}
INIT_ENV_EXPORT(mnt_init);
#endif
