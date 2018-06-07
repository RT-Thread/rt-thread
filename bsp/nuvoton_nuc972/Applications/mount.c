/*
 * File      : mount.c
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/28     Urey         first implementation
 */


#include <rtthread.h>
#include <rtdevice.h>
#include <dfs_fs.h>
#include <board.h>

extern int rt_nuc97x_sdio_init(void);
int mnt_init(void)
{
#ifdef RT_USING_SDIO
    rt_nuc97x_sdio_init();
    rt_thread_delay(RT_TICK_PER_SECOND*2);
    /* mount sd card fat partition 1 as root directory */
    if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("File System on TF initialized!\n");
    }
#endif

#ifdef RT_USING_LITTLEFS
    /* mount file system */
    if (dfs_mount("appfs", "/", "lfs", 0, 0) == 0)
    {
        rt_kprintf("LFS on nor initialized!\n");
    }
    else
    {
        dfs_mkfs("lfs","appfs");
        if (dfs_mount("appfs", "/", "lfs", 0, 0) == 0)
        {
            rt_kprintf("LFS on appfs initialized!\n");
        }
        else
        {
            rt_kprintf("*** ERROR*** LFS on nor failed!\n");
        }
    }
#endif

#ifdef RT_USING_DFS_UFFS
    /* mount nand flash partition 0 as root directory */
    if (dfs_mount("nand0", "/", "uffs", 0, 0) == 0)
    {
        rt_kprintf("uffs initialized!\n");
    }
    else
    {
        rt_kprintf("uffs initialzation failed!\n");
    }
#endif     // End of RT_USING_DFS_UFFS
}
INIT_ENV_EXPORT(mnt_init);

