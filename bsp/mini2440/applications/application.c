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

#include <rtthread.h>
#include "touch.h"
#include "lcd.h"
#include "led.h"
#include "dm9000.h"

#ifdef RT_USING_DFS
/* dfs filesystem:ELM FatFs filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#ifdef RT_USING_DFS_UFFS
/* dfs filesystem:UFFS filesystem init */
#include <dfs_uffs.h>
#endif
#endif

#ifdef RT_USING_LWIP
#include <netif/ethernetif.h>
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
#endif

#ifdef RT_USING_FTK
#include "ftk.h"
#endif

#define RT_INIT_THREAD_STACK_SIZE (2*1024)

#ifdef RT_USING_DFS_ROMFS
#include <dfs_romfs.h>
#endif

#ifdef RT_USING_FTK
static int argc = 1;
static char* argv[] = {"ftk", NULL};

void rt_ftk_thread_entry(void *parameter)
{
	int FTK_MAIN(int argc, char *argv[]);

	FTK_MAIN(argc, argv);

	return;
}

#endif

void rt_init_thread_entry(void *parameter)
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

#if defined(RT_USING_DFS_ROMFS)
		dfs_romfs_init();
		if (dfs_mount(RT_NULL, "/rom", "rom", 0, &romfs_root) == 0)
		{
			rt_kprintf("ROM File System initialized!\n");
		}
		else
			rt_kprintf("ROM File System initialzation failed!\n");
#endif

#if defined(RT_USING_DFS_DEVFS)
		devfs_init();
		if (dfs_mount(RT_NULL, "/dev", "devfs", 0, 0) == 0)
			rt_kprintf("Device File System initialized!\n");
		else
			rt_kprintf("Device File System initialzation failed!\n");

		#ifdef RT_USING_NEWLIB
		/* init libc */
		libc_system_init("uart0");
		#endif
#endif

#if defined(RT_USING_DFS) && defined(RT_USING_LWIP) && defined(RT_USING_DFS_NFS)
		/* NFSv3 Initialization */
		nfs_init();

		if (dfs_mount(RT_NULL, "/nfs", "nfs", 0, RT_NFS_HOST_EXPORT) == 0)
			rt_kprintf("NFSv3 File System initialized!\n");
		else
			rt_kprintf("NFSv3 File System initialzation failed!\n");
#endif

#if defined(RT_USING_DFS_UFFS)
		/* init the uffs filesystem */
		dfs_uffs_init();

		/* mount flash device as flash directory */
		if (dfs_mount("nand0", "/nand0", "uffs", 0, 0) == 0)
			rt_kprintf("UFFS File System initialized!\n");
		else
			rt_kprintf("UFFS File System initialzation failed!\n");
#endif
	}
#endif

#ifdef RT_USING_RTGUI
	{
		extern void rtgui_system_server_init(void);

		rt_device_t lcd;
		
		/* init lcd */
		rt_hw_lcd_init();
			
		/* init touch panel */
		rtgui_touch_hw_init();	

		/* init keypad */
		rt_hw_key_init();

		/* find lcd device */
		lcd = rt_device_find("lcd");

		/* set lcd device as rtgui graphic driver */		
		rtgui_graphic_set_device(lcd);

		/* initalize rtgui system server */
		rtgui_system_server_init();
	}
#endif

/* LwIP Initialization */
#ifdef RT_USING_LWIP
	{
		extern void lwip_sys_init(void);
		eth_system_device_init();

		/* register ethernetif device */
		rt_hw_dm9000_init();

		/* init lwip system */
		lwip_sys_init();
		rt_kprintf("TCP/IP initialized!\n");
	}
#endif

#ifdef RT_USING_FTK
	{
		rt_thread_t ftk_thread;

		/* init lcd */
		rt_hw_lcd_init();

		/* init touch panel */
		rtgui_touch_hw_init();	

		/* init keypad */
		rt_hw_key_init();

		/* create ftk thread */
		ftk_thread = rt_thread_create("ftk",
									rt_ftk_thread_entry, RT_NULL,
									10 * 1024, 8, 20);	

		/* startup ftk thread */
		if (ftk_thread != RT_NULL)
			rt_thread_startup(ftk_thread);		
	}
#endif
}

void rt_led_thread_entry(void *parameter)
{
	while (1)
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

int rt_application_init(void)
{
	rt_thread_t init_thread;
	rt_thread_t led_thread;

#if (RT_THREAD_PRIORITY_MAX == 32)
	init_thread = rt_thread_create("init",
								rt_init_thread_entry, RT_NULL,
								RT_INIT_THREAD_STACK_SIZE, 8, 20);

	led_thread = rt_thread_create("led",
								rt_led_thread_entry, RT_NULL,
								512, 20, 20);
#else
	init_thread = rt_thread_create("init",
								rt_init_thread_entry, RT_NULL,
								RT_INIT_THREAD_STACK_SIZE, 80, 20);

	led_thread = rt_thread_create("led",
								rt_led_thread_entry, RT_NULL,
								512, 200, 20);
#endif

	if (init_thread != RT_NULL)
		rt_thread_startup(init_thread);

	if (led_thread != RT_NULL)
		rt_thread_startup(led_thread);

	return 0;
}

/*@}*/
