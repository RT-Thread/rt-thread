/*
 * 程序清单：texbox控件演示
 *
 * 这个例子会在创建出的view上添加几个不同类型的textbox控件
 */
#include "demo_view.h"
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/textbox.h>

/* 创建用于演示textbox控件的视图 */
rtgui_view_t* demo_view_textbox(rtgui_workbench_t* workbench)
{
	rtgui_rect_t rect, textbox_rect;
	rtgui_view_t* view;
	rtgui_label_t* label;
	rtgui_textbox_t* text;

	/* 先创建一个演示用的视图 */
	view = demo_view(workbench, "TextBox View");

	/* 获得视图的位置信息 */
	demo_view_get_rect(view, &rect);
	rect.x1 += 5;
	rect.x2 = rect.x1 + 30;
	rect.y1 += 5;
	rect.y2 = rect.y1 + 20;
	/* 创建一个label控件 */
	label = rtgui_label_create("名字: ");
	/* 设置label的位置 */
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	/* view是一个container控件，调用add_child方法添加这个label控件 */
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));

	/* 让textbox_rect赋值到rect，以计算textbox控件的位置 */
	textbox_rect = rect;
	textbox_rect.x1 = textbox_rect.x2 + 5;
	textbox_rect.x2 = textbox_rect.x1 + 160;
	/* 创建一个textbox控件 */
	text = rtgui_textbox_create("bernard",RTGUI_TEXTBOX_SINGLE);
	/* 设置textbox控件的位置 */
	rtgui_widget_set_rect(RTGUI_WIDGET(text), &textbox_rect);
	/* 添加textbox控件到视图中 */
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(text));

	/* 计算下一个label控件的位置 */
	rect.y1 += 23;
	rect.y2 = rect.y1 + 20;
	/* 创建一个label控件 */
	label = rtgui_label_create("邮件: ");
	/* 设置label的位置 */
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	/* 添加label控件到视图中 */
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));
	textbox_rect = rect;
	textbox_rect.x1 = textbox_rect.x2 + 5;
	textbox_rect.x2 = textbox_rect.x1 + 160;
	/* 创建一个textbox控件 */
	text = rtgui_textbox_create("bernard.xiong@gmail.com",RTGUI_TEXTBOX_SINGLE);
	/* 设置textbox控件的位置 */
	rtgui_widget_set_rect(RTGUI_WIDGET(text), &textbox_rect);
	/* 添加textbox控件到视图中 */
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(text));

	rect.y1 += 23;
	rect.y2 = rect.y1 + 20;
	/* 创建一个label控件 */
	label = rtgui_label_create("密码: ");
	/* 设置label的位置 */
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	/* 添加label控件到视图中 */
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));
	textbox_rect = rect;
	textbox_rect.x1 = textbox_rect.x2 + 5;
	textbox_rect.x2 = textbox_rect.x1 + 160;
	/* 创建一个textbox控件 */
	text = rtgui_textbox_create("rt-thread",RTGUI_TEXTBOX_SINGLE);
	/* 设置textbox显示文本为掩码形式(即显示为*号，适合于显示密码的情况) */
	text->flag |= RTGUI_TEXTBOX_MASK;
	/* 设置textbox控件的位置 */
	rtgui_widget_set_rect(RTGUI_WIDGET(text), &textbox_rect);
	/* 添加textbox控件到视图中 */
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(text));

	rect.y1 += 23;
	rect.y2 = rect.y1 + 20;
	/* 创建一个label控件 */
	label = rtgui_label_create("主页: ");
	/* 设置label的位置 */
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	/* 添加label控件到视图中 */
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));
	textbox_rect = rect;
	textbox_rect.x1 = textbox_rect.x2 + 5;
	textbox_rect.x2 = textbox_rect.x1 + 160;
	/* 创建一个textbox控件 */
	text = rtgui_textbox_create("http://www.rt-thread.org",RTGUI_TEXTBOX_SINGLE);
	/* 设置textbox控件的位置 */
	rtgui_widget_set_rect(RTGUI_WIDGET(text), &textbox_rect);
	/* 添加textbox控件到视图中 */
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(text));

	return view;
}
