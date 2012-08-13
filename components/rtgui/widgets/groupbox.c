/*
 * File      : groupbox.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-07-29     Bernard      first version
 */
#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/groupbox.h>

static void _rtgui_groupbox_constructor(rtgui_groupbox_t *box)
{
	/* init widget and set event handler */
	rtgui_object_set_event_handler(RTGUI_OBJECT(box), rtgui_groupbox_event_handler);

	/* set field */
	box->box = RT_NULL;
	box->label = RT_NULL;
	box->selected = RT_NULL;

	box->on_selected = RT_NULL;
}

DEFINE_CLASS_TYPE(groupbox, "groupbox", 
	RTGUI_PANEL_TYPE,
	_rtgui_groupbox_constructor,
	RT_NULL,
	sizeof(struct rtgui_groupbox));

rt_bool_t rtgui_groupbox_event_handler(struct rtgui_object *object, struct rtgui_event* event)
{
	struct rtgui_groupbox* box;

	box = RTGUI_GROUPBOX(object);
	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		{
			rtgui_panel_event_handler(RTGUI_OBJECT(box), event);

			/* dispatch paint event to child */
			rtgui_container_dispatch_event(RTGUI_CONTAINER(box), event);
		}
		break;
	default:
		return rtgui_container_event_handler(object, event);
	}

	return RT_FALSE;
}

rtgui_groupbox_t* rtgui_groupbox_create(const char* label, struct rtgui_rect *rect, 
										int style, widget_select_t select_func)
{
    struct rtgui_groupbox *box;

	RT_ASSERT(select_func != RT_NULL);

    box = (struct rtgui_groupbox*) rtgui_widget_create(RTGUI_GROUPBOX_TYPE);
    if (box != RT_NULL)
    {
		rtgui_widget_set_rect(RTGUI_WIDGET(box), rect);

		if (label != RT_NULL)
		{
			box->label = rt_strdup(label);
		}

		/* create layout box */
		box->box = rtgui_box_create(style, RTGUI_WIDGET_DEFAULT_MARGIN + 1);
		rtgui_container_set_box(RTGUI_CONTAINER(box), box->box);

		rtgui_panel_set_border(RTGUI_PANEL(box), RTGUI_BORDER_NONE);

		box->select_func = select_func;
    }

    return box;
}

void rtgui_groupbox_destroy(rtgui_groupbox_t* groupbox)
{
	rtgui_object_destroy(RTGUI_OBJECT(groupbox));
}

void rtgui_groupbox_select_widget(struct rtgui_groupbox *box, struct rtgui_widget *widget)
{
	struct rtgui_event event;

	RT_ASSERT(box != RT_NULL);
	RT_ASSERT(widget != RT_NULL);

	if (box->selected != widget)
	{
		if (box->selected != RT_NULL)
		{
			box->select_func(box->selected, RT_FALSE);
			if (box->on_selected != RT_NULL)
			{
				RTGUI_EVENT_INIT(&event, RTGUI_EVENT_UNSELECTED);
				box->on_selected(RTGUI_OBJECT(widget), &event);
			}
			rtgui_widget_update(widget);
		}
		box->selected = widget;
	}

	box->select_func(box->selected, RT_TRUE);

	if (box->on_selected != RT_NULL)
	{
		RTGUI_EVENT_INIT(&event, RTGUI_EVENT_SELECTED);
		box->on_selected(RTGUI_OBJECT(widget), &event);
	}
}

struct rtgui_widget *rtgui_groupbox_get_selected(struct rtgui_groupbox *box)
{
	RT_ASSERT(box != RT_NULL);

	return box->selected;
}

void rtgui_groupbox_add_widget(struct rtgui_groupbox *box, struct rtgui_widget *widget)
{
	widget->user_data = (rt_uint32_t)box;
	rtgui_container_add_child(RTGUI_CONTAINER(box), widget);
	RTGUI_WIDGET_ALIGN(widget) = RTGUI_ALIGN_CENTER;
	RTGUI_WIDGET_BACKGROUND(widget) = RTGUI_WIDGET_BACKGROUND(box);
}

void rtgui_groupbox_layout(struct rtgui_groupbox *box)
{
	if (RTGUI_PANEL(box)->border_style != RTGUI_BORDER_NONE)
	{
		rtgui_box_layout(box->box);
	}
	else
	{
		struct rtgui_rect extent;

		RT_ASSERT(box != RT_NULL);
		rtgui_widget_get_extent(RTGUI_WIDGET(box), &extent);
		rtgui_rect_inflate(&extent, -RTGUI_WIDGET_DEFAULT_MARGIN);
		rtgui_box_layout_rect(box->box, &extent);
	}
}
