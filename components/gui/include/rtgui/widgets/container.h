/*
 * File      : container.h
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
#ifndef __RTGUI_CONTAINER_H__
#define __RTGUI_CONTAINER_H__

#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/box.h>

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_CLASS_TYPE(container);
/** Gets the type of a container */
#define RTGUI_CONTAINER_TYPE       (RTGUI_TYPE(container))
/** Casts the object to an rtgui_container */
#define RTGUI_CONTAINER(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_CONTAINER_TYPE, rtgui_container_t))
/** Checks if the object is an rtgui_container */
#define RTGUI_IS_CONTAINER(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_CONTAINER_TYPE))

/*
 * the container widget
 */
struct rtgui_container
{
    struct rtgui_widget parent;

    /* layout box */
    struct rtgui_box *layout_box;

    rtgui_list_t children;
};
typedef struct rtgui_container rtgui_container_t;

rtgui_container_t *rtgui_container_create(void);
void rtgui_container_destroy(rtgui_container_t *container);

rt_bool_t rtgui_container_event_handler(struct rtgui_object *widget, struct rtgui_event *event);

/* set layout box */
void rtgui_container_set_box(struct rtgui_container *container, struct rtgui_box *box);
void rtgui_container_layout(struct rtgui_container *container);

void rtgui_container_add_child(rtgui_container_t *container, rtgui_widget_t *child);
void rtgui_container_remove_child(rtgui_container_t *container, rtgui_widget_t *child);
void rtgui_container_destroy_children(rtgui_container_t *container);
rtgui_widget_t *rtgui_container_get_first_child(rtgui_container_t *container);

rt_bool_t rtgui_container_event_handler(struct rtgui_object *widget, rtgui_event_t *event);

rt_bool_t rtgui_container_dispatch_event(rtgui_container_t *container, rtgui_event_t *event);
rt_bool_t rtgui_container_dispatch_mouse_event(rtgui_container_t *container, struct rtgui_event_mouse *event);

struct rtgui_object* rtgui_container_get_object(struct rtgui_container *container, rt_uint32_t id);
#ifdef __cplusplus
}
#endif

#endif
