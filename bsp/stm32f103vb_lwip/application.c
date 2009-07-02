/*
 * File      : app.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-05-24     Bernard      Add lwip init
 */

/**
 * @addtogroup STM32
 */
/*@{*/

#include <rtthread.h>

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#endif

/* thread phase init */
void rt_init_thread_entry(void *parameter)
{
/* LwIP Initialization */
#ifdef RT_USING_LWIP
	{
		extern void lwip_sys_init(void);
		extern void httpd_init(void);
		
		/* init lwip system */
		lwip_sys_init();
		rt_kprintf("TCP/IP initialized!\n");
		
		httpd_init();
		rt_kprintf("httpd initialized!\n");
	}
#endif
}

int rt_application_init()
{
	rt_thread_t init_thread;

	init_thread = rt_thread_create("init",
								rt_init_thread_entry, RT_NULL,
								2048, 8, 20);
	rt_thread_startup(init_thread);

	return 0;
}

/*@}*/
