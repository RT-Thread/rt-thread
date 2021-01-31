/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>
#include <dfs.h>
#include "floppy.h"
#ifdef RT_USING_MODULE
#include <rtm.h>
#endif
extern int elm_init(void);
#endif

/* components initialization for simulator */
void components_init(void)
{
#ifdef RT_USING_DFS
	rt_floppy_init();
	/* initialize the device file system */
	dfs_init();

#ifdef RT_USING_DFS_ELMFAT
	/* initialize the elm chan FatFS file system*/
	elm_init();
#endif

#ifdef RT_USING_MODULE
	rt_system_dlmodule_init();
#endif
#endif
}
void rt_init_thread_entry(void *parameter)
{
    components_init();

    /* File system Initialization */
#ifdef RT_USING_DFS
    {

#ifdef RT_USING_DFS_ELMFAT
        /* mount sd card fatfs as root directory */
        if (dfs_mount("floppy", "/", "elm", 0, 0) == 0)
            rt_kprintf("fatfs initialized!\n");
        else
            rt_kprintf("fatfs initialization failed!\n");
#endif
    }
#endif
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
                           rt_init_thread_entry, RT_NULL,
                           2048, RT_THREAD_PRIORITY_MAX / 3, 20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
