/*
 * 程序清单：button控件演示
 *
 * 这个例子会在创建出的view上添加几个不同类型的button控件
 */

#include "demo_view.h"
#include <rtgui/widgets/button.h>

/* 创建用于演示button控件的视图 */
rtgui_view_t* demo_view_button(rtgui_workbench_t* workbench)
{
	rtgui_rect_t rect;
	rtgui_view_t* view;
	rtgui_button_t* button;
	rtgui_font_t* font;

	/* 先创建一个演示用的视图 */
	view = demo_view(workbench, "Button View");

	/* 获得视图的位置信息 */
	demo_view_get_rect(view, &rect);
	rect.x1 += 5;
	rect.x2 = rect.x1 + 100;
	rect.y1 += 5;
	rect.y2 = rect.y1 + 20;
	/* 创建一个button控件 */
	button = rtgui_button_create("Red");
	/* 设置label控件的前景色为红色 */
	RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(button)) = red;
	/* 设置button的位置 */
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	/* view是一个container控件，调用add_child方法添加这个button控件 */
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(button));

	/* 获得视图的位置信息 */
	demo_view_get_rect(view, &rect);
	rect.x1 += 5;
	rect.x2 = rect.x1 + 100;
	rect.y1 += 5 + 25;
	rect.y2 = rect.y1 + 20;
	/* 创建一个button控件 */
	button = rtgui_button_create("Blue");
	/* 设置label控件的前景色为蓝色 */
	RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(button)) = blue;
	/* 设置button的位置 */
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	/* view是一个container控件，调用add_child方法添加这个button控件 */
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(button));

	/* 获得视图的位置信息 */
	demo_view_get_rect(view, &rect);
	rect.x1 += 5;
	rect.x2 = rect.x1 + 100;
	rect.y1 += 5 + 25 + 25;
	rect.y2 = rect.y1 + 20;
	/* 创建一个button控件 */
	button = rtgui_button_create("12 font");
	/* 设置字体为12点阵的asc字体 */
	font = rtgui_font_refer("asc", 12);
	RTGUI_WIDGET_FONT(RTGUI_WIDGET(button)) = font;
	/* 设置button的位置 */
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	/* view是一个container控件，调用add_child方法添加这个button控件 */
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(button));

	/* 获得视图的位置信息 */
	demo_view_get_rect(view, &rect);
	rect.x1 += 5;
	rect.x2 = rect.x1 + 100;
	rect.y1 += 5 + 25 + 25 + 25;
	rect.y2 = rect.y1 + 20;
	/* 创建一个button控件 */
	button = rtgui_button_create("16 font");
	/* 设置字体为16点阵的asc字体 */
	font = rtgui_font_refer("asc", 16);
	RTGUI_WIDGET_FONT(RTGUI_WIDGET(button)) = font;
	/* 设置button的位置 */
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	/* view是一个container控件，调用add_child方法添加这个button控件 */
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(button));

	return view;
}
