/*
 * File      : panel.h
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

#ifndef __RT_PANEL_H__
#define __RT_PANEL_H__

#include <rtgui/rtgui.h>
#include <rtgui/list.h>
#include <rtgui/region.h>

struct rtgui_panel_thread
{
	/* thread id */
	rt_thread_t tid;

	/* the list of thread */
	rtgui_list_t list;

	/* monitor rect list */
	rtgui_list_t monitor_list;
};
typedef struct rtgui_panel_thread rtgui_panel_thread_list_t;

struct rtgui_panel
{
	char name[RTGUI_NAME_MAX];

	/* the extent of panel */
	rtgui_rect_t extent;

	/* the list of panel */
	rtgui_list_t sibling;

	/* the thread list in this panel */
	rtgui_list_t thread_list;

	/* the workbench manager thread */
	rt_thread_t wm_thread;

	/* is focusable */
	rt_bool_t is_focusable;
};

/* find panel by name */
struct rtgui_panel* rtgui_panel_find(char* name);

/* add or remove application thread from specified panel */
rtgui_panel_t* rtgui_panel_thread_add(char* name, rt_thread_t tid);
void rtgui_panel_thread_remove(rtgui_panel_t* panel, rt_thread_t tid);

rt_thread_t rtgui_panel_get_active_thread(rtgui_panel_t* panel);
void rtgui_panel_set_active_thread(rtgui_panel_t* panel, rt_thread_t tid);

rtgui_panel_t* rtgui_panel_get_contain(int x, int y);
void rtgui_panel_set_wm(rtgui_panel_t* panel, rt_thread_t wm);

void rtgui_panel_append_monitor_rect(rtgui_panel_t* panel, rt_thread_t tid, rtgui_rect_t* rect);
void rtgui_panel_remove_monitor_rect(rtgui_panel_t* panel, rt_thread_t tid, rtgui_rect_t* rect);

#endif

