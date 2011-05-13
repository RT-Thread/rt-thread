/*
 * File      : button.h
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
#ifndef __RTGUI_BUTTON_H__
#define __RTGUI_BUTTON_H__

#include <rtgui/image.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/label.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup rtgui_button
 * @{
 */

DECLARE_CLASS_TYPE(button);

/** Gets the type of a button */
#define RTGUI_BUTTON_TYPE       (RTGUI_TYPE(button))
/** Casts the object to an rtgui_button */
#define RTGUI_BUTTON(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_BUTTON_TYPE, rtgui_button_t))
/** Checks if the object is an rtgui_button */
#define RTGUI_IS_BUTTON(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_BUTTON_TYPE))

#define RTGUI_BUTTON_FLAG_PRESS		0x01
#define RTGUI_BUTTON_FLAG_DEFAULT	0x02

#define RTGUI_BUTTON_TYPE_NORMAL	0x00
#define RTGUI_BUTTON_TYPE_PUSH		0x10

/*
 * the button widget
 */
struct rtgui_button
{
	/* inherit from label */
	struct rtgui_label parent;

	/* button flag */
	rt_base_t flag;

	/* pressed and unpressed image */
	rtgui_image_t *pressed_image, *unpressed_image;

	/* click button event handler */
	void (*on_button)(struct rtgui_widget* widget, rtgui_event_t *event);
};
typedef struct rtgui_button rtgui_button_t;

rtgui_button_t* rtgui_button_create(const char* text);
rtgui_button_t* rtgui_pushbutton_create(const char* text);
void rtgui_button_destroy(rtgui_button_t* btn);

void rtgui_button_set_pressed_image(rtgui_button_t* btn, rtgui_image_t* image);
void rtgui_button_set_unpressed_image(rtgui_button_t* btn, rtgui_image_t* image);

void rtgui_button_set_onbutton(rtgui_button_t* btn, rtgui_onbutton_func_t func);

rt_bool_t rtgui_button_event_handler(struct rtgui_widget* widget, struct rtgui_event* event);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
