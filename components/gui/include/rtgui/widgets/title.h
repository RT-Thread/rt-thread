/*
 * File      : title.h
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
#ifndef __RTGUI_TITLE__
#define __RTGUI_TITLE__

#include <rtgui/widgets/widget.h>

DECLARE_CLASS_TYPE(wintitle);
/** Gets the type of a title */
#define RTGUI_WINTITLE_TYPE       (RTGUI_TYPE(wintitle))
/** Casts the object to an rtgui_wintitle */
#define RTGUI_WINTITLE(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_WINTITLE_TYPE, rtgui_wintitle_t))
/** Checks if the object is an rtgui_wintitle */
#define RTGUI_IS_WINTITLE(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_WINTITLE_TYPE))

struct rtgui_wintitle
{
    struct rtgui_widget parent;
};
typedef struct rtgui_wintitle rtgui_wintitle_t;

rtgui_wintitle_t *rtgui_wintitle_create(struct rtgui_win *window);
void rtgui_wintitle_destroy(rtgui_wintitle_t *wintitle);

rt_bool_t rtgui_wintile_event_handler(struct rtgui_object *object, rtgui_event_t *event);

#endif
