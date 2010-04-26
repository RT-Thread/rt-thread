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
 * Date           Author		Notes
 * 2007-11-20     Yi.Qiu		add rtgui application
 * 2008-6-28      Bernard		no rtgui init
 */

/**
 * @addtogroup mini2440
 */
/*@{*/

#include <board.h>
#include <rtthread.h>
#include "led.h"

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs_init.h>
/* dfs filesystem:ELM FatFs filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_LWIP
#include <netif/ethernetif.h>
#endif

#ifdef RT_USING_RTGUI
extern void rt_hw_lcd_init(void);
extern void rt_hw_key_init(void);
#endif

void rt_init_thread_entry(void* parameter)
{
/* Filesystem Initialization */
#ifdef RT_USING_DFS
	{
		/* init the device filesystem */
		dfs_init();

#if defined(RT_USING_DFS_ELMFAT)
		/* init the elm chan FatFs filesystam*/
		elm_init();

		/* mount sd card fat partition 1 as root directory */
		if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
		{
			rt_kprintf("File System initialized!\n");
		}
		else
			rt_kprintf("File System initialzation failed!\n");
#endif
	}
#endif

/* LwIP Initialization */
#ifdef RT_USING_LWIP
	{
		extern void lwip_sys_init(void);
		eth_system_device_init();

		/* register ethernetif device */
		rt_hw_dm9000_init();

		/* re-init device driver */
		rt_device_init_all();

		/* init lwip system */
		lwip_sys_init();
		rt_kprintf("TCP/IP initialized!\n");
	}
#endif

#ifdef RT_USING_RTGUI
	{
		rt_hw_touch_init();
		rtgui_startup();
	}
#endif
}

void rt_led_thread_entry(void* parameter)
{
	while(1)
	{
		/* light on leds for one second */
		rt_hw_led_on(LED2|LED3);
		rt_hw_led_off(LED1|LED4);
		rt_thread_delay(100);

		/* light off leds for one second */
		rt_hw_led_off(LED2|LED3);
		rt_hw_led_on(LED1|LED4);
		rt_thread_delay(100);

	}
}


int rt_application_init()
{
	rt_thread_t init_thread;
	rt_thread_t led_thread;

#if (RT_THREAD_PRIORITY_MAX == 32)
	init_thread = rt_thread_create("init",
								rt_init_thread_entry, RT_NULL,
								2048, 8, 20);

	led_thread = rt_thread_create("led",
								rt_led_thread_entry, RT_NULL,
								512, 20, 20);
#else
	init_thread = rt_thread_create("init",
								rt_init_thread_entry, RT_NULL,
								2048, 80, 20);

	led_thread = rt_thread_create("led",
								rt_led_thread_entry, RT_NULL,
								512, 200, 20);
#endif

	if (init_thread != RT_NULL)
		rt_thread_startup(init_thread);

	if(led_thread != RT_NULL)
		rt_thread_startup(led_thread);

	return 0;
}

/*@}*/
