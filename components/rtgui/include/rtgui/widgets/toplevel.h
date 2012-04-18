/*
 * File      : toplevel.h
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
#ifndef __RTGUI_TOPLEVEL_H__
#define __RTGUI_TOPLEVEL_H__

#include <rtgui/widgets/container.h>

DECLARE_CLASS_TYPE(toplevel);
/** Gets the type of a toplevel */
#define RTGUI_TOPLEVEL_TYPE       (RTGUI_TYPE(toplevel))
/** Casts the object to an rtgui_toplevel */
#define RTGUI_TOPLEVEL(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_TOPLEVEL_TYPE, rtgui_toplevel_t))
/** Checks if the object is an rtgui_toplevel */
#define RTGUI_IS_TOPLEVEL(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_TOPLEVEL_TYPE))

struct rtgui_toplevel
{
	/* inherit from view */
	rtgui_container_t parent;

	/* drawing count */
	rt_base_t drawing;

	/* external clip info */
	rtgui_rect_t*	external_clip_rect;
	rt_uint32_t		external_clip_size;
};
typedef struct rtgui_toplevel rtgui_toplevel_t;

rt_bool_t rtgui_toplevel_event_handler(struct rtgui_object* widget, struct rtgui_event* event);
void rtgui_toplevel_update_clip(rtgui_toplevel_t* top);

#endif
