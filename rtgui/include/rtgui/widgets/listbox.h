/*
 * File      : listbox.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-16     Bernard      first version
 */
#ifndef __RTGUI_LISTBOX_H__
#define __RTGUI_LISTBOX_H__

#include <rtgui/widgets/item.h>
#include <rtgui/widgets/scrollview.h>

#define RTGUI_LISTBOX_WIDTH	    150
#define RTGUI_LISTBOX_HEIGHT    200

/** Gets the type of a listbox */
#define RTGUI_LISTBOX_TYPE       (rtgui_listbox_type_get())
/** Casts the object to a rtgui_listbox */
#define RTGUI_LISTBOX(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_LISTBOX_TYPE, rtgui_listbox_t))
/** Checks if the object is a rtgui_listbox */
#define RTGUI_IS_LISTBOX(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_LISTBOX_TYPE))

/*
* the listbox widget
*/
struct rtgui_listbox
{
	struct rtgui_scrollview parent;

	/* widget private data */
	int flag;

	/* total number of items */
	rt_uint32_t count;

	/* the selected item */
	struct rtgui_item* selected;

	/* call back */
	rt_bool_t (*on_selected)  (struct rtgui_widget* widget, struct rtgui_event* event);
	rt_bool_t (*on_activated) (struct rtgui_widget* widget, struct rtgui_event* event);
};
typedef struct rtgui_listbox rtgui_listbox_t;

rtgui_type_t *rtgui_listbox_type_get(void);

rtgui_listbox_t* rtgui_listbox_create(void);
void rtgui_listbox_destroy(rtgui_listbox_t* listbox);

rt_bool_t rtgui_listbox_event_handler(struct rtgui_widget* widget, struct rtgui_event* event);

struct rtgui_item* rtgui_listbox_get_select(struct rtgui_listbox* box);
void rtgui_listbox_set_select(struct rtgui_listbox* box, rt_uint32_t index);
void rtgui_listbox_set_select_item(struct rtgui_listbox* box, struct rtgui_item* item);

struct rtgui_item* rtgui_listbox_add_item_string(struct rtgui_listbox* box, const unsigned char* text);
void rtgui_listbox_add_item(struct rtgui_listbox* list, struct rtgui_item* item);

#endif
