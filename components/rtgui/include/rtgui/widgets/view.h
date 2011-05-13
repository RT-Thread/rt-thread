/*
 * File      : view.h
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
#ifndef __RTGUI_VIEW_H__
#define __RTGUI_VIEW_H__

#include <rtgui/widgets/box.h>
#include <rtgui/widgets/container.h>

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_CLASS_TYPE(view);
/** Gets the type of a view */
#define RTGUI_VIEW_TYPE       (RTGUI_TYPE(view))
/** Casts the object to an rtgui_view */
#define RTGUI_VIEW(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_VIEW_TYPE, rtgui_view_t))
/** Checks if the object is an rtgui_view */
#define RTGUI_IS_VIEW(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_VIEW_TYPE))

/*
 * the view widget
 */
struct rtgui_view
{
	/* inherit from container */
	struct rtgui_container parent;

	/* private field */
	char* title;
	rt_bool_t modal_show;
};
typedef struct rtgui_view rtgui_view_t;

rtgui_view_t* rtgui_view_create(const char* title);
void rtgui_view_destroy(rtgui_view_t* view);

rt_bool_t rtgui_view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event);

#ifndef RTGUI_USING_SMALL_SIZE
void rtgui_view_set_box(rtgui_view_t* view, rtgui_box_t* box);
#endif

rtgui_modal_code_t rtgui_view_show(rtgui_view_t* view, rt_bool_t is_modal);
void rtgui_view_hide(rtgui_view_t* view);
void rtgui_view_end_modal(rtgui_view_t* view, rtgui_modal_code_t modal_code);

char* rtgui_view_get_title(rtgui_view_t* view);
void rtgui_view_set_title(rtgui_view_t* view, const char* title);

#ifdef __cplusplus
}
#endif

#endif
