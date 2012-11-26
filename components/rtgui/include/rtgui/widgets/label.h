/*
 * File      : label.h
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
#ifndef __RTGUI_LABEL_H__
#define __RTGUI_LABEL_H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/widget.h>

DECLARE_CLASS_TYPE(label);

/** Gets the type of a button */
#define RTGUI_LABEL_TYPE       (RTGUI_TYPE(label))
/** Casts the object to an rtgui_button */
#define RTGUI_LABEL(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_LABEL_TYPE, rtgui_label_t))
/** Checks if the object is an rtgui_button */
#define RTGUI_IS_LABEL(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_LABEL_TYPE))

/*
 * the label widget
 */
struct rtgui_label
{
    struct rtgui_widget parent;

    /* label */
    char *text;
};
typedef struct rtgui_label rtgui_label_t;

rtgui_label_t *rtgui_label_create(const char *text);
void rtgui_label_destroy(rtgui_label_t *label);

rt_bool_t rtgui_label_event_handler(struct rtgui_object *object, struct rtgui_event *event);

void rtgui_label_set_text(rtgui_label_t *label, const char *text);
char *rtgui_label_get_text(rtgui_label_t *label);

#endif
