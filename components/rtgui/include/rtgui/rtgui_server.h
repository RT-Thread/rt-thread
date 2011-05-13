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

/* RTGUI server definitions */

/* top window definitions in server */
enum
{
	WINTITLE_NO			= 0x01,
	WINTITLE_BORDER		= 0x02,
	WINTITLE_ACTIVATE	= 0x04,
	WINTITLE_CLOSEBOX	= 0x08,
	WINTITLE_MOVE		= 0x0C,
	WINTITLE_CB_PRESSED	= 0x10,
	WINTITLE_NOFOCUS	= 0x20
};

#define WINTITLE_HEIGHT			20
#define WINTITLE_CB_WIDTH		16
#define WINTITLE_CB_HEIGHT		16
#define WINTITLE_BORDER_SIZE	2

struct rtgui_topwin
{
	/* the window flag */
	rt_uint32_t flag;
	/* event mask */
	rt_uint32_t mask;

	struct rtgui_wintitle* title;

	/* the window id */
	struct rtgui_win* wid;

	/* the thread id */
	rt_thread_t tid;

	/* the extent information */
	rtgui_rect_t extent;

	/* the top window list */
	rtgui_list_t list;

	/* the monitor rect list */
	rtgui_list_t monitor_list;
};
typedef struct rtgui_topwin rtgui_topwin_t;

/* top win manager init */
void rtgui_topwin_init(void);
void rtgui_server_init(void);

/* post an event to server */
void rtgui_server_post_event(struct rtgui_event* event, rt_size_t size);

/* register or deregister panel in server */
void rtgui_panel_register(char* name, rtgui_rect_t* extent);
void rtgui_panel_deregister(char* name);

void rtgui_panel_set_default_focused(char* name);
void rtgui_panel_set_nofocused(char* name);

#endif

