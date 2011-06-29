/*
 * File      : toplevel.c
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
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/toplevel.h>
extern void rtgui_topwin_do_clip(rtgui_widget_t* widget);

static void _rtgui_toplevel_constructor(rtgui_toplevel_t *toplevel)
{
	/* set event handler */
	rtgui_widget_set_event_handler(RTGUI_WIDGET(toplevel), rtgui_toplevel_event_handler);

	/* set toplevel to self */
	RTGUI_WIDGET(toplevel)->toplevel = RTGUI_WIDGET(toplevel);

	/* init toplevel property */
	toplevel->drawing = 0;

	/* hide toplevel default */
	RTGUI_WIDGET_HIDE(RTGUI_WIDGET(toplevel));

	/* set server as RT_NULL (no connected) */
	toplevel->server = RT_NULL;
	/* initialize last mouse event handled widget */
	toplevel->last_mevent_widget = RT_NULL;
}

static void _rtgui_toplevel_destructor(rtgui_toplevel_t* toplevel)
{
	/* release external clip info */
	toplevel->drawing = 0;
}

DEFINE_CLASS_TYPE(toplevel, "toplevel", 
	RTGUI_CONTAINER_TYPE,
	_rtgui_toplevel_constructor,
	_rtgui_toplevel_destructor,
	sizeof(struct rtgui_toplevel));

rt_bool_t rtgui_toplevel_event_handler(rtgui_widget_t* widget, rtgui_event_t* event)
{
	rtgui_toplevel_t* toplevel = (rtgui_toplevel_t*)widget;

	switch (event->type)
	{
	case RTGUI_EVENT_KBD:
		if (RTGUI_CONTAINER(toplevel)->focused != RT_NULL)
		{
			RTGUI_CONTAINER(toplevel)->focused->event_handler(RTGUI_CONTAINER(toplevel)->focused, event);
		}
		break;

	case RTGUI_EVENT_CLIP_INFO:
		/* update toplevel clip */
		rtgui_toplevel_update_clip(toplevel);
		break;

	case RTGUI_EVENT_TIMER:
		{
			struct rtgui_timer* timer;
			struct rtgui_event_timer* etimer = (struct rtgui_event_timer*) event;

			timer = etimer->timer;
			if (timer->timeout != RT_NULL)
			{
				/* call timeout function */
				timer->timeout(timer, timer->user_data);
			}
		}
		break;

	case RTGUI_EVENT_COMMAND:
		if (rtgui_container_dispatch_event(RTGUI_CONTAINER(widget), event) != RT_TRUE)
		{
#ifndef RTGUI_USING_SMALL_SIZE
			if (widget->on_command != RT_NULL)
			{
				widget->on_command(widget, event);
			}
#endif
		}
		else return RT_TRUE;
		break;

	default :
		return rtgui_container_event_handler(widget, event);
	}

	return RT_FALSE;
}

#include <rtgui/driver.h> /* to get screen rect */

void rtgui_toplevel_update_clip(rtgui_toplevel_t* top)
{
	rtgui_container_t* container;
	struct rtgui_list_node* node;
	rtgui_rect_t screen_rect;

	if (top == RT_NULL) return;

	/* reset toplevel widget clip to extent */
	rtgui_region_reset(&(RTGUI_WIDGET(top)->clip), &(RTGUI_WIDGET(top)->extent));

	/* subtract the screen rect */
	screen_rect.x1 = screen_rect.y1 = 0;
	screen_rect.x2 = rtgui_graphic_driver_get_default()->width;
	screen_rect.y2 = rtgui_graphic_driver_get_default()->height;
	rtgui_region_intersect_rect(&(RTGUI_WIDGET(top)->clip), &(RTGUI_WIDGET(top)->clip),
		&screen_rect);

	/* subtract the external rect */
	rtgui_topwin_do_clip(RTGUI_WIDGET(top));

	/* update the clip info of each child */
	container = RTGUI_CONTAINER(top);
	rtgui_list_foreach(node, &(container->children))
	{
		rtgui_widget_t* child = rtgui_list_entry(node, rtgui_widget_t, sibling);

		rtgui_widget_update_clip(child);
	}
}
