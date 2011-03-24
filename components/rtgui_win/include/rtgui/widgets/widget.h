/*
 * File      : widget.h
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
#ifndef __RTGUI_WIDGET_H__
#define __RTGUI_WIDGET_H__

#include <rtgui/rtgui.h>
#include <rtgui/color.h>
#include <rtgui/font.h>
#include <rtgui/list.h>
#include <rtgui/region.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rtgui_widget rtgui_widget_t;

/** Gets the type of a widget */
#define RTGUI_WIDGET_TYPE       (rtgui_widget_type_get())
/** Casts the object to a rtgui_widget */
#define RTGUI_WIDGET(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_WIDGET_TYPE, rtgui_widget_t))
/** Check if the object is a rtgui_widget */
#define RTGUI_IS_WIDGET(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_WIDGET_TYPE))

/*
 * the base widget object
 */
struct rtgui_widget
{
	rtgui_object_t 		object;				/* inherit from rtgui_object_t */
	rtgui_widget_t 		*parent, *toplevel;	/* the parent and root widget */
	rtgui_list_t 		sibling;			/* the widget child and sibling */
	rt_uint32_t 		flag;				/* widget flag */

	rt_uint32_t 		dc_type;			/* hardware device context */
	const struct rtgui_dc_engine* dc_engine;
	rtgui_gc_t 			gc;					/* the graphic context of widget */
	rt_uint16_t			tab_index;			/* table detect order */
	rt_uint16_t			tab_stop;
	rtgui_rect_t 		extent;				/* the widget extent */
	rt_uint32_t 		align;				/* widget align */
	rt_uint16_t 		border,border_style;
	rtgui_region_t 		clip; 				/* the rect clip */
	
	rt_bool_t (*event_handler)(PVOID wdt, rtgui_event_t* event);/* the event handler */
	
	rt_bool_t (*on_focus_in)(PVOID wdt, rtgui_event_t* event);/* call back */
	rt_bool_t (*on_focus_out)(PVOID wdt, rtgui_event_t* event);
	rt_bool_t (*on_draw)(PVOID wdt, rtgui_event_t* event);
	rt_bool_t (*on_mouseclick)(PVOID wdt, rtgui_event_t* event);
	rt_bool_t (*on_key)(PVOID wdt, rtgui_event_t* event);
	rt_bool_t (*on_size)(PVOID wdt, rtgui_event_t* event);
	rt_bool_t (*on_command)(PVOID wdt, rtgui_event_t* event);

	rt_uint32_t user_data;			/* reserved user data */
};

#define RTGUI_WIDGET_FOREGROUND(w)		(RTGUI_WIDGET(w))->gc.foreground
#define RTGUI_WIDGET_BACKGROUND(w)		(RTGUI_WIDGET(w))->gc.background
#define RTGUI_WIDGET_FONT(w)			(RTGUI_WIDGET(w))->gc.font
#define RTGUI_WIDGET_TEXTALIGN(w)		(RTGUI_WIDGET(w))->gc.textalign

#define RTGUI_WIDGET_FLAG(w)			(RTGUI_WIDGET(w))->flag
#define RTGUI_WIDGET_ALIGN(w)			(RTGUI_WIDGET(w))->align
#define RTGUI_WIDGET_EVENT_HANDLE(w)	(RTGUI_WIDGET(w))->event_handler 
#define RTGUI_WIDGET_EVENT_CALL(w,e)	(RTGUI_WIDGET(w))->event_handler(w,e) 
#define RTGUI_WIDGET_PARENT(w)			(RTGUI_WIDGET(w))->parent
#define RTGUI_WIDGET_EXTENT(w)			(RTGUI_WIDGET(w))->extent
#define RTGUI_WIDGET_BORDER(w)			(RTGUI_WIDGET(w))->border
#define RTGUI_WIDGET_BORDER_STYLE(w)	(RTGUI_WIDGET(w))->border_style
#define RTGUI_WIDGET_CLIP(w)			(RTGUI_WIDGET(w))->clip

#define RTGUI_WIDGET_FLAG_DEFAULT		0x0000	//默认
#define RTGUI_WIDGET_FLAG_HIDE			0x0001	//隐藏的
#define RTGUI_WIDGET_FLAG_DISABLE		0x0002	//无效的
#define RTGUI_WIDGET_FLAG_FOCUS			0x0004	//焦点的
#define RTGUI_WIDGET_FLAG_TRANSPARENT	0x0008	//透明的
#define RTGUI_WIDGET_FLAG_FOCUSABLE		0x0010	//可获得焦点的
#define RTGUI_WIDGET_FLAG_DC_VISIBLE	0x0100

#define RTGUI_WIDGET_UNHIDE(w)			RTGUI_WIDGET_FLAG(w) &= ~RTGUI_WIDGET_FLAG_HIDE
#define RTGUI_WIDGET_HIDE(w)			RTGUI_WIDGET_FLAG(w) |= RTGUI_WIDGET_FLAG_HIDE
#define RTGUI_WIDGET_IS_HIDE(w)			(RTGUI_WIDGET_FLAG(w) & RTGUI_WIDGET_FLAG_HIDE)

#define RTGUI_WIDGET_ENABLE(w)			RTGUI_WIDGET_FLAG(w) &= ~RTGUI_WIDGET_FLAG_DISABLE
#define RTGUI_WIDGET_DISABLE(w)			RTGUI_WIDGET_FLAG(w) |= RTGUI_WIDGET_FLAG_DISABLE
#define RTGUI_WIDGET_IS_ENABLE(w)		!(RTGUI_WIDGET_FLAG(w) &  RTGUI_WIDGET_FLAG_DISABLE)

#define RTGUI_WIDGET_UNFOCUS(w)			RTGUI_WIDGET_FLAG(w) &= ~RTGUI_WIDGET_FLAG_FOCUS
#define RTGUI_WIDGET_FOCUS(w)			RTGUI_WIDGET_FLAG(w) |= RTGUI_WIDGET_FLAG_FOCUS
#define RTGUI_WIDGET_IS_FOCUSED(w)		(RTGUI_WIDGET_FLAG(w) & RTGUI_WIDGET_FLAG_FOCUS)

#define RTGUI_WIDGET_IS_FOCUSABLE(w) 	(RTGUI_WIDGET_FLAG(w) & RTGUI_WIDGET_FLAG_FOCUSABLE)

#define RTGUI_WIDGET_IS_DC_VISIBLE(w)	(RTGUI_WIDGET_FLAG(w) & RTGUI_WIDGET_FLAG_DC_VISIBLE)
#define RTGUI_WIDGET_DC_SET_VISIBLE(w)	RTGUI_WIDGET_FLAG(w) |= RTGUI_WIDGET_FLAG_DC_VISIBLE 
#define RTGUI_WIDGET_DC_SET_UNVISIBLE(w) RTGUI_WIDGET_FLAG(w) &= ~RTGUI_WIDGET_FLAG_DC_VISIBLE
#define RTGUI_WIDGET_DC(w)				((rtgui_dc_t*)&(RTGUI_WIDGET(w)->dc_type))

rtgui_type_t *rtgui_widget_type_get(void);
PVOID rtgui_widget_create(rtgui_type_t *widget_type);
void rtgui_widget_destroy(PVOID wdt);

/* set the event handler of widget */
void rtgui_widget_set_event_handler(PVOID wdt, rtgui_event_handler_ptr handler);
/* widget default event handler */
rt_bool_t rtgui_widget_event_handler(PVOID wdt, rtgui_event_t* event);

/* focus and unfocus */
PVOID rtgui_widget_get_focus(PVOID wdt);
void rtgui_widget_focus(PVOID wdt);
void rtgui_widget_unfocus(PVOID wdt);

/* event handler for each command */
void rtgui_widget_set_onfocus(PVOID wdt, rtgui_event_handler_ptr handler);
void rtgui_widget_set_onunfocus(PVOID wdt, rtgui_event_handler_ptr handler);

void rtgui_widget_set_ondraw(PVOID wdt, rtgui_event_handler_ptr handler);
void rtgui_widget_set_onmouseclick(PVOID wdt, rtgui_event_handler_ptr handler);
void rtgui_widget_set_onkey(PVOID wdt, rtgui_event_handler_ptr handler);
void rtgui_widget_set_onsize(PVOID wdt, rtgui_event_handler_ptr handler);
void rtgui_widget_set_oncommand(PVOID wdt, rtgui_event_handler_ptr handler);

void rtgui_widget_get_rect(PVOID wdt, rtgui_rect_t *rect);/* get and set rect of widget */
void rtgui_widget_set_rect(PVOID wdt, rtgui_rect_t* rect);
void rtgui_widget_get_position(PVOID wdt, rtgui_point_t *p);
rt_uint16_t rtgui_widget_get_width(PVOID wdt);
rt_uint16_t rtgui_widget_get_height(PVOID wdt);

void rtgui_widget_set_style(PVOID wdt, rt_uint32_t style);
void rtgui_widget_point_to_device(PVOID wdt, rtgui_point_t *point);/* get the physical position of a logic point on widget */
void rtgui_widget_rect_to_device(PVOID wdt, rtgui_rect_t *rect);/* get the physical position of a logic rect on widget */
void rtgui_widget_point_to_logic(PVOID wdt, rtgui_point_t *point);/* get the logic position of a physical point on widget */
void rtgui_widget_rect_to_logic(PVOID wdt, rtgui_rect_t *rect);/* get the logic position of a physical rect on widget */
void rtgui_widget_move_to_logic(PVOID wdt, int dx, int dy);/* move widget and its child to a logic point */

/* update the clip info of widget */
void rtgui_widget_update_clip(PVOID wdt);
void rtgui_widget_update_clip_pirate(PVOID wdt,PVOID topwdt);

PVOID rtgui_widget_get_toplevel(PVOID wdt);	/* get the toplevel widget of widget */
void rtgui_widget_show(PVOID wdt);
void rtgui_widget_hide(PVOID wdt);
void rtgui_widget_update(PVOID wdt);
/* get parent color */
rtgui_color_t rtgui_widget_get_parent_foreground(PVOID wdt);
rtgui_color_t rtgui_widget_get_parent_background(PVOID wdt);
/* get the next sibling of widget */
rtgui_widget_t* rtgui_widget_get_next_sibling(PVOID wdt);
/* get the prev sibling of widget */
rtgui_widget_t* rtgui_widget_get_prev_sibling(PVOID wdt);

#ifdef __cplusplus
}
#endif

#endif
