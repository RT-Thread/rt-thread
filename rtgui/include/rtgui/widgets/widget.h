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
#include <rtgui/list.h>
#include <rtgui/region.h>
#include <rtgui/event.h>
#include <rtgui/color.h>
#include <rtgui/font.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RTGUI_WIDGET_FLAG_HIDE			0x01
#define RTGUI_WIDGET_FLAG_DISABLE		0x02
#define RTGUI_WIDGET_FLAG_FOCUS			0x04
#define RTGUI_WIDGET_FLAG_TRANSPARENT	0x08
#define RTGUI_WIDGET_FLAG_FOCUSABLE		0x10
#define RTGUI_WIDGET_FLAG_DEFAULT		0x00

#define RTGUI_WIDGET_UNHIDE(w)			(w)->flag &= ~RTGUI_WIDGET_FLAG_HIDE
#define RTGUI_WIDGET_HIDE(w)			(w)->flag |= RTGUI_WIDGET_FLAG_HIDE
#define RTGUI_WIDGET_IS_HIDE(w)			((w)->flag & RTGUI_WIDGET_FLAG_HIDE)

#define RTGUI_WIDGET_ENABLE(w)			(w)->flag &= ~RTGUI_WIDGET_FLAG_DISABLE
#define RTGUI_WIDGET_DISABLE(w)			(w)->flag |= RTGUI_WIDGET_FLAG_DISABLE
#define RTGUI_WIDGET_IS_ENABLE(w)		!(w->flag & RTGUI_WIDGET_FLAG_DISABLE)

#define RTGUI_WIDGET_UNFOCUS(w)			(w)->flag &= ~RTGUI_WIDGET_FLAG_FOCUS
#define RTGUI_WIDGET_FOCUS(w)			(w)->flag |= RTGUI_WIDGET_FLAG_FOCUS
#define RTGUI_WIDGET_IS_FOCUS(w)		((w)->flag & RTGUI_WIDGET_FLAG_FOCUS)

#define RTGUI_WIDGET_IS_FOCUSABLE(w) 	((w)->flag & RTGUI_WIDGET_FLAG_FOCUSABLE)

/* get rtgui widget object */
#define RTGUI_WIDGET_FOREGROUND(w) 		((w)->gc.foreground)
#define RTGUI_WIDGET_BACKGROUND(w)		((w)->gc.background)
#define RTGUI_WIDGET_TEXTALIGN(w)		((w)->gc.textalign)
#define RTGUI_WIDGET_FONT(w)			((w)->gc.font)
#define RTGUI_WIDGET_FLAG(w)			((w)->flag)

/** Gets the type of a widget */
#define RTGUI_WIDGET_TYPE       (rtgui_widget_type_get())
/** Casts the object to a rtgui_widget */
#define RTGUI_WIDGET(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_WIDGET_TYPE, rtgui_widget_t))
/** Check if the object is a rtgui_widget */
#define RTGUI_IS_WIDGET(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_WIDGET_TYPE))

struct rtgui_gc
{
	/* foreground and background color */
	rtgui_color_t foreground, background;

	/* text align */
	rt_base_t textalign;

	/* font */
	rtgui_font_t* font;
};
typedef struct rtgui_gc rtgui_gc_t;

/*
 * the base widget object
 */
struct rtgui_widget
{
   /* inherit from rtgui_object */
	struct rtgui_object object;

	/* the parent and root widget */
	struct rtgui_widget *parent, *toplevel;
	/* the widget children and sibling */
	rtgui_list_t sibling;

	/* widget flag */
	rt_int32_t flag;
	/* widget align */
	rt_int32_t align;

	/* the graphic context of widget */
	rtgui_gc_t gc;

	/* the widget extent */
	rtgui_rect_t extent;
#ifndef RTGUI_USING_SMALL_SIZE
	rt_int16_t mini_width, mini_height;
	rt_int16_t margin, margin_style;
#endif

	/* the rect clip */
	rtgui_region_t clip;
#ifndef RTGUI_USING_SMALL_SIZE
	rt_uint32_t clip_sync;
#endif

	/* the event handler */
	rt_bool_t (*event_handler)	(struct rtgui_widget* widget, struct rtgui_event* event);

	/* call back */
	rt_bool_t (*on_focus_in)	(struct rtgui_widget* widget, struct rtgui_event* event);
	rt_bool_t (*on_focus_out)	(struct rtgui_widget* widget, struct rtgui_event* event);
#ifndef RTGUI_USING_SMALL_SIZE
	rt_bool_t (*on_draw)		(struct rtgui_widget* widget, struct rtgui_event* event);
	rt_bool_t (*on_mouseclick)	(struct rtgui_widget* widget, struct rtgui_event* event);
	rt_bool_t (*on_key)			(struct rtgui_widget* widget, struct rtgui_event* event);
	rt_bool_t (*on_size)		(struct rtgui_widget* widget, struct rtgui_event* event);
	rt_bool_t (*on_command)		(struct rtgui_widget* widget, struct rtgui_event* event);
#endif
};
typedef struct rtgui_widget rtgui_widget_t;

rtgui_type_t *rtgui_widget_type_get(void);
rtgui_widget_t *rtgui_widget_create(rtgui_type_t *widget_type);
void rtgui_widget_destroy(rtgui_widget_t* widget);

/* initial a widget */
void rtgui_widget_init(rtgui_widget_t* widget, rtgui_type_t type, rtgui_rect_t* rect);
/* detach a widget */
void rtgui_widget_detach(rtgui_widget_t* widget);

/* update toplevel widget */
void rtgui_widget_update_toplevel(rtgui_widget_t* widget);

/* set the event handler of widget */
void rtgui_widget_set_event_handler(rtgui_widget_t* widget, rtgui_event_handler_ptr handler);
/* widget default event handler */
rt_bool_t rtgui_widget_event_handler(rtgui_widget_t* widget, rtgui_event_t* event);

/* dispatch event to child widget */
rt_bool_t rtgui_widget_dispatch_event(rtgui_widget_t* widget, rtgui_event_t* event);
rt_bool_t rtgui_widget_dispatch_mouse_event(rtgui_widget_t* widget, struct rtgui_event_mouse* event);

/* set and get widget label */
char* rtgui_widget_get_label(rtgui_widget_t* widget);
void rtgui_widget_set_label(rtgui_widget_t* widget, const char* label);

/* focus and unfocus */
void rtgui_widget_focus(rtgui_widget_t * widget);
void rtgui_widget_unfocus(rtgui_widget_t *widget);

/* event handler for each command */
void rtgui_widget_set_onfocus(rtgui_widget_t* widget, rtgui_event_handler_ptr handler);
void rtgui_widget_set_onunfocus(rtgui_widget_t* widget, rtgui_event_handler_ptr handler);
#ifndef RTGUI_USING_SMALL_SIZE
void rtgui_widget_set_ondraw(rtgui_widget_t* widget, rtgui_event_handler_ptr handler);
void rtgui_widget_set_onmouseclick(rtgui_widget_t* widget, rtgui_event_handler_ptr handler);
void rtgui_widget_set_onkey(rtgui_widget_t* widget, rtgui_event_handler_ptr handler);
void rtgui_widget_set_onsize(rtgui_widget_t* widget, rtgui_event_handler_ptr handler);
void rtgui_widget_set_oncommand(rtgui_widget_t* widget, rtgui_event_handler_ptr handler);
#endif

/* get and set rect of widget */
void rtgui_widget_get_rect(rtgui_widget_t* widget, rtgui_rect_t *rect);
void rtgui_widget_set_rect(rtgui_widget_t* widget, rtgui_rect_t* rect);

#ifndef RTGUI_USING_SMALL_SIZE
void rtgui_widget_set_miniwidth(rtgui_widget_t* widget, int width);
void rtgui_widget_set_miniheight(rtgui_widget_t* widget, int height);
#endif

/* get the physical position of a logic point on widget */
void rtgui_widget_point_to_device(rtgui_widget_t * widget, rtgui_point_t * point);
/* get the physical position of a logic rect on widget */
void rtgui_widget_rect_to_device(rtgui_widget_t * widget, rtgui_rect_t * rect);

/* get the logic position of a physical point on widget */
void rtgui_widget_point_to_logic(rtgui_widget_t* widget, rtgui_point_t * point);
/* get the logic position of a physical rect on widget */
void rtgui_widget_rect_to_logic(rtgui_widget_t* widget, rtgui_rect_t* rect);

/* move widget and its children to a logic point */
void rtgui_widget_move_to_logic(rtgui_widget_t* widget, int dx, int dy);

/* update the clip info of widget */
void rtgui_widget_update_clip(rtgui_widget_t* widget);

/* get the toplevel widget of widget */
rtgui_widget_t* rtgui_widget_get_toplevel(rtgui_widget_t* widget);

void rtgui_widget_show(rtgui_widget_t* widget);
void rtgui_widget_hide(rtgui_widget_t* widget);
void rtgui_widget_update(rtgui_widget_t* widget);

/* get the next sibling of widget */
rtgui_widget_t* rtgui_widget_get_next_sibling(rtgui_widget_t* widget);
/* get the prev sibling of widget */
rtgui_widget_t* rtgui_widget_get_prev_sibling(rtgui_widget_t* widget);

#ifdef __cplusplus
}
#endif

#endif
