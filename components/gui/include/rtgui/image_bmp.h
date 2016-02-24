/*
 * File      : image_bmp.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
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
