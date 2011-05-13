/*
 * File      : workbench.h
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-04     Bernard      first version
 */
#ifndef __RTGUI_WORKBENCH_H__
#define __RTGUI_WORKBENCH_H__

#include <rtgui/rtgui.h>
#include <rtgui/list.h>
#include <rtgui/region.h>
#include <rtgui/dc.h>

#include <rtgui/widgets/view.h>
#include <rtgui/widgets/toplevel.h>

#define RTGUI_WORKBENCH_FLAG_VISIBLE	0x00	/* workbench is visible */
#define RTGUI_WORKBENCH_FLAG_INVISIBLE	0x01	/* workbench is invisible */
#define RTGUI_WORKBENCH_FLAG_FULLSCREEN	0x02	/* workbench is full screen */
#define RTGUI_WORKBENCH_FLAG_MODAL_MODE	0x04	/* workbench is modal mode showing */

#define RTGUI_WORKBENCH_FLAG_CLOSEBLE	0x00
#define RTGUI_WORKBENCH_FLAG_UNCLOSEBLE	0x10
#define RTGUI_WORKBENCH_FLAG_CLOSED		0x20

#define RTGUI_WORKBENCH_FLAG_DEFAULT	RTGUI_WORKBENCH_FLAG_VISIBLE | RTGUI_WORKBENCH_FLAG_CLOSEBLE

#define RTGUI_WORKBENCH_IS_MODAL_MODE(w) ((w)->flag & RTGUI_WORKBENCH_FLAG_MODAL_MODE)

DECLARE_CLASS_TYPE(workbench);

/** Gets the type of a workbench */
#define RTGUI_WORKBENCH_TYPE       (RTGUI_TYPE(workbench))
/** Casts the object to an rtgui_workbench */
#define RTGUI_WORKBENCH(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_WORKBENCH_TYPE, rtgui_workbench_t))
/** Checks if the object is an rtgui_workbench */
#define RTGUI_IS_WORKBENCH(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_WORKBENCH_TYPE))

struct rtgui_workbench
{
	/* inherit from toplevel */
	struct rtgui_toplevel parent;

	/* panel id */
	rtgui_panel_t* panel;

	/* workbench flag */
	rt_uint8_t flag;
	rtgui_modal_code_t modal_code;
	rtgui_widget_t *modal_widget;

	/* workbench title */
	unsigned char* title;
	rtgui_view_t* current_view;
};

rtgui_type_t* rtgui_workbench_type_get(void);

rtgui_workbench_t *rtgui_workbench_create(const char* panel_name, const unsigned char* title);
void rtgui_workbench_destroy(rtgui_workbench_t* workbench);
void rtgui_workbench_close(rtgui_workbench_t* workbench);

rt_bool_t rtgui_workbench_event_handler(rtgui_widget_t* widget, rtgui_event_t* event);

void rtgui_workbench_set_flag(rtgui_workbench_t* workbench, rt_uint8_t flag);

rt_bool_t rtgui_workbench_event_loop(rtgui_workbench_t* workbench);

rt_err_t rtgui_workbench_show (rtgui_workbench_t* workbench);
rt_err_t rtgui_workbench_hide (rtgui_workbench_t* workbench);

void rtgui_workbench_add_view(rtgui_workbench_t* workbench, rtgui_view_t* view);
void rtgui_workbench_remove_view(rtgui_workbench_t* workbench, rtgui_view_t* view);
void rtgui_workbench_show_view(rtgui_workbench_t* workbench, rtgui_view_t* view);
void rtgui_workbench_hide_view(rtgui_workbench_t* workbench, rtgui_view_t* view);

rtgui_view_t *rtgui_workbench_get_current_view(rtgui_workbench_t * workbench);

#endif
