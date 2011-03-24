/*
 * File      : win_server.h
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
#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>


rt_err_t rtgui_topwin_add(rtgui_win_t* win); /* add a top win */
rt_err_t rtgui_topwin_remove(rtgui_win_t* win);	/* remove a top win */
rt_err_t rtgui_topwin_raise(rtgui_win_t* win); /* raise window to front */
rt_err_t rtgui_topwin_show(rtgui_win_t* win); /* show a window */
rt_err_t rtgui_topwin_hide(rtgui_win_t* win); /* hide a window */
rt_err_t rtgui_topwin_move(rtgui_win_t* win, int x, int y);	/* move a window */
rt_err_t rtgui_topwin_resize(rtgui_win_t* wid, rtgui_rect_t* r); /* resize a window */

rtgui_win_t* rtgui_topwin_get_wnd(int x, int y); /* get window at (x, y) */

rt_err_t rtgui_topwin_activate(rtgui_win_t* win);
rt_err_t rtgui_topwin_deactivate(rtgui_win_t* win);

void rtgui_toplevel_update_clip(PVOID wdt, rtgui_rect_t *rect, int front_num);
void rtgui_panel_update_clip(PVOID wdt);
void rtgui_panel_redraw(rtgui_rect_t* rect);
/* window title */
void rtgui_topwin_title_onmouse(rtgui_win_t* win, rtgui_event_mouse_t* event);
void rtgui_update_external_clip_info(void);

#endif

