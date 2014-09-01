/*
 * File      : components.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012 - 2013, RT-Thread Development Team
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
 * 2012-09-20     Bernard      Change the name to components.c
 *                             And all components related header files.
 * 2012-12-23     Bernard      fix the pthread initialization issue.
 * 2013-06-23     Bernard      Add the init_call for components initialization.
 * 2013-07-05     Bernard      Remove initialization feature for MS VC++ compiler 
 */

#include "components.h"

static int rti_start(void)
{
    return 0;
}
INIT_EXPORT(rti_start, "0");

static int rti_board_end(void)
{
    return 0;
}
INIT_EXPORT(rti_board_end, "1.post");

static int rti_end(void)
{
    return 0;
}
INIT_EXPORT(rti_end,"7");

/**
 * RT-Thread Components Initialization for board
 */
void rt_components_board_init(void)
{
#ifndef _MSC_VER
#if RT_DEBUG_INIT
	int result;
	const struct rt_init_desc *desc;
	for (desc = &__rt_init_desc_rti_start; desc < &__rt_init_desc_rti_board_end; desc ++)
	{
		rt_kprintf("initialize %s", desc->fn_name);
		result = desc->fn();
		rt_kprintf(":%d done\n", result);
	}
#else
    const init_fn_t *fn_ptr;

    for (fn_ptr = &__rt_init_rti_start; fn_ptr < &__rt_init_rti_board_end; fn_ptr++)
    {
        (*fn_ptr)();
    }
#endif
#endif
}

/**
 * RT-Thread Components Initialization
 */
void rt_components_init(void)
{
#ifndef _MSC_VER
#if RT_DEBUG_INIT
	int result;
	const struct rt_init_desc *desc;

	rt_kprintf("do components intialization.\n");
	for (desc = &__rt_init_desc_rti_board_end; desc < &__rt_init_desc_rti_end; desc ++)
	{
		rt_kprintf("initialize %s", desc->fn_name);
		result = desc->fn();
		rt_kprintf(":%d done\n", result);
	}
#else
    const init_fn_t *fn_ptr;

    for (fn_ptr = &__rt_init_rti_board_end; fn_ptr < &__rt_init_rti_end; fn_ptr ++)
    {
        (*fn_ptr)();
    }
#endif
#else
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
#endif
}
