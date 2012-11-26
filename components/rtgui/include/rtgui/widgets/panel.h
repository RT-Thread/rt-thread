/*
 * File      : panel.h
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
#ifndef __RTGUI_PANEL_H__
#define __RTGUI_PANEL_H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/container.h>

DECLARE_CLASS_TYPE(panel);

/** Gets the type of a panel */
#define RTGUI_PANEL_TYPE       (RTGUI_TYPE(panel))
/** Casts the object to an panel */
#define RTGUI_PANEL(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_PANEL_TYPE, rtgui_panel_t))
/** Checks if the object is an rtgui_panel */
#define RTGUI_IS_PANEL(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_PANEL_TYPE))

/*
 * the panel widget
 */
struct rtgui_panel
{
    struct rtgui_container parent;

    int border_style;
};
typedef struct rtgui_panel rtgui_panel_t;

rtgui_panel_t *rtgui_panel_create(int border_style);
void rtgui_panel_destroy(rtgui_panel_t *panel);

rt_inline void rtgui_panel_set_border(struct rtgui_panel *panel, int border_style)
{
    RT_ASSERT(panel != RT_NULL);
    panel->border_style = border_style;
}

rt_bool_t rtgui_panel_event_handler(struct rtgui_object *object, struct rtgui_event *event);

#endif
