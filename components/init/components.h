/*
 * File      : components_init.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
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
 * 2012-09-20     Bernard      Change the name to components.h
 *                             And all components related header files.
 */

#ifndef __COMPONENTS_INIT_H__
#define __COMPONENTS_INIT_H__

#include <rtthread.h>

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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initializes board routine in RT-Thread.
 */
void rt_components_board_init(void);

/**
 * Initializes components in RT-Thread
 * notes: this function must be invoked in Init Thread
 */
void rt_components_init(void);

#ifdef __cplusplus
}
#endif

#endif
