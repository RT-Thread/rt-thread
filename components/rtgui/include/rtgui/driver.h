/*
 * File      : driver.h
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-04     Bernard      first version
 */
#ifndef __RTGUI_DRIVER_H__
#define __RTGUI_DRIVER_H__

#include <rtgui/list.h>
#include <rtgui/color.h>

struct rtgui_graphic_driver_ops
{
	/* set and get pixel in (x, y) */
	void (*set_pixel) (rtgui_color_t *c, int x, int y);
	void (*get_pixel) (rtgui_color_t *c, int x, int y);

	void (*draw_hline)(rtgui_color_t *c, int x1, int x2, int y);
	void (*draw_vline)(rtgui_color_t *c, int x , int y1, int y2);

	/* draw raw hline */
	void (*draw_raw_hline)(rt_uint8_t *pixels, int x1, int x2, int y);
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
	volatile rt_uint8_t *framebuffer;
	rt_device_t device;
	const struct rtgui_graphic_driver_ops *ops;
};

void rtgui_graphic_driver_add(const struct rtgui_graphic_driver* driver);

struct rtgui_graphic_driver* rtgui_graphic_driver_get_default(void);

void rtgui_graphic_driver_get_rect(const struct rtgui_graphic_driver *driver, rtgui_rect_t *rect);
void rtgui_graphic_driver_screen_update(const struct rtgui_graphic_driver* driver, rtgui_rect_t *rect);
rt_uint8_t* rtgui_graphic_driver_get_framebuffer(const struct rtgui_graphic_driver* driver);

rt_err_t rtgui_graphic_set_device(rt_device_t device);

rt_inline struct rtgui_graphic_driver* rtgui_graphic_get_device()
{
	extern struct rtgui_graphic_driver _driver;
	return &_driver;
}

#endif

