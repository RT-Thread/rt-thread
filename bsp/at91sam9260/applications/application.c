/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
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
 * Date           Author		Notes
 * 2011-01-13     weety		first version
 */

/**
 * @addtogroup at91sam9260
 */
/*@{*/

#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs_init.h>
/* dfs filesystem:ELM FatFs filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#ifdef RT_USING_DFS_UFFS
/* dfs filesystem:UFFS filesystem init */
#include <dfs_uffs.h>
#endif
#endif

#if defined(RT_USING_DFS_DEVFS)
#include <devfs.h>
#endif

#ifdef RT_USING_SDIO
#include <drivers/mmcsd_core.h>
#include "at91_mci.h"
#endif

#ifdef RT_USING_LWIP
#include <netif/ethernetif.h>
//#include <arch/sys_arch_init.h>
#include "macb.h"
#endif

#ifdef RT_USING_LED
#include "led.h"
#endif

#define RT_INIT_THREAD_STACK_SIZE (2*1024)

#ifdef RT_USING_DFS_ROMFS
#include <dfs_romfs.h>
#endif

void rt_init_thread_entry(void* parameter)
{
/* Filesystem Initialization */
#ifdef RT_USING_DFS
	{
		/* init the device filesystem */
		dfs_init();

#if defined(RT_USING_DFS_ELMFAT)
		/* init the elm chan FatFs filesystam*/
		elm_init();
#endif

#if defined(RT_USING_DFS_ROMFS)
		dfs_romfs_init();
		if (dfs_mount(RT_NULL, "/rom", "rom", 0, &romfs_root) == 0)
		{
			rt_kprintf("ROM File System initialized!\n");
		}
		else
			rt_kprintf("ROM File System initialzation failed!\n");
#endif

#if defined(RT_USING_DFS_DEVFS)
		devfs_init();
		if (dfs_mount(RT_NULL, "/dev", "devfs", 0, 0) == 0)
			rt_kprintf("Device File System initialized!\n");
		else
			rt_kprintf("Device File System initialzation failed!\n");

		#ifdef RT_USING_NEWLIB
		/* init libc */
		libc_system_init("uart0");
		#endif
#endif

#if defined(RT_USING_DFS_UFFS)
	{
		/* init the uffs filesystem */
		dfs_uffs_init();

		/* mount flash device as flash directory */
		if(dfs_mount("nand0", "/nand0", "uffs", 0, 0) == 0)
			rt_kprintf("UFFS File System initialized!\n");
		else
			rt_kprintf("UFFS File System initialzation failed!\n");
	}
#endif

#ifdef RT_USING_SDIO
	rt_mmcsd_core_init();
	rt_mmcsd_blk_init();
	at91_mci_init();
	rt_thread_delay(RT_TICK_PER_SECOND*2);
	/* mount sd card fat partition 1 as root directory */
		if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
		{
			rt_kprintf("File System initialized!\n");
		}
		else
			rt_kprintf("File System initialzation failed!\n");
#endif
	}
#endif

#ifdef RT_USING_LWIP
	{
		/* register ethernetif device */
		eth_system_device_init();
		rt_hw_macb_init();
		/* init lwip system */
		lwip_sys_init();
	}
#endif

#ifdef RT_USING_I2C
	{
		rt_i2c_core_init();
		at91_i2c_init();
	}
#endif

}

#ifdef RT_USING_LED
void rt_led_thread_entry(void* parameter)
{
	rt_uint8_t cnt = 0;
	led_init();
	while(1)
	{
		/* light on leds for one second */
		rt_thread_delay(40);
		cnt++;
		if (cnt&0x01)
			led_on(1);
		else
			led_off(1);
		if (cnt&0x02)
			led_on(2);
		else
			led_off(2);
		if (cnt&0x04)
			led_on(3);
		else
			led_off(3);
			
	}
}
#endif

int rt_application_init()
{
	rt_thread_t init_thread;
#ifdef RT_USING_LED
	rt_thread_t led_thread;
#endif

#if (RT_THREAD_PRIORITY_MAX == 32)
	init_thread = rt_thread_create("init",
								rt_init_thread_entry, RT_NULL,
								RT_INIT_THREAD_STACK_SIZE, 8, 20);
#ifdef RT_USING_LED
	led_thread = rt_thread_create("led",
								rt_led_thread_entry, RT_NULL,
								512, 20, 20);
#endif
								
#else
	init_thread = rt_thread_create("init",
								rt_init_thread_entry, RT_NULL,
								RT_INIT_THREAD_STACK_SIZE, 80, 20);
#ifdef RT_USING_LED
	led_thread = rt_thread_create("led",
								rt_led_thread_entry, RT_NULL,
								512, 200, 20);
#endif
								
#endif

	if (init_thread != RT_NULL)
		rt_thread_startup(init_thread);
#ifdef RT_USING_LED
	if(led_thread != RT_NULL)
		rt_thread_startup(led_thread);
#endif

	return 0;
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
