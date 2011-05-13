/*
 * File      : list_view.h
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-01-06     Bernard      first version
 */

#ifndef __RTGUI_ABOUT_VIEW_H__
#define __RTGUI_ABOUT_VIEW_H__

#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/view.h>

DECLARE_CLASS_TYPE(aboutview);
/** Gets the type of a about view */
#define RTGUI_ABOUT_VIEW_TYPE       (RTGUI_TYPE(aboutview))
/** Casts the object to a about view */
#define RTGUI_ABOUT_VIEW(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_ABOUT_VIEW_TYPE, rtgui_about_view_t))
/** Checks if the object is a about view */
#define RTGUI_IS_ABOUT_VIEW(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_ABOUT_VIEW_TYPE))

struct rtgui_about_view
{
	struct rtgui_view parent;

	/* widget private data */
	rtgui_image_t* logo;
	const char* description;
};
typedef struct rtgui_about_view rtgui_about_view_t;

rtgui_type_t *rtgui_about_view_type_get(void);

rtgui_about_view_t* rtgui_about_view_create(rtgui_image_t *logo, const char* description);
rt_bool_t rtgui_about_view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event);

#endif
