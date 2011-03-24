#ifndef __RTGUI_CHECKBOX_H__
#define __RTGUI_CHECKBOX_H__

#include <rtgui/rtgui.h>


#define RTGUI_CHECKBOX_TYPE        (rtgui_checkbox_type_get())
#define RTGUI_CHECKBOX(obj)        (RTGUI_OBJECT_CAST((obj), RTGUI_CHECKBOX_TYPE, rtgui_checkbox_t))
#define RTGUI_IS_CHECKBOX(obj) (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_CHECKBOX_TYPE))

//#define RTGUI_CHECKBOX_STATUS_CHECKED		1
//#define RTGUI_CHECKBOX_STATUS_UNCHECKED	0

struct rtgui_checkbox
{
	/* inherit from label */
	rtgui_label_t parent;

	/* check box status */
	int value;
};
typedef struct rtgui_checkbox rtgui_checkbox_t;

rtgui_type_t *rtgui_checkbox_type_get(void);

rtgui_checkbox_t* rtgui_checkbox_create(PVOID wdt,const char* text, rt_bool_t checked,rtgui_color_t fc,int left,int top);
void rtgui_checkbox_destroy(rtgui_checkbox_t* checkbox);

void rtgui_checkbox_set_checked(rtgui_checkbox_t* checkbox, rt_bool_t checked);
rt_bool_t rtgui_checkbox_get_checked(rtgui_checkbox_t* checkbox);

rt_bool_t rtgui_checkbox_event_handler(PVOID wdt, rtgui_event_t* event);
void rtgui_checkbox_set_text(rtgui_checkbox_t *box, const char* text);

#endif
