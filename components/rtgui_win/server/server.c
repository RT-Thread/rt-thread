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
#include <topwin.h>
#include <rtgui/event.h>
#include <panel.h>
#include <mouse.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/window.h>
#include <rtgui/rtgui_theme.h>

static struct rt_messagequeue *rtgui_server_mq;

extern rtgui_win_t* rtgui_server_focus_win;

void rtgui_server_handle_update(rtgui_event_update_t* event)
{
	const struct rtgui_graphic_driver* gd = rtgui_graphic_driver_get_default();
	gd->screen_update(&(event->rect));
}

void rtgui_server_handle_mouse_btn(rtgui_event_mouse_t* event)
{
	rtgui_win_t* win;
	rtgui_panel_t* panel=rtgui_panel_get();

	/* re-init to server thread */
	RTGUI_EVENT_MOUSE_BUTTON_INIT(event);

#ifdef RTGUI_USING_WINMOVE
	if (rtgui_winrect_is_moved() &&
		event->button & (RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_UP))
	{/* 释放鼠标按键后,更新窗口位置 */
		rtgui_win_t *wid;
		rtgui_rect_t rect;

		if (rtgui_winrect_moved_done(&rect, &wid) == RT_TRUE)
		{
			struct rtgui_event_win_move ewin;

			/* move window */
			RTGUI_EVENT_WIN_MOVE_INIT(&ewin);
			ewin.wid = wid;

			ewin.x = rect.x1;
			ewin.y = rect.y1;
			
			/* send to client thread */
			rtgui_thread_send(wid->tid, &(ewin.parent), sizeof(ewin));

			return;
		}
	}
#endif

	if(RTGUI_PANEL_IS_MODAL_MODE(panel))
	{
		if(panel->modal_widget != RT_NULL && RTGUI_IS_WIN(panel->modal_widget))
		{
			win = RTGUI_WIN(panel->modal_widget);
			
			if(rtgui_rect_contains_point(&(RTGUI_WIDGET_EXTENT(win)), event->x, event->y) != RT_EOK)
			{
				win->status &= ~RTGUI_WIN_STATUS_ACTIVATE;
				rtgui_theme_draw_win_title(win);
				win->status |= RTGUI_WIN_STATUS_ACTIVATE;
				rtgui_theme_draw_win_title(win);
				win->status &= ~RTGUI_WIN_STATUS_ACTIVATE;
				rtgui_theme_draw_win_title(win);
				win->status |= RTGUI_WIN_STATUS_ACTIVATE;
				rtgui_theme_draw_win_title(win);
				return;	
			}	
		}
	}
	/* 是否在一个窗口上 */
	win = rtgui_topwin_get_wnd(event->x, event->y);

	if(win != RT_NULL)
	{
		rtgui_rect_t rect;
		
		event->wid = win;
		if(rtgui_server_focus_win != win)
		{//不是焦点窗口,则举升它
			rt_kprintf("1.raise win.");
			rtgui_topwin_raise(win);
		}

		rtgui_win_get_title_rect(win, &rect);
		rtgui_widget_rect_to_device(win, &rect);
		if(rtgui_rect_contains_point(&rect, event->x, event->y) == RT_EOK)
		{//鼠标在窗口的标题栏
			rtgui_topwin_title_onmouse(win, event);
		}
		else
		{//鼠标在窗口的客户区	
			/*if(win->style & RTGUI_WIN_CLOSEBOX_PRESSED)
			{
				win->style &= ~RTGUI_WIN_CLOSEBOX_PRESSED;
				rtgui_theme_draw_win_closebox(win);
			}*/
			/* send mouse event to thread */
			rtgui_thread_send(win->tid, (rtgui_event_t*)event, sizeof(rtgui_event_mouse_t));
		}
		return;
	}

	//发送消息到panel
	/* deactivate old window */
	if (rtgui_server_focus_win != RT_NULL)
	{
		rtgui_topwin_deactivate(rtgui_server_focus_win);
	}
	rtgui_server_focus_win = RT_NULL;
	event->wid = RT_NULL; 
	rtgui_thread_send(panel->tid,(rtgui_event_t*)event,sizeof(rtgui_event_mouse_t));
}

//static rt_bool_t motion_down=0;
//static rt_int16_t downx,downy;
//鼠标手势处理句柄
void rtgui_server_handle_mouse_motion(rtgui_event_mouse_t* event)
{
	rtgui_panel_t* panel;
	rtgui_win_t* win=RT_NULL;

	panel = rtgui_panel_get();

	if(panel != RT_NULL)
	{
		win = rtgui_topwin_get_wnd(event->x, event->y);
	
		if(win != RT_NULL)
		{	/* send mouse event to thread */
			rtgui_thread_send(win->tid, (rtgui_event_t*)event, sizeof(rtgui_event_mouse_t));
		}
		else 
		{	//发送消息到panel
			rtgui_thread_send(panel->tid,(rtgui_event_t*)event,sizeof(rtgui_event_mouse_t));
		}
	}
	/* move mouse to (x, y) */
	rtgui_mouse_moveto(event->x, event->y);
}

void rtgui_server_handle_kbd(rtgui_event_kbd_t* event)
{
	rtgui_win_t *win;
	rtgui_panel_t *panel;

	/* re-init to server thread */
	RTGUI_EVENT_KBD_INIT(event);

	/* send to focus window or focus panel */
	panel = rtgui_panel_get();

	if(panel != RT_NULL)
	{	
		win = rtgui_server_focus_win;
		if(win != RT_NULL && win->status & RTGUI_WIN_STATUS_ACTIVATE)
		{
			event->wid = win;
			rtgui_thread_send(win->tid, (rtgui_event_t*)event, sizeof(rtgui_event_kbd_t));
		}
		else 
		{//发送消息到panel
			event->wid = RT_NULL;
			rtgui_thread_send(panel->tid,(rtgui_event_t*)event,sizeof(rtgui_event_kbd_t));
		}
	}
}

void rtgui_server_handle_current_pos(rtgui_event_current_pos_t* event)
{
	struct rt_thread *thread = rtgui_panel_get()->tid;

	/* re-init to server thread */
	RTGUI_EVENT_CURRENT_POS_INIT(event);

	/* send to panel */
	if(thread != RT_NULL)
	{//要用同步方式发送事件,否则会引起触摸屏检测死机
		rtgui_thread_send_sync(thread, (rtgui_event_t*)event, sizeof(rtgui_event_current_pos_t));
	}
}

/**
 * rtgui server thread's entry
 */
static void rtgui_server_entry(void* parameter)
{
	/* create rtgui server msgq */
	rtgui_server_mq = rt_mq_create("rtgui", 256, 8, RT_IPC_FLAG_FIFO);


	/* register rtgui server thread */
	rtgui_thread_register(rt_thread_self(), rtgui_server_mq);

	/* init mouse and show */
	rtgui_mouse_init();
#ifdef RTGUI_USING_MOUSE_CURSOR
	rtgui_mouse_show_cursor();
#endif

	while(1)
	{
		/* the buffer uses to receive event */
		char event_buf[256];
		rtgui_event_t* event = (rtgui_event_t*)&(event_buf[0]);

		if(rtgui_thread_recv(event, sizeof(event_buf)) == RT_EOK)
		{
			/* dispatch event */
			switch (event->type)
			{
				case RTGUI_EVENT_WIN_CREATE:
					if (rtgui_topwin_add(((rtgui_event_win_t*)event)->wid) == RT_EOK)
						rtgui_thread_ack(event, RTGUI_STATUS_OK);
					else
						rtgui_thread_ack(event, RTGUI_STATUS_ERROR);
					break;

				case RTGUI_EVENT_WIN_DESTROY:
					if (rtgui_topwin_remove(((rtgui_event_win_t*)event)->wid) == RT_EOK)
						rtgui_thread_ack(event, RTGUI_STATUS_OK);
					else
						rtgui_thread_ack(event, RTGUI_STATUS_ERROR);
					break;
	
				case RTGUI_EVENT_WIN_SHOW:
					if (rtgui_topwin_show(((rtgui_event_win_t*)event)->wid) == RT_EOK)
						rtgui_thread_ack(event, RTGUI_STATUS_OK);
					else
						rtgui_thread_ack(event, RTGUI_STATUS_ERROR);
					break;
	
				case RTGUI_EVENT_WIN_HIDE:
					if (rtgui_topwin_hide(((rtgui_event_win_t*)event)->wid) == RT_EOK)
						rtgui_thread_ack(event, RTGUI_STATUS_OK);
					else
						rtgui_thread_ack(event, RTGUI_STATUS_ERROR);
					break;
	
				case RTGUI_EVENT_WIN_MOVE: 
					if (rtgui_topwin_move(((rtgui_event_win_move_t*)event)->wid,
							((rtgui_event_win_move_t*)event)->x,
							((rtgui_event_win_move_t*)event)->y))
						rtgui_thread_ack(event, RTGUI_STATUS_OK);
					else
						rtgui_thread_ack(event, RTGUI_STATUS_ERROR);
					break;
	
				case RTGUI_EVENT_WIN_RESIZE:
					rtgui_topwin_resize(((rtgui_event_win_resize_t*)event)->wid,
						&(((rtgui_event_win_resize_t*)event)->rect));
					break;
	
				case RTGUI_EVENT_UPDATE:
					/* handle screen update */
					rtgui_server_handle_update((rtgui_event_update_t*)event);
#ifdef RTGUI_USING_MOUSE_CURSOR
					/* show cursor */
					rtgui_mouse_show_cursor();
#endif
					break;
				
				case RTGUI_EVENT_MOUSE_MOTION:
					rtgui_server_handle_mouse_motion((rtgui_event_mouse_t*)event);
					break;
	
				case RTGUI_EVENT_MOUSE_BUTTON:
					rtgui_server_handle_mouse_btn((rtgui_event_mouse_t*)event);
					break;
	
				case RTGUI_EVENT_KBD:
					rtgui_server_handle_kbd((rtgui_event_kbd_t*)event);
					break;
	
				case RTGUI_EVENT_CURRENT_POS:
					rtgui_server_handle_current_pos((rtgui_event_current_pos_t*)event);
					break;
	
				case RTGUI_EVENT_COMMAND:
					break;
			}
		}
	}
}

void rtgui_server_post_event(rtgui_event_t* event, rt_size_t size)
{
	rt_mq_send(rtgui_server_mq, event, size);
}

void rtgui_server_init(void)
{
	struct rt_thread* rtgui_server_tid;
	rtgui_server_tid = rt_thread_create("rtgui",
		rtgui_server_entry, RT_NULL,
		RTGUI_SVR_THREAD_STACK_SIZE,
		RTGUI_SVR_THREAD_PRIORITY,
		RTGUI_SVR_THREAD_TIMESLICE);

	/* start rtgui server thread */
	if(rtgui_server_tid != RT_NULL)
		rt_thread_startup(rtgui_server_tid);
}
