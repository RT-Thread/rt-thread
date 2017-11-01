/*
 * File      : image_bmp.h
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
 * 2010-08-10     Bernard      first version
 */
#ifndef __RTGUI_IMAGE_BMP_H__
#define __RTGUI_IMAGE_BMP_H__

#pragma pack(push)
#pragma pack(2)

struct rtgui_image_bmp_header
{
    /* The Win32 BMP file header (14 bytes) */
    rt_uint16_t bfType;
    rt_uint32_t bfSize;
    rt_uint16_t bfReserved1;
    rt_uint16_t bfReserved2;
    rt_uint32_t bfOffBits;

    /* The Win32 BITMAPINFOHEADER struct (40 bytes) */
    rt_uint32_t biSize;
    rt_int32_t  biWidth;
    rt_int32_t  biHeight;
    rt_uint16_t biPlanes;
    rt_uint16_t biBitCount;
    rt_uint32_t biCompression;
    rt_uint32_t biSizeImage;
    rt_int32_t  biXPelsPerMeter;
    rt_int32_t  biYPelsPerMeter;
    rt_uint32_t biClrUsed;
    rt_uint32_t biClrImportant;
};
#pragma pack(pop)

void rtgui_image_bmp_init(void);

#endif
