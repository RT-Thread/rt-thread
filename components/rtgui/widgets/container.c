/*
 * File      : container.c
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
 * 2010-09-24     Bernard      fix container destroy issue
 */
#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_application.h>
#include <rtgui/widgets/container.h>
#include <rtgui/widgets/window.h>

static void _rtgui_container_constructor(rtgui_container_t *container)
{
	/* init container */
	rtgui_object_set_event_handler(RTGUI_OBJECT(container),
		rtgui_container_event_handler);

	rtgui_list_init(&(container->children));

	/* container is used to 'contain'(show) widgets and dispatch events to
	 * them, not interact with user. So no need to grab focus. If we did it,
	 * some widget inherited from container(e.g. notebook) will grab the focus
	 * annoyingly.
	 *
	 * For example, a focusable notebook N has a widget W. When the user press
	 * W, N will gain the focus and W will lose it at first. Then N will set
	 * focus to W because it is W that eventually interact with people. N will
	 * yield focus and W will gain the focus again. This loop will make W
	 * repaint twice every time user press it.
	 *
	 * Just eliminate it.
	 */
	RTGUI_WIDGET(container)->flag &= ~RTGUI_WIDGET_FLAG_FOCUSABLE;
}

static void _rtgui_container_destructor(rtgui_container_t *container)
{
	rtgui_container_destroy_children(container);
}

static void _rtgui_container_update_toplevel(rtgui_container_t* container)
{
	struct rtgui_win *window;
	struct rtgui_list_node* node;

	window = rtgui_widget_get_toplevel(RTGUI_WIDGET(container));

	rtgui_list_foreach(node, &(container->children))
	{
		rtgui_widget_t* child = rtgui_list_entry(node, rtgui_widget_t, sibling);
		/* set child toplevel */
		child->toplevel = window;

		if (RTGUI_IS_CONTAINER(child))
		{
			_rtgui_container_update_toplevel(RTGUI_CONTAINER(child));
		}
	}
}

DEFINE_CLASS_TYPE(container, "container",
	RTGUI_WIDGET_TYPE,
	_rtgui_container_constructor,
	_rtgui_container_destructor,
	sizeof(struct rtgui_container));

rt_bool_t rtgui_container_dispatch_event(rtgui_container_t *container, rtgui_event_t* event)
{
	/* handle in child widget */
	struct rtgui_list_node* node;

	rtgui_list_foreach(node, &(container->children))
	{
		struct rtgui_widget* w;
		w = rtgui_list_entry(node, struct rtgui_widget, sibling);

		if (RTGUI_OBJECT(w)->event_handler(RTGUI_OBJECT(w), event) == RT_TRUE)
			return RT_TRUE;
	}

	return RT_FALSE;
}

rt_bool_t rtgui_container_dispatch_mouse_event(rtgui_container_t *container, struct rtgui_event_mouse* event)
{
	/* handle in child widget */
	struct rtgui_list_node* node;
	struct rtgui_widget *old_focus;

	old_focus = RTGUI_WIDGET(container)->toplevel->focused_widget;

	rtgui_list_foreach(node, &(container->children))
	{
		struct rtgui_widget* w;
		w = rtgui_list_entry(node, struct rtgui_widget, sibling);
		if (rtgui_rect_contains_point(&(w->extent),
					                  event->x, event->y) == RT_EOK)
		{
			if ((old_focus != w) && RTGUI_WIDGET_IS_FOCUSABLE(w))
				rtgui_widget_focus(w);
			if (RTGUI_OBJECT(w)->event_handler(RTGUI_OBJECT(w),
											   (rtgui_event_t*)event) == RT_TRUE)
				return RT_TRUE;
		}
	}

	return RT_FALSE;
}

rt_bool_t rtgui_container_event_handler(struct rtgui_object* object, struct rtgui_event* event)
{
	struct rtgui_container *container;
	struct rtgui_widget    *widget;

	RT_ASSERT(object != RT_NULL);
	RT_ASSERT(event != RT_NULL);

	container = RTGUI_CONTAINER(object);
	widget    = RTGUI_WIDGET(object);

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		{
			struct rtgui_dc* dc;
			struct rtgui_rect rect;

			dc = rtgui_dc_begin_drawing(widget);
			if (dc == RT_NULL)
				return RT_FALSE;
			rtgui_widget_get_rect(widget, &rect);

			/* fill container with background */
			rtgui_dc_fill_rect(dc, &rect);

			/* paint on each child */
			rtgui_container_dispatch_event(container, event);

			rtgui_dc_end_drawing(dc);
		}
		break;

	case RTGUI_EVENT_KBD:
		/* let parent to handle keyboard event */
		if (widget->parent != RT_NULL &&
			widget->parent != RTGUI_WIDGET(widget->toplevel))
		{
			return RTGUI_OBJECT(widget->parent)->event_handler(
					RTGUI_OBJECT(widget->parent),
					event);
		}
		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
	case RTGUI_EVENT_MOUSE_MOTION:
		/* handle in child widget */
		return rtgui_container_dispatch_mouse_event(container,
			(struct rtgui_event_mouse*)event);

	case RTGUI_EVENT_COMMAND:
	case RTGUI_EVENT_RESIZE:
		rtgui_container_dispatch_event(container, event);
		break;

	default:
		/* call parent widget event handler */
		return rtgui_widget_event_handler(RTGUI_OBJECT(widget), event);
	}

	return RT_FALSE;
}

rtgui_container_t* rtgui_container_create(void)
{
	struct rtgui_container* container;

	/* allocate container */
	container = (struct rtgui_container*) rtgui_widget_create (RTGUI_CONTAINER_TYPE);
	return container;
}

void rtgui_container_destroy(rtgui_container_t* container)
{
	rtgui_container_hide(container);
	rtgui_widget_destroy(RTGUI_WIDGET(container));
}

/*
 * This function will add a child to a container widget
 * Note: this function will not change the widget layout
 * the layout is the responsibility of layout widget, such as box.
 */
void rtgui_container_add_child(rtgui_container_t *container, rtgui_widget_t* child)
{
	RT_ASSERT(container != RT_NULL);
	RT_ASSERT(child != RT_NULL);

	/* set parent and toplevel widget */
	child->parent = RTGUI_WIDGET(container);
	/* put widget to parent's children list */
	rtgui_list_append(&(container->children), &(child->sibling));

	/* update children toplevel */
	if (RTGUI_WIDGET(container)->toplevel != RT_NULL &&
		RTGUI_IS_TOPLEVEL(RTGUI_WIDGET(container)->toplevel))
	{
		child->toplevel = rtgui_widget_get_toplevel(RTGUI_WIDGET(container));

		/* update all child toplevel */
		if (RTGUI_IS_CONTAINER(child))
		{
			_rtgui_container_update_toplevel(RTGUI_CONTAINER(child));
		}
	}
}

/* remove a child to widget */
void rtgui_container_remove_child(rtgui_container_t *container, rtgui_widget_t* child)
{
	RT_ASSERT(container != RT_NULL);
	RT_ASSERT(child != RT_NULL);

	rtgui_widget_unfocus(child);

	/* remove widget from parent's children list */
	rtgui_list_remove(&(container->children), &(child->sibling));

	/* set parent and toplevel widget */
	child->parent = RT_NULL;
	child->toplevel = RT_NULL;
}

/* destroy all children of container */
void rtgui_container_destroy_children(rtgui_container_t *container)
{
	struct rtgui_list_node* node;

	if (container == RT_NULL) return;

	node = container->children.next;
	while (node != RT_NULL)
	{
		rtgui_widget_t* child = rtgui_list_entry(node, rtgui_widget_t, sibling);

		if (RTGUI_IS_CONTAINER(child))
		{
			/* break parent firstly */
			child->parent = RT_NULL;

			/* destroy children of child */
			rtgui_container_destroy_children(RTGUI_CONTAINER(child));
		}

		/* remove widget from parent's children list */
		rtgui_list_remove(&(container->children), &(child->sibling));

		/* set parent and toplevel widget */
		child->parent = RT_NULL;

		/* destroy object and remove from parent */
		rtgui_object_destroy(RTGUI_OBJECT(child));

		node = container->children.next;
	}

	container->children.next = RT_NULL;

	/* update widget clip */
	rtgui_toplevel_update_clip(RTGUI_TOPLEVEL(RTGUI_WIDGET(container)->toplevel));
}

rtgui_widget_t* rtgui_container_get_first_child(rtgui_container_t* container)
{
	rtgui_widget_t* child = RT_NULL;

	if (container->children.next != RT_NULL)
	{
		child = rtgui_list_entry(container->children.next, rtgui_widget_t, sibling);
	}

	return child;
}

#ifndef RTGUI_USING_SMALL_SIZE
void rtgui_container_set_box(rtgui_container_t* container, struct rtgui_box* box)
{
	if (container == RT_NULL || box  == RT_NULL)
        return;

	rtgui_container_add_child(RTGUI_CONTAINER(container), RTGUI_WIDGET(box));
	rtgui_widget_set_rect(RTGUI_WIDGET(box), &(RTGUI_WIDGET(container)->extent));
}
#endif

void rtgui_container_hide(rtgui_container_t* container)
{
	if (container == RT_NULL) return;

	if (RTGUI_WIDGET(container)->parent == RT_NULL)
	{
		RTGUI_WIDGET_HIDE(RTGUI_WIDGET(container));
		return;
	}
}

