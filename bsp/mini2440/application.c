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
 * Date           Author		Notes
 * 2007-11-20     Yi.Qiu		add rtgui application
 * 2008-6-28      Bernard		no rtgui init
 */

/**
 * @addtogroup s3ceb2410
 */ 

/*@{*/
#include <rtthread.h>

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
#endif

#ifdef RT_USING_DFS
/* dfs init */
#include <dfs_init.h>
/* dfs filesystem:FAT filesystem init */
#include <dfs_fat.h>
/* dfs filesystem:EFS filesystem init */
#include <dfs_efs.h> 
/* dfs Filesystem APIs */
#include <dfs_fs.h>

void dfs_init_entry(void* parameter)
{	
	/* init the device filesystem */
	dfs_init();
	/* init the fat filesystem */
	fatfs_init();
	/* init the efsl filesystam*/
	efsl_init();

	/* mount sd card fat partition 1 as root directory */
	dfs_mount("sd1", "/", "efs", 0, 0);
	/* mount sd card fat partition 0 */
	//dfs_mount("sd0", "/DEV", "efs", 0, 0);

	rt_kprintf("File System initialized!\n");
}
#endif

#ifdef RT_USING_LWIP
#include "lwip/sys.h"
#include "lwip/api.h"

#ifdef RT_USING_WEBSERVER
extern void thread_webserver(void *parameter);
#endif

#ifdef RT_USING_FTPSERVER
extern void thread_ftpserver(void *parameter);
#endif

void thread_tcpecho(void *parameter)
{
	struct netconn *conn, *newconn;
	err_t err;

	/* Create a new connection identifier. */
	conn = netconn_new(NETCONN_TCP);

	/* Bind connection to well known port number 7. */
	netconn_bind(conn, NULL, 7);

	/* Tell connection to go into listening mode. */
	netconn_listen(conn);

	while(1)
	{
		/* Grab new connection. */
		newconn = netconn_accept(conn);
		/* Process the new connection. */
		if(newconn != NULL)
		{
			struct netbuf *buf;
			void *data;
			u16_t len;

			while((buf = netconn_recv(newconn)) != NULL)
			{
				do
				{
					netbuf_data(buf, &data, &len);
					err = netconn_write(newconn, data, len, NETCONN_COPY);
					if(err != ERR_OK){}
				}
				while(netbuf_next(buf) >= 0);
				netbuf_delete(buf);
			}
			/* Close connection and discard connection identifier. */
			netconn_delete(newconn);
		}
	}
}

void lwip_init_entry(void* parameter)
{
	/* init lwip system */
	lwip_sys_init();
	rt_kprintf("TCP/IP initialized!\n");
}
#endif

/* application start function */
void rt_application_init()
{
#ifdef RT_USING_DFS
	rt_thread_t dfs_init;

	dfs_init = rt_thread_create("tdfs",
								dfs_init_entry, RT_NULL,
								2048, 150, 20);
	rt_thread_startup(dfs_init);
#endif

#ifdef RT_USING_LWIP
	rt_thread_t lwip_init;
	rt_thread_t echo;

	lwip_init = rt_thread_create("tlwip",
								 lwip_init_entry, RT_NULL,
								 1024, 100,20);
	rt_thread_startup(lwip_init);

	echo = rt_thread_create("echo",
							thread_tcpecho, RT_NULL,
							1024, 200,20);
	rt_thread_startup(echo);
	
#ifdef RT_USING_WEBSERVER
	rt_thread_t webserver;

	webserver = rt_thread_create("twebserv",
							thread_webserver, RT_NULL,
							4096, 140, 20); 
	rt_thread_startup(webserver);
#endif

#ifdef RT_USING_FTPSERVER
	rt_thread_t ftpserver;

	ftpserver = rt_thread_create("tftpserv",
							thread_ftpserver, RT_NULL, 
							1024, 200, 20);
	rt_thread_startup(ftpserver);
#endif

#endif

#ifdef RT_USING_RTGUI
	{
		rtgui_rect_t rect;

		/* init rtgui system */
		rtgui_system_server_init();

		/* init graphic driver */
		rt_hw_lcd_init();

		/* register dock panel */
		rect.x1 = 0;
		rect.y1 = 0;
		rect.x2 = 240;
		rect.y2 = 25;
		rtgui_panel_register("dock", &rect);

		/* register main panel */
		rect.x1 = 0;
		rect.y1 = 25;
		rect.x2 = 240;
		rect.y2 = 320;
		rtgui_panel_register("main", &rect);

		rtgui_system_app_init();
	}
#endif
}
 
/*@}*/ 
