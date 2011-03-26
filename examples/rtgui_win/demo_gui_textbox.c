/*
 * 程序清单：texbox控件演示
 *
 * 这个例子会在创建出的view上添加几个不同类型的textbox控件
 */
#include "demo_view.h"
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/textbox.h>

/* 创建用于演示textbox控件的视图 */
rtgui_view_t* demo_gui_textbox(rtgui_view_t* parent_view)
{
	rtgui_view_t* view;
	
	/* 先创建一个演示用的视图 */
	view = demo_view_create(parent_view, "TextBox View");

	rtgui_label_create(view, "名字: ", 5, 40, 50, 20);
	rtgui_textbox_create(view, "bernard",5, 60, 200, 20, RTGUI_TEXTBOX_NONE);

	rtgui_label_create(view, "邮件: ", 5, 80, 50, 20);
	rtgui_textbox_create(view, "bernard.xiong@gmail.com", 5, 100, 200, 20, RTGUI_TEXTBOX_NONE);

	rtgui_label_create(view, "密码: ", 5, 120, 50, 20);
	rtgui_textbox_create(view, "rt-thread", 5, 140, 200, 20, RTGUI_TEXTBOX_MASK);

	rtgui_label_create(view, "主页: ", 5, 160, 50, 20);
	rtgui_textbox_create(view, "http://www.rt-thread.org", 5, 180, 200, 20, RTGUI_TEXTBOX_NONE);

	return view;
}
