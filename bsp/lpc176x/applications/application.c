/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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

#ifdef RT_USING_LWIP
#include <emac.h>
#include <netif/ethernetif.h>
extern int lwip_system_init(void);
#endif

#ifdef RT_USING_DFS
#include <dfs_fs.h>
#include <dfs.h>
#include <sd.h>
#ifdef RT_USING_DFS_ELMFAT
#include <dfs_elm.h>
#endif
#endif

#ifdef RT_USING_FINSH
#include <shell.h>
#include <finsh.h>
#endif

/* thread phase init */
void rt_init_thread_entry(void *parameter)
{
    /* initialize platform */
    platform_init();

#ifdef RT_USING_LWIP
    /* register Ethernet interface device */
    lpc17xx_emac_hw_init();

    /* initialize lwip stack */
    /* register ethernetif device */
    eth_system_device_init();

    /* initialize lwip system */
    lwip_system_init();
    rt_kprintf("TCP/IP initialized!\n");
#endif

    /* Filesystem Initialization */
#ifdef RT_USING_DFS
    rt_hw_sdcard_init();

    /* initialize the device file system */
    dfs_init();

#ifdef RT_USING_DFS_ELMFAT
    /* initialize the elm chan FatFS file system*/
    elm_init();
#endif

    /* mount sd card fat partition 1 as root directory */
    if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
        rt_kprintf("File System initialized!\n");
    else
        rt_kprintf("File System init failed!\n");
#endif

#ifdef RT_USING_FINSH
    /* initialize finsh */
    finsh_system_init();
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
