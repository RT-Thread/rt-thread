/*
 * 程序清单：button控件演示
 *
 * 这个例子会在创建出的view上添加几个不同类型的button控件
 */

#include "demo_view.h"
#include <rtgui/widgets/button.h>

/* 创建用于演示button控件的视图 */
rtgui_view_t* demo_gui_button(rtgui_view_t* parent_view)
{
	rtgui_view_t* view;
	rtgui_button_t* button;
	rtgui_font_t* font;

	/* 先创建一个演示用的视图 */
	view = demo_view_create(parent_view, "Button View");

	/* 创建一个button控件 */
	button = rtgui_button_create(view, "Red", 5, 40, 100, 25);
	/* 设置label控件的前景色为红色 */
	RTGUI_WIDGET_FOREGROUND(button) = red;

	button = rtgui_button_create(view, "Blue", 5, 70, 100, 25);
	RTGUI_WIDGET_FOREGROUND(button) = blue;
	
	button = rtgui_button_create(view, "12 font", 5, 100, 100, 25);
	/* 设置字体为12点阵的asc字体 */
	font = rtgui_font_refer("asc", 12);
	RTGUI_WIDGET_FONT(button) = font;
	
	button = rtgui_button_create(view, "16 font", 5, 130, 100, 25);
	/* 设置字体为16点阵的asc字体 */
	font = rtgui_font_refer("asc", 16);
	RTGUI_WIDGET_FONT(button) = font;


	return view;
}
