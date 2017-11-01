/*
 * File      : image_hdc.h
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
#ifndef __RTGUI_IMAGE_HDC_H__
#define __RTGUI_IMAGE_HDC_H__

#include <rtgui/image.h>

struct rtgui_image_hdcmm
{
    struct rtgui_image parent;

    /* hdc image information */
    rt_uint16_t byte_per_pixel;
    rt_uint16_t pitch;

    rt_uint8_t *pixels;
};

struct rtgui_image_hdc
{
    rt_bool_t is_loaded;

    /* hdc image information */
    rt_uint16_t byte_per_pixel;
    rt_uint16_t pitch;
    rt_uint8_t  pixel_format;

    rt_size_t   pixel_offset;
    rt_uint8_t *pixels;

    struct rtgui_filerw *filerw;
};

void rtgui_image_hdc_init(void);
extern const struct rtgui_image_engine rtgui_image_hdcmm_engine;

#define HDC_HEADER_SIZE     (5 * 4)
#define RTGUI_IMAGE_HDC_DEF(bpp, w, h, pixels)  \
    {{w, h, &rtgui_image_hdcmm_engine, RT_NULL}, bpp, (bpp * w), ((rt_uint8_t*)pixels + HDC_HEADER_SIZE)}

#endif
