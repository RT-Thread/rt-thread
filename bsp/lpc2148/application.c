/*
 * File      : app.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-06-05     Bernard      the first version
 */

#include <rtthread.h>
#include <finsh.h>

/**
 * @addtogroup LPC2148
 */
/*@{*/

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs_init.h>
/* dfs filesystem:FAT filesystem init */
#include <dfs_fat.h>
/* dfs filesystem:EFS filesystem init */
#include <dfs_efs.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
#endif

/* thread phase init */
void rt_init_thread_entry(void *parameter)
{
/* Filesystem Initialization */
#ifdef RT_USING_DFS
	{
		/* init the device filesystem */
		dfs_init();
		/* init the efsl filesystam*/
		efsl_init();

		/* mount sd card fat partition 1 as root directory */
		if (dfs_mount("sd0", "/", "efs", 0, 0) == 0)
			rt_kprintf("File System initialized!\n");
		else
			rt_kprintf("File System init failed!\n");
	}
#endif

/* LwIP Initialization */
#ifdef RT_USING_LWIP
	{
		extern void lwip_sys_init(void);
	
		/* init lwip system */
		lwip_sys_init();
		rt_kprintf("TCP/IP initialized!\n");
	}
#endif
}

/************** LED BLINK *******************/
#include "lpc214x.h"
#define LED1 ( 1<<16) //P1
#define LED2 ( 1<<17) //P1
#define LED3 ( 1<<18) //P1
#define LED4 ( 1<<19) //P1
char thread3_stack[512];
struct rt_thread thread3;
void thread3_entry(void* parameter)
{
 volatile unsigned int i;
 IO1DIR |= LED1;
 while(1)
 {
 IO1CLR = LED1;
 rt_thread_delay(20);
 IO1SET = LED1;
 rt_thread_delay(20);
 }
}

char thread4_stack[512];
struct rt_thread thread4;
void thread4_entry(void* parameter)
{
 volatile unsigned int i;
 IO1DIR |= LED2;
 while(1)
 {
 IO1CLR = LED2;
 rt_thread_delay(30);
 IO1SET = LED2;
 rt_thread_delay(30);
 }
}
/************** LED BLINK *******************/

int rt_application_init()
{
	rt_thread_init(&thread3,
		"led1",
		thread3_entry, RT_NULL,
		&thread3_stack[0], sizeof(thread3_stack),
		20, 10);

	rt_thread_init(&thread4,
		"led2",
		thread4_entry, RT_NULL,
		&thread4_stack[0], sizeof(thread4_stack),
		25, 8);
	rt_thread_startup(&thread3);
	rt_thread_startup(&thread4);

	{
		rt_thread_t init_thread;
	
		init_thread = rt_thread_create("init",
									rt_init_thread_entry, RT_NULL,
									1024, 8, 5);
		rt_thread_startup(init_thread);
	}
	
	rt_kprintf("enter list() to get function list!\n");

	return 0;
}

/*@}*/
