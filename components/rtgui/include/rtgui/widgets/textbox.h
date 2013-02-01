/*
* File      : textbox.h
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
#ifndef __RTGUI_TEXTBOX_H__
#define __RTGUI_TEXTBOX_H__

#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/container.h>

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_CLASS_TYPE(textbox);

/** Gets the type of a textbox */
#define RTGUI_TEXTBOX_TYPE       (RTGUI_TYPE(textbox))
/** Casts the object to a rtgui_textbox_t */
#define RTGUI_TEXTBOX(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_TEXTBOX_TYPE, rtgui_textbox_t))
/** Checks if the object is a rtgui_textbox_t */
#define RTGUI_IS_TEXTBOX(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_TEXTBOX_TYPE))

#define RTGUI_TEXTBOX_DEFAULT_WIDTH     80
#define RTGUI_TEXTBOX_DEFAULT_HEIGHT        20

#define RTGUI_TEXTBOX_BORDER_WIDTH     1

#define RTGUI_TEXTBOX_SINGLE        0x00
#define RTGUI_TEXTBOX_MULTI         0x01 /* multiline */
#define RTGUI_TEXTBOX_MASK          0x02 /* ciphertext */
#define RTGUI_TEXTBOX_DIGIT         0x04 /* digit */
#define RTGUI_TEXTBOX_CARET_SHOW    0x10
#define RTGUI_TEXTBOX_CARET_STAT    0x20 /* unused */

#define RTGUI_TEXTBOX_LINE_MAX      128  /* text line cache */

struct rtgui_textbox
{
	/* inherit from widget */
	struct rtgui_widget parent;

	/* text box flag */
	rt_uint32_t flag;

	/* current line and position */
	rt_uint16_t line, line_begin, position;
    /** maximum chars a line could hold excluding the NULL byte */
    rt_uint16_t line_length;
	rt_uint16_t dis_length; /*may be display length.*/
	rt_uint16_t first_pos;
	char mask_char;
    /** a NULL terminated string that the textbox is holding */
	char *text;
	rt_size_t font_width;

	rtgui_timer_t *caret_timer;
	rtgui_color_t *caret;
	rtgui_rect_t  caret_rect;

	/* textbox private data */
	rt_bool_t (*on_enter)(struct rtgui_textbox *box, rtgui_event_t *event);
};
typedef struct rtgui_textbox rtgui_textbox_t;

rtgui_textbox_t *rtgui_textbox_create(const char *text, rt_uint32_t flag);
void rtgui_textbox_destroy(struct rtgui_textbox *box);

rt_bool_t rtgui_textbox_event_handler(struct rtgui_object *object, struct rtgui_event *event);

void rtgui_textbox_set_value(struct rtgui_textbox *box, const char *text);
const char *rtgui_textbox_get_value(struct rtgui_textbox *box);
void rtgui_textbox_set_mask_char(rtgui_textbox_t *box, const char ch);
char rtgui_textbox_get_mask_char(rtgui_textbox_t *box);
/** set the maximum chars a line could hold excluding the NULL byte
 *
 * It will truncate the current line if the length is smaller than the chars
 * the box is currently holding. But the box->text is guaranteed to be NULL
 * terminated anyway.
 *
 * @param box the text box it operate on
 * @param length the new line length. It should be greater than 0.
 *
 * @return -RT_ERROR on invalid length; -RT_ENOMEM if there is no enough memory
 * to allocate the new buffer. On returning -RT_ENOMEM, the original text would
 * remain unchanged.
 */
rt_err_t rtgui_textbox_set_line_length(struct rtgui_textbox *box, rt_size_t length);

void rtgui_textbox_get_edit_rect(struct rtgui_textbox *box, rtgui_rect_t *rect);

void rtgui_textbox_ondraw(rtgui_textbox_t *box);
#ifdef __cplusplus
}
#endif

#endif
