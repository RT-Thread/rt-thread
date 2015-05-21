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

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <shell.h>
#endif

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <netif/ethernetif.h>
extern void lwip_system_init(void);
#endif

#ifdef RT_USING_DFS
#include <dfs_init.h>
#include <dfs_fs.h>
#ifdef RT_USING_DFS_ELMFAT
#include <dfs_elm.h>
#endif
#if defined(RT_USING_LWIP) && defined(RT_USING_DFS_NFS)
#include <dfs_nfs.h>
#endif
#ifdef RT_USING_DFS_ROMFS
#include <dfs_romfs.h>
#endif
#ifdef RT_USING_DFS_DEVFS
#include <devfs.h>
#endif
#ifdef RT_USING_DFS_UFFS
#include <dfs_uffs.h>
#endif
#ifdef RT_USING_DFS_JFFS2
#include <dfs_jffs2.h>
#endif
#ifdef RT_USING_DFS_YAFFS2
#include <dfs_yaffs2.h>
#endif
#ifdef RT_USING_DFS_ROMFS
#include <dfs_romfs.h>
#endif
#endif

#ifdef RT_USING_NEWLIB
#include <libc.h>
#endif
#ifdef RT_USING_PTHREADS
#include <pthread.h>
#endif

#ifdef RT_USING_MODULE
#include <rtm.h>
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui_system.h>
#endif

void rt_init_thread_entry(void *parameter)
{
#ifdef RT_USING_LWIP
#ifdef RT_USING_TAPNETIF
    tap_netif_hw_init();
#else
    pcap_netif_hw_init();
#endif
#endif

    rt_platform_init();

#ifdef RT_USING_MODULE
    rt_system_module_init();
#endif

#ifdef RT_USING_FINSH
	/* initialize finsh */
	finsh_system_init();
	finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_LWIP
	/* initialize lwip stack */
	/* register ethernetif device */
	eth_system_device_init();

	/* initialize lwip system */
	lwip_system_init();
	rt_kprintf("TCP/IP initialized!\n");
#endif

#ifdef RT_USING_DFS
	/* initialize the device file system */
	dfs_init();

#ifdef RT_USING_DFS_ELMFAT
	/* initialize the elm chan FatFS file system*/
	elm_init();
#endif

#if defined(RT_USING_DFS_NFS) && defined(RT_USING_LWIP)
	/* initialize NFSv3 client file system */
	nfs_init();
#endif

#ifdef RT_USING_DFS_YAFFS2
	dfs_yaffs2_init();
#endif

#ifdef RT_USING_DFS_UFFS
	dfs_uffs_init();
#endif

#ifdef RT_USING_DFS_JFFS2
	dfs_jffs2_init();
#endif

#ifdef RT_USING_DFS_ROMFS
	dfs_romfs_init();
#endif

#ifdef RT_USING_DFS_RAMFS
	dfs_ramfs_init();
#endif

#ifdef RT_USING_DFS_DEVFS
	devfs_init();
#endif
#endif /* end of RT_USING_DFS */

#ifdef RT_USING_NEWLIB
	libc_system_init(RT_CONSOLE_DEVICE_NAME);
#else
	/* the pthread system initialization will be initiallized in libc */
#ifdef RT_USING_PTHREADS 
	pthread_system_init();
#endif
#endif

#ifdef RT_USING_RTGUI
	rtgui_system_server_init();
#endif

#ifdef RT_USING_USB_HOST
	rt_usb_host_init();
#endif

#ifdef RT_USING_RTGUI
    /* start sdl thread to simulate an LCD. SDL may depend on DFS and should be
     * called after rt_components_init. */
    rt_hw_sdl_start();
#endif /* RT_USING_RTGUI */

    /* File system Initialization */
#ifdef RT_USING_DFS
    {
#ifdef RT_USING_DFS_WINSHAREDIR
        {
            extern rt_err_t rt_win_sharedir_init(const char *name);
            extern int dfs_win32_init(void);

            rt_win_sharedir_init("wdd");
            dfs_win32_init();

            if (dfs_mount("wdd", "/", "wdir", 0, 0) == 0)
                rt_kprintf("win32 share directory initialized!\n");
            else
                rt_kprintf("win32 share directory initialized failed!\n");
        }
#endif

#ifdef RT_USING_DFS_ELMFAT
        /* mount sd card fatfs as root directory */
#ifdef _WIN32
        if (dfs_mount("sd0", "/disk/sd", "elm", 0, 0) == 0)
#else
        if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
#endif
            rt_kprintf("fatfs initialized!\n");
        else
            rt_kprintf("fatfs initialization failed!\n");
#endif

#ifdef RT_USING_DFS_UFFS
        /* mount uffs as the nand flash file system */
        if (dfs_mount("nand0", "/disk/nand", "uffs", 0, 0) == 0)
            rt_kprintf("uffs initialized!\n");
        else
            rt_kprintf("uffs initialization failed!\n");
#endif

#ifdef RT_USING_DFS_JFFS2
        /* mount jffs2 as the nor flash file system */
        if (dfs_mount("nor", "/disk/nor", "jffs2", 0, 0) == 0)
            rt_kprintf("jffs2 initialized!\n");
        else
            rt_kprintf("jffs2 initialization failed!\n");
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

/*@}*/