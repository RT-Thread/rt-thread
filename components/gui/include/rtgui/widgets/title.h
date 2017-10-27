/*
 * File      : title.h
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
#ifndef __RTGUI_TITLE__
#define __RTGUI_TITLE__

#include <rtgui/widgets/widget.h>

DECLARE_CLASS_TYPE(wintitle);
/** Gets the type of a title */
#define RTGUI_WINTITLE_TYPE       (RTGUI_TYPE(wintitle))
/** Casts the object to an rtgui_wintitle */
#define RTGUI_WINTITLE(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_WINTITLE_TYPE, rtgui_wintitle_t))
/** Checks if the object is an rtgui_wintitle */
#define RTGUI_IS_WINTITLE(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_WINTITLE_TYPE))

struct rtgui_wintitle
{
    struct rtgui_widget parent;
};
typedef struct rtgui_wintitle rtgui_wintitle_t;

rtgui_wintitle_t *rtgui_wintitle_create(struct rtgui_win *window);
void rtgui_wintitle_destroy(rtgui_wintitle_t *wintitle);

rt_bool_t rtgui_wintile_event_handler(struct rtgui_object *object, rtgui_event_t *event);

#endif
