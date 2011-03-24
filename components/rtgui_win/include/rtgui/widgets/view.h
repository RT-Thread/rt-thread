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

#include <rtgui/widgets/container.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Gets the type of a view */
#define RTGUI_VIEW_TYPE       (rtgui_view_type_get())
/** Casts the object to an rtgui_view_t */
#define RTGUI_VIEW(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_VIEW_TYPE, rtgui_view_t))
/** Checks if the object is an rtgui_view_t */
#define RTGUI_IS_VIEW(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_VIEW_TYPE))

/*
 * the view widget
 */
struct rtgui_view
{
	/* inherit from box */
	rtgui_container_t parent;

	/* private field */
	char* title;
};
typedef struct rtgui_view rtgui_view_t;

rtgui_type_t *rtgui_view_type_get(void);

rtgui_view_t *rtgui_view_create(PVOID wdt,const char* title,int left,int top,int w,int h);
void rtgui_view_destroy(rtgui_view_t* view);

rt_bool_t rtgui_view_event_handler(PVOID wdt, rtgui_event_t* event);

rt_bool_t rtgui_view_show(rtgui_view_t* view);
void rtgui_view_hide(rtgui_view_t* view);

char* rtgui_view_get_title(rtgui_view_t* view);
void rtgui_view_set_title(rtgui_view_t* view, const char* title);
void rtgui_view_show_child(PVOID wdt,const char* name);


#ifdef __cplusplus
}
#endif

#endif
