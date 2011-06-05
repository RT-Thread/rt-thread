/*
 * File      : widget.c
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-04     Bernard      first version
 * 2010-06-26     Bernard      add user_data to widget structure
 */

#include <rtgui/dc_client.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/view.h>
extern void rtgui_topwin_do_clip(rtgui_widget_t* widget);

static void _rtgui_widget_constructor(rtgui_widget_t *widget)
{
   if (!widget) return;

	/* set default flag */
	widget->flag = RTGUI_WIDGET_FLAG_DEFAULT;

	/* init list */
	rtgui_list_init(&(widget->sibling));

	/* init gc */
	widget->gc.foreground = default_foreground;
	widget->gc.background = default_background;
	widget->gc.font = rtgui_font_default();
	widget->gc.textstyle = RTGUI_TEXTSTYLE_NORMAL;
	widget->gc.textalign = RTGUI_ALIGN_LEFT | RTGUI_ALIGN_TOP;
#ifndef RTGUI_USING_SMALL_SIZE
	widget->align = RTGUI_ALIGN_LEFT | RTGUI_ALIGN_TOP;
#endif

	/* set parent and toplevel root */
	widget->parent			= RT_NULL;
	widget->toplevel		= RT_NULL;

	/* some common event handler */
	widget->on_focus_in		= RT_NULL;
	widget->on_focus_out	= RT_NULL;

#ifndef RTGUI_USING_SMALL_SIZE
	widget->on_draw 		= RT_NULL;
	widget->on_mouseclick 	= RT_NULL;
	widget->on_key 			= RT_NULL;
	widget->on_size 		= RT_NULL;
	widget->on_command 		= RT_NULL;
#endif

	/* set default event handler */
	rtgui_widget_set_event_handler(widget,rtgui_widget_event_handler);

	/* init user data private to 0 */
	widget->user_data = 0;

	/* init clip information */
	rtgui_region_init(&(widget->clip));

	/* init hardware dc */
	rtgui_dc_client_init(widget);
}

/* Destroys the widget */
static void _rtgui_widget_destructor(rtgui_widget_t *widget)
{
	if (widget == RT_NULL) return;

	if (widget->parent != RT_NULL)
	{
		/* remove widget from parent's children list */
		rtgui_list_remove(&(RTGUI_CONTAINER(widget->parent)->children), &(widget->sibling));

		widget->parent = RT_NULL;
	}

	/* fini clip region */
	rtgui_region_fini(&(widget->clip));
}

DEFINE_CLASS_TYPE(widget, "widget", 
	RTGUI_OBJECT_TYPE,
	_rtgui_widget_constructor,
	_rtgui_widget_destructor,
	sizeof(struct rtgui_widget));

rtgui_widget_t *rtgui_widget_create(rtgui_type_t *widget_type)
{
	struct rtgui_widget* widget;

	widget = RTGUI_WIDGET(rtgui_object_create(widget_type));

	return widget;
}

void rtgui_widget_destroy(rtgui_widget_t* widget)
{
	rtgui_object_destroy(RTGUI_OBJECT(widget));
}

void rtgui_widget_set_rect(rtgui_widget_t* widget, const rtgui_rect_t* rect)
{
	if (widget == RT_NULL || rect == RT_NULL) return;

	widget->extent = *rect;

#ifndef RTGUI_USING_SMALL_SIZE
	/* reset mini width and height */
	widget->mini_width  = rtgui_rect_width(widget->extent);
	widget->mini_height = rtgui_rect_height(widget->extent);
#endif

	/* it's not empty, fini it */
	if (rtgui_region_not_empty(&(widget->clip)))
	{
		rtgui_region_fini(&(widget->clip));
	}

	/* reset clip info */
	rtgui_region_init_with_extents(&(widget->clip), rect);
	if ((widget->parent != RT_NULL) && (widget->toplevel != RT_NULL))
	{
		/* update widget clip */
		rtgui_widget_update_clip(widget->parent);
	}
}

void rtgui_widget_set_rectangle(rtgui_widget_t* widget, int x, int y, int width, int height)
{
	rtgui_rect_t rect;

	rect.x1 = x; rect.y1 = y;
	rect.x2 = x + width; rect.y2 = y + height;

	rtgui_widget_set_rect(widget, &rect);
}

void rtgui_widget_set_parent(rtgui_widget_t* widget, rtgui_widget_t* parent)
{
	/* set parent and toplevel widget */
	widget->parent = parent;

	/* update children toplevel */
	if (parent->toplevel != RT_NULL &&
		RTGUI_IS_TOPLEVEL(parent->toplevel))
	{
		widget->toplevel = rtgui_widget_get_toplevel(parent);
	}
}

void rtgui_widget_get_extent(rtgui_widget_t* widget, rtgui_rect_t *rect)
{
	RT_ASSERT(widget != RT_NULL);
	RT_ASSERT(rect != RT_NULL);

	*rect = widget->extent;
}

#ifndef RTGUI_USING_SMALL_SIZE
void rtgui_widget_set_miniwidth(rtgui_widget_t* widget, int width)
{
	RT_ASSERT(widget != RT_NULL);

	widget->mini_width = width;
}

void rtgui_widget_set_miniheight(rtgui_widget_t* widget, int height)
{
	RT_ASSERT(widget != RT_NULL);

	widget->mini_height = height;
}
#endif

/*
 * This function moves widget and its children to a logic point
 */
void rtgui_widget_move_to_logic(rtgui_widget_t* widget, int dx, int dy)
{
	struct rtgui_list_node* node;
	rtgui_widget_t* child;

	if (widget == RT_NULL) return;

	rtgui_rect_moveto(&(widget->extent), dx, dy);

	/* move each child */
	if (RTGUI_IS_CONTAINER(widget))
	{
		rtgui_list_foreach(node, &(RTGUI_CONTAINER(widget)->children))
		{
			child = rtgui_list_entry(node, rtgui_widget_t, sibling);

			rtgui_widget_move_to_logic(child, dx, dy);
		}
	}
}

void rtgui_widget_set_event_handler(rtgui_widget_t* widget, rtgui_event_handler_ptr handler)
{
	RT_ASSERT(widget != RT_NULL);

	widget->event_handler = handler;
}

void rtgui_widget_get_rect(rtgui_widget_t* widget, rtgui_rect_t *rect)
{
	RT_ASSERT(widget != RT_NULL);

	if (rect != RT_NULL)
	{
		rect->x1 = rect->y1 = 0;
		rect->x2 = widget->extent.x2 - widget->extent.x1;
		rect->y2 = widget->extent.y2 - widget->extent.y1;
	}
}

void rtgui_widget_set_onfocus(rtgui_widget_t* widget, rtgui_event_handler_ptr handler)
{
	RT_ASSERT(widget != RT_NULL);

	widget->on_focus_in = handler;
}

void rtgui_widget_set_onunfocus(rtgui_widget_t* widget, rtgui_event_handler_ptr handler)
{
	RT_ASSERT(widget != RT_NULL);

	widget->on_focus_out = handler;
}

#ifndef RTGUI_USING_SMALL_SIZE
void rtgui_widget_set_ondraw(rtgui_widget_t* widget, rtgui_event_handler_ptr handler)
{
	RT_ASSERT(widget != RT_NULL);

	widget->on_draw = handler;
}

void rtgui_widget_set_onmouseclick(rtgui_widget_t* widget, rtgui_event_handler_ptr handler)
{
	RT_ASSERT(widget != RT_NULL);

	widget->on_mouseclick = handler;
}

void rtgui_widget_set_onkey(rtgui_widget_t* widget, rtgui_event_handler_ptr handler)
{
	RT_ASSERT(widget != RT_NULL);

	widget->on_key = handler;
}

void rtgui_widget_set_onsize(rtgui_widget_t* widget, rtgui_event_handler_ptr handler)
{
	RT_ASSERT(widget != RT_NULL);

	widget->on_size = handler;
}

void rtgui_widget_set_oncommand(rtgui_widget_t* widget, rtgui_event_handler_ptr handler)
{
	RT_ASSERT(widget != RT_NULL);

	widget->on_command = handler;
}
#endif

/**
 * @brief Focuses the widget. The focused widget is the widget which can receive the keyboard events
 * @param widget a widget
 * @note The widget has to be attached to a toplevel widget, otherwise it will have no effect
 */
void rtgui_widget_focus(rtgui_widget_t *widget)
{
	rtgui_container_t *parent;

	RT_ASSERT(widget != RT_NULL);

	if (!widget->parent || !widget->toplevel) return;
	if (!RTGUI_WIDGET_IS_FOCUSABLE(widget) || !RTGUI_WIDGET_IS_ENABLE(widget))
		return;

	/* set widget as focused */
	widget->flag |= RTGUI_WIDGET_FLAG_FOCUS;

	/* get root parent container and old focused widget */
	parent = RTGUI_CONTAINER(widget->toplevel);
	if (parent->focused == widget) return ; /* it's the same focused widget */

	/* unfocused the old widget */
	if (parent->focused != RT_NULL)	rtgui_widget_unfocus(parent->focused);

	/* set widget as focused widget in parent link */
	parent = RTGUI_CONTAINER(widget->parent);
	do 
	{
		parent->focused = widget;
		parent = RTGUI_CONTAINER(RTGUI_WIDGET(parent)->parent);
	} while ((parent != RT_NULL) && !RTGUI_WIDGET_IS_HIDE(RTGUI_WIDGET(parent)));

	/* invoke on focus in call back */
	if (widget->on_focus_in != RT_NULL)
   		widget->on_focus_in(widget, RT_NULL);
}

/**
 * @brief Unfocused the widget
 * @param widget a widget
 */
void rtgui_widget_unfocus(rtgui_widget_t *widget)
{
	RT_ASSERT(widget != RT_NULL);

	if (!widget->toplevel || !RTGUI_WIDGET_IS_FOCUSED(widget))
		return;

	widget->flag &= ~RTGUI_WIDGET_FLAG_FOCUS;

	if (widget->on_focus_out != RT_NULL)
   		widget->on_focus_out(widget, RT_NULL);

	/* refresh widget */
	rtgui_widget_update(widget);
}

void rtgui_widget_point_to_device(rtgui_widget_t* widget, rtgui_point_t* point)
{
	RT_ASSERT(widget != RT_NULL);

	if (point != RT_NULL)
	{
		point->x += widget->extent.x1;
		point->y += widget->extent.y1;
	}
}

void rtgui_widget_rect_to_device(rtgui_widget_t* widget, rtgui_rect_t* rect)
{
	RT_ASSERT(widget != RT_NULL);

	if (rect != RT_NULL)
	{
		rect->x1 += widget->extent.x1;
		rect->x2 += widget->extent.x1;

		rect->y1 += widget->extent.y1;
		rect->y2 += widget->extent.y1;
	}
}

void rtgui_widget_point_to_logic(rtgui_widget_t* widget, rtgui_point_t* point)
{
	RT_ASSERT(widget != RT_NULL);

	if (point != RT_NULL)
	{
		point->x -= widget->extent.x1;
		point->y -= widget->extent.y1;
	}
}

void rtgui_widget_rect_to_logic(rtgui_widget_t* widget, rtgui_rect_t* rect)
{
	RT_ASSERT(widget != RT_NULL);

	if (rect != RT_NULL)
	{
		rect->x1 -= widget->extent.x1;
		rect->x2 -= widget->extent.x1;

		rect->y1 -= widget->extent.y1;
		rect->y2 -= widget->extent.y1;
	}
}

rtgui_widget_t* rtgui_widget_get_toplevel(rtgui_widget_t* widget)
{
	rtgui_widget_t* r;

	RT_ASSERT(widget != RT_NULL);

	if (widget->toplevel) return widget->toplevel;

	r = widget;
	/* get the toplevel widget */
	while (r->parent != RT_NULL) r = r->parent;

	/* set toplevel */
	widget->toplevel = r;

	return r;
}

rt_bool_t rtgui_widget_event_handler(rtgui_widget_t* widget, rtgui_event_t* event)
{
#ifndef RTGUI_USING_SMALL_SIZE
	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		if (widget->on_draw != RT_NULL) return widget->on_draw(widget, event);
		break;

	case RTGUI_EVENT_KBD:
		if (widget->on_key != RT_NULL) return widget->on_key(widget, event);
		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
		if (widget->on_mouseclick != RT_NULL) return widget->on_mouseclick(widget, event);
		break;

	case RTGUI_EVENT_COMMAND:
		if (widget->on_command != RT_NULL) return widget->on_command(widget, event);
		break;

	case RTGUI_EVENT_RESIZE:
		if (widget->on_size != RT_NULL) return widget->on_size(widget, event);
		break;
	}
#endif

	return RT_FALSE;
}

/*
 * This function updates the clip info of widget
 */
void rtgui_widget_update_clip(rtgui_widget_t* widget)
{
	struct rtgui_list_node* node;
	rtgui_widget_t *parent;

	/* no widget or widget is hide, no update clip */
	if (widget == RT_NULL || RTGUI_WIDGET_IS_HIDE(widget)) return;

	parent = widget->parent;
	/* if there is no parent, do not update clip (please use toplevel widget API) */
	if (parent == RT_NULL)
	{
		if (RTGUI_IS_TOPLEVEL(widget))
		{
			/* if it's toplevel widget, update it by toplevel function */
			rtgui_toplevel_update_clip(RTGUI_TOPLEVEL(widget));
		}
		return;
	}

	/* reset clip to extent */
	rtgui_region_reset(&(widget->clip), &(widget->extent));

	/* limit widget extent in parent extent */
	rtgui_region_intersect(&(widget->clip), &(widget->clip), &(parent->clip));

	/* get the no transparent parent */
	while (parent != RT_NULL && parent->flag & RTGUI_WIDGET_FLAG_TRANSPARENT)
	{
		parent = parent->parent;
	}

	if (parent != RT_NULL)
	{
		/* subtract widget clip in parent clip */
		if (!(widget->flag & RTGUI_WIDGET_FLAG_TRANSPARENT))
		{
			rtgui_region_subtract_rect(&(parent->clip), &(parent->clip),
				&(widget->extent));
		}
	}

	/*
	 * note: since the layout widget introduction, the sibling widget will not
	 * intersect.
	 */

	/* if it's a container object, update the clip info of children */
	if (RTGUI_IS_CONTAINER(widget))
	{
		rtgui_widget_t* child;
		rtgui_list_foreach(node, &(RTGUI_CONTAINER(widget)->children))
		{
			child = rtgui_list_entry(node, rtgui_widget_t, sibling);

			rtgui_widget_update_clip(child);
		}
	}
}

void rtgui_widget_show(rtgui_widget_t* widget)
{
	/* there is no parent or the parent is hide, no show at all */
	if (widget->parent == RT_NULL ||
		RTGUI_WIDGET_IS_HIDE(widget->parent)) return;

	/* update the clip info of widget */
	RTGUI_WIDGET_UNHIDE(widget);
	rtgui_widget_update_clip(widget);
}

void rtgui_widget_hide(rtgui_widget_t* widget)
{
	/* hide this widget */
	RTGUI_WIDGET_HIDE(widget);

	if (widget->parent != RT_NULL)
	{
		rtgui_widget_t *parent;

		parent = widget->parent;
		/* get the no transparent parent */
		while (parent != RT_NULL && parent->flag & RTGUI_WIDGET_FLAG_TRANSPARENT)
		{
			parent = parent->parent;
		}

		/* union widget rect */
		rtgui_region_union_rect(&(parent->clip), &(parent->clip), &(widget->extent));

		/* subtract the external rect */
		rtgui_topwin_do_clip(RTGUI_WIDGET(parent));
	}
}

rtgui_color_t rtgui_widget_get_parent_foreground(rtgui_widget_t* widget)
{
	rtgui_widget_t* parent;
	
	/* get parent widget */
	parent = widget->parent;
	while (parent->parent != RT_NULL && (RTGUI_WIDGET_FLAG(parent) & RTGUI_WIDGET_FLAG_TRANSPARENT))
		parent = parent->parent;

	/* get parent's color */
	if (parent != RT_NULL)
		return RTGUI_WIDGET_FOREGROUND(parent);

	return RTGUI_WIDGET_FOREGROUND(widget);
}

rtgui_color_t rtgui_widget_get_parent_background(rtgui_widget_t* widget)
{
	rtgui_widget_t* parent;
	
	/* get parent widget */
	parent = widget->parent;
	while (parent->parent != RT_NULL && (RTGUI_WIDGET_FLAG(parent) & RTGUI_WIDGET_FLAG_TRANSPARENT))
		parent = parent->parent;

	/* get parent's color */
	if (parent != RT_NULL)
		return RTGUI_WIDGET_BACKGROUND(parent);

	return RTGUI_WIDGET_BACKGROUND(widget);
}

void rtgui_widget_update(rtgui_widget_t* widget)
{
	struct rtgui_event_paint paint;
	RTGUI_EVENT_PAINT_INIT(&paint);
	paint.wid = RT_NULL;

	RT_ASSERT(widget != RT_NULL);

	if (widget->event_handler != RT_NULL)
	{
		widget->event_handler(widget, &paint.parent);
	}
}

rtgui_widget_t* rtgui_widget_get_next_sibling(rtgui_widget_t* widget)
{
	rtgui_widget_t* sibling = RT_NULL;

	if (widget->sibling.next != RT_NULL)
	{
		sibling = rtgui_list_entry(widget->sibling.next, rtgui_widget_t, sibling);
	}

	return sibling;
}

rtgui_widget_t* rtgui_widget_get_prev_sibling(rtgui_widget_t* widget)
{
	struct rtgui_list_node* node;
	rtgui_widget_t *sibling, *parent;

	node = RT_NULL; sibling = RT_NULL;
	parent = widget->parent;
	if (parent != RT_NULL)
	{
		rtgui_list_foreach(node, &(RTGUI_CONTAINER(parent)->children))
		{
			if (node->next == &(widget->sibling))
				break;
		}
	}

	if (node != RT_NULL)
		sibling = rtgui_list_entry(node, rtgui_widget_t, sibling);

	return sibling;
}

#ifdef RTGUI_WIDGET_DEBUG
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
void rtgui_widget_dump(rtgui_widget_t* widget)
{
	struct rtgui_object *obj;

	obj = RTGUI_OBJECT(widget);
	rt_kprintf("widget type: %s ", obj->type->name);

	if (RTGUI_IS_VIEW(widget) == RT_TRUE)
		rt_kprintf(":%s ", RTGUI_VIEW(widget)->title);
	if (RTGUI_IS_WIN(widget) == RT_TRUE)
		rt_kprintf(":%s ", RTGUI_WIN(widget)->title);
	if ((RTGUI_IS_LABEL(widget) == RT_TRUE) || (RTGUI_IS_BUTTON(widget) == RT_TRUE))
		rt_kprintf(":%s ", RTGUI_LABEL(widget)->text);

	rt_kprintf("extent(%d, %d) - (%d, %d)\n", widget->extent.x1, 
		widget->extent.y1, widget->extent.x2, widget->extent.y2);
	// rtgui_region_dump(&(widget->clip));
}
#endif
