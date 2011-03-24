/*
 * File      : panel.c
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

#include <panel.h>
#include <mouse.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/rtgui_theme.h>

/* the global parameter */
rtgui_panel_t *rtgui_panel = RT_NULL;

//在SVN版中,下面两个变量是在topwin层定义的,
//由于取消了topwin层,所有提出来作为全局变量
rtgui_rect_t *external_clip_rect=RT_NULL;
rt_uint32_t	external_clip_size=0;

static void _rtgui_panel_constructor(rtgui_panel_t *panel)
{
	panel->status = 0;
	RTGUI_WIDGET_FLAG(panel) |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	panel->image = RT_NULL;
	rtgui_widget_set_event_handler(panel, rtgui_panel_event_handler);
	panel->modal_widget = RT_NULL;	
}

static void _rtgui_panel_destructor(rtgui_panel_t *panel)
{
	if(external_clip_size > 0)
	{
		rt_free(external_clip_rect);
		external_clip_rect = RT_NULL;
		external_clip_size = 0;
	}
}

rtgui_type_t *rtgui_panel_type_get(void)
{
	static rtgui_type_t *panel_type = RT_NULL;

	if(!panel_type)
	{
		panel_type = rtgui_type_create("panel", RTGUI_CONTAINER_TYPE,sizeof(rtgui_panel_t), 
			RTGUI_CONSTRUCTOR(_rtgui_panel_constructor),
			RTGUI_DESTRUCTOR(_rtgui_panel_destructor));
	}

	return panel_type;
}

rtgui_panel_t* rtgui_panel_create(int left, int top, int w, int h)
{
	rtgui_rect_t rect;
	rtgui_panel_t *panel;
	rtgui_thread_t *thread;
	
	panel = rtgui_widget_create(RTGUI_PANEL_TYPE);
	if(panel == RT_NULL) return RT_NULL;
	rtgui_panel_set(panel);

	thread = rtgui_thread_self();
	panel->tid = thread->tid;
	
	RTGUI_WIDGET(panel)->toplevel = RTGUI_WIDGET(panel);

	rect.x1 = left;
	rect.y1 = top;
	rect.x2 = rect.x1+w;
	rect.y2 = rect.y1+h;

	rtgui_widget_set_rect(panel,&rect);
	rtgui_widget_update_clip(panel);

	rtgui_thread_set_widget(panel);

	return panel;
}

void rtgui_panel_destroy(char* name)
{
	//Panel需要永远驻留内存中
	//......
}

void rtgui_panel_set(rtgui_panel_t *panel)
{
	rtgui_panel = panel;
}

rtgui_panel_t* rtgui_panel_get(void)
{
	return rtgui_panel;
}

void rtgui_panel_show(rtgui_panel_t *panel)
{
	rtgui_widget_update_clip(panel);
	rtgui_widget_update(panel);	
}

rt_bool_t rtgui_panel_ondraw(rtgui_panel_t* panel)
{
	rtgui_theme_draw_panel(panel);
	return RT_TRUE;
}

rt_bool_t rtgui_panel_event_handler(PVOID wdt,rtgui_event_t *event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_panel_t *panel = (rtgui_panel_t*)wdt;

	RT_ASSERT((wdt != RT_NULL) && (event != RT_NULL));

	switch (event->type)
	{
		case RTGUI_EVENT_WIN_CLOSE:
		case RTGUI_EVENT_WIN_ACTIVATE:
		case RTGUI_EVENT_WIN_DEACTIVATE:
		{
			rtgui_event_win_t* wevent = (rtgui_event_win_t*)event;
			rtgui_win_t* win = wevent->wid;
			if (win != RT_NULL && RTGUI_WIDGET_EVENT_HANDLE(win) != RT_NULL)
			{
				RTGUI_WIDGET_EVENT_CALL(win, event);
			}
			break;
		}
		case RTGUI_EVENT_WIN_MOVE:
		{
			rtgui_event_win_move_t* wevent = (rtgui_event_win_move_t*)event;
			rtgui_win_t* win = wevent->wid;
			if (win != RT_NULL && RTGUI_WIDGET_EVENT_HANDLE(win) != RT_NULL)
			{
				RTGUI_WIDGET_EVENT_CALL(win, event);
			}
			break;
		}
		case RTGUI_EVENT_PAINT:
			if(widget->on_draw != RT_NULL) 
				widget->on_draw(widget, event);
			else
				rtgui_panel_ondraw(panel);
			break;

		case RTGUI_EVENT_MOUSE_BUTTON:
		{
			rtgui_event_mouse_t* emouse = (rtgui_event_mouse_t*)event;
			rtgui_win_t* win = emouse->wid;

			/* check the destination window */
			if(win != RT_NULL && RTGUI_WIDGET_EVENT_HANDLE(win) != RT_NULL)
			{	
				RTGUI_WIDGET_EVENT_CALL(win, event);
			}
			else
			{	
				if(RTGUI_PANEL_IS_MODAL_MODE(panel))
				{
					/* let modal widget to handle it */
					if(panel->modal_widget != RT_NULL && RTGUI_WIDGET_EVENT_HANDLE(panel->modal_widget) != RT_NULL)
					{
						RTGUI_WIDGET_EVENT_CALL(panel->modal_widget, event);
					}
				}
				else
				{	
					return rtgui_container_dispatch_mouse_event(RTGUI_CONTAINER(panel),(rtgui_event_mouse_t*)event);
				}
			}
			break;
		}
	
		case RTGUI_EVENT_MOUSE_MOTION:
			return rtgui_container_dispatch_mouse_event(RTGUI_CONTAINER(panel),(rtgui_event_mouse_t*)event);
	
	    case RTGUI_EVENT_KBD:
		{
			rtgui_event_kbd_t* kbd = (rtgui_event_kbd_t*)event;
			rtgui_win_t* win = kbd->wid;

			/* check the destination window */
			if(win != RT_NULL && RTGUI_WIDGET_EVENT_HANDLE(win) != RT_NULL)
			{
				RTGUI_WIDGET_EVENT_CALL(win, event);
			}
			else
			{
				if(RTGUI_PANEL_IS_MODAL_MODE(panel))
				{
					/* let modal widget to handle it */
					if(panel->modal_widget != RT_NULL && RTGUI_WIDGET_EVENT_HANDLE(panel->modal_widget) != RT_NULL)
					{
						RTGUI_WIDGET_EVENT_CALL(panel->modal_widget, event);
					}
				}
				else if(RTGUI_CONTAINER(panel)->focused != RT_NULL)
				{
					if(RTGUI_CONTAINER(panel)->focused != widget)
					{
						RTGUI_WIDGET_EVENT_CALL(RTGUI_CONTAINER(panel)->focused, event);
					}
				}
			}
			break;
		}
	        
		default:
			return rtgui_container_event_handler(widget, event);
	}
	return RT_FALSE;
}

void rtgui_panel_event_loop(rtgui_panel_t *panel)
{
	rt_err_t result;
	rtgui_thread_t* tid;
	rtgui_event_t* event;

	tid = rtgui_thread_self();
	RT_ASSERT(tid != RT_NULL);

	/* point to event buffer */
	event = (rtgui_event_t*)tid->event_buffer;

	if(RTGUI_PANEL_IS_MODAL_MODE(panel))
	{
		/* event loop for modal mode shown view */
		while(RTGUI_PANEL_IS_MODAL_MODE(panel))
		{
			if (tid->on_idle != RT_NULL)
			{
				result = rtgui_thread_recv_nosuspend(event, RTGUI_EVENT_BUFFER_SIZE);
				if (result == RT_EOK)
					RTGUI_WIDGET_EVENT_CALL(panel, event);
				else if (result == -RT_ETIMEOUT)
					tid->on_idle(panel, RT_NULL);
			}
			else
			{
				result = rtgui_thread_recv(event, RTGUI_EVENT_BUFFER_SIZE);
				if (result == RT_EOK)
					RTGUI_WIDGET_EVENT_CALL(panel, event);
			}
		}
	}
	else
	{
		while(1)
		{	
			if(tid->on_idle != RT_NULL)
			{
				result = rtgui_thread_recv_nosuspend(event, RTGUI_EVENT_BUFFER_SIZE);
				if (result == RT_EOK)
					RTGUI_WIDGET_EVENT_CALL(panel, event);
				else if (result == -RT_ETIMEOUT)
					tid->on_idle(panel, RT_NULL);
			}
			else
			{
				result = rtgui_thread_recv(event, RTGUI_EVENT_BUFFER_SIZE);

				if (result == RT_EOK)
				{
					/* perform event handler */
					RTGUI_WIDGET_EVENT_CALL(panel, event);
				}
			}
		}
	}
}



