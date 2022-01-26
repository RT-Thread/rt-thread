/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-01-13     weety     first version
 */


/**
 * @addtogroup dm365
 */
/*@{*/

#include <rtthread.h>

#ifdef RT_USING_DFS
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_SDIO
#include <drivers/mmcsd_core.h>
#endif

int main(void)
{
    int timeout = 0;

/* Filesystem Initialization */
#ifdef RT_USING_DFS
    {

#if defined(RT_USING_DFS_ROMFS)
        if (dfs_mount(RT_NULL, "/rom", "rom", 0, &romfs_root) == 0)
        {
            rt_kprintf("ROM File System initialized!\n");
        }
        else
            rt_kprintf("ROM File System initialzation failed!\n");
#endif

#if defined(RT_USING_DFS_UFFS)
    {
        /* mount flash device as flash directory */
        if(dfs_mount("nand0", "/nand0", "uffs", 0, 0) == 0)
            rt_kprintf("UFFS File System initialized!\n");
        else
            rt_kprintf("UFFS File System initialzation failed!\n");
    }
#endif

#ifdef RT_USING_SDIO
    timeout = 0;
    while ((rt_device_find("sd0") == RT_NULL) && (timeout++ < RT_TICK_PER_SECOND*2))
    {
        rt_thread_delay(1);
    }

    if (timeout < RT_TICK_PER_SECOND*2)
    {
        /* mount sd card fat partition 1 as root directory */
        if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
        {
            rt_kprintf("File System initialized!\n");
        }
        else
            rt_kprintf("File System initialzation failed!%d\n", rt_get_errno());
    }
    else
    {
        rt_kprintf("No SD card found.\n");
    }
#endif
    }
#endif

    /* put user application code here */

}


/* NFSv3 Initialization */
#if defined(RT_USING_DFS) && defined(RT_USING_LWIP) && defined(RT_USING_DFS_NFS)
#include <dfs_nfs.h>
void nfs_start(void)
{
    nfs_init();

    if (dfs_mount(RT_NULL, "/nfs", "nfs", 0, RT_NFS_HOST_EXPORT) == 0)
    {
        rt_kprintf("NFSv3 File System initialized!\n");
    }
    else
        rt_kprintf("NFSv3 File System initialzation failed!\n");
}

#include "finsh.h"
FINSH_FUNCTION_EXPORT(nfs_start, start net filesystem);
#endif

/*@}*/
