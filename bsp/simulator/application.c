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

#include <rtthread.h>
#include <stdio.h>
#include <board.h>

#include <components.h>

void rt_init_thread_entry(void* parameter)
{
    /* initialization RT-Thread Components */
    rt_components_init();

    rt_platform_init();

    /* Filesystem Initialization */
#ifdef RT_USING_DFS
    {
#ifdef RT_USING_DFS_ELMFAT
        /* mount sd card fat partition 1 as root directory */
        if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
        {
            rt_kprintf("fatfs initialized!\n");
        }
        else
            rt_kprintf("fatfs initialzation failed!\n");
#endif

#ifdef RT_USING_DFS_ELMFAT
        /* mount sd card fat partition 1 as root directory */
        if (dfs_mount("nand0", "/nand", "uffs", 0, 0) == 0)
        {
            rt_kprintf("uffs initialized!\n");
        }
        else
            rt_kprintf("uffs initialzation failed!\n");
#endif

#ifdef RT_USING_DFS_JFFS2
        /* mount sd card fat partition 1 as root directory */
        if (dfs_mount("nor", "/nor", "jffs2", 0, 0) == 0)
        {
            rt_kprintf("jffs2 initialized!\n");
        }
        else
            rt_kprintf("jffs2 initialzation failed!\n");
#endif
    }
#endif
}

void rt_test_thread_entry(void* parameter)
{
	int i;
	for(i=0; i<10; i++)
	{
		rt_kprintf("hello, world\n");
		rt_thread_delay(100);
	}
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
        rt_init_thread_entry, RT_NULL,
        2048, RT_THREAD_PRIORITY_MAX/3, 20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    tid = rt_thread_create("test",
        rt_test_thread_entry, RT_NULL,
        2048, RT_THREAD_PRIORITY_MAX * 3 /4, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}

#include <stdlib.h>
void rt_hw_exit(void)
{
    rt_kprintf("RT-Thread, bye\n");
    exit(0);
}
FINSH_FUNCTION_EXPORT_ALIAS(rt_hw_exit, exit, exit rt-thread);

/*@}*/
