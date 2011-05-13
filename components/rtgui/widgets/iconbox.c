/*
 * File      : iconbox.c
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
#include <rtgui/widgets/iconbox.h>
#include <rtgui/rtgui_theme.h>

static void _rtgui_iconbox_constructor(rtgui_iconbox_t *iconbox)
{
	/* init widget and set event handler */
	RTGUI_WIDGET(iconbox)->flag |= RTGUI_WIDGET_FLAG_TRANSPARENT;
	rtgui_widget_set_event_handler(RTGUI_WIDGET(iconbox), rtgui_iconbox_event_handler);

	/* set proper of control */
	iconbox->image = RT_NULL;
	iconbox->selected = RT_FALSE;
	iconbox->text = RT_NULL;
	iconbox->text_position = RTGUI_ICONBOX_TEXT_BELOW;
}

static void _rtgui_iconbox_destructor(rtgui_iconbox_t *iconbox)
{
	if (iconbox->image != RT_NULL)
	{
		rtgui_image_destroy(iconbox->image);
		iconbox->image = RT_NULL;
	}

	rt_free(iconbox->text);
	iconbox->text = RT_NULL;
}

DEFINE_CLASS_TYPE(iconbox, "iconbox", 
	RTGUI_WIDGET_TYPE,
	_rtgui_iconbox_constructor,
	_rtgui_iconbox_destructor,
	sizeof(struct rtgui_iconbox));

rt_bool_t rtgui_iconbox_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_iconbox* iconbox = (struct rtgui_iconbox*)widget;

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_draw != RT_NULL) widget->on_draw(widget, event);
		else
#endif
		{
			rtgui_theme_draw_iconbox(iconbox);
		}

		break;
	}

	return RT_FALSE;
}

struct rtgui_iconbox* rtgui_iconbox_create(struct rtgui_image* image,
	const char* text,
	int position)
{
    struct rtgui_iconbox* iconbox;

	iconbox = (struct rtgui_iconbox*)rtgui_widget_create(RTGUI_ICONBOX_TYPE);
    if (iconbox != RT_NULL)
    {
		rtgui_rect_t rect = {0, 0, 0, 0}, text_rect;

		rect.x2 = image->w;
		rect.y2 = image->h;

		/* get text rect */
		rtgui_font_get_metrics(rtgui_font_default(), text, &text_rect);
		if (position == RTGUI_ICONBOX_TEXT_BELOW)
		{
			rect.y2 += RTGUI_WIDGET_DEFAULT_MARGIN;
			if (text_rect.x2 > rect.x2)
			{
				rect.x2 = text_rect.x2;
			}
			rect.y2 += text_rect.y2;
		}
		else if (position == RTGUI_ICONBOX_TEXT_RIGHT)
		{
			rect.x2 += RTGUI_WIDGET_DEFAULT_MARGIN;
			if (text_rect.y2 > rect.y2)
			{
				rect.y2 = text_rect.y2;
			}
			rect.x2 += text_rect.x2;
		}

		/* set widget rect */
		rtgui_widget_set_rect(RTGUI_WIDGET(iconbox), &rect);

		/* set image and text position */
		iconbox->image = image;
		iconbox->text = (char*)rt_strdup((const char*)text);
		iconbox->text_position = position;
	}

	return iconbox;
}

void rtgui_iconbox_destroy(struct rtgui_iconbox* iconbox)
{
	rtgui_widget_destroy(RTGUI_WIDGET(iconbox));
}

void rtgui_iconbox_set_text_position(struct rtgui_iconbox* iconbox, int position)
{
	rtgui_rect_t rect = {0, 0, 0, 0}, text_rect;

	RT_ASSERT(iconbox != RT_NULL);

	iconbox->text_position = position;

	/* set mini width and height */
	rect.x2 = iconbox->image->w;
	rect.y2 = iconbox->image->h;

	/* get text rect */
	if (iconbox->text != RT_NULL)
	{
		rtgui_font_get_metrics(rtgui_font_default(),
			iconbox->text, &text_rect);
		if (position == RTGUI_ICONBOX_TEXT_BELOW)
		{
			rect.y2 += RTGUI_WIDGET_DEFAULT_MARGIN;
			if (text_rect.x2 > rect.x2)
			{
				rect.x2 = text_rect.x2;
			}
			rect.y2 += text_rect.y2;
		}
		else if (position == RTGUI_ICONBOX_TEXT_RIGHT)
		{
			rect.x2 += RTGUI_WIDGET_DEFAULT_MARGIN;
			if (text_rect.y2 > rect.y2)
			{
				rect.y2 = text_rect.y2;
			}
			rect.x2 += text_rect.x2;
		}
	}

#ifndef RTGUI_USING_SMALL_SIZE
	rtgui_widget_set_miniwidth(RTGUI_WIDGET(iconbox), rect.x2);
	rtgui_widget_set_miniheight(RTGUI_WIDGET(iconbox), rect.y2);
#endif
}
