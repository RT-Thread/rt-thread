/*
 * File      : dc_buffer.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-04-10     Bernard      first version
 */
#ifndef __RTGUI_DC_HW_H__
#define __RTGUI_DC_HW_H__

#include <rtgui/dc.h>

/* hardware device context */
struct rtgui_dc_hw
{
	struct rtgui_dc parent;

	/* widget owner */
	rtgui_widget_t* owner;

	/* visible */
	rt_bool_t visible;

	/* display driver */
	struct rtgui_graphic_driver* device;
};

/* create a hardware dc */
struct rtgui_dc* rtgui_dc_hw_create(rtgui_widget_t* owner);
struct rtgui_dc* rtgui_dc_begin_drawing(rtgui_widget_t* owner);
void rtgui_dc_end_drawing(struct rtgui_dc* dc);

/* draw a hline with raw pixel data */
void rtgui_dc_hw_draw_raw_hline(struct rtgui_dc_hw* dc, rt_uint8_t* raw_ptr, int x1, int x2, int y);

#endif
