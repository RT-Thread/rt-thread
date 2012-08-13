/*
 * File      : iconbox.h
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
#ifndef __RTGUI_ICONBOX_H__
#define __RTGUI_ICONBOX_H__

#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/widgets/widget.h>

DECLARE_CLASS_TYPE(iconbox);
/** Gets the type of a iconbox */
#define RTGUI_ICONBOX_TYPE       (RTGUI_TYPE(iconbox))
/** Casts the object to a rtgui_iconbox */
#define RTGUI_ICONBOX(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_ICONBOX_TYPE, rtgui_iconbox_t))
/** Checks if the object is a rtgui_iconbox */
#define RTGUI_IS_ICONBOX(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_ICONBOX_TYPE))

#define RTGUI_ICONBOX_NOTEXT		0x00
#define RTGUI_ICONBOX_TEXT_RIGHT	0x01
#define RTGUI_ICONBOX_TEXT_BELOW	0x02

struct rtgui_iconbox
{
	/* inherit from widget */
	struct rtgui_widget parent;

	/* widget private data */
	struct rtgui_image* image;

	char *text;
	rt_ubase_t text_position;

	rt_bool_t selected;
};
typedef struct rtgui_iconbox rtgui_iconbox_t;

struct rtgui_iconbox* rtgui_iconbox_create(struct rtgui_image* image, const char* text, int position);
void rtgui_iconbox_destroy(struct rtgui_iconbox* iconbox);

rt_bool_t rtgui_iconbox_event_handler(struct rtgui_object* object, struct rtgui_event* event);

void rtgui_iconbox_set_text_position(struct rtgui_iconbox* iconbox, int position);
void rtgui_iconbox_set_selected(struct rtgui_iconbox* iconbox, rt_bool_t selected);

#endif
