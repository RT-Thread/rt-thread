/*
 * File      : topwin.c
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
#include "panel.h"
#include "topwin.h"
#include "mouse.h"

#include <rtgui/event.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/window.h>

struct rtgui_topwin* rtgui_server_focus_topwin = RT_NULL;

static struct rtgui_list_node _rtgui_topwin_show_list;
static struct rtgui_list_node _rtgui_topwin_hide_list;
static struct rt_semaphore _rtgui_topwin_lock;

static void rtgui_topwin_update_clip(void);
static void rtgui_topwin_redraw(struct rtgui_rect* rect);

void rtgui_topwin_init()
{
	/* init window list */
	rtgui_list_init(&_rtgui_topwin_show_list);
	rtgui_list_init(&_rtgui_topwin_hide_list);

	rt_sem_init(&_rtgui_topwin_lock, 
		"topwin", 1, RT_IPC_FLAG_FIFO);
}

static struct rtgui_topwin*
rtgui_topwin_search_in_list(struct rtgui_win* wid, struct rtgui_list_node* list)
{
	struct rtgui_list_node* node;
	struct rtgui_topwin* topwin;

	/* search in list */
	rtgui_list_foreach(node, list)
	{
		topwin = rtgui_list_entry(node, struct rtgui_topwin, list);

		/* is this node? */
		if (topwin->wid == wid)
		{
			return topwin;
		}
	}

	return RT_NULL;
}

/* add a window to window list[hide] */
rt_err_t rtgui_topwin_add(struct rtgui_event_win_create* event)
{
	struct rtgui_topwin* topwin;

	topwin = rtgui_malloc(sizeof(struct rtgui_topwin));
	if (topwin == RT_NULL) return -RT_ERROR;

	topwin->wid 	= event->wid;
#ifdef RTGUI_USING_SMALL_SIZE
	topwin->extent	= RTGUI_WIDGET(event->wid)->extent;
#else
	topwin->extent 	= event->extent;
#endif
	topwin->tid 	= event->parent.sender;

	topwin->flag 	= 0;
	if (event->parent.user & RTGUI_WIN_STYLE_NO_TITLE) topwin->flag |= WINTITLE_NO;
	if (event->parent.user & RTGUI_WIN_STYLE_CLOSEBOX) topwin->flag |= WINTITLE_CLOSEBOX;
	if (!(event->parent.user & RTGUI_WIN_STYLE_NO_BORDER)) topwin->flag |= WINTITLE_BORDER;
	if (event->parent.user & RTGUI_WIN_STYLE_NO_FOCUS) topwin->flag |= WINTITLE_NOFOCUS;

	if(!(topwin->flag & WINTITLE_NO) || (topwin->flag & WINTITLE_BORDER))
	{
		/* get win extent */
		rtgui_rect_t rect = topwin->extent;

		/* add border rect */
		if (topwin->flag & WINTITLE_BORDER)
		{
			rtgui_rect_inflate(&rect, WINTITLE_BORDER_SIZE);
		}

		/* add title rect */
		if (!(topwin->flag & WINTITLE_NO)) rect.y1 -= WINTITLE_HEIGHT;

#ifdef RTGUI_USING_SMALL_SIZE
		topwin->title = rtgui_wintitle_create(event->wid->title);
#else
		topwin->title = rtgui_wintitle_create((const char*)event->title);
#endif
		rtgui_widget_set_rect(RTGUI_WIDGET(topwin->title), &rect);

		/* update clip info */
		rtgui_toplevel_update_clip(RTGUI_TOPLEVEL(topwin->title));
		rtgui_region_subtract_rect(&(RTGUI_WIDGET(topwin->title)->clip),
			&(RTGUI_WIDGET(topwin->title)->clip),
			&(topwin->extent));
	}
	else topwin->title = RT_NULL;

	rtgui_list_init(&topwin->list);
	rtgui_list_init(&topwin->monitor_list);

	/* add topwin node to the hidden window list */
	rtgui_list_insert(&(_rtgui_topwin_hide_list), &(topwin->list));

	return RT_EOK;
}

rt_err_t rtgui_topwin_remove(struct rtgui_win* wid)
{
	struct rtgui_topwin* topwin;

	/* find the topwin node */
	topwin = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_show_list);

	if (topwin)
	{
		/* remove node from list */
		rtgui_list_remove(&_rtgui_topwin_show_list, &(topwin->list));

		rtgui_topwin_update_clip();

		/* redraw the old rect */
		rtgui_topwin_redraw(&(topwin->extent));

		if (rtgui_server_focus_topwin == topwin)
		{
			/* activate the next window */
			if (_rtgui_topwin_show_list.next != RT_NULL)
			{
				struct rtgui_event_win wevent;
				struct rtgui_topwin* wnd;

				/* get the topwin */
				wnd = rtgui_list_entry(_rtgui_topwin_show_list.next,
					struct rtgui_topwin, list);

				/* activate the window */
				RTGUI_EVENT_WIN_ACTIVATE_INIT(&wevent);
				wevent.wid = wnd->wid;
				rtgui_thread_send(wnd->tid, &(wevent.parent), sizeof(struct rtgui_event_win));

				/* set new focus topwin */
				rtgui_server_focus_topwin = wnd;
			}
			else
			{
				/* there is no shown window right now */
				rtgui_server_focus_topwin = RT_NULL;
			}
		}

		/* free the monitor rect list, topwin node and title */
		while (topwin->monitor_list.next != RT_NULL)
		{
			struct rtgui_mouse_monitor* monitor = rtgui_list_entry(topwin->monitor_list.next,
				struct rtgui_mouse_monitor, list);

			topwin->monitor_list.next = topwin->monitor_list.next->next;
			rtgui_free(monitor);
		}

		/* destroy win title */
		rtgui_wintitle_destroy(topwin->title);
		topwin->title = RT_NULL;

		rtgui_free(topwin);

		return RT_EOK;
	}

	topwin = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_hide_list);
	if (topwin)
	{
		/* remove node from list */
		rtgui_list_remove(&_rtgui_topwin_hide_list, &(topwin->list));

		/* free the topwin node and title */
		rtgui_wintitle_destroy(topwin->title);
		topwin->title = RT_NULL;

		rtgui_free(topwin);

		return RT_EOK;
	}

	return -RT_ERROR;
}

/* activate a win
 * - deactivate the old focus win
 * - activate a win
 * - set the focus win to activate win
 * - draw win title
 */
void rtgui_topwin_activate_win(struct rtgui_topwin* win)
{
	struct rtgui_event_win event;

	/* activate the raised window */
	RTGUI_EVENT_WIN_ACTIVATE_INIT(&event);
	event.wid = win->wid;
	rtgui_thread_send(win->tid, &(event.parent), sizeof(struct rtgui_event_win));

	/* redraw title */
	if (win->title != RT_NULL)
	{
		win->flag |= WINTITLE_ACTIVATE;
		rtgui_theme_draw_win(win);
	}

	if ((rtgui_server_focus_topwin != RT_NULL) && (rtgui_server_focus_topwin != win))
	{
		/* deactivate the old focus win  */
		RTGUI_EVENT_WIN_DEACTIVATE_INIT(&event);
		event.wid = rtgui_server_focus_topwin->wid;
		rtgui_thread_send(rtgui_server_focus_topwin->tid,
			&event.parent, sizeof(struct rtgui_event_win));

		/* redraw title */
		if (rtgui_server_focus_topwin->title != RT_NULL)
		{
			rtgui_server_focus_topwin->flag &= ~WINTITLE_ACTIVATE;
			rtgui_theme_draw_win(rtgui_server_focus_topwin);
		}
	}

	rtgui_server_focus_topwin = win;
}

/*
 * deactivate a win
 * - deactivate the win
 * - redraw win title
 * - set rtgui_server_focus_topwin
 */
void rtgui_topwin_deactivate_win(struct rtgui_topwin* win)
{
	/* deactivate win */
	struct rtgui_event_win event;
	RTGUI_EVENT_WIN_DEACTIVATE_INIT(&event);
	event.wid = win->wid;
	rtgui_thread_send(win->tid,
		&event.parent, sizeof(struct rtgui_event_win));

	win->flag &= ~WINTITLE_ACTIVATE;
	rtgui_theme_draw_win(win);

	if (rtgui_server_focus_topwin == win)
	{
		rtgui_server_focus_topwin = RT_NULL;
	}
}

/* raise window to front */
void rtgui_topwin_raise(struct rtgui_win* wid, rt_thread_t sender)
{
	struct rtgui_topwin* topwin;
	struct rtgui_list_node* node;
	struct rtgui_event_clip_info eclip;

	RTGUI_EVENT_CLIP_INFO_INIT(&eclip);
	eclip.wid = RT_NULL;

	/* the window is already placed in front */
	if (&(topwin->list) == _rtgui_topwin_show_list.next)
	{
		rtgui_server_focus_topwin = RT_NULL;
		rtgui_topwin_activate_win(topwin);
	    return ;
	}

	// rt_sem_take(&_rtgui_topwin_lock, RT_WAITING_FOREVER);
	/* find the topwin node */
	for (node = _rtgui_topwin_show_list.next; node->next != RT_NULL; node = node->next)
	{
		topwin = rtgui_list_entry(node->next, struct rtgui_topwin, list);
		if (topwin->wid == wid)
		{
			/* found target */

			struct rtgui_list_node* n;
			n = node->next;
			/* remove node */
			node->next = node->next->next;
			/* insert node to the header */
			n->next = _rtgui_topwin_show_list.next;
			_rtgui_topwin_show_list.next = n;

			/* send clip update to each upper window */
			for (n = _rtgui_topwin_show_list.next; n != node->next; n = n->next)
			{
				struct rtgui_topwin* wnd = rtgui_list_entry(n, struct rtgui_topwin, list);
				eclip.wid = wnd->wid;

				/* send to destination window */
				rtgui_thread_send(wnd->tid, &(eclip.parent), sizeof(struct rtgui_event_clip_info));

				/* reset clip info in title */
				if (wnd->title != RT_NULL)
				{
					rtgui_toplevel_update_clip(RTGUI_TOPLEVEL(wnd->title));
					rtgui_region_subtract_rect(&(RTGUI_WIDGET(wnd->title)->clip),
						&(RTGUI_WIDGET(wnd->title)->clip),
						&(wnd->extent));
				}
			}

			/* active window */
			rtgui_topwin_activate_win(topwin);
			break;
		}
	}
	// rt_sem_release(&_rtgui_topwin_lock);
}

/* show a window */
void rtgui_topwin_show(struct rtgui_event_win* event)
{
	struct rtgui_topwin* topwin;
	struct rtgui_win* wid = event->wid;
	rt_thread_t sender = RTGUI_EVENT(event)->sender;

	/* find in hide list */
	topwin = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_hide_list);

	/* find it */
	if (topwin != RT_NULL)
	{
		/* remove node from hidden list */
		rtgui_list_remove(&_rtgui_topwin_hide_list, &(topwin->list));

		/* add node to show list */
		rtgui_list_insert(&_rtgui_topwin_show_list, &(topwin->list));

		/* show window title */
		if (topwin->title != RT_NULL)
		{
			RTGUI_WIDGET_UNHIDE(RTGUI_WIDGET(topwin->title));
		}

		/* update clip info */
		rtgui_topwin_update_clip();

		rtgui_thread_ack(RTGUI_EVENT(event), RTGUI_STATUS_OK);

		/* activate this window */
		rtgui_topwin_activate_win(topwin);
	}
	else
	{
		/* the wnd is located in show list, raise wnd to front */
		topwin = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_show_list);
		if (topwin != RT_NULL)
		{
			if (_rtgui_topwin_show_list.next != &(topwin->list))
			{
				rtgui_thread_ack(RTGUI_EVENT(event), RTGUI_STATUS_OK);

				/* not the front window, raise it */
				rtgui_topwin_raise(wid, sender);
			}
			else
			{
				/* just raise it */
				rtgui_topwin_raise(wid, sender);
			}
		}
		else
		{
			/* there is no wnd in wnd list */
			rtgui_thread_ack(RTGUI_EVENT(event), RTGUI_STATUS_ERROR);
		}
	}
}

/* send clip info to panel */
#ifdef RTGUI_USING_SMALL_SIZE
void rtgui_topwin_update_clip_to_panel(struct rtgui_panel* panel)
{
	rt_uint32_t count;
	rt_thread_t tid;
	struct rtgui_list_node* node;
	struct rtgui_event_clip_info eclip;

	/* get topwin count  */
	count = 0;
	node = _rtgui_topwin_show_list.next;
	while (node != RT_NULL)
	{
		count ++;
		node = node->next;
	}

	/* send clip info event to panel */
	RTGUI_EVENT_CLIP_INFO_INIT(&eclip);
	eclip.num_rect = count; eclip.wid = RT_NULL;

	/* send to the activated thread of panel */
	tid = rtgui_panel_get_active_thread(panel);
	rtgui_thread_send(tid, &eclip.parent, sizeof(struct rtgui_event_clip_info));
}
#else
void rtgui_topwin_update_clip_to_panel(struct rtgui_panel* panel)
{
	rt_uint32_t count;
	rt_thread_t tid;
	struct rtgui_list_node* node;
	struct rtgui_event_clip_info* eclip;

	/* get topwin count  */
	count = 0;
	node = _rtgui_topwin_show_list.next;
	while (node != RT_NULL)
	{
		count ++;
		node = node->next;
	}

	eclip = (struct rtgui_event_clip_info*)rtgui_malloc(sizeof(struct rtgui_event_clip_info)
		+ (count + 1)* sizeof(struct rtgui_rect));
	if (eclip == RT_NULL)
	{
		/* no memory */
		return ;
	}

	/* reset clip info to top window */
	RTGUI_EVENT_CLIP_INFO_INIT(eclip);
	eclip->num_rect = count; eclip->wid = RT_NULL;

	count = 0;
	for (node = _rtgui_topwin_show_list.next; node != RT_NULL; node  = node->next)
	{
		struct rtgui_topwin* wnd;
		struct rtgui_rect* rect;

		wnd = rtgui_list_entry(node, struct rtgui_topwin, list);

		rect = RTGUI_EVENT_GET_RECT(eclip, count++);
		*rect = (wnd->title != RT_NULL)? RTGUI_WIDGET(wnd->title)->extent : wnd->extent;
	}

	/* send to the activated thread of panel */
	tid = rtgui_panel_get_active_thread(panel);
	rtgui_thread_send(tid, (struct rtgui_event*)eclip, sizeof(struct rtgui_event_clip_info)
		+ count* sizeof(struct rtgui_rect));

	/* release clip info event */
	rtgui_free(eclip);
}
#endif

/* hide a window */
void rtgui_topwin_hide(struct rtgui_event_win* event)
{
	struct rtgui_topwin* topwin;
	struct rtgui_win* wid = event->wid;

	/* find in show list */
	topwin = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_show_list);

	/* found it */
	if (topwin)
	{
		/* remove node from show list */
		rtgui_list_remove(&_rtgui_topwin_show_list, &(topwin->list));

		/* add node to hidden list */
		rtgui_list_insert(&_rtgui_topwin_hide_list, &(topwin->list));

		/* show window title */
		if (topwin->title != RT_NULL)
		{
			RTGUI_WIDGET_HIDE(RTGUI_WIDGET(topwin->title));
		}

		/* update clip info */
		rtgui_topwin_update_clip();

		/* redraw the old rect */
		rtgui_topwin_redraw(&(topwin->extent));

		if (rtgui_server_focus_topwin == topwin)
		{
			/* activate the next window */
			if (_rtgui_topwin_show_list.next != RT_NULL)
			{
				/* get the topwin */
				topwin = rtgui_list_entry(_rtgui_topwin_show_list.next,
					struct rtgui_topwin, list);

				rtgui_server_focus_topwin = RT_NULL;
				rtgui_topwin_activate_win(topwin);
			}
			else
			{
				/* there is no shown window right now */
				rtgui_server_focus_topwin = RT_NULL;
			}
		}
	}
	else
	{
		rtgui_thread_ack(RTGUI_EVENT(event), RTGUI_STATUS_ERROR);
		return;
	}

	rtgui_thread_ack(RTGUI_EVENT(event), RTGUI_STATUS_OK);
}

/* move top window */
void rtgui_topwin_move(struct rtgui_event_win_move* event)
{
	struct rtgui_topwin* topwin;

	/* find in show list */
	topwin = rtgui_topwin_search_in_list(event->wid, &_rtgui_topwin_show_list);
	if (topwin != RT_NULL)
	{
		int dx, dy;
		rtgui_rect_t rect; /* the old topwin coverage area */
		struct rtgui_list_node* node;

		/* send status ok */
		rtgui_thread_ack(RTGUI_EVENT(event), RTGUI_STATUS_OK);

		/* get the delta move x, y */
		dx = event->x - topwin->extent.x1;
		dy = event->y - topwin->extent.y1;

		rect = topwin->extent;
		/* move window rect */
		rtgui_rect_moveto(&(topwin->extent), dx, dy);

		/* move window title */
		if (topwin->title != RT_NULL)
		{
			rect = RTGUI_WIDGET(topwin->title)->extent;
			rtgui_widget_move_to_logic(RTGUI_WIDGET(topwin->title), dx, dy);
		}

		/* move the monitor rect list */
		rtgui_list_foreach(node, &(topwin->monitor_list))
		{
			struct rtgui_mouse_monitor* monitor = rtgui_list_entry(node,
				struct rtgui_mouse_monitor,
				list);
			rtgui_rect_moveto(&(monitor->rect), dx, dy);
		}

		/* update windows clip info */
		rtgui_topwin_update_clip();

		/* update top window title */
		if (topwin->title != RT_NULL) rtgui_theme_draw_win(topwin);
		if (rtgui_rect_is_intersect(&rect, &(topwin->extent)) != RT_EOK)
		{
			/*
			 * the old rect is not intersect with moved rect,
			 * re-paint window
			 */
			struct rtgui_event_paint epaint;
			RTGUI_EVENT_PAINT_INIT(&epaint);
			epaint.wid = topwin->wid;
			rtgui_thread_send(topwin->tid, &(epaint.parent), sizeof(epaint));
		}

		/* update old window coverage area */
		rtgui_topwin_redraw(&rect);
	}
	else
	{
		rtgui_thread_ack(RTGUI_EVENT(event), RTGUI_STATUS_ERROR);
	}
}

/*
 * resize a top win
 * Note: currently, only support resize hidden window
 */
void rtgui_topwin_resize(struct rtgui_win* wid, rtgui_rect_t* r)
{
	struct rtgui_topwin* topwin;

	/* find in show list */
	topwin = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_hide_list);
	if (topwin)
	{
		topwin->extent = *r;

		if (topwin->title != RT_NULL)
		{
			/* get win extent */
			rtgui_rect_t rect = topwin->extent;

			/* add border rect */
			if (topwin->flag & WINTITLE_BORDER)
			{
				rtgui_rect_inflate(&rect, WINTITLE_BORDER_SIZE);
			}

			/* add title rect */
			if (!(topwin->flag & WINTITLE_NO)) rect.y1 -= WINTITLE_HEIGHT;

			RTGUI_WIDGET(topwin->title)->extent = rect;

			/* update title & border clip info */
			rtgui_toplevel_update_clip(RTGUI_TOPLEVEL(topwin->title));
			rtgui_region_subtract_rect(&(RTGUI_WIDGET(topwin->title)->clip),
				&(RTGUI_WIDGET(topwin->title)->clip),
				&(topwin->extent));
		}
	}
}

struct rtgui_topwin* rtgui_topwin_get_wnd(int x, int y)
{
	struct rtgui_list_node* node;
	struct rtgui_topwin* topwin;

	/* search in list */
	rtgui_list_foreach(node, &(_rtgui_topwin_show_list))
	{
		topwin = rtgui_list_entry(node, struct rtgui_topwin, list);

		/* is this window? */
		if ((topwin->title != RT_NULL) &&
			rtgui_rect_contains_point(&(RTGUI_WIDGET(topwin->title)->extent), x, y) == RT_EOK)
		{
			return topwin;
		}
		else if (rtgui_rect_contains_point(&(topwin->extent), x, y) == RT_EOK)
		{
			return topwin;
		}
	}

	return RT_NULL;
}

extern struct rtgui_list_node _rtgui_panel_list;
static void rtgui_topwin_update_clip()
{
	rt_int32_t count = 0;
	struct rtgui_event_clip_info eclip;
	struct rtgui_list_node* node = _rtgui_topwin_show_list.next;

	RTGUI_EVENT_CLIP_INFO_INIT(&eclip);

	rtgui_list_foreach(node, &_rtgui_topwin_show_list)
	{
		struct rtgui_topwin* wnd;
		wnd = rtgui_list_entry(node, struct rtgui_topwin, list);

		eclip.num_rect = count;
		eclip.wid = wnd->wid;

		count ++;

		/* send to destination window */
		rtgui_thread_send(wnd->tid, &(eclip.parent), sizeof(struct rtgui_event_clip_info));

		/* update clip in win title */
		if (wnd->title != RT_NULL)
		{
			/* reset clip info */
			rtgui_toplevel_update_clip(RTGUI_TOPLEVEL(wnd->title));
			rtgui_region_subtract_rect(&(RTGUI_WIDGET(wnd->title)->clip),
				&(RTGUI_WIDGET(wnd->title)->clip),
				&(wnd->extent));
		}
	}

	/* send clip info to each panel */
	eclip.wid = RT_NULL;
	eclip.num_rect = count;

	rtgui_list_foreach(node, &(_rtgui_panel_list))
	{
		struct rtgui_panel* panel;
		struct rtgui_list_node* panel_node;

		panel = rtgui_list_entry(node, struct rtgui_panel, sibling);

		rtgui_list_foreach(panel_node, &(panel->thread_list))
		{
			struct rtgui_panel_thread* thread;
			thread = rtgui_list_entry(panel_node, struct rtgui_panel_thread, list);

			/* send clip info to panel */
			rtgui_thread_send(thread->tid, &(eclip.parent),	sizeof(struct rtgui_event_clip_info));
		}
	}
}

static void rtgui_topwin_redraw(struct rtgui_rect* rect)
{
	struct rtgui_list_node* node;
	struct rtgui_event_paint epaint;
	RTGUI_EVENT_PAINT_INIT(&epaint);
	epaint.wid = RT_NULL;

	rtgui_list_foreach(node, &_rtgui_topwin_show_list)
	{
		struct rtgui_topwin* wnd = rtgui_list_entry(node, struct rtgui_topwin, list);

		if (rtgui_rect_is_intersect(rect, &(wnd->extent)) == RT_EOK)
		{
			/* draw window */
			epaint.wid = wnd->wid;
			rtgui_thread_send(wnd->tid, &(epaint.parent), sizeof(epaint));

			/* draw title */
			if (wnd->title != RT_NULL)
			{
				rtgui_theme_draw_win(wnd);
			}
		}
	}

	/* redraw the panel */
	rtgui_list_foreach(node, &(_rtgui_panel_list))
	{
		struct rtgui_panel* panel;
		panel = rtgui_list_entry(node, struct rtgui_panel, sibling);

		if (rtgui_rect_is_intersect(rect, &(panel->extent)) == RT_EOK)
		{
			rt_thread_t tid;

			tid = rtgui_panel_get_active_thread(panel);
			if (tid != RT_NULL)
			{
				/* draw panel */
				epaint.wid = RT_NULL;
				rtgui_thread_send(tid, &(epaint.parent), sizeof(epaint));
			}
		}
	}
}

void rtgui_topwin_title_onmouse(struct rtgui_topwin* win, struct rtgui_event_mouse* event)
{
	rtgui_rect_t rect;

	/* let window to process this mouse event */
	if (rtgui_rect_contains_point(&win->extent, event->x, event->y) == RT_EOK)
	{
		/* send mouse event to thread */
		rtgui_thread_send(win->tid, &(event->parent), sizeof(struct rtgui_event_mouse));
		return;
	}

	/* get close button rect (device value) */
	rect.x1 = RTGUI_WIDGET(win->title)->extent.x2 - WINTITLE_BORDER_SIZE - WINTITLE_CB_WIDTH - 3;
	rect.y1 = RTGUI_WIDGET(win->title)->extent.y1 + WINTITLE_BORDER_SIZE + 3;
	rect.x2 = rect.x1 + WINTITLE_CB_WIDTH;
	rect.y2 = rect.y1 + WINTITLE_CB_HEIGHT;

	if (event->button & RTGUI_MOUSE_BUTTON_LEFT)
	{
		if (event->button & RTGUI_MOUSE_BUTTON_DOWN)
		{
			if (rtgui_rect_contains_point(&rect, event->x, event->y) == RT_EOK)
			{
				win->flag |= WINTITLE_CB_PRESSED;
				rtgui_theme_draw_win(win);
			}
#ifdef RTGUI_USING_WINMOVE
			else
			{
				/* maybe move window */
				rtgui_winrect_set(win);
			}
#endif
		}
		else if (event->button & RTGUI_MOUSE_BUTTON_UP)
		{
			if (rtgui_rect_contains_point(&rect, event->x, event->y) == RT_EOK)
			{
				struct rtgui_event_win event;

				win->flag &= ~WINTITLE_CB_PRESSED;
				rtgui_theme_draw_win(win);

				/* send close event to window */
				RTGUI_EVENT_WIN_CLOSE_INIT(&event);
				event.wid = win->wid;
				rtgui_thread_send(win->tid, &(event.parent), sizeof(struct rtgui_event_win));
			}
		}
	}
}

void rtgui_topwin_append_monitor_rect(struct rtgui_win* wid, rtgui_rect_t* rect)
{
	struct rtgui_topwin* win;

	/* parameters check */
	if (wid == RT_NULL || rect == RT_NULL) return;

	/* find topwin */
	win = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_show_list);
	if (win == RT_NULL)
		win = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_hide_list);

	if (win == RT_NULL) return;

	/* append rect to top window monitor rect list */
	rtgui_mouse_monitor_append(&(win->monitor_list), rect);
}

void rtgui_topwin_remove_monitor_rect(struct rtgui_win* wid, rtgui_rect_t* rect)
{
	struct rtgui_topwin* win;

	/* parameters check */
	if (wid == RT_NULL || rect == RT_NULL) return;

	/* find topwin */
	win = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_show_list);
	if (win == RT_NULL)
		win = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_hide_list);

	if (win == RT_NULL) return;

	/* remove rect from top window monitor rect list */
	rtgui_mouse_monitor_remove(&(win->monitor_list), rect);
}

/**
 * do clip for topwin list
 * widget, the clip widget to be done clip
 */
void rtgui_topwin_do_clip(rtgui_widget_t* widget)
{
	rtgui_widget_t* wid;
	struct rtgui_rect* rect;
	struct rtgui_topwin* topwin;
	struct rtgui_list_node* node;

	/* get toplevel wid */
	wid = widget->toplevel;

	rt_sem_take(&_rtgui_topwin_lock, RT_WAITING_FOREVER);
	/* get all of topwin rect list */
	rtgui_list_foreach(node, &_rtgui_topwin_show_list)
	{
		topwin = rtgui_list_entry(node, struct rtgui_topwin, list);

		if (topwin->wid == (rtgui_win_t*)(wid) ||
			RTGUI_WIDGET(topwin->title) == widget) break; /* it's self window, break */

		/* get extent */
		if (topwin->title != RT_NULL) 
			rect = &(RTGUI_WIDGET(topwin->title)->extent);
		else 
			rect = &(topwin->extent);

		/* subtract the topwin rect */
		rtgui_region_subtract_rect(&(widget->clip), &(widget->clip), rect);
	}
	rt_sem_release(&_rtgui_topwin_lock);
}

