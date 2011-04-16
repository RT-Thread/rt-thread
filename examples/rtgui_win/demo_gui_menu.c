/*
 * 程序清单：menu控件演示
 *
 * 这个例子会在创建出的view上添加几个不同类型的label控件
 */
#include "demo_view.h"
#include <rtgui/widgets/menu.h>
#include <rtgui/widgets/button.h>

/* 创建用于演示menu控件的视图 */
rtgui_view_t* demo_gui_menu(rtgui_view_t* parent_view)
{
	rtgui_view_t *view;
	rtgui_menu_t *main_menu, *sub_menu, *toolmenu;

	/* 先创建一个演示用的视图 */
	view = demo_view_create(parent_view, "MENU View");

	/* 1.使用动态方式创建菜单 */
	main_menu = rtgui_menu_create(view, "menu", 5, 40, RTGUI_MENU_NORMAL);
		sub_menu = rtgui_menu_create(view, "File", 0, 0, RTGUI_MENU_POPUP);
		rtgui_menu_append(sub_menu, 0, 0x20001, "New", RT_NULL);
		rtgui_menu_append(sub_menu, 0, 0x20002, "Open", RT_NULL);
		rtgui_menu_append(sub_menu, 0, 0x20003, "Save", RT_NULL);
		rtgui_menu_append(sub_menu, 0, 0x20004, "Print", RT_NULL);
		rtgui_menu_append(sub_menu, 0, 0x20005, "Exit", RT_NULL);
	rtgui_menu_append(main_menu, RTGUI_MENU_POPUP, (rt_uint32_t)sub_menu, sub_menu->name, RT_NULL);
		sub_menu = rtgui_menu_create(view, "EditDocument", 0, 0, RTGUI_MENU_POPUP);
		rtgui_menu_append(sub_menu, 0, 0x30001, "Cut", RT_NULL);
		rtgui_menu_append(sub_menu, 0, 0x30002, "Copy", RT_NULL);
		rtgui_menu_append(sub_menu, 0, 0x30002, "Paste", RT_NULL);
		rtgui_menu_append(sub_menu, 0, 0x30003, "Find...", RT_NULL);
			toolmenu = rtgui_menu_create(view, "Toolbars", 0, 0, RTGUI_MENU_POPUP);
			rtgui_menu_append(toolmenu, 0, 0x50001, "File Tools", RT_NULL);
			rtgui_menu_append(toolmenu, 0, 0x50002, "build Tools", RT_NULL);
		rtgui_menu_append(sub_menu, RTGUI_MENU_POPUP, (rt_uint32_t)toolmenu, toolmenu->name, RT_NULL);
	rtgui_menu_append(main_menu, RTGUI_MENU_POPUP, (rt_uint32_t)sub_menu, sub_menu->name, RT_NULL);
		sub_menu = rtgui_menu_create(view, "View", 0, 0, RTGUI_MENU_POPUP);
		rtgui_menu_append(sub_menu, 0, 0x40001, "Status bar", RT_NULL);
		rtgui_menu_append(sub_menu, 0, 0x40001, "Tool bar", RT_NULL);
		rtgui_menu_append(sub_menu, 0, 0x40001, "Project window", RT_NULL);
		rtgui_menu_append(sub_menu, 0, 0x40001, "Books window", RT_NULL);
		rtgui_menu_append(sub_menu, 0, 0x40001, "Functions window", RT_NULL);
		rtgui_menu_append(sub_menu, 0, 0x40001, "Full screen", RT_NULL);
	rtgui_menu_append(main_menu, RTGUI_MENU_POPUP, (rt_uint32_t)sub_menu, sub_menu->name, RT_NULL);
	rtgui_menu_append(main_menu, 0, 0x10004, "Help", RT_NULL);

	/* 2.使用静态方式创建菜单 */
	/* 菜单的一些功能还在调试中... */
	return view;
}
