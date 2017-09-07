/*
 * File      : blit.h
 * This file is part of RT-Thread GUI
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
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
 * 2013-10-04     Bernard      porting SDL software render to RT-Thread GUI
 */

/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2013 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef __RTGUI_BLIT_H__
#define __RTGUI_BLIT_H__

#include <rtgui/rtgui.h>

/* Assemble R-G-B values into a specified pixel format and store them */
#define RGB565_FROM_RGB(Pixel, r, g, b)                                 \
{                                                                       \
    Pixel = ((r>>3)<<11)|((g>>2)<<5)|(b>>3);                            \
}
#define BGR565_FROM_RGB(Pixel, r, g, b)                                 \
{                                                                       \
    Pixel = ((b>>3)<<11)|((g>>2)<<5)|(r>>3);                            \
}
#define RGB555_FROM_RGB(Pixel, r, g, b)                                 \
{                                                                       \
    Pixel = ((r>>3)<<10)|((g>>3)<<5)|(b>>3);                            \
}
#define RGB888_FROM_RGB(Pixel, r, g, b)                                 \
{                                                                       \
    Pixel = (r<<16)|(g<<8)|b;                                           \
}
#define ARGB8888_FROM_RGBA(Pixel, r, g, b, a)                           \
{                                                                       \
    Pixel = (a<<24)|(r<<16)|(g<<8)|b;                                   \
}
#define RGBA8888_FROM_RGBA(Pixel, r, g, b, a)                           \
{                                                                       \
    Pixel = (r<<24)|(g<<16)|(b<<8)|a;                                   \
}
#define ABGR8888_FROM_RGBA(Pixel, r, g, b, a)                           \
{                                                                       \
    Pixel = (a<<24)|(b<<16)|(g<<8)|r;                                   \
}
#define BGRA8888_FROM_RGBA(Pixel, r, g, b, a)                           \
{                                                                       \
    Pixel = (b<<24)|(g<<16)|(r<<8)|a;                                   \
}
#define ARGB2101010_FROM_RGBA(Pixel, r, g, b, a)                        \
{                                                                       \
    r = r ? ((r << 2) | 0x3) : 0;                                       \
    g = g ? ((g << 2) | 0x3) : 0;                                       \
    b = b ? ((b << 2) | 0x3) : 0;                                       \
    a = (a * 3) / 255;                                                  \
    Pixel = (a<<30)|(r<<20)|(g<<10)|b;                                  \
}

/* Load pixel of the specified format from a buffer and get its R-G-B values */
#define RGB_FROM_RGB565(Pixel, r, g, b)                                 \
    {                                                                   \
    r = rtgui_blit_expand_byte[3][((Pixel&0xF800)>>11)];                \
    g = rtgui_blit_expand_byte[2][((Pixel&0x07E0)>>5)];                 \
    b = rtgui_blit_expand_byte[3][(Pixel&0x001F)];                      \
}
#define RGB_FROM_BGR565(Pixel, r, g, b)                                 \
    {                                                                   \
    b = rtgui_blit_expand_byte[3][((Pixel&0xF800)>>11)];                \
    g = rtgui_blit_expand_byte[2][((Pixel&0x07E0)>>5)];                 \
    r = rtgui_blit_expand_byte[3][(Pixel&0x001F)];                      \
}
#define RGB_FROM_RGB555(Pixel, r, g, b)                                 \
{                                                                       \
    r = rtgui_blit_expand_byte[3][((Pixel&0x7C00)>>10)];                \
    g = rtgui_blit_expand_byte[3][((Pixel&0x03E0)>>5)];                 \
    b = rtgui_blit_expand_byte[3][(Pixel&0x001F)];                      \
}
#define RGB_FROM_RGB888(Pixel, r, g, b)                                 \
{                                                                       \
    r = ((Pixel&0xFF0000)>>16);                                         \
    g = ((Pixel&0xFF00)>>8);                                            \
    b = (Pixel&0xFF);                                                   \
}

#define RGBA_FROM_RGBA8888(Pixel, r, g, b, a)                           \
{                                                                       \
    r = (Pixel>>24);                                                    \
    g = ((Pixel>>16)&0xFF);                                             \
    b = ((Pixel>>8)&0xFF);                                              \
    a = (Pixel&0xFF);                                                   \
}
#define RGBA_FROM_ARGB8888(Pixel, r, g, b, a)                           \
{                                                                       \
    r = ((Pixel>>16)&0xFF);                                             \
    g = ((Pixel>>8)&0xFF);                                              \
    b = (Pixel&0xFF);                                                   \
    a = (Pixel>>24);                                                    \
}
#define RGBA_FROM_ABGR8888(Pixel, r, g, b, a)                           \
{                                                                       \
    r = (Pixel&0xFF);                                                   \
    g = ((Pixel>>8)&0xFF);                                              \
    b = ((Pixel>>16)&0xFF);                                             \
    a = (Pixel>>24);                                                    \
}
#define RGBA_FROM_BGRA8888(Pixel, r, g, b, a)                           \
{                                                                       \
    r = ((Pixel>>8)&0xFF);                                              \
    g = ((Pixel>>16)&0xFF);                                             \
    b = (Pixel>>24);                                                    \
    a = (Pixel&0xFF);                                                   \
}
#define RGBA_FROM_ARGB2101010(Pixel, r, g, b, a)                        \
{                                                                       \
    r = ((Pixel>>22)&0xFF);                                             \
    g = ((Pixel>>12)&0xFF);                                             \
    b = ((Pixel>>2)&0xFF);                                              \
    a = rtgui_blit_expand_byte[6][(Pixel>>30)];                         \
}

/* 4-times unrolled loop */
#define DUFFS_LOOP4(pixel_copy_increment, width)                        \
{ int n = (width+3)/4;                                                  \
    switch (width & 3) {                                                \
    case 0: do {    pixel_copy_increment;                               \
    case 3:     pixel_copy_increment;                                   \
    case 2:     pixel_copy_increment;                                   \
    case 1:     pixel_copy_increment;                                   \
        } while (--n > 0);                                              \
    }                                                                   \
}

/* 8-times unrolled loop */
#define DUFFS_LOOP8(pixel_copy_increment, width)                        \
{ int n = (width+7)/8;                                                  \
    switch (width & 7) {                                                \
    case 0: do {    pixel_copy_increment;                               \
    case 7:     pixel_copy_increment;                                   \
    case 6:     pixel_copy_increment;                                   \
    case 5:     pixel_copy_increment;                                   \
    case 4:     pixel_copy_increment;                                   \
    case 3:     pixel_copy_increment;                                   \
    case 2:     pixel_copy_increment;                                   \
    case 1:     pixel_copy_increment;                                   \
        } while ( --n > 0 );                                            \
    }                                                                   \
}

/* Use the 8-times version of the loop by default */
#define DUFFS_LOOP(pixel_copy_increment, width)                         \
    DUFFS_LOOP8(pixel_copy_increment, width)

struct rtgui_blit_info
{
    rt_uint8_t *src;
    int src_w, src_h;
    int src_pitch;
    int src_skip;

    rt_uint8_t *dst;
    int dst_w, dst_h;
    int dst_pitch;
    int dst_skip;

    rt_uint8_t src_fmt;
    rt_uint8_t dst_fmt;
    rt_uint8_t r, g, b, a;
};

struct rtgui_blit_info_src
{
	rt_uint8_t *src;
	int src_w, src_h;
	int src_skip;

	rt_uint8_t src_fmt;
};

extern const rt_uint8_t* rtgui_blit_expand_byte[9];

typedef void (*rtgui_blit_line_func)(rt_uint8_t *dst, rt_uint8_t *src, int line);
rtgui_blit_line_func rtgui_blit_line_get(int dst_bpp, int src_bpp);
rtgui_blit_line_func rtgui_blit_line_get_inv(int dst_bpp, int src_bpp);

void rtgui_blit(struct rtgui_blit_info * info);

#endif

