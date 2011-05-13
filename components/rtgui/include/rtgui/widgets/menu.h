#ifndef __RTGUI_MENU_H__
#define __RTGUI_MENU_H__

#include <rtgui/image.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/listctrl.h>

/* rtgui menu item */
enum rtgui_menu_item_type
{
	RTGUI_ITEM_NORMAL,
	RTGUI_ITEM_CHECK,
	RTGUI_ITEM_SUBMENU,
	RTGUI_ITEM_SEPARATOR
};
typedef enum rtgui_menu_item_type rtgui_menu_item_type_t;

struct rtgui_menu_item
{
	rtgui_menu_item_type_t type;

	/* menu text label */
	const char* label;
	/* menu image */
	rtgui_image_t *image;

	/* sub-menu item */
	const struct rtgui_menu_item_t *submenu;
	rt_uint16_t submenu_count;

	/* menu action */
	rt_bool_t (*on_menuaction)(rtgui_widget_t* widget, rtgui_event_t* event);
};
typedef struct rtgui_menu_item rtgui_menu_item_t;

DECLARE_CLASS_TYPE(menu);
/** Gets the type of a menu */
#define RTGUI_MENU_TYPE       (RTGUI_TYPE(menu))
/** Casts the object to an rtgui_menu */
#define RTGUI_MENU(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_MENU_TYPE, rtgui_menu_t))
/** Checks if the object is an rtgui_menu */
#define RTGUI_IS_MENU(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_MENU_TYPE))

#define RTGUI_MENU_DEFAULT_WIDTH	100
struct rtgui_menu
{
	/* inherited from window */
	struct rtgui_win parent;

	/* menu items */
	const struct rtgui_menu_item *items;
	rt_uint16_t items_count;

	/* parent menu */
	struct rtgui_menu *parent_menu;
	struct rtgui_menu *sub_menu;

	/* menu item list control */
	struct rtgui_listctrl *items_list;

	/* pop event handle */
	rt_bool_t (*on_menupop)(rtgui_widget_t* widget, rtgui_event_t* event);
	rt_bool_t (*on_menuhide)(rtgui_widget_t* widget, rtgui_event_t* event);
};
typedef struct rtgui_menu rtgui_menu_t;

rtgui_type_t *rtgui_menu_type_get(void);

struct rtgui_menu* rtgui_menu_create(const char* title, struct rtgui_menu* parent_menu,
	const struct rtgui_menu_item* items, rt_uint16_t count);
void rtgui_menu_destroy(struct rtgui_menu* menu);

void rtgui_menu_set_onmenupop(struct rtgui_menu* menu, rtgui_event_handler_ptr handler);
void rtgui_menu_set_onmenuhide(struct rtgui_menu* menu, rtgui_event_handler_ptr handler);

void rtgui_menu_pop(struct rtgui_menu* menu, int x, int y);
void rtgui_menu_hiden(struct rtgui_menu* menu);

#endif

