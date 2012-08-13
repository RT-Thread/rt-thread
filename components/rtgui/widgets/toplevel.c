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
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/title.h>

static void _rtgui_toplevel_constructor(rtgui_toplevel_t *toplevel)
{
	/* set event handler */
	rtgui_object_set_event_handler(RTGUI_OBJECT(toplevel), rtgui_toplevel_event_handler);

	/* set toplevel to self */
	if (RTGUI_IS_WINTITLE(toplevel))
		RTGUI_WIDGET(toplevel)->toplevel = (struct rtgui_win*)toplevel;
	else
		RTGUI_WIDGET(toplevel)->toplevel = RTGUI_WIN(toplevel);

	/* init toplevel property */
	toplevel->drawing = 0;

	/* hide toplevel default */
	RTGUI_WIDGET_HIDE(toplevel);
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

rt_bool_t rtgui_toplevel_event_handler(struct rtgui_object* object, rtgui_event_t* event)
{
	struct rtgui_toplevel* toplevel;

	RT_ASSERT(object != RT_NULL);
	RT_ASSERT(event != RT_NULL);

	toplevel = RTGUI_TOPLEVEL(object);

	switch (event->type)
	{
	case RTGUI_EVENT_CLIP_INFO:
		/* update toplevel clip */
		rtgui_toplevel_update_clip(toplevel);
		break;

	case RTGUI_EVENT_COMMAND:
		if (rtgui_container_dispatch_event(RTGUI_CONTAINER(object), event) != RT_TRUE)
		{
#ifndef RTGUI_USING_SMALL_SIZE
			if (RTGUI_WIDGET(object)->on_command != RT_NULL)
			{
				RTGUI_WIDGET(object)->on_command(object, event);
			}
#endif
		}
		else return RT_TRUE;
		break;

	default :
		return rtgui_container_event_handler(object, event);
	}

	return RT_FALSE;
}

void rtgui_toplevel_update_clip(rtgui_toplevel_t* top)
{
	rtgui_container_t* view;
	struct rtgui_list_node* node;

	if (top == RT_NULL)
		return;

	/* update the clip info of each child */
	view = RTGUI_CONTAINER(top);
	rtgui_list_foreach(node, &(view->children))
	{
		rtgui_widget_t* child = rtgui_list_entry(node, rtgui_widget_t, sibling);

		rtgui_widget_update_clip(child);
	}
}
