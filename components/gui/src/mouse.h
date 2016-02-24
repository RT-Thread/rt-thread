/*
 * File      : mouse.h
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
