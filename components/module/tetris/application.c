/*
 * File      : app.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-08-28     Yi.Qiu       the first version
 */

/**
 * @addtogroup LM3S
 */
/*@{*/

#include <rtthread.h>
#include <rtgui/rtgui.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/workbench.h>

extern void tetris_ui_entry(void* parameter);

int rt_application_init()
{
	rt_thread_t tid;
	rtgui_rect_t rect;

	/* ×¢²áÃæ°å */
	rect.x1 = 0;
	rect.y1 = 0;
	rect.x2 = 128;
	rect.y2 = 96;
	rtgui_panel_register("main", &rect);
	rtgui_panel_set_default_focused("main");

	tid = rt_thread_create("wb", tetris_ui_entry, RT_NULL, 2048, 20, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
	return 0;
}
/*@}*/
