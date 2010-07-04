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

struct rtgui_graphic_driver
{
	/* driver name */
	char* name;

	/* byte per pixel */
	rt_uint16_t byte_per_pixel;

	/* screen width and height */
	rt_uint16_t width;
	rt_uint16_t height;

	/* screen update */
	void (*screen_update)(rtgui_rect_t* rect);

	/* get video frame buffer */
	rt_uint8_t* (*get_framebuffer)(void);

	/* set and get pixel in (x, y) */
	void (*set_pixel) (rtgui_color_t *c, rt_base_t x, rt_base_t y);
	void (*get_pixel) (rtgui_color_t *c, rt_base_t x, rt_base_t y);

	void (*draw_hline)(rtgui_color_t *c, rt_base_t x1, rt_base_t x2, rt_base_t y);
	void (*draw_vline)(rtgui_color_t *c, rt_base_t x , rt_base_t y1, rt_base_t y2);

	/* draw raw hline */
	void (*draw_raw_hline)(rt_uint8_t *pixels, rt_base_t x1, rt_base_t x2, rt_base_t y);

	/* the driver list */
	rtgui_list_t list;
};

#ifdef RTGUI_USING_GRAPHIC_DRIVER_LIST
void rtgui_graphic_driver_add(struct rtgui_graphic_driver* driver);
void rtgui_graphic_driver_remove(struct rtgui_graphic_driver* driver);

struct rtgui_graphic_driver* rtgui_graphic_driver_find(char* name);
#else
void rtgui_graphic_driver_add(const struct rtgui_graphic_driver* driver);
#endif

const struct rtgui_graphic_driver* rtgui_graphic_driver_get_default(void);

void rtgui_graphic_driver_get_rect(const struct rtgui_graphic_driver *driver, rtgui_rect_t *rect);
void rtgui_graphic_driver_get_default_rect(rtgui_rect_t *rect);

#endif

