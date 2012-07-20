/*
 * File      : rtgui_server.h
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-04     Bernard      first version
 */
#ifndef __RTGUI_SERVER_H__
#define __RTGUI_SERVER_H__

#include <rtgui/list.h>
#include <rtgui/dlist.h>

/* RTGUI server definitions */

/* top window definitions in server */
enum rtgui_topwin_flag
{
	WINTITLE_NO         =  0x01,
	WINTITLE_BORDER     =  0x02,
	WINTITLE_ACTIVATE   =  0x04,
	WINTITLE_CLOSEBOX   =  0x08,
	WINTITLE_MOVE       =  0x0C,
	WINTITLE_CB_PRESSED =  0x10,
	WINTITLE_NOFOCUS    =  0x20,
	/* window is hidden by default */
	WINTITLE_SHOWN      =  0x40,
	/* window is modaled by other window */
	WINTITLE_MODALED    =  0x80,
	/* window is modaling other window */
	WINTITLE_MODALING   = 0x100,
	WINTITLE_ONTOP      = 0x200,
	WINTITLE_ONBTM      = 0x400,
};

#define WINTITLE_HEIGHT         20
#define WINTITLE_CB_WIDTH       16
#define WINTITLE_CB_HEIGHT      16
#define WINTITLE_BORDER_SIZE    2

struct rtgui_topwin
{
	/* the window flag */
	enum rtgui_topwin_flag flag;
	/* event mask */
	rt_uint32_t mask;

	struct rtgui_wintitle* title;

	/* the window id */
	struct rtgui_win* wid;

	/* the thread id */
	rt_thread_t tid;

	/* the extent information */
	rtgui_rect_t extent;

	struct rtgui_topwin *parent;

	/* we need to iterate the topwin list with usual order(get target window)
	 * or reversely(painting). So it's better to use a double linked list */
	struct rtgui_dlist_node list;
	struct rtgui_dlist_node child_list;

	/* the monitor rect list */
	rtgui_list_t monitor_list;
};
typedef struct rtgui_topwin rtgui_topwin_t;

/* top win manager init */
void rtgui_topwin_init(void);
void rtgui_server_init(void);

/* post an event to server */
void rtgui_server_post_event(struct rtgui_event* event, rt_size_t size);
rt_err_t rtgui_server_post_event_sync(struct rtgui_event* event, rt_size_t size);

#endif

