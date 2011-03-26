/*
 * 程序清单：label控件演示
 *
 * 这个例子会在创建出的view上添加几个不同类型的label控件
 */
#include "demo_view.h"
#include <rtgui/widgets/label.h>

/* 创建用于演示label控件的视图 */
rtgui_view_t* demo_gui_label(rtgui_view_t* parent_view)
{
	rtgui_view_t* view;
	rtgui_label_t* label;
	rtgui_font_t* font;

	/* 先创建一个演示用的视图 */
	view = demo_view_create(parent_view, "Label View");

	/* 创建一个label控件 */
	label = rtgui_label_create(view, "Red Left", 10, 40, 200, 20);
	/* 设置label控件上的文本对齐方式为：左对齐 */
	RTGUI_WIDGET_TEXTALIGN(label) = RTGUI_ALIGN_LEFT|RTGUI_ALIGN_CENTER_VERTICAL;
	/* 设置label控件的前景色为红色 */
	RTGUI_WIDGET_FOREGROUND(label) = red;
	RTGUI_WIDGET_BACKGROUND(label) = white;
	

	label = rtgui_label_create(view, "Blue Right", 10, 65, 200, 20);
	RTGUI_WIDGET_TEXTALIGN(label) = RTGUI_ALIGN_RIGHT|RTGUI_ALIGN_CENTER_VERTICAL;
	RTGUI_WIDGET_FOREGROUND(label) = blue;
	RTGUI_WIDGET_BACKGROUND(label) = white;
	
	label = rtgui_label_create(view, "Green Center", 10, 90, 200, 20);
	RTGUI_WIDGET_TEXTALIGN(label) = RTGUI_ALIGN_CENTER_HORIZONTAL|RTGUI_ALIGN_CENTER_VERTICAL;
	RTGUI_WIDGET_FOREGROUND(label) = green;
	RTGUI_WIDGET_BACKGROUND(label) = white;
	
	label = rtgui_label_create(view, "12 font",10, 115, 200, 20);
	/* 设置字体为12点阵的asc字体 */
	font = rtgui_font_refer("asc", 12);
	RTGUI_WIDGET_FONT(label) = font;
	RTGUI_WIDGET_BACKGROUND(label) = white;

	label = rtgui_label_create(view, "16 font", 10, 140, 200, 20);
	font = rtgui_font_refer("asc", 16);
	RTGUI_WIDGET_FONT(RTGUI_WIDGET(label)) = font;
	RTGUI_WIDGET_BACKGROUND(label) = white;

	return view;
}

