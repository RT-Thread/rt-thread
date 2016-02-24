/*
 * File      : widget.c
 * This file is part of RT-Thread GUI
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-04     Bernard      first version
 * 2010-06-26     Bernard      add user_data to widget structure
 * 2013-10-07     Bernard      remove the win_check in update_clip.
 */

#include <rtgui/dc_client.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/container.h>
#ifdef RTGUI_USING_NOTEBOOK
#include <rtgui/widgets/notebook.h>
#endif

static void _rtgui_widget_constructor(rtgui_widget_t *widget)
{
    if (!widget) return;

    /* set widget as shown */
    widget->flag = RTGUI_WIDGET_FLAG_SHOWN;

    /* init list */
    rtgui_list_init(&(widget->sibling));

    /* init gc */
    widget->gc.foreground = default_foreground;
    widget->gc.background = default_background;
    widget->gc.font = rtgui_font_default();
    widget->gc.textstyle = RTGUI_TEXTSTYLE_NORMAL;
    widget->gc.textalign = RTGUI_ALIGN_LEFT | RTGUI_ALIGN_TOP;
    widget->align = RTGUI_ALIGN_LEFT | RTGUI_ALIGN_TOP;

    /* clear the garbage value of extent and clip */
    widget->extent.x1 = widget->extent.y1 = 0;
    widget->extent.x2 = widget->extent.y2 = 0;
    widget->min_width = widget->min_height = 0;
    rtgui_region_init_with_extents(&widget->clip, &widget->extent);

    /* set parent and toplevel root */
    widget->parent        = RT_NULL;
    widget->toplevel      = RT_NULL;

    /* some common event handler */
    widget->on_focus_in   = RT_NULL;
    widget->on_focus_out  = RT_NULL;
    widget->on_paint      = RT_NULL;

    /* set default event handler */
    rtgui_object_set_event_handler(RTGUI_OBJECT(widget), rtgui_widget_event_handler);

    /* init user data private to 0 */
    widget->user_data = 0;

    /* init clip information */
    rtgui_region_init(&(widget->clip));

    /* init hardware dc */
    rtgui_dc_client_init(widget);
}

/* Destroys the widget */
static void _rtgui_widget_destructor(rtgui_widget_t *widget)
{
    if (widget == RT_NULL) return;

    if (widget->parent != RT_NULL && RTGUI_IS_CONTAINER(widget->parent))
    {
        /* remove widget from parent's children list */
        rtgui_list_remove(&(RTGUI_CONTAINER(widget->parent)->children), &(widget->sibling));

        widget->parent = RT_NULL;
    }

    /* fini clip region */
    rtgui_region_fini(&(widget->clip));
}

DEFINE_CLASS_TYPE(widget, "widget",
                  RTGUI_PARENT_TYPE(object),
                  _rtgui_widget_constructor,
                  _rtgui_widget_destructor,
                  sizeof(struct rtgui_widget));
RTM_EXPORT(_rtgui_widget);

rtgui_widget_t *rtgui_widget_create(const rtgui_type_t *widget_type)
{
    struct rtgui_widget *widget;

    widget = RTGUI_WIDGET(rtgui_object_create(widget_type));

    return widget;
}
RTM_EXPORT(rtgui_widget_create);

void rtgui_widget_destroy(rtgui_widget_t *widget)
{
    rtgui_object_destroy(RTGUI_OBJECT(widget));
}
RTM_EXPORT(rtgui_widget_destroy);

void rtgui_widget_set_rect(rtgui_widget_t *widget, const rtgui_rect_t *rect)
{
    int delta_x, delta_y;

    if (widget == RT_NULL || rect == RT_NULL) return;

    /* update extent rectangle */
    widget->extent = *rect;
    if (RTGUI_IS_CONTAINER(widget))
    {
        /* re-do layout */
        rtgui_container_layout(RTGUI_CONTAINER(widget));
    }

    /* reset min width and height */
    widget->min_width  = rtgui_rect_width(widget->extent);
    widget->min_height = rtgui_rect_height(widget->extent);

    /* it's not empty, fini it */
    if (rtgui_region_not_empty(&(widget->clip)))
    {
        rtgui_region_fini(&(widget->clip));
    }

    /* reset clip info */
    rtgui_region_init_with_extents(&(widget->clip), rect);
    if ((widget->parent != RT_NULL) && (widget->toplevel != RT_NULL))
    {
        if ((void*)widget->parent == (void*)widget->toplevel)
        {
            rtgui_win_update_clip(widget->toplevel);
        }
        else
        {
            /* update widget clip */
            rtgui_widget_update_clip(widget->parent);
        }
    }

    /* move to a logic position if it's a container widget */
    if (RTGUI_IS_CONTAINER(widget))
    {
        delta_x = rect->x1 - widget->extent.x1;
        delta_y = rect->y1 - widget->extent.y1;

        rtgui_widget_move_to_logic(widget, delta_x, delta_y);
    }

}
RTM_EXPORT(rtgui_widget_set_rect);

void rtgui_widget_set_rectangle(rtgui_widget_t *widget, int x, int y, int width, int height)
{
    rtgui_rect_t rect;

    rect.x1 = x;
    rect.y1 = y;
    rect.x2 = x + width;
    rect.y2 = y + height;

    rtgui_widget_set_rect(widget, &rect);
}
RTM_EXPORT(rtgui_widget_set_rectangle);

void rtgui_widget_set_parent(rtgui_widget_t *widget, rtgui_widget_t *parent)
{
    /* set parent and toplevel widget */
    widget->parent = parent;
}
RTM_EXPORT(rtgui_widget_set_parent);

void rtgui_widget_get_extent(rtgui_widget_t *widget, rtgui_rect_t *rect)
{
    RT_ASSERT(widget != RT_NULL);
    RT_ASSERT(rect != RT_NULL);

    *rect = widget->extent;
}
RTM_EXPORT(rtgui_widget_get_extent);

void rtgui_widget_set_minsize(rtgui_widget_t *widget, int width, int height)
{
    RT_ASSERT(widget != RT_NULL);
    widget->min_width = width;
    widget->min_height = height;
}
RTM_EXPORT(rtgui_widget_set_minsize);

void rtgui_widget_set_minwidth(rtgui_widget_t *widget, int width)
{
    RT_ASSERT(widget != RT_NULL);

    widget->min_width = width;
}
RTM_EXPORT(rtgui_widget_set_minwidth);

void rtgui_widget_set_minheight(rtgui_widget_t *widget, int height)
{
    RT_ASSERT(widget != RT_NULL);

    widget->min_height = height;
}
RTM_EXPORT(rtgui_widget_set_minheight);

static void _widget_moveto(struct rtgui_widget* widget, int dx, int dy)
{
    struct rtgui_list_node *node;
    rtgui_widget_t *child;

    rtgui_rect_moveto(&(widget->extent), dx, dy);
    /* reset clip info */
    rtgui_region_init_with_extents(&(widget->clip), &(widget->extent));

    /* move each child */
    if (RTGUI_IS_CONTAINER(widget))
    {
        rtgui_list_foreach(node, &(RTGUI_CONTAINER(widget)->children))
        {
            child = rtgui_list_entry(node, rtgui_widget_t, sibling);

            _widget_moveto(child, dx, dy);
        }
    }
}

/*
 * This function moves widget and its children to a logic point
 */
void rtgui_widget_move_to_logic(rtgui_widget_t *widget, int dx, int dy)
{
    rtgui_rect_t rect;
    rtgui_widget_t *parent;

    if (widget == RT_NULL)
        return;

    /* give clip of this widget back to parent */
    parent = widget->parent;
    if (parent != RT_NULL)
    {
        /* get the parent rect, even if it's a transparent parent. */
        rect = parent->clip.extents;
    }

    /* we should find out the none-transparent parent */
    while (parent != RT_NULL && parent->flag & RTGUI_WIDGET_FLAG_TRANSPARENT) parent = parent->parent;
    if (parent != RT_NULL)
    {
        /* reset clip info */
        rtgui_region_init_with_extents(&(widget->clip), &(widget->extent));
        rtgui_region_intersect_rect(&(widget->clip), &(widget->clip), &rect);
        rtgui_region_intersect_rect(&(widget->clip), &(widget->clip), &(parent->extent));

        /* give back the extent */
        rtgui_region_union(&(parent->clip), &(parent->clip), &(widget->clip));
    }

    /* move this widget (and its children if it's a container) to destination point */
    _widget_moveto(widget, dx, dy);
    /* update this widget */
    rtgui_widget_update_clip(widget);
}
RTM_EXPORT(rtgui_widget_move_to_logic);

void rtgui_widget_get_rect(rtgui_widget_t *widget, rtgui_rect_t *rect)
{
    RT_ASSERT(widget != RT_NULL);

    if (rect != RT_NULL)
    {
        rect->x1 = rect->y1 = 0;
        rect->x2 = widget->extent.x2 - widget->extent.x1;
        rect->y2 = widget->extent.y2 - widget->extent.y1;
    }
}
RTM_EXPORT(rtgui_widget_get_rect);

/**
 * set widget draw style
 */
void rtgui_widget_set_border(rtgui_widget_t *widget, rt_uint32_t style)
{
    RT_ASSERT(widget != RT_NULL);

    widget->border_style = style;
    switch (style)
    {
    case RTGUI_BORDER_NONE:
        widget->border = 0;
        break;
    case RTGUI_BORDER_SIMPLE:
    case RTGUI_BORDER_UP:
    case RTGUI_BORDER_DOWN:
        widget->border = 1;
        break;
    case RTGUI_BORDER_STATIC:
    case RTGUI_BORDER_RAISE:
    case RTGUI_BORDER_SUNKEN:
    case RTGUI_BORDER_BOX:
    case RTGUI_BORDER_EXTRA:
        widget->border = 2;
        break;
    default:
        widget->border = 2;
        break;
    }
}
RTM_EXPORT(rtgui_widget_set_border);

void rtgui_widget_set_onfocus(rtgui_widget_t *widget, rtgui_event_handler_ptr handler)
{
    RT_ASSERT(widget != RT_NULL);

    widget->on_focus_in = handler;
}
RTM_EXPORT(rtgui_widget_set_onfocus);

void rtgui_widget_set_onunfocus(rtgui_widget_t *widget, rtgui_event_handler_ptr handler)
{
    RT_ASSERT(widget != RT_NULL);

    widget->on_focus_out = handler;
}
RTM_EXPORT(rtgui_widget_set_onunfocus);

void rtgui_widget_set_onpaint(rtgui_widget_t *widget, rtgui_event_handler_ptr handler)
{
    RT_ASSERT(widget != RT_NULL);

    widget->on_paint = handler;
}
RTM_EXPORT(rtgui_widget_set_onpaint);

/**
 * @brief Focuses the widget. The focused widget is the widget which can receive the keyboard events
 * @param widget a widget
 * @note The widget has to be attached to a toplevel widget, otherwise it will have no effect
 */
void rtgui_widget_focus(rtgui_widget_t *widget)
{
    struct rtgui_widget *old_focus;

    RT_ASSERT(widget != RT_NULL);
    RT_ASSERT(widget->toplevel != RT_NULL);

    if (!RTGUI_WIDGET_IS_FOCUSABLE(widget) || !RTGUI_WIDGET_IS_ENABLE(widget))
        return;

    old_focus = RTGUI_WIN(widget->toplevel)->focused_widget;
    if (old_focus == widget)
        return; /* it's the same focused widget */

    /* unfocused the old widget */
    if (old_focus != RT_NULL)
        rtgui_widget_unfocus(old_focus);

    /* set widget as focused */
    widget->flag |= RTGUI_WIDGET_FLAG_FOCUS;
    RTGUI_WIN(widget->toplevel)->focused_widget = widget;

    /* invoke on focus in call back */
    if (widget->on_focus_in != RT_NULL)
        widget->on_focus_in(RTGUI_OBJECT(widget), RT_NULL);
}
RTM_EXPORT(rtgui_widget_focus);

/**
 * @brief Unfocused the widget
 * @param widget a widget
 */
void rtgui_widget_unfocus(rtgui_widget_t *widget)
{

    RT_ASSERT(widget != RT_NULL);

    if (!widget->toplevel || !RTGUI_WIDGET_IS_FOCUSED(widget))
        return;

    widget->flag &= ~RTGUI_WIDGET_FLAG_FOCUS;

    if (widget->on_focus_out != RT_NULL)
        widget->on_focus_out(RTGUI_OBJECT(widget), RT_NULL);

    RTGUI_WIN(widget->toplevel)->focused_widget = RT_NULL;

    /* Ergodic constituent widget, make child loss of focus */
    if (RTGUI_IS_CONTAINER(widget))
    {
        rtgui_list_t *node;
        rtgui_list_foreach(node, &(RTGUI_CONTAINER(widget)->children))
        {
            rtgui_widget_t *child = rtgui_list_entry(node, rtgui_widget_t, sibling);
            if (RTGUI_WIDGET_IS_HIDE(child)) continue;
            rtgui_widget_unfocus(child);
        }
    }
}
RTM_EXPORT(rtgui_widget_unfocus);

void rtgui_widget_point_to_device(rtgui_widget_t *widget, rtgui_point_t *point)
{
    RT_ASSERT(widget != RT_NULL);

    if (point != RT_NULL)
    {
        point->x += widget->extent.x1;
        point->y += widget->extent.y1;
    }
}
RTM_EXPORT(rtgui_widget_point_to_device);

void rtgui_widget_rect_to_device(rtgui_widget_t *widget, rtgui_rect_t *rect)
{
    RT_ASSERT(widget != RT_NULL);

    if (rect != RT_NULL)
    {
        rect->x1 += widget->extent.x1;
        rect->x2 += widget->extent.x1;

        rect->y1 += widget->extent.y1;
        rect->y2 += widget->extent.y1;
    }
}
RTM_EXPORT(rtgui_widget_rect_to_device);

void rtgui_widget_point_to_logic(rtgui_widget_t *widget, rtgui_point_t *point)
{
    RT_ASSERT(widget != RT_NULL);

    if (point != RT_NULL)
    {
        point->x -= widget->extent.x1;
        point->y -= widget->extent.y1;
    }
}
RTM_EXPORT(rtgui_widget_point_to_logic);

void rtgui_widget_rect_to_logic(rtgui_widget_t *widget, rtgui_rect_t *rect)
{
    RT_ASSERT(widget != RT_NULL);

    if (rect != RT_NULL)
    {
        rect->x1 -= widget->extent.x1;
        rect->x2 -= widget->extent.x1;

        rect->y1 -= widget->extent.y1;
        rect->y2 -= widget->extent.y1;
    }
}
RTM_EXPORT(rtgui_widget_rect_to_logic);

struct rtgui_win *rtgui_widget_get_toplevel(rtgui_widget_t *widget)
{
    rtgui_widget_t *r;

    RT_ASSERT(widget != RT_NULL);

    if (widget->toplevel)
        return widget->toplevel;

    rt_kprintf("widget->toplevel not properly set\n");
    r = widget;
    /* get the toplevel widget */
    while (r->parent != RT_NULL)
        r = r->parent;

    /* set toplevel */
    widget->toplevel = RTGUI_WIN(r);

    return RTGUI_WIN(r);
}
RTM_EXPORT(rtgui_widget_get_toplevel);

rt_bool_t rtgui_widget_onupdate_toplvl(struct rtgui_object *object, struct rtgui_event *event)
{
    struct rtgui_widget *widget;
    struct rtgui_event_update_toplvl *eup;

    RT_ASSERT(object);
    RT_ASSERT(event);

    widget = RTGUI_WIDGET(object);
    eup = (struct rtgui_event_update_toplvl *)event;

    widget->toplevel = eup->toplvl;

    return RT_FALSE;
}
RTM_EXPORT(rtgui_widget_onupdate_toplvl);

rt_bool_t rtgui_widget_onpaint(struct rtgui_object *object, struct rtgui_event *event)
{
    if (RTGUI_WIDGET(object)->on_paint)
        return RTGUI_WIDGET(object)->on_paint(object, event);
    else
        return RT_FALSE;
}
RTM_EXPORT(rtgui_widget_onpaint);

rt_bool_t rtgui_widget_event_handler(struct rtgui_object *object, rtgui_event_t *event)
{
    RTGUI_WIDGET_EVENT_HANDLER_PREPARE;

    switch (event->type)
    {
    case RTGUI_EVENT_PAINT:
        return rtgui_widget_onpaint(object, event);
    case RTGUI_EVENT_SHOW:
        return rtgui_widget_onshow(object, event);
    case RTGUI_EVENT_HIDE:
        return rtgui_widget_onhide(object, event);
    case RTGUI_EVENT_UPDATE_TOPLVL:
        return rtgui_widget_onupdate_toplvl(object, event);
    default:
        break;
    }

    return rtgui_object_event_handler(object, event);
}
RTM_EXPORT(rtgui_widget_event_handler);

/*
 * This function updates the clip info of widget
 */
void rtgui_widget_update_clip(rtgui_widget_t *widget)
{
    rtgui_rect_t rect;
    struct rtgui_list_node *node;
    rtgui_widget_t *parent;

    /* no widget or widget is hide, no update clip */
    if (widget == RT_NULL || RTGUI_WIDGET_IS_HIDE(widget) || widget->parent == RT_NULL)
        return;

    parent = widget->parent;
    rect = parent->clip.extents;
    /* reset clip to extent */
    rtgui_region_reset(&(widget->clip), &(widget->extent));
    /* limit widget extent in parent extent */
    rtgui_region_intersect_rect(&(widget->clip), &(widget->clip), &rect);

    /* get the no transparent parent */
    while (parent != RT_NULL && parent->flag & RTGUI_WIDGET_FLAG_TRANSPARENT)
    {
        parent = parent->parent;
    }
    if (parent != RT_NULL)
    {
        /* give my clip back to parent */
        rtgui_region_union(&(parent->clip), &(parent->clip), &(widget->clip));

        /* subtract widget clip in parent clip */
        if (!(widget->flag & RTGUI_WIDGET_FLAG_TRANSPARENT) && RTGUI_IS_CONTAINER(parent))
        {
            rtgui_region_subtract_rect(&(parent->clip), &(parent->clip), &(widget->extent));
        }
    }

    /*
     * note: since the layout widget introduction, the sibling widget should not intersect.
     */

    /* if it's a container object, update the clip info of children */
    if (RTGUI_IS_CONTAINER(widget))
    {
        rtgui_widget_t *child;
        rtgui_list_foreach(node, &(RTGUI_CONTAINER(widget)->children))
        {
            child = rtgui_list_entry(node, rtgui_widget_t, sibling);

            rtgui_widget_update_clip(child);
        }
    }
}
RTM_EXPORT(rtgui_widget_update_clip);

void rtgui_widget_show(struct rtgui_widget *widget)
{
    struct rtgui_event_show eshow;
    RT_ASSERT(widget != RT_NULL);

    if (!RTGUI_WIDGET_IS_HIDE(widget))
        return;

    RTGUI_WIDGET_UNHIDE(widget);

    if (widget->toplevel != RT_NULL)
    {
        RTGUI_EVENT_SHOW_INIT(&eshow);
        if (RTGUI_OBJECT(widget)->event_handler != RT_NULL)
        {
            RTGUI_OBJECT(widget)->event_handler(
                RTGUI_OBJECT(widget),
                &eshow);
        }
    }
}
RTM_EXPORT(rtgui_widget_show);

void rtgui_widget_hide(struct rtgui_widget *widget)
{
    struct rtgui_event_hide ehide;
    RT_ASSERT(widget != RT_NULL);

    if (RTGUI_WIDGET_IS_HIDE(widget))
        return;

    RTGUI_WIDGET_HIDE(widget);
    if (widget->toplevel != RT_NULL)
    {
        RTGUI_EVENT_HIDE_INIT(&ehide);
        if (RTGUI_OBJECT(widget)->event_handler != RT_NULL)
        {
            RTGUI_OBJECT(widget)->event_handler(
                RTGUI_OBJECT(widget),
                &ehide);
        }
    }
}
RTM_EXPORT(rtgui_widget_hide);

rt_bool_t rtgui_widget_onshow(struct rtgui_object *object, struct rtgui_event *event)
{
    struct rtgui_widget *widget = RTGUI_WIDGET(object);

    if (RTGUI_WIDGET_IS_HIDE(object)) return RT_FALSE;

    if (widget->parent != RT_NULL)
    {
        rtgui_widget_clip_parent(widget);
    }

    return RT_FALSE;
}
RTM_EXPORT(rtgui_widget_onshow);

rt_bool_t rtgui_widget_onhide(struct rtgui_object *object, struct rtgui_event *event)
{
    struct rtgui_widget *widget = RTGUI_WIDGET(object);

    if (RTGUI_WIDGET_IS_HIDE(object))
        return RT_FALSE;

    if (widget->parent != RT_NULL)
    {
        rtgui_widget_clip_return(widget);
    }

    return RT_FALSE;
}
RTM_EXPORT(rtgui_widget_onhide);

rtgui_color_t rtgui_widget_get_parent_foreground(rtgui_widget_t *widget)
{
    rtgui_widget_t *parent;

    /* get parent widget */
    parent = widget->parent;
    if (parent == RT_NULL)
        return RTGUI_WIDGET_FOREGROUND(widget);

    while (parent->parent != RT_NULL && (RTGUI_WIDGET_FLAG(parent) & RTGUI_WIDGET_FLAG_TRANSPARENT))
        parent = parent->parent;

    /* get parent's color */
    return RTGUI_WIDGET_FOREGROUND(parent);
}
RTM_EXPORT(rtgui_widget_get_parent_foreground);

rtgui_color_t rtgui_widget_get_parent_background(rtgui_widget_t *widget)
{
    rtgui_widget_t *parent;

    /* get parent widget */
    parent = widget->parent;
    if (parent == RT_NULL)
        return RTGUI_WIDGET_BACKGROUND(widget);

    while (parent->parent != RT_NULL && (RTGUI_WIDGET_FLAG(parent) & RTGUI_WIDGET_FLAG_TRANSPARENT))
        parent = parent->parent;

    /* get parent's color */
    return RTGUI_WIDGET_BACKGROUND(parent);
}
RTM_EXPORT(rtgui_widget_get_parent_background);

void rtgui_widget_clip_parent(rtgui_widget_t *widget)
{
    rtgui_widget_t *parent;

    parent = widget->parent;
    /* get the no transparent parent */
    while (parent != RT_NULL && parent->flag & RTGUI_WIDGET_FLAG_TRANSPARENT) parent = parent->parent;

    /* clip the widget extern from parent */
    if (parent != RT_NULL) rtgui_region_subtract(&(parent->clip), &(parent->clip), &(widget->clip));
}
RTM_EXPORT(rtgui_widget_clip_parent);

void rtgui_widget_clip_return(rtgui_widget_t *widget)
{
    rtgui_widget_t *parent;

    parent = widget->parent;
    /* get the no transparent parent */
    while (parent != RT_NULL && parent->flag & RTGUI_WIDGET_FLAG_TRANSPARENT) parent = parent->parent;

    /* give clip back to parent */
    if (parent != RT_NULL) rtgui_region_union(&(parent->clip), &(parent->clip), &(widget->clip));
}
RTM_EXPORT(rtgui_widget_clip_return);

void rtgui_widget_update(rtgui_widget_t *widget)
{
    struct rtgui_event_paint paint;
    RTGUI_EVENT_PAINT_INIT(&paint);
    paint.wid = RT_NULL;

    RT_ASSERT(widget != RT_NULL);

    if (RTGUI_OBJECT(widget)->event_handler != RT_NULL &&
        !(RTGUI_WIDGET_FLAG(widget) & RTGUI_WIDGET_FLAG_IN_ANIM))
    {
        RTGUI_OBJECT(widget)->event_handler(RTGUI_OBJECT(widget),
                                            &paint.parent);
    }
}
RTM_EXPORT(rtgui_widget_update);

rtgui_widget_t *rtgui_widget_get_next_sibling(rtgui_widget_t *widget)
{
    rtgui_widget_t *sibling = RT_NULL;

    if (widget->sibling.next != RT_NULL)
    {
        sibling = rtgui_list_entry(widget->sibling.next, rtgui_widget_t, sibling);
    }

    return sibling;
}
RTM_EXPORT(rtgui_widget_get_next_sibling);

rtgui_widget_t *rtgui_widget_get_prev_sibling(rtgui_widget_t *widget)
{
    struct rtgui_list_node *node;
    rtgui_widget_t *sibling, *parent;

    node = RT_NULL;
    sibling = RT_NULL;
    parent = widget->parent;
    if (parent != RT_NULL)
    {
        rtgui_list_foreach(node, &(RTGUI_CONTAINER(parent)->children))
        {
            if (node->next == &(widget->sibling))
                break;
        }
    }

    if (node != RT_NULL)
        sibling = rtgui_list_entry(node, rtgui_widget_t, sibling);

    return sibling;
}
RTM_EXPORT(rtgui_widget_get_prev_sibling);

rt_bool_t rtgui_widget_is_in_animation(rtgui_widget_t *widget)
{
    /* check the visible of widget */
    while (widget != RT_NULL)
    {
        if (widget->flag & RTGUI_WIDGET_FLAG_IN_ANIM)
        {
            return RT_TRUE;
        }
        widget = widget->parent;
    }
    return RT_FALSE;
}
RTM_EXPORT(rtgui_widget_is_in_animation);

#ifdef RTGUI_WIDGET_DEBUG
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
void rtgui_widget_dump(rtgui_widget_t *widget)
{
    struct rtgui_object *obj;

    obj = RTGUI_OBJECT(widget);
    rt_kprintf("widget type: %s ", obj->type->name);

    if (RTGUI_IS_WIN(widget) == RT_TRUE)
        rt_kprintf(":%s ", RTGUI_WIN(widget)->title);
    else if ((RTGUI_IS_LABEL(widget) == RT_TRUE) || (RTGUI_IS_BUTTON(widget) == RT_TRUE))
        rt_kprintf(":%s ", RTGUI_LABEL(widget)->text);

    rt_kprintf("extent(%d, %d) - (%d, %d)\n", widget->extent.x1,
               widget->extent.y1, widget->extent.x2, widget->extent.y2);
    // rtgui_region_dump(&(widget->clip));
}
#endif

