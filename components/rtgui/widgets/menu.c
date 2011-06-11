#include <rtgui/dc.h>
#include <rtgui/widgets/menu.h>
#include <rtgui/rtgui_theme.h>

static rt_bool_t rtgui_menu_on_deactivate(rtgui_widget_t* widget, rtgui_event_t* event);
const static rt_uint8_t right_arrow[] = {0x80, 0xc0, 0xe0, 0xf0, 0xe0, 0xc0, 0x80};

static void _rtgui_menu_constructor(rtgui_menu_t *menu)
{
	/* set window style */
	RTGUI_WIN(menu)->style = RTGUI_WIN_STYLE_NO_TITLE;

	/* set deactivate handler */
	rtgui_win_set_ondeactivate(RTGUI_WIN(menu), rtgui_menu_on_deactivate);

	/* set proper of control */
	menu->parent_menu = RT_NULL;
	menu->sub_menu = RT_NULL;

	menu->items = RT_NULL;
	menu->items_count = 0; 
	menu->items_list = RT_NULL;

	menu->on_menupop  = RT_NULL;
	menu->on_menuhide = RT_NULL;
}

static void _rtgui_menu_destructor(rtgui_menu_t* menu)
{
	if (menu->sub_menu != RT_NULL)
	{
		rtgui_menu_destroy(menu->sub_menu);
		menu->sub_menu = RT_NULL;
	}

	rtgui_listctrl_destroy(menu->items_list);
	menu->items_list = RT_NULL;
}

static void _rtgui_menu_onitem(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_menu* menu;

	/* get menu */
	menu = RTGUI_MENU(rtgui_widget_get_toplevel(widget));
	if (menu->items[menu->items_list->current_item].type == RTGUI_ITEM_SUBMENU)
	{
		const rtgui_menu_item_t* items;
		rt_uint16_t count;
		rtgui_rect_t item_rect;

		items = (rtgui_menu_item_t*)menu->items[menu->items_list->current_item].submenu;
		count = menu->items[menu->items_list->current_item].submenu_count;
		if (menu->sub_menu != RT_NULL)
		{
			if (menu->sub_menu->items == items)
			{
				if (!RTGUI_WIDGET_IS_HIDE(RTGUI_WIDGET(menu->sub_menu)))
				{
					/* hide this sub menu */
					rtgui_win_hiden(RTGUI_WIN(menu->sub_menu));
					return;
				}

				/* show this sub menu */
				rtgui_listctrl_get_item_rect(menu->items_list, menu->items_list->current_item, &item_rect);
				rtgui_menu_pop(menu->sub_menu, item_rect.x2, item_rect.y1);
				return;
			}

			/* delete sub menu */
			rtgui_menu_destroy(menu->sub_menu);
			menu->sub_menu = RT_NULL;
		}

		/* create sub menu */
		menu->sub_menu = rtgui_menu_create("submenu", menu, items, count);

		rtgui_listctrl_get_item_rect(menu->items_list, menu->items_list->current_item, &item_rect);
		rtgui_menu_pop(menu->sub_menu, item_rect.x2 + 5, item_rect.y1);
	}
	else /* other menu item */
	{
		/* invoke action */
		if (menu->items[menu->items_list->current_item].on_menuaction != RT_NULL)
			menu->items[menu->items_list->current_item].on_menuaction(RTGUI_WIDGET(menu), RT_NULL);

		/* hide sub-menu */
		if (menu->sub_menu != RT_NULL)
		{
			rtgui_menu_hiden(menu->sub_menu);
		}
		rtgui_menu_hiden(menu);
	}
}

static void _rtgui_menu_item_ondraw(struct rtgui_listctrl *list, struct rtgui_dc* dc, rtgui_rect_t* rect, rt_uint16_t index)
{
	rtgui_rect_t item_rect;
	struct rtgui_menu_item* item;

	item_rect = *rect;
	item_rect.x1 += 5;

	/* re-fill item */
	if (list->current_item == index)
	{
		rtgui_color_t bc;

		bc = RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(list));
		RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(list)) = blue;
		rtgui_dc_fill_rect(dc, rect);
		RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(list)) = bc;
	}

	/* get menu item */
	item = (rtgui_menu_item_t*)list->items;
	item = &item[index];

	if (item->type == RTGUI_ITEM_SUBMENU)
	{
		rtgui_rect_t r = {0, 0, 8, 8};
		rtgui_dc_draw_text(dc, item->label, &item_rect);
		item_rect.x1 = item_rect.x2 - 16; item_rect.x2 -= 8;
		rtgui_rect_moveto_align(&item_rect, &r, RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL);
		rtgui_dc_draw_byte(dc, r.x1, r.y1, 8, right_arrow);
	}
	else if (item->type == RTGUI_ITEM_SEPARATOR)
	{
		rtgui_dc_draw_horizontal_line(dc, item_rect.x1, item_rect.x2, (item_rect.y2 + item_rect.y1)/2);
	}
	else if (item->type == RTGUI_ITEM_CHECK)
	{
		/* not support right now */
	}
	else
	{
		/* normal menu item */	
		rtgui_dc_draw_text(dc, item->label, &item_rect);
		if (item->image != RT_NULL)
			rtgui_image_blit(item->image, dc, &item_rect);
	}
}

DEFINE_CLASS_TYPE(menu, "menu", 
	RTGUI_WIN_TYPE,
	_rtgui_menu_constructor,
	_rtgui_menu_destructor,
	sizeof(struct rtgui_menu));

static rt_bool_t rtgui_menu_on_deactivate(rtgui_widget_t* widget, rtgui_event_t* event)
{
	rtgui_menu_t* menu = (rtgui_menu_t*) widget;

	if (menu->parent_menu != RT_NULL)
	{
		/* whether click on parent menu */
		if (rtgui_win_is_activated(RTGUI_WIN(menu->parent_menu)) == RT_TRUE &&
			menu->parent_menu->items[menu->parent_menu->items_list->current_item].submenu == (struct rtgui_menu_item_t *)menu->items)
			return RT_TRUE;
	}

	/* submenu is activate */
	if (menu->items[menu->items_list->current_item].type == RTGUI_ITEM_SUBMENU)
	{
		/* if sub menu activated, not hide menu */
		if (menu->sub_menu != RT_NULL && 
			rtgui_win_is_activated(RTGUI_WIN(menu->sub_menu)) == RT_TRUE)
			return RT_TRUE;
	}

	rtgui_win_hiden(RTGUI_WIN(menu));
	if (menu->on_menuhide != RT_NULL)
	{
		menu->on_menuhide(RTGUI_WIDGET(menu), RT_NULL);
	}

	/* un-select item */
	menu->items_list->current_item = -1;

	/* if it's a submenu, try to hide parent menu */
	if (menu->parent_menu != RT_NULL &&
		rtgui_win_is_activated(RTGUI_WIN(menu->parent_menu)) == RT_FALSE)
	{
		rtgui_menu_on_deactivate(RTGUI_WIDGET(menu->parent_menu), event);
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
		menu->items_list = rtgui_listctrl_create((rt_uint32_t)items, count, &rect, _rtgui_menu_item_ondraw); 
		RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(menu->items_list)) = rtgui_theme_default_bc();
		rtgui_container_add_child(RTGUI_CONTAINER(menu), RTGUI_WIDGET(menu->items_list));
		rtgui_listctrl_set_onitem(menu->items_list, _rtgui_menu_onitem);
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
	struct rtgui_event_resize eresize;

	if (menu == RT_NULL) return;

	/* set window extent */
	rect.x1 = 0; rect.y1 = 0;
	rect.x2 = 100; rect.y2 = menu->items_count * (rtgui_theme_get_selected_height() + 2) + 5;
	rtgui_rect_moveto(&rect, x, y);
	rtgui_win_set_rect(RTGUI_WIN(menu), &rect);
	rtgui_rect_inflate(&rect, -1);
	rtgui_widget_set_rect(RTGUI_WIDGET(menu->items_list), &rect);

	eresize.parent.type = RTGUI_EVENT_RESIZE;
	eresize.x = rect.x1; eresize.y = rect.y1;
	eresize.h = rect.y2 - rect.y1; eresize.w = rect.x2 - rect.x1;
	rtgui_listctrl_event_handler(RTGUI_WIDGET(menu->items_list), &(eresize.parent));

	/* on menu pop handler */
	if (menu->on_menupop != RT_NULL)
	{
		menu->on_menupop(RTGUI_WIDGET(menu), RT_NULL);
	}

	/* show menu window */
	rtgui_win_show(RTGUI_WIN(menu), RT_FALSE);
}

void rtgui_menu_hiden(struct rtgui_menu* menu)
{
	rtgui_win_hiden(RTGUI_WIN(menu));
	/* un-select item */
	menu->items_list->current_item = -1;

	if (menu->parent_menu != RT_NULL)
		rtgui_menu_hiden(menu->parent_menu);
}

