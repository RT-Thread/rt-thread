/*
 * File      : topwin.h
 * This file is part of RT-Thread GUI Engine
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
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
 * Date           Author       Notes
 * 2009-10-16     Bernard      first version
 */
#ifndef __RTGUI_TOPWIN_H__
#define __RTGUI_TOPWIN_H__

#include <rtgui/rtgui.h>
#include <rtgui/region.h>
#include <rtgui/event.h>
#include <rtgui/widgets/title.h>
#include <rtgui/rtgui_server.h>

/* add or remove a top win */
rt_err_t rtgui_topwin_add(struct rtgui_event_win_create *event);
rt_err_t rtgui_topwin_remove(struct rtgui_win *wid);
rt_err_t rtgui_topwin_activate(struct rtgui_event_win_activate *event);
rt_err_t rtgui_topwin_activate_topwin(struct rtgui_topwin *win);

/* show a window */
rt_err_t rtgui_topwin_show(struct rtgui_event_win *event);
/* hide a window */
rt_err_t rtgui_topwin_hide(struct rtgui_event_win *event);
/* move a window */
rt_err_t rtgui_topwin_move(struct rtgui_event_win_move *event);
/* resize a window */
void rtgui_topwin_resize(struct rtgui_win *wid, rtgui_rect_t *r);
/* a window is entering modal mode */
rt_err_t rtgui_topwin_modal_enter(struct rtgui_event_win_modal_enter *event);

/* get window at (x, y) */
struct rtgui_topwin *rtgui_topwin_get_wnd(int x, int y);
struct rtgui_topwin *rtgui_topwin_get_wnd_no_modaled(int x, int y);

//void rtgui_topwin_deactivate_win(struct rtgui_topwin* win);

/* window title */
void rtgui_topwin_title_ondraw(struct rtgui_topwin *win);
void rtgui_topwin_title_onmouse(struct rtgui_topwin *win, struct rtgui_event_mouse *event);

/* monitor rect */
void rtgui_topwin_append_monitor_rect(struct rtgui_win *wid, rtgui_rect_t *rect);
void rtgui_topwin_remove_monitor_rect(struct rtgui_win *wid, rtgui_rect_t *rect);

/* get the topwin that is currently focused */
struct rtgui_topwin *rtgui_topwin_get_focus(void);

struct rtgui_topwin *rtgui_topwin_get_topmost_window_shown_all(void);

#endif

