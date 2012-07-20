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
#include <rtgui/rtgui_object.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/driver.h>

#include "mouse.h"
#include "topwin.h"

static struct rt_thread *rtgui_server_tid;

static struct rtgui_app *rtgui_server_application = RT_NULL;
static struct rtgui_app *rtgui_wm_application = RT_NULL;

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
	/* add monitor rect to top window list */
	rtgui_topwin_append_monitor_rect(event->wid, &(event->rect));
}

void rtgui_server_handle_monitor_remove(struct rtgui_event_monitor* event)
{
	/* add monitor rect to top window list */
	rtgui_topwin_remove_monitor_rect(event->wid, &(event->rect));
}

void rtgui_server_handle_mouse_btn(struct rtgui_event_mouse* event)
{
	struct rtgui_topwin* wnd;

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
			rtgui_send(topwin->tid, &(ewin.parent), sizeof(ewin));

			return;
		}
	}
#endif

	/* get the wnd which contains the mouse */
	wnd = rtgui_topwin_get_wnd_no_modaled(event->x, event->y);
	if (wnd != RT_NULL)
	{
		event->wid = wnd->wid;

		if (rtgui_topwin_get_focus() != wnd)
		{
			/* raise this window */
			rtgui_topwin_activate_topwin(wnd);
		}

		if (wnd->title != RT_NULL &&
			rtgui_rect_contains_point(&(RTGUI_WIDGET(wnd->title)->extent), event->x, event->y) == RT_EOK)
		{
			rtgui_topwin_title_onmouse(wnd, event);
		}
		else
		{
			/* send mouse event to thread */
			rtgui_send(wnd->tid, (struct rtgui_event*)event, sizeof(struct rtgui_event_mouse));
		}
		return ;
	}
}

static struct rtgui_topwin* last_monitor_topwin = RT_NULL;

void rtgui_server_handle_mouse_motion(struct rtgui_event_mouse* event)
{
	/* the topwin contains current mouse */
	struct rtgui_topwin* win 	= RT_NULL;

	/* re-init mouse event */
	RTGUI_EVENT_MOUSE_MOTION_INIT(event);

	win = rtgui_topwin_get_wnd_no_modaled(event->x, event->y);
	if (win != RT_NULL && win->monitor_list.next != RT_NULL)
	{
		// FIXME:
		/* check whether the monitor exist */
		if (rtgui_mouse_monitor_contains_point(&(win->monitor_list),
											   event->x, event->y) != RT_TRUE)
		{
			win = RT_NULL;
		}
	}

	if (last_monitor_topwin != RT_NULL)
	{
		event->wid = last_monitor_topwin->wid;
		/* send mouse motion event */
		rtgui_send(last_monitor_topwin->tid, &(event->parent), sizeof(struct rtgui_event_mouse));
	}

	if (last_monitor_topwin != win)
	{
		last_monitor_topwin = win;
		if (last_monitor_topwin != RT_NULL)
		{
			event->wid = last_monitor_topwin->wid;

			/* send mouse motion event */
			rtgui_send(last_monitor_topwin->tid, &(event->parent), sizeof(struct rtgui_event_mouse));
		}
	}

	/* move mouse to (x, y) */
	rtgui_mouse_moveto(event->x, event->y);
}

void rtgui_server_handle_kbd(struct rtgui_event_kbd* event)
{
	struct rtgui_topwin* wnd;

	/* re-init to server thread */
	RTGUI_EVENT_KBD_INIT(event);

	/* todo: handle input method and global shortcut */

	wnd = rtgui_topwin_get_focus();
	if (wnd != RT_NULL)
	{
		RT_ASSERT(wnd->flag & WINTITLE_ACTIVATE)

		/* send to focus window */
		event->wid = wnd->wid;

		/* send keyboard event to thread */
		rtgui_send(wnd->tid, (struct rtgui_event*)event, sizeof(struct rtgui_event_kbd));

		return;
	}
}

#ifdef _WIN32
#include <windows.h>
#endif

static rt_bool_t rtgui_server_event_handler(struct rtgui_object *object,
                                            struct rtgui_event *event)
{
    RT_ASSERT(object != RT_NULL);
    RT_ASSERT(event != RT_NULL);

    /* dispatch event */
    switch (event->type)
    {
    case RTGUI_EVENT_APP_CREATE:
	case RTGUI_EVENT_APP_DESTROY:
		if (rtgui_wm_application != RT_NULL)
		{
			/* forward event to wm application */
			rtgui_send(rtgui_wm_application->tid, event, sizeof(struct rtgui_event_application));
		}
		else
		{
			/* always ack with OK */
			rtgui_ack(event, RTGUI_STATUS_OK);
		}
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

		/* window event */
    case RTGUI_EVENT_WIN_CREATE:
        if (rtgui_topwin_add((struct rtgui_event_win_create*)event) == RT_EOK)
			rtgui_ack(event, RTGUI_STATUS_OK);
		else
			rtgui_ack(event, RTGUI_STATUS_ERROR);
        break;

    case RTGUI_EVENT_WIN_SHOW:
        if (rtgui_topwin_show((struct rtgui_event_win*)event) == RT_EOK)
            rtgui_ack(event, RTGUI_STATUS_OK);
        else
            rtgui_ack(event, RTGUI_STATUS_ERROR);
        break;

    case RTGUI_EVENT_WIN_HIDE:
        if (rtgui_topwin_hide((struct rtgui_event_win*)event) == RT_EOK)
            rtgui_ack(event, RTGUI_STATUS_OK);
        else
            rtgui_ack(event, RTGUI_STATUS_ERROR);
        break;

    case RTGUI_EVENT_WIN_MOVE:
        if (rtgui_topwin_move((struct rtgui_event_win_move*)event) == RT_EOK)
            rtgui_ack(event, RTGUI_STATUS_OK);
        else
            rtgui_ack(event, RTGUI_STATUS_ERROR);
        break;

	case RTGUI_EVENT_WIN_MODAL_ENTER:
		if (rtgui_topwin_modal_enter((struct rtgui_event_win_modal_enter*)event) == RT_EOK)
			rtgui_ack(event, RTGUI_STATUS_OK);
		else
			rtgui_ack(event, RTGUI_STATUS_ERROR);
		break;

	case RTGUI_EVENT_WIN_ACTIVATE:
		if (rtgui_topwin_activate((struct rtgui_event_win_activate*)event) == RT_EOK)
			rtgui_ack(event, RTGUI_STATUS_OK);
		else
			rtgui_ack(event, RTGUI_STATUS_ERROR);
		break;

    case RTGUI_EVENT_WIN_DESTROY:
		if (last_monitor_topwin != RT_NULL &&
			last_monitor_topwin->wid == ((struct rtgui_event_win*)event)->wid)
				last_monitor_topwin = RT_NULL;
        if (rtgui_topwin_remove(((struct rtgui_event_win*)event)->wid) == RT_EOK)
            rtgui_ack(event, RTGUI_STATUS_OK);
        else
            rtgui_ack(event, RTGUI_STATUS_ERROR);
        break;

    case RTGUI_EVENT_WIN_RESIZE:
        rtgui_topwin_resize(((struct rtgui_event_win_resize*)event)->wid,
                &(((struct rtgui_event_win_resize*)event)->rect));
        break;

	case RTGUI_EVENT_SET_WM:
		if (rtgui_wm_application != RT_NULL)
		{
			rtgui_ack(event, RTGUI_STATUS_ERROR);
		}
		else
		{
			struct rtgui_event_set_wm *set_wm;

			set_wm = (struct rtgui_event_set_wm*) event;
			rtgui_wm_application = set_wm->app;
			rtgui_ack(event, RTGUI_STATUS_OK);
		}
		break;

        /* other event */
    case RTGUI_EVENT_COMMAND:
        break;

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
    }

	return RT_TRUE;
}

/**
 * rtgui server thread's entry
 */
static void rtgui_server_entry(void* parameter)
{
#ifdef _WIN32
	/* set the server thread to highest */
	HANDLE hCurrentThread = GetCurrentThread();
	SetThreadPriority(hCurrentThread, THREAD_PRIORITY_HIGHEST);
#endif

	/* create rtgui server application */
	rtgui_server_application = rtgui_app_create(rtgui_server_tid,
                                                        "rtgui");
    if (rtgui_server_application == RT_NULL)
        return;

    rtgui_object_set_event_handler(RTGUI_OBJECT(rtgui_server_application),
                                   rtgui_server_event_handler);
	/* init mouse and show */
	rtgui_mouse_init();
#ifdef RTGUI_USING_MOUSE_CURSOR
	rtgui_mouse_show_cursor();
#endif

    rtgui_app_run(rtgui_server_application);

    rtgui_app_destroy(rtgui_server_application);
    rtgui_server_application = RT_NULL;
}

void rtgui_server_post_event(struct rtgui_event* event, rt_size_t size)
{
	if (rtgui_server_tid != RT_NULL)
		rtgui_send(rtgui_server_tid, event, size);
	else
		rt_kprintf("post when server is not running\n");
}

rt_err_t rtgui_server_post_event_sync(struct rtgui_event* event, rt_size_t size)
{
	if (rtgui_server_tid != RT_NULL)
		return rtgui_send_sync(rtgui_server_tid, event, size);
	else
	{
		rt_kprintf("post when server is not running\n");
		return -RT_ENOSYS;
	}
}

void rtgui_server_init(void)
{
    if (rtgui_server_tid != RT_NULL)
        return;

	rtgui_server_tid = rt_thread_create("rtgui",
		rtgui_server_entry, RT_NULL,
		RTGUI_SVR_THREAD_STACK_SIZE,
		RTGUI_SVR_THREAD_PRIORITY,
		RTGUI_SVR_THREAD_TIMESLICE);

	/* start rtgui server thread */
	if (rtgui_server_tid != RT_NULL)
		rt_thread_startup(rtgui_server_tid);
}
