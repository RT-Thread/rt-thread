/*
 * File      : dc.h
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
#ifndef __RTGUI_DC_H__
#define __RTGUI_DC_H__

#include <rtgui/rtgui.h>
#include <rtgui/font.h>
#include <rtgui/driver.h>
#include <rtgui/widgets/widget.h>

enum rtgui_dc_type
{
	RTGUI_DC_HW,
	RTGUI_DC_BUFFER,
	RTGUI_DC_IMLIB2,
};

/* the abstract device context */
struct rtgui_dc
{
	/* type of device context */
	rt_uint32_t type;

	/* interface */
	void (*draw_point)(struct rtgui_dc* dc, int x, int y);
	void (*draw_vline)(struct rtgui_dc* dc, int x, int y1, int y2);
	void (*draw_hline)(struct rtgui_dc* dc, int x1, int x2, int y);
	void (*fill_rect )(struct rtgui_dc* dc, rtgui_rect_t* rect);
	void (*blit		 )(struct rtgui_dc* dc, struct rtgui_point* dc_point, struct rtgui_dc* dest, rtgui_rect_t* rect);

	/* set and get color */
	void (*set_color )(struct rtgui_dc* dc, rtgui_color_t color);
	rtgui_color_t (*get_color)(struct rtgui_dc* dc);

	/* set and get font */
	void (*set_font  )(struct rtgui_dc* dc, rtgui_font_t* font);
	rtgui_font_t* (*get_font)(struct rtgui_dc* dc);
	void (*set_textalign)(struct rtgui_dc* dc, rt_int32_t align);
	rt_int32_t (*get_textalign)(struct rtgui_dc* dc);

	/* get dc visible */
	rt_bool_t (*get_visible)(struct rtgui_dc* dc);

	/* get dc rect */
	void (*get_rect  )(struct rtgui_dc* dc, rtgui_rect_t* rect);

	rt_bool_t (*fini )(struct rtgui_dc* dc);
};

/* create a buffer dc */
struct rtgui_dc* rtgui_dc_buffer_create(int width, int height);
rt_uint8_t* rtgui_dc_buffer_get_pixel(struct rtgui_dc* dc);

/* destroy a dc */
void rtgui_dc_destory(struct rtgui_dc* dc);

void rtgui_dc_draw_point(struct rtgui_dc* dc, int x, int y);

void rtgui_dc_draw_vline(struct rtgui_dc* dc, int x, int y1, int y2);
void rtgui_dc_draw_hline(struct rtgui_dc* dc, int x1, int x2, int y);
void rtgui_dc_fill_rect (struct rtgui_dc* dc, struct rtgui_rect* rect);
void rtgui_dc_blit(struct rtgui_dc* dc, struct rtgui_point* dc_point, struct rtgui_dc* dest, rtgui_rect_t* rect);

void rtgui_dc_set_color(struct rtgui_dc* dc, rtgui_color_t color);
rtgui_color_t rtgui_dc_get_color(struct rtgui_dc* dc);

void rtgui_dc_set_font(struct rtgui_dc* dc, rtgui_font_t* font);
rtgui_font_t* rtgui_dc_get_font(struct rtgui_dc* dc);
void rtgui_dc_set_textalign(struct rtgui_dc* dc, rt_int32_t align);
rt_int32_t rtgui_dc_get_textalign(struct rtgui_dc* dc);

rt_bool_t rtgui_dc_get_visible(struct rtgui_dc* dc);
void rtgui_dc_get_rect(struct rtgui_dc*dc, rtgui_rect_t* rect);

void rtgui_dc_draw_line (struct rtgui_dc* dc, int x1, int y1, int x2, int y2);
void rtgui_dc_draw_rect (struct rtgui_dc* dc, struct rtgui_rect* rect);
void rtgui_dc_draw_round_rect(struct rtgui_dc* dc, struct rtgui_rect* rect);

void rtgui_dc_draw_text (struct rtgui_dc* dc, const char* text, struct rtgui_rect* rect);
void rtgui_dc_draw_byte(struct rtgui_dc*dc, int x, int y, int h, const rt_uint8_t* data);
void rtgui_dc_draw_word(struct rtgui_dc*dc, int x, int y, int h, const rt_uint8_t* data);

void rtgui_dc_draw_border(struct rtgui_dc* dc, rtgui_rect_t* rect, int flag);
void rtgui_dc_draw_horizontal_line(struct rtgui_dc* dc, int x1, int x2, int y);
void rtgui_dc_draw_vertical_line(struct rtgui_dc* dc, int x, int y1, int y2);
void rtgui_dc_draw_arrow(struct rtgui_dc* dc, rtgui_rect_t* rect, int kind);
void rtgui_dc_draw_focus_rect(struct rtgui_dc* dc, rtgui_rect_t* rect);

void rtgui_dc_draw_polygon(struct rtgui_dc* dc, const int *vx, const int *vy, int count);
void rtgui_dc_fill_polygon(struct rtgui_dc* dc, const int* vx, const int* vy, int count);

void rtgui_dc_draw_circle(struct rtgui_dc* dc, int x, int y, int r);
void rtgui_dc_fill_circle(struct rtgui_dc* dc, rt_int16_t x, rt_int16_t y, rt_int16_t r);
void rtgui_dc_draw_arc(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t r, rt_int16_t start, rt_int16_t end);

void rtgui_dc_draw_ellipse(struct rtgui_dc* dc, rt_int16_t x, rt_int16_t y, rt_int16_t rx, rt_int16_t ry);
void rtgui_dc_fill_ellipse(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t rx, rt_int16_t ry);

#endif
