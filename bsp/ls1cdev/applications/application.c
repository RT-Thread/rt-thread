/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2012, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date                Author         Notes
 * 2010-06-25          Bernard        first version
 * 2011-08-08          lgnq           modified for Loongson LS1B
 * 2015-07-06          chinesebear    modified for Loongson LS1C
 * 2018-02-08          sundm75    modified for Loongson LS1C SmartLoongV3
 */

#include <rtthread.h>
#include "net/synopGMAC.h"
#include <lwip/api.h>

void rt_init_thread_entry(void *parameter)
{
#ifdef RT_USING_COMPONENTS_INIT
    /* initialization RT-Thread Components */
    rt_components_init();
#endif
#if defined(RT_USING_DFS) && defined(RT_USING_DFS_ELMFAT)
    /* mount sd card fat partition 1 as root directory */
    if( dfs_mount("sd0", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("File System initialized!\n");
    }
    else
    {
        rt_kprintf("File System initialzation failed!\n");
    }
#endif /* RT_USING_DFS && RT_USING_DFS_ELMFAT */

/*网口EMAC初始化*/
    rt_hw_eth_init();
#if defined(RT_USING_RTGUI)
/*触摸屏使用SPI总线SPI1 CS0  初始化*/
    rtgui_touch_hw_init("spi10");
#endif

}

int rt_application_init(void)
{
    rt_thread_t tid;

    /* create initialization thread */
    tid = rt_thread_create("init",
            rt_init_thread_entry, RT_NULL,
            4096, RT_THREAD_PRIORITY_MAX/3, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
