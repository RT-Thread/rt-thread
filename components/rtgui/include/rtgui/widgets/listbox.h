/*
 * File      : listbox.h
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-01-06     Bernard      first version
 */

#ifndef __RTGUI_LISTBOX_H__
#define __RTGUI_LISTBOX_H__

#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/widget.h>

struct rtgui_listbox_item
{
    char* name;
	rtgui_image_t *image;
};

DECLARE_CLASS_TYPE(listbox);
/** Gets the type of a list box */
#define RTGUI_LISTBOX_TYPE		(RTGUI_TYPE(listbox))
/** Casts the object to a filelist */
#define RTGUI_LISTBOX(obj)		(RTGUI_OBJECT_CAST((obj), RTGUI_LISTBOX_TYPE, rtgui_listbox_t))
/** Checks if the object is a filelist box */
#define RTGUI_IS_LISTBOX(obj)	(RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_LISTBOX_TYPE))

struct rtgui_listbox
{
	struct rtgui_widget parent;

	/* widget private data */
	/* listbox item */
    const struct rtgui_listbox_item* items;

	/* item event handler */
	void (*on_item)(rtgui_widget_t *widgets, struct rtgui_event* event);

	/* total number of items */
	rt_uint16_t items_count;
    /* the number of item in a page */
    rt_uint16_t page_items;
    /* current item */
    rt_int16_t current_item;
};
typedef struct rtgui_listbox rtgui_listbox_t;
typedef void (*rtgui_onitem_func_t)(struct rtgui_widget* widget, rtgui_event_t *event);

rtgui_listbox_t* rtgui_listbox_create(const struct rtgui_listbox_item* items, rt_uint16_t count,
    rtgui_rect_t *rect);
void rtgui_listbox_destroy(rtgui_listbox_t* box);

rt_bool_t rtgui_listbox_event_handler(struct rtgui_widget* widget, struct rtgui_event* event);
void rtgui_listbox_set_onitem(rtgui_listbox_t* box, rtgui_onitem_func_t func);
void rtgui_listbox_set_items(rtgui_listbox_t* box, struct rtgui_listbox_item* items, rt_uint16_t count);
void rtgui_listbox_set_current_item(rtgui_listbox_t* box, int index);

#endif

