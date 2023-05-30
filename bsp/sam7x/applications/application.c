/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-06-05     Bernard      the first version
 */

/**
 * @addtogroup sam7x
 */
/*@{*/
#include <rtthread.h>

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs.h>
/* dfs filesystem:FAT filesystem init */
#include <dfs_fat.h>
/* dfs filesystem:EFS filesystem init */
#include <dfs_efs.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <netif/ethernetif.h>
#include "sam7x_emac.h"
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
#endif

/* thread phase init */
void rt_init_thread_entry(void *parameter)
{
/* Filesystem Initialization */
#ifdef RT_USING_DFS
    {
        /* init the device filesystem */
        dfs_init();
        /* init the efsl filesystam*/
        efsl_init();

        /* mount sd card fat partition 1 as root directory */
        if (dfs_mount("sd0", "/", "efs", 0, 0) == 0)
            rt_kprintf("File System initialized!\n");
        else
            rt_kprintf("File System init failed!\n");
    }
#endif

/* LwIP Initialization */
#ifdef RT_USING_LWIP
    {
        extern void lwip_sys_init(void);

        eth_system_device_init();

        /* register AT91 EMAC device */
        sam7xether_register("E0");

        /* init lwip system */
        lwip_sys_init();
        rt_kprintf("TCP/IP initialized!\n");
    }
#endif
}

int rt_application_init()
{
    rt_thread_t init_thread;

    init_thread = rt_thread_create("init",
                                rt_init_thread_entry, RT_NULL,
                                1024, 8, 5);
    rt_thread_startup(init_thread);

    rt_kprintf("enter list() to get function list!\n");

    return 0;
}

/*@}*/
