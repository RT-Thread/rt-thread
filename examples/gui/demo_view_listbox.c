/*
 * 程序清单：label控件演示
 *
 * 这个例子会在创建出的view上添加几个不同类型的label控件
 */
#include "demo_view.h"
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/listbox.h>

const static struct rtgui_listbox_item items[] = 
{
	{"list #0", RT_NULL},
	{"list #1", RT_NULL},
	{"list #2", RT_NULL},
	{"list #3", RT_NULL},
};

static void on_items(rtgui_widget_t* widget, struct rtgui_event* event)
{
	rtgui_listbox_t* box;
	/* get listbox */
	box = RTGUI_LISTBOX(widget);

	/* 打印当前的项 */
	rt_kprintf("current item: %d\n", box->current_item);
}

/* 创建用于演示label控件的视图 */
rtgui_view_t* demo_view_listbox(rtgui_workbench_t* workbench)
{
	rtgui_rect_t rect;
	rtgui_view_t* view;
	rtgui_label_t* label;
	rtgui_listbox_t* box;

	/* 先创建一个演示用的视图 */
	view = demo_view(workbench, "ListBox Demo");

	/* 获得视图的位置信息 */
	demo_view_get_rect(view, &rect);
	rect.x1 += 5;
	rect.x2 -= 5;
	rect.y1 += 5;
	rect.y2 = rect.y1 + 20;
	/* 创建一个label控件 */
	label = rtgui_label_create("listbox: ");
	/* 设置label的位置 */
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	/* view是一个container控件，调用add_child方法添加这个label控件 */
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));

	rect.y1 = rect.y2 + 3;
	rect.y2 = 250;
	box = rtgui_listbox_create(items, sizeof(items)/sizeof(struct rtgui_listbox_item), &rect);
	rtgui_listbox_set_onitem(box, on_items);
	/* view是一个container控件，调用add_child方法添加这个listbox控件 */
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(box));

	return view;
}
