/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-01-13     weety     first version
 */

/**
 * @addtogroup at91sam9260
 */
/*@{*/

#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_DFS
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_SDIO
#include <drivers/dev_mmcsd_core.h>
#include "at91_mci.h"
#endif

#ifdef RT_USING_LED
#include "led.h"
#endif

static int rt_led_app_init(void);

int main(void)
{
    int timeout = 0;

/* Filesystem Initialization */
#ifdef RT_USING_DFS
    {
#if defined(RT_USING_DFS_ROMFS)
        if (dfs_mount(RT_NULL, "/rom", "rom", 0, &romfs_root) == 0)
        {
            rt_kprintf("ROM File System initialized!\n");
        }
        else
            rt_kprintf("ROM File System initialzation failed!\n");
#endif

#if defined(RT_USING_DFS_UFFS)
    {
        /* mount flash device as flash directory */
        if(dfs_mount("nand0", "/nand0", "uffs", 0, 0) == 0)
            rt_kprintf("UFFS File System initialized!\n");
        else
            rt_kprintf("UFFS File System initialzation failed!\n");
    }
#endif

#ifdef RT_USING_SDIO
    timeout = 0;
    while ((rt_device_find("sd0") == RT_NULL) && (timeout++ < RT_TICK_PER_SECOND*2))
    {
        rt_thread_delay(1);
    }

    if (timeout < RT_TICK_PER_SECOND*2)
    {
        /* mount sd card fat partition 1 as root directory */
        if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
        {
            rt_kprintf("File System initialized!\n");
        }
        else
            rt_kprintf("File System initialzation failed!%d\n", rt_get_errno());
    }
    else
    {
        rt_kprintf("No SD card found.\n");
    }
#endif
    }
#endif

#ifdef RT_USING_LED
    rt_led_app_init();
#endif
}

#ifdef RT_USING_LED
void rt_led_thread_entry(void* parameter)
{
    rt_uint8_t cnt = 0;
    led_init();
    while(1)
    {
        /* light on leds for one second */
        rt_thread_delay(40);
        cnt++;
        if (cnt&0x01)
            led_on(1);
        else
            led_off(1);
        if (cnt&0x02)
            led_on(2);
        else
            led_off(2);
        if (cnt&0x04)
            led_on(3);
        else
            led_off(3);
    }
}
#endif

static int rt_led_app_init(void)
{
#ifdef RT_USING_LED
    rt_thread_t led_thread;

#if (RT_THREAD_PRIORITY_MAX == 32)
    led_thread = rt_thread_create("led",
                                rt_led_thread_entry, RT_NULL,
                                512, 20, 20);
#else
    led_thread = rt_thread_create("led",
                                rt_led_thread_entry, RT_NULL,
                                512, 200, 20);
#endif

    if(led_thread != RT_NULL)
        rt_thread_startup(led_thread);
#endif

    return 0;
}

/* NFSv3 Initialization */
#if defined(RT_USING_DFS) && defined(RT_USING_LWIP) && defined(RT_USING_DFS_NFS)
#include <dfs_nfs.h>
void nfs_start(void)
{
    nfs_init();

    if (dfs_mount(RT_NULL, "/nfs", "nfs", 0, RT_NFS_HOST_EXPORT) == 0)
    {
        rt_kprintf("NFSv3 File System initialized!\n");
    }
    else
        rt_kprintf("NFSv3 File System initialzation failed!\n");
}

#include "finsh.h"
FINSH_FUNCTION_EXPORT(nfs_start, start net filesystem);
#endif

/*@}*/
