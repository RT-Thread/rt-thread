/*
 * File      : window.h
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
 * 2010-05-03     Bernard      add win close function
 */
#ifndef __RTGUI_WINDOW_H__
#define __RTGUI_WINDOW_H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/container.h>

/** Gets the type of a win */
#define RTGUI_WIN_TYPE       (rtgui_win_type_get())
/** Casts the object to an rtgui_win_t */
#define RTGUI_WIN(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_WIN_TYPE, rtgui_win_t))
/** Checks if the object is an rtgui_win_t */
#define RTGUI_IS_WIN(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_WIN_TYPE))

#define RTGUI_WIN_CLOSEBOX_WIDTH	16
#define RTGUI_WIN_CLOSEBOX_HEIGHT  	16

#define RTGUI_WIN_TITLE_HEIGHT	 	20	//标题栏高度
#define RTGUI_WIN_STATUS_HEIGHT	 	20	//状态栏高度
#define RTGUI_WIN_MENU_HEIGHT		20  //菜单栏高度

//窗口的状态
#define RTGUI_WIN_STATUS_MODAL	 	(1ul << 0)	//模式窗口
#define RTGUI_WIN_STATUS_MIN		(1ul << 1)
#define RTGUI_WIN_STATUS_MAX		(1ul << 2)	//窗口处于最大化状态
#define RTGUI_WIN_STATUS_CLOSED	 	(1ul << 3)	//关闭的
#define RTGUI_WIN_STATUS_ACTIVATE	(1ul << 4)	//活动的
#define RTGUI_WIN_STATUS_FOCUS	 	(1ul << 5)	//获得焦点的

#define RTGUI_WIN_IS_MODAL_MODE(w)	(w->status & RTGUI_WIN_STATUS_MODAL)
//窗口的样式,属性
#define RTGUI_WIN_TITLE			 	(1ul << 1)	//标题栏
#define RTGUI_WIN_STATUS			(1ul << 2)	//状态栏
#define RTGUI_WIN_MENU			 	(1ul << 3)	//菜单栏
#define RTGUI_WIN_BORDER			(1ul << 4)	//边框
#define RTGUI_WIN_MINBOX			(1ul << 5)	//最小化按钮
#define RTGUI_WIN_MAXBOX			(1ul << 6)	//最大化按钮
#define RTGUI_WIN_CLOSEBOX		 	(1ul << 7)	//关闭按钮
#define RTGUI_WIN_MINBOX_PRESSED	(1ul << 8)
#define RTGUI_WIN_MAXBOX_PRESSED	(1ul << 9)
#define RTGUI_WIN_CLOSEBOX_PRESSED 	(1ul << 10)  //关闭按钮被按下

#define RTGUI_WIN_NOTITLE	(0)
#define RTGUI_WIN_DEFAULT	(RTGUI_WIN_BORDER|RTGUI_WIN_TITLE|RTGUI_WIN_CLOSEBOX)
#define RTGUI_WIN_DIALOG	(RTGUI_WIN_BORDER|RTGUI_WIN_TITLE|RTGUI_WIN_CLOSEBOX|RTGUI_WIN_MINBOX)
#define RTGUI_WIN_NORMAL	(RTGUI_WIN_BORDER|RTGUI_WIN_TITLE|RTGUI_WIN_CLOSEBOX|RTGUI_WIN_MINBOX|RTGUI_WIN_MAXBOX)


struct rtgui_win_title;
struct rtgui_win_area;

struct rtgui_win
{
	/* inherit from top */
	rtgui_container_t 		parent;

	/* window title */
	char* 		title;
	
	/* parent top */
	PVOID		modal_widget;
	rtgui_list_t 		list; /* window list */

	/* the thread id */
	struct rt_thread*	tid;	//所在线程
	
	rt_uint32_t style;			//窗口的样式
	rt_uint32_t status;			//窗口的状态
	rt_uint16_t	title_height;	//标题栏高度
	rt_uint16_t	status_height;	//状态栏高度
	rt_uint16_t	menu_height;	//菜单栏高度
	rt_uint16_t	border_size;	//窗体边框宽度

	/* call back */
	rt_bool_t (*on_activate)(PVOID wdt, rtgui_event_t* event);
	rt_bool_t (*on_deactivate)(PVOID wdt, rtgui_event_t* event);
	rt_bool_t (*on_close)(PVOID wdt, rtgui_event_t* event);

	/* reserved user data */
	void* user_data;
};

rtgui_type_t *rtgui_win_type_get(void);
rtgui_win_t* rtgui_win_create(PVOID parent, const char* title, rtgui_rect_t *rect, rt_uint32_t flag);
void rtgui_win_destroy(rtgui_win_t* win);
rtgui_win_t* rtgui_win_get_win_by_widget(PVOID wdt);
void rtgui_win_close(PVOID wdt, rtgui_event_t *event);
rt_bool_t rtgui_win_ondraw(rtgui_win_t* win);

void rtgui_win_show(rtgui_win_t* win, rt_bool_t modal);
void rtgui_win_hiden(rtgui_win_t* win);
void rtgui_win_end_modal(rtgui_win_t* win);

rt_bool_t rtgui_win_is_activated(rtgui_win_t* win);

void rtgui_win_move(rtgui_win_t* win, int x, int y);

/* reset extent of window */
void rtgui_win_set_rect(rtgui_win_t* win, rtgui_rect_t* rect);
void rtgui_win_set_onactivate(rtgui_win_t* win, rtgui_event_handler_ptr handler);
void rtgui_win_set_ondeactivate(rtgui_win_t* win, rtgui_event_handler_ptr handler);
void rtgui_win_set_onclose(rtgui_win_t* win, rtgui_event_handler_ptr handler);

rt_bool_t rtgui_win_event_handler(PVOID wdt, rtgui_event_t* event);
void rtgui_win_event_loop(rtgui_win_t* win);

void rtgui_win_set_title(rtgui_win_t* win, const char *title);
char* rtgui_win_get_title(rtgui_win_t* win);

rtgui_point_t rtgui_win_get_client_zero(rtgui_win_t *win);
void rtgui_win_get_client_rect(rtgui_win_t *win, rtgui_rect_t *rect);
void rtgui_win_get_title_rect(rtgui_win_t *win, rtgui_rect_t *rect);
void rtgui_win_get_closebox_rect(rtgui_win_t *win, rtgui_rect_t *rect);
void rtgui_win_get_maxbox_rect(rtgui_win_t *win, rtgui_rect_t *rect);
void rtgui_win_get_minbox_rect(rtgui_win_t *win, rtgui_rect_t *rect);

#endif
