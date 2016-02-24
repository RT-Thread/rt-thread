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
 * 2012-02-25     Grissiom     rewrite topwin implementation 
 */
#include "topwin.h"
#include "mouse.h"

#include <rtservice.h>
#include <rtgui/event.h>
#include <rtgui/image.h>
//#include <rtgui/rtgui_theme.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/container.h>

/*
 * windows tree in the server side. 
 *
 * This list is divided into two parts. The first part is the shown list, in
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
#define get_topwin_from_list(list_entry) (rt_list_entry((list_entry), struct rtgui_topwin, list))
/* the direction can only be next or prev. If you want to iterate the list in
 * normal order, use next. If you want to iterate the list with reverse order,
 * use prev.*/
#define rt_list_foreach(node, list, direction)  \
    for ((node) = (list)->direction; (node) != list; (node) = (node)->direction)

#define IS_ROOT_WIN(topwin) ((topwin)->parent == RT_NULL)

static rt_list_t _rtgui_topwin_list = RT_LIST_OBJECT_INIT(_rtgui_topwin_list);
static struct rt_semaphore _rtgui_topwin_lock;

static void rtgui_topwin_update_clip(void);
static void rtgui_topwin_redraw(struct rtgui_rect *rect);
static void _rtgui_topwin_activate_next(enum rtgui_topwin_flag);

void rtgui_topwin_init(void)
{
    /* initialize semaphore */
    rt_sem_init(&_rtgui_topwin_lock, "wintree", 1, RT_IPC_FLAG_FIFO);
}

static struct rtgui_topwin *rtgui_topwin_search_in_list(struct rtgui_win *window,
        struct rt_list_node *list)
{
    /* TODO: use a cache to speed up the search. */
    struct rt_list_node *node;
    struct rtgui_topwin *topwin;

    /* the action is tend to operate on the top most window. So we search in a
     * depth first order.
     */
    rt_list_foreach(node, list, next)
    {
        topwin = rt_list_entry(node, struct rtgui_topwin, list);

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
rt_err_t rtgui_topwin_add(struct rtgui_event_win_create *event)
{
    struct rtgui_topwin *topwin;

    topwin = rtgui_malloc(sizeof(struct rtgui_topwin));
    if (topwin == RT_NULL)
        return -RT_ERROR;

    topwin->wid    = event->wid;
    if (event->wid->_title_wgt)
        topwin->extent = RTGUI_WIDGET(event->wid->_title_wgt)->extent;
    else
        topwin->extent = RTGUI_WIDGET(event->wid)->extent;
    topwin->app    = event->parent.sender;

    if (event->parent_window == RT_NULL)
    {
        topwin->parent = RT_NULL;
        rt_list_insert_before(&_rtgui_topwin_list, &topwin->list);
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
        rt_list_insert_before(&topwin->parent->child_list, &topwin->list);
    }

    rt_list_init(&topwin->child_list);

    topwin->flag = WINTITLE_INIT;
    if (event->parent.user & RTGUI_WIN_STYLE_NO_FOCUS)
        topwin->flag |= WINTITLE_NOFOCUS;
    if (event->parent.user & RTGUI_WIN_STYLE_ONTOP)
        topwin->flag |= WINTITLE_ONTOP;
    if (event->parent.user & RTGUI_WIN_STYLE_ONBTM)
        topwin->flag |= WINTITLE_ONBTM;

    topwin->title = RT_NULL;

    rtgui_list_init(&topwin->monitor_list);

    return RT_EOK;
}

static struct rtgui_topwin *_rtgui_topwin_get_root_win(struct rtgui_topwin *topwin)
{
    struct rtgui_topwin *topparent;

    RT_ASSERT(topwin != RT_NULL);

    topparent = topwin;
    while (topparent && !IS_ROOT_WIN(topparent))
        topparent = topparent->parent;
    return topparent;
}

static struct rtgui_topwin *_rtgui_topwin_get_topmost_child_shown(struct rtgui_topwin *topwin)
{
    RT_ASSERT(topwin != RT_NULL);

    while (!(rt_list_isempty(&topwin->child_list)) &&
            get_topwin_from_list(topwin->child_list.next)->flag & WINTITLE_SHOWN)
    {
        topwin = get_topwin_from_list(topwin->child_list.next);
    }
    return topwin;
}

static rt_bool_t _rtgui_topwin_in_layer(struct rtgui_topwin *topwin, enum rtgui_topwin_flag flag)
{
    return (topwin->flag & (WINTITLE_ONTOP | WINTITLE_ONBTM))
           == (flag & (WINTITLE_ONTOP | WINTITLE_ONBTM));
}

/* find the topmost window shown in the layer set by flag. The flag has many
 * other infomations but we only use the ONTOP/ONBTM */
struct rtgui_topwin *rtgui_topwin_get_topmost_window_shown(enum rtgui_topwin_flag flag)
{
    struct rt_list_node *node;

    rt_list_foreach(node, &_rtgui_topwin_list, next)
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

struct rtgui_topwin *rtgui_topwin_get_topmost_window_shown_all(void)
{
    struct rtgui_topwin *top;

    top = rtgui_topwin_get_topmost_window_shown(WINTITLE_ONTOP);
    /* 0 is normal layer */
    if (top == RT_NULL)
        top = rtgui_topwin_get_topmost_window_shown(WINTITLE_INIT);
    if (top == RT_NULL)
        top = rtgui_topwin_get_topmost_window_shown(WINTITLE_ONBTM);

    return top;
}

struct rtgui_win* rtgui_win_get_topmost_shown(void)
{
    struct rtgui_topwin *top;

    top = rtgui_topwin_get_topmost_window_shown_all();
    if (!top)
        return RT_NULL;
    return top->wid;
}

static struct rtgui_topwin* _rtgui_topwin_get_next_shown(struct rtgui_topwin *top)
{
    /* move to next sibling tree */
    if (top->parent == RT_NULL)
    {
        if (top->list.next != &_rtgui_topwin_list &&
            get_topwin_from_list(top->list.next)->flag & WINTITLE_SHOWN)
            top = _rtgui_topwin_get_topmost_child_shown(get_topwin_from_list(top->list.next));
        else
            return RT_NULL;
    }
    /* move to next slibing topwin */
    else if (top->list.next != &top->parent->child_list &&
             get_topwin_from_list(top->list.next)->flag & WINTITLE_SHOWN)
    {
        top = _rtgui_topwin_get_topmost_child_shown(get_topwin_from_list(top->list.next));
    }
    /* level up */
    else
    {
        top = top->parent;
    }

    return top;
}

struct rtgui_win* rtgui_win_get_next_shown(void)
{
    struct rtgui_topwin *top;

    top = rtgui_topwin_get_topmost_window_shown_all();
    if (!top)
        return RT_NULL;

    top = _rtgui_topwin_get_next_shown(top);
    if (!top)
        return RT_NULL;

    return top->wid;
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
    struct rt_list_node *node;

    RT_ASSERT(topwin != RT_NULL);

    rt_list_foreach(node, &topwin->child_list, next)
    _rtgui_topwin_union_region_tree(get_topwin_from_list(node), region);

    rtgui_region_union_rect(region, region, &topwin->extent);
}

/* The return value of this function is the next node in tree.
 *
 * As we freed the node in this function, it would be a null reference error of
 * the caller iterate the tree normally.
 */
static struct rt_list_node *_rtgui_topwin_free_tree(struct rtgui_topwin *topwin)
{
    struct rt_list_node *node, *next_node;

    RT_ASSERT(topwin != RT_NULL);

    node = topwin->child_list.next;
    while (node != &topwin->child_list)
        node = _rtgui_topwin_free_tree(get_topwin_from_list(node));

    next_node = topwin->list.next;
    rt_list_remove(&topwin->list);

    /* free the monitor rect list, topwin node and title */
    while (topwin->monitor_list.next != RT_NULL)
    {
        struct rtgui_mouse_monitor *monitor = rtgui_list_entry(topwin->monitor_list.next,
                                              struct rtgui_mouse_monitor, list);

        topwin->monitor_list.next = topwin->monitor_list.next->next;
        rtgui_free(monitor);
    }

    rtgui_free(topwin);
    return next_node;
}

rt_err_t rtgui_topwin_remove(struct rtgui_win *wid)
{
    struct rtgui_topwin *topwin, *old_focus;
    struct rtgui_region region;

    /* find the topwin node */
    topwin = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_list);

    if (topwin == RT_NULL) return -RT_ERROR;

    rtgui_region_init(&region);

    old_focus = rtgui_topwin_get_focus();

    /* remove the root from _rtgui_topwin_list will remove the whole tree from
     * _rtgui_topwin_list. */
    rt_list_remove(&topwin->list);

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

    rtgui_region_fini(&region);
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
    rtgui_send(topwin->app, &(event.parent), sizeof(struct rtgui_event_win));
}

/* activate next window in the same layer as flag. The flag has many other
 * infomations but we only use the ONTOP/ONBTM */
static void _rtgui_topwin_activate_next(enum rtgui_topwin_flag flag)
{
    struct rtgui_topwin *topwin;

    topwin = rtgui_topwin_get_topmost_window_shown(flag);
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
    RT_ASSERT(topwin->app != RT_NULL);

    RTGUI_EVENT_WIN_DEACTIVATE_INIT(&event);
    event.wid = topwin->wid;
    rtgui_send(topwin->app,
               &event.parent, sizeof(struct rtgui_event_win));

    topwin->flag &= ~WINTITLE_ACTIVATE;
}

/* Return 1 on the tree is truely moved. If the tree is already in position,
 * return 0. */
static int _rtgui_topwin_move_whole_tree2top(struct rtgui_topwin *topwin)
{
    struct rtgui_topwin *topparent;

    RT_ASSERT(topwin != RT_NULL);

    /* move the whole tree */
    topparent = _rtgui_topwin_get_root_win(topwin);
    RT_ASSERT(topparent != RT_NULL);

    /* add node to show list */
    if (topwin->flag & WINTITLE_ONTOP)
    {
        if (get_topwin_from_list(_rtgui_topwin_list.next) == topwin)
            return 0;
        rt_list_remove(&topparent->list);
        rt_list_insert_after(&_rtgui_topwin_list, &(topparent->list));
    }
    else if (topwin->flag & WINTITLE_ONBTM)
    {
        /* botton layer window, before the fisrt bottom window or hidden window. */
        struct rt_list_node *node;
        struct rtgui_topwin *ntopwin = RT_NULL;

        rt_list_foreach(node, &_rtgui_topwin_list, next)
        {
            ntopwin = get_topwin_from_list(node);
            if ((ntopwin->flag & WINTITLE_ONBTM)
                    || !(ntopwin->flag & WINTITLE_SHOWN))
                break;
        }
        if (get_topwin_from_list(node) == topparent)
            return 0;
        rt_list_remove(&topparent->list);
        rt_list_insert_before(node, &(topparent->list));
    }
    else
    {
        /* normal layer window, before the fisrt shown normal layer window. */
        struct rtgui_topwin *ntopwin = RT_NULL;
        struct rt_list_node *node;

        rt_list_foreach(node, &_rtgui_topwin_list, next)
        {
            ntopwin = get_topwin_from_list(node);
            if (!((ntopwin->flag & WINTITLE_ONTOP)
                    && (ntopwin->flag & WINTITLE_SHOWN)))
                break;
        }
        if (get_topwin_from_list(node) == topparent)
            return 0;
        rt_list_remove(&topparent->list);
        rt_list_insert_before(node, &(topparent->list));
    }
    return 1;
}

static void _rtgui_topwin_raise_in_sibling(struct rtgui_topwin *topwin)
{
    struct rt_list_node *win_level;

    RT_ASSERT(topwin != RT_NULL);

    if (topwin->parent == RT_NULL)
        win_level = &_rtgui_topwin_list;
    else
        win_level = &topwin->parent->child_list;
    rt_list_remove(&topwin->list);
    rt_list_insert_after(win_level, &topwin->list);
}

/* it will do 2 things. One is moving the whole tree(the root of the tree) to
 * the front and the other is moving topwin to the front of it's siblings. */
static int _rtgui_topwin_raise_tree_from_root(struct rtgui_topwin *topwin)
{
    int moved;

    RT_ASSERT(topwin != RT_NULL);

    moved = _rtgui_topwin_move_whole_tree2top(topwin);
    /* root win is aleady moved by _rtgui_topwin_move_whole_tree2top */
    if (!IS_ROOT_WIN(topwin))
        _rtgui_topwin_raise_in_sibling(topwin);

    return moved;
}

/* activate a win means:
 * - deactivate the old focus win if any
 * - raise the window to the front of it's siblings
 * - activate a win
 */
rt_err_t rtgui_topwin_activate(struct rtgui_event_win_activate *event)
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
    struct rt_list_node *node;

    rt_list_foreach(node, &topwin->child_list, next)
    {
        if (!(get_topwin_from_list(node)->flag & WINTITLE_SHOWN))
            break;
        _rtgui_topwin_draw_tree(get_topwin_from_list(node), epaint);
    }

    epaint->wid = topwin->wid;
    rtgui_send(topwin->app, &(epaint->parent), sizeof(*epaint));
}

rt_err_t rtgui_topwin_activate_topwin(struct rtgui_topwin *topwin)
{
    int tpmoved;
    struct rtgui_topwin *old_focus_topwin;
    struct rtgui_event_paint epaint;

    RT_ASSERT(topwin != RT_NULL);

    RTGUI_EVENT_PAINT_INIT(&epaint);

    if (!(topwin->flag & WINTITLE_SHOWN))
        return -RT_ERROR;

    if (topwin->flag & WINTITLE_NOFOCUS)
    {
        /* just raise and show, no other effects.  Active window is the one
         * which will receive kbd events. So a no-focus window can only be
         * "raised" but not "activated".
         */
        tpmoved = _rtgui_topwin_raise_tree_from_root(topwin);
        rtgui_topwin_update_clip();
        if (tpmoved)
            _rtgui_topwin_draw_tree(_rtgui_topwin_get_root_win(topwin),
                                    &epaint);
        else
            _rtgui_topwin_draw_tree(topwin, &epaint);

        return RT_EOK;
    }

    if (topwin->flag & WINTITLE_ACTIVATE)
        return RT_EOK;

    old_focus_topwin = rtgui_topwin_get_focus();
    /* if topwin has the focus, it should have WINTITLE_ACTIVATE set and
     * returned above. */
    RT_ASSERT(old_focus_topwin != topwin);

    tpmoved = _rtgui_topwin_raise_tree_from_root(topwin);
    /* clip before active the window, so we could get right boarder region. */
    rtgui_topwin_update_clip();

    if (old_focus_topwin != RT_NULL)
    {
        /* deactivate the old focus window firstly, otherwise it will make the new
         * window invisible. */
        _rtgui_topwin_deactivate(old_focus_topwin);
    }

    _rtgui_topwin_only_activate(topwin);

    if (tpmoved)
        _rtgui_topwin_draw_tree(_rtgui_topwin_get_root_win(topwin),
                                &epaint);
    else
        _rtgui_topwin_draw_tree(topwin, &epaint);

    return RT_EOK;
}

/* map func to the topwin tree in preorder.
 *
 * Remember that we are in a embedded system so write the @param func memory
 * efficiently.
 */
rt_inline void _rtgui_topwin_preorder_map(struct rtgui_topwin *topwin, void (*func)(struct rtgui_topwin *))
{
    struct rt_list_node *child;

    RT_ASSERT(topwin != RT_NULL);
    RT_ASSERT(func != RT_NULL);

    func(topwin);

    rt_list_foreach(child, &topwin->child_list, next)
        _rtgui_topwin_preorder_map(get_topwin_from_list(child), func);
}

rt_inline void _rtgui_topwin_mark_hidden(struct rtgui_topwin *topwin)
{
    topwin->flag &= ~WINTITLE_SHOWN;
    RTGUI_WIDGET_HIDE(topwin->wid);
}

rt_inline void _rtgui_topwin_mark_shown(struct rtgui_topwin *topwin)
{
    if (topwin->flag & WINTITLE_SHOWN)
        return;

    topwin->flag |= WINTITLE_SHOWN;

    if (RTGUI_WIDGET_IS_HIDE(topwin->wid))
    {
        rtgui_widget_show(RTGUI_WIDGET(topwin->wid));
    }
}

rt_err_t rtgui_topwin_show(struct rtgui_event_win *event)
{
    struct rtgui_topwin *topwin;
    struct rtgui_win *wid = event->wid;

    topwin = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_list);
    /* no such a window recorded */
    if (topwin == RT_NULL)
        return -RT_ERROR;

    /* child windows could only be shown iif the parent is shown */
    if (!_rtgui_topwin_could_show(topwin))
    {
        return -RT_ERROR;
    }

    _rtgui_topwin_preorder_map(topwin, _rtgui_topwin_mark_shown);
    rtgui_topwin_activate_topwin(topwin);

    return RT_EOK;
}

static void _rtgui_topwin_clear_modal_tree(struct rtgui_topwin *topwin)
{
    struct rt_list_node *node;

    RT_ASSERT(topwin != RT_NULL);
    RT_ASSERT(topwin->parent != RT_NULL);

    while (!IS_ROOT_WIN(topwin))
    {
        rt_list_foreach(node, &topwin->parent->child_list, next)
        {
            get_topwin_from_list(node)->flag &= ~WINTITLE_MODALED;
            get_topwin_from_list(node)->wid->flag &= ~RTGUI_WIN_FLAG_UNDER_MODAL;
            if (get_topwin_from_list(node)->flag & WINTITLE_MODALING)
            {
                goto _out;
            }
        }
        topwin = topwin->parent;
    }
_out:
    /* clear the modal flag of the root window */
    topwin->flag &= ~WINTITLE_MODALED;
    topwin->wid->flag &= ~RTGUI_WIN_FLAG_UNDER_MODAL;
}

/* hide a window */
rt_err_t rtgui_topwin_hide(struct rtgui_event_win *event)
{
    struct rtgui_topwin *topwin;
    struct rtgui_topwin *old_focus_topwin;
    struct rtgui_win    *wid;
    struct rt_list_node *containing_list;

    if (!event)
        return -RT_ERROR;

    wid = event->wid;
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

    rt_list_remove(&topwin->list);
    rt_list_insert_before(containing_list, &topwin->list);

    /* update clip info */
    rtgui_topwin_update_clip();

    if (topwin->flag & WINTITLE_MODALING)
    {
        topwin->flag &= ~WINTITLE_MODALING;
        _rtgui_topwin_clear_modal_tree(topwin);
    }

    if (old_focus_topwin == topwin)
    {
        _rtgui_topwin_activate_next(topwin->flag);
    }

    topwin->flag &= ~WINTITLE_ACTIVATE;

    /* redraw the old rect */
    rtgui_topwin_redraw(&(topwin->extent));

    return RT_EOK;
}

/* move top window */
rt_err_t rtgui_topwin_move(struct rtgui_event_win_move *event)
{
    struct rtgui_topwin *topwin;
    int dx, dy;
    rtgui_rect_t old_rect; /* the old topwin coverage area */
    struct rtgui_list_node *node;

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

    /* move the monitor rect list */
    rtgui_list_foreach(node, &(topwin->monitor_list))
    {
        struct rtgui_mouse_monitor *monitor = rtgui_list_entry(node,
                                              struct rtgui_mouse_monitor,
                                              list);
        rtgui_rect_moveto(&(monitor->rect), dx, dy);
    }

    /* update windows clip info */
    rtgui_topwin_update_clip();

    /* update old window coverage area */
    rtgui_topwin_redraw(&old_rect);

    if (rtgui_rect_is_intersect(&old_rect, &(topwin->extent)) != RT_EOK)
    {
        /*
         * the old rect is not intersect with moved rect,
         * re-paint window
         */
        struct rtgui_event_paint epaint;
        RTGUI_EVENT_PAINT_INIT(&epaint);
        epaint.wid = topwin->wid;
        rtgui_send(topwin->app, &(epaint.parent), sizeof(epaint));
    }

    return RT_EOK;
}

/*
 * resize a top win
 * Note: currently, only support resize hidden window
 */
void rtgui_topwin_resize(struct rtgui_win *wid, rtgui_rect_t *rect)
{
    struct rtgui_topwin *topwin;
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

    /* update windows clip info */
    rtgui_topwin_update_clip();

    /* update old window coverage area */
    rtgui_topwin_redraw(rtgui_region_extents(&region));

    rtgui_region_fini(&region);
}

static struct rtgui_topwin *_rtgui_topwin_get_focus_from_list(struct rt_list_node *list)
{
    struct rt_list_node *node;

    RT_ASSERT(list != RT_NULL);

    rt_list_foreach(node, list, next)
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

struct rtgui_topwin *rtgui_topwin_get_focus(void)
{
    return _rtgui_topwin_get_focus_from_list(&_rtgui_topwin_list);
}

static struct rtgui_topwin *_rtgui_topwin_get_wnd_from_tree(struct rt_list_node *list,
        int x, int y,
        rt_bool_t exclude_modaled)
{
    struct rt_list_node *node;
    struct rtgui_topwin *topwin, *target;

    RT_ASSERT(list != RT_NULL);

    rt_list_foreach(node, list, next)
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

        if (rtgui_rect_contains_point(&(topwin->extent), x, y) == RT_EOK)
        {
            return topwin;
        }
    }

    return RT_NULL;
}

struct rtgui_topwin *rtgui_topwin_get_wnd(int x, int y)
{
    return _rtgui_topwin_get_wnd_from_tree(&_rtgui_topwin_list, x, y, RT_FALSE);
}

struct rtgui_topwin *rtgui_topwin_get_wnd_no_modaled(int x, int y)
{
    return _rtgui_topwin_get_wnd_from_tree(&_rtgui_topwin_list, x, y, RT_TRUE);
}

/* clip region from topwin, and the windows beneath it. */
rt_inline void _rtgui_topwin_clip_to_region(struct rtgui_topwin *topwin,
                                            struct rtgui_region *region)
{
    RT_ASSERT(region != RT_NULL);
    RT_ASSERT(topwin != RT_NULL);

    rtgui_region_reset(&topwin->wid->outer_clip, &topwin->wid->outer_extent);
    rtgui_region_intersect(&topwin->wid->outer_clip, &topwin->wid->outer_clip, region);
}

static void rtgui_topwin_update_clip(void)
{
    struct rtgui_topwin *top;
    struct rtgui_event_clip_info eclip;
    /* Note that the region is a "female die", that means it's the region you
     * can paint to, not the region covered by others.
     */
    struct rtgui_region region_available;

    if (rt_list_isempty(&_rtgui_topwin_list) ||
        !(get_topwin_from_list(_rtgui_topwin_list.next)->flag & WINTITLE_SHOWN))
        return;

    RTGUI_EVENT_CLIP_INFO_INIT(&eclip);

    rtgui_region_init_rect(&region_available, 0, 0,
                           rtgui_graphic_driver_get_default()->width,
                           rtgui_graphic_driver_get_default()->height);

    /* from top to bottom. */
    top = rtgui_topwin_get_topmost_window_shown(WINTITLE_ONTOP);
    /* 0 is normal layer */
    if (top == RT_NULL)
        top = rtgui_topwin_get_topmost_window_shown(WINTITLE_INIT);
    if (top == RT_NULL)
        top = rtgui_topwin_get_topmost_window_shown(WINTITLE_ONBTM);

    while (top != RT_NULL)
    {
        /* clip the topwin */
        _rtgui_topwin_clip_to_region(top, &region_available);

        /* update available region */
        rtgui_region_subtract_rect(&region_available, &region_available, &top->extent);

        /* send clip event to destination window */
        eclip.wid = top->wid;
        rtgui_send(top->app, &(eclip.parent), sizeof(struct rtgui_event_clip_info));

        top = _rtgui_topwin_get_next_shown(top);
    }

    rtgui_region_fini(&region_available);
}

static void _rtgui_topwin_redraw_tree(struct rt_list_node *list,
                                      struct rtgui_rect *rect,
                                      struct rtgui_event_paint *epaint)
{
    struct rt_list_node *node;

    RT_ASSERT(list != RT_NULL);
    RT_ASSERT(rect != RT_NULL);
    RT_ASSERT(epaint != RT_NULL);

    /* skip the hidden windows */
    rt_list_foreach(node, list, prev)
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
            rtgui_send(topwin->app, &(epaint->parent), sizeof(*epaint));
        }

        _rtgui_topwin_redraw_tree(&topwin->child_list, rect, epaint);
    }
}

static void rtgui_topwin_redraw(struct rtgui_rect *rect)
{
    struct rtgui_event_paint epaint;
    RTGUI_EVENT_PAINT_INIT(&epaint);
    epaint.wid = RT_NULL;

    _rtgui_topwin_redraw_tree(&_rtgui_topwin_list, rect, &epaint);
}

/* a window enter modal mode will modal all the sibling window and parent
 * window all along to the root window. If a root window modals, there is
 * nothing to do here.*/
rt_err_t rtgui_topwin_modal_enter(struct rtgui_event_win_modal_enter *event)
{
    struct rtgui_topwin *topwin, *parent_top;
    struct rt_list_node *node;

    topwin = rtgui_topwin_search_in_list(event->wid, &_rtgui_topwin_list);

    if (topwin == RT_NULL)
        return -RT_ERROR;

    if (IS_ROOT_WIN(topwin))
        return RT_EOK;

    parent_top = topwin->parent;

    /* modal window should be on top already */
    RT_ASSERT(get_topwin_from_list(parent_top->child_list.next) == topwin);

    do {
        rt_list_foreach(node, &parent_top->child_list, next)
        {
            get_topwin_from_list(node)->flag |= WINTITLE_MODALED;
            get_topwin_from_list(node)->wid->flag |= RTGUI_WIN_FLAG_UNDER_MODAL;
        }

        parent_top->flag |= WINTITLE_MODALED;
        parent_top->wid->flag |= RTGUI_WIN_FLAG_UNDER_MODAL;
        parent_top = parent_top->parent;
    } while (parent_top);

    topwin->flag &= ~WINTITLE_MODALED;
    topwin->wid->flag &= ~RTGUI_WIN_FLAG_UNDER_MODAL;
    topwin->flag |= WINTITLE_MODALING;

    return RT_EOK;
}

void rtgui_topwin_append_monitor_rect(struct rtgui_win *wid, rtgui_rect_t *rect)
{
    struct rtgui_topwin *win;

    /* parameters check */
    if (wid == RT_NULL || rect == RT_NULL) return;

    /* find topwin */
    win = rtgui_topwin_search_in_list(wid, &_rtgui_topwin_list);
    if (win == RT_NULL)
        return;

    /* append rect to top window monitor rect list */
    rtgui_mouse_monitor_append(&(win->monitor_list), rect);
}

void rtgui_topwin_remove_monitor_rect(struct rtgui_win *wid, rtgui_rect_t *rect)
{
    struct rtgui_topwin *win;

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

static struct rtgui_object* _get_obj_in_topwin(struct rtgui_topwin *topwin,
                                               struct rtgui_app *app,
                                               rt_uint32_t id)
{
    struct rtgui_object *object;
    struct rt_list_node *node;

    object = RTGUI_OBJECT(topwin->wid);
    if (object->id == id)
        return object;

    object = rtgui_container_get_object(RTGUI_CONTAINER(object), id);
    if (object)
        return object;

    rt_list_foreach(node, &topwin->child_list, next)
    {
        struct rtgui_topwin *topwin;

        topwin = get_topwin_from_list(node);
        if (topwin->app != app)
            continue;

        object = _get_obj_in_topwin(topwin, app, id);
        if (object)
            return object;
    }

    return RT_NULL;
}

struct rtgui_object* rtgui_get_object(struct rtgui_app *app, rt_uint32_t id)
{
    struct rtgui_object *object;
    struct rt_list_node *node;

    object = RTGUI_OBJECT(app);
    if (object->id == id)
        return object;

    rt_list_foreach(node, &_rtgui_topwin_list, next)
    {
        struct rtgui_topwin *topwin;

        topwin = get_topwin_from_list(node);
        if (topwin->app != app)
            continue;

        object = _get_obj_in_topwin(topwin, app, id);
        if (object)
            return object;
    }
    return RT_NULL;
}
RTM_EXPORT(rtgui_get_object);

struct rtgui_object* rtgui_get_self_object(rt_uint32_t id)
{
    return rtgui_get_object(rtgui_app_self(), id);
}
RTM_EXPORT(rtgui_get_self_object);

static void _rtgui_topwin_dump(struct rtgui_topwin *topwin)
{
    rt_kprintf("0x%p:%s,0x%x,%c%c",
               topwin, topwin->wid->title, topwin->flag,
               topwin->flag & WINTITLE_SHOWN ? 'S' : 'H',
               topwin->flag & WINTITLE_MODALED ? 'm' :
                  topwin->flag & WINTITLE_MODALING ? 'M' : ' ');
}

static void _rtgui_topwin_dump_tree(struct rtgui_topwin *topwin)
{
    struct rt_list_node *node;

    _rtgui_topwin_dump(topwin);

    rt_kprintf("(");
    rt_list_foreach(node, &topwin->child_list, next)
    {
        _rtgui_topwin_dump_tree(get_topwin_from_list(node));
    }
    rt_kprintf(")");
}

void rtgui_topwin_dump_tree(void)
{
    struct rt_list_node *node;

    rt_list_foreach(node, &_rtgui_topwin_list, next)
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
