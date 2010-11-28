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
 * 2007-11-20     Yi.Qiu		add rtgui application
 * 2008-6-28      Bernard		no rtgui init
 */

/**
 * @addtogroup mini2440
 */
/*@{*/

#include <board.h>
#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_init.h>
#include <dfs_elm.h>
#include <dfs_fs.h>
#include <dfs_posix.h>
#endif

static rt_uint8_t buf_init[0x200];
static struct rt_thread thread_test;


void rt_init_thread_entry(void* parameter)
{
	int fd;
	rt_uint32_t sz;
	char buffer[20];
#ifdef RT_USING_DFS
	dfs_init();
#ifdef RT_USING_DFS_ELMFATFS
	elm_init();
	/* mount sd card fat partition 1 as root directory */
	if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
	{
		rt_kprintf("File System initialized!\n");

		/*Open a file*/
		fd = open("/fattest.txt", O_RDWR|O_CREAT, 0);
		if (fd < 0)
		{
			rt_kprintf("open file for write failed\n");
			return;
		}

		sz = write(fd,"Hello RT-Thread!",sizeof("Hello RT-Thread!"));

		if(sz!=0)
		{
			rt_kprintf("written %d\n",sz);
		}
		else
			rt_kprintf("haven't written\n");

		lseek(fd,0,SEEK_SET);
		
		sz = read(fd,buffer,sizeof(buffer));

		if(sz!=0)
		{
			rt_kprintf("READ %d:",sz);
			while(sz--)
				rt_kprintf("%c",buffer[sz]);//opposite
			rt_kprintf("\n");
		}
		else
			rt_kprintf("haven't read\n");

		close(fd);
	}
	else
		rt_kprintf("File System initialzation failed!\n");
#endif	
#endif
}

void rt_led_thread_entry(void* parameter)
{
	/*
	rt_uint32_t flag = 0;
	while(1)
	{
		//Add your led implemention here
		
		rt_led_put(flag^0x01);
		rt_kprintf("rt led test %s\n",flag?"on":"off" );
		rt_thread_delay(100);
		
		
	} */
	//rt_thread_suspend(rt_thread_self());
}


int rt_application_init()
{
	rt_thread_t led_thread;
	rt_err_t err;

 	err = rt_thread_init(&thread_test,"init",
								rt_init_thread_entry, RT_NULL,buf_init,
								sizeof(buf_init), 19, 20);

	led_thread = rt_thread_create("led",
								rt_led_thread_entry, RT_NULL,
								512, 200, 20);

	if(err == RT_EOK)
		rt_thread_startup(&thread_test);

	if (led_thread != RT_NULL)
		rt_thread_startup(led_thread);

	return 0;
}

/*@}*/
