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
 * Date           Author		Notes
 * 2011-01-13     weety		first version
 */

/**
 * @addtogroup at91sam9260
 */
/*@{*/

#include <rtthread.h>

#ifdef RT_USING_LED
#include "led.h"
#endif

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
#ifdef RT_USING_LED
	rt_thread_t led_thread;

#if (RT_THREAD_PRIORITY_MAX == 32)
	

	led_thread = rt_thread_create("led",
								rt_led_thread_entry, RT_NULL,
								512, 20, 20);
								
#else
	

	led_thread = rt_thread_create("led",
								rt_led_thread_entry, RT_NULL,
								512, 200, 20);
								
#endif


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
