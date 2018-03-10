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
 * 2014-04-27     Bernard      make code cleanup. 
 */

#include <board.h>
#include <rtthread.h>

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs.h>
/* dfs filesystem:ELM filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#include <dfs_posix.h>
#endif

#ifdef PKG_USING_GUIENGINE
#include "rtgui_demo.h"
#include <rtgui/driver.h>
#endif

void rt_init_thread_entry(void* parameter)
{    
     /* initialization RT-Thread Components */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_init();
#endif
    
#ifdef RT_USING_DFS  
    #ifdef RT_USING_DFS_ELMFAT
        /* mount spi flash as root directory */
        if (dfs_mount("W25Q64", "/", "elm", 0, 0) == 0)
        {
            rt_kprintf("spi flash mount to / !\n");
        }
        else
        {
            rt_kprintf("spi flash mount to / failed!\n");
        }
        
        /* mount sd card fat partition 0 as root directory */
        if (dfs_mount("sd0", "/sd0", "elm", 0, 0) == 0)
        {
            rt_kprintf("sd0 mount to /sd0 !\n");
        }
        else
        {
            rt_kprintf("sd0 mount to /sd0 failed!\n");
        }    
    #endif /* RT_USING_DFS_ELMFAT */
        
#endif /* DFS */
    
#ifdef PKG_USING_GUIENGINE
	{
		rt_device_t device;

		device = rt_device_find("lcd");
		/* re-set graphic device */
		rtgui_graphic_set_device(device);
        
        rt_gui_demo_init();
	}
#endif
}
int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
        rt_init_thread_entry, RT_NULL,
        2048, RT_THREAD_PRIORITY_MAX/3, 20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
