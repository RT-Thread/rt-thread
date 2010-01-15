/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

/**
 * @addtogroup STM32
 */
/*@{*/

#include <rtthread.h>
#include <finsh.h>

#include <stm32f10x.h>
#include "board.h"
#include "netbuffer.h"
#include "lcd.h"

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs_init.h>
/* dfs filesystem:FAT filesystem init */
#include <dfs_fat.h>
/* dfs filesystem:EFS filesystem init */
#include <dfs_efs.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>
#endif

#ifdef RT_USING_RTGUI
extern void radio_rtgui_init(void);
#endif

/* thread phase init */
void rt_init_thread_entry(void *parameter)
{
    /* Filesystem Initialization */
#ifdef RT_USING_DFS
    {
        /* init the device filesystem */
        dfs_init();
#ifdef RT_USING_DFS_EFSL
        /* init the efsl filesystam*/
        efsl_init();

        /* mount sd card fat partition 1 as root directory */
        if (dfs_mount("sd0", "/", "efs", 0, 0) == 0)
            rt_kprintf("File System initialized!\n");
        else
            rt_kprintf("File System init failed!\n");
#elif defined(RT_USING_DFS_ELMFAT)
        /* init the elm FAT filesystam*/
        elm_init();

        /* mount sd card fat partition 1 as root directory */
        if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
            rt_kprintf("File System initialized!\n");
        else
            rt_kprintf("File System init failed!\n");
#endif
    }
#endif

	/* RTGUI Initialization */
#ifdef RT_USING_RTGUI
	{
		extern void rt_hw_key_init(void);

		radio_rtgui_init();
		rt_hw_key_init();
	}
#endif

    /* LwIP Initialization */
#ifdef RT_USING_LWIP
    {
        extern void lwip_sys_init(void);
		extern void rt_hw_dm9000_init(void);

		eth_system_device_init();

		/* register ethernetif device */
		rt_hw_dm9000_init();
		/* init all device */
		rt_device_init_all();

        /* init lwip system */
        lwip_sys_init();
        rt_kprintf("TCP/IP initialized!\n");
    }
#endif

#if STM32_EXT_SRAM
	/* init netbuf worker */
	net_buf_init(320 * 1024);
#endif
}

int rt_application_init()
{
    rt_thread_t init_thread;

	rt_hw_lcd_init();

#if (RT_THREAD_PRIORITY_MAX == 32)
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 8, 20);
#else
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 80, 20);
#endif
    if (init_thread != RT_NULL) rt_thread_startup(init_thread);

    return 0;
}

/*@}*/
