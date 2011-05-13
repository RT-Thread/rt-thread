#ifndef __RTGUI_CHECKBOX_H__
#define __RTGUI_CHECKBOX_H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/label.h>

DECLARE_CLASS_TYPE(checkbox);

/** Gets the type of a checkbox */
#define RTGUI_CHECKBOX_TYPE       (RTGUI_TYPE(checkbox))
/** Casts the object to an rtgui_button */
#define RTGUI_CHECKBOX(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_CHECKBOX_TYPE, rtgui_checkbox))
/** Checks if the object is an rtgui_button */
#define RTGUI_IS_CHECKBOX(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_CHECKBOX_TYPE))

#define RTGUI_CHECKBOX_STATUS_CHECKED		0
#define RTGUI_CHECKBOX_STATUS_UNCHECKED		1

struct rtgui_checkbox
{
	/* inherit from label */
	struct rtgui_label parent;

	/* check box status */
	rt_uint8_t status_down;

	/* click button event handler */
	void (*on_button)(struct rtgui_widget* widget, rtgui_event_t *event);
};
typedef struct rtgui_checkbox rtgui_checkbox_t;

rtgui_checkbox_t* rtgui_checkbox_create(const char* text, rt_bool_t checked);
void rtgui_checkbox_destroy(rtgui_checkbox_t* checkbox);

void rtgui_checkbox_set_checked(rtgui_checkbox_t* checkbox, rt_bool_t checked);
rt_bool_t rtgui_checkbox_get_checked(rtgui_checkbox_t* checkbox);

void rtgui_checkbox_set_onbutton(rtgui_checkbox_t* checkbox, rtgui_onbutton_func_t func);

rt_bool_t rtgui_checkbox_event_handler(struct rtgui_widget* widget, struct rtgui_event* event);

#endif
