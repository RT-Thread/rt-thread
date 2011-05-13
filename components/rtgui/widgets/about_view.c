/*
 * File      : about_view.c
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-01-06     Bernard      first version
 */

#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/about_view.h>

static void _rtgui_about_view_constructor(struct rtgui_about_view *view)
{
	/* default rect */
	struct rtgui_rect rect = {0, 0, 200, 200};

	/* set default widget rect and set event handler */
	rtgui_widget_set_event_handler(RTGUI_WIDGET(view),rtgui_about_view_event_handler);
	rtgui_widget_set_rect(RTGUI_WIDGET(view), &rect);

	RTGUI_WIDGET(view)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;

	view->logo = RT_NULL;
	view->description = RT_NULL;

	RTGUI_WIDGET_TEXTALIGN(RTGUI_WIDGET(view)) = RTGUI_ALIGN_CENTER_VERTICAL;
}

DEFINE_CLASS_TYPE(aboutview, "aboutview", 
	RTGUI_VIEW_TYPE,
	_rtgui_about_view_constructor,
	RT_NULL,
	sizeof(struct rtgui_about_view));

void rtgui_about_view_ondraw(struct rtgui_about_view* view)
{
	struct rtgui_rect rect;
	struct rtgui_dc* dc;

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(view));
	if (dc == RT_NULL) return;

	rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);
	rtgui_dc_fill_rect(dc, &rect);

	if (view->logo != RT_NULL)
		rtgui_image_blit(view->logo, dc, &rect);

	rect.y1 += view->logo->h + 5;
	if (view->description != RT_NULL)
		rtgui_dc_draw_text(dc, view->description, &rect);

	rect.y1 += rtgui_dc_get_gc(dc)->font->height;
	rtgui_dc_draw_hline(dc, rect.x1 + 3, rect.x2 - 3, rect.y1);
	RTGUI_DC_FC(dc) = white;
	rtgui_dc_draw_hline(dc, rect.x1 + 4, rect.x2 - 2, rect.y1 + 1);

	rtgui_dc_end_drawing(dc);
}

rt_bool_t rtgui_about_view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_about_view* view = RT_NULL;

	view = RTGUI_ABOUT_VIEW(widget);
	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		rtgui_about_view_ondraw(view);
		return RT_FALSE;
	}

    /* use view event handler */
    return rtgui_view_event_handler(widget, event);
}

rtgui_about_view_t* rtgui_about_view_create(rtgui_image_t *logo, const char* description)
{
	struct rtgui_about_view* view = RT_NULL;

	view = (struct rtgui_about_view*) rtgui_widget_create(RTGUI_ABOUT_VIEW_TYPE);
	if (view != RT_NULL)
	{
	    view->logo = logo;
	    view->description = description;
	}

	return view;
}

void rtgui_about_view_destroy(rtgui_about_view_t* view)
{
    /* destroy view */
	rtgui_widget_destroy(RTGUI_WIDGET(view));
}
