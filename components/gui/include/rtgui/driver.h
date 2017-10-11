/*
 * File      : driver.h
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
 * 2009-10-04     Bernard      first version
 */
#ifndef __RTGUI_DRIVER_H__
#define __RTGUI_DRIVER_H__

#include <rtgui/list.h>
#include <rtgui/color.h>

/* graphic driver operations */
struct rtgui_graphic_driver_ops
{
    /* set and get pixel in (x, y) */
    void (*set_pixel)(rtgui_color_t *c, int x, int y);
    void (*get_pixel)(rtgui_color_t *c, int x, int y);

    void (*draw_hline)(rtgui_color_t *c, int x1, int x2, int y);
    void (*draw_vline)(rtgui_color_t *c, int x , int y1, int y2);

    /* draw raw hline */
    void (*draw_raw_hline)(rt_uint8_t *pixels, int x1, int x2, int y);
};

/* graphic extension operations */
struct rtgui_graphic_ext_ops
{
    /* some 2D operations */
    void (*draw_line)(rtgui_color_t *c, int x1, int y1, int x2, int y2);

    void (*draw_rect)(rtgui_color_t *c, int x1, int y1, int x2, int y2);
    void (*fill_rect)(rtgui_color_t *c, int x1, int y1, int x2, int y2);

    void (*draw_circle)(rtgui_color_t *c, int x, int y, int r);
    void (*fill_circle)(rtgui_color_t *c, int x, int y, int r);

    void (*draw_ellipse)(rtgui_color_t *c, int x, int y, int rx, int ry);
    void (*fill_ellipse)(rtgui_color_t *c, int x, int y, int rx, int ry);
};

struct rtgui_graphic_driver
{
    /* pixel format and byte per pixel */
    rt_uint8_t pixel_format;
    rt_uint8_t bits_per_pixel;
    rt_uint16_t pitch;

    /* screen width and height */
    rt_uint16_t width;
    rt_uint16_t height;

    /* framebuffer address and ops */
    rt_uint8_t *framebuffer;
    struct rt_device* device;

    const struct rtgui_graphic_driver_ops *ops;
    const struct rtgui_graphic_ext_ops *ext_ops;
};

struct rtgui_graphic_driver *rtgui_graphic_driver_get_default(void);

void rtgui_graphic_driver_get_rect(const struct rtgui_graphic_driver *driver, rtgui_rect_t *rect);
void rtgui_graphic_driver_screen_update(const struct rtgui_graphic_driver *driver, rtgui_rect_t *rect);
rt_uint8_t *rtgui_graphic_driver_get_framebuffer(const struct rtgui_graphic_driver *driver);

rt_err_t rtgui_graphic_set_device(rt_device_t device);
void rtgui_graphic_driver_set_framebuffer(void *fb);

rt_inline struct rtgui_graphic_driver *rtgui_graphic_get_device()
{
    return rtgui_graphic_driver_get_default();
}

#ifdef RTGUI_USING_HW_CURSOR
/*
 * hardware cursor
 */
enum rtgui_cursor_type
{
    RTGUI_CURSOR_ARROW,
    RTGUI_CURSOR_HAND,
};

void rtgui_cursor_set_device(const char* device_name);
void rtgui_cursor_set_position(rt_uint16_t x, rt_uint16_t y);
void rtgui_cursor_set_image(enum rtgui_cursor_type type);
#endif

#ifdef RTGUI_USING_VFRAMEBUFFER
void rtgui_graphic_driver_vmode_enter(void);
void rtgui_graphic_driver_vmode_exit(void);
struct rtgui_dc* rtgui_graphic_driver_get_rect_buffer(const struct rtgui_graphic_driver *driver, struct rtgui_rect *rect);
#endif

rt_bool_t rtgui_graphic_driver_is_vmode(void);

#endif

