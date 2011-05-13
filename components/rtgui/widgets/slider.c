/*
 * File      : slider.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-16     Bernard      first version
 * 2010-09-10     Bernard      fix hide issue
 */
#include <rtgui/dc.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/slider.h>

#define RTGUI_SLIDER_DEFAULT_WIDTH	100
#define RTGUI_SLIDER_DEFAULT_HEIGHT	20
#define RTGUI_SLIDER_DEFAULT_MIN	0
#define RTGUI_SLIDER_DEFAULT_MAX	100

static void _rtgui_slider_constructor(rtgui_slider_t *slider)
{
	rtgui_rect_t rect = {0, 0, RTGUI_SLIDER_DEFAULT_WIDTH, RTGUI_SLIDER_DEFAULT_HEIGHT};

	/* init widget and set event handler */
	RTGUI_WIDGET(slider)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	rtgui_widget_set_rect(RTGUI_WIDGET(slider), &rect);
	rtgui_widget_set_event_handler(RTGUI_WIDGET(slider), rtgui_slider_event_handler);

	/* set proper of control */
	slider->min = RTGUI_SLIDER_DEFAULT_MIN;
	slider->max = RTGUI_SLIDER_DEFAULT_MAX;
	slider->value = RTGUI_SLIDER_DEFAULT_MIN;
	slider->orient = RTGUI_HORIZONTAL;

	slider->ticks = 10;
	slider->thumb_width = 8;
	slider->on_changed = RT_NULL;
}

DEFINE_CLASS_TYPE(slider, "slider", 
	RTGUI_WIDGET_TYPE,
	_rtgui_slider_constructor,
	RT_NULL,
	sizeof(struct rtgui_slider));

static void rtgui_slider_onmouse(struct rtgui_slider* slider, struct rtgui_event_mouse* event)
{
	RT_ASSERT(slider != RT_NULL);
	RT_ASSERT(event  != RT_NULL);

	if (event->button & RTGUI_MOUSE_BUTTON_DOWN &&
		event->button & RTGUI_MOUSE_BUTTON_LEFT)
	{
		int sel;
		int range = slider->max - slider->min;
		int x0, xsize;
		int x;
		x0 = 1 + slider->thumb_width/2;

		if (slider->orient == RTGUI_VERTICAL)
		{
			x = event->y - RTGUI_WIDGET(slider)->extent.y1;
			x -= x0;
			xsize = rtgui_rect_height(RTGUI_WIDGET(slider)->extent) - 2 * x0;
		}
		else
		{
			x = event->x - RTGUI_WIDGET(slider)->extent.x1;
			x -= x0;
			xsize = rtgui_rect_width(RTGUI_WIDGET(slider)->extent) - 2 * x0;
		}

		if (x <= 0)
		{
			sel = slider->min;
		}
		else if (x >= xsize)
		{
			sel = slider->max;
		}
		else
		{
			sel = ((range * x) + xsize/2) / xsize;
			sel += slider->min;
		}

		rtgui_widget_focus(RTGUI_WIDGET(slider));
		rtgui_slider_set_value(slider, sel);
		if (slider->on_changed != RT_NULL) /* invoke callback function */
			slider->on_changed(RTGUI_WIDGET(slider), RT_NULL);
	}
}

static void rtgui_slider_onkey(struct rtgui_slider* slider, struct rtgui_event_kbd *event)
{
	RT_ASSERT(slider != RT_NULL);
	RT_ASSERT(event != RT_NULL);

	if (!(RTGUI_KBD_IS_UP(event))) return;

	if (event->key == RTGUIK_LEFT)
	{
		if (slider->value > slider->min)
			slider->value ++;
	}

	if (event->key == RTGUIK_RIGHT)
	{
		if (slider->value < slider->max)
			slider->value --;
	}

	/* update widget */
	rtgui_widget_update(RTGUI_WIDGET(slider));
	if (slider->on_changed != RT_NULL) /* invoke callback function */
		slider->on_changed(RTGUI_WIDGET(slider), RT_NULL);
}

rt_bool_t rtgui_slider_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_slider* slider = (struct rtgui_slider*)widget;

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_draw != RT_NULL) widget->on_draw(widget, event);
		else
#endif
		{
			rtgui_theme_draw_slider(slider);
		}

		break;

	case RTGUI_EVENT_KBD:
		if (!RTGUI_WIDGET_IS_ENABLE(widget) || RTGUI_WIDGET_IS_HIDE(widget)) return RT_FALSE;

#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_key != RT_NULL) widget->on_key(widget, event);
		else
#endif
		{
			rtgui_slider_onkey(slider, (struct rtgui_event_kbd *)event);
		}
		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
		if (!RTGUI_WIDGET_IS_ENABLE(widget) || RTGUI_WIDGET_IS_HIDE(widget)) return RT_FALSE;

#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_mouseclick != RT_NULL) widget->on_mouseclick(widget, event);
		else
#endif
		{
			rtgui_slider_onmouse(slider, (struct rtgui_event_mouse*)event);
		}
		break;
	}

	return RT_FALSE;
}

struct rtgui_slider* rtgui_slider_create(rt_size_t min, rt_size_t max, int orient)
{
    struct rtgui_slider* slider;

    slider = (struct rtgui_slider*) rtgui_widget_create (RTGUI_SLIDER_TYPE);
    if (slider != RT_NULL)
    {
		/* set proper of control */
		slider->min = min;
		slider->max = max;
		slider->value = min;

		slider->ticks = 10;
		slider->thumb_width = 8;

		rtgui_slider_set_orientation(slider, orient);
	}

	return slider;
}

void rtgui_slider_set_range(struct rtgui_slider* slider, rt_size_t min, rt_size_t max)
{
	RT_ASSERT(slider != RT_NULL);

	slider->max = max;
	slider->min = min;
}

void rtgui_slider_set_value(struct rtgui_slider* slider, rt_size_t value)
{
	RT_ASSERT(slider != RT_NULL);

	if (RTGUI_WIDGET_IS_ENABLE(RTGUI_WIDGET(slider)))
	{
		if (value < slider->min) value = slider->min;
		if (value > slider->max) value = slider->max;

		if (slider->value != value)
		{
			slider->value = value;
			rtgui_theme_draw_slider(slider);
		}
	}
}

void rtgui_slider_set_orientation(struct rtgui_slider* slider, int orientation)
{
	RT_ASSERT(slider != RT_NULL);

	/* set orientation */
	slider->orient = orientation;
#ifndef RTGUI_USING_SMALL_SIZE
	if (slider->orient == RTGUI_HORIZONTAL)
	{
		/* HORIZONTAL */
		rtgui_widget_set_miniheight(RTGUI_WIDGET(slider), RTGUI_SLIDER_DEFAULT_HEIGHT);
		rtgui_widget_set_miniwidth(RTGUI_WIDGET(slider), RTGUI_SLIDER_DEFAULT_WIDTH);
	}
	else 
	{
		/* VERTICAL */
		rtgui_widget_set_miniwidth(RTGUI_WIDGET(slider), RTGUI_SLIDER_DEFAULT_HEIGHT);
		rtgui_widget_set_miniheight(RTGUI_WIDGET(slider), RTGUI_SLIDER_DEFAULT_WIDTH);
	}
#endif
}

rt_size_t rtgui_slider_get_value(struct rtgui_slider* slider)
{
	RT_ASSERT(slider != RT_NULL);

	return slider->value;
}
