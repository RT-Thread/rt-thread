/*
 * File      : groupbox.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-07-29     Bernard      first version
 */
#ifndef __RTGUI_GROUPBOX_H__
#define __RTGUI_GROUPBOX_H__

#include <rtgui/rtgui.h>
#include <rtgui/event.h>
#include <rtgui/widgets/panel.h>
#include <rtgui/widgets/box.h>

DECLARE_CLASS_TYPE(groupbox);

/** Gets the type of a groupbox */
#define RTGUI_GROUPBOX_TYPE       (RTGUI_TYPE(groupbox))
/** Casts the object to an groupbox */
#define RTGUI_GROUPBOX(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_GROUPBOX_TYPE, rtgui_groupbox_t))
/** Checks if the object is an rtgui_groupbox */
#define RTGUI_IS_GROUPBOX(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_GROUPBOX_TYPE))

typedef void (*widget_select_t)(struct rtgui_widget *widget, rt_bool_t selected);

/*
 * the groupbox widget
 *
 * The Group Box is a container widget, in which user can place some other widget into it.
 * However, the current selected in group box must be notified by user:
 * - invoke rtgui_groupbox_select_widget to notify group box the current selected widget;
 * - when a widget has been selected, group box invokes groupbox->select_func to change
 *   the status of widget, for example un-select this widget.
 */
struct rtgui_groupbox
{
    struct rtgui_panel parent;

    char *label;
    struct rtgui_box *box;
    struct rtgui_widget *selected;

    widget_select_t select_func;
    rtgui_event_handler_ptr on_selected;
};
typedef struct rtgui_groupbox rtgui_groupbox_t;

rtgui_groupbox_t *rtgui_groupbox_create(const char *label, struct rtgui_rect *rect, int style, widget_select_t select_func);
void rtgui_groupbox_destroy(rtgui_groupbox_t *groupbox);

void rtgui_groupbox_layout(struct rtgui_groupbox *box);

void rtgui_groupbox_add_widget(struct rtgui_groupbox *box, struct rtgui_widget *widget);
void rtgui_groupbox_select_widget(struct rtgui_groupbox *box, struct rtgui_widget *widget);
struct rtgui_widget *rtgui_groupbox_get_selected(struct rtgui_groupbox *box);

rt_bool_t rtgui_groupbox_event_handler(struct rtgui_object *object, struct rtgui_event *event);

rt_inline void rtgui_groupbox_set_onselected(struct rtgui_groupbox *box, rtgui_event_handler_ptr on_selected)
{
    RT_ASSERT(box != RT_NULL);
    box->on_selected = on_selected;
}

#endif

