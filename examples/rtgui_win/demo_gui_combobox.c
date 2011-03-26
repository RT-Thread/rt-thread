/*
 * 程序清单：label控件演示
 *
 * 这个例子会在创建出的view上添加几个不同类型的label控件
 */
#include "demo_view.h"
#include <rtgui/widgets/combobox.h>

rtgui_listbox_item_t items[] = 
{
	{"item 1", RT_NULL},
	{"item 2", RT_NULL},
	{"item 3", RT_NULL},
};

/* 创建用于演示combobox控件的视图 */
rtgui_view_t* demo_gui_combobox(rtgui_view_t* parent_view)
{
	rtgui_view_t* view;
	rtgui_combo_t* box;

	/* 先创建一个演示用的视图 */
	view = demo_view_create(parent_view, "ComboBox View");

	box = rtgui_combo_create(view, "demo combo", 5, 40, 120, 20);
	rtgui_combo_set_items(box, items, RT_COUNT(items));
	box->add_string(box, "add item 1");
	box->add_string(box, "add item 2");

	return view;
}
