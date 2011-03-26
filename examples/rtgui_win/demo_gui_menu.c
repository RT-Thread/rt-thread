/*
 * 程序清单：menu控件演示
 *
 * 这个例子会在创建出的view上添加几个不同类型的label控件
 */
#include "demo_view.h"
#include <rtgui/widgets/menu.h>
#include <rtgui/widgets/button.h>

static rt_bool_t _onmenuitem(struct rtgui_widget *widget, struct rtgui_event* event)
{
	rt_kprintf("menu action!!\n");
	return RT_TRUE;
}

static const rtgui_menu_item_t sub_items[] = 
{
	{RTGUI_ITEM_NORMAL, "item #1", RT_NULL, RT_NULL, 0, _onmenuitem},
	{RTGUI_ITEM_NORMAL, "item #2", RT_NULL, RT_NULL, 0, RT_NULL},
	{RTGUI_ITEM_SEPARATOR, RT_NULL, RT_NULL, RT_NULL, 0, RT_NULL},
	{RTGUI_ITEM_NORMAL, "item #3", RT_NULL, RT_NULL, 0, RT_NULL},
};
static const rtgui_menu_item_t items[] = 
{
	{RTGUI_ITEM_NORMAL, "item #1", RT_NULL, RT_NULL, 0, RT_NULL},
	{RTGUI_ITEM_NORMAL, "item #2", RT_NULL, RT_NULL, 0, RT_NULL},
	{RTGUI_ITEM_SEPARATOR, RT_NULL, RT_NULL, RT_NULL, 0, RT_NULL},
	{RTGUI_ITEM_SUBMENU, "item #3", RT_NULL, (struct rtgui_menu_item_t *)sub_items, sizeof(sub_items)/sizeof(sub_items[0]), RT_NULL},
};
static rtgui_menu_t* menu;

static _onmenu(PVOID wdt, rtgui_event_t* event)
{
	rtgui_rect_t rect;

	rtgui_widget_get_rect(widget, &rect);
	rtgui_widget_rect_to_device(widget, &rect);

	if (menu != RT_NULL)
		rtgui_menu_pop(menu, rect.x1, rect.y2 + 5);
}

/* 创建用于演示menu控件的视图 */
rtgui_view_t* demo_gui_menu(rtgui_view_t* parent_view)
{
	rtgui_rect_t rect;
	rtgui_view_t* view;
	rtgui_button_t* button;

	/* 先创建一个演示用的视图 */
	view = demo_view_create(parent_view, "MENU View");

	button = rtgui_button_create(view, "Pop Menu", 5, 40, 50, 22);
	rtgui_button_set_onbutton(button, _onmenu);

	menu = rtgui_menu_create("Menu Test", RT_NULL, items, sizeof(items)/sizeof(items[0]));

	return view;
}
