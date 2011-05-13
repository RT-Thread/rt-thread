/*
 * File      : scrollbar.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-08-09     Bernard      first version
 */
#include <rtgui/dc.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/scrollbar.h>

static void _rtgui_scrollbar_constructor(rtgui_scrollbar_t *bar)
{
	struct rtgui_rect rect = {0, 0, RTGUI_DEFAULT_SB_WIDTH, RTGUI_DEFAULT_SB_HEIGHT};

	/* set event handler */
	rtgui_widget_set_event_handler(RTGUI_WIDGET(bar), rtgui_scrollbar_event_handler);

	rtgui_scrollbar_set_range(bar, 0, 100);
	rtgui_scrollbar_set_page_step(bar, 20);
	rtgui_scrollbar_set_line_step(bar, 10);

	bar->status = 0;
	bar->thumb_position = 0;
	bar->thumb_size = 16;
	bar->on_scroll = RT_NULL;

	bar->orient = RTGUI_HORIZONTAL;
	rtgui_widget_set_rect(RTGUI_WIDGET(bar), &rect);

	/* set gc */
	RTGUI_WIDGET_TEXTALIGN(RTGUI_WIDGET(bar)) = RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL;
}

rt_inline rt_uint32_t _rtgui_scrollbar_get_length(rtgui_scrollbar_t *bar)
{
	struct rtgui_rect rect;

	rtgui_widget_get_rect(RTGUI_WIDGET(bar), &rect);

	if (bar->orient & RTGUI_VERTICAL)
		return rect.y2 - 2 * (rect.x2 - rect.x1);

	return rect.x2 - 2 * (rect.y2 - rect.y1);
}

rt_inline rt_uint32_t _rtgui_scrollbar_get_thumb_position(rtgui_scrollbar_t* bar)
{
	rt_uint32_t thumb_position;

	/* calculate thumb position */
	thumb_position = (rtgui_scrollbar_get_value(bar) - bar->min_position) * _rtgui_scrollbar_get_length(bar) / 
		(bar->max_position - bar->min_position);

	return thumb_position;
}

void rtgui_scrollbar_get_thumb_rect(rtgui_scrollbar_t *bar, rtgui_rect_t *rect)
{
	struct rtgui_rect scrollbar_rect;

	rtgui_widget_get_rect(RTGUI_WIDGET(bar), &scrollbar_rect);
	if (bar->orient & RTGUI_VERTICAL)
	{
		rt_uint32_t btn_width = scrollbar_rect.x2 - scrollbar_rect.x1;

		/* vertical scroll bar */
		rect->x1 = scrollbar_rect.x1;
		rect->x2 = scrollbar_rect.x2;
		rect->y1 = scrollbar_rect.y1 + btn_width + _rtgui_scrollbar_get_thumb_position(bar);
		rect->y2 = rect->y1 + btn_width;
	}
	else
	{
		rt_uint32_t btn_height = scrollbar_rect.y2 - scrollbar_rect.y1;

		/* horizontal scroll bar */
		rect->x1 = scrollbar_rect.x1 + btn_height + _rtgui_scrollbar_get_thumb_position(bar);
		rect->x2 = rect->x1 + btn_height;

		rect->y1 = scrollbar_rect.y1;
		rect->y2 = scrollbar_rect.y2;
	}
}

DEFINE_CLASS_TYPE(scrollbar, "scrollbar", 
	RTGUI_WIDGET_TYPE,
	_rtgui_scrollbar_constructor,
	RT_NULL,
	sizeof(struct rtgui_scrollbar));

static void _rtgui_scrollbar_on_mouseclick(struct rtgui_widget * widget, struct rtgui_event * event)
{
	rtgui_rect_t btn_rect, bar_rect;
	rt_uint32_t thumb_size, thumb_position;
    struct rtgui_scrollbar* bar = (struct rtgui_scrollbar*)widget;
    struct rtgui_event_mouse* mouse = (struct rtgui_event_mouse*)event;

	/* get the thumb size and position */
	thumb_size = bar->thumb_size * (bar->max_position - bar->min_position) / _rtgui_scrollbar_get_length(bar);
	thumb_position = _rtgui_scrollbar_get_thumb_position(bar);

    if (bar->orient == RTGUI_VERTICAL)
    {
		/* get up arrow button rect */
		btn_rect.x1 = widget->extent.x1;
		btn_rect.x2 = widget->extent.x2;
		btn_rect.y1 = widget->extent.y1;
		btn_rect.y2 = widget->extent.y1 + (widget->extent.x2 - widget->extent.x1);
        if (rtgui_rect_contains_point(&btn_rect, mouse->x, mouse->y) == RT_EOK)
        {
            if ((mouse->button & (RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN)) ==
				(RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN))
            {
                bar->status |= SBS_UPARROW;

				/* line step */
				bar->thumb_position -= bar->line_step;
				if (bar->thumb_position < bar->min_position) bar->thumb_position = bar->min_position;
            }
            else if (mouse->button & RTGUI_MOUSE_BUTTON_UP)
			{
                bar->status = 0;
			}
			goto __exit;
        }

		/* get bar rect */
		bar_rect.x1 = widget->extent.x1;
		bar_rect.x2 = widget->extent.x2;
		bar_rect.y1 = widget->extent.y1 + (widget->extent.x2 - widget->extent.x1);
		bar_rect.y2 = widget->extent.y2 - (widget->extent.x2 - widget->extent.x1);
        if (rtgui_rect_contains_point(&bar_rect, mouse->x, mouse->y) == RT_EOK)
        {
			if ((mouse->button & (RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN)) ==
				(RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN))
            {
				/* page step */
				if (mouse->y < bar_rect.y1 + thumb_position)
				{
					bar->thumb_position -= bar->page_step;
					if (bar->thumb_position < bar->min_position)					
						bar->thumb_position = bar->min_position;
				}
				else if (mouse->y > thumb_position + bar->thumb_size)
				{
					bar->thumb_position += bar->page_step;
					if (bar->thumb_position > bar->max_position - thumb_size)
						bar->thumb_position = bar->max_position - thumb_size;
				}
            }
			goto __exit;
        }

		/* get down arrow button rect */
        btn_rect.y1 = widget->extent.y2 - (widget->extent.x2 - widget->extent.x1);
        btn_rect.y2 = widget->extent.y2;
        bar_rect.y1 = widget->extent.y1 + ((widget->extent.y2 - widget->extent.y1)/2);
        bar_rect.y2 = widget->extent.y2 - (widget->extent.x2 - widget->extent.x1);
        if (rtgui_rect_contains_point(&btn_rect, mouse->x, mouse->y) == RT_EOK)
        {
            if ((mouse->button & (RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN)) ==
				(RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN))
            {
                bar->status |= SBS_DOWNARROW;

				/* line step */
				bar->thumb_position += bar->line_step;
				if (bar->thumb_position > bar->max_position - thumb_size)
					bar->thumb_position = bar->max_position - thumb_size;
            }
            else if (mouse->button & RTGUI_MOUSE_BUTTON_UP)
                bar->status = 0;
        }
    }
    else
    {
		/* get left arrow button rect */
		btn_rect.x1 = widget->extent.x1;
		btn_rect.x2 = widget->extent.x1 + (widget->extent.y2 - widget->extent.y1);
		btn_rect.y1 = widget->extent.y1;
		btn_rect.y2 = widget->extent.y2;
        if (rtgui_rect_contains_point(&btn_rect, mouse->x, mouse->y) == RT_EOK)
        {
            if ((mouse->button & (RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN)) ==
				(RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN))
            {
                bar->status |= SBS_LEFTARROW;

				/* line step */
				bar->thumb_position -= bar->line_step;
				if (bar->thumb_position < bar->min_position) bar->thumb_position = bar->min_position;
            }
             else if (mouse->button & RTGUI_MOUSE_BUTTON_UP)
                bar->status = 0;
			goto __exit;
       }

		/* get bar rect */
		bar_rect.x1 = widget->extent.x1 + (widget->extent.y2 - widget->extent.y1);
		bar_rect.x2 = widget->extent.x2 - (widget->extent.y2 - widget->extent.y1);
		bar_rect.y1 = widget->extent.y1;
		bar_rect.y2 = widget->extent.y2;
        if (rtgui_rect_contains_point(&bar_rect, mouse->x, mouse->y) == RT_EOK)
        {
            if ((mouse->button & (RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN)) ==
				(RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN))
            {
				/* page step */
				if (mouse->x <  bar_rect.x1 + thumb_position)
				{
					bar->thumb_position -= bar->page_step;
					if (bar->thumb_position < bar->min_position)					
						bar->thumb_position = bar->min_position;
				}
				else if (mouse->x > thumb_position + bar->thumb_size)
				{
					bar->thumb_position += bar->page_step;
					if (bar->thumb_position > bar->max_position - thumb_size)
						bar->thumb_position = bar->max_position - thumb_size;
				}
            }
			goto __exit;
        }

		/* get right arrow button rect */
        btn_rect.x1 = widget->extent.x2 - (widget->extent.y2 - widget->extent.y1);
        btn_rect.x2 = widget->extent.x2;
        bar_rect.x1 = widget->extent.x1 + ((widget->extent.x2 - widget->extent.x1)/2);
        bar_rect.x2 = widget->extent.x2 - (widget->extent.y2 - widget->extent.y1);
        if (rtgui_rect_contains_point(&btn_rect,
                            mouse->x, mouse->y) == RT_EOK)
        {
            if ((mouse->button & (RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN)) ==
				(RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN))
            {
                bar->status |= SBS_RIGHTARROW;

				/* line step */
				bar->thumb_position += bar->line_step;
				if (bar->thumb_position > bar->max_position - bar->line_step)
					bar->thumb_position = bar->max_position - bar->line_step;
            }
             else if (mouse->button & RTGUI_MOUSE_BUTTON_UP)
                bar->status = 0;
        }
    }

__exit:
    rtgui_theme_draw_scrollbar(bar);
	if ((mouse->button & (RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN)) ==
		(RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN))
	{
		if (bar->on_scroll != RT_NULL) bar->on_scroll(widget, RT_NULL);
	}
}

rt_bool_t rtgui_scrollbar_event_handler(struct rtgui_widget * widget,
	struct rtgui_event * event)
{
	struct rtgui_scrollbar* bar = (struct rtgui_scrollbar*)widget;

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_draw != RT_NULL) widget->on_draw(widget, event);
		else
#endif
		{
			rtgui_theme_draw_scrollbar(bar);
		}

		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
		if (RTGUI_WIDGET_IS_ENABLE(widget) && !RTGUI_WIDGET_IS_HIDE(widget))
		{
#ifndef RTGUI_USING_SMALL_SIZE
			if (widget->on_mouseclick != RT_NULL)
			{
				widget->on_mouseclick(widget, event);
			}
			else
#endif
			{
				_rtgui_scrollbar_on_mouseclick(widget, event);
			}
		}

		break;

	default:
		break;
	}

	return RT_FALSE;
}

struct rtgui_scrollbar* rtgui_scrollbar_create(int orient, rtgui_rect_t* r)
{
    struct rtgui_scrollbar* bar;

    bar = (struct rtgui_scrollbar*) rtgui_widget_create (RTGUI_SCROLLBAR_TYPE);
    if (bar != RT_NULL)
    {
		if (r != RT_NULL)
		{
			rtgui_widget_set_rect(RTGUI_WIDGET(bar), r);
			if (orient == RTGUI_VERTICAL)
				bar->thumb_size = (r->x2 - r->x1);
			else
				bar->thumb_size = (r->y2 - r->y1);
		}

		bar->orient = orient;
    }

    return bar;
}

void rtgui_scrollbar_destroy(struct rtgui_scrollbar* bar)
{
	rtgui_widget_destroy(RTGUI_WIDGET(bar));
}

void rtgui_scrollbar_set_orientation(rtgui_scrollbar_t* bar, int orientation)
{
	RT_ASSERT(bar != RT_NULL);

	bar->orient = orientation;
#ifndef RTGUI_USING_SMALL_SIZE
	if (bar->orient == RTGUI_HORIZONTAL)
	{
		/* horizontal */
		rtgui_widget_set_miniwidth(RTGUI_WIDGET(bar), RTGUI_DEFAULT_SB_WIDTH);
		rtgui_widget_set_miniheight(RTGUI_WIDGET(bar), RTGUI_DEFAULT_SB_HEIGHT);
	}
	else 
	{
		/* vertical */
		rtgui_widget_set_miniwidth(RTGUI_WIDGET(bar), RTGUI_DEFAULT_SB_HEIGHT);
		rtgui_widget_set_miniheight(RTGUI_WIDGET(bar), RTGUI_DEFAULT_SB_WIDTH);
	}
#endif
}

void rtgui_scrollbar_set_range(struct rtgui_scrollbar* bar, int min, int max)
{
	RT_ASSERT(bar != RT_NULL);

	if (min >= max )
	{
		RTGUI_WIDGET_DISABLE(RTGUI_WIDGET(bar));
		return;
	}

	bar->min_position = (rt_int16_t)min;
	bar->max_position = (rt_int16_t)max;
}

void rtgui_scrollbar_set_page_step(struct rtgui_scrollbar* bar, int step)
{
	RT_ASSERT(bar != RT_NULL);

	bar->page_step = step;
		
	/* disable or enable scrollbar */
	if (bar->page_step > (bar->max_position - bar->min_position))
	{
		/* disable bar */
		RTGUI_WIDGET_DISABLE(RTGUI_WIDGET(bar));
	}
	else
	{
		/* enable bar */
		RTGUI_WIDGET_ENABLE(RTGUI_WIDGET(bar));
	}
}

void rtgui_scrollbar_set_line_step(struct rtgui_scrollbar* bar, int step)
{
	RT_ASSERT(bar != RT_NULL);

	bar->line_step = step;
}

rt_int16_t rtgui_scrollbar_get_value(struct rtgui_scrollbar* bar)
{
	RT_ASSERT(bar != RT_NULL);

	return bar->thumb_position;
}

void rtgui_scrollbar_set_value(struct rtgui_scrollbar* bar, rt_int16_t position)
{
	RT_ASSERT(bar != RT_NULL);

	bar->thumb_position = position;
	rtgui_widget_update(RTGUI_WIDGET(bar));
}

void rtgui_scrollbar_set_onscroll(struct rtgui_scrollbar* bar,
								  rtgui_event_handler_ptr handler)
{
	if (bar == RT_NULL || handler == RT_NULL) return;

	bar->on_scroll = handler;
}
