/*
 * File      : tetris_view.c
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-08-14     Yi.Qiu       first version
 */
 
#include <rtthread.h>
#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/view.h>
#include <rtgui/dc.h>
#include "tetris.h"

static rt_err_t _rt_tetris_view_update(rt_tetris_view_t* thiz, rt_tetris_t* tetris);
static rt_err_t _rt_tetris_view_update_next_brick(rt_tetris_view_t* thiz, rt_tetris_t* tetris);
static rt_err_t _rt_tetris_view_update_level(rt_tetris_view_t* thiz, rt_tetris_t* tetris);
static rt_err_t _rt_tetris_view_update_score_and_lines(rt_tetris_view_t* thiz, rt_tetris_t* tetris);

rt_tetris_view_t* rt_tetris_view_create(void* private)
{
	rt_tetris_view_t* thiz;

	RT_ASSERT(private != RT_NULL)

	thiz = (rt_tetris_view_t*)rt_malloc(sizeof(rt_tetris_view_t));
	thiz->width = 96;
	thiz->height = 96;

	thiz->update = _rt_tetris_view_update;
	thiz->update_next_brick = _rt_tetris_view_update_next_brick;
	thiz->update_level = _rt_tetris_view_update_level;
	thiz->update_score_and_lines = _rt_tetris_view_update_score_and_lines;
	thiz->private = private;

	return thiz;
}

rt_err_t rt_tetris_view_destroy(rt_tetris_view_t* thiz)
{
	RT_ASSERT(thiz != RT_NULL);

	rt_free(thiz);

	return RT_EOK;
}

static rt_err_t _rt_tetris_view_update_next_brick(rt_tetris_view_t* thiz, rt_tetris_t* tetris)
{
	struct rtgui_dc* dc;
	struct rtgui_rect rect;
	rt_uint32_t width;
	rt_uint32_t ppb, i;
	rtgui_widget_t* widget;
	rt_uint32_t* next_brick;

	RT_ASSERT(thiz != RT_NULL);
	RT_ASSERT(tetris != RT_NULL);

	next_brick = rt_tetris_next_brick(tetris);
	widget = (rtgui_widget_t*)thiz->private;
	width = rt_tetris_width(tetris);
	/* pixel per block */
	ppb = thiz->width / width; 

	dc = rtgui_dc_begin_drawing(widget);
	if (dc == RT_NULL) return -RT_ERROR;

	rect.x1 = 100;
	rect.x2 = rect.x1 + 4 * ppb;
	rect.y1 = 16;
	rect.y2 = rect.y1 + 2 * ppb;

	RTGUI_DC_BC(dc) = RTGUI_RGB(0xff, 0xff, 0xff);
	rtgui_dc_fill_rect(dc, &rect);

	for(i=0; i<4; i++)
	{
		rt_uint32_t y = next_brick[i] / width;
		rt_uint32_t x = next_brick[i] % width;

		rect.x1 = 100 + ppb * (x - 6);
		rect.x2 = rect.x1 + ppb - 1;
		rect.y1 = 16 + ppb * y ;
		rect.y2 = rect.y1 + ppb - 1;

		RTGUI_DC_BC(dc) = RTGUI_RGB(0xff, 0x00, 0x00);
		rtgui_dc_fill_rect(dc, &rect);
	}

	rtgui_dc_end_drawing(dc);

	return RT_EOK;	
}

static rt_err_t _rt_tetris_view_update_level(rt_tetris_view_t* thiz, rt_tetris_t* tetris)
{
	struct rtgui_dc* dc;
	struct rtgui_rect rect;
	rtgui_widget_t* widget;
	char text[4];

	RT_ASSERT(thiz != RT_NULL);
	RT_ASSERT(tetris != RT_NULL);

	widget = (rtgui_widget_t*)thiz->private;
	dc = rtgui_dc_begin_drawing(widget);
	if (dc == RT_NULL) return -RT_ERROR;

	rect.x1 = 96;
	rect.y1 = 42;
	rect.x2 = 128;
	rect.y2 = rect.y1 + 10;
	RTGUI_DC_BC(dc) = RTGUI_RGB(0xff, 0xff, 0xff);
	rtgui_dc_fill_rect(dc, &rect);
	rt_sprintf(text, "%d", rt_tetris_level(tetris));
	RTGUI_DC_BC(dc) = RTGUI_RGB(0xff, 0x00, 0x00);
	rtgui_dc_draw_text(dc, text, &rect);

	/* Redraw panel */	
	rtgui_dc_end_drawing(dc);

	return RT_EOK;	
}

static rt_err_t _rt_tetris_view_update_score_and_lines(rt_tetris_view_t* thiz, rt_tetris_t* tetris)
{
	struct rtgui_dc* dc;
	struct rtgui_rect rect;
	rtgui_widget_t* widget;
	char text[4];

	RT_ASSERT(thiz != RT_NULL);
	RT_ASSERT(tetris != RT_NULL);

	widget = (rtgui_widget_t*)thiz->private;
	dc = rtgui_dc_begin_drawing(widget);
	if (dc == RT_NULL) return -RT_ERROR;

	rect.x1 = 96;
	rect.y1 = 64;
	rect.x2 = 128;
	rect.y2 = rect.y1 + 10;
	RTGUI_DC_BC(dc) = RTGUI_RGB(0xff, 0xff, 0xff);
    	rtgui_dc_fill_rect(dc, &rect);
	rt_sprintf(text, "%d", rt_tetris_lines(tetris));
	RTGUI_DC_BC(dc) = RTGUI_RGB(0xff, 0x00, 0x00);
	rtgui_dc_draw_text(dc, text, &rect);

	rect.y1 += 22;
	rect.y2 = rect.y1 + 10;
	RTGUI_DC_BC(dc) = RTGUI_RGB(0xff, 0xff, 0xff);
	rtgui_dc_fill_rect(dc, &rect);
	rt_sprintf(text, "%d", rt_tetris_score(tetris));
	RTGUI_DC_BC(dc) = RTGUI_RGB(0xff, 0x00, 0x00);
	rtgui_dc_draw_text(dc, text, &rect);

	/* Redraw panel */	
	rtgui_dc_end_drawing(dc);

	return RT_EOK;	
}

static rt_err_t _rt_tetris_view_update(rt_tetris_view_t* thiz, rt_tetris_t* tetris)
{
	struct rtgui_dc* dc;
	struct rtgui_rect rect;
	rt_uint32_t width, height;
	rt_uint32_t j,k, ppb;
	rtgui_widget_t* widget;

	RT_ASSERT(thiz != RT_NULL);
	RT_ASSERT(tetris != RT_NULL);

	widget = (rtgui_widget_t*)thiz->private;
	width = rt_tetris_width(tetris);
	height = rt_tetris_height(tetris);
	ppb = thiz->width / width;

	dc = rtgui_dc_begin_drawing(widget);
	if (dc == RT_NULL) return -RT_ERROR;

	/* Redraw panel */
	for(j=0; j<width; j++)
	{
		for(k=1; k<height; k++)
		{
			rect.x1 = ppb * j;
			rect.x2 = ppb * (j + 1) - 1;
			rect.y1 = ppb * (k - 1);
			rect.y2 = ppb * k - 1;

			if(rt_tetris_check_collision(tetris, k * width + j))
			{
				RTGUI_DC_BC(dc) = RTGUI_RGB(0xff, 0xff, 0xff);
			}
			else
			{
				RTGUI_DC_BC(dc) = RTGUI_RGB(0xff, 0x00, 0x00);
			}

			rtgui_dc_fill_rect(dc, &rect);
		}	
	}

	/* Redraw panel */	
	rtgui_dc_end_drawing(dc);

	return RT_EOK;	
}

