/*
 * File      : server.c
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

#include <rtgui/rtgui.h>
#include <rtgui/event.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/driver.h>

#include "mouse.h"
#include "panel.h"
#include "topwin.h"

static struct rt_thread *rtgui_server_tid;
static struct rt_messagequeue *rtgui_server_mq;

extern struct rtgui_topwin* rtgui_server_focus_topwin;
struct rtgui_panel* rtgui_server_focus_panel = RT_NULL;

void rtgui_server_create_application(struct rtgui_event_panel_attach* event)
{
	struct rtgui_panel* panel = rtgui_panel_find(event->panel_name);

	if (panel != RT_NULL)
	{
		struct rtgui_event_panel_info ep;
		RTGUI_EVENT_PANEL_INFO_INIT(&ep);

		if (panel->wm_thread != RT_NULL)
		{
			/* notify to workbench */
			rtgui_thread_send(panel->wm_thread, &(event->parent), sizeof(struct rtgui_event_panel_attach));
		}

		/* send the responses - ok */
		rtgui_thread_ack(RTGUI_EVENT(event), RTGUI_STATUS_OK);

		/* send the panel info */
		ep.panel = panel;
		ep.extent = panel->extent;
		rtgui_thread_send(event->parent.sender, (struct rtgui_event*)&ep, sizeof(ep));

		rtgui_panel_thread_add(event->panel_name, event->parent.sender);
	}
	else
	{
		/* send the responses - failure */
		rtgui_thread_ack(RTGUI_EVENT(event), RTGUI_STATUS_NRC);
	}
}

void rtgui_server_destroy_application(struct rtgui_event_panel_detach* event)
{
	struct rtgui_panel* panel = event->panel;

	if (panel != RT_NULL)
	{
		if (panel->wm_thread != RT_NULL)
		{
			/* notify to workbench */
			rtgui_thread_send(panel->wm_thread, &(event->parent), sizeof(struct rtgui_event_panel_detach));
		}

		/* send the responses */
		rtgui_thread_ack(RTGUI_EVENT(event), RTGUI_STATUS_OK);

		rtgui_panel_thread_remove(panel, event->parent.sender);

		{
			/* get next thread and active it */
			rt_thread_t tid = rtgui_panel_get_active_thread(panel);
			if (tid != RT_NULL)
			{
				/* let this thread repaint */
				struct rtgui_event_paint epaint;
				RTGUI_EVENT_PAINT_INIT(&epaint);
				epaint.wid = RT_NULL;
				rtgui_thread_send(tid, (struct rtgui_event*)&epaint, sizeof(epaint));
			}
		}
	}
	else
	{
		/* send the responses - failure */
		rtgui_thread_ack(RTGUI_EVENT(event), RTGUI_STATUS_NRC);
	}
}

void rtgui_server_thread_panel_show(struct rtgui_event_panel_show* event)
{
	struct rtgui_panel* panel = event->panel;

	if (panel != RT_NULL)
	{
		struct rtgui_event_paint epaint;

		/* send the responses */
		rtgui_thread_ack(RTGUI_EVENT(event), RTGUI_STATUS_OK);

		if (panel->wm_thread != RT_NULL)
		{
			/* notify to workbench */
			rtgui_thread_send(panel->wm_thread, &(event->parent), sizeof(struct rtgui_event_panel_show));
		}

		rtgui_panel_set_active_thread(panel, event->parent.sender);

		/* send all topwin clip info */
		rtgui_topwin_update_clip_to_panel(panel);

		/* send paint event */
		RTGUI_EVENT_PAINT_INIT(&epaint);
		epaint.wid = RT_NULL;
		rtgui_thread_send(event->parent.sender, (struct rtgui_event*)&epaint,
			sizeof(epaint));
	}
	else
	{
		/* send failed */
		rtgui_thread_ack(RTGUI_EVENT(event), RTGUI_STATUS_ERROR);
	}
}

void rtgui_server_thread_panel_hide(struct rtgui_event_panel_hide* event)
{
	struct rtgui_panel* panel = event->panel;

	if (panel != RT_NULL)
	{
		rt_thread_t tid;

		/* send the responses */
		rtgui_thread_ack(RTGUI_EVENT(event), RTGUI_STATUS_OK);

		if (panel->thread_list.next != RT_NULL)
		{
			struct rtgui_panel_thread* thread;
			thread = rtgui_list_entry(panel->thread_list.next, struct rtgui_panel_thread, list);

			/* remove it */
			panel->thread_list.next = thread->list.next;

			/* append to the tail of thread list */
			rtgui_list_append(&(panel->thread_list), &(thread->list));
		}

		/* send all topwin clip info */
		rtgui_topwin_update_clip_to_panel(panel);

		/* get new active thread */
		tid = rtgui_panel_get_active_thread(panel);
		if (tid != RT_NULL)
		{
			struct rtgui_event_paint epaint;

			/* send paint event */
			RTGUI_EVENT_PAINT_INIT(&epaint);
			epaint.wid = RT_NULL;
			rtgui_thread_send(tid, (struct rtgui_event*)&epaint, sizeof(epaint));
		}
	}
	else
	{
		/* send failed */
		rtgui_thread_ack(RTGUI_EVENT(event), RTGUI_STATUS_ERROR);
	}
}

void rtgui_server_handle_set_wm(struct rtgui_event_set_wm *event)
{
	struct rtgui_panel* panel = rtgui_panel_find(event->panel_name);

	if (panel != RT_NULL)
	{
		rtgui_panel_set_wm(panel, event->parent.sender);
	}
}

void rtgui_server_handle_update(struct rtgui_event_update_end* event)
{
	struct rtgui_graphic_driver* driver;

	driver = rtgui_graphic_driver_get_default();
	if (driver != RT_NULL)
	{
		rtgui_graphic_driver_screen_update(driver, &(event->rect));
	}
}

void rtgui_server_handle_monitor_add(struct rtgui_event_monitor* event)
{
	if (event->panel != RT_NULL)
	{
		/* append monitor rect to panel list */
		rtgui_panel_append_monitor_rect(event->panel, event->parent.sender, &(event->rect));
	}
	else
	{
		/* add monitor rect to top window list */
		rtgui_topwin_append_monitor_rect(event->wid, &(event->rect));
	}
}

void rtgui_server_handle_monitor_remove(struct rtgui_event_monitor* event)
{
	if (event->panel != RT_NULL)
	{
		/* add monitor rect to panel list */
		rtgui_panel_remove_monitor_rect(event->panel, event->parent.sender, &(event->rect));
	}
	else
	{
		/* add monitor rect to top window list */
		rtgui_topwin_remove_monitor_rect(event->wid, &(event->rect));
	}
}

void rtgui_server_handle_mouse_btn(struct rtgui_event_mouse* event)
{
	struct rtgui_topwin* wnd;
	struct rtgui_panel* panel;

	/* re-init to server thread */
	RTGUI_EVENT_MOUSE_BUTTON_INIT(event);

#ifdef RTGUI_USING_WINMOVE
	if (rtgui_winrect_is_moved() &&
		event->button & (RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_UP))
	{
		struct rtgui_topwin* topwin;
		rtgui_rect_t rect;

		if (rtgui_winrect_moved_done(&rect, &topwin) == RT_TRUE)
		{
			struct rtgui_event_win_move ewin;

			/* move window */
			RTGUI_EVENT_WIN_MOVE_INIT(&ewin);
			ewin.wid = topwin->wid;
			if (topwin->title != RT_NULL)
			{
				if (topwin->flag & WINTITLE_BORDER)
				{
					ewin.x = rect.x1 + WINTITLE_BORDER_SIZE;
					ewin.y = rect.y1 + WINTITLE_BORDER_SIZE;
				}
				if (!(topwin->flag & WINTITLE_NO)) ewin.y += WINTITLE_HEIGHT;
			}
			else
			{
				ewin.x = rect.x1;
				ewin.y = rect.y1;
			}

			/* send to client thread */
			rtgui_thread_send(topwin->tid, &(ewin.parent), sizeof(ewin));

			return;
		}
	}
#endif

	/* get the wnd which contains the mouse */
	wnd = rtgui_topwin_get_wnd(event->x, event->y);
	if (wnd != RT_NULL)
	{
		event->wid = wnd->wid;

		if (rtgui_server_focus_topwin != wnd)
		{
			/* raise this window */
			rtgui_topwin_activate_win(wnd);
			rtgui_server_focus_panel = RT_NULL;
		}

		if (wnd->title != RT_NULL &&
			rtgui_rect_contains_point(&(RTGUI_WIDGET(wnd->title)->extent), event->x, event->y) == RT_EOK)
		{
			rtgui_topwin_title_onmouse(wnd, event);
		}
		else
		{
			/* send mouse event to thread */
			rtgui_thread_send(wnd->tid, (struct rtgui_event*)event, sizeof(struct rtgui_event_mouse));
		}
		return ;
	}

	/* get the panel which contains the mouse */
	panel = rtgui_panel_get_contain(event->x, event->y);
	if ((panel != RT_NULL) && (panel->is_focusable == RT_TRUE))
	{
		/* deactivate old window */
		if (rtgui_server_focus_topwin != RT_NULL)
		{
			rtgui_topwin_deactivate_win(rtgui_server_focus_topwin);
		}

		rtgui_server_focus_panel = panel;
		rtgui_server_focus_topwin = RT_NULL;

		/* set destination window to null */
		event->wid = RT_NULL;

		/* send mouse event to thread */
		if (rtgui_panel_get_active_thread(panel) != RT_NULL)
		{
			rtgui_thread_send(rtgui_panel_get_active_thread(panel),
				(struct rtgui_event*)event,
				sizeof(struct rtgui_event_mouse));
		}
	}
}

static struct rtgui_panel* last_monitor_panel = RT_NULL;
static struct rtgui_topwin* last_monitor_topwin = RT_NULL;

void rtgui_server_handle_mouse_motion(struct rtgui_event_mouse* event)
{
	/* the topwin contains current mouse */
	struct rtgui_topwin* win 	= RT_NULL;
	struct rtgui_panel* panel 	= RT_NULL;

	/* re-init mouse event */
	RTGUI_EVENT_MOUSE_MOTION_INIT(event);

	/* find the panel or topwin which monitor the mouse motion */
	win = rtgui_topwin_get_wnd(event->x, event->y);
	if (win == RT_NULL)
	{
		/* try to find monitor on the panel */
		panel = rtgui_panel_get_contain(event->x, event->y);

		if (panel != RT_NULL)
		{
			struct rtgui_panel_thread* thread;

			/* get active panel thread */
			if (panel->thread_list.next != RT_NULL)
			{
				thread = rtgui_list_entry(panel->thread_list.next, struct rtgui_panel_thread, list);
				if (!rtgui_mouse_monitor_contains_point(&(thread->monitor_list),
					event->x, event->y) == RT_TRUE)
				{
					/* no monitor in this panel */
					panel = RT_NULL;
				}
			}
		}
	}
	else if (win->monitor_list.next != RT_NULL)
	{
		/* check whether the monitor exist */
		if (rtgui_mouse_monitor_contains_point(&(win->monitor_list), event->x, event->y) != RT_TRUE)
		{
			win = RT_NULL;

			/* try to find monitor on the panel */
			panel = rtgui_panel_get_contain(event->x, event->y);
			if (panel != RT_NULL)
			{
				struct rtgui_panel_thread* thread;

				/* get active panel thread */
				if (panel->thread_list.next != RT_NULL)
				{
					thread = rtgui_list_entry(panel->thread_list.next, struct rtgui_panel_thread, list);
					if (!rtgui_mouse_monitor_contains_point(&(thread->monitor_list),
						event->x, event->y) == RT_TRUE)
					{
						/* no monitor in this panel */
						panel = RT_NULL;
					}
				}
			}
		}
	}
	else
	{
		win = RT_NULL;
	}

	/* check old panel or window */
	if (last_monitor_panel != RT_NULL)
	{
		rt_thread_t tid = rtgui_panel_get_active_thread(last_monitor_panel);

		/* send mouse motion event */
		if (tid != RT_NULL)
		{
			event->wid = RT_NULL;
			rtgui_thread_send(tid, &(event->parent), sizeof(struct rtgui_event_mouse));
		}
	}
	else if (last_monitor_topwin != RT_NULL)
	{
		event->wid = last_monitor_topwin->wid;

		/* send mouse motion event */
		rtgui_thread_send(last_monitor_topwin->tid, &(event->parent), sizeof(struct rtgui_event_mouse));
	}

	if (last_monitor_panel != panel)
	{
		last_monitor_panel = panel;
		if (last_monitor_panel != RT_NULL)
		{
			rt_thread_t tid = rtgui_panel_get_active_thread(last_monitor_panel);
			event->wid = RT_NULL;

			/* send mouse motion event */
			if (tid != RT_NULL)
				rtgui_thread_send(tid, &(event->parent), sizeof(struct rtgui_event_mouse));
		}
	}

	if (last_monitor_topwin != win)
	{
		last_monitor_topwin = win;
		if (last_monitor_topwin != RT_NULL)
		{
			event->wid = last_monitor_topwin->wid;

			/* send mouse motion event */
			rtgui_thread_send(last_monitor_topwin->tid, &(event->parent), sizeof(struct rtgui_event_mouse));
		}
	}

	/* move mouse to (x, y) */
	rtgui_mouse_moveto(event->x, event->y);
}

void rtgui_server_handle_kbd(struct rtgui_event_kbd* event)
{
	struct rtgui_topwin* wnd;
	struct rtgui_panel* panel;

	/* re-init to server thread */
	RTGUI_EVENT_KBD_INIT(event);

	/* todo: handle input method and global shortcut */

	/* send to focus window or focus panel */
	wnd = rtgui_server_focus_topwin;
	if (wnd != RT_NULL && wnd->flag & WINTITLE_ACTIVATE)
	{
		/* send to focus window */
		event->wid = wnd->wid;

		/* send keyboard event to thread */
		rtgui_thread_send(wnd->tid, (struct rtgui_event*)event, sizeof(struct rtgui_event_kbd));

		return;
	}

	panel = rtgui_server_focus_panel;
	if (panel != RT_NULL)
	{
		rt_thread_t tid;

		/* get active thread in this panel */
		tid = rtgui_panel_get_active_thread(panel);
		if (tid != RT_NULL)
		{
			/* send to focus panel */
			event->wid = RT_NULL;

			/* send keyboard event to thread */
			rtgui_thread_send(tid, (struct rtgui_event*)event, sizeof(struct rtgui_event_kbd));
		}
	}
}

#ifdef __WIN32__
#include <windows.h>
#endif

/**
 * rtgui server thread's entry
 */
static void rtgui_server_entry(void* parameter)
{
#ifdef __WIN32__
	/* set the server thread to highest */
	HANDLE hCurrentThread = GetCurrentThread();
	SetThreadPriority(hCurrentThread, THREAD_PRIORITY_HIGHEST);
#endif

#ifdef RTGUI_USING_SMALL_SIZE
	/* create rtgui server msgq */
	rtgui_server_mq = rt_mq_create("rtgui",
		32, 16, RT_IPC_FLAG_FIFO);
#else
	/* create rtgui server msgq */
	rtgui_server_mq = rt_mq_create("rtgui",
		256, 8, RT_IPC_FLAG_FIFO);
#endif
	/* register rtgui server thread */
	rtgui_thread_register(rtgui_server_tid, rtgui_server_mq);

	/* init mouse and show */
	rtgui_mouse_init();
#ifdef RTGUI_USING_MOUSE_CURSOR
	rtgui_mouse_show_cursor();
#endif

	while (1)
	{
		/* the buffer uses to receive event */
#ifdef RTGUI_USING_SMALL_SIZE
		char event_buf[64];
#else
		char event_buf[256];
#endif
		struct rtgui_event* event = (struct rtgui_event*)&(event_buf[0]);

		if (rtgui_thread_recv(event, sizeof(event_buf)) == RT_EOK)
		{
			/* dispatch event */
			switch (event->type)
			{
			/* panel event */
			case RTGUI_EVENT_PANEL_ATTACH:
				/* register an application in panel */
				rtgui_server_create_application((struct rtgui_event_panel_attach*)event);
				break;

			case RTGUI_EVENT_PANEL_DETACH:
				/* unregister an application */
				rtgui_server_destroy_application((struct rtgui_event_panel_detach*)event);
				break;

			case RTGUI_EVENT_PANEL_SHOW:
				/* handle raise an application */
				rtgui_server_thread_panel_show((struct rtgui_event_panel_show*)event);
				break;

			case RTGUI_EVENT_PANEL_HIDE:
				/* handle hide an application */
				rtgui_server_thread_panel_hide((struct rtgui_event_panel_hide*)event);
				break;

			case RTGUI_EVENT_SET_WM:
				/* handle set workbench manager event */
				rtgui_server_handle_set_wm((struct rtgui_event_set_wm*)event);
				break;

			/* window event */
			case RTGUI_EVENT_WIN_CREATE:
				rtgui_thread_ack(event, RTGUI_STATUS_OK);
				rtgui_topwin_add((struct rtgui_event_win_create*)event);
				break;

			case RTGUI_EVENT_WIN_DESTROY:
				if (rtgui_topwin_remove(((struct rtgui_event_win*)event)->wid) == RT_EOK)
					rtgui_thread_ack(event, RTGUI_STATUS_OK);
				else
					rtgui_thread_ack(event, RTGUI_STATUS_ERROR);
				break;

			case RTGUI_EVENT_WIN_SHOW:
				rtgui_topwin_show((struct rtgui_event_win*)event);
				break;

			case RTGUI_EVENT_WIN_HIDE:
				rtgui_topwin_hide((struct rtgui_event_win*)event);
				break;

			case RTGUI_EVENT_WIN_MOVE:
				rtgui_topwin_move((struct rtgui_event_win_move*)event);
				break;

			case RTGUI_EVENT_WIN_RESIZE:
				rtgui_topwin_resize(((struct rtgui_event_win_resize*)event)->wid,
					&(((struct rtgui_event_win_resize*)event)->rect));
				break;

			/* other event */
			case RTGUI_EVENT_UPDATE_BEGIN:
#ifdef RTGUI_USING_MOUSE_CURSOR
				/* hide cursor */
				rtgui_mouse_hide_cursor();
#endif
				break;

			case RTGUI_EVENT_UPDATE_END:
				/* handle screen update */
				rtgui_server_handle_update((struct rtgui_event_update_end*)event);
#ifdef RTGUI_USING_MOUSE_CURSOR
				/* show cursor */
				rtgui_mouse_show_cursor();
#endif
				break;

			case RTGUI_EVENT_MONITOR_ADD:
				/* handle mouse monitor */
				rtgui_server_handle_monitor_add((struct rtgui_event_monitor*)event);
				break;

			/* mouse and keyboard event */
			case RTGUI_EVENT_MOUSE_MOTION:
				/* handle mouse motion event */
				rtgui_server_handle_mouse_motion((struct rtgui_event_mouse*)event);
				break;

			case RTGUI_EVENT_MOUSE_BUTTON:
				/* handle mouse button */
				rtgui_server_handle_mouse_btn((struct rtgui_event_mouse*)event);
				break;

			case RTGUI_EVENT_KBD:
				/* handle keyboard event */
				rtgui_server_handle_kbd((struct rtgui_event_kbd*)event);
				break;

			case RTGUI_EVENT_COMMAND:
				break;
			}
		}
	}

	/* unregister in rtgui thread */
	// rtgui_thread_deregister(rt_thread_self());
}

void rtgui_server_post_event(struct rtgui_event* event, rt_size_t size)
{
	rt_mq_send(rtgui_server_mq, event, size);
}

void rtgui_server_init()
{
	rtgui_server_tid = rt_thread_create("rtgui",
		rtgui_server_entry, RT_NULL,
		RTGUI_SVR_THREAD_STACK_SIZE,
		RTGUI_SVR_THREAD_PRIORITY,
		RTGUI_SVR_THREAD_TIMESLICE);

	/* start rtgui server thread */
	if (rtgui_server_tid != RT_NULL)
		rt_thread_startup(rtgui_server_tid);
}
