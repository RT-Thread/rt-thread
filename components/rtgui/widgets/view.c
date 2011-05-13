/*
 * File      : view.c
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
 * 2010-09-24     Bernard      fix view destroy issue
 */
#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/view.h>
#include <rtgui/widgets/workbench.h>

static void _rtgui_view_constructor(rtgui_view_t *view)
{
	/* init view */
	rtgui_widget_set_event_handler(RTGUI_WIDGET(view),
		rtgui_view_event_handler);

	view->modal_show = RT_FALSE;
	view->title = RT_NULL;
}

static void _rtgui_view_destructor(rtgui_view_t *view)
{
	/* remove view from workbench */
	if (RTGUI_WIDGET(view)->parent != RT_NULL)
	{
		rtgui_workbench_t *workbench;

		if (view->modal_show == RT_TRUE)
			rtgui_view_end_modal(view, RTGUI_MODAL_CANCEL);

		workbench = RTGUI_WORKBENCH(RTGUI_WIDGET(view)->parent);
		rtgui_workbench_remove_view(workbench, view);
	}

	if (view->title != RT_NULL)
	{
		rt_free(view->title);
		view->title = RT_NULL;
	}
}

DEFINE_CLASS_TYPE(view, "view", 
	RTGUI_CONTAINER_TYPE,
	_rtgui_view_constructor,
	_rtgui_view_destructor,
	sizeof(struct rtgui_view));

rt_bool_t rtgui_view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_view* view = (struct rtgui_view*) widget;
	RT_ASSERT(widget != RT_NULL);

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		{
			struct rtgui_dc* dc;
			struct rtgui_rect rect;

			dc = rtgui_dc_begin_drawing(widget);
			if (dc == RT_NULL) return RT_FALSE;
			rtgui_widget_get_rect(widget, &rect);

			/* fill view with background */
			rtgui_dc_fill_rect(dc, &rect);

			/* paint on each child */
			rtgui_container_dispatch_event(RTGUI_CONTAINER(view), event);

			rtgui_dc_end_drawing(dc);
		}
		break;

	default:
		return rtgui_container_event_handler(widget, event);
	}

	return RT_FALSE;
}

rtgui_view_t* rtgui_view_create(const char* title)
{
	struct rtgui_view* view;

	/* allocate view */
	view = (struct rtgui_view*) rtgui_widget_create (RTGUI_VIEW_TYPE);
	if (view != RT_NULL)
	{
		if (title != RT_NULL)
			view->title = rt_strdup(title);
	}

	return view;
}

void rtgui_view_destroy(rtgui_view_t* view)
{
	if (view->modal_show == RT_TRUE)
		rtgui_view_end_modal(view, RTGUI_MODAL_CANCEL);
	else
	{
		rtgui_view_hide(view);
		rtgui_widget_destroy(RTGUI_WIDGET(view));
	}
}

#ifndef RTGUI_USING_SMALL_SIZE
void rtgui_view_set_box(rtgui_view_t* view, rtgui_box_t* box)
{
	if (view == RT_NULL ||
		box  == RT_NULL) return;

	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(box));
	rtgui_widget_set_rect(RTGUI_WIDGET(box), &(RTGUI_WIDGET(view)->extent));
}
#endif

rtgui_modal_code_t rtgui_view_show(rtgui_view_t* view, rt_bool_t is_modal)
{
	rtgui_workbench_t* workbench;

	/* parameter check */
	if (view == RT_NULL) return RTGUI_MODAL_CANCEL;

	if (RTGUI_WIDGET(view)->parent == RT_NULL)
	{
		RTGUI_WIDGET_UNHIDE(RTGUI_WIDGET(view));
		return RTGUI_MODAL_CANCEL;
	}

	workbench = RTGUI_WORKBENCH(RTGUI_WIDGET(view)->parent);
	rtgui_workbench_show_view(workbench, view);
	if (RTGUI_CONTAINER(view)->focused != RT_NULL)
		rtgui_widget_focus(RTGUI_CONTAINER(view)->focused);
	else
	{
		if (RTGUI_WIDGET_IS_FOCUSABLE(RTGUI_WIDGET(view)))
			rtgui_widget_focus(RTGUI_WIDGET(view));
	}

	view->modal_show = is_modal;
	if (is_modal == RT_TRUE)
	{
		/* set modal mode */
		workbench->flag |= RTGUI_WORKBENCH_FLAG_MODAL_MODE;
		workbench->modal_widget = RTGUI_WIDGET(view);

		/* perform workbench event loop */
		rtgui_workbench_event_loop(workbench);

		workbench->modal_widget = RT_NULL;
		return workbench->modal_code;
	}

	/* no modal mode, always return modal_ok */
	return RTGUI_MODAL_OK;
}

void rtgui_view_end_modal(rtgui_view_t* view, rtgui_modal_code_t modal_code)
{
	rtgui_workbench_t* workbench;

	/* parameter check */
	if ((view == RT_NULL) || (RTGUI_WIDGET(view)->parent == RT_NULL))return ;

	workbench = RTGUI_WORKBENCH(RTGUI_WIDGET(view)->parent);
	workbench->modal_code = modal_code;
	workbench->flag &= ~RTGUI_WORKBENCH_FLAG_MODAL_MODE;

	/* remove modal mode */
	view->modal_show = RT_FALSE;
}

void rtgui_view_hide(rtgui_view_t* view)
{
	if (view == RT_NULL) return;

	if (RTGUI_WIDGET(view)->parent == RT_NULL)
	{
		RTGUI_WIDGET_HIDE(RTGUI_WIDGET(view));
		return;
	}

	rtgui_workbench_hide_view((rtgui_workbench_t*)(RTGUI_WIDGET(view)->parent), view);
}

char* rtgui_view_get_title(rtgui_view_t* view)
{
	RT_ASSERT(view != RT_NULL);

	return view->title;
}

void rtgui_view_set_title(rtgui_view_t* view, const char *title)
{
	RT_ASSERT(view != RT_NULL);

	if (view->title != RT_NULL)
	{
		rtgui_free(view->title);

		if (title != RT_NULL) view->title = rt_strdup(title);
		else view->title = RT_NULL;
	}
}
