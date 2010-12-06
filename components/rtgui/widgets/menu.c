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
	rtgui_box_t* box;
	rtgui_rect_t rect = {0, 0, RTGUI_MENU_DEFAULT_WIDTH, RTGUI_BORDER_DEFAULT_WIDTH << 1};

	/* set default rect */
	menu->width  = RTGUI_MENU_DEFAULT_WIDTH;
	menu->height = (RTGUI_BORDER_DEFAULT_WIDTH << 1);
	rtgui_widget_set_rect(RTGUI_WIDGET(menu), &rect);
	/* set window style */
	RTGUI_WIN(menu)->style = RTGUI_WIN_STYLE_NO_TITLE;

	/* set deactivate handler */
	rtgui_win_set_ondeactivate(RTGUI_WIN(menu), rtgui_menu_on_deactivate);

	/* set proper of control */
	menu->parent_item = RT_NULL;
	menu->select_item = RT_NULL;
	menu->on_menupop  = RT_NULL;
	menu->on_menuhide = RT_NULL;

	/* create box */
	box = rtgui_box_create(RTGUI_VERTICAL, &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(menu), RTGUI_WIDGET(box));
}

rtgui_type_t *rtgui_menu_type_get(void)
{
	static rtgui_type_t *menu_type = RT_NULL;

	if (!menu_type)
	{
		menu_type = rtgui_type_create("menu", RTGUI_WIN_TYPE,
			sizeof(rtgui_menu_t), RTGUI_CONSTRUCTOR(_rtgui_menu_constructor), RT_NULL);
	}

	return menu_type;
}

static rt_bool_t rtgui_menu_on_deactivate(rtgui_widget_t* widget, rtgui_event_t* event)
{
	rtgui_menu_t* menu = (rtgui_menu_t*) widget;

	if (menu->select_item != RT_NULL)
	{
		/* try to wake through to find sub menu activated */
		if (menu->select_item->type == RTGUI_ITEM_SUBMENU)
		{
			/* if sub menu activated, not hide menu */
			if (menu->select_item->sub_menu != RT_NULL &&
				rtgui_win_is_activated(RTGUI_WIN(menu->select_item->sub_menu)))
			{
				return RT_TRUE;
			}
		}
	}

	rtgui_win_hiden(RTGUI_WIN(menu));
	if (menu->on_menuhide != RT_NULL)
	{
		menu->on_menuhide(RTGUI_WIDGET(menu), RT_NULL);
	}

	/* if it's a submenu, try to hide parent menu */
	if (menu->parent_item != RT_NULL &&
		!rtgui_win_is_activated(RTGUI_WIN(menu->parent_item->parent_menu)))
	{
		rtgui_menu_on_deactivate(RTGUI_WIDGET(menu->parent_item->parent_menu), event);
	}

	/* unselected all items */
	if (menu->select_item != RT_NULL)
	{
		// rtgui_menu_item_unselect(menu->select_item);
	}

	return RT_TRUE;
}

struct rtgui_menu* rtgui_menu_create(const char* title)
{
    struct rtgui_menu* menu;

    menu = (struct rtgui_menu*) rtgui_widget_create ( RTGUI_MENU_TYPE );
	if (menu != RT_NULL)
	{
		rtgui_win_set_title(RTGUI_WIN(menu), title);
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

	/* layout box */
	box = (rtgui_box_t*) rtgui_container_get_first_child(RTGUI_CONTAINER(menu));
	RTGUI_WIDGET(box)->extent = rect;
	rtgui_box_layout(box);

	/* on menu pop handler */
	if (menu->on_menupop != RT_NULL)
	{
		menu->on_menupop(RTGUI_WIDGET(menu), RT_NULL);
	}

	/* show menu window */
	rtgui_win_show(RTGUI_WIN(menu), RT_FALSE);
}

rtgui_menu_item_t* rtgui_menu_item_new(struct rtgui_menu* menu, char* text, int type,
	rt_bool_t (*on_menu)(rtgui_widget_t* widget, rtgui_event_t* event))
{
	rtgui_menu_item_t* item;

	if (menu == RT_NULL) return RT_NULL;
	item = rtgui_menu_item_create(text);
	if (item == RT_NULL) return RT_NULL;

	item->type = type;
	item->image = RT_NULL;
	item->on_menuaction = on_menu;

	rtgui_menu_item_add(menu, item);

	return item;
}

rtgui_menu_item_t* rtgui_menu_item_new_separator(struct rtgui_menu* menu)
{
	rtgui_menu_item_t* item;

	if (menu == RT_NULL) return RT_NULL;

	item = rtgui_menu_item_create("--");
	if (item == RT_NULL) return RT_NULL;

	item->type = RTGUI_ITEM_SEPARATOR;
	item->image = RT_NULL;
	item->on_menuaction = RT_NULL;

	/* resize item extent */
	rtgui_widget_set_miniheight(RTGUI_WIDGET(item), 2);
	RTGUI_WIDGET(item)->extent.y2 = RTGUI_WIDGET(item)->extent.y1 + 2;

	rtgui_menu_item_add(menu, item);

	return item;
}

void rtgui_menu_item_add(struct rtgui_menu* menu, struct rtgui_menu_item* item)
{
	rtgui_box_t* box;

	if (menu == RT_NULL || item == RT_NULL) return;

	box = (rtgui_box_t*) rtgui_container_get_first_child(RTGUI_CONTAINER(menu));

	menu->height += rtgui_rect_height(RTGUI_WIDGET(item)->extent);
	if (menu->width < rtgui_rect_width(RTGUI_WIDGET(item)->extent) + RTGUI_MENU_IMAGE_MAGIN + RTGUI_MENU_SUBMENU_MAGIN)
	{
		menu->width = rtgui_rect_width(RTGUI_WIDGET(item)->extent) + RTGUI_MENU_IMAGE_MAGIN + RTGUI_MENU_SUBMENU_MAGIN;
	}

	item->parent_menu = menu;
	if (item->type == RTGUI_ITEM_SUBMENU)
	{
		item->sub_menu->parent_item = item;
	}

	rtgui_box_append(box, RTGUI_WIDGET(item));
}

struct rtgui_menu_item* rtgui_menu_get_first_item(struct rtgui_menu* menu)
{
	rtgui_box_t* box;
	rtgui_menu_item_t* item;

	if (menu == RT_NULL) return RT_NULL;

	box = (rtgui_box_t*) rtgui_container_get_first_child(RTGUI_CONTAINER(menu));
	if (box == RT_NULL) return RT_NULL;

	item = (rtgui_menu_item_t*) rtgui_container_get_first_child(RTGUI_CONTAINER(box));

	return item;
}
