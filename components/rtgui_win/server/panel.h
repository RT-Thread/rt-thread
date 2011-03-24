/*
 * File      : panel.h
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

#ifndef __RT_PANEL_H__
#define __RT_PANEL_H__

#include <rtgui/rtgui.h>
#include <rtgui/list.h>
#include <rtgui/image.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/container.h>

#define RTGUI_PANEL_STATUS_MODAL	(1ul << 0)	/* panel is modal mode showing */	

#define RTGUI_PANEL_IS_MODAL_MODE(panel)	(panel->status & RTGUI_PANEL_STATUS_MODAL)

typedef struct rtgui_panel rtgui_panel_t;

#define RTGUI_PANEL_TYPE       (rtgui_panel_type_get())
#define RTGUI_PANEL(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_PANEL_TYPE, rtgui_panel_t))
#define RTGUI_IS_PANEL(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_PANEL_TYPE))

struct rtgui_panel
{
	rtgui_container_t   parent;
	struct rt_thread*	tid;		//panelÏß³Ì

	PVOID				modal_widget;
	rt_uint32_t 		status;		//panelµÄ×´Ì¬
	rtgui_image_t*		image;		//±³¾°Í¼Æ¬
};

extern rtgui_rect_t *external_clip_rect;
extern rt_uint32_t	external_clip_size;

rtgui_type_t *rtgui_panel_type_get(void);
rtgui_panel_t* rtgui_panel_create(int left, int top, int w, int h);

void rtgui_panel_set(rtgui_panel_t *panel);
rtgui_panel_t* rtgui_panel_get(void);
struct rt_thread* PanelGetActiveThread(void);
void PanelSetActiveThread(struct rt_thread* tid);

rt_bool_t rtgui_panel_event_handler(PVOID wdt,rtgui_event_t *event);
void rtgui_panel_show(rtgui_panel_t *panel);
void rtgui_panel_event_loop(rtgui_panel_t *panel);

extern rtgui_panel_t *rtgui_panel;

#endif
