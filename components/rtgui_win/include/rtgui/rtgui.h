/*
 * File      : rtgui.h
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-04     Bernard      first version
 */
#ifndef __RT_GUI_H__
#define __RT_GUI_H__

#include <rtthread.h>
#include <rtgui/rtgui_config.h>
#include <string.h>

#define RT_INT16_MAX		32767
#define RT_INT16_MIN		(-RT_INT16_MAX-1)

#define SELECTED_HEIGHT			20	//已选择行的高度

#define RT_COUNT(array)	sizeof(array)/sizeof(array[0])

/* Use new name & namespace */
typedef struct rtgui_point      rtgui_point_t;
typedef struct rtgui_rect       rtgui_rect_t;
typedef rt_uint32_t             rtgui_color_t;
typedef struct rtgui_event      rtgui_event_t;
typedef struct rtgui_font       rtgui_font_t;
typedef struct rtgui_dc         rtgui_dc_t;
typedef struct rtgui_gc         rtgui_gc_t;

typedef void*                   PVOID;
typedef struct rtgui_type       rtgui_type_t;
typedef struct rtgui_object     rtgui_object_t;
typedef struct rtgui_widget     rtgui_widget_t;
typedef struct rtgui_panel      rtgui_panel_t;
typedef struct rtgui_container  rtgui_container_t;
typedef struct rtgui_win        rtgui_win_t;
typedef struct rtgui_staticline rtgui_staticline_t;
typedef struct rtgui_label      rtgui_label_t;
typedef struct rtgui_textbox    rtgui_textbox_t;
typedef struct rtgui_button     rtgui_button_t;
typedef struct rtgui_view       rtgui_view_t;
typedef struct rtgui_checkbox   rtgui_checkbox_t;
typedef struct rtgui_radiobox   rtgui_radiobox_t;
typedef struct rtgui_listbox    rtgui_listbox_t;
typedef struct rtgui_list_view  rtgui_list_view_t;
typedef struct rtgui_fileview   rtgui_filelist_view_t;
typedef struct rtgui_scrollbar  rtgui_scrollbar_t;
typedef struct rtgui_iconbox    rtgui_iconbox_t;
typedef struct rtgui_menu_item  rtgui_menu_item_t;
typedef struct rtgui_menu       rtgui_menu_t;
typedef struct rtgui_combo      rtgui_combo_t;


typedef rt_bool_t (*rtgui_event_handler_ptr)(PVOID wdt, rtgui_event_t* event);

struct rtgui_point
{
	rt_int16_t x, y;
};

struct rtgui_rect
{
	rt_int16_t x1, y1, x2, y2;
};

extern rtgui_point_t rtgui_empty_point;

#define rtgui_rect_width(r)     ((r).x2 - (r).x1)
#define rtgui_rect_height(r)    ((r).y2 - (r).y1)

struct rtgui_gc
{
	/* foreground and background color */
	rtgui_color_t foreground, background;

	/* text style */
	rt_uint16_t textstyle;
	/* text align */
	rt_uint16_t textalign;

	/* font */
	struct rtgui_font* font;
};

enum RTGUI_MARGIN_STYLE
{
	RTGUI_MARGIN_LEFT	= 0x01,
	RTGUI_MARGIN_RIGHT	= 0x02,
	RTGUI_MARGIN_TOP	= 0x04,
	RTGUI_MARGIN_BOTTOM = 0x08,
	RTGUI_MARGIN_ALL = (RTGUI_MARGIN_LEFT | RTGUI_MARGIN_RIGHT | RTGUI_MARGIN_TOP | RTGUI_MARGIN_BOTTOM)
};

enum RTGUI_BORDER_STYLE
{
	RTGUI_BORDER_NONE = 0,
	RTGUI_BORDER_SIMPLE,
	RTGUI_BORDER_RAISE,
	RTGUI_BORDER_SUNKEN,
	RTGUI_BORDER_BOX,
	RTGUI_BORDER_STATIC,
	RTGUI_BORDER_EXTRA,
	RTGUI_BORDER_UP,
	RTGUI_BORDER_DOWN
};

#define RTGUI_BORDER_DEFAULT_WIDTH	2
#define RTGUI_WIDGET_DEFAULT_MARGIN	3

enum RTGUI_ORIENTATION
{
    RTGUI_HORIZONTAL		= 0x01,
	RTGUI_VERTICAL			= 0x02,
	RTGUI_ORIENTATION_BOTH	= RTGUI_HORIZONTAL | RTGUI_VERTICAL
};

enum RTGUI_ALIGN
{
	RTGUI_ALIGN_NOT					= 0x00,
	RTGUI_ALIGN_CENTER_HORIZONTAL	= 0x01,
	RTGUI_ALIGN_LEFT				= RTGUI_ALIGN_NOT,
	RTGUI_ALIGN_TOP					= RTGUI_ALIGN_NOT,
	RTGUI_ALIGN_RIGHT				= 0x02,
	RTGUI_ALIGN_BOTTOM				= 0x04,
	RTGUI_ALIGN_CENTER_VERTICAL		= 0x08,
	RTGUI_ALIGN_EXPAND				= 0x10,
	RTGUI_ALIGN_STRETCH				= 0x20,
};

enum RTGUI_TEXTSTYLE
{
	RTGUI_TEXTSTYLE_NORMAL 			= 0x00,
	RTGUI_TEXTSTYLE_DRAW_BACKGROUND = 0x01,
	RTGUI_TEXTSTYLE_SHADOW 			= 0x02,
	RTGUI_TEXTSTYLE_OUTLINE 		= 0x04,
};

enum RTGUI_MODAL_CODE
{
	RTGUI_MODAL_OK,
	RTGUI_MODAL_CANCEL
};
typedef enum RTGUI_MODAL_CODE rtgui_modal_code_t;

#include <rtgui/rtgui_object.h>

#endif
