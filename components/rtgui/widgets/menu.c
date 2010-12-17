#include <rtgui/dc.h>
#include <rtgui/widgets/box.h>
#include <rtgui/widgets/menu.h>
#include <rtgui/widgets/window.h>

#define RTGUI_MENU_IMAGE_MAGIN		18
#define RTGUI_MENU_SUBMENU_MAGIN	16

static void rtgui_menu_item_unselect(struct rtgui_menu_item* item);
static rt_bool_t rtgui_menu_on_deactivate(rtgui_widget_t* widget, rtgui_event_t* event);

static void _rtgui_menu_constructor(rtgui_menu_t *menu)
{
	/* set window style */
	RTGUI_WIN(menu)->style = RTGUI_WIN_STYLE_NO_TITLE;

	/* set deactivate handler */
	rtgui_win_set_ondeactivate(RTGUI_WIN(menu), rtgui_menu_on_deactivate);

	/* set proper of control */
	menu->parent_menu = RT_NULL;
	menu->items = RT_NULL;
	menu->items_count = 0; 
	menu->current_item = 0;
	menu->items_list = RT_NULL;

	menu->on_menupop  = RT_NULL;
	menu->on_menuhide = RT_NULL;
}

static void _rtgui_menu_destructor(rtgui_menu_t* menu)
{
}

static void _rtgui_menu_item_ondraw(struct rtgui_listctrl *list, struct rtgui_dc* dc, rtgui_rect_t* rect, rt_uint16_t index)
{
	struct rtgui_menu_item* item;

	/* get menu item */
	item = (rtgui_menu_item_t*)list->items;
	item = &item[index];

	if (item->type == RTGUI_ITEM_SUBMENU)
	{
		rtgui_dc_draw_text(dc, item->label, &rect);
		rtgui_dc_draw_byte(dc, left_arraw, &rect);
	}
	else if (item->type == RTGUI_ITEM_SEPARATOR)
	{
		rtgui_dc_draw_vline(dc, &rect);
	}
	else if (item->type == RTGUI_ITEM_CHECK)
	{
		/* not support right now */
	}
	else
	{
		/* normal menu item */	
		rtgui_dc_draw_text(dc, item->label, &rect);
		if (item->image != RT_NULL)
			rtgui_image_blit(item->image, dc, &rect);
	}
}

static void _rtgui_menu_item_onmouse()
{
}

rtgui_type_t *rtgui_menu_type_get(void)
{
	static rtgui_type_t *menu_type = RT_NULL;

	if (!menu_type)
	{
		menu_type = rtgui_type_create("menu", RTGUI_WIN_TYPE,
			sizeof(rtgui_menu_t), 
			RTGUI_CONSTRUCTOR(_rtgui_menu_constructor), 
			RTGUI_DESTRUCTOR (_rtgui_menu_destructor));
	}

	return menu_type;
}

static rt_bool_t rtgui_menu_on_deactivate(rtgui_widget_t* widget, rtgui_event_t* event)
{
	rtgui_menu_t* menu = (rtgui_menu_t*) widget;

	/* submenu is activate */
	if (menu->items[menu->current_item].type == RTGUI_ITEM_SUBMEN)
	{
		/* if sub menu activated, not hide menu */
		if (menu->select_item->sub_menu != RT_NULL &&
			rtgui_win_is_activated(RTGUI_WIN(menu->select_item->sub_menu)))
		{
			return RT_TRUE;
		}
	}

	rtgui_win_hiden(RTGUI_WIN(menu));
	if (menu->on_menuhide != RT_NULL)
	{
		menu->on_menuhide(RTGUI_WIDGET(menu), RT_NULL);
	}

	/* if it's a submenu, try to hide parent menu */
	if (menu->parent_menu != RT_NULL &&
		!rtgui_win_is_activated(RTGUI_WIN(menu->parent_menu)))
	{
		rtgui_menu_on_deactivate(RTGUI_WIDGET(menu->parent_item->parent_menu), event);
	}

	return RT_TRUE;
}

struct rtgui_menu* rtgui_menu_create(const char* title, struct rtgui_menu* parent_menu, 
	const struct rtgui_menu_item* items, rt_uint16_t count)
{
	rtgui_rect_t rect = {0, 0, 100, 100};
    struct rtgui_menu* menu;

    menu = (struct rtgui_menu*) rtgui_widget_create ( RTGUI_MENU_TYPE );
	if (menu != RT_NULL)
	{
		rtgui_win_set_title(RTGUI_WIN(menu), title);
		menu->parent_menu = parent_menu;
		menu->items = items;
		menu->items_count = count;

		rtgui_widget_set_rect(RTGUI_WIDGET(menu), &rect);
		rtgui_rect_inflate(&rect, -1);
		/* create menu item list */
		menu->items_list = rtgui_listctrl_create(items, count, &rect, _rtgui_menu_item_ondraw); 
	}

	return menu;
}

void rtgui_menu_destroy(struct rtgui_menu* menu)
{
	rtgui_widget_destroy (RTGUI_WIDGET(menu));
}

void rtgui_menu_set_onmenupop(struct rtgui_menu* menu, rtgui_event_handler_ptr handler)
{
	if (menu == RT_NULL) return;

	menu->on_menupop = handler;
}

void rtgui_menu_set_onmenuhide(struct rtgui_menu* menu, rtgui_event_handler_ptr handler)
{
	if (menu == RT_NULL) return;

	menu->on_menuhide = handler;
}

void rtgui_menu_pop(struct rtgui_menu* menu, int x, int y)
{
	rtgui_rect_t rect;
	rtgui_box_t* box;

	if (menu == RT_NULL) return;

	/* set window extent */
	rect.x1 = x;
	rect.y1 = y;
	rect.x2 = x + menu->width;
	rect.y2 = y + menu->height;
	rtgui_win_set_rect(RTGUI_WIN(menu), &rect);

	/* on menu pop handler */
	if (menu->on_menupop != RT_NULL)
	{
		menu->on_menupop(RTGUI_WIDGET(menu), RT_NULL);
	}

	/* show menu window */
	rtgui_win_show(RTGUI_WIN(menu), RT_FALSE);
}

