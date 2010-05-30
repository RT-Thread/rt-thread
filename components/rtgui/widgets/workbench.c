/*
 * File      : workbench.c
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
 */
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/workbench.h>

static void _rtgui_workbench_constructor(rtgui_workbench_t *workbench)
{
	/* set event handler */
	rtgui_widget_set_event_handler(RTGUI_WIDGET(workbench), rtgui_workbench_event_handler);

	/* set attributes */
	workbench->flag 		= RTGUI_WORKBENCH_FLAG_DEFAULT;
	workbench->panel 		= RT_NULL;
	workbench->title 		= RT_NULL;
	workbench->current_view = RT_NULL;
	workbench->modal_code 	= RTGUI_MODAL_OK;
	workbench->modal_widget = RT_NULL;
}

static void _rtgui_workbench_destructor(rtgui_workbench_t *workbench)
{
	RT_ASSERT(workbench != RT_NULL);

	if (RTGUI_TOPLEVEL(workbench)->server != RT_NULL)
	{
		struct rtgui_event_panel_detach edetach;
		RTGUI_EVENT_PANEL_DETACH_INIT(&edetach);

		/* detach from panel */
		edetach.panel = workbench->panel;

		/* send PANEL DETACH to server */
		if (rtgui_thread_send_sync(RTGUI_TOPLEVEL(workbench)->server,
			RTGUI_EVENT(&edetach), sizeof(struct rtgui_event_panel_detach)) != RT_EOK)
			return;

		RTGUI_TOPLEVEL(workbench)->server = RT_NULL;
	}

	/* release title */
	rt_free(workbench->title);
	workbench->title = RT_NULL;
}

rtgui_type_t *rtgui_workbench_type_get(void)
{
	static rtgui_type_t *workbench_type = RT_NULL;

	if (!workbench_type)
	{
		workbench_type = rtgui_type_create("workbench", RTGUI_TOPLEVEL_TYPE,
			sizeof(rtgui_workbench_t),
			RTGUI_CONSTRUCTOR(_rtgui_workbench_constructor),
			RTGUI_DESTRUCTOR(_rtgui_workbench_destructor));
	}

	return workbench_type;
}

rtgui_workbench_t *rtgui_workbench_create(const char* panel_name, const unsigned char* title)
{
	struct rtgui_workbench* workbench;

	/* the server thread id */
	rt_thread_t server = rtgui_thread_get_server();
	if (server == RT_NULL)
	{
		rt_kprintf("can't find rtgui server\n");
		return RT_NULL;
	}

	/* create workbench */
	workbench = (rtgui_workbench_t*) rtgui_widget_create (RTGUI_WORKBENCH_TYPE);
	if (workbench != RT_NULL)
	{
		/* the buffer uses to receive event */
		union
		{
			struct rtgui_event_panel_attach ecreate;
			struct rtgui_event_panel_info epanel;

			char buffer[256];	/* use to recv other information */
		} event;

		/* set workbench title */
		workbench->title = (unsigned char*)rt_strdup((char*)title);

		/* create application in server */
		RTGUI_EVENT_PANEL_ATTACH_INIT(&(event.ecreate));

		/* set the panel name and workbench */
		rt_strncpy(event.ecreate.panel_name, panel_name, RTGUI_NAME_MAX);
		event.ecreate.workbench = workbench;

		/* send PANEL ATTACH to server */
		if (rtgui_thread_send_sync(server,
			&(event.ecreate.parent), sizeof(struct rtgui_event_panel_attach)) != RTGUI_STATUS_OK)
		{
			return RT_NULL;
		}

		/* get PANEL INFO */
		rtgui_thread_recv_filter(RTGUI_EVENT_PANEL_INFO, &(event.epanel.parent), sizeof(event));

		/* set panel */
		workbench->panel = (struct rtgui_panel*)event.epanel.panel;

		/* connected */
		RTGUI_TOPLEVEL(workbench)->server = server;

		/* set extent of workbench */
		rtgui_widget_set_rect(RTGUI_WIDGET(workbench), &(event.epanel.extent));

		/* set workbench in thread */
		rtgui_thread_set_widget(RTGUI_WIDGET(workbench));
	}

	return workbench;
}

void rtgui_workbench_destroy(rtgui_workbench_t* workbench)
{
	RT_ASSERT(workbench != RT_NULL);

	if (RTGUI_TOPLEVEL(workbench)->server != RT_NULL)
	{
		struct rtgui_event_panel_detach edetach;
		RTGUI_EVENT_PANEL_DETACH_INIT(&edetach);

		/* detach from panel */
		edetach.panel = workbench->panel;

		/* send PANEL DETACH to server */
		if (rtgui_thread_send_sync(RTGUI_TOPLEVEL(workbench)->server,
			RTGUI_EVENT(&edetach), sizeof(struct rtgui_event_panel_detach)) != RT_EOK)
			return;

			RTGUI_TOPLEVEL(workbench)->server = RT_NULL;
	}

	rtgui_widget_destroy(RTGUI_WIDGET(workbench));
}

void rtgui_workbench_set_flag(rtgui_workbench_t* workbench, rt_uint8_t flag)
{
	RT_ASSERT(workbench != RT_NULL);

	workbench->flag = flag;
}

rt_bool_t rtgui_workbench_event_loop(rtgui_workbench_t* workbench)
{
	rtgui_thread_t* tid;
	struct rtgui_event* event;

	tid = rtgui_thread_self();
	RT_ASSERT(tid != RT_NULL);

	/* point to event buffer */
	event = (struct rtgui_event*)tid->event_buffer;

	if (workbench->flag & RTGUI_WORKBENCH_FLAG_MODAL_MODE)
	{
		/* event loop for modal mode shown view */
		while (workbench->flag & RTGUI_WORKBENCH_FLAG_MODAL_MODE)
		{
			if (rtgui_thread_recv(event, RTGUI_EVENT_BUFFER_SIZE) == RT_EOK)
			{
				RTGUI_WIDGET(workbench)->event_handler(RTGUI_WIDGET(workbench), event);
			}
		}
	}
	else
	{
		/* show workbench firstly */
		rtgui_workbench_show(workbench);
		
		while (!(workbench->flag & RTGUI_WORKBENCH_FLAG_CLOSED))
		{
			if (rtgui_thread_recv(event, RTGUI_EVENT_BUFFER_SIZE) == RT_EOK)
			{
				RTGUI_WIDGET(workbench)->event_handler(RTGUI_WIDGET(workbench), event);
			}
		}
	}

	return RT_TRUE;
}

rt_err_t rtgui_workbench_show(rtgui_workbench_t* workbench)
{
	RT_ASSERT(workbench != RT_NULL);

	if (RTGUI_TOPLEVEL(workbench)->server != RT_NULL)
	{
		struct rtgui_event_panel_show eraise;
		RTGUI_EVENT_PANEL_SHOW_INIT(&eraise);
		eraise.workbench = workbench;

		eraise.panel = workbench->panel;
		if (rtgui_thread_send_sync(workbench->parent.server, RTGUI_EVENT(&eraise),
			sizeof(struct rtgui_event_panel_show)) != RT_EOK)
			return -RT_ERROR;

		RTGUI_WIDGET_UNHIDE(RTGUI_WIDGET(workbench));
		rtgui_toplevel_update_clip(RTGUI_TOPLEVEL(workbench));
	}
	else return -RT_ERROR;

	return RT_EOK;
}

rt_err_t rtgui_workbench_hide(rtgui_workbench_t* workbench)
{
	if (RTGUI_TOPLEVEL(workbench)->server != RT_NULL)
	{
		struct rtgui_event_panel_hide ehide;
		RTGUI_EVENT_PANEL_HIDE_INIT(&ehide);

		RT_ASSERT(workbench != RT_NULL);
		if (workbench->parent.server == RT_NULL) return -RT_ERROR;

		ehide.panel = workbench->panel;
		if (rtgui_thread_send_sync(RTGUI_TOPLEVEL(workbench)->server, RTGUI_EVENT(&ehide),
			sizeof(struct rtgui_event_panel_hide)) != RT_EOK)
			return -RT_ERROR;

		RTGUI_WIDGET_HIDE(RTGUI_WIDGET(workbench));
		rtgui_toplevel_update_clip(RTGUI_TOPLEVEL(workbench));
	}

	return RT_EOK;
}

rt_bool_t rtgui_workbench_event_handler(rtgui_widget_t* widget, rtgui_event_t* event)
{
	struct rtgui_workbench* workbench = (struct rtgui_workbench*)widget;

	switch (event->type)
	{
	case RTGUI_EVENT_PANEL_DETACH:
		RTGUI_WIDGET_HIDE(RTGUI_WIDGET(workbench));
		RTGUI_TOPLEVEL(workbench)->server = RT_NULL;
		return RT_TRUE;

	case RTGUI_EVENT_PANEL_SHOW:
		/* show workbench in server */
		rtgui_workbench_show(workbench);
		break;

	case RTGUI_EVENT_PANEL_HIDE:
		/* hide widget */
		RTGUI_WIDGET_HIDE(widget);
		break;

	case RTGUI_EVENT_MOUSE_MOTION:
		{
			struct rtgui_event_mouse* emouse = (struct rtgui_event_mouse*)event;
			struct rtgui_toplevel* top = RTGUI_TOPLEVEL(emouse->wid);

			/* check the destination window */
			if (top != RT_NULL && RTGUI_WIDGET(top)->event_handler != RT_NULL)
			{
				RTGUI_WIDGET(top)->event_handler(RTGUI_WIDGET(top), event);
			}
			else
			{
				/* let viewer to handle it */
				rtgui_view_t* view = workbench->current_view;
				if (view != RT_NULL &&
					RTGUI_WIDGET(view)->event_handler != RT_NULL)
				{
					RTGUI_WIDGET(view)->event_handler(RTGUI_WIDGET(view), event);
				}
			}
		}
		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
		{
			struct rtgui_event_mouse* emouse = (struct rtgui_event_mouse*)event;
			struct rtgui_toplevel* top = RTGUI_TOPLEVEL(emouse->wid);

			/* check the destination window */
			if (top != RT_NULL && RTGUI_WIDGET(top)->event_handler != RT_NULL)
			{
				RTGUI_WIDGET(top)->event_handler(RTGUI_WIDGET(top), event);
			}
			else
			{
				if (RTGUI_WORKBENCH_IS_MODAL_MODE(workbench))
				{
					/* let modal widget to handle it */
					if (workbench->modal_widget != RT_NULL &&
							workbench->modal_widget->event_handler != RT_NULL)
					{
						workbench->modal_widget->event_handler(workbench->modal_widget, event);
					}
				}
				else
				{
					/* let viewer to handle it */
					rtgui_view_t* view = workbench->current_view;
					if (view != RT_NULL &&
							RTGUI_WIDGET(view)->event_handler != RT_NULL)
					{
						RTGUI_WIDGET(view)->event_handler(RTGUI_WIDGET(view), event);
					}
				}
			}
		}
		break;

	case RTGUI_EVENT_KBD:
		{
			struct rtgui_event_kbd* kbd = (struct rtgui_event_kbd*)event;
			struct rtgui_toplevel* top = RTGUI_TOPLEVEL(kbd->wid);

			/* check the destination window */
			if (top != RT_NULL && RTGUI_WIDGET(top)->event_handler != RT_NULL)
			{
				RTGUI_WIDGET(top)->event_handler(RTGUI_WIDGET(top), event);
			}
			else
			{
				if (RTGUI_WORKBENCH_IS_MODAL_MODE(workbench))
				{
					/* let modal widget to handle it */
					if (workbench->modal_widget != RT_NULL &&
							workbench->modal_widget->event_handler != RT_NULL)
					{
						workbench->modal_widget->event_handler(workbench->modal_widget, event);
					}
				}
				else
				{
					if (RTGUI_CONTAINER(widget)->focused == widget)
					{
						/* set focused widget to the current view */
						if (workbench->current_view != RT_NULL)
							rtgui_widget_focus(RTGUI_WIDGET(RTGUI_CONTAINER(workbench->current_view)->focused));
					}

					return rtgui_toplevel_event_handler(widget, event);
				}
			}
		}
		break;

	case RTGUI_EVENT_PAINT:
		{
			struct rtgui_event_paint* epaint = (struct rtgui_event_paint*)event;
			struct rtgui_toplevel* top = RTGUI_TOPLEVEL(epaint->wid);

			/* check the destination window */
			if (top != RT_NULL && RTGUI_WIDGET(top)->event_handler != RT_NULL)
			{
				RTGUI_WIDGET(top)->event_handler(RTGUI_WIDGET(top), event);
			}
			else
			{
				rtgui_view_t* view;

				/* paint a view */
				view = workbench->current_view;
				if (view != RT_NULL)
				{
					/* remake a paint event */
					RTGUI_EVENT_PAINT_INIT(epaint);
					epaint->wid = RT_NULL;

					/* send this event to the view */
					if (RTGUI_WIDGET(view)->event_handler != RT_NULL)
					{
						RTGUI_WIDGET(view)->event_handler(RTGUI_WIDGET(view), event);
					}
				}
				else
				{
					struct rtgui_dc* dc;
					struct rtgui_rect rect;

					dc = rtgui_dc_begin_drawing(widget);
					rtgui_widget_get_rect(widget, &rect);
					rtgui_dc_fill_rect(dc, &rect);
					rtgui_dc_end_drawing(dc);
				}
			}
		}
		break;

	case RTGUI_EVENT_CLIP_INFO:
		{
			struct rtgui_event_clip_info* eclip = (struct rtgui_event_clip_info*)event;
			struct rtgui_widget* dest_widget = RTGUI_WIDGET(eclip->wid);

			if (dest_widget != RT_NULL && dest_widget->event_handler != RT_NULL)
			{
				dest_widget->event_handler(dest_widget, event);
			}
			else
			{
				return rtgui_toplevel_event_handler(widget, event);
			}
		}
		break;

	case RTGUI_EVENT_WIN_CLOSE:
	case RTGUI_EVENT_WIN_ACTIVATE:
	case RTGUI_EVENT_WIN_DEACTIVATE:
		{
			struct rtgui_event_win* wevent = (struct rtgui_event_win*)event;
			struct rtgui_widget* dest_widget = RTGUI_WIDGET(wevent->wid);
			if (dest_widget != RT_NULL && dest_widget->event_handler != RT_NULL)
			{
				dest_widget->event_handler(dest_widget, event);
			}
		}
		break;

	case RTGUI_EVENT_WIN_MOVE:
		{
			struct rtgui_event_win_move* wevent = (struct rtgui_event_win_move*)event;
			struct rtgui_toplevel* top = RTGUI_TOPLEVEL(wevent->wid);
			if (top != RT_NULL && RTGUI_WIDGET(top)->event_handler != RT_NULL)
			{
				RTGUI_WIDGET(top)->event_handler(RTGUI_WIDGET(top), event);
			}
		}
		break;

	default:
		return rtgui_toplevel_event_handler(widget, event);
	}

	return RT_TRUE;
}

/*
 *
 * view on workbench
 *
 */

void rtgui_workbench_add_view(rtgui_workbench_t* workbench, rtgui_view_t* view)
{
	rtgui_container_add_child(RTGUI_CONTAINER(workbench), RTGUI_WIDGET(view));
	/* hide view in default */
	RTGUI_WIDGET_HIDE(RTGUI_WIDGET(view));

	/* reset view extent */
	rtgui_widget_set_rect(RTGUI_WIDGET(view), &(RTGUI_WIDGET(workbench)->extent));
}

void rtgui_workbench_remove_view(rtgui_workbench_t* workbench, rtgui_view_t* view)
{
	if (view == workbench->current_view)
		rtgui_workbench_hide_view(workbench, view);

	rtgui_container_remove_child(RTGUI_CONTAINER(workbench), RTGUI_WIDGET(view));
}

void rtgui_workbench_show_view(rtgui_workbench_t* workbench, rtgui_view_t* view)
{
	RT_ASSERT(workbench != RT_NULL);
	RT_ASSERT(view != RT_NULL);

	/* already shown */
	if (workbench->current_view == view) return;

	if (workbench->current_view != RT_NULL)
	{
		/* hide old view */
		RTGUI_WIDGET_HIDE(RTGUI_WIDGET(workbench->current_view));
	}

	/* show view */
	RTGUI_WIDGET_UNHIDE(RTGUI_WIDGET(view));
	workbench->current_view = view;

	/* update workbench clip */
	rtgui_toplevel_update_clip(RTGUI_TOPLEVEL(workbench));

	if (!RTGUI_WIDGET_IS_HIDE(RTGUI_WIDGET(workbench)))
	{
		rtgui_widget_update(RTGUI_WIDGET(view));
	}
}

void rtgui_workbench_hide_view(rtgui_workbench_t* workbench, rtgui_view_t* view)
{
	RT_ASSERT(workbench != RT_NULL);
	RT_ASSERT(view != RT_NULL);

	/* hide view */
	RTGUI_WIDGET_HIDE(RTGUI_WIDGET(view));

	if (view == workbench->current_view)
	{
		rtgui_view_t *next_view;

		workbench->current_view = RT_NULL;

		next_view = RTGUI_VIEW(rtgui_widget_get_next_sibling(RTGUI_WIDGET(view)));
		if (next_view == RT_NULL)
			next_view = RTGUI_VIEW(rtgui_widget_get_prev_sibling(RTGUI_WIDGET(view)));

		if (next_view != RT_NULL)
		{
			rtgui_view_show(next_view, RT_FALSE);
		}
		else
		{
			/* update workbench clip */
			rtgui_toplevel_update_clip(RTGUI_TOPLEVEL(workbench));
		}
	}
}
