/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2010-03-04     Magicoe      for LPC1766 version
 * 2010-05-02     Aozima       add led function
 * 2010-05-24     Bernard      add filesystem initialization and move led function to led.c
 * 2012-04-15     Bernard      enable components_init.
 */

#include <rtthread.h>
#include "platform.h"

#ifdef RT_USING_COMPONENTS_INIT
#include <components.h>
#endif
#ifdef RT_USING_LWIP
#include <emac.h>
#endif
#ifdef RT_USING_DFS
#include <dfs_fs.h>
#endif

/* thread phase init */
void rt_init_thread_entry(void *parameter)
{
	/* initialize platform */
	platform_init();

#ifdef RT_USING_LWIP
    /* register Ethernet interface device */
    lpc17xx_emac_hw_init();
#endif

#ifdef RT_USING_COMPONENTS_INIT
    /* initialization RT-Thread Components */
    rt_components_init();
#endif

    /* Filesystem Initialization */
#ifdef RT_USING_DFS
    /* mount sd card fat partition 1 as root directory */
    if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
    	rt_kprintf("File System initialized!\n");
    else
    	rt_kprintf("File System init failed!\n");
#endif
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
    		rt_init_thread_entry, RT_NULL,
    		2048, RT_THREAD_PRIORITY_MAX/3, 20);
    if (tid != RT_NULL) rt_thread_startup(tid);

    return 0;
}
