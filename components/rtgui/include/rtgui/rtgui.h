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

#define RT_INT16_MAX		32767
#define RT_INT16_MIN		(-RT_INT16_MAX-1)
#define RTGUI_NOT_FOUND		(-1)

struct rtgui_event;

struct rtgui_object;
struct rtgui_widget;
struct rtgui_win;
struct rtgui_font;

typedef struct rtgui_win rtgui_win_t;
typedef rt_bool_t (*rtgui_event_handler_ptr)(struct rtgui_object* object, struct rtgui_event* event);
typedef void (*rtgui_onbutton_func_t)(struct rtgui_object* object, struct rtgui_event* event);

/**
 * Coordinate point
 */
struct rtgui_point
{
	rt_int16_t x, y;
};
typedef struct rtgui_point rtgui_point_t;
extern rtgui_point_t rtgui_empty_point;

/**
 * Rectangle structure
 */
struct rtgui_rect
{
	rt_int16_t x1, y1, x2, y2;
};
typedef struct rtgui_rect rtgui_rect_t;
#define rtgui_rect_width(r)		((r).x2 - (r).x1)
#define rtgui_rect_height(r)	((r).y2 - (r).y1)

typedef unsigned long rtgui_color_t;

/**
 * Graphic context
 */
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
typedef struct rtgui_gc rtgui_gc_t;

enum RTGUI_MARGIN_STYLE
{
	RTGUI_MARGIN_LEFT	= 0x01,
	RTGUI_MARGIN_RIGHT	= 0x02,
	RTGUI_MARGIN_TOP	= 0x04,
	RTGUI_MARGIN_BOTTOM = 0x08,
	RTGUI_MARGIN_ALL = RTGUI_MARGIN_LEFT | RTGUI_MARGIN_RIGHT | RTGUI_MARGIN_TOP | RTGUI_MARGIN_BOTTOM
};

/**
 * Border style 
 */
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

/**
 * Orientation
 */
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
	RTGUI_ALIGN_CENTER				= RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL,
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

