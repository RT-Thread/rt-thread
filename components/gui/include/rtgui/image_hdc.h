/*
 * File      : image_xpm.h
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

void rtgui_image_hdc_init(void);
extern const struct rtgui_image_engine rtgui_image_hdcmm_engine;

#define HDC_HEADER_SIZE     (5 * 4)
#define RTGUI_IMAGE_HDC_DEF(bpp, w, h, pixels)  \
    {{w, h, &rtgui_image_hdcmm_engine, RT_NULL}, bpp, (bpp * w), ((rt_uint8_t*)pixels + HDC_HEADER_SIZE)}

#endif
