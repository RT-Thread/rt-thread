/*
 * File      : image_container.h
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
 * 2010-04-10     Bernard      first version
 */

#ifndef __RTGUI_IMAGE_CONTAINER_H__
#define __RTGUI_IMAGE_CONTAINER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtgui/rtgui.h>
#include <rtgui/image.h>

#if defined(RTGUI_IMAGE_CONTAINER)
/* image item in image container */
struct rtgui_image_item
{
    rtgui_image_t *image;
    char *filename;

    rt_uint32_t refcount;
};
typedef struct rtgui_image_item rtgui_image_item_t;

void rtgui_system_image_container_init(void);

struct rtgui_image_item *rtgui_image_container_get(const char *filename);
void rtgui_image_container_put(struct rtgui_image_item *item);

#endif

#ifdef __cplusplus
}
#endif

#endif

