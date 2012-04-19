/*
 * File      : list_view.h
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

#ifndef __RTGUI_LIST_VIEW_H__
#define __RTGUI_LIST_VIEW_H__

#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>

#include <rtgui/widgets/container.h>

typedef void (*item_action)(struct rtgui_widget* widget, void* parameter);
struct rtgui_list_item
{
    char* name;
	rtgui_image_t *image;

    item_action action;
    void *parameter;
};

DECLARE_CLASS_TYPE(listview);
/** Gets the type of a list view */
#define RTGUI_LIST_VIEW_TYPE       (RTGUI_TYPE(listview))
/** Casts the object to a filelist */
#define RTGUI_LIST_VIEW(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_LIST_VIEW_TYPE, rtgui_list_view_t))
/** Checks if the object is a filelist view */
#define RTGUI_IS_LIST_VIEW(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_LIST_VIEW_TYPE))

#define RTGUI_LIST_VIEW_LIST		0x00
#define RTGUI_LIST_VIEW_ICON		0x01
#define RTGUI_LIST_VIEW_REPORT		0x02

struct rtgui_list_view
{
	struct rtgui_container parent;

	/* widget private data */
	/* list item */
    const struct rtgui_list_item* items;

	/* layout flag */
	rt_uint16_t flag;

	/* total number of items */
	rt_uint16_t items_count;
    /* the number of item in a page */
    rt_uint16_t page_items;
	/* current item */
    rt_int16_t current_item;

	/* icon layout */
	rt_uint8_t row_items, col_items;
};
typedef struct rtgui_list_view rtgui_list_view_t;

rtgui_list_view_t* rtgui_list_view_create(const struct rtgui_list_item* items, rt_uint16_t count,
    rtgui_rect_t *rect, rt_uint16_t flag);
void rtgui_list_view_destroy(rtgui_list_view_t* view);

rt_bool_t rtgui_list_view_event_handler(struct rtgui_object* widget, struct rtgui_event* event);

#endif

