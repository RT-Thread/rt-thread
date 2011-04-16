/*
 * 程序清单：窗口演示
 *
 * 这个例子会先创建出一个演示用的view，当点击上面的按钮时会不同的模式创建窗口
 */

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include "demo_view.h"
#include <string.h>

static rtgui_timer_t *timer;
static char label_text[80];
static rt_uint8_t cnt = 5;

/* 获取一个递增的窗口标题 */
static char* get_win_title(void)
{
	static rt_uint8_t win_no = 0;
	static char win_title[16];

	rt_sprintf(win_title, "win %d", ++win_no);
	return win_title;
}

rt_bool_t auto_window_close(PVOID wdt, rtgui_event_t* event)
{
	if(timer != RT_NULL)
	{
		rtgui_timer_stop(timer);
		rtgui_timer_destory(timer);
	}
	return RT_TRUE;
}

/* 关闭对话框时的回调函数 */
void diag_close(struct rtgui_timer* timer, void* parameter)
{
	rtgui_label_t *label;

	label = (rtgui_label_t*)parameter;
	cnt --;
	rt_sprintf(label_text, "closed then %d s", cnt);

	/* 设置标签文本并更新控件 */
	rtgui_label_set_text(label, label_text);
	rtgui_widget_update(RTGUI_WIDGET(label));

	if (cnt == 0)
	{
		rtgui_win_t *win;
		win = rtgui_win_get_win_by_widget(label);
		if(win == RT_NULL) return;
		/* 超时，关闭对话框 */
		rtgui_win_close(win, RT_NULL);

		/* 停止并删除定时器 */
		rtgui_timer_stop(timer);
		rtgui_timer_destory(timer);
	}
}

static rt_uint16_t delta_x = 20;
static rt_uint16_t delta_y = 40;

/* 触发正常窗口显示 */
static void demo_win_onbutton(PVOID wdt, rtgui_event_t* event)
{
	rtgui_win_t *win;
	PVOID parent;
	rtgui_rect_t rect={0, 0, 180, 120};

	parent = rtgui_widget_get_toplevel(wdt);
	rtgui_rect_moveto(&rect, delta_x, delta_y);
	delta_x += 20;
	delta_y += 20;

	/* 创建一个窗口 */
	win = rtgui_win_create(parent, get_win_title(), &rect, RTGUI_WIN_DEFAULT);

	/* 添加一个文本标签 */
	rtgui_label_create(win, "这是一个普通窗口", 10, 30, 150, 20);

	/* 非模态显示窗口 */
	rtgui_win_show(win, RT_FALSE);
}

/* 触发自动窗口显示 */
static void demo_autowin_onbutton(PVOID wdt, rtgui_event_t* event)
{
	PVOID parent;
	rtgui_label_t *label = RT_NULL;
	rtgui_win_t *msgbox;
	struct rtgui_rect rect ={50, 50, 200, 200};

	parent = rtgui_widget_get_toplevel(wdt);
	msgbox = rtgui_win_create(parent, "Information", &rect, RTGUI_WIN_DEFAULT);
	if (msgbox != RT_NULL)
	{
		cnt = 5;
		rt_sprintf(label_text, "closed then %d s", cnt);
		label = rtgui_label_create(msgbox, label_text, 10,30,120,20);
		/* 设置关闭窗口时的动作 */
		rtgui_win_set_onclose(msgbox, auto_window_close);

		rtgui_win_show(msgbox, RT_FALSE);
	}

	/* 创建一个定时器 */
	timer = rtgui_timer_create(100, RT_TIMER_FLAG_PERIODIC, diag_close, label);
	rtgui_timer_start(timer);
}

/* 触发模态窗口显示 */
static void demo_modalwin_onbutton(PVOID wdt, rtgui_event_t* event)
{
	rtgui_win_t *win;
	PVOID parent;
	rtgui_rect_t rect = {0, 0, 180, 120};

	parent = rtgui_widget_get_toplevel(wdt);
	rtgui_rect_moveto(&rect, (rtgui_widget_get_width(parent) -180)/2, 
							 (rtgui_widget_get_height(parent)-120)/2);

	/* 创建一个窗口 */
	win = rtgui_win_create(parent,get_win_title(), &rect, RTGUI_WIN_DEFAULT);

	rect.x1 += 20;
	rect.x2 -= 5;
	rect.y1 += 5;
	rect.y2 = rect.y1 + 20;

	rtgui_label_create(win, "这是一个模式窗口", 20, 30, 150,20);

	/* 模态显示窗口 */
	rtgui_win_show(win, RT_TRUE);
}

/* 触发无标题窗口显示 */
static void demo_ntitlewin_onbutton(PVOID wdt, rtgui_event_t* event)
{
	rtgui_win_t *win;
	rtgui_label_t *label;
	rtgui_button_t *button;
	PVOID parent;
	rtgui_rect_t rect = {0, 0, 180, 120};

	parent = rtgui_widget_get_toplevel(wdt);
	rtgui_rect_moveto(&rect, delta_x, delta_y);
	delta_x += 20;
	delta_y += 20;
	/* 创建一个窗口，风格为无标题及无边框 */
	win = rtgui_win_create(parent,"no title", &rect, RTGUI_WIN_DEFAULT);
	RTGUI_WIDGET_BACKGROUND(win) = white;
	win->level = RTGUI_WIN_LEVEL_EXPERT;
	/* 创建一个文本标签 */
	label = rtgui_label_create(win, "无标题栏窗口", 10, 30, 100, 20);
	RTGUI_WIDGET_BACKGROUND(label) = white;

	button = rtgui_button_create(win,"关闭", 65, 85, 60, 25);
	rtgui_button_set_onbutton(button, rtgui_win_close);

	/* 非模态显示窗口 */
	rtgui_win_show(win, RT_FALSE);
}

rtgui_view_t* demo_gui_window(rtgui_view_t* parent_view)
{
	rtgui_view_t* view;
	rtgui_button_t *button;

	/* 创建一个演示用的视图 */
	view = demo_view_create(parent_view, "Window Demo");


	button = rtgui_button_create(view, "Normal Win", 10, 40, 100, 25);
	rtgui_button_set_onbutton(button, demo_win_onbutton);

	button = rtgui_button_create(view, "Auto Win", 10, 70, 100, 25);
	rtgui_button_set_onbutton(button, demo_autowin_onbutton);

	button = rtgui_button_create(view, "Modal Win", 10, 100, 100, 25);
	rtgui_button_set_onbutton(button, demo_modalwin_onbutton);

	button = rtgui_button_create(view, "NoTitle Win", 10, 130, 100, 25);
	rtgui_button_set_onbutton(button, demo_ntitlewin_onbutton);

	return view;
}
