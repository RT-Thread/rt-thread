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
	rtgui_widget_set_event_handler(RTGUI_WIDGET(label), rtgui_label_event_handler);

	/* set field */
	label->text = RT_NULL;
}

static void _rtgui_label_destructor(rtgui_label_t *label)
{
	/* release text memory */
	rt_free(label->text);
	label->text = RT_NULL;
}

DEFINE_CLASS_TYPE(label, "label", 
	RTGUI_WIDGET_TYPE,
	_rtgui_label_constructor,
	_rtgui_label_destructor,
	sizeof(struct rtgui_label));

rt_bool_t rtgui_label_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_label* label;

	RT_ASSERT(widget != RT_NULL);

	label = (struct rtgui_label*) widget;
	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		rtgui_theme_draw_label(label);
		break;
	}

	return RT_FALSE;
}

rtgui_label_t* rtgui_label_create(const char* text)
{
    struct rtgui_label* label;

    label = (struct rtgui_label*) rtgui_widget_create(RTGUI_LABEL_TYPE);
    if (label != RT_NULL)
    {
		rtgui_rect_t rect;

		/* set default rect */
		rtgui_font_get_metrics(rtgui_font_default(), text, &rect);
		rect.x2 += (RTGUI_BORDER_DEFAULT_WIDTH << 1);
		rect.y2 += (RTGUI_BORDER_DEFAULT_WIDTH << 1);
		rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);

		/* set text */
		label->text = (char*)rt_strdup((const char*)text);
    }

    return label;
}

void rtgui_label_destroy(rtgui_label_t* label)
{
	rtgui_widget_destroy(RTGUI_WIDGET(label));
}

char* rtgui_label_get_text(rtgui_label_t* label)
{
	RT_ASSERT(label != RT_NULL);

	return label->text;
}

void rtgui_label_set_text(rtgui_label_t* label, const char* text)
{
	RT_ASSERT(label != RT_NULL);

	if (label->text != RT_NULL)
	{
		/* it's a same text string */
		if (rt_strncmp(text, label->text, rt_strlen(text)) == 0) return;
		
		/* release old text memory */
		rt_free(label->text);
	}

	if (text != RT_NULL) label->text = (char*)rt_strdup((const char*)text);
	else label->text = RT_NULL;

	/* update widget */
	rtgui_theme_draw_label(label);
}

