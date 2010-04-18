/*
 * File      : topwin.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-16     Bernard      first version
 */
#ifndef __RTGUI_TOPWIN_H__
#define __RTGUI_TOPWIN_H__

#include <rtgui/rtgui.h>
#include <rtgui/list.h>
#include <rtgui/region.h>
#include <rtgui/event.h>
#include <rtgui/widgets/title.h>
#include <rtgui/rtgui_server.h>

/* add or remove a top win */
rt_err_t rtgui_topwin_add(struct rtgui_event_win_create* event);
rt_err_t rtgui_topwin_remove(struct rtgui_win* wid);

/* raise window to front */
void rtgui_topwin_raise(struct rtgui_win* wid, rt_thread_t sender);
/* update clip info to a panel */
void rtgui_topwin_update_clip_to_panel(struct rtgui_panel* panel);

/* show a window */
void rtgui_topwin_show(struct rtgui_event_win* event);
/* hide a window */
void rtgui_topwin_hide(struct rtgui_event_win* event);
/* move a window */
void rtgui_topwin_move(struct rtgui_event_win_move* event);
/* resize a window */
void rtgui_topwin_resize(struct rtgui_win* wid, rtgui_rect_t* r);

/* get window at (x, y) */
struct rtgui_topwin* rtgui_topwin_get_wnd(int x, int y);

void rtgui_topwin_activate_win(struct rtgui_topwin* win);
void rtgui_topwin_deactivate_win(struct rtgui_topwin* win);

/* window title */
void rtgui_topwin_title_ondraw(struct rtgui_topwin* win);
void rtgui_topwin_title_onmouse(struct rtgui_topwin* win, struct rtgui_event_mouse* event);

/* monitor rect */
void rtgui_topwin_append_monitor_rect(struct rtgui_win* wid, rtgui_rect_t* rect);
void rtgui_topwin_remove_monitor_rect(struct rtgui_win* wid, rtgui_rect_t* rect);

void rtgui_topwin_get_clipinfo(struct rtgui_rect* rect_list, rt_int32_t count);

#endif

