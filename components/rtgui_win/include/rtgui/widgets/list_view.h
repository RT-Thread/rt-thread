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
#include <rtgui/kbddef.h>
#include <rtgui/color.h>
#include <rtgui/event.h>
#include <rtgui/widgets/view.h>

typedef void (*item_action)(void* parameter);
typedef struct rtgui_list_item	rtgui_list_view_item_t;
struct rtgui_list_item
{
    char* name;
	rtgui_image_t *image;
    item_action action;
    void *parameter;
};

/** Gets the type of a list view */
#define RTGUI_LIST_VIEW_TYPE       (rtgui_list_view_type_get())
/** Casts the object to a rtgui_list_view_t */
#define RTGUI_LIST_VIEW(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_LIST_VIEW_TYPE, rtgui_list_view_t))
/** Checks if the object is a rtgui_list_view_t */
#define RTGUI_IS_LIST_VIEW(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_LIST_VIEW_TYPE))

#define RTGUI_LIST_VIEW_LIST		0x00
#define RTGUI_LIST_VIEW_ICON		0x01
#define RTGUI_LIST_VIEW_REPORT		0x02

struct rtgui_list_view
{
	rtgui_view_t parent;

	/* widget private data */
	/* list item */
    const rtgui_list_view_item_t* items;

	/* layout flag */
	rt_uint16_t flag;

	/* total number of items */
	rt_uint16_t item_count;
    /* the number of item in a page */
    rt_uint16_t page;
	/* current item */
    rt_int16_t item_current;

	/* icon layout */
	rt_uint32_t row_items, col_items;
};
typedef struct rtgui_list_view rtgui_list_view_t;

rtgui_type_t *rtgui_list_view_type_get(void);

rtgui_list_view_t* rtgui_list_view_create(PVOID parent,const rtgui_list_view_item_t* items, rt_uint16_t count, int left,int top,int w,int h, rt_uint16_t flag);
void rtgui_list_view_destroy(rtgui_list_view_t* view);

rt_bool_t rtgui_list_view_event_handler(PVOID wdt, rtgui_event_t* event);

#endif

