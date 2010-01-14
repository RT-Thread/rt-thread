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
 */
#include <rtgui/widgets/toplevel.h>
#include <rtgui/widgets/container.h>

static void _rtgui_container_constructor(rtgui_container_t *container)
{
	/* set event handler and init field */
	rtgui_widget_set_event_handler(RTGUI_WIDGET(container), rtgui_container_event_handler);
	rtgui_list_init(&(container->children));
	
	/* set focused widget to itself */
	container->focused = RTGUI_WIDGET(container);
	/* set container as focusable widget */
	RTGUI_WIDGET(container)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
}

static void _rtgui_container_destructor(rtgui_container_t *container)
{
	/* destroy children of container */
	rtgui_container_destroy_children(container);
}

static void _rtgui_container_update_toplevel(rtgui_container_t* container)
{
	struct rtgui_list_node* node;

	rtgui_list_foreach(node, &(container->children))
	{
		rtgui_widget_t* child = rtgui_list_entry(node, rtgui_widget_t, sibling);
		/* set child toplevel */
		child->toplevel = rtgui_widget_get_toplevel(RTGUI_WIDGET(container));

		if (RTGUI_IS_CONTAINER(child))
		{
			_rtgui_container_update_toplevel(RTGUI_CONTAINER(child));
		}
	}
}

rtgui_type_t *rtgui_container_type_get(void)
{
	static rtgui_type_t *container_type = RT_NULL;

	if (!container_type)
	{
		container_type = rtgui_type_create("container", RTGUI_WIDGET_TYPE,
			sizeof(rtgui_container_t),
			RTGUI_CONSTRUCTOR(_rtgui_container_constructor),
			RTGUI_DESTRUCTOR(_rtgui_container_destructor));
	}

	return container_type;
}

rt_bool_t rtgui_container_dispatch_event(rtgui_container_t *container, rtgui_event_t* event)
{
	/* handle in child widget */
	struct rtgui_list_node* node;

	rtgui_list_foreach(node, &(container->children))
	{
		struct rtgui_widget* w;
		w = rtgui_list_entry(node, struct rtgui_widget, sibling);

		if (w->event_handler(w, event) == RT_TRUE) return RT_TRUE;
	}

	return RT_FALSE;
}

rt_bool_t rtgui_container_dispatch_mouse_event(rtgui_container_t *container, struct rtgui_event_mouse* event)
{
	/* handle in child widget */
	struct rtgui_list_node* node;

	rtgui_list_foreach(node, &(container->children))
	{
		struct rtgui_widget* w;
		w = rtgui_list_entry(node, struct rtgui_widget, sibling);
		if (rtgui_rect_contains_point(&(w->extent), event->x, event->y) == RT_EOK)
		{
			if (w->event_handler(w, (rtgui_event_t*)event) == RT_TRUE) return RT_TRUE;
		}
	}

	return RT_FALSE;
}

rt_bool_t rtgui_container_event_handler(rtgui_widget_t* widget, rtgui_event_t* event)
{
	rtgui_container_t *container = RTGUI_CONTAINER(widget);

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
#ifndef RTGUI_USING_SMALL_SIZE	
		if (widget->on_draw != RT_NULL)
		{
			return widget->on_draw(widget, event);
		}
#endif

		rtgui_container_dispatch_event(container, event);
		break;

	case RTGUI_EVENT_KBD:
#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_key != RT_NULL)
		{
			return widget->on_key(widget, event);
		}
		else
#endif
		{
			/* let parent to handle keyboard event */
			if (widget->parent != RT_NULL && widget->parent != widget->toplevel)
			{
				return widget->parent->event_handler(widget->parent, event);
			}
		}
		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
		/* handle in child widget */
		if (rtgui_container_dispatch_mouse_event(container,
			(struct rtgui_event_mouse*)event) == RT_FALSE)
		{
#ifndef RTGUI_USING_SMALL_SIZE
			/* handle event in current widget */
			if (widget->on_mouseclick != RT_NULL)
			{
				return widget->on_mouseclick(widget, event);
			}
#endif
		}
		else return RT_TRUE;
		break;

	case RTGUI_EVENT_MOUSE_MOTION:
		if (rtgui_container_dispatch_mouse_event(container,
			(struct rtgui_event_mouse*)event) == RT_FALSE)
		{
#ifndef RTGUI_USING_SMALL_SIZE
#if 0
			/* handle event in current widget */
			if (widget->on_mousemotion != RT_NULL)
			{
				return widget->on_mousemotion(widget, event);
			}
#endif
#endif
		}
		else return RT_TRUE;
		break;

	case RTGUI_EVENT_COMMAND:
		if (rtgui_container_dispatch_event(container, event) == RT_FALSE)
		{
#ifndef RTGUI_USING_SMALL_SIZE
			if (widget->on_command != RT_NULL)
			{
				return widget->on_command(widget, event);
			}
#endif
		}
		else return RT_TRUE;
		break;

	case RTGUI_EVENT_RESIZE:
		if (rtgui_container_dispatch_event(container, event) == RT_FALSE)
		{
#ifndef RTGUI_USING_SMALL_SIZE
			if (widget->on_size != RT_NULL)
				return widget->on_size(widget, event);
#endif
		}
		else return RT_TRUE;
		break;

	default:
		/* call parent widget event handler */
		return rtgui_widget_event_handler(widget, event);
	}

	return RT_FALSE;
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

	if (child == container->focused)
	{
		/* set focused to itself */
		container->focused = RTGUI_WIDGET(container);

		rtgui_widget_focus(RTGUI_WIDGET(container));
	}

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
	container->focused = RTGUI_WIDGET(container);
	if (RTGUI_WIDGET(container)->parent != RT_NULL)
		rtgui_widget_focus(RTGUI_WIDGET(container));

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
