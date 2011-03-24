/*
 * File      : scrollbar.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-08-09     Bernard      first version
 */
#ifndef __RTGUI_SCROLLBAR_H__
#define __RTGUI_SCROLLBAR_H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/widget.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Gets the type of a scrollbar */
#define RTGUI_SCROLLBAR_TYPE       (rtgui_scrollbar_type_get())
/** Casts the object to an rtgui_scrollbar */
#define RTGUI_SCROLLBAR(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_SCROLLBAR_TYPE, rtgui_scrollbar_t))
/** Checks if the object is an rtgui_scrollbar */
#define RTGUI_IS_SCROLLBAR(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_SCROLLBAR_TYPE))

#define RTGUI_DEFAULT_SB_WIDTH			16

/* scrollbar status/positions*/
#define SBAR_UNKNOWN        0x0000
#define SBAR_LEFTARROW      0x0001 //在向左按钮上
#define SBAR_RIGHTARROW     0x0002 //在向右按钮上
#define SBAR_LEFTSPACE      0x0004 //在活动块左侧空白处
#define SBAR_RIGHTSPACE     0x0008 //在活动块右侧空白处
#define SBAR_HORZTHUMB      0x0010 //活动块水平滑动
#define SBAR_UPARROW        0x0020 //状态向上
#define SBAR_DOWNARROW      0x0040 //状态向下
#define SBAR_UPSPACE        0x0080 //在活动块上侧空白处
#define SBAR_DOWNSPACE      0x0100 //在活动块下侧空白处
#define SBAR_VERTTHUMB      0x0200 //活动块垂直滑动

#define SBAR_UPTHUMB		0x0400 //活动块向上滑动
#define SBAR_DOWNTHUMB		0x0800 //活动块向下滑动
#define SBAR_LEFTTHUMB		0x1000 //活动块向左滑动
#define SBAR_RIGHTTHUMB		0x2000 //活动块向右滑动

struct rtgui_scrollbar
{
	/* inherit from widget */
	rtgui_widget_t parent;

	rt_uint32_t orient;
	rt_uint32_t status;

	/* page_step = display lines of scrollbar */
	/* thumb_len = line_step * page_step / (page_step - (button width * 2)) */
	rt_int16_t line_step, page_step;
	rt_int16_t value, thumb_len,thumb_w;
	/* position 1:1 width of scrollbar */
	rt_int16_t count;
	
	PVOID widgetlnk;//链接的控件
	rt_bool_t (*on_scroll) (PVOID wdt, rtgui_event_t* event);
};
typedef struct rtgui_scrollbar rtgui_scrollbar_t;

rtgui_type_t *rtgui_scrollbar_type_get(void);

rtgui_scrollbar_t* rtgui_scrollbar_create(PVOID wdt,int left,int top,int w,int len,int orient);
void rtgui_scrollbar_destroy(rtgui_scrollbar_t* bar);

void rtgui_scrollbar_get_thumb_rect(rtgui_scrollbar_t *bar, rtgui_rect_t *erect);

void rtgui_scrollbar_set_range(rtgui_scrollbar_t* bar, int count);
void rtgui_scrollbar_set_value(rtgui_scrollbar_t* bar, rt_int16_t value);

void rtgui_scrollbar_set_onscroll(rtgui_scrollbar_t* bar, rtgui_event_handler_ptr handler);
void rtgui_scrollbar_set_orientation(rtgui_scrollbar_t* bar, int orient);
void rtgui_scrollbar_set_page_step(rtgui_scrollbar_t* bar, int step);
void rtgui_scrollbar_set_line_step(rtgui_scrollbar_t* bar, int step);

rt_bool_t rtgui_scrollbar_event_handler(PVOID wdt, rtgui_event_t* event);

#ifdef __cplusplus
}
#endif

#endif
