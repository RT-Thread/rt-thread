/*
 * File      : caret.h
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
#ifndef __RTGUI_CARET_H__
#define __RTGUI_CARET_H__

#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/widget.h>

struct rtgui_caret
{
	/* show flag */
	rt_bool_t is_show;
	/* the show point of caret */
	struct rtgui_point show_point;

	/* widget owner */
	struct rtgui_widget* owner;

	/* caret buffer dc */
	struct rtgui_dc *dc;

	/* caret extent */
	struct rtgui_rect extent;

	/* the blink timer */
	struct rtgui_timer* timer;
	rt_int32_t timer_period;
};
typedef struct rtgui_caret rtgui_caret_t;

struct rtgui_caret* rtgui_caret_create(struct rtgui_widget* owner);
void rtgui_caret_destroy(struct rtgui_caret* caret);

void rtgui_caret_show(struct rtgui_caret* caret, rt_base_t x, rt_base_t y);
void rtgui_caret_hide(struct rtgui_caret* caret);
void rtgui_caret_draw(struct rtgui_caret* caret);

void rtgui_caret_set_point(struct rtgui_caret* caret, int x, int y);
void rtgui_caret_set_box(struct rtgui_caret* caret, int w, int h);

#endif
