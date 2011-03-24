/*
 * File      : label.c
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
#include <rtgui/widgets/label.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_theme.h>

static void _rtgui_label_constructor(rtgui_label_t *label)
{
	/* init widget and set event handler */
	rtgui_widget_set_event_handler(label, rtgui_label_event_handler);

	RTGUI_WIDGET_FOREGROUND(label) = black;
	RTGUI_WIDGET_BACKGROUND(label) = default_background;
	RTGUI_WIDGET_TEXTALIGN(label) = RTGUI_ALIGN_CENTER_VERTICAL;
	/* set field */
	label->text = RT_NULL;
}

static void _rtgui_label_destructor(rtgui_label_t *label)
{
	/* release text memory */
	if(label->text != RT_NULL)
	{
		rt_free(label->text);
		label->text = RT_NULL;
	}
}

rtgui_type_t *rtgui_label_type_get(void)
{
	static rtgui_type_t *label_type = RT_NULL;

	if(!label_type)
	{
		label_type = rtgui_type_create("label", RTGUI_WIDGET_TYPE,
			sizeof(rtgui_label_t),
			RTGUI_CONSTRUCTOR(_rtgui_label_constructor),
			RTGUI_DESTRUCTOR(_rtgui_label_destructor));
	}

	return label_type;
}

rt_bool_t rtgui_label_event_handler(PVOID wdt, rtgui_event_t* event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_label_t* label;

	RT_ASSERT(widget != RT_NULL);

	label = (rtgui_label_t*) widget;
	switch (event->type)
	{
		case RTGUI_EVENT_PAINT:
			rtgui_theme_draw_label(label);
			break;
		default:
			break;
	}

	return RT_FALSE;
}

//parent必须是一个容器类控件
rtgui_label_t* rtgui_label_create(PVOID parent, const char* text,int left, int top, int w, int h)
{
    rtgui_label_t* label;
	
	RT_ASSERT(parent != RT_NULL);

    label = rtgui_widget_create(RTGUI_LABEL_TYPE);
    if(label != RT_NULL)
    {
		rtgui_rect_t rect;
		rtgui_widget_get_rect(parent, &rect);
		rtgui_widget_rect_to_device(parent,&rect);
		rect.x1 += left;
		rect.y1 += top;
		rect.x2 = rect.x1+w;
		rect.y2 = rect.y1+h;
		rtgui_widget_set_rect(label, &rect);

		label->text = rt_strdup(text);
		
		rtgui_container_add_child(parent, label);
    }

    return label;
}

void rtgui_label_destroy(rtgui_label_t* label)
{
	rtgui_widget_destroy(label);
}

char* rtgui_label_get_text(rtgui_label_t* label)
{
	if(label == RT_NULL)return RT_NULL;

	return label->text;
}

void rtgui_label_set_text(rtgui_label_t* label, const char* text)
{
	if(label == RT_NULL)return;

	if(strcmp(text,label->text)==0)return;

	if(label->text != RT_NULL)
	{
		/* release old text memory */
		rt_free(label->text);
		label->text = RT_NULL;
	}

	if(text != RT_NULL) 
		label->text = rt_strdup(text);
	else 
		label->text = RT_NULL;

	/* update widget */
	rtgui_theme_draw_label(label);//该句似乎是多余的,会在左上角(0,0)绘制一个字符串
}
