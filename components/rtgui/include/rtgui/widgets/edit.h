/*
 * File      : edit.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-06-04     amsl         first version
 */
#ifndef __RTGUI_EDIT_H__
#define __RTGUI_EDIT_H__

#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/container.h>

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_CLASS_TYPE(edit);

/** Gets the type of a edit */
#define RTGUI_EDIT_TYPE       (RTGUI_TYPE(edit))
/** Casts the object to a rtgui_edit */
#define RTGUI_EDIT(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_EDIT_TYPE, struct rtgui_edit))
/** Checks if the object is a rtgui_edit */
#define RTGUI_IS_EDIT(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_EDIT_TYPE))

#define RTGUI_EDIT_NONE				0x00
#define RTGUI_EDIT_CARET			0x01
#define RTGUI_EDIT_VSCROLL			0x02
#define RTGUI_EDIT_HSCROLL			0x04
#define RTGUI_EDIT_SHIFT			0x10
#define RTGUI_EDIT_CTRL				0x20
#define RTGUI_EDIT_ALT				0x40
#define RTGUI_EDIT_CAPSLOCK			0x80
#define RTGUI_EDIT_NUMLOCK			0x100

struct edit_update
{
	/* rt_uint32_t type; */ /* update type */
	rtgui_point_t start, end; /* update area */
};

struct edit_line
{
	rt_int16_t  zsize; /* zone size */
	rt_int16_t  len;
	struct edit_line *prev;
	struct edit_line *next;
	char        *text;
};

struct rtgui_edit
{
	/* inherit from container */
	rtgui_container_t parent;

	/* edit flag */
	rt_uint32_t   flag;
	rt_int16_t    max_rows, max_cols;
	rt_int16_t    row_per_page, col_per_page;
	rtgui_point_t upleft;
	rtgui_point_t visual;
	rt_uint8_t    tabsize;
	rt_uint8_t    item_height;
	rt_uint8_t    font_width,font_height;
	rt_uint8_t    margin;
	rt_int16_t    bzsize; /* base zone size */
	
	struct rtgui_timer *caret_timer;
	rtgui_color_t *caret;
	rtgui_rect_t  caret_rect;
	struct edit_update update;
	char          *update_buf; /* speed up renewal process */
	struct rtgui_dc *dbl_buf;
	
	struct edit_line  *head;
	struct edit_line  *tail;
	struct edit_line  *first_line;
#ifdef RTGUI_EDIT_USING_SCROLL
	struct rtgui_scrollbar *hscroll;
	struct rtgui_scrollbar *vscroll;
#endif
};

rt_bool_t rtgui_edit_append_line(struct rtgui_edit *edit, const char *text);
rt_bool_t rtgui_edit_insert_line(struct rtgui_edit *edit, struct edit_line *p, char *text);
rt_bool_t rtgui_edit_delete_line(struct rtgui_edit *edit, struct edit_line *line);
rt_bool_t rtgui_edit_connect_line(struct rtgui_edit *edit, struct edit_line *line, struct edit_line *connect);

void _rtgui_edit_constructor(struct rtgui_edit *box);
void _rtgui_edit_deconstructor(struct rtgui_edit *textbox);

struct rtgui_edit* rtgui_edit_create(struct rtgui_container* container, int left, int top, int w, int h);
void rtgui_edit_destroy(struct rtgui_edit *edit);
void rtgui_edit_update(struct rtgui_edit *edit);
void rtgui_edit_ondraw(struct rtgui_edit *edit);
rt_bool_t rtgui_edit_event_handler(struct rtgui_object* object, rtgui_event_t* event);
void rtgui_edit_set_text(struct rtgui_edit *edit, const char* text);
rtgui_point_t rtgui_edit_get_current_point(struct rtgui_edit *edit);
rt_uint32_t rtgui_edit_get_mem_consume(struct rtgui_edit *edit);
rt_bool_t rtgui_edit_readin_file(struct rtgui_edit *edit, const char *filename);
rt_bool_t rtgui_edit_saveas_file(struct rtgui_edit *edit, const char *filename);

#ifdef __cplusplus
}
#endif

#endif
