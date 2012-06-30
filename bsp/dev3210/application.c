/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-06-25     Bernard      first version
 */

#include <rtthread.h>
#include <soc3210.h>

#ifdef RT_USING_DFS
#include <dfs.h>
#include <dfs_elm.h>
#ifdef RT_USING_DFS_ROMFS
#include <dfs_romfs.h>
#endif
#ifdef RT_USING_DFS_DEVFS
#include <devfs.h>
#endif
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>
#endif

void rt_init_thread_entry(void *parameter)
{
	/* Filesystem Initialization */
#ifdef RT_USING_DFS
	{
		/* init the device filesystem */
		dfs_init();

#if defined(RT_USING_DFS_ROMFS)
		dfs_romfs_init();
		if (dfs_mount(RT_NULL, "/", "rom", 0, &romfs_root) == 0)
		{
			rt_kprintf("ROM File System initialized!\n");
		}
		else
			rt_kprintf("ROM File System initialzation failed!\n");
#endif

#if defined(RT_USING_DFS_ELMFAT)
		/* init the elm chan FatFs filesystam*/
		elm_init();
		/* mount sd card fat partition 1 as root directory */
		if (dfs_mount("sd0", "/sd", "elm", 0, 0) == 0)
		{
			rt_kprintf("File System initialized!\n");
		}
		else
			rt_kprintf("File System initialzation failed!\n");
#endif

#if defined(RT_USING_DFS_DEVFS)
		devfs_init();
		if (dfs_mount(RT_NULL, "/dev", "devfs", 0, 0) == 0)
			rt_kprintf("Device File System initialized!\n");
		else
			rt_kprintf("Device File System initialzation failed!\n");

		#ifdef RT_USING_NEWLIB
		/* init libc */
		libc_system_init("uart");
		rt_kprintf("libc init done\n");
		#endif
#endif
	}
#endif

#ifdef RT_USING_RTGUI
	{
		rtgui_rect_t rect;

		rtgui_system_server_init();

		/* register dock panel */
		rect.x1 = 0;
		rect.y1 = 0;
		rect.x2 = 400;
		rect.y2 = 480;
//		rtgui_panel_register("panel", &rect);

		/* register main panel */
		rect.x1 = 400;
		rect.y1 = 0;
		rect.x2 = 800;
		rect.y2 = 480;
//		rtgui_panel_register("main", &rect);
//		rtgui_panel_set_default_focused("main");

		rt_hw_lcd_init();
	}
#endif
}

int rt_application_init(void)
{
	rt_thread_t tid;

	/* create initialization thread */
	tid = rt_thread_create("init",
							rt_init_thread_entry, RT_NULL,
							4096, 8, 20);
	if (tid != RT_NULL)
		rt_thread_startup(tid);

	return 0;
}
