/*
 * File      : color.h
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
 * 2012-01-24     onelife      add mono color support
 */
#ifndef __RTGUI_COLOR_H__
#define __RTGUI_COLOR_H__

#include <rtgui/rtgui.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The color used in the GUI:
 *
 *         bit        bit
 * RGB565  15 R,G,B   0
 * BGR565  15 B,G,R   0
 * RGB888  23 R,G,B   0
 * ARGB888 31 A,R,G,B 0
 * RGBA888 31 R,G,B,A 0
 * ABGR888 31 A,B,G,R 0
 *
 * The rtgui_color is defined as ARGB888.
 *        bit31 A,R,G,B bit0
 */
#define RTGUI_ARGB(a, r, g, b)  \
        ((rtgui_color_t)(((rt_uint8_t)(b)|\
        (((unsigned long)(rt_uint8_t)(g))<<8))|\
        (((unsigned long)(rt_uint8_t)(r))<<16)|\
        (((unsigned long)(rt_uint8_t)(a))<<24)))
#define RTGUI_RGB(r, g, b)  RTGUI_ARGB(255, (r), (g), (b))

#define RTGUI_RGB_B(c)  ((c) & 0xff)
#define RTGUI_RGB_G(c)  (((c) >> 8)  & 0xff)
#define RTGUI_RGB_R(c)  (((c) >> 16) & 0xff)
#define RTGUI_RGB_A(c)  (((c) >> 24) & 0xff)

extern const rtgui_color_t default_foreground;
extern const rtgui_color_t default_background;

/* it's better use these color definitions */
#define RED                RTGUI_RGB(0xff, 0x00, 0x00)
#define GREEN              RTGUI_RGB(0x00, 0xff, 0x00)
#define BLUE               RTGUI_RGB(0x00, 0x00, 0xff)
#define BLACK              RTGUI_RGB(0x00, 0x00, 0x00)
#define WHITE              RTGUI_RGB(0xff, 0xff, 0xff)
#define HIGH_LIGHT         RTGUI_RGB(0xfc, 0xfc, 0xfc)
#define DARK_GREY          RTGUI_RGB(0x7f, 0x7f, 0x7f)
#define LIGHT_GREY         RTGUI_RGB(0xc0, 0xc0, 0xc0)
#define TRANSPARENT        RTGUI_ARGB(0, 0, 0, 0)

extern const rtgui_color_t red;
extern const rtgui_color_t green;
extern const rtgui_color_t blue;
extern const rtgui_color_t black;
extern const rtgui_color_t white;
extern const rtgui_color_t high_light;
extern const rtgui_color_t dark_grey;
extern const rtgui_color_t light_grey;

/*
 * RTGUI default color format: ARGB
 * AAAA AAAA RRRR RRRR GGGG GGGG BBBB BBBB
 * 31                                    0
 */

/* convert rtgui color to mono */
rt_inline rt_uint8_t rtgui_color_to_mono(rtgui_color_t c)
{
    rt_uint8_t pixel;

    pixel = (RTGUI_RGB_R(c) | RTGUI_RGB_G(c) | RTGUI_RGB_B(c)) ? 0x01 : 0x00;
    return pixel;
}

rt_inline rtgui_color_t rtgui_color_from_mono(rt_uint8_t pixel)
{
    rtgui_color_t color;

    if (pixel)
    {
        color = white;
    }
    else
    {
        color = black;
    }
    return color;
}

/* convert rtgui color to RRRRRGGGGGGBBBBB */
rt_inline rt_uint16_t rtgui_color_to_565(rtgui_color_t c)
{
    rt_uint16_t pixel;

    pixel = (rt_uint16_t)(((RTGUI_RGB_R(c) >> 3) << 11) | ((RTGUI_RGB_G(c) >> 2) << 5) | (RTGUI_RGB_B(c) >> 3));

    return pixel;
}

rt_inline rtgui_color_t rtgui_color_from_565(rt_uint16_t pixel)
{
    rt_uint16_t r, g, b;
    rtgui_color_t color;

    r = (pixel >> 11) & 0x1f;
    g = (pixel >> 5)  & 0x3f;
    b = pixel & 0x1f;

    color = b * 255 / 31 + ((g * 255 / 63) << 8) + ((r * 255 / 31) << 16);

    return color;
}

/* convert rtgui color to BBBBBGGGGGGRRRRR */
rt_inline rt_uint16_t rtgui_color_to_565p(rtgui_color_t c)
{
    rt_uint16_t pixel;

    pixel = (rt_uint16_t)(((RTGUI_RGB_B(c) >> 3) << 11) | ((RTGUI_RGB_G(c) >> 2) << 5) | (RTGUI_RGB_R(c) >> 3));
    return pixel;
}

rt_inline rtgui_color_t rtgui_color_from_565p(rt_uint16_t pixel)
{
    rt_uint8_t r, g, b;
    rtgui_color_t color;

    r = pixel & 0x1f;
    g = (pixel >> 5) & 0x3f;
    b = (pixel >> 11) & 0x1f;

    color = b * 255 / 31 + ((g * 255 / 63) << 8) + ((r * 255 / 31) << 16);

    return color;
}

/* convert rtgui color to RGB */
rt_inline rt_uint32_t rtgui_color_to_888(rtgui_color_t c)
{
    rt_uint32_t pixel;

    pixel = RTGUI_RGB_R(c) << 16 | RTGUI_RGB_G(c) << 8 | RTGUI_RGB_B(c);
    return pixel;
}

rt_inline rtgui_color_t rtgui_color_from_888(rt_uint32_t pixel)
{
    rtgui_color_t color;

    color = RTGUI_RGB(((pixel >> 16) & 0xff), ((pixel >> 8) & 0xff), pixel & 0xff);

    return color;
}

/* get the bits of specified pixle format */
rt_uint8_t rtgui_color_get_bits(rt_uint8_t pixel_format) RTGUI_PURE;
/* get the bytes of specified pixle format */
rt_uint8_t rtgui_color_get_bpp(rt_uint8_t pixel_format) RTGUI_PURE;

#ifdef __cplusplus
}
#endif

#endif

