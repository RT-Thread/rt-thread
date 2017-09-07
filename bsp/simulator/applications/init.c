/*
 * File      : init.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2015, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-09-30     Bernard      the first version
 */

#include <rtthread.h>

#include "init.h"

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

/* components initialization for simulator */
void components_init(void)
{
    platform_init();

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
}
