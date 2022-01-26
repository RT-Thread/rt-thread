/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-05-24     Bernard      the first version
 */

/**
 * @addtogroup FM3
 */

/*@{*/

#include <rtthread.h>
#include "board.h"
#include "led.h"

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs.h>
/* dfs filesystem:ELM filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

void rt_init_thread_entry(void *parameter)
{
    /* LED Initialization */
    rt_hw_led_init();

#ifdef RT_USING_COMPONENTS_INIT
    /* initialization RT-Thread Components */
    rt_components_init();
#endif

    /* Filesystem Initialization */
#ifdef RT_USING_DFS
    /* mount nand fat partition 1 as root directory */
    if (dfs_mount("nand", "/", "elm", 0, 0) == 0)
        rt_kprintf("File System initialized!\n");
    else
        rt_kprintf("File System init failed!\n");
#endif
}

int rt_application_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
            rt_init_thread_entry, RT_NULL,
            2048, RT_THREAD_PRIORITY_MAX/3, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}

/*@}*/
