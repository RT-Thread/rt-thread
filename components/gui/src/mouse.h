/*
 * File      : mouse.h
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
#ifndef __RTGUI_MOUSE_H__
#define __RTGUI_MOUSE_H__

#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/widgets/window.h>

struct rtgui_mouse_monitor
{
    /* event rect */
    rtgui_rect_t rect;

    /* node list */
    rtgui_list_t list;
};
typedef struct rtgui_mouse_monitor rtgui_mouse_monitor_t;

void rtgui_mouse_init(void);
void rtgui_mouse_fini(void);
void rtgui_mouse_moveto(int x, int y);
/* set cursor position */
void rtgui_mouse_set_position(int x, int y);

void rtgui_mouse_set_cursor_enable(rt_bool_t enable);
void rtgui_mouse_set_cursor(rtgui_image_t *cursor);
void rtgui_mouse_get_cursor_rect(rtgui_rect_t *rect);

void rtgui_mouse_show_cursor(void);
void rtgui_mouse_hide_cursor(void);

rt_bool_t rtgui_mouse_is_intersect(rtgui_rect_t *r);

#ifdef RTGUI_USING_WINMOVE
rt_bool_t rtgui_winrect_is_moved(void);
void rtgui_winrect_set(struct rtgui_win *win);
rt_bool_t rtgui_winrect_moved_done(rtgui_rect_t *winrect, struct rtgui_win **win);
#endif

void rtgui_mouse_monitor_append(rtgui_list_t *head, rtgui_rect_t *rect);
void rtgui_mouse_monitor_remove(rtgui_list_t *head, rtgui_rect_t *rect);
rt_bool_t rtgui_mouse_monitor_contains_point(rtgui_list_t *head, int x, int y);

#endif
