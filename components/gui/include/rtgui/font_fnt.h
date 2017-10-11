/*
 * File      : font_fnt.h
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

#ifndef __FONT_FNT_H__
#define __FONT_FNT_H__

#include <rtgui/font.h>
#include <rtgui/dc.h>

/* fnt font header */
struct fnt_header
{
    rt_uint8_t version[4];
    rt_uint16_t max_width;
    rt_uint16_t height;
    rt_uint16_t ascent;
    rt_uint16_t depth;

    rt_uint32_t first_char;
    rt_uint32_t default_char;
    rt_uint32_t size;
    rt_uint32_t nbits;
    rt_uint32_t noffset;
    rt_uint32_t nwidth;
};
typedef rt_uint8_t MWIMAGEBITS;

struct fnt_font
{
    struct fnt_header header;

    const MWIMAGEBITS *bits;   /* nbits */
    const rt_uint16_t *offset; /* noffset */
    const rt_uint8_t  *width;  /* nwidth */
};
extern const struct rtgui_font_engine fnt_font_engine;

struct rtgui_font *fnt_font_create(const char* filename);

#endif

