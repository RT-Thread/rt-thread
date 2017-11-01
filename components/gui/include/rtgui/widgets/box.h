/*
 * File      : box.h
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
#ifndef __RTGUI_BOX_H__
#define __RTGUI_BOX_H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/container.h>

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_CLASS_TYPE(box);

/** Gets the type of a box */
#define RTGUI_BOX_TYPE       (RTGUI_TYPE(box))
/** Casts the object to an rtgui_box */
#define RTGUI_BOX(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_BOX_TYPE, rtgui_box_t))
/** Checks if the object is an rtgui_box */
#define RTGUI_IS_BOX(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_BOX_TYPE))

struct rtgui_box
{
    struct rtgui_object parent;

    rt_uint16_t orient;
    rt_uint16_t border_size;

    struct rtgui_container *container;
};
typedef struct rtgui_box rtgui_box_t;

struct rtgui_box *rtgui_box_create(int orientation, int border_size);
void rtgui_box_destroy(struct rtgui_box *box);

void rtgui_box_layout(rtgui_box_t *box);
void rtgui_box_layout_rect(rtgui_box_t *box, struct rtgui_rect *rect);

#ifdef __cplusplus
}
#endif

#endif
