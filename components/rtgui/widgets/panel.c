/*
 * File      : panel.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-07-07     Bernard      implement panel as a widget
 */
#include <rtgui/dc.h>
#include <rtgui/widgets/panel.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_theme.h>

static void _rtgui_panel_constructor(rtgui_panel_t *panel)
{
	/* init widget and set event handler */
	rtgui_object_set_event_handler(RTGUI_OBJECT(panel), rtgui_panel_event_handler);

	/* set field */
	panel->border_style = RTGUI_BORDER_NONE;
}

DEFINE_CLASS_TYPE(panel, "panel", 
	RTGUI_CONTAINER_TYPE,
	_rtgui_panel_constructor,
	RT_NULL,
	sizeof(struct rtgui_panel));

rt_bool_t rtgui_panel_event_handler(struct rtgui_object *object, struct rtgui_event* event)
{
	struct rtgui_panel* panel;

	panel = RTGUI_PANEL(object);
	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		{
			struct rtgui_dc* dc;
			struct rtgui_rect rect;

			rtgui_widget_get_rect(RTGUI_WIDGET(object), &rect);
			
			dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(object));
			if (dc == RT_NULL) return RT_FALSE;

			rtgui_dc_fill_rect(dc, &rect);
			// rtgui_rect_inflate(&rect, RTGUI_WIDGET(panel)->);
			rtgui_dc_draw_border(dc, &rect, panel->border_style);

			/* paint on each child */
			rtgui_container_dispatch_event(RTGUI_CONTAINER(panel), event);

			rtgui_dc_end_drawing(dc);
		}
		break;

	default:
		return rtgui_container_event_handler(object, event);
	}

	return RT_FALSE;
}

rtgui_panel_t* rtgui_panel_create(int border_style)
{
    struct rtgui_panel* panel;

    panel = (struct rtgui_panel*) rtgui_widget_create(RTGUI_PANEL_TYPE);
    if (panel != RT_NULL)
    {
		rtgui_rect_t rect = {0, 0, 100, 100};
		rtgui_widget_set_rect(RTGUI_WIDGET(panel), &rect);

		panel->border_style = border_style;
    }

    return panel;
}

void rtgui_panel_destroy(rtgui_panel_t* panel)
{
	rtgui_object_destroy(RTGUI_OBJECT(panel));
}

