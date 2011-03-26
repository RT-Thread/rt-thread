/*
 * 程序清单：checkbox控件演示
 *
 * 这个例子会在创建出的view上添加几个checkbox控件
 */

#include "demo_view.h"
#include <rtgui/widgets/checkbox.h>

/* 创建用于演示checkbox控件的视图 */
rtgui_view_t* demo_gui_checkbox(rtgui_view_t* parent_view)
{
	rtgui_view_t* view;
	rtgui_checkbox_t* checkbox;
	rtgui_font_t* font;

	/* 先创建一个演示用的视图 */
	view = demo_view_create(parent_view, "CheckBox View");

	/* 创建一个checkbox控件 */
	checkbox = rtgui_checkbox_create(view, "Red", RT_TRUE, 5, 40);
	/* 设置前景色为红色 */
	RTGUI_WIDGET_FOREGROUND(checkbox) = red;

	checkbox = rtgui_checkbox_create(view, "Blue", RT_TRUE, 5, 60);
	RTGUI_WIDGET_FOREGROUND(checkbox) = blue;

	checkbox = rtgui_checkbox_create(view, "12 font", RT_TRUE, 5, 80);
	font = rtgui_font_refer("asc", 12);
	RTGUI_WIDGET_FONT(checkbox) = font;

	checkbox = rtgui_checkbox_create(view, "16 font", RT_TRUE, 5, 100);
	font = rtgui_font_refer("asc", 16);
	RTGUI_WIDGET_FONT(checkbox) = font;

	return view;
}
