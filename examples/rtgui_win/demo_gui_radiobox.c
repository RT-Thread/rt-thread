/*
 * 程序清单：radiobox控件演示
 *
 * 这个例子会在创建出的view上添加两个不同方向的radiobox控件
 */

#include "demo_view.h"
#include <rtgui/widgets/radiobox.h>

static rt_uint32_t bind_var;

/* 创建用于演示radiobox控件的视图 */
rtgui_view_t* demo_gui_radiobox(rtgui_view_t* parent_view)
{
	rtgui_view_t* view;
	rtgui_radiobox_t *rbox;
	rtgui_rb_group_t *group,*_group;

	/* 先创建一个演示用的视图 */
	view = demo_view_create(parent_view, "RadioBox View");

	/* 使用方法一 */
	/* 可以先创建一个组对象，再使用 */
	group = rtgui_radiobox_create_group();
	rtgui_radiobox_create(view, "radio1", 5, 40, 100, 20, group);
	rtgui_radiobox_create(view, "radio2", 5, 60, 100, 20, group);
	
	/* 使用方法二 */
	rbox = rtgui_radiobox_create(view, "radio-x", 5, 90, 100, 20, RT_NULL);
	/* 也可以从radiobox控件中获得一个组对象 */
	group = rtgui_radiobox_get_group(rbox);

	_group = rtgui_radiobox_create_group();
	rtgui_radiobox_create(view, "radio_m", 20,110, 100, 20, _group);
	rtgui_radiobox_create(view, "radio_n", 20,130, 100, 20, _group); 
	/* 设定一个初始值 */
	rtgui_rb_group_set_sel(_group, 1);
	rtgui_radiobox_create(view, "radio-y", 5, 150, 100, 20, group);

	/* 可以为组绑定一个变量,之后可以使用该变量获得group的当前焦点 */
	rtgui_rb_group_bind(group, &bind_var);

	return view;
}
