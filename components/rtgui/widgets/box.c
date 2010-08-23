/*
 * File      : box.c
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
#include <rtgui/widgets/box.h>

#ifndef RTGUI_USING_SMALL_SIZE
static void _rtgui_box_constructor(rtgui_box_t *box)
{
	/* init widget and set event handler */
	rtgui_widget_set_event_handler(RTGUI_WIDGET(box), rtgui_box_event_handler);

	RTGUI_WIDGET(box)->flag |= RTGUI_WIDGET_FLAG_TRANSPARENT;
	rtgui_widget_set_event_handler(RTGUI_WIDGET(box), rtgui_box_event_handler);

	/* set proper of control */
	box->orient = RTGUI_HORIZONTAL;
	box->border_size = RTGUI_BORDER_DEFAULT_WIDTH;
}

rtgui_type_t *rtgui_box_type_get(void)
{
	static rtgui_type_t *box_type = RT_NULL;

	if (!box_type)
	{
		box_type = rtgui_type_create("box", RTGUI_CONTAINER_TYPE,
			sizeof(rtgui_box_t), RTGUI_CONSTRUCTOR(_rtgui_box_constructor), RT_NULL);
	}

	return box_type;
}

rt_bool_t rtgui_box_event_handler(rtgui_widget_t* widget, rtgui_event_t* event)
{
	struct rtgui_box* box = (struct rtgui_box*)widget;

	RT_ASSERT(box != RT_NULL);

	switch (event->type)
	{
	case RTGUI_EVENT_RESIZE:
		/* re-layout */
		rtgui_box_layout(box);
		break;

	default:
		return rtgui_container_event_handler(RTGUI_WIDGET(box), event);
	}

	return RT_FALSE;
}

struct rtgui_box* rtgui_box_create(int orientation, rtgui_rect_t* rect)
{
    struct rtgui_box* box;

    box = (struct rtgui_box*) rtgui_widget_create (RTGUI_BOX_TYPE);
    if (box != RT_NULL)
    {
		/* set proper of control */
		rtgui_widget_set_rect(RTGUI_WIDGET(box), rect);
		box->orient = orientation;
	}

	return box;
}

void rtgui_box_append(struct rtgui_box* box, rtgui_widget_t* widget)
{
	/* put to box's children list */
	rtgui_container_add_child(RTGUI_CONTAINER(box), widget);
}

static void rtgui_box_layout_vertical(rtgui_box_t* box)
{
	rtgui_list_t *node;
	rt_int32_t box_width;
	rt_int32_t space_count;
	rt_int32_t next_x, next_y;
	rt_int32_t total_height, space_height;
	struct rtgui_event_resize size_event;

	/* prepare the resize event */
	RTGUI_EVENT_RESIZE_INIT(&size_event);

	/* find spaces */
	space_count  = 0;
	total_height = 0;
	space_height = 0;

	rtgui_list_foreach(node, &(RTGUI_CONTAINER(box)->children))
	{
		rtgui_widget_t* widget = rtgui_list_entry(node, struct rtgui_widget, sibling);
		if (widget->align & RTGUI_ALIGN_STRETCH) space_count ++;
		else total_height += widget->mini_height;
	}

	/* calculate the height for each spaces */
	if (space_count != 0)
	{
		space_height = (rtgui_rect_height(RTGUI_WIDGET(box)->extent) - total_height - (box->border_size << 1)) / space_count;
	}

	/* init (x, y) and box width */
	next_x = RTGUI_WIDGET(box)->extent.x1 + box->border_size;
	next_y = RTGUI_WIDGET(box)->extent.y1 + box->border_size;
	box_width = rtgui_rect_width(RTGUI_WIDGET(box)->extent) - (box->border_size << 1);

	/* layout each widget */
	rtgui_list_foreach(node, &(RTGUI_CONTAINER(box)->children))
	{
		rtgui_rect_t *rect;
		rtgui_widget_t* widget = rtgui_list_entry(node, struct rtgui_widget, sibling);

		/* get extent of widget */
		rect = &(widget->extent);

		/* reset rect */
		rtgui_rect_moveto(rect, -rect->x1, -rect->y1);
		rect->x2 = widget->mini_width;
		rect->y2 = widget->mini_height;

		/* left in default */
		rtgui_rect_moveto(rect, next_x, next_y);

		if (widget->align & RTGUI_ALIGN_EXPAND)
		{
			/* expand on horizontal */
			rect->x2 = rect->x1 + (rt_int16_t)box_width;
		}
		if (widget->align & RTGUI_ALIGN_CENTER_VERTICAL)
		{
			/* center */
			rt_uint32_t mid;

			mid = box_width - rtgui_rect_width(*rect);
			mid = mid /2;

			rect->x1 = next_x + mid;
			rect->x2 = next_x + box_width - mid;
		}
		else if (widget->align & RTGUI_ALIGN_RIGHT)
		{
			/* right */
			rect->x1 = next_x + box_width - rtgui_rect_width(*rect);
			rect->x2 = next_x + box_width;
		}

		if (widget->align & RTGUI_ALIGN_STRETCH)
		{
			rect->y2 = rect->y1 + space_height;
		}

		/* process resize event */
		size_event.x = rect->x1;
		size_event.y = rect->y1;
		size_event.w = rect->x2 - rect->x1;
		size_event.h = rect->y2 - rect->y1;
		widget->event_handler(widget, &size_event.parent);

		/* point to next height */
		next_y = rect->y2;
	}
}

static void rtgui_box_layout_horizontal(rtgui_box_t* box)
{
	rtgui_list_t *node;
	rt_int32_t box_height;
	rt_int32_t space_count;
	rt_int32_t next_x, next_y;
	rt_int32_t total_width, space_width;
	struct rtgui_event_resize size_event;

	/* prepare the resize event */
	RTGUI_EVENT_RESIZE_INIT(&size_event);

	/* find spaces */
	space_count = 0;
	total_width = 0;
	space_width = 0;

	rtgui_list_foreach(node, &(RTGUI_CONTAINER(box)->children))
	{
		rtgui_widget_t* widget = rtgui_list_entry(node, struct rtgui_widget, sibling);
		if (widget->align & RTGUI_ALIGN_STRETCH) space_count ++;
		else total_width += widget->mini_width;
	}

	if (space_count != 0)
	{
		/* calculate the height for each spaces */
		space_width = (rtgui_rect_width(RTGUI_WIDGET(box)->extent) - total_width) / space_count;
	}

	/* init (x, y) and box height */
	next_x = RTGUI_WIDGET(box)->extent.x1 + box->border_size;
	next_y = RTGUI_WIDGET(box)->extent.y1 + box->border_size;
	box_height = rtgui_rect_height(RTGUI_WIDGET(box)->extent) - (box->border_size << 1);

	/* layout each widget */
	rtgui_list_foreach(node, &(RTGUI_CONTAINER(box)->children))
	{
		rtgui_rect_t *rect;
		rtgui_widget_t* widget = rtgui_list_entry(node, struct rtgui_widget, sibling);

		/* get extent of widget */
		rect = &(widget->extent);

		/* reset rect */
		rtgui_rect_moveto(rect, -rect->x1, -rect->y1);
		rect->x2 = widget->mini_width;
		rect->y2 = widget->mini_height;

		/* top in default */
		rtgui_rect_moveto(rect, next_x, next_y);

		if (widget->align & RTGUI_ALIGN_EXPAND)
		{
			/* expand on vertical */
			rect->y2 = rect->y1 + box_height;
		}
		if (widget->align & RTGUI_ALIGN_CENTER_HORIZONTAL)
		{
			/* center */
			rt_uint32_t mid;

			mid = box_height - rtgui_rect_height(*rect);
			mid = mid /2;

			rect->y1 = next_y + mid;
			rect->y2 = next_y + box_height - mid;
		}
		else if (widget->align & RTGUI_ALIGN_RIGHT)
		{
			/* right */
			rect->y1 = next_y + box_height - rtgui_rect_height(*rect);
			rect->y2 = next_y + box_height;
		}

		if (widget->align & RTGUI_ALIGN_STRETCH)
		{
			rect->x2 = rect->x1 + space_width;
		}

		/* process resize event */
		size_event.x = rect->x1;
		size_event.y = rect->y1;
		size_event.w = rect->x2 - rect->x1;
		size_event.h = rect->y2 - rect->y1;
		widget->event_handler(widget, &size_event.parent);

		/* point to next width */
		next_x = rect->x2;
	}
}

void rtgui_box_layout(rtgui_box_t* box)
{
    RT_ASSERT(box != RT_NULL);

	if (box->orient & RTGUI_VERTICAL)
	{
		rtgui_box_layout_vertical(box);
	}
	else
	{
		rtgui_box_layout_horizontal(box);
	}

	/* update box and its children clip */
	if (!RTGUI_WIDGET_IS_HIDE(RTGUI_WIDGET(box)))
	{
		rtgui_widget_update_clip(RTGUI_WIDGET(box));
	}
}

rt_uint32_t rtgui_box_get_width(rtgui_box_t* box)
{
	rtgui_list_t *node;
	rt_uint32_t width;

	width = 0;
	rtgui_list_foreach(node, &(RTGUI_CONTAINER(box)->children))
	{
		rtgui_widget_t* widget = rtgui_list_entry(node, struct rtgui_widget, sibling);
		rt_uint32_t widget_width;

		widget_width = rtgui_rect_width(widget->extent);
		if (box->orient & RTGUI_VERTICAL)
		{
			/* get the max width */
			if (width < widget_width) width = widget_width;
		}
		else
		{
			/* get the total width */
			width += widget_width;
		}
	}

	return width;
}

rt_uint32_t rtgui_box_get_height(rtgui_box_t* box)
{
	rtgui_list_t *node;
	rt_uint32_t height;

	height = 0;
	rtgui_list_foreach(node, &(RTGUI_CONTAINER(box)->children))
	{
		rtgui_widget_t* widget = rtgui_list_entry(node, struct rtgui_widget, sibling);
		rt_uint32_t widget_height;

		widget_height = rtgui_rect_height(widget->extent);
		if (box->orient & RTGUI_HORIZONTAL)
		{
			/* get the max height */
			if (height < widget_height) height = widget_height;
		}
		else
		{
			/* get the total height */
			height += widget_height;
		}
	}

	return height;
}
#endif

