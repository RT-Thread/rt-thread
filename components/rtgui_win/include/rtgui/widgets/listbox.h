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
#include <rtgui/kbddef.h>
#include <rtgui/color.h>
#include <rtgui/image.h>

struct rtgui_listbox_item
{
    char *name;
	rtgui_image_t *image;
};
typedef struct rtgui_listbox_item	rtgui_listbox_item_t;
/** Gets the type of a list box */
#define RTGUI_LISTBOX_TYPE		(rtgui_listbox_type_get())
/** Casts the object to a filelist */
#define RTGUI_LISTBOX(obj)		(RTGUI_OBJECT_CAST((obj), RTGUI_LISTBOX_TYPE, rtgui_listbox_t))
/** Checks if the object is a filelist box */
#define RTGUI_IS_LISTBOX(obj)	(RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_LISTBOX_TYPE))

typedef struct rtgui_listbox rtgui_listbox_t;

struct rtgui_listbox
{
	rtgui_container_t parent;

	/* widget private data */
	rt_int16_t  		item_per_page;  /* the number of item in a page */
	rt_int16_t  		item_count;	    /* total number of items */
	rt_int16_t			item_size;		/* item size */
    rt_int16_t  		frist_aloc;     /* frist item */
	rt_int16_t  		now_aloc;       /* now item */
	rt_int16_t  		old_aloc;       /* old item */
	rt_bool_t			ispopup;	    /* 是弹出类型列表 */
	PVOID 		widgetlnk;		/* 链接的控件 */
	rtgui_scrollbar_t  	*sbar;
    rtgui_listbox_item_t *items;	    /* items array */
	
	/* item event handler */
	rt_bool_t (*on_item)(PVOID wdt, rtgui_event_t* event);

	rt_uint32_t (*get_count)(rtgui_listbox_t* box);
	void (*add_item)(rtgui_listbox_t* box, rtgui_listbox_item_t* item);
};


rtgui_type_t *rtgui_listbox_type_get(void);

rtgui_listbox_t* rtgui_listbox_create(PVOID wdt, int left,int top,int w,int h,rt_uint32_t style);
void rtgui_listbox_destroy(rtgui_listbox_t* box);

void rtgui_listbox_update(rtgui_listbox_t* box);
rt_bool_t rtgui_listbox_event_handler(PVOID wdt, rtgui_event_t* event);
void rtgui_listbox_set_onitem(rtgui_listbox_t* box, rtgui_event_handler_ptr func);
void rtgui_listbox_set_items(rtgui_listbox_t* box, rtgui_listbox_item_t* items, rt_uint32_t count);

void rtgui_listbox_delete_item(rtgui_listbox_t* box, rt_uint32_t item_num);

#endif

