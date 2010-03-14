/*
 * 程序清单：radiobox控件演示
 *
 * 这个例子会在创建出的view上添加两个不同方向的radiobox控件
 */

#include "demo_view.h"
#include <rtgui/widgets/radiobox.h>

/* 用于显示垂直方向的radio文本项数组 */
static char* radio_item_v[5] =
	{
		"one",
		"two",
		"three",
		"item 1",
		"item 2"
	};

/* 用于显示水平方向的radio文本项数组 */
static char* radio_item_h[3] =
	{
		"one", "two", "three"
	};

/* 创建用于演示radiobox控件的视图 */
rtgui_view_t* demo_view_radiobox(rtgui_workbench_t* workbench)
{
	rtgui_rect_t rect;
	rtgui_view_t* view;
	rtgui_radiobox_t* radiobox;

	/* 先创建一个演示用的视图 */
	view = demo_view(workbench, "RadioBox View");

	/* 获得视图的位置信息 */
	demo_view_get_rect(view, &rect);
	rect.x1 += 5;
	rect.x2 -= 5;
	rect.y1 += 5;
	rect.y2 = rect.y1 + 5 * 25;

	/* 创建一个垂直方向显示的radiobox控件，文本项是radio_item_v数组，共5个项 */
	radiobox = rtgui_radiobox_create("Radio Box", RTGUI_VERTICAL, radio_item_v, 5);
	/* 设置当前选择的数组是第0项 */
	rtgui_radiobox_set_selection(radiobox, 0);
	/* 添加radiobox控件到视图中 */
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(radiobox));
	/* 设置radiobox控件的位置信息 */
	rtgui_widget_set_rect(RTGUI_WIDGET(radiobox), &rect);

	/* 获得视图的位置信息 */
	demo_view_get_rect(view, &rect);
	rect.x1 += 5;
	rect.x2 -= 5;
	rect.y1 += 5 + 5 * 25;
	rect.y2 = rect.y1 + 60;

	/* 创建一个水平方向显示的radiobox控件，文本项是radio_item_h数组，共3个项 */
	radiobox = rtgui_radiobox_create("Radio Box", RTGUI_HORIZONTAL, radio_item_h, 3);
	/* 设置当前选择的数组是第0项 */
	rtgui_radiobox_set_selection(radiobox, 0);
	/* 添加radiobox控件到视图中 */
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(radiobox));
	/* 设置radiobox控件的位置信息 */
	rtgui_widget_set_rect(RTGUI_WIDGET(radiobox), &rect);

	return view;
}
