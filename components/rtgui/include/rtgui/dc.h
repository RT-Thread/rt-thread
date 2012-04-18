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
	RTGUI_DC_CLIENT,
	RTGUI_DC_BUFFER,
};

struct rtgui_dc_engine
{
	/* interface */
	void (*draw_point)(struct rtgui_dc* dc, int x, int y);
	void (*draw_color_point)(struct rtgui_dc* dc, int x, int y, rtgui_color_t color);
	void (*draw_vline)(struct rtgui_dc* dc, int x, int y1, int y2);
	void (*draw_hline)(struct rtgui_dc* dc, int x1, int x2, int y);
	void (*fill_rect )(struct rtgui_dc* dc, rtgui_rect_t* rect);
	void (*blit_line) (struct rtgui_dc* dc, int x1, int x2, int y, rt_uint8_t* line_data);
	void (*blit		 )(struct rtgui_dc* dc, struct rtgui_point* dc_point, struct rtgui_dc* dest, rtgui_rect_t* rect);

	/* set and get graphic context */
	void (*set_gc)(struct rtgui_dc* dc, struct rtgui_gc *gc);
	struct rtgui_gc* (*get_gc)(struct rtgui_dc* dc);

	/* get dc visible */
	rt_bool_t (*get_visible)(struct rtgui_dc* dc);

	/* get dc rect */
	void (*get_rect  )(struct rtgui_dc* dc, rtgui_rect_t* rect);

	rt_bool_t (*fini )(struct rtgui_dc* dc);
};

/* the abstract device context */
struct rtgui_dc
{
	/* type of device context */
	rt_uint32_t type;

	/* dc engine */
	const struct rtgui_dc_engine* engine;
};

#define RTGUI_DC_FC(dc)			(rtgui_dc_get_gc(dc)->foreground)
#define RTGUI_DC_BC(dc)			(rtgui_dc_get_gc(dc)->background)
#define RTGUI_DC_FONT(dc)		(rtgui_dc_get_gc(dc)->font)
#define RTGUI_DC_TEXTALIGN(dc)	(rtgui_dc_get_gc(dc)->textalign)

/* create a buffer dc */
struct rtgui_dc* rtgui_dc_buffer_create(int width, int height);
rt_uint8_t* rtgui_dc_buffer_get_pixel(struct rtgui_dc* dc);

/* begin and end a drawing */
struct rtgui_dc* rtgui_dc_begin_drawing(rtgui_widget_t* owner);
void rtgui_dc_end_drawing(struct rtgui_dc* dc);

/* destroy a dc */
void rtgui_dc_destory(struct rtgui_dc* dc);

void rtgui_dc_draw_line (struct rtgui_dc* dc, int x1, int y1, int x2, int y2);
void rtgui_dc_draw_rect (struct rtgui_dc* dc, struct rtgui_rect* rect);
void rtgui_dc_fill_rect_forecolor(struct rtgui_dc* dc, struct rtgui_rect* rect);
void rtgui_dc_draw_round_rect(struct rtgui_dc* dc, struct rtgui_rect* rect, int r);
void rtgui_dc_fill_round_rect(struct rtgui_dc* dc, struct rtgui_rect* rect, int r);
void rtgui_dc_draw_annulus(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t r1, rt_int16_t r2, rt_int16_t start, rt_int16_t end);
void rtgui_dc_draw_sector(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t r, rt_int16_t start, rt_int16_t end);
void rtgui_dc_fill_sector(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t r, rt_int16_t start, rt_int16_t end);

void rtgui_dc_draw_text (struct rtgui_dc* dc, const char* text, struct rtgui_rect* rect);

void rtgui_dc_draw_mono_bmp(struct rtgui_dc* dc, int x, int y, int w, int h, const rt_uint8_t* data);
void rtgui_dc_draw_byte(struct rtgui_dc*dc, int x, int y, int h, const rt_uint8_t* data);
void rtgui_dc_draw_word(struct rtgui_dc*dc, int x, int y, int h, const rt_uint8_t* data);

void rtgui_dc_draw_border(struct rtgui_dc* dc, rtgui_rect_t* rect, int flag);
void rtgui_dc_draw_horizontal_line(struct rtgui_dc* dc, int x1, int x2, int y);
void rtgui_dc_draw_vertical_line(struct rtgui_dc* dc, int x, int y1, int y2);
void rtgui_dc_draw_focus_rect(struct rtgui_dc* dc, rtgui_rect_t* rect);

void rtgui_dc_draw_polygon(struct rtgui_dc* dc, const int *vx, const int *vy, int count);
void rtgui_dc_fill_polygon(struct rtgui_dc* dc, const int* vx, const int* vy, int count);

void rtgui_dc_draw_circle(struct rtgui_dc* dc, int x, int y, int r);
void rtgui_dc_fill_circle(struct rtgui_dc* dc, rt_int16_t x, rt_int16_t y, rt_int16_t r);
void rtgui_dc_draw_arc(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t r, rt_int16_t start, rt_int16_t end);

void rtgui_dc_draw_ellipse(struct rtgui_dc* dc, rt_int16_t x, rt_int16_t y, rt_int16_t rx, rt_int16_t ry);
void rtgui_dc_fill_ellipse(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t rx, rt_int16_t ry);

/*
 * dc inline function
 *
 * Note:
 * In order to improve drawing speed, put most of common function of dc to inline
 */

/*
 * draw a point on dc
 */
rt_inline void rtgui_dc_draw_point(struct rtgui_dc* dc, int x, int y)
{
	dc->engine->draw_point(dc, x, y);
}

/*
 * draw a color point on dc
 */
rt_inline void rtgui_dc_draw_color_point(struct rtgui_dc* dc, int x, int y, rtgui_color_t color)
{
	dc->engine->draw_color_point(dc, x, y, color);
}

/*
 * draw a vertical line on dc
 */
rt_inline void rtgui_dc_draw_vline(struct rtgui_dc* dc, int x, int y1, int y2)
{
	dc->engine->draw_vline(dc, x, y1, y2);
}

/*
 * draw a horizontal line on dc
 */
rt_inline void rtgui_dc_draw_hline(struct rtgui_dc* dc, int x1, int x2, int y)
{
	dc->engine->draw_hline(dc, x1, x2, y);
}

/*
 * fill a rect with background color 
 */
rt_inline void rtgui_dc_fill_rect (struct rtgui_dc* dc, struct rtgui_rect* rect)
{
	dc->engine->fill_rect(dc, rect);
}

/*
 * blit a dc on hardware dc
 */
rt_inline void rtgui_dc_blit(struct rtgui_dc* dc, struct rtgui_point* dc_point, struct rtgui_dc* dest, rtgui_rect_t* rect)
{
	dc->engine->blit(dc, dc_point, dest, rect);
}

/*
 * set gc of dc
 */
rt_inline void rtgui_dc_set_gc(struct rtgui_dc* dc, rtgui_gc_t* gc)
{
	dc->engine->set_gc(dc, gc);
}

/*
 * get gc of dc
 */
rt_inline rtgui_gc_t *rtgui_dc_get_gc(struct rtgui_dc* dc)
{
	return dc->engine->get_gc(dc);
}

/*
 * get visible status of dc 
 */
rt_inline rt_bool_t rtgui_dc_get_visible(struct rtgui_dc* dc)
{
	return dc->engine->get_visible(dc);
}

/*
 * get rect of dc
 */
rt_inline void rtgui_dc_get_rect(struct rtgui_dc*dc, rtgui_rect_t* rect)
{
	dc->engine->get_rect(dc, rect);
}

#endif
