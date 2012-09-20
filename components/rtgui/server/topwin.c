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
#include "topwin.h"
#include "mouse.h"

#include <rtgui/dlist.h>
#include <rtgui/event.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/widgets/window.h>

/* This list is divided into two parts. The first part is the shown list, in
 * which all the windows have the WINTITLE_SHOWN flag set. Second part is the
 * hidden items, in which all the windows don't have WINTITLE_SHOWN flag.
 *
 * The active window is the one that would receive kbd events. It should always
 * be in the first tree. The order of this list is the order of the windows.
 * Top window can always clip the window beneath it when the two
 * overlapping. Child window can always clip it's parent. Slibing windows can
 * clip each other with the same rule as this list. Each child list is the same
 * as _rtgui_topwin_list. This forms the hierarchy tree structure of all
 * windows.
 *
 * Thus, the left most leaf of the tree is the top most window and the right
 * most root node is the bottom window.  The hidden part have no specific
 * order.
 */
static struct rtgui_dlist_node _rtgui_topwin_list;
#define get_topwin_from_list(list_entry) \
	(rtgui_dlist_entry((list_entry), struct rtgui_topwin, list))

#define IS_ROOT_WIN(topwin) ((topwin)->parent == RT_NULL)

static struct rt_semaphore _rtgui_topwin_lock;

static void rtgui_topwin_update_clip(void);
static void rtgui_topwin_redraw(struct rtgui_rect* rect);
static void _rtgui_topwin_activate_next(enum rtgui_topwin_flag);

void rtgui_topwin_init(void)
{
	/* init window list */
	rtgui_dlist_init(&_rtgui_topwin_list);

	rt_sem_init(&_rtgui_topwin_lock,
		"topwin", 1, RT_IPC_FLAG_FIFO);
}

static struct rtgui_topwin* rtgui_topwin_search_in_list(struct rtgui_win* window,
														struct rtgui_dlist_node* list)
{
	/* TODO: use a cache to speed up the search. */
	struct rtgui_dlist_node* node;
	struct rtgui_topwin* topwin;

	/* the action is tend to operate on the top most window. So we search in a
	 * depth first order.
	 */
	rtgui_dlist_foreach(node, list, next)
	{
		topwin = rtgui_dlist_entry(node, struct rtgui_topwin, list);

		/* is this node? */
		if (topwin->wid == window)
		{
			return topwin;
		}

		topwin = rtgui_topwin_search_in_list(window, &topwin->child_list);
		if (topwin != RT_NULL)
			return topwin;
	}

	return RT_NULL;
}

/* add a window to window list[hide] */
rt_err_t rtgui_topwin_add(struct rtgui_event_win_create* event)
{
	struct rtgui_topwin* topwin;

	topwin = rtgui_malloc(sizeof(struct rtgui_topwin));
	if (topwin == RT_NULL)
		return -RT_ERROR;

	topwin->wid    = event->wid;
#ifdef RTGUI_USING_SMALL_SIZE
	topwin->extent = RTGUI_WIDGET(event->wid)->extent;
#else
	topwin->extent = event->extent;
#endif
	topwin->tid    = event->parent.sender;

	if (event->parent_window == RT_NULL)
	{
		topwin->parent = RT_NULL;
		rtgui_dlist_insert_before(&_rtgui_topwin_list, &topwin->list);
	}
	else
	{
		topwin->parent = rtgui_topwin_search_in_list(event->parent_window, &_rtgui_topwin_list);
		if (topwin->parent == RT_NULL)
		{
			/* parent does not exist. Orphan window? */
			rtgui_free(topwin);
			return -RT_ERROR;
		}
		rtgui_dlist_insert_before(&topwin->parent->child_list, &topwin->list);
	}

	rtgui_dlist_init(&topwin->child_list);

	topwin->flag = 0;
	if (event->parent.user & RTGUI_WIN_STYLE_NO_TITLE) topwin->flag |= WINTITLE_NO;
	if (event->parent.user & RTGUI_WIN_STYLE_CLOSEBOX) topwin->flag |= WINTITLE_CLOSEBOX;
	if (!(event->parent.user & RTGUI_WIN_STYLE_NO_BORDER)) topwin->flag |= WINTITLE_BORDER;
	if (event->parent.user & RTGUI_WIN_STYLE_NO_FOCUS) topwin->flag |= WINTITLE_NOFOCUS;
	if (event->parent.user & RTGUI_WIN_STYLE_ONTOP) topwin->flag |= WINTITLE_ONTOP;
	if (event->parent.user & RTGUI_WIN_STYLE_ONBTM) topwin->flag |= WINTITLE_ONBTM;

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
		topwin->title = rtgui_wintitle_create(topwin->wid, event->wid->title);
#else
		topwin->title = rtgui_wintitle_create(topwin->wid, (const char*)event->title);
#endif
		rtgui_widget_set_rect(RTGUI_WIDGET(topwin->title), &rect);

		/* update clip info */
		rtgui_region_subtract_rect(&(RTGUI_WIDGET(topwin->title)->clip),
			&(RTGUI_WIDGET(topwin->title)->clip),
			&(topwin->extent));
	}
	else
		topwin->title = RT_NULL;

	rtgui_list_init(&topwin->monitor_list);

	return RT_EOK;
}

static struct rtgui_topwin* _rtgui_topwin_get_root_win(struct rtgui_topwin *topwin)
{
	struct rtgui_topwin *topparent;

	RT_ASSERT(topwin != RT_NULL);

	topparent = topwin;
	while (topparent && !IS_ROOT_WIN(topparent))
		topparent = topparent->parent;
	return topparent;
}

static struct rtgui_topwin* _rtgui_topwin_get_topmost_child_shown(struct rtgui_topwin *topwin)
{
	RT_ASSERT(topwin != RT_NULL);

	while (!(rtgui_dlist_isempty(&topwin->child_list)) &&
		   get_topwin_from_list(topwin->child_list.next)->flag & WINTITLE_SHOWN)
		topwin = get_topwin_from_list(topwin->child_list.next);
	return topwin;
}

static rt_bool_t _rtgui_topwin_in_layer(struct rtgui_topwin *topwin, enum rtgui_topwin_flag flag)
{
	return (topwin->flag & (WINTITLE_ONTOP|WINTITLE_ONBTM))
		    == (flag & (WINTITLE_ONTOP|WINTITLE_ONBTM));
}

/* find the topmost window shown in the layer set by flag. The flag has many
 * other infomations but we only use the ONTOP/ONBTM */
static struct rtgui_topwin* _rtgui_topwin_get_topmost_window_shown(enum rtgui_topwin_flag flag)
{
	struct rtgui_dlist_node *node;

	rtgui_dlist_foreach(node, &_rtgui_topwin_list, next)
	{
		struct rtgui_topwin *topwin = get_topwin_from_list(node);

		/* reach the hidden region no window shown in current layer */
		if (!(topwin->flag & WINTITLE_SHOWN))
			return RT_NULL;

		if (_rtgui_topwin_in_layer(topwin, flag))
			return _rtgui_topwin_get_topmost_child_shown(topwin);
	}
	/* no window in current layer is shown */
	return RT_NULL;
}

/* a hidden parent will hide it's children. Top level window can be shown at
 * any time. */
static rt_bool_t _rtgui_topwin_could_show(struct rtgui_topwin *topwin)
{
	struct rtgui_topwin *parent;

	RT_ASSERT(topwin != RT_NULL);

	for (parent = topwin->parent; parent != RT_NULL; parent = parent->parent)
	{
		if (!(parent->flag & WINTITLE_SHOWN))
			return RT_FALSE;
	}
	return RT_TRUE;
}

static void _rtgui_topwin_union_region_tree(struct rtgui_topwin *topwin,
											struct rtgui_region *region)
{
	struct rtgui_dlist_node *node;

	RT_ASSERT(topwin != RT_NULL);

	rtgui_dlist_foreach(node, &topwin->child_list, next)
		_rtgui_topwin_union_region_tree(get_topwin_from_list(node), region);

	if (topwin->title != RT_NULL)
		rtgui_region_union_rect(region, region, &RTGUI_WIDGET(topwin->title)->extent);
	else
		rtgui_region_union_rect(region, region, &topwin->extent);
}

/* The return value of this function is the next node in tree.
 *
 * As we freed the node in this function, it would be a null reference error of
 * the caller iterate the tree normally.
 */
static struct rtgui_dlist_node* _rtgui_topwin_free_tree(struct rtgui_topwin *topwin)
{
	struct rtgui_dlist_node *node, *next_node;

	RT_ASSERT(topwin != RT_NULL);

	node = topwin->child_list.next;
	while (node != &topwin->child_list)
		node = _rtgui_topwin_free_tree(get_topwin_from_list(node));

	next_node = topwin->list.next;
	rtgui_dlist_remove(&topwin->list);

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
	return next_node;
}

rt_err_t rtgui_topwin_remove(struct rtgui_win* wid)
{
	struct rtgui_topwin *topwin, *old_focus;
	struct rtgui_region region;

	/* find the topwin node */
	topwin = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_list);

	if (topwin == RT_NULL)
		return -RT_ERROR;

	rtgui_region_init(&region);

	old_focus = rtgui_topwin_get_focus();

	/* remove the root from _rtgui_topwin_list will remove the whole tree from
	 * _rtgui_topwin_list. */
	rtgui_dlist_remove(&topwin->list);

	if (old_focus == topwin)
	{
		_rtgui_topwin_activate_next(topwin->flag);
	}

	if (topwin->flag & WINTITLE_SHOWN)
	{
		rtgui_topwin_update_clip();
		/* redraw the old rect */
		_rtgui_topwin_union_region_tree(topwin, &region);
		rtgui_topwin_redraw(rtgui_region_extents(&region));
	}

	_rtgui_topwin_free_tree(topwin);

	return RT_EOK;
}

/* neither deactivate the old focus nor change _rtgui_topwin_list.
 * Suitable to be called when the first item is the window to be activated
 * already. */
static void _rtgui_topwin_only_activate(struct rtgui_topwin *topwin)
{
	struct rtgui_event_win event;

	RT_ASSERT(topwin != RT_NULL);

	if (topwin->flag & WINTITLE_NOFOCUS)
		return;

	/* activate the raised window */
	RTGUI_EVENT_WIN_ACTIVATE_INIT(&event);

	topwin->flag |= WINTITLE_ACTIVATE;

	event.wid = topwin->wid;
	rtgui_send(topwin->tid, &(event.parent), sizeof(struct rtgui_event_win));

	/* redraw title */
	if (topwin->title != RT_NULL)
	{
		rtgui_theme_draw_win(topwin);
	}
}

/* activate next window in the same layer as flag. The flag has many other
 * infomations but we only use the ONTOP/ONBTM */
static void _rtgui_topwin_activate_next(enum rtgui_topwin_flag flag)
{
	struct rtgui_topwin *topwin;

	topwin = _rtgui_topwin_get_topmost_window_shown(flag);
	if (topwin == RT_NULL)
		return;

	_rtgui_topwin_only_activate(topwin);
}

/* this function does not update the clip(to avoid doubel clipping). So if the
 * tree has changed, make sure it has already updated outside. */
static void _rtgui_topwin_deactivate(struct rtgui_topwin *topwin)
{
	struct rtgui_event_win event;

	RT_ASSERT(topwin != RT_NULL);
	RT_ASSERT(topwin->tid != RT_NULL);

	RTGUI_EVENT_WIN_DEACTIVATE_INIT(&event);
	event.wid = topwin->wid;
	rtgui_send(topwin->tid,
			&event.parent, sizeof(struct rtgui_event_win));

	topwin->flag &= ~WINTITLE_ACTIVATE;

	/* redraw title */
	if (topwin->title != RT_NULL)
	{
		rtgui_theme_draw_win(topwin);
	}
}

static void _rtgui_topwin_move_whole_tree2top(struct rtgui_topwin *topwin)
{
	struct rtgui_topwin *topparent;

	RT_ASSERT(topwin != RT_NULL);

	/* move the whole tree */
	topparent = _rtgui_topwin_get_root_win(topwin);
	RT_ASSERT(topparent != RT_NULL);

	/* remove node from hidden list */
	rtgui_dlist_remove(&topparent->list);
	/* add node to show list */
	if (topwin->flag & WINTITLE_ONTOP)
	{
		rtgui_dlist_insert_after(&_rtgui_topwin_list, &(topparent->list));
	}
	else if (topwin->flag & WINTITLE_ONBTM)
	{
		/* botton layer window, before the fisrt bottom window or hidden window. */
		struct rtgui_topwin *ntopwin = get_topwin_from_list(&_rtgui_topwin_list);
		struct rtgui_dlist_node *node;

		rtgui_dlist_foreach(node, &_rtgui_topwin_list, next)
		{
			ntopwin = get_topwin_from_list(node);
			if ((ntopwin->flag & WINTITLE_ONBTM)
					|| !(ntopwin->flag & WINTITLE_SHOWN))
				break;
		}
		/* all other windows are shown top/normal layer windows. Insert it as
		 * the last window. */
		if (node == &_rtgui_topwin_list)
			rtgui_dlist_insert_before(&_rtgui_topwin_list, &(topparent->list));
		else
			rtgui_dlist_insert_before(&ntopwin->list, &(topparent->list));
	}
	else
	{
		/* normal layer window, before the fisrt shown normal layer window. */
		struct rtgui_topwin *ntopwin = get_topwin_from_list(&_rtgui_topwin_list);
		struct rtgui_dlist_node *node;

		rtgui_dlist_foreach(node, &_rtgui_topwin_list, next)
		{
			ntopwin = get_topwin_from_list(node);
			if (!((ntopwin->flag & WINTITLE_ONTOP)
						&& (ntopwin->flag & WINTITLE_SHOWN)))
				break;
		}
		/* all other windows are shown top layer windows. Insert it as
		 * the last window. */
		if (node == &_rtgui_topwin_list)
			rtgui_dlist_insert_before(&_rtgui_topwin_list, &(topparent->list));
		else
			rtgui_dlist_insert_before(&ntopwin->list, &(topparent->list));
	}
}

static void _rtgui_topwin_raise_in_sibling(struct rtgui_topwin *topwin)
{
	struct rtgui_dlist_node *win_level;

	RT_ASSERT(topwin != RT_NULL);

	if (topwin->parent == RT_NULL)
		win_level = &_rtgui_topwin_list;
	else
		win_level = &topwin->parent->child_list;
	rtgui_dlist_remove(&topwin->list);
	rtgui_dlist_insert_after(win_level, &topwin->list);
}

/* it will do 2 things. One is moving the whole tree(the root of the tree) to
 * the front and the other is moving topwin to the front of it's siblings. */
static void _rtgui_topwin_raise_tree_from_root(struct rtgui_topwin *topwin)
{
	RT_ASSERT(topwin != RT_NULL);

	_rtgui_topwin_move_whole_tree2top(topwin);
	/* root win is aleady moved by _rtgui_topwin_move_whole_tree2top */
	if (!IS_ROOT_WIN(topwin))
		_rtgui_topwin_raise_in_sibling(topwin);
}

/* activate a win means:
 * - deactivate the old focus win if any
 * - raise the window to the front of it's siblings
 * - activate a win
 */
rt_err_t rtgui_topwin_activate(struct rtgui_event_win_activate* event)
{
	struct rtgui_topwin *topwin;

	RT_ASSERT(event);

	topwin = rtgui_topwin_search_in_list(event->wid, &_rtgui_topwin_list);
	if (topwin == RT_NULL)
		return -RT_ERROR;

	return rtgui_topwin_activate_topwin(topwin);
}

static void _rtgui_topwin_draw_tree(struct rtgui_topwin *topwin, struct rtgui_event_paint *epaint)
{
	struct rtgui_dlist_node *node;

	if (topwin->title != RT_NULL)
	{
		rtgui_theme_draw_win(topwin);
	}

	epaint->wid = topwin->wid;
	rtgui_send(topwin->tid, &(epaint->parent), sizeof(struct rtgui_event_paint));

	rtgui_dlist_foreach(node, &topwin->child_list, prev)
	{
		if (!(get_topwin_from_list(node)->flag & WINTITLE_SHOWN))
			return;
		_rtgui_topwin_draw_tree(get_topwin_from_list(node), epaint);
	}
}

rt_err_t rtgui_topwin_activate_topwin(struct rtgui_topwin* topwin)
{
	struct rtgui_topwin *old_focus_topwin;
    struct rtgui_event_paint epaint;

	RT_ASSERT(topwin != RT_NULL);

    RTGUI_EVENT_PAINT_INIT(&epaint);

	if (!(topwin->flag & WINTITLE_SHOWN))
		return -RT_ERROR;

	if (topwin->flag & WINTITLE_NOFOCUS)
	{
		/* just raise and show, not affect others. */
        _rtgui_topwin_raise_tree_from_root(topwin);
        rtgui_topwin_update_clip();
        _rtgui_topwin_draw_tree(topwin, &epaint);
		return RT_EOK;
	}

	if (topwin->flag & WINTITLE_ACTIVATE)
		return RT_EOK;

	old_focus_topwin = rtgui_topwin_get_focus();
	/* if topwin has the focus, it shoule have WINTITLE_ACTIVATE set and
	 * returned above. */
	RT_ASSERT(old_focus_topwin != topwin);

	_rtgui_topwin_raise_tree_from_root(topwin);
    /* clip before active the window, so we could get right boarder region. */
	rtgui_topwin_update_clip();

	if (old_focus_topwin != RT_NULL)
	{
		/* deactivate the old focus window firstly, otherwise it will make the new
		 * window invisible. */
		_rtgui_topwin_deactivate(old_focus_topwin);
	}

	_rtgui_topwin_only_activate(topwin);

    _rtgui_topwin_draw_tree(topwin, &epaint);

	return RT_EOK;
}

/* map func to the topwin tree in preorder.
 *
 * Remember that we are in a embedded system so write the @param func memory
 * efficiently.
 */
rt_inline void _rtgui_topwin_preorder_map(struct rtgui_topwin *topwin, void (*func)(struct rtgui_topwin*))
{
	struct rtgui_dlist_node *child;

	RT_ASSERT(topwin != RT_NULL);
	RT_ASSERT(func != RT_NULL);

	func(topwin);

	rtgui_dlist_foreach(child, &topwin->child_list, next)
		_rtgui_topwin_preorder_map(get_topwin_from_list(child), func);
}

rt_inline void _rtgui_topwin_mark_hidden(struct rtgui_topwin *topwin)
{
	topwin->flag &= ~WINTITLE_SHOWN;
	if (topwin->title != RT_NULL)
	{
		RTGUI_WIDGET_HIDE(topwin->title);
	}
	RTGUI_WIDGET_HIDE(topwin->wid);
}

rt_inline void _rtgui_topwin_mark_shown(struct rtgui_topwin *topwin)
{
	if (!(topwin->flag & WINTITLE_SHOWN)
		&& RTGUI_WIDGET_IS_HIDE(topwin->wid))
		return;

	topwin->flag |= WINTITLE_SHOWN;
	if (topwin->title != RT_NULL)
	{
		RTGUI_WIDGET_UNHIDE(topwin->title);
	}
	RTGUI_WIDGET_UNHIDE(topwin->wid);
}

rt_err_t rtgui_topwin_show(struct rtgui_event_win* event)
{
	struct rtgui_topwin *topwin;
	struct rtgui_win* wid = event->wid;

	topwin = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_list);
	/* no such a window recorded */
	if (topwin == RT_NULL)
		return -RT_ERROR;

	/* if the parent is hidden, just mark it as shown. It will be shown when
	 * the parent is shown. */
	if (!_rtgui_topwin_could_show(topwin))
	{
		topwin->flag |= WINTITLE_SHOWN;
		_rtgui_topwin_raise_in_sibling(topwin);

		return -RT_ERROR;
	}

    _rtgui_topwin_preorder_map(topwin, _rtgui_topwin_mark_shown);
    rtgui_topwin_activate_topwin(topwin);

	return RT_EOK;
}

static void _rtgui_topwin_clear_modal_tree(struct rtgui_topwin *topwin)
{
	struct rtgui_dlist_node *node;

	RT_ASSERT(topwin != RT_NULL);
	RT_ASSERT(topwin->parent != RT_NULL);

	while (!IS_ROOT_WIN(topwin))
	{
		rtgui_dlist_foreach(node, &topwin->parent->child_list, next)
			get_topwin_from_list(node)->flag &= ~WINTITLE_MODALED;
		topwin = topwin->parent;
	}
	/* clear the modal flag of the root window */
	topwin->flag &= ~WINTITLE_MODALED;
}

/* hide a window */
rt_err_t rtgui_topwin_hide(struct rtgui_event_win* event)
{
	struct rtgui_topwin *topwin;
	struct rtgui_topwin *old_focus_topwin = rtgui_topwin_get_focus();
	struct rtgui_win    *wid = event->wid;
	struct rtgui_dlist_node *containing_list;

	/* find in show list */
	topwin = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_list);
	if (topwin == RT_NULL)
	{
		return -RT_ERROR;
	}
	if (!(topwin->flag & WINTITLE_SHOWN))
	{
		return RT_EOK;
	}

	old_focus_topwin = rtgui_topwin_get_focus();

	_rtgui_topwin_preorder_map(topwin, _rtgui_topwin_mark_hidden);

	if (topwin->parent == RT_NULL)
		containing_list = &_rtgui_topwin_list;
	else
		containing_list = &topwin->parent->child_list;

	rtgui_dlist_remove(&topwin->list);
	rtgui_dlist_insert_before(containing_list, &topwin->list);

	/* update clip info */
	rtgui_topwin_update_clip();

	/* redraw the old rect */
	rtgui_topwin_redraw(&(topwin->extent));

	if (topwin->flag & WINTITLE_MODALING)
	{
		_rtgui_topwin_clear_modal_tree(topwin);
		topwin->flag &= ~WINTITLE_MODALING;
	}

	if (old_focus_topwin == topwin)
	{
		_rtgui_topwin_activate_next(topwin->flag);
	}

    topwin->flag &= ~WINTITLE_ACTIVATE;

	return RT_EOK;
}

/* move top window */
rt_err_t rtgui_topwin_move(struct rtgui_event_win_move* event)
{
	struct rtgui_topwin* topwin;
	int dx, dy;
	rtgui_rect_t old_rect; /* the old topwin coverage area */
	struct rtgui_list_node* node;

	/* find in show list */
	topwin = rtgui_topwin_search_in_list(event->wid, &_rtgui_topwin_list);
	if (topwin == RT_NULL ||
		!(topwin->flag & WINTITLE_SHOWN))
	{
		return -RT_ERROR;
	}

	/* get the delta move x, y */
	dx = event->x - topwin->extent.x1;
	dy = event->y - topwin->extent.y1;

	old_rect = topwin->extent;
	/* move window rect */
	rtgui_rect_moveto(&(topwin->extent), dx, dy);

	/* move window title */
	if (topwin->title != RT_NULL)
	{
		old_rect = RTGUI_WIDGET(topwin->title)->extent;
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

	/* update old window coverage area */
	rtgui_topwin_redraw(&old_rect);

	/* update top window title */
	if (topwin->title != RT_NULL)
		rtgui_theme_draw_win(topwin);
	if (rtgui_rect_is_intersect(&old_rect, &(topwin->extent)) != RT_EOK)
	{
		/*
		 * the old rect is not intersect with moved rect,
		 * re-paint window
		 */
		struct rtgui_event_paint epaint;
		RTGUI_EVENT_PAINT_INIT(&epaint);
		epaint.wid = topwin->wid;
		rtgui_send(topwin->tid, &(epaint.parent), sizeof(epaint));
	}

	return RT_EOK;
}

/*
 * resize a top win
 * Note: currently, only support resize hidden window
 */
void rtgui_topwin_resize(struct rtgui_win* wid, rtgui_rect_t* rect)
{
	struct rtgui_topwin* topwin;
	struct rtgui_region region;

	/* find in show list */
	topwin = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_list);
	if (topwin == RT_NULL ||
		!(topwin->flag & WINTITLE_SHOWN))
		return;

	/* record the old rect */
	rtgui_region_init_with_extents(&region, &topwin->extent);
	/* union the new rect so this is the region we should redraw */
	rtgui_region_union_rect(&region, &region, rect);

	topwin->extent = *rect;

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
		if (!(topwin->flag & WINTITLE_NO))
			rect.y1 -= WINTITLE_HEIGHT;

		RTGUI_WIDGET(topwin->title)->extent = rect;
	}

	/* update windows clip info */
	rtgui_topwin_update_clip();

	/* update old window coverage area */
	rtgui_topwin_redraw(rtgui_region_extents(&region));
}

static struct rtgui_topwin* _rtgui_topwin_get_focus_from_list(struct rtgui_dlist_node *list)
{
	struct rtgui_dlist_node *node;

	RT_ASSERT(list != RT_NULL);

	rtgui_dlist_foreach(node, list, next)
	{
		struct rtgui_topwin *child = get_topwin_from_list(node);
		if (child->flag & WINTITLE_ACTIVATE)
			return child;

		child = _rtgui_topwin_get_focus_from_list(&child->child_list);
		if (child != RT_NULL)
			return child;
	}

	return RT_NULL;
}

struct rtgui_topwin* rtgui_topwin_get_focus(void)
{
	return _rtgui_topwin_get_focus_from_list(&_rtgui_topwin_list);
}

static struct rtgui_topwin* _rtgui_topwin_get_wnd_from_tree(struct rtgui_dlist_node *list,
															int x, int y,
															rt_bool_t exclude_modaled)
{
	struct rtgui_dlist_node *node;
	struct rtgui_topwin *topwin, *target;

	RT_ASSERT(list != RT_NULL);

	rtgui_dlist_foreach(node, list, next)
	{
		topwin = get_topwin_from_list(node);
		if (!(topwin->flag & WINTITLE_SHOWN))
			break;

		/* if higher window have this point, return it */
		target = _rtgui_topwin_get_wnd_from_tree(&topwin->child_list, x, y, exclude_modaled);
		if (target != RT_NULL)
			return target;

		if (exclude_modaled && (topwin->flag & WINTITLE_MODALED))
			break;

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

struct rtgui_topwin* rtgui_topwin_get_wnd(int x, int y)
{
	return _rtgui_topwin_get_wnd_from_tree(&_rtgui_topwin_list, x, y, RT_FALSE);
}

struct rtgui_topwin* rtgui_topwin_get_wnd_no_modaled(int x, int y)
{
	return _rtgui_topwin_get_wnd_from_tree(&_rtgui_topwin_list, x, y, RT_TRUE);
}

/* clip region from topwin, and the windows beneath it. */
rt_inline void _rtgui_topwin_clip_to_region(struct rtgui_region *region,
										    struct rtgui_topwin *topwin)
{
	RT_ASSERT(region != RT_NULL);
	RT_ASSERT(topwin != RT_NULL);

	if (topwin->title != RT_NULL)
	{
		rtgui_region_reset(&(RTGUI_WIDGET(topwin->title)->clip),
						   &(RTGUI_WIDGET(topwin->title)->extent));
		rtgui_region_intersect(&(RTGUI_WIDGET(topwin->title)->clip),
							   &(RTGUI_WIDGET(topwin->title)->clip),
							   region);
		rtgui_region_subtract_rect(&(RTGUI_WIDGET(topwin->title)->clip),
								   &(RTGUI_WIDGET(topwin->title)->clip),
								   &topwin->extent);
	}

	rtgui_region_reset(&RTGUI_WIDGET(topwin->wid)->clip,
					   &RTGUI_WIDGET(topwin->wid)->extent);
	rtgui_region_intersect(&RTGUI_WIDGET(topwin->wid)->clip,
						   &RTGUI_WIDGET(topwin->wid)->clip,
						   region);
}

static void rtgui_topwin_update_clip(void)
{
	struct rtgui_topwin *top;
	struct rtgui_event_clip_info eclip;
	/* Note that the region is a "female die", that means it's the region you
	 * can paint to, not the region covered by others.
	 */
	struct rtgui_region region_available;

	if (rtgui_dlist_isempty(&_rtgui_topwin_list) ||
		!(get_topwin_from_list(_rtgui_topwin_list.next)->flag & WINTITLE_SHOWN))
		return;

	RTGUI_EVENT_CLIP_INFO_INIT(&eclip);

	rtgui_region_init_rect(&region_available, 0, 0,
			rtgui_graphic_driver_get_default()->width,
			rtgui_graphic_driver_get_default()->height);

	/* from top to bottom. */
	top = _rtgui_topwin_get_topmost_window_shown(WINTITLE_ONTOP);
	/* 0 is normal layer */
	if (top == RT_NULL)
		top = _rtgui_topwin_get_topmost_window_shown(0);
	if (top == RT_NULL)
		top = _rtgui_topwin_get_topmost_window_shown(WINTITLE_ONBTM);

	while (top != RT_NULL)
	{
		/* clip the topwin */
		_rtgui_topwin_clip_to_region(&region_available, top);
#if 0
		/* debug window clipping */
		rt_kprintf("clip %s ", top->wid->title);
		rtgui_region_dump(&region_available);
		rt_kprintf("\n");
#endif

		/* update available region */
		if (top->title != RT_NULL)
			rtgui_region_subtract_rect(&region_available, &region_available, &RTGUI_WIDGET(top->title)->extent);
		else
			rtgui_region_subtract_rect(&region_available, &region_available, &top->extent);

		/* send clip event to destination window */
		eclip.wid = top->wid;
		rtgui_send(top->tid, &(eclip.parent), sizeof(struct rtgui_event_clip_info));

		/* move to next sibling tree */
		if (top->parent == RT_NULL)
			if (top->list.next != &_rtgui_topwin_list &&
					get_topwin_from_list(top->list.next)->flag & WINTITLE_SHOWN)
				top = _rtgui_topwin_get_topmost_child_shown(get_topwin_from_list(top->list.next));
			else
				break;
		/* move to next slibing topwin */
		else if (top->list.next != &top->parent->child_list &&
			get_topwin_from_list(top->list.next)->flag & WINTITLE_SHOWN)
			top = _rtgui_topwin_get_topmost_child_shown(get_topwin_from_list(top->list.next));
		/* level up */
		else
			top = top->parent;
	}
}

static void _rtgui_topwin_redraw_tree(struct rtgui_dlist_node *list,
									  struct rtgui_rect* rect,
									  struct rtgui_event_paint *epaint)
{
	struct rtgui_dlist_node *node;

	RT_ASSERT(list != RT_NULL);
	RT_ASSERT(rect != RT_NULL);
	RT_ASSERT(epaint != RT_NULL);

	/* skip the hidden windows */
	rtgui_dlist_foreach(node, list, prev)
	{
		if (get_topwin_from_list(node)->flag & WINTITLE_SHOWN)
			break;
	}

	for (; node != list; node = node->prev)
	{
		struct rtgui_topwin *topwin;

		topwin = get_topwin_from_list(node);

		//FIXME: intersect with clip?
		if (rtgui_rect_is_intersect(rect, &(topwin->extent)) == RT_EOK)
		{
			epaint->wid = topwin->wid;
			rtgui_send(topwin->tid, &(epaint->parent), sizeof(*epaint));

			/* draw title */
			if (topwin->title != RT_NULL)
			{
				rtgui_theme_draw_win(topwin);
			}
		}

		_rtgui_topwin_redraw_tree(&topwin->child_list, rect, epaint);
	}
}

static void rtgui_topwin_redraw(struct rtgui_rect* rect)
{
	struct rtgui_event_paint epaint;
	RTGUI_EVENT_PAINT_INIT(&epaint);
	epaint.wid = RT_NULL;

	_rtgui_topwin_redraw_tree(&_rtgui_topwin_list, rect, &epaint);
}

/* a window enter modal mode will modal all the sibling window and parent
 * window all along to the root window(which parent is RT_NULL or the desktop
 * window if there is). If a root window modals, there is nothing to do here.*/
rt_err_t rtgui_topwin_modal_enter(struct rtgui_event_win_modal_enter* event)
{
	struct rtgui_topwin *topwin, *parent_top;
	struct rtgui_dlist_node *node;

	topwin = rtgui_topwin_search_in_list(event->wid, &_rtgui_topwin_list);

	if (topwin == RT_NULL)
		return -RT_ERROR;

	if (IS_ROOT_WIN(topwin))
		return RT_EOK;

	parent_top = topwin->parent;

	/* modal window should be on top already */
	RT_ASSERT(get_topwin_from_list(parent_top->child_list.next) == topwin);

	while (!IS_ROOT_WIN(parent_top))
	{
		rtgui_dlist_foreach(node, &parent_top->child_list, next)
			get_topwin_from_list(node)->flag |= WINTITLE_MODALED;
		parent_top->flag |= WINTITLE_MODALED;

		parent_top = parent_top->parent;
	}
	/* mark root window as modaled */
	parent_top->flag |= WINTITLE_MODALED;

	topwin->flag &= ~WINTITLE_MODALED;
	topwin->flag |= WINTITLE_MODALING;

	return RT_EOK;
}

void rtgui_topwin_title_onmouse(struct rtgui_topwin* win, struct rtgui_event_mouse* event)
{
	rtgui_rect_t rect;

	/* let window to process this mouse event */
	if (rtgui_rect_contains_point(&win->extent, event->x, event->y) == RT_EOK)
	{
		/* send mouse event to thread */
		rtgui_send(win->tid, &(event->parent), sizeof(struct rtgui_event_mouse));
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
		else if (win->flag & WINTITLE_CB_PRESSED && event->button & RTGUI_MOUSE_BUTTON_UP)
		{
			if (rtgui_rect_contains_point(&rect, event->x, event->y) == RT_EOK)
			{
				struct rtgui_event_win event;

				win->flag &= ~WINTITLE_CB_PRESSED;
				rtgui_theme_draw_win(win);

				/* send close event to window */
				RTGUI_EVENT_WIN_CLOSE_INIT(&event);
				event.wid = win->wid;
				rtgui_send(win->tid, &(event.parent), sizeof(struct rtgui_event_win));
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
	win = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_list);
	if (win == RT_NULL)
		return;

	/* append rect to top window monitor rect list */
	rtgui_mouse_monitor_append(&(win->monitor_list), rect);
}

void rtgui_topwin_remove_monitor_rect(struct rtgui_win* wid, rtgui_rect_t* rect)
{
	struct rtgui_topwin* win;

	/* parameters check */
	if (wid == RT_NULL || rect == RT_NULL)
		return;

	/* find topwin */
	win = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_list);
	if (win == RT_NULL)
		return;

	/* remove rect from top window monitor rect list */
	rtgui_mouse_monitor_remove(&(win->monitor_list), rect);
}

static void _rtgui_topwin_dump(struct rtgui_topwin *topwin)
{
	rt_kprintf("0x%p:%s,0x%x", topwin, topwin->wid->title, topwin->flag);
}

static void _rtgui_topwin_dump_tree(struct rtgui_topwin *topwin)
{
	struct rtgui_dlist_node *node;

	_rtgui_topwin_dump(topwin);

	rt_kprintf("(");
	rtgui_dlist_foreach(node, &topwin->child_list, next)
	{
		_rtgui_topwin_dump_tree(get_topwin_from_list(node));
	}
	rt_kprintf(")");
}

void rtgui_topwin_dump_tree(void)
{
	struct rtgui_dlist_node *node;

	rtgui_dlist_foreach(node, &_rtgui_topwin_list, next)
	{
		_rtgui_topwin_dump_tree(get_topwin_from_list(node));
		rt_kprintf("\n");
	}
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void dump_tree()
{
	rtgui_topwin_dump_tree();
}
FINSH_FUNCTION_EXPORT(dump_tree, dump rtgui topwin tree)
#endif
