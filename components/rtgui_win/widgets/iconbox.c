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
#include <rtgui/font.h>

static rt_bool_t rtgui_iconbox_onfocus(PVOID wdt, rtgui_event_t* event);
static rt_bool_t rtgui_iconbox_onunfocus(PVOID wdt, rtgui_event_t* event);

static void _rtgui_iconbox_constructor(rtgui_iconbox_t *iconbox)
{
	/* init widget and set event handler */
	rtgui_widget_set_event_handler(iconbox, rtgui_iconbox_event_handler);
	RTGUI_WIDGET_FLAG(iconbox) |= RTGUI_WIDGET_FLAG_TRANSPARENT;
	/* set proper of control */
	iconbox->image = RT_NULL;
	iconbox->selected = RT_FALSE;
	iconbox->text = RT_NULL;
	iconbox->text_position = RTGUI_ICONBOX_TEXT_BELOW;
	iconbox->call = RT_NULL;

	rtgui_widget_set_onfocus(iconbox,rtgui_iconbox_onfocus);
	rtgui_widget_set_onunfocus(iconbox,rtgui_iconbox_onunfocus);
}

static void _rtgui_iconbox_destructor(rtgui_iconbox_t *iconbox)
{
	if(iconbox->image != RT_NULL)
	{
		rtgui_image_destroy(iconbox->image);
		iconbox->image = RT_NULL;
	}
	if(iconbox->text != RT_NULL)
	{
		rt_free(iconbox->text);
		iconbox->text = RT_NULL;
	}
}

rtgui_type_t *rtgui_iconbox_type_get(void)
{
	static rtgui_type_t *iconbox_type = RT_NULL;

	if(!iconbox_type)
	{
		iconbox_type = rtgui_type_create("iconbox", RTGUI_WIDGET_TYPE,
			sizeof(rtgui_iconbox_t), RTGUI_CONSTRUCTOR(_rtgui_iconbox_constructor), 
			RTGUI_DESTRUCTOR(_rtgui_iconbox_destructor));
	}

	return iconbox_type;
}

rt_bool_t rtgui_iconbox_event_handler(PVOID wdt, rtgui_event_t* event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_iconbox_t* iconbox = (rtgui_iconbox_t*)widget;

	switch (event->type)
	{
		case RTGUI_EVENT_PAINT:
			if(widget->on_draw != RT_NULL) 
				widget->on_draw(widget, event);
			else
			{
				rtgui_theme_draw_iconbox(iconbox);
			}
	
			break;
		case RTGUI_EVENT_MOUSE_BUTTON:
			rtgui_widget_focus(wdt);
			if(iconbox->call)
				iconbox->call();
			break;
	}

	return RT_FALSE;
}

rtgui_iconbox_t* rtgui_iconbox_create(PVOID parent, rtgui_image_t* image,const char* text,int position)
{
    rtgui_iconbox_t* iconbox;

	RT_ASSERT(parent != RT_NULL);

	iconbox = rtgui_widget_create(RTGUI_ICONBOX_TYPE);
    if(iconbox != RT_NULL)
    {
		rtgui_rect_t rect, text_rect;
		
		rect.x2 = image->w;
		rect.y2 = image->h;

		/* get text rect */
		rtgui_font_get_string_rect(RTGUI_WIDGET_FONT(iconbox), text, &text_rect);
		if(position == RTGUI_ICONBOX_TEXT_BELOW)
		{
			rect.y2 += RTGUI_WIDGET_DEFAULT_MARGIN;
			if(text_rect.x2 > rect.x2)
			{
				rect.x2 = text_rect.x2;
			}
			rect.y2 += text_rect.y2;
		}
		else if(position == RTGUI_ICONBOX_TEXT_RIGHT)
		{
			rect.x2 += RTGUI_WIDGET_DEFAULT_MARGIN;
			if(text_rect.y2 > rect.y2)
			{
				rect.y2 = text_rect.y2;
			}
			rect.x2 += text_rect.x2;
		}

		/* set widget rect */
		rtgui_widget_set_rect(iconbox, &rect);

		/* set image and text position */
		iconbox->image = image;
		iconbox->text = rt_strdup(text);
		iconbox->text_position = position;

		rtgui_container_add_child(parent, iconbox);
	}

	return iconbox;
}

void rtgui_iconbox_destroy(rtgui_iconbox_t* iconbox)
{
	rtgui_widget_destroy(iconbox);
}

void rtgui_iconbox_set_text_position(rtgui_iconbox_t* iconbox, int position)
{
	rtgui_rect_t rect = {0, 0, 0, 0}, text_rect;

	RT_ASSERT(iconbox != RT_NULL);

	iconbox->text_position = position;

	/* set mini width and height */
	rect.x2 = iconbox->image->w;
	rect.y2 = iconbox->image->h;

	/* get text rect */
	if(iconbox->text != RT_NULL)
	{
		rtgui_font_get_string_rect(RTGUI_WIDGET_FONT(iconbox),
			iconbox->text, &text_rect);
		if(position == RTGUI_ICONBOX_TEXT_BELOW)
		{
			rect.y2 += RTGUI_WIDGET_DEFAULT_MARGIN;
			if(text_rect.x2 > rect.x2)
			{
				rect.x2 = text_rect.x2;
			}
			rect.y2 += text_rect.y2;
		}
		else if(position == RTGUI_ICONBOX_TEXT_RIGHT)
		{
			rect.x2 += RTGUI_WIDGET_DEFAULT_MARGIN;
			if(text_rect.y2 > rect.y2)
			{
				rect.y2 = text_rect.y2;
			}
			rect.x2 += text_rect.x2;
		}
	}
}

static rt_bool_t rtgui_iconbox_onfocus(PVOID wdt, rtgui_event_t* event)
{
	rtgui_rect_t rect;
	rtgui_dc_t *dc;

	RT_ASSERT(wdt != RT_NULL);

	dc = rtgui_dc_begin_drawing(wdt);
	if(dc == RT_NULL)return RT_FALSE;

	rtgui_widget_get_rect(wdt,&rect);
	rtgui_dc_draw_focus_rect(dc,&rect);

	rtgui_dc_end_drawing(dc);

	return RT_TRUE;
}

static rt_bool_t rtgui_iconbox_onunfocus(PVOID wdt, rtgui_event_t* event)
{
	rtgui_rect_t rect;
	rtgui_dc_t *dc;

	RT_ASSERT(wdt != RT_NULL);

	dc = rtgui_dc_begin_drawing(wdt);
	if(dc == RT_NULL)return RT_FALSE;

	rtgui_widget_get_rect(wdt,&rect);
	RTGUI_DC_FC(dc) = RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(wdt)->parent);
	rtgui_dc_draw_focus_rect(dc,&rect);

	rtgui_dc_end_drawing(dc);

	return RT_TRUE;
}

