#ifndef __RTGUI_COMBOBOX_H__
#define __RTGUI_COMBOBOX_H__

#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/widgets/window.h>

/* combobox item */
struct rtgui_combobox_item
{
    char* name;
	rtgui_image_t *image;
};

/** Gets the type of a combobox */
#define RTGUI_COMBOBOX_TYPE       (rtgui_combobox_type_get())
/** Casts the object to a rtgui_combobox */
#define RTGUI_COMBOBOX(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_COMBOBOX_TYPE, rtgui_combobox_t))
/** Checks if the object is a rtgui_combobox */
#define RTGUI_IS_COMBOBOX(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_COMBOBOX_TYPE))

#define RTGUI_COMBOBOX_WIDTH		75
#define RTGUI_COMBOBOX_HEIGHT		20
#define RTGUI_COMBOBOX_BUTTON_WIDTH	18

struct rtgui_combobox
{
	struct rtgui_widget parent;

	/* widget private data */

	/* pull down window */
	struct rtgui_win* pd_win;
	rt_bool_t pd_pressed;
	rt_uint16_t pd_win_width;
	rt_uint16_t pd_win_height;

	/* combobox items */
	struct rtgui_combobox_item* items;
	rt_uint16_t items_count;
	rt_uint16_t current_item;

	/* call back */
	rt_bool_t (*on_selected) (struct rtgui_widget* widget, struct rtgui_event* event);
};
typedef struct rtgui_combobox rtgui_combobox_t;

rtgui_type_t *rtgui_combobox_type_get(void);
rtgui_combobox_t *rtgui_combobox_create();
void rtgui_combobox_destroy(rtgui_combobox_t* box);

rt_bool_t rtgui_combobox_event_handler(struct rtgui_widget* widget, struct rtgui_event* event);
struct rtgui_combobox_item* rtgui_combox_get_select(struct rtgui_combobox* box);

#endif
