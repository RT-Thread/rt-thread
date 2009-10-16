/*
 * File      : caret.c
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
#include <rtgui/dc.h>
#include <rtgui/caret.h>
#include <rtgui/rtgui_system.h>

#define RTGUI_CARET_WIDTH	2

#ifdef __WIN32__
#define RTGUI_CARET_BLINK	300
#else
#define RTGUI_CARET_BLINK	30
#endif

static void rtgui_caret_blink(struct rtgui_timer* timer, void* parameter)
{
	struct rtgui_caret* caret;
	rtgui_widget_t* widget;

	caret = (struct rtgui_caret*)parameter;

	RT_ASSERT(caret != RT_NULL);

	if (caret->owner == RT_NULL) return;

	/* caret's owner is visible? */
	widget = caret->owner;
	do
	{
		if (RTGUI_WIDGET_IS_HIDE(widget) == RT_TRUE) return;

		widget = widget->parent;
	} while (widget != RT_NULL);

	if (caret->is_show == RT_TRUE)
	{
		/* set to false */
		caret->is_show = RT_FALSE;

		/* update owner widget */
		if (caret->owner != RT_NULL)
		{
			rtgui_widget_update(caret->owner);
		}
	}
	else
	{
		/* set to true */
		caret->is_show = RT_TRUE;

		/* draw caret */
		rtgui_caret_draw(caret);
	}
}

struct rtgui_caret* rtgui_caret_create(struct rtgui_widget* owner)
{
	struct rtgui_caret* caret;

	RT_ASSERT(owner != RT_NULL);

	caret = (struct rtgui_caret*)rtgui_malloc(sizeof(struct rtgui_caret));
	if (caret != RT_NULL)
	{
		caret->is_show = RT_FALSE;

		caret->extent.x1 = 0;
		caret->extent.y1 = 0;
		caret->extent.x2 = RTGUI_CARET_WIDTH;
		caret->extent.y2 = owner->gc.font->height;
		caret->owner = owner;

		caret->dc = (struct rtgui_dc*)rtgui_dc_buffer_create(RTGUI_CARET_WIDTH, caret->extent.y2);
		if (caret->dc == RT_NULL) goto __exit;

		rtgui_dc_set_color(caret->dc, black);
		rtgui_dc_fill_rect(caret->dc, &(caret->extent));

		caret->timer_period = RTGUI_CARET_BLINK;
		caret->timer = rtgui_timer_create(caret->timer_period,
			RT_TIMER_FLAG_PERIODIC,
			rtgui_caret_blink, caret);
		if (caret->timer == RT_NULL) goto __exit_dc;

		caret->show_point.x = 0;
		caret->show_point.y = 0;
	}

	return caret;

__exit_dc:
	rtgui_dc_destory(caret->dc);
__exit:
	rtgui_free(caret);
	return RT_NULL;
}

void rtgui_caret_destroy(struct rtgui_caret* caret)
{
	RT_ASSERT(caret != RT_NULL);

	if (caret->is_show == RT_TRUE)
	{
		/* stop timer */
		rtgui_timer_stop(caret->timer);
	}

	caret->owner = RT_NULL;
	rtgui_dc_destory(caret->dc);
	rtgui_timer_destory(caret->timer);

	rtgui_free(caret);
}

/* show caret on owner widget logic position */
void rtgui_caret_show(struct rtgui_caret* caret, rt_base_t x, rt_base_t y)
{
	if (caret->is_show == RT_TRUE)
	{
		/* set show flag and stop blink timer */
		caret->is_show = RT_FALSE;
		rtgui_timer_stop(caret->timer);
	}

	/* set show x and y */
	caret->show_point.x = x;
	caret->show_point.y = y;

	/* set show flag and start blink timer */
	caret->is_show = RT_TRUE;

	/* draw caret */
	rtgui_caret_draw(caret);

	/* start blink timer */
	rtgui_timer_start(caret->timer);
}

void rtgui_caret_hide(struct rtgui_caret* caret)
{
	RT_ASSERT(caret != RT_NULL);

	/* set show flag and stop blink timer */
	caret->is_show = RT_FALSE;
	rtgui_timer_stop(caret->timer);

	/* update owner widget */
	if (caret->owner != RT_NULL)
	{
		rtgui_widget_update(caret->owner);
	}
}

void rtgui_caret_set_point(struct rtgui_caret* caret, int x, int y)
{
	RT_ASSERT(caret != RT_NULL);

	if (caret->is_show == RT_TRUE)
	{
		/* stop the old caret */
		rtgui_timer_stop(caret->timer);
		/* update owner widget */
		if (caret->owner != RT_NULL && caret->is_show)
		{
			rtgui_widget_update(caret->owner);
		}
	}

	caret->show_point.x = x;
	caret->show_point.y = y;

	/* draw caret */
	rtgui_caret_draw(caret);

	/* start blink timer */
	rtgui_timer_start(caret->timer);
}

void rtgui_caret_set_box(struct rtgui_caret* caret, int w, int h)
{
	RT_ASSERT(caret != RT_NULL);

	caret->extent.x2 = caret->extent.x1 + w;
	caret->extent.y2 = caret->extent.y1 + h;
}

void rtgui_caret_draw(struct rtgui_caret* caret)
{
	RT_ASSERT(caret != RT_NULL);

	if (caret->is_show == RT_TRUE && caret->owner->toplevel != RT_NULL)
	{
		struct rtgui_rect rect = caret->extent;
		struct rtgui_point point = {0, 0};
		struct rtgui_dc* hw_dc;

		rtgui_rect_moveto(&rect, caret->show_point.x, caret->show_point.y);
		hw_dc = rtgui_dc_begin_drawing(caret->owner);
		rtgui_dc_blit(caret->dc, &point, hw_dc, &rect);
		rtgui_dc_end_drawing(hw_dc);
	}
}

